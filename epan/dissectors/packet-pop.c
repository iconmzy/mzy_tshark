/* packet-pop.c
 * Routines for pop packet dissection
 * RFC 1939
 * Copyright 1999, Richard Sharpe <rsharpe@ns.aus.com>
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * Copied from packet-tftp.c
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "config.h"

#include <stdlib.h>

#include <epan/packet.h>
#include <epan/strutil.h>
#include <epan/conversation.h>
#include <epan/prefs.h>
#include <epan/reassemble.h>
#include <epan/proto_data.h>
#include <epan/expert.h>

#include <wsutil/str_util.h>
#include <wsutil/strtoi.h>

#include <ui/tap-credentials.h>
#include <tap.h>

#include "packet-tls.h"
#include "packet-tls-utils.h"

void proto_register_pop(void);
void proto_reg_handoff_pop(void);

static int proto_pop = -1;

static int credentials_tap = -1;

static int hf_pop_response = -1;
static int hf_pop_response_indicator = -1;
static int hf_pop_response_description = -1;
static int hf_pop_response_data = -1;

static int hf_pop_request = -1;
static int hf_pop_request_command = -1;
static int hf_pop_request_parameter = -1;
static int hf_pop_request_data = -1;

static int hf_pop_data_fragments = -1;
static int hf_pop_data_fragment = -1;
static int hf_pop_data_fragment_overlap = -1;
static int hf_pop_data_fragment_overlap_conflicts = -1;
static int hf_pop_data_fragment_multiple_tails = -1;
static int hf_pop_data_fragment_too_long_fragment = -1;
static int hf_pop_data_fragment_error = -1;
static int hf_pop_data_fragment_count = -1;
static int hf_pop_data_reassembled_in = -1;
static int hf_pop_data_reassembled_length = -1;

static expert_field ei_pop_resp_tot_len_invalid = EI_INIT;

static gint ett_pop = -1;
static gint ett_pop_reqresp = -1;

static gint ett_pop_data_fragment = -1;
static gint ett_pop_data_fragments = -1;

static dissector_handle_t pop_handle;
static dissector_handle_t imf_handle;
static dissector_handle_t tls_handle;

#define TCP_PORT_POP            110
#define TCP_PORT_SSL_POP        995

/* desegmentation of POP command and response lines */
static gboolean pop_data_desegment = TRUE;

static reassembly_table pop_data_reassembly_table;

static const fragment_items pop_data_frag_items = {
  /* Fragment subtrees */
  &ett_pop_data_fragment,
  &ett_pop_data_fragments,
  /* Fragment fields */
  &hf_pop_data_fragments,
  &hf_pop_data_fragment,
  &hf_pop_data_fragment_overlap,
  &hf_pop_data_fragment_overlap_conflicts,
  &hf_pop_data_fragment_multiple_tails,
  &hf_pop_data_fragment_too_long_fragment,
  &hf_pop_data_fragment_error,
  &hf_pop_data_fragment_count,
  /* Reassembled in field */
  &hf_pop_data_reassembled_in,
  /* Reassembled length field */
  &hf_pop_data_reassembled_length,
  /* Reassembled data field */
  NULL,
  /* Tag */
  "DATA fragments"
};

struct pop_proto_data {
  guint16 conversation_id;
  gboolean more_frags;
};

struct pop_data_val {
  gboolean msg_request;
  guint32 msg_read_len;  /* Length of RETR message read so far */
  guint32 msg_tot_len;   /* Total length of RETR message */
  gboolean stls_request;  /* Received STLS request */
  gchar* username;
  guint username_num;
};

typedef enum {
  pop_arg_type_unknown,
  pop_arg_type_username,
  pop_arg_type_password
} pop_arg_type_t;

static gboolean response_is_continuation(const guchar *data);

static int
dissect_pop(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void* data _U_)
{
  struct pop_proto_data  *frame_data_p;
  gboolean               is_request;
  gboolean               is_continuation;
  proto_tree             *pop_tree, *reqresp_tree;
  proto_item             *ti;
  gint                   offset = 0;
  guchar                 *line;
  gint                   next_offset;
  int                    linelen;
  int                    tokenlen;
  const guchar           *next_token;
  fragment_head          *frag_msg = NULL;
  tvbuff_t               *next_tvb = NULL;
  conversation_t         *conversation = NULL;
  struct pop_data_val    *data_val = NULL;
  gint                   length_remaining;
  pop_arg_type_t         pop_arg_type = pop_arg_type_unknown;

  col_set_str(pinfo->cinfo, COL_PROTOCOL, "POP");

  frame_data_p = (struct pop_proto_data *)p_get_proto_data(wmem_file_scope(), pinfo, proto_pop, 0);

  conversation = find_or_create_conversation(pinfo);
  data_val = (struct pop_data_val *)conversation_get_proto_data(conversation, proto_pop);
  if (!data_val) {

     /*
      * No conversation - create one and attach it.
      */
     data_val = wmem_new0(wmem_file_scope(), struct pop_data_val);

     conversation_add_proto_data(conversation, proto_pop, data_val);
  }

  /*
   * Find the end of the first line.
   */
  linelen = tvb_find_line_end(tvb, offset, -1, &next_offset, FALSE);
  line = (guchar*)wmem_alloc(wmem_packet_scope(), linelen+1);
  tvb_memcpy(tvb, line, offset, linelen);
  line[linelen] = '\0';

  if (pinfo->match_uint == pinfo->destport) {
    is_request = TRUE;
    is_continuation = FALSE;
  } else {
    is_request = FALSE;
    is_continuation = response_is_continuation(line);
    if (data_val->msg_request && tvb_reported_length_remaining(tvb, linelen) > 0) {
      // 对 RETR 或 TOP 指令响应的第一帧
      is_continuation = TRUE;
      data_val->msg_read_len = 0;
      data_val->msg_tot_len = 0;
      sscanf(line, "%*s %u %*s", &data_val->msg_tot_len);
    }
  }

  /*
   * Put the first line from the buffer into the summary
   * if it's a POP request or reply (but leave out the
   * line terminator).
   * Otherwise, just call it a continuation.
   */
  if (is_continuation) {
      if (data_val->msg_request) {
          length_remaining = tvb_reported_length_remaining(tvb, linelen);
          col_add_fstr(pinfo->cinfo, COL_INFO, "S: %s, DATA fragment, %d byte%s",
                       format_text(wmem_packet_scope(), line, linelen),
                       length_remaining, plurality (length_remaining, "", "s"));
      }
      else {
          length_remaining = tvb_reported_length_remaining(tvb, offset);
          col_add_fstr(pinfo->cinfo, COL_INFO, "S: DATA fragment, %d byte%s",
                       length_remaining, plurality (length_remaining, "", "s"));
      }
  }
  else
    col_add_fstr(pinfo->cinfo, COL_INFO, "%s: %s", is_request ? "C" : "S",
                   format_text(wmem_packet_scope(), line, linelen));

  ti = proto_tree_add_item(tree, proto_pop, tvb, offset, -1, ENC_NA);
  pop_tree = proto_item_add_subtree(ti, ett_pop);

  if (is_continuation) {

    if (pop_data_desegment) {

      if (!frame_data_p) {
          if (data_val->msg_request)
              data_val->msg_read_len += tvb_reported_length_remaining(tvb, linelen);
          else
              data_val->msg_read_len += tvb_reported_length(tvb);

        frame_data_p = wmem_new(wmem_file_scope(), struct pop_proto_data);

        frame_data_p->conversation_id = conversation->conv_index;
        frame_data_p->more_frags = data_val->msg_read_len < data_val->msg_tot_len;

        p_add_proto_data(wmem_file_scope(), pinfo, proto_pop, 0, frame_data_p);
      }

        if (data_val->msg_request) {
            frag_msg = fragment_add_seq_next(&pop_data_reassembly_table, tvb, linelen,
                                             pinfo,
                                             frame_data_p->conversation_id,
                                             NULL,
                                             tvb_reported_length_remaining(tvb, linelen),
                                             frame_data_p->more_frags);
            offset = linelen;
            next_tvb = process_reassembled_data(tvb, offset, pinfo,
                                                "Reassembled DATA",
                                                frag_msg, &pop_data_frag_items,
                                                NULL, pop_tree);
            data_val->msg_request = FALSE;
        } else {
            frag_msg = fragment_add_seq_next(&pop_data_reassembly_table, tvb, 0,
                                             pinfo,
                                             frame_data_p->conversation_id,
                                             NULL,
                                             tvb_reported_length(tvb),
                                             frame_data_p->more_frags);

            next_tvb = process_reassembled_data(tvb, offset, pinfo,
                                                "Reassembled DATA",
                                                frag_msg, &pop_data_frag_items,
                                                NULL, pop_tree);
        }

      if (next_tvb) {

        if (imf_handle)
          call_dissector(imf_handle, next_tvb, pinfo, tree);

        if (data_val) {
          /* we have read everything - reset */

          data_val->msg_read_len = 0;
          data_val->msg_tot_len = 0;
        }
        pinfo->fragmented = FALSE;
      } else {
        pinfo->fragmented = TRUE;
      }

    } else {

      /*
       * Put the whole packet into the tree as data.
       */
      call_data_dissector(tvb, pinfo, pop_tree);

    }
    return tvb_captured_length(tvb);
  }

  /*
   * Put the line into the protocol tree.
   */
  ti = proto_tree_add_string_format(pop_tree,
                                    (is_request) ?
                                        hf_pop_request :
                                        hf_pop_response,
                                    tvb, offset,
                                    next_offset - offset,
                                    "", "%s",
                                    tvb_format_text(tvb, offset, next_offset - offset));
  reqresp_tree = proto_item_add_subtree(ti, ett_pop_reqresp);

  /*
   * Extract the first token, and, if there is a first
   * token, add it as the request or reply code.
   */
  tokenlen = get_token_len(line, line + linelen, &next_token);
  if (tokenlen != 0) {
    proto_tree_add_item(reqresp_tree,
                        (is_request) ?
                            hf_pop_request_command :
                            hf_pop_response_indicator,
                        tvb, offset, tokenlen, ENC_ASCII|ENC_NA);

    if (data_val) {
      if (is_request) {
        /* see if this is RETR or TOP command */
        if (g_ascii_strncasecmp(line, "RETR", 4) == 0 ||
           g_ascii_strncasecmp(line, "TOP", 3) == 0)
          /* the next response will tell us how many bytes */
          data_val->msg_request = TRUE;

        if (g_ascii_strncasecmp(line, "STLS", 4) == 0) {
          data_val->stls_request = TRUE;
        }

        if (g_ascii_strncasecmp(line, "USER", 4) == 0) {
          pop_arg_type = pop_arg_type_username;
        }

        if (g_ascii_strncasecmp(line, "PASS", 4) == 0) {
          pop_arg_type = pop_arg_type_password;
        }
      } else {
        if (data_val->msg_request) {
          /* this is a response to a RETR or TOP command */

          if (g_ascii_strncasecmp(line, "+OK ", 4) == 0 && linelen > 4) {
            /* the message will be sent - work out how many bytes */
            data_val->msg_read_len = 0;
            data_val->msg_tot_len = 0;
            if (sscanf(line, "%*s %u %*s", &data_val->msg_tot_len) != 1)
              expert_add_info(pinfo, ti, &ei_pop_resp_tot_len_invalid);
          }
          data_val->msg_request = FALSE;
        }

        if (data_val->stls_request) {
          if (g_ascii_strncasecmp(line, "+OK ", 4) == 0) {
              /* This is the last non-TLS frame. */
              ssl_starttls_ack(tls_handle, pinfo, pop_handle);
          }
          data_val->stls_request = FALSE;
        }
      }
    }

    offset += (gint) (next_token - line);
    linelen -= (int) (next_token - line);
  }


  /*
   * Add the rest of the first line as request or
   * reply param/description.
   */
  if (linelen != 0) {
    tap_credential_t* auth;
    proto_tree_add_item(reqresp_tree,
                        (is_request) ?
                            hf_pop_request_parameter :
                            hf_pop_response_description,
                        tvb, offset, linelen, ENC_ASCII|ENC_NA);
    switch (pop_arg_type) {
      case pop_arg_type_username:
        if (!data_val->username && linelen > 0) {
          data_val->username = tvb_get_string_enc(wmem_file_scope(), tvb, offset, linelen, ENC_NA|ENC_ASCII);;
          data_val->username_num = pinfo->num;
        }
        break;
      case pop_arg_type_password:
        auth = wmem_new0(wmem_packet_scope(), tap_credential_t);
        auth->num = pinfo->num;
        auth->username_num = data_val->username_num;
        auth->password_hf_id = hf_pop_request_parameter;
        auth->username = data_val->username;
        auth->proto = "POP3";
        auth->info = wmem_strdup_printf(wmem_packet_scope(), "Username in packet %u", data_val->username_num);
        tap_queue_packet(credentials_tap, pinfo, auth);
        break;
      default:
        break;
    }
  }
  offset = next_offset;

  /*
   * Show the rest of the request or response as text,
   * a line at a time.
   */
  while (tvb_offset_exists(tvb, offset)) {
    /*
     * Find the end of the line.
     */
    tvb_find_line_end(tvb, offset, -1, &next_offset, FALSE);

    /*
     * Put this line.
     */
    proto_tree_add_string_format(pop_tree,
                                 (is_request) ?
                                     hf_pop_request_data :
                                     hf_pop_response_data,
                                 tvb, offset,
                                 next_offset - offset,
                                 "", "%s",
                                 tvb_format_text(tvb, offset, next_offset - offset));
    offset = next_offset;
  }
  return tvb_captured_length(tvb);
}

static gboolean response_is_continuation(const guchar *data)
{
  if (strncmp(data, "+OK", strlen("+OK")) == 0)
    return FALSE;

  if (strncmp(data, "-ERR", strlen("-ERR")) == 0)
    return FALSE;

  return TRUE;
}

void
proto_register_pop(void)
{
  expert_module_t* expert_pop;

  static hf_register_info hf[] = {
    { &hf_pop_response,
      { "Response",           "pop_response",
        FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL }},
    { &hf_pop_response_indicator,
      { "Response indicator",           "pop_response_indicator",
         FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL }},
    { &hf_pop_response_description,
      { "Response description",           "pop_response_description",
         FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL }},
    { &hf_pop_response_data,
      { "Data",           "pop_response_data",
        FT_STRING, BASE_NONE, NULL, 0x0, "Response Data", HFILL }},
    { &hf_pop_request,
      { "Request",           "pop_request",
         FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL }},
    { &hf_pop_request_command,
      { "Request command",            "pop_request_command",
        FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL }},
    { &hf_pop_request_parameter,
      { "Request parameter",            "pop_request_parameter",
        FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL }},
    { &hf_pop_request_data,
      { "Data",           "pop_request_data",
         FT_STRING, BASE_NONE, NULL, 0x0, "Request data", HFILL }},
    /* Fragment entries */
    { &hf_pop_data_fragments,
      { "DATA fragments", "pop_data_fragments", FT_NONE, BASE_NONE,
        NULL, 0x00, "Message fragments", HFILL } },
    { &hf_pop_data_fragment,
      { "DATA fragment", "pop_data_fragment", FT_FRAMENUM, BASE_NONE,
        NULL, 0x00, "Message fragment", HFILL } },
    { &hf_pop_data_fragment_overlap,
      { "DATA fragment overlap", "pop_data_fragment_overlap", FT_BOOLEAN,
        BASE_NONE, NULL, 0x0, "Message fragment overlap", HFILL } },
    { &hf_pop_data_fragment_overlap_conflicts,
      { "DATA fragment overlapping with conflicting data",
        "pop_data_fragment_overlap_conflicts", FT_BOOLEAN, BASE_NONE, NULL,
        0x0, "Message fragment overlapping with conflicting data", HFILL } },
    { &hf_pop_data_fragment_multiple_tails,
      { "DATA has multiple tail fragments",
        "pop_data_fragment_multiple_tails", FT_BOOLEAN, BASE_NONE,
        NULL, 0x0, "Message has multiple tail fragments", HFILL } },
    { &hf_pop_data_fragment_too_long_fragment,
      { "DATA fragment too long", "pop_data_fragment_too_long_fragment",
        FT_BOOLEAN, BASE_NONE, NULL, 0x0, "Message fragment too long",
        HFILL } },
    { &hf_pop_data_fragment_error,
      { "DATA defragmentation error", "pop_data_fragment_error", FT_FRAMENUM,
        BASE_NONE, NULL, 0x00, "Message defragmentation error", HFILL } },
    { &hf_pop_data_fragment_count,
      { "DATA fragment count", "pop_data_fragment_count", FT_UINT32, BASE_DEC,
        NULL, 0x00, NULL, HFILL } },
    { &hf_pop_data_reassembled_in,
      { "Reassembled DATA in frame", "pop_data_reassembled_in", FT_FRAMENUM, BASE_NONE,
        NULL, 0x00, "This DATA fragment is reassembled in this frame", HFILL } },
    { &hf_pop_data_reassembled_length,
      { "Reassembled DATA length", "pop_data_reassembled_length", FT_UINT32, BASE_DEC,
        NULL, 0x00, "The total length of the reassembled payload", HFILL } },
  };

  static ei_register_info ei[] = {
    { &ei_pop_resp_tot_len_invalid, { "pop.response.tot_len.invalid", PI_MALFORMED, PI_ERROR,
      "Length must be a string containing an integer", EXPFILL }}
  };

  static gint *ett[] = {
    &ett_pop,
    &ett_pop_reqresp,
    &ett_pop_data_fragment,
    &ett_pop_data_fragments
  };
  module_t *pop_module;


  proto_pop = proto_register_protocol("Post Office Protocol", "POP", "pop");
  pop_handle = register_dissector("pop", dissect_pop, proto_pop);
  proto_register_field_array(proto_pop, hf, array_length(hf));
  proto_register_subtree_array(ett, array_length(ett));

  reassembly_table_register (&pop_data_reassembly_table,
                         &addresses_ports_reassembly_table_functions);

  /* Preferences */
  pop_module = prefs_register_protocol(proto_pop, NULL);

  prefs_register_bool_preference(pop_module, "desegment_data",
    "Reassemble POP RETR and TOP responses spanning multiple TCP segments",
    "Whether the POP dissector should reassemble RETR and TOP responses and spanning multiple TCP segments."
    " To use this option, you must also enable \"Allow subdissectors to reassemble TCP streams\" in the TCP protocol settings.",
    &pop_data_desegment);

  expert_pop = expert_register_protocol(proto_pop);
  expert_register_field_array(expert_pop, ei, array_length(ei));

  credentials_tap = register_tap("credentials");
}

void
proto_reg_handoff_pop(void)
{
  dissector_add_uint_with_preference("tcp.port", TCP_PORT_POP, pop_handle);
  ssl_dissector_add(TCP_PORT_SSL_POP, pop_handle);

  /* find the IMF dissector */
  imf_handle = find_dissector_add_dependency("imf", proto_pop);

  /* find the TLS dissector */
  tls_handle = find_dissector_add_dependency("tls", proto_pop);
}

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local Variables:
 * c-basic-offset: 2
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * ex: set shiftwidth=2 tabstop=8 expandtab:
 * :indentSize=2:tabSize=8:noTabs=true:
 */
