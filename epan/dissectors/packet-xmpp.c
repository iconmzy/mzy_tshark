/* packet-xmpp.c
 * Wireshark's XMPP dissector.
 *
 * Copyright 2011, Mariusz Okroj <okrojmariusz[]gmail.com>
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "config.h"


#include <epan/packet.h>
#include <epan/conversation.h>
#include <epan/prefs.h>
#include <epan/proto_data.h>

#include "packet-xmpp.h"
#include "packet-xmpp-core.h"

#define XMPP_PORT 5222

void proto_register_xmpp(void);
void proto_reg_handoff_xmpp(void);

int proto_xmpp = -1;

static gboolean xmpp_desegment = TRUE;

gint hf_xmpp_xmlns = -1;
gint hf_xmpp_id = -1;
gint hf_xmpp_from = -1;
gint hf_xmpp_to = -1;
gint hf_xmpp_type = -1;
gint hf_xmpp_cdata = -1;
gint hf_xmpp_attribute = -1;

gint hf_xmpp_iq = -1;

gint hf_xmpp_query = -1;
gint hf_xmpp_query_node = -1;

gint hf_xmpp_query_item = -1;
gint hf_xmpp_query_item_jid = -1;
gint hf_xmpp_query_item_name = -1;
gint hf_xmpp_query_item_subscription = -1;
gint hf_xmpp_query_item_ask = -1;
gint hf_xmpp_query_item_group = -1;
gint hf_xmpp_query_item_node = -1;
gint hf_xmpp_query_item_approved = -1;

gint hf_xmpp_query_identity = -1;
gint hf_xmpp_query_identity_category = -1;
gint hf_xmpp_query_identity_type = -1;
gint hf_xmpp_query_identity_name = -1;
gint hf_xmpp_query_identity_lang = -1;

gint hf_xmpp_query_feature = -1;

gint hf_xmpp_query_streamhost = -1;
gint hf_xmpp_query_streamhost_used = -1;
gint hf_xmpp_query_activate = -1;
gint hf_xmpp_query_udpsuccess = -1;

gint hf_xmpp_error = -1;
gint hf_xmpp_error_type = -1;
gint hf_xmpp_error_code = -1;
gint hf_xmpp_error_condition = -1;
gint hf_xmpp_error_text = -1;

gint hf_xmpp_iq_bind = -1;
gint hf_xmpp_iq_bind_jid = -1;
gint hf_xmpp_iq_bind_resource = -1;

gint hf_xmpp_services = -1;
gint hf_xmpp_channel = -1;

gint hf_xmpp_iq_session = -1;
gint hf_xmpp_stream = -1;
gint hf_xmpp_features = -1;

gint hf_xmpp_vcard  = -1;
gint hf_xmpp_vcard_x_update = -1;

gint hf_xmpp_jingle = -1;
gint hf_xmpp_jingle_sid = -1;
gint hf_xmpp_jingle_initiator = -1;
gint hf_xmpp_jingle_responder = -1;
gint hf_xmpp_jingle_action = -1;

gint hf_xmpp_jingle_content = -1;
gint hf_xmpp_jingle_content_creator = -1;
gint hf_xmpp_jingle_content_name = -1;
gint hf_xmpp_jingle_content_disposition = -1;
gint hf_xmpp_jingle_content_senders = -1;

gint hf_xmpp_jingle_content_description = -1;
gint hf_xmpp_jingle_content_description_media = -1;
gint hf_xmpp_jingle_content_description_ssrc = -1;

gint hf_xmpp_jingle_cont_desc_payload = -1;
gint hf_xmpp_jingle_cont_desc_payload_id = -1;
gint hf_xmpp_jingle_cont_desc_payload_channels = -1;
gint hf_xmpp_jingle_cont_desc_payload_clockrate = -1;
gint hf_xmpp_jingle_cont_desc_payload_maxptime = -1;
gint hf_xmpp_jingle_cont_desc_payload_name = -1;
gint hf_xmpp_jingle_cont_desc_payload_ptime = -1;

gint hf_xmpp_jingle_cont_desc_payload_param = -1;
gint hf_xmpp_jingle_cont_desc_payload_param_value = -1;
gint hf_xmpp_jingle_cont_desc_payload_param_name = -1;

gint hf_xmpp_jingle_cont_desc_enc = -1;
gint hf_xmpp_jingle_cont_desc_enc_zrtp_hash = -1;
gint hf_xmpp_jingle_cont_desc_enc_crypto = -1;

gint hf_xmpp_jingle_cont_desc_rtp_hdr = -1;
gint hf_xmpp_jingle_cont_desc_bandwidth = -1;

gint hf_xmpp_jingle_cont_trans = -1;
gint hf_xmpp_jingle_cont_trans_pwd = -1;
gint hf_xmpp_jingle_cont_trans_ufrag = -1;

gint hf_xmpp_jingle_cont_trans_cand = -1;
gint hf_xmpp_jingle_cont_trans_rem_cand = -1;
gint hf_xmpp_jingle_cont_trans_activated = -1;
gint hf_xmpp_jingle_cont_trans_candidate_error = -1;
gint hf_xmpp_jingle_cont_trans_candidate_used = -1;
gint hf_xmpp_jingle_cont_trans_proxy_error = -1;


gint hf_xmpp_jingle_reason = -1;
gint hf_xmpp_jingle_reason_condition = -1;
gint hf_xmpp_jingle_reason_text = -1;

gint hf_xmpp_jingle_rtp_info = -1;

gint hf_xmpp_jingle_file_transfer_offer = -1;
gint hf_xmpp_jingle_file_transfer_request = -1;
gint hf_xmpp_jingle_file_transfer_received = -1;
gint hf_xmpp_jingle_file_transfer_abort = -1;
gint hf_xmpp_jingle_file_transfer_checksum = -1;

gint hf_xmpp_si = -1;
gint hf_xmpp_si_file = -1;

gint hf_xmpp_iq_feature_neg = -1;
gint hf_xmpp_x_data = -1;
gint hf_xmpp_x_data_field = -1;
gint hf_xmpp_x_data_field_value = -1;
gint hf_xmpp_x_data_instructions = -1;
gint hf_xmpp_muc_user_status = -1;

gint hf_xmpp_message = -1;
gint hf_xmpp_message_chatstate = -1;

gint hf_xmpp_message_thread = -1;
gint hf_xmpp_message_thread_parent = -1;

gint hf_xmpp_message_body = -1;
gint hf_xmpp_message_subject = -1;

gint hf_xmpp_ibb_open = -1;
gint hf_xmpp_ibb_close = -1;
gint hf_xmpp_ibb_data = -1;

gint hf_xmpp_delay = -1;

gint hf_xmpp_x_event = -1;
gint hf_xmpp_x_event_condition = -1;

gint hf_xmpp_presence = -1;
gint hf_xmpp_presence_show = -1;
gint hf_xmpp_presence_status = -1;
gint hf_xmpp_presence_caps = -1;

gint hf_xmpp_auth = -1;
gint hf_xmpp_failure = -1;
gint hf_xmpp_failure_text = -1;
gint hf_xmpp_starttls = -1;
gint hf_xmpp_proceed = -1;
gint hf_xmpp_xml_header_version = -1;
gint hf_xmpp_stream_end = -1;

gint hf_xmpp_muc_x = -1;
gint hf_xmpp_muc_user_x  = -1;
gint hf_xmpp_muc_user_item  = -1;
gint hf_xmpp_muc_user_invite  = -1;

gint hf_xmpp_gtalk_session = -1;
gint hf_xmpp_gtalk_session_type = -1;
gint hf_xmpp_gtalk = -1;
gint hf_xmpp_gtalk_setting = -1;
gint hf_xmpp_gtalk_setting_element = -1;
gint hf_xmpp_gtalk_nosave_x = -1;
gint hf_xmpp_gtalk_mail_mailbox = -1;
gint hf_xmpp_gtalk_mail_new_mail = -1;
gint hf_xmpp_gtalk_transport_p2p = -1;
gint hf_xmpp_gtalk_mail_snippet = -1;
gint hf_xmpp_gtalk_status_status_list = -1;

gint hf_xmpp_conf_info = -1;
gint hf_xmpp_conf_info_sid = -1;

gint hf_xmpp_unknown = -1;
gint hf_xmpp_unknown_attr = -1;

gint hf_xmpp_out = -1;
gint hf_xmpp_in = -1;
gint hf_xmpp_response_in = -1;
gint hf_xmpp_response_to = -1;
gint hf_xmpp_jingle_session = -1;
gint hf_xmpp_ibb = -1;

gint hf_xmpp_ping = -1;
gint hf_xmpp_hashes = -1;

gint hf_xmpp_jitsi_inputevt = -1;
gint hf_xmpp_jitsi_inputevt_rmt_ctrl = -1;

gint ett_xmpp = -1;
gint ett_xmpp_iq = -1;
gint ett_xmpp_query = -1;
gint ett_xmpp_query_item = -1;
gint ett_xmpp_query_identity = -1;
gint ett_xmpp_query_feature = -1;

gint ett_xmpp_query_streamhost = -1;
gint ett_xmpp_query_streamhost_used = -1;
gint ett_xmpp_query_udpsuccess = -1;

gint ett_xmpp_iq_error = -1;
gint ett_xmpp_iq_bind = -1;
gint ett_xmpp_iq_session = -1;
gint ett_xmpp_vcard = -1;
gint ett_xmpp_vcard_x_update = -1;

gint ett_xmpp_jingle = -1;
gint ett_xmpp_jingle_content = -1;
gint ett_xmpp_jingle_content_description = -1;
gint ett_xmpp_jingle_cont_desc_enc = -1;
gint ett_xmpp_jingle_cont_desc_enc_zrtp_hash = -1;
gint ett_xmpp_jingle_cont_desc_enc_crypto = -1;
gint ett_xmpp_jingle_cont_desc_rtp_hdr = -1;
gint ett_xmpp_jingle_cont_desc_bandwidth = -1;
gint ett_xmpp_jingle_cont_desc_payload = -1;
gint ett_xmpp_jingle_cont_desc_payload_param = -1;
gint ett_xmpp_jingle_cont_trans = -1;
gint ett_xmpp_jingle_cont_trans_cand = -1;
gint ett_xmpp_jingle_cont_trans_rem_cand = -1;
gint ett_xmpp_jingle_reason = -1;
gint ett_xmpp_jingle_rtp_info = -1;

gint ett_xmpp_jingle_file_transfer_offer = -1;
gint ett_xmpp_jingle_file_transfer_request = -1;
gint ett_xmpp_jingle_file_transfer_abort = -1;
gint ett_xmpp_jingle_file_transfer_received = -1;
gint ett_xmpp_jingle_file_transfer_checksum = -1;
gint ett_xmpp_jingle_file_transfer_file = -1;

gint ett_xmpp_services = -1;
gint ett_xmpp_services_relay = -1;
gint ett_xmpp_channel = -1;

gint ett_xmpp_si = -1;
gint ett_xmpp_si_file = -1;
gint ett_xmpp_si_file_range = -1;

gint ett_xmpp_iq_feature_neg = -1;
gint ett_xmpp_x_data = -1;
gint ett_xmpp_x_data_field = -1;
gint ett_xmpp_x_data_field_value = -1;

gint ett_xmpp_ibb_open = -1;
gint ett_xmpp_ibb_close = -1;
gint ett_xmpp_ibb_data = -1;

gint ett_xmpp_delay = -1;

gint ett_xmpp_x_event = -1;

gint ett_xmpp_message = -1;
gint ett_xmpp_message_thread = -1;
gint ett_xmpp_message_body = -1;
gint ett_xmpp_message_subject = -1;

gint ett_xmpp_presence = -1;
gint ett_xmpp_presence_status = -1;
gint ett_xmpp_presence_caps = -1;

gint ett_xmpp_auth = -1;
gint ett_xmpp_challenge = -1;
gint ett_xmpp_response = -1;
gint ett_xmpp_success = -1;
gint ett_xmpp_failure = -1;
gint ett_xmpp_stream = -1;
gint ett_xmpp_features = -1;
gint ett_xmpp_features_mechanisms = -1;
gint ett_xmpp_starttls = -1;
gint ett_xmpp_proceed = -1;

gint ett_xmpp_muc_x = -1;
gint ett_xmpp_muc_hist = -1;
gint ett_xmpp_muc_user_x = -1;
gint ett_xmpp_muc_user_item = -1;
gint ett_xmpp_muc_user_invite = -1;

gint ett_xmpp_gtalk_session = -1;
gint ett_xmpp_gtalk_session_desc = -1;
gint ett_xmpp_gtalk_session_cand = -1;
gint ett_xmpp_gtalk_session_desc_payload = -1;
gint ett_xmpp_gtalk_session_reason = -1;
gint ett_xmpp_gtalk_jingleinfo_stun = -1;
gint ett_xmpp_gtalk_jingleinfo_server = -1;
gint ett_xmpp_gtalk_jingleinfo_relay = -1;
gint ett_xmpp_gtalk_jingleinfo_relay_serv = -1;
gint ett_xmpp_gtalk_setting = -1;
gint ett_xmpp_gtalk_nosave_x = -1;
gint ett_xmpp_gtalk_mail_mailbox = -1;
gint ett_xmpp_gtalk_mail_mail_info = -1;
gint ett_xmpp_gtalk_mail_senders = -1;
gint ett_xmpp_gtalk_mail_sender = -1;
gint ett_xmpp_gtalk_status_status_list = -1;
gint ett_xmpp_gtalk_transport_p2p = -1;
gint ett_xmpp_gtalk_transport_p2p_cand = -1;

gint ett_xmpp_conf_info = -1;
gint ett_xmpp_conf_desc = -1;
gint ett_xmpp_conf_state = -1;
gint ett_xmpp_conf_users = -1;
gint ett_xmpp_conf_user = -1;
gint ett_xmpp_conf_endpoint = -1;
gint ett_xmpp_conf_media = -1;

gint ett_xmpp_ping = -1;
gint ett_xmpp_hashes = -1;
gint ett_xmpp_hashes_hash = -1;

gint ett_xmpp_jitsi_inputevt = -1;
gint ett_xmpp_jitsi_inputevt_rmt_ctrl = -1;

gint ett_unknown[ETT_UNKNOWN_LEN];

static expert_field ei_xmpp_xml_disabled = EI_INIT;
static expert_field ei_xmpp_packet_unknown = EI_INIT;
expert_field ei_xmpp_starttls_missing = EI_INIT;
expert_field ei_xmpp_response = EI_INIT;
expert_field ei_xmpp_challenge = EI_INIT;
expert_field ei_xmpp_success = EI_INIT;
expert_field ei_xmpp_proceed_already_in_frame = EI_INIT;
expert_field ei_xmpp_starttls_already_in_frame = EI_INIT;
expert_field ei_xmpp_packet_without_response = EI_INIT;
expert_field ei_xmpp_unknown_element = EI_INIT;
expert_field ei_xmpp_field_unexpected_value = EI_INIT;
expert_field ei_xmpp_unknown_attribute = EI_INIT;
expert_field ei_xmpp_required_attribute = EI_INIT;

static dissector_handle_t xmpp_handle;

static dissector_handle_t xml_handle;

static int
dissect_xmpp(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void* data _U_) {

    xml_frame_t *xml_frame;
    xml_frame_t *xml_dissector_frame;
    gboolean     out_packet;

    conversation_t   *conversation;
    xmpp_conv_info_t *xmpp_info;

    proto_tree *xmpp_tree  = NULL;
    proto_item *xmpp_item  = NULL;
    proto_item *outin_item;

    xmpp_element_t *packet = NULL;

    int proto_xml = dissector_handle_get_protocol_index(xml_handle);

    gboolean whitespace_keepalive = ((tvb_reported_length(tvb) == 1) && tvb_get_guint8(tvb, 0) == ' ');

    /*check if desegment
     * now it checks that last char is '>',
     * TODO checks that first element in packet is closed*/
    int   indx;
    gchar last_char;

    if (xmpp_desegment && !whitespace_keepalive)
    {
        indx = tvb_reported_length(tvb) - 1;
        if (indx >= 0)
        {
            last_char = tvb_get_guint8(tvb, indx);

            while ((last_char <= ' ') && (indx - 1 >= 0))
            {
                indx--;
                last_char = tvb_get_guint8(tvb, indx);
            }

            if ((indx >= 0) && (last_char != '>'))
            {
                pinfo->desegment_len = DESEGMENT_ONE_MORE_SEGMENT;
                return tvb_captured_length(tvb);
            }
        }
    }

    col_set_str(pinfo->cinfo, COL_PROTOCOL, "XMPP");
    col_clear(pinfo->cinfo, COL_INFO);

    /*if tree == NULL then xmpp_item and xmpp_tree will also NULL*/
    xmpp_item = proto_tree_add_item(tree, proto_xmpp, tvb, 0, -1, ENC_NA);
    xmpp_tree = proto_item_add_subtree(xmpp_item, ett_xmpp);

    if (whitespace_keepalive) {
        /* RFC 6120 section 4.6.1 */
        col_set_str(pinfo->cinfo, COL_INFO, "Whitespace Keepalive");
        return tvb_captured_length(tvb);
    }

    call_dissector_with_data(xml_handle, tvb, pinfo, xmpp_tree, NULL);

    /* If XML dissector is disabled, we can't do much */
    if (!proto_is_protocol_enabled(find_protocol_by_id(proto_xml)))
    {
        col_append_str(pinfo->cinfo, COL_INFO, "(XML dissector disabled, can't dissect XMPP)");
        expert_add_info(pinfo, xmpp_item, &ei_xmpp_xml_disabled);
        return tvb_captured_length(tvb);
    }

    /*if stream end occurs then return*/
    if(xmpp_stream_close(xmpp_tree,tvb, pinfo))
    {
        if(xmpp_tree)
            xmpp_proto_tree_hide_first_child(xmpp_tree);
        return tvb_captured_length(tvb);
    }

    xml_dissector_frame = (xml_frame_t *)p_get_proto_data(pinfo->pool, pinfo, proto_xml, 0);
    if(xml_dissector_frame == NULL)
        return tvb_captured_length(tvb);

    /*data from XML dissector*/
    xml_frame = xml_dissector_frame->first_child;

    if(!xml_frame)
        return tvb_captured_length(tvb);

    conversation = find_or_create_conversation(pinfo);
    xmpp_info = (xmpp_conv_info_t *)conversation_get_proto_data(conversation, proto_xmpp);

    if (!xmpp_info) {
        xmpp_info = wmem_new(wmem_file_scope(), xmpp_conv_info_t);
        xmpp_info->req_resp        = wmem_tree_new(wmem_file_scope());
        xmpp_info->jingle_sessions = wmem_tree_new(wmem_file_scope());
        xmpp_info->ibb_sessions    = wmem_tree_new(wmem_file_scope());
        xmpp_info->gtalk_sessions  = wmem_tree_new(wmem_file_scope());
        xmpp_info->ssl_start   = 0;
        conversation_add_proto_data(conversation, proto_xmpp, (void *) xmpp_info);
    }

    if (pinfo->match_uint == pinfo->destport)
        out_packet = TRUE;
    else
        out_packet = FALSE;

    while(xml_frame)
    {
        packet = xmpp_xml_frame_to_element_t(xml_frame, NULL, tvb);
        DISSECTOR_ASSERT(packet);

        if (strcmp(packet->name, "iq") == 0) {
            xmpp_iq_reqresp_track(pinfo, packet, xmpp_info);
            xmpp_jingle_session_track(pinfo, packet, xmpp_info);
            xmpp_gtalk_session_track(pinfo, packet, xmpp_info);
        }

        if (strcmp(packet->name, "iq") == 0 || strcmp(packet->name, "message") == 0) {
            xmpp_ibb_session_track(pinfo, packet, xmpp_info);
        }

        if (out_packet)
            outin_item = proto_tree_add_boolean(xmpp_tree, hf_xmpp_out, tvb, 0, 0, TRUE);
        else
            outin_item = proto_tree_add_boolean(xmpp_tree, hf_xmpp_in, tvb, 0, 0, TRUE);

        proto_item_set_hidden(outin_item);


        /*it hides tree generated by XML dissector*/
        xmpp_proto_tree_hide_first_child(xmpp_tree);

        if (strcmp(packet->name, "iq") == 0) {
            xmpp_iq(xmpp_tree, tvb, pinfo, packet);
        } else if (strcmp(packet->name, "presence") == 0) {
            xmpp_presence(xmpp_tree, tvb, pinfo, packet);
        } else if (strcmp(packet->name, "message") == 0) {
            xmpp_message(xmpp_tree, tvb, pinfo, packet);
        } else if (strcmp(packet->name, "auth") == 0) {
            xmpp_auth(xmpp_tree, tvb, pinfo, packet);
        } else if (strcmp(packet->name, "challenge") == 0) {
            xmpp_challenge_response_success(xmpp_tree, tvb, pinfo, packet, &ei_xmpp_challenge, ett_xmpp_challenge, "CHALLENGE");
        } else if (strcmp(packet->name, "response") == 0) {
            xmpp_challenge_response_success(xmpp_tree, tvb, pinfo, packet, &ei_xmpp_response, ett_xmpp_response, "RESPONSE");
        } else if (strcmp(packet->name, "success") == 0) {
            xmpp_challenge_response_success(xmpp_tree, tvb, pinfo, packet, &ei_xmpp_success, ett_xmpp_success, "SUCCESS");
        } else if (strcmp(packet->name, "failure") == 0) {
            xmpp_failure(xmpp_tree, tvb, pinfo, packet);
        } else if (strcmp(packet->name, "xml") == 0) {
            xmpp_xml_header(xmpp_tree, tvb, pinfo, packet);
        } else if (strcmp(packet->name, "stream") == 0) {
            xmpp_stream(xmpp_tree, tvb, pinfo, packet);
        } else if (strcmp(packet->name, "features") == 0) {
            xmpp_features(xmpp_tree, tvb, pinfo, packet);
        } else if (strcmp(packet->name, "starttls") == 0) {
            xmpp_starttls(xmpp_tree, tvb, pinfo, packet, xmpp_info);
        } else if (strcmp(packet->name, "proceed") == 0) {
            xmpp_proceed(xmpp_tree, tvb, pinfo, packet, xmpp_info);
        } else {
            xmpp_proto_tree_show_first_child(xmpp_tree);
            expert_add_info_format(pinfo, xmpp_tree, &ei_xmpp_packet_unknown, "Unknown packet: %s", packet->name);
            col_set_str(pinfo->cinfo, COL_INFO, "UNKNOWN PACKET ");
        }

        /*appends to COL_INFO information about src or dst*/
        if (pinfo->match_uint == pinfo->destport) {
            xmpp_attr_t *to = xmpp_get_attr(packet, "to");
            if (to)
                col_append_fstr(pinfo->cinfo, COL_INFO, "> %s ", to->value);
        } else {
            xmpp_attr_t *from = xmpp_get_attr(packet, "from");
            if (from)
                col_append_fstr(pinfo->cinfo, COL_INFO, "< %s ", from->value);
        }

        xmpp_element_t_tree_free(packet);
        xml_frame = xml_frame->next_sibling;
    }
    return tvb_captured_length(tvb);
}


void
proto_register_xmpp(void) {
    static hf_register_info hf[] = {
        { &hf_xmpp_iq,
          {
              "IQ", "xmpp_iq", FT_NONE, BASE_NONE, NULL, 0x0,
              "iq packet", HFILL
          }},
        {&hf_xmpp_xmlns,
         {
             "xmlns", "xmpp_xmlns", FT_STRING, BASE_NONE, NULL, 0x0,
             "element namespace", HFILL
         }},
        {&hf_xmpp_cdata,
         {
             "CDATA", "xmpp_cdata", FT_STRING, BASE_NONE, NULL, 0x0,
             NULL, HFILL
         }},
        {&hf_xmpp_attribute,
         {
             "Attribute", "xmpp_attribute", FT_STRING, BASE_NONE, NULL, 0x0,
             NULL, HFILL
         }},
        { &hf_xmpp_id,
          {
              "id", "xmpp_id", FT_STRING, BASE_NONE, NULL, 0x0,
              "packet id", HFILL
          }},
        { &hf_xmpp_type,
          {
              "type", "xmpp_type", FT_STRING, BASE_NONE, NULL, 0x0,
              "packet type", HFILL
          }},
        { &hf_xmpp_from,
          {
              "from", "xmpp_from", FT_STRING, BASE_NONE, NULL, 0x0,
              "packet from", HFILL
          }},
        { &hf_xmpp_to,
          {
              "to", "xmpp_to", FT_STRING, BASE_NONE, NULL, 0x0,
              "packet to", HFILL
          }},
        { &hf_xmpp_query,
          {
              "QUERY", "xmpp_query", FT_NONE, BASE_NONE, NULL, 0x0,
              "iq query", HFILL
          }},
        { &hf_xmpp_query_node,
          {
              "node", "xmpp_query_node", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq query node", HFILL
          }},
        { &hf_xmpp_query_item,
          {
              "ITEM", "xmpp_query_item", FT_NONE, BASE_NONE, NULL, 0x0,
              "iq query item", HFILL

          }},
        { &hf_xmpp_query_item_jid,
          {
              "jid", "xmpp_query_item_jid", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq query item jid", HFILL

          }},
        { &hf_xmpp_query_item_name,
          {
              "name", "xmpp_query_item_name", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq query item name", HFILL
          }},
        { &hf_xmpp_query_item_subscription,
          {
              "subscription", "xmpp_query_item_subscription", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq query item subscription", HFILL
          }},
        { &hf_xmpp_query_item_ask,
          {
              "ask", "xmpp_query_item_ask", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq query item ask", HFILL
          }},
        { &hf_xmpp_query_item_group,
          {
              "GROUP", "xmpp_query_item_group", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq query item group", HFILL

          }},
        { &hf_xmpp_query_item_approved,
          {
              "approved", "xmpp_query_item_approved", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq query item approved", HFILL

          }},
        { &hf_xmpp_query_item_node,
          {
              "node", "xmpp_query_item_node", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq query item node", HFILL

          }},
        { &hf_xmpp_query_identity,
          {
              "IDENTITY", "xmpp_query_identity", FT_NONE, BASE_NONE, NULL, 0x0,
              "iq query identity", HFILL

          }},
        { &hf_xmpp_query_identity_category,
          {
              "category", "xmpp_query_identity_category", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq query identity category", HFILL

          }},
        { &hf_xmpp_query_identity_type,
          {
              "type", "xmpp_query_identity_type", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq query identity type", HFILL

          }},
        { &hf_xmpp_query_identity_name,
          {
              "name", "xmpp_query_identity_name", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq query identity name", HFILL

          }},
        { &hf_xmpp_query_identity_lang,
          {
              "lang", "xmpp_query_identity_lang", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq query identity lang", HFILL

          }},
        { &hf_xmpp_query_feature,
          {
              "FEATURE", "xmpp_query_feature", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq query feature", HFILL

          }},
        { &hf_xmpp_query_streamhost,
          {
              "STREAMHOST", "xmpp_query_streamhost", FT_NONE, BASE_NONE, NULL, 0x0,
              "iq query streamhost", HFILL

          }},
        { &hf_xmpp_query_streamhost_used,
          {
              "STREAMHOST-USED", "xmpp_query_streamhost-used", FT_NONE, BASE_NONE, NULL, 0x0,
              "iq query streamhost-used", HFILL

          }},
        { &hf_xmpp_query_activate,
          {
              "ACTIVATE", "xmpp_query_activate", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq query activate", HFILL

          }},
        { &hf_xmpp_query_udpsuccess,
          {
              "UDPSUCCESS", "xmpp_query_udpsuccess", FT_NONE, BASE_NONE, NULL, 0x0,
              "iq query streamhost-used", HFILL

          }},
        { &hf_xmpp_error,
          {
              "ERROR", "xmpp_error", FT_NONE, BASE_NONE, NULL, 0x0,
              "iq error", HFILL
          }},
        { &hf_xmpp_error_code,
          {
              "code", "xmpp_error_code", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq stanza error code", HFILL

          }},
        { &hf_xmpp_error_type,
          {
              "type", "xmpp_error_type", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq error type", HFILL

          }},
        { &hf_xmpp_error_condition,
          {
              "CONDITION", "xmpp_error_condition", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq error condition", HFILL

          }},
        { &hf_xmpp_error_text,
          {
              "TEXT", "xmpp_error_text", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq error text", HFILL

          }},
        { &hf_xmpp_iq_bind,
          {
              "BIND", "xmpp_iq_bind", FT_NONE, BASE_NONE, NULL, 0x0,
              "iq bind", HFILL

          }},
        { &hf_xmpp_iq_bind_jid,
          {
              "jid", "xmpp_iq_bind_jid", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq bind jid", HFILL

          }},
        { &hf_xmpp_iq_bind_resource,
          {
              "resource", "xmpp_iq_bind_resource", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq bind resource", HFILL

          }},
        { &hf_xmpp_services,
          {
              "SERVICES", "xmpp_services", FT_NONE, BASE_NONE, NULL, 0x0,
              "http://jabber.org/protocol/jinglenodes services", HFILL
          }},
        { &hf_xmpp_channel,
          {
              "CHANNEL", "xmpp_channel", FT_NONE, BASE_NONE, NULL, 0x0,
              "http://jabber.org/protocol/jinglenodes#channel", HFILL
          }},
        { &hf_xmpp_iq_session,
          {
              "SESSION", "xmpp_iq_session", FT_NONE, BASE_NONE, NULL, 0x0,
              "iq session", HFILL
          }},
        { &hf_xmpp_vcard,
          {
              "VCARD", "xmpp_vcard", FT_NONE, BASE_NONE, NULL, 0x0,
              "vcard-temp", HFILL
          }},
        { &hf_xmpp_vcard_x_update,
          {
              "X VCARD-UPDATE", "xmpp_vcard-update", FT_NONE, BASE_NONE, NULL, 0x0,
              "vcard-temp:x:update", HFILL
          }},
        { &hf_xmpp_jingle,
          {
              "JINGLE", "xmpp_jingle", FT_NONE, BASE_NONE, NULL, 0x0,
              "iq jingle", HFILL
          }},
        { &hf_xmpp_jingle_action,
          {
              "action", "xmpp_jingle_action", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq jingle action", HFILL
          }},
        { &hf_xmpp_jingle_sid,
          {
              "sid", "xmpp_jingle_sid", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq jingle sid", HFILL
          }},
        { &hf_xmpp_jingle_initiator,
          {
              "initiator", "xmpp_jingle_initiator", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq jingle initiator", HFILL
          }},
        { &hf_xmpp_jingle_responder,
          {
              "responder", "xmpp_jingle_responder", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq jingle responder", HFILL
          }},
        { &hf_xmpp_jingle_content,
          {
              "CONTENT", "xmpp_jingle_content", FT_NONE, BASE_NONE, NULL, 0x0,
              "iq jingle content", HFILL
          }},
        { &hf_xmpp_jingle_content_creator,
          {
              "creator", "xmpp_jingle_content_creator", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq jingle content creator", HFILL
          }},
        { &hf_xmpp_jingle_content_name,
          {
              "name", "xmpp_jingle_content_name", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq jingle content name", HFILL
          }},
        { &hf_xmpp_jingle_content_disposition,
          {
              "disposition", "xmpp_jingle_content_disposition", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq jingle content disposition", HFILL
          }},
        { &hf_xmpp_jingle_content_senders,
          {
              "senders", "xmpp_jingle_content_senders", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq jingle content senders", HFILL
          }},
        { &hf_xmpp_jingle_content_description,
          {
              "DESCRIPTION", "xmpp_jingle_content_description", FT_NONE, BASE_NONE, NULL, 0x0,
              "iq jingle content description", HFILL
          }},
        { &hf_xmpp_jingle_content_description_media,
          {
              "media", "xmpp_jingle_content_description_media", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq jingle content description", HFILL
          }},
        { &hf_xmpp_jingle_content_description_ssrc,
          {
              "ssrc", "xmpp_jingle_content_description_ssrc", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq jingle content description ssrc", HFILL
          }},
        { &hf_xmpp_jingle_cont_desc_payload,
          {
              "PAYLOAD-TYPE", "xmpp_jingle_content_description_payload-type", FT_NONE, BASE_NONE, NULL, 0x0,
              "iq jingle content description payload-type", HFILL
          }},
        { &hf_xmpp_jingle_cont_desc_payload_id,
          {
              "id", "xmpp_jingle_content_description_payload-type_id", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq jingle content description payload-type id", HFILL
          }},
        { &hf_xmpp_jingle_cont_desc_payload_channels,
          {
              "channels", "xmpp_jingle_content_description_payload-type_channels", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq jingle content description payload-type channels", HFILL
          }},
        { &hf_xmpp_jingle_cont_desc_payload_clockrate,
          {
              "clockrate", "xmpp_jingle_content_description_payload-type_clockrate", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq jingle content description payload-type clockrate", HFILL
          }},
        { &hf_xmpp_jingle_cont_desc_payload_maxptime,
          {
              "maxptime", "xmpp_jingle_content_description_payload-type_maxptime", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq jingle content description payload-type maxptime", HFILL
          }},
        { &hf_xmpp_jingle_cont_desc_payload_name,
          {
              "name", "xmpp_jingle_content_description_payload-type_name", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq jingle content description payload-type name", HFILL
          }},
        { &hf_xmpp_jingle_cont_desc_payload_ptime,
          {
              "ptime", "xmpp_jingle_content_description_payload-type_ptime", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq jingle content description payload-type ptime", HFILL
          }},
        { &hf_xmpp_jingle_cont_desc_payload_param,
          {
              "PARAMETER", "xmpp_jingle_content_description_payload-type_parameter", FT_NONE, BASE_NONE, NULL, 0x0,
              "iq jingle content description payload-type parameter", HFILL
          }},
        { &hf_xmpp_jingle_cont_desc_payload_param_name,
          {
              "name", "xmpp_jingle_content_description_payload-type_parameter_name", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq jingle content description payload-type parameter name", HFILL
          }},
        { &hf_xmpp_jingle_cont_desc_payload_param_value,
          {
              "value", "xmpp_jingle_content_description_payload-type_parameter_value", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq jingle content description payload-type parameter value", HFILL
          }},
        { &hf_xmpp_jingle_cont_trans,
          {
              "TRANSPORT", "xmpp_jingle_content_transport", FT_NONE, BASE_NONE, NULL, 0x0,
              "iq jingle content transport", HFILL
          }},
        { &hf_xmpp_jingle_cont_trans_ufrag,
          {
              "ufrag", "xmpp_jingle_content_transport_ufrag", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq jingle content transport ufrag", HFILL
          }},
        { &hf_xmpp_jingle_cont_trans_pwd,
          {
              "pwd", "xmpp_jingle_content_transport_pwd", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq jingle content transport pwd", HFILL
          }},
        { &hf_xmpp_jingle_cont_trans_cand,
          {
              "CANDIDATE", "xmpp_jingle_content_transport_candidate", FT_NONE, BASE_NONE, NULL, 0x0,
              "iq jingle content transport candidate", HFILL
          }},
        { &hf_xmpp_jingle_cont_trans_rem_cand,
          {
              "REMOTE-CANDIDATE", "xmpp_jingle_content_transport_remote-candidate", FT_NONE, BASE_NONE, NULL, 0x0,
              "iq jingle content transport remote-candidate", HFILL
          }},
        { &hf_xmpp_jingle_cont_trans_activated,
          {
              "ACTIVATED", "xmpp_jingle_content_transport_activated", FT_NONE, BASE_NONE, NULL, 0x0,
              "urn:xmpp:jingle:transports:s5b:1 activated", HFILL
          }},
        { &hf_xmpp_jingle_cont_trans_candidate_used,
          {
              "CANDIDATE-USED", "xmpp_jingle_content_transport_candidate-used", FT_NONE, BASE_NONE, NULL, 0x0,
              "urn:xmpp:jingle:transports:s5b:1 candidate-used", HFILL
          }},
        { &hf_xmpp_jingle_cont_trans_candidate_error,
          {
              "CANDIDATE-ERROR", "xmpp_jingle_content_transport_candidate-error", FT_NONE, BASE_NONE, NULL, 0x0,
              "urn:xmpp:jingle:transports:s5b:1 candidate-error", HFILL
          }},
        { &hf_xmpp_jingle_cont_trans_proxy_error,
          {
              "PROXY-ERROR", "xmpp_jingle_content_transport_proxy-error", FT_NONE, BASE_NONE, NULL, 0x0,
              "urn:xmpp:jingle:transports:s5b:1 proxy-error", HFILL
          }},
        { &hf_xmpp_jingle_cont_desc_enc,
          {
              "ENCRYPTION", "xmpp_jingle_content_description_encryption", FT_NONE, BASE_NONE, NULL, 0x0,
              "iq jingle content description encryption", HFILL
          }},
        { &hf_xmpp_jingle_cont_desc_enc_zrtp_hash,
          {
              "ZRTP-HASH", "xmpp_jingle_content_description_encryption_zrtp-hash", FT_NONE, BASE_NONE, NULL, 0x0,
              "iq jingle content description encryption zrtp-hash", HFILL
          }},
        { &hf_xmpp_jingle_cont_desc_enc_crypto,
          {
              "CRYPTO", "xmpp_jingle_content_description_encryption_crypto", FT_NONE, BASE_NONE, NULL, 0x0,
              "iq jingle content description encryption crypto", HFILL
          }},
        { &hf_xmpp_jingle_cont_desc_bandwidth,
          {
              "BANDWIDTH", "xmpp_jingle_content_description_bandwidth", FT_NONE, BASE_NONE, NULL, 0x0,
              "iq jingle content description bandwidth", HFILL
          }},
        { &hf_xmpp_jingle_cont_desc_rtp_hdr,
          {
              "RTP-HDREXT", "xmpp_jingle_content_description_rtp-hdrext", FT_NONE, BASE_NONE, NULL, 0x0,
              "iq jingle content description rtp-hdrext", HFILL
          }},
        { &hf_xmpp_jingle_reason,
          {
              "REASON", "xmpp_jingle_reason", FT_NONE, BASE_NONE, NULL, 0x0,
              "iq jingle reason", HFILL
          }},
        { &hf_xmpp_jingle_reason_condition,
          {
              "CONDITION", "xmpp_jingle_reason_condition", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq jingle reason condition", HFILL
          }},
        { &hf_xmpp_jingle_reason_text,
          {
              "TEXT", "xmpp_jingle_reason_text", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq jingle reason text", HFILL
          }},
        { &hf_xmpp_jingle_rtp_info,
          {
              "RTP-INFO", "xmpp_jingle_rtp_info", FT_STRING, BASE_NONE, NULL, 0x0,
              "iq jingle rtp-info(ringing, active, hold, mute, ...)", HFILL
          }},
        { &hf_xmpp_jingle_file_transfer_offer,
          {
              "OFFER", "xmpp_jingle_content_description_offer", FT_NONE, BASE_NONE, NULL, 0x0,
              "urn:xmpp:jingle:apps:file-transfer:3 offer", HFILL
          }},
        { &hf_xmpp_jingle_file_transfer_request,
          {
              "REQUEST", "xmpp_jingle_content_description_request", FT_NONE, BASE_NONE, NULL, 0x0,
              "urn:xmpp:jingle:apps:file-transfer:3 request", HFILL
          }},
        { &hf_xmpp_jingle_file_transfer_received,
          {
              "RECEIVED", "xmpp_jingle_content_received", FT_NONE, BASE_NONE, NULL, 0x0,
              "urn:xmpp:jingle:apps:file-transfer:3 received", HFILL
          }},
        { &hf_xmpp_jingle_file_transfer_abort,
          {
              "ABORT", "xmpp_jingle_content_abort", FT_NONE, BASE_NONE, NULL, 0x0,
              "urn:xmpp:jingle:apps:file-transfer:3 abort", HFILL
          }},
        { &hf_xmpp_jingle_file_transfer_checksum,
          {
              "CHECKSUM", "xmpp_jingle_content_checksum", FT_NONE, BASE_NONE, NULL, 0x0,
              "urn:xmpp:jingle:apps:file-transfer:3 checksum", HFILL
          }},
        { &hf_xmpp_si,
          {
              "SI", "xmpp_si", FT_NONE, BASE_NONE, NULL, 0x0,
              "iq si", HFILL
          }},
        { &hf_xmpp_si_file,
          {
              "FILE", "xmpp_si_file", FT_NONE, BASE_NONE, NULL, 0x0,
              "iq si file", HFILL
          }},
        { &hf_xmpp_iq_feature_neg,
          {
              "FEATURE", "xmpp_feature-neg", FT_NONE, BASE_NONE, NULL, 0x0,
              "http://jabber.org/protocol/feature-neg", HFILL
          }},
        { &hf_xmpp_x_data,
          {
              "X-DATA", "xmpp_x-data", FT_NONE, BASE_NONE, NULL, 0x0,
              "jabber:x:data", HFILL
          }},
        { &hf_xmpp_x_data_field,
          {
              "FIELD", "xmpp_x-data_field", FT_NONE, BASE_NONE, NULL, 0x0,
              "jabber:x:data field", HFILL
          }},
        { &hf_xmpp_x_data_field_value,
          {
              "VALUE", "xmpp_x-data_field_value", FT_NONE, BASE_NONE, NULL, 0x0,
              "jabber:x:data field value", HFILL
          }},
        { &hf_xmpp_x_data_instructions,
          {
              "INSTRUCTIONS", "xmpp_x-data_instructions", FT_STRING, BASE_NONE, NULL, 0x0,
              NULL, HFILL
          }},
        { &hf_xmpp_muc_user_status,
          {
              "STATUS", "xmpp_muc_user_status", FT_STRING, BASE_NONE, NULL, 0x0,
              NULL, HFILL
          }},
        { &hf_xmpp_delay,
          {
              "DELAY", "xmpp_delay", FT_NONE, BASE_NONE, NULL, 0x0,
              "urn:xmpp:delay", HFILL
          }},
        { &hf_xmpp_x_event,
          {
              "X EVENT", "xmpp_x-event", FT_NONE, BASE_NONE, NULL, 0x0,
              "jabber:x:event", HFILL
          }},
        { &hf_xmpp_x_event_condition,
          {
              "CONDITION", "xmpp_x-event_condition", FT_STRING, BASE_NONE, NULL, 0x0,
              "jabber:x:event condition", HFILL
          }},
        { &hf_xmpp_presence,
          {
              "PRESENCE", "xmpp_presence", FT_NONE, BASE_NONE, NULL, 0x0,
              "presence packet", HFILL
          }},
        { &hf_xmpp_presence_show,
          {
              "SHOW", "xmpp_presence_show", FT_STRING, BASE_NONE, NULL, 0x0,
              "presence show", HFILL
          }},
        { &hf_xmpp_presence_status,
          {
              "STATUS", "xmpp_presence_status", FT_NONE, BASE_NONE, NULL, 0x0,
              "presence status", HFILL
          }},
        { &hf_xmpp_presence_caps,
          {
              "CAPS", "xmpp_presence_caps", FT_NONE, BASE_NONE, NULL, 0x0,
              "presence caps", HFILL
          }},
        { &hf_xmpp_message,
          {
              "MESSAGE", "xmpp_message", FT_NONE, BASE_NONE, NULL, 0x0,
              "message packet", HFILL
          }},
        { &hf_xmpp_message_chatstate,
          {
              "CHATSTATE", "xmpp_message_chatstate", FT_STRING, BASE_NONE, NULL, 0x0,
              "message chatstate", HFILL
          }},
        { &hf_xmpp_message_thread,
          {
              "THREAD", "xmpp_message_thread", FT_NONE, BASE_NONE, NULL, 0x0,
              "message thread", HFILL
          }},
        { &hf_xmpp_message_body,
          {
              "BODY", "xmpp_message_body", FT_NONE, BASE_NONE, NULL, 0x0,
              "message body", HFILL
          }},
        { &hf_xmpp_message_subject,
          {
              "SUBJECT", "xmpp_message_subject", FT_NONE, BASE_NONE, NULL, 0x0,
              "message subject", HFILL
          }},
        { &hf_xmpp_message_thread_parent,
          {
              "parent", "xmpp_message_thread_parent", FT_STRING, BASE_NONE, NULL, 0x0,
              "message thread parent", HFILL
          }},
        { &hf_xmpp_auth,
          {
              "AUTH", "xmpp_auth", FT_NONE, BASE_NONE, NULL, 0x0,
              "auth packet", HFILL
          }},
        { &hf_xmpp_stream,
          {
              "STREAM", "xmpp_stream", FT_NONE, BASE_NONE, NULL, 0x0,
              "XMPP stream", HFILL
          }},
        { &hf_xmpp_failure,
          {
              "FAILURE", "xmpp_failure", FT_NONE, BASE_NONE, NULL, 0x0,
              "failure packet", HFILL
          }},
        { &hf_xmpp_failure_text,
          {
              "FAILURE TEXT", "xmpp_failure_text", FT_STRING, BASE_NONE, NULL, 0x0,
              NULL, HFILL
          }},
        { &hf_xmpp_xml_header_version,
          {
              "XML HEADER VER", "xmpp_xml_header_version", FT_STRING, BASE_NONE, NULL, 0x0,
              NULL, HFILL
          }},
        { &hf_xmpp_stream_end,
          {
              "STREAM END", "xmpp_stream_end", FT_NONE, BASE_NONE, NULL, 0x0,
              NULL, HFILL
          }},
        { &hf_xmpp_features,
          {
              "FEATURES", "xmpp_features", FT_NONE, BASE_NONE, NULL, 0x0,
              "stream features", HFILL
          }},
        { &hf_xmpp_starttls,
          {
              "STARTTLS", "xmpp_starttls", FT_NONE, BASE_NONE, NULL, 0x0,
              "starttls packet", HFILL
          }},
        { &hf_xmpp_proceed,
          {
              "PROCEED", "xmpp_proceed", FT_NONE, BASE_NONE, NULL, 0x0,
              "proceed packet", HFILL
          }},
        { &hf_xmpp_unknown,
          {
              "UNKNOWN", "xmpp_unknown", FT_STRING, BASE_NONE, NULL, 0x0,
              "unknown element", HFILL
          }},
        { &hf_xmpp_unknown_attr,
          {
              "UNKNOWN ATTR", "xmpp_unknown_attr", FT_STRING, BASE_NONE, NULL, 0x0,
              "unknown attribute", HFILL
          }},
        { &hf_xmpp_ibb_open,
          {
              "IBB-OPEN", "xmpp_ibb_open", FT_NONE, BASE_NONE, NULL, 0x0,
              "xmpp ibb open", HFILL
          }},
        { &hf_xmpp_ibb_close,
          {
              "IBB-CLOSE", "xmpp_ibb_close", FT_NONE, BASE_NONE, NULL, 0x0,
              "xmpp ibb close", HFILL
          }},
        { &hf_xmpp_ibb_data,
          {
              "IBB-DATA", "xmpp_ibb_data", FT_NONE, BASE_NONE, NULL, 0x0,
              "xmpp ibb data", HFILL
          }},
        { &hf_xmpp_muc_x,
          {
              "X MUC", "xmpp_muc-x", FT_NONE, BASE_NONE, NULL, 0x0,
              "http://jabber.org/protocol/muc", HFILL
          }},
        { &hf_xmpp_muc_user_x,
          {
              "X MUC-USER", "xmpp_muc-user-x", FT_NONE, BASE_NONE, NULL, 0x0,
              "http://jabber.org/protocol/muc#user", HFILL
          }},
        { &hf_xmpp_muc_user_item,
          {
              "ITEM", "xmpp_muc-user-x_item", FT_NONE, BASE_NONE, NULL, 0x0,
              "muc#user item", HFILL
          }},
        { &hf_xmpp_muc_user_invite,
          {
              "INVITE", "xmpp_muc-user-x_invite", FT_NONE, BASE_NONE, NULL, 0x0,
              "muc#user invite", HFILL
          }},
        { &hf_xmpp_gtalk_session,
          {
              "GTALK-SESSION", "xmpp_gtalk_session", FT_NONE, BASE_NONE, NULL, 0x0,
              "GTalk session", HFILL
          }},
        { &hf_xmpp_gtalk_session_type,
          {
              "type", "xmpp_gtalk_session_type", FT_STRING, BASE_NONE, NULL, 0x0,
              "GTalk session type", HFILL
          }},
        { &hf_xmpp_gtalk,
          {
              "GTALK SESSION", "xmpp_gtalk", FT_STRING, BASE_NONE, NULL, 0x0,
              "GTalk SID", HFILL
          }},
        { &hf_xmpp_gtalk_setting,
          {
              "USERSETTING", "xmpp_gtalk_setting", FT_NONE, BASE_NONE, NULL, 0x0,
              "google:setting usersetting", HFILL
          }},
        { &hf_xmpp_gtalk_setting_element,
          {
              "USERSETTING ELEMENT", "xmpp_gtalk_setting_element", FT_STRING, BASE_NONE, NULL, 0x0,
              NULL, HFILL
          }},
        { &hf_xmpp_gtalk_nosave_x,
          {
              "X-NOSAVE", "xmpp_gtalk_nosave_x", FT_NONE, BASE_NONE, NULL, 0x0,
              "google:nosave x", HFILL
          }},
        { &hf_xmpp_gtalk_mail_mailbox,
          {
              "MAILBOX", "xmpp_gtalk_mailbox", FT_NONE, BASE_NONE, NULL, 0x0,
              "google:mail:notify mailbox", HFILL
          }},
        { &hf_xmpp_gtalk_mail_new_mail,
          {
              "NEW MAIL", "xmpp_gtalk_new-mail", FT_NONE, BASE_NONE, NULL, 0x0,
              "google:mail:notify new-mail", HFILL
          }},
        { &hf_xmpp_gtalk_transport_p2p,
          {
              "TRANSPORT", "xmpp_gtalk_transport-p2p", FT_NONE, BASE_NONE, NULL, 0x0,
              "google/transport/p2p", HFILL
          }},
        { &hf_xmpp_gtalk_mail_snippet,
          {
              "SNIPPET", "xmpp_gtalk_mail_snippet", FT_STRING, BASE_NONE, NULL, 0x0,
              NULL, HFILL
          }},
        { &hf_xmpp_gtalk_status_status_list,
          {
              "STATUS", "xmpp_gtalk_status_status_list", FT_STRING, BASE_NONE, NULL, 0x0,
              NULL, HFILL
          }},
        { &hf_xmpp_conf_info,
          {
              "CONFERENCE INFO", "xmpp_conf-info", FT_NONE, BASE_NONE, NULL, 0x0,
              "urn:ietf:params:xml:ns:conference-info", HFILL
          }},
        { &hf_xmpp_conf_info_sid,
          {
              "sid", "xmpp_conf-info_sid", FT_STRING, BASE_NONE, NULL, 0x0,
              "urn:ietf:params:xml:ns:conference-info sid", HFILL
          }},
        { &hf_xmpp_response_in,
          { "Response In", "xmpp_response_in",
            FT_FRAMENUM, BASE_NONE, NULL, 0x0,
            "The response to this request is in this frame", HFILL }
        },
        { &hf_xmpp_response_to,
          { "Request In", "xmpp_response_to",
            FT_FRAMENUM, BASE_NONE, NULL, 0x0,
            "This is a response to the request in this frame", HFILL }
        },
        { &hf_xmpp_out,
          {
              "Out", "xmpp_out", FT_BOOLEAN, BASE_NONE, NULL, 0x0,
              "Outgoing packet", HFILL
          }},
        { &hf_xmpp_in,
          {
              "In", "xmpp_in", FT_BOOLEAN, BASE_NONE, NULL, 0x0,
              "Ingoing packet", HFILL
          }},
        { &hf_xmpp_ibb,
          {
              "IBB SESSION", "xmpp_ibb", FT_STRING, BASE_NONE, NULL, 0x0,
              "In-Band Bytestreams session", HFILL
          }},
        { &hf_xmpp_jingle_session,
          {
              "JINGLE SESSION", "xmpp_jingle_session", FT_STRING, BASE_NONE, NULL, 0x0,
              "Jingle SID", HFILL
          }},
        { &hf_xmpp_ping,
          {
              "PING", "xmpp_ping", FT_NONE, BASE_NONE, NULL, 0x0,
              "urn:xmpp:ping", HFILL
          }},
        { &hf_xmpp_hashes,
          {
              "HASHES", "xmpp_hashes", FT_NONE, BASE_NONE, NULL, 0x0,
              "urn:xmpp:hashes:0", HFILL
          }},
        { &hf_xmpp_jitsi_inputevt,
          {
              "INPUTEVT", "xmpp_inputevt", FT_NONE, BASE_NONE, NULL, 0x0,
              "http://jitsi.org/protocol/inputevt", HFILL
          }},
        { &hf_xmpp_jitsi_inputevt_rmt_ctrl,
          {
              "REMOTE-CONTROL", "xmpp_inputevt_remote-control", FT_NONE, BASE_NONE, NULL, 0x0,
              "http://jitsi.org/protocol/inputevt remote-control", HFILL
          }},
    };

    static gint * ett[] = {
        &ett_xmpp,
        &ett_xmpp_iq,
        &ett_xmpp_query,
        &ett_xmpp_query_item,
        &ett_xmpp_query_identity,
        &ett_xmpp_query_feature,
        &ett_xmpp_query_streamhost,
        &ett_xmpp_query_streamhost_used,
        &ett_xmpp_query_udpsuccess,
        &ett_xmpp_iq_error,
        &ett_xmpp_iq_bind,
        &ett_xmpp_iq_session,
        &ett_xmpp_vcard,
        &ett_xmpp_vcard_x_update,
        &ett_xmpp_jingle,
        &ett_xmpp_jingle_content,
        &ett_xmpp_jingle_content_description,
        &ett_xmpp_jingle_cont_desc_payload,
        &ett_xmpp_jingle_cont_desc_payload_param,
        &ett_xmpp_jingle_cont_desc_enc,
        &ett_xmpp_jingle_cont_desc_enc_zrtp_hash,
        &ett_xmpp_jingle_cont_desc_enc_crypto,
        &ett_xmpp_jingle_cont_desc_bandwidth,
        &ett_xmpp_jingle_cont_desc_rtp_hdr,
        &ett_xmpp_jingle_cont_trans,
        &ett_xmpp_jingle_cont_trans_cand,
        &ett_xmpp_jingle_cont_trans_rem_cand,
        &ett_xmpp_jingle_reason,
        &ett_xmpp_jingle_rtp_info,
        &ett_xmpp_services,
        &ett_xmpp_services_relay,
        &ett_xmpp_channel,
        &ett_xmpp_si,
        &ett_xmpp_si_file,
        &ett_xmpp_si_file_range,
        &ett_xmpp_iq_feature_neg,
        &ett_xmpp_x_data,
        &ett_xmpp_x_data_field,
        &ett_xmpp_x_data_field_value,
        &ett_xmpp_ibb_open,
        &ett_xmpp_ibb_close,
        &ett_xmpp_ibb_data,
        &ett_xmpp_delay,
        &ett_xmpp_x_event,
        &ett_xmpp_message,
        &ett_xmpp_message_thread,
        &ett_xmpp_message_subject,
        &ett_xmpp_message_body,
        &ett_xmpp_presence,
        &ett_xmpp_presence_status,
        &ett_xmpp_presence_caps,
        &ett_xmpp_auth,
        &ett_xmpp_challenge,
        &ett_xmpp_response,
        &ett_xmpp_success,
        &ett_xmpp_failure,
        &ett_xmpp_muc_x,
        &ett_xmpp_muc_hist,
        &ett_xmpp_muc_user_x,
        &ett_xmpp_muc_user_item,
        &ett_xmpp_muc_user_invite,
        &ett_xmpp_gtalk_session,
        &ett_xmpp_gtalk_session_desc,
        &ett_xmpp_gtalk_session_desc_payload,
        &ett_xmpp_gtalk_session_cand,
        &ett_xmpp_gtalk_session_reason,
        &ett_xmpp_gtalk_jingleinfo_stun,
        &ett_xmpp_gtalk_jingleinfo_server,
        &ett_xmpp_gtalk_jingleinfo_relay,
        &ett_xmpp_gtalk_jingleinfo_relay_serv,
        &ett_xmpp_gtalk_setting,
        &ett_xmpp_gtalk_nosave_x,
        &ett_xmpp_gtalk_mail_mailbox,
        &ett_xmpp_gtalk_mail_mail_info,
        &ett_xmpp_gtalk_mail_senders,
        &ett_xmpp_gtalk_mail_sender,
        &ett_xmpp_gtalk_status_status_list,
        &ett_xmpp_conf_info,
        &ett_xmpp_conf_desc,
        &ett_xmpp_conf_state,
        &ett_xmpp_conf_users,
        &ett_xmpp_conf_user,
        &ett_xmpp_conf_endpoint,
        &ett_xmpp_conf_media,
        &ett_xmpp_gtalk_transport_p2p,
        &ett_xmpp_gtalk_transport_p2p_cand,
        &ett_xmpp_ping,
        &ett_xmpp_hashes_hash,
        &ett_xmpp_hashes,
        &ett_xmpp_jingle_file_transfer_offer,
        &ett_xmpp_jingle_file_transfer_request,
        &ett_xmpp_jingle_file_transfer_received,
        &ett_xmpp_jingle_file_transfer_abort,
        &ett_xmpp_jingle_file_transfer_checksum,
        &ett_xmpp_jingle_file_transfer_file,
        &ett_xmpp_jitsi_inputevt,
        &ett_xmpp_jitsi_inputevt_rmt_ctrl,
        &ett_xmpp_stream,
        &ett_xmpp_features,
        &ett_xmpp_features_mechanisms,
        &ett_xmpp_starttls,
        &ett_xmpp_proceed,
    };

    static ei_register_info ei[] = {
        { &ei_xmpp_xml_disabled, { "xmpp.xml_disabled", PI_UNDECODED, PI_WARN, "XML dissector disabled, can't dissect XMPP", EXPFILL }},
        { &ei_xmpp_packet_unknown, { "xmpp.packet_unknown", PI_UNDECODED, PI_NOTE, "Unknown packet", EXPFILL }},
        { &ei_xmpp_packet_without_response, { "xmpp.packet_without_response", PI_PROTOCOL, PI_CHAT, "Packet without response", EXPFILL }},
        { &ei_xmpp_response, { "xmpp.response", PI_RESPONSE_CODE, PI_CHAT, "RESPONSE", EXPFILL }},
        { &ei_xmpp_challenge, { "xmpp.challenge", PI_RESPONSE_CODE, PI_CHAT, "CHALLENGE", EXPFILL }},
        { &ei_xmpp_success, { "xmpp.success", PI_RESPONSE_CODE, PI_CHAT, "SUCCESS", EXPFILL }},
        { &ei_xmpp_starttls_already_in_frame, { "xmpp.starttls.already_in_frame", PI_PROTOCOL, PI_WARN, "Already saw STARTTLS in frame X", EXPFILL }},
        { &ei_xmpp_starttls_missing, { "xmpp.starttls.missing", PI_PROTOCOL, PI_WARN, "Haven't seen a STARTTLS, did the capture start in the middle of a session?", EXPFILL }},
        { &ei_xmpp_proceed_already_in_frame, { "xmpp.proceed.already_in_frame", PI_PROTOCOL, PI_WARN, "Already saw PROCEED in frame X", EXPFILL }},
        { &ei_xmpp_unknown_element, { "xmpp.unknown.element", PI_UNDECODED, PI_NOTE, "Unknown element", EXPFILL }},
        { &ei_xmpp_unknown_attribute, { "xmpp.unknown.attribute", PI_UNDECODED, PI_NOTE, "Unknown attribute", EXPFILL }},
        { &ei_xmpp_required_attribute, { "xmpp.required_attribute", PI_PROTOCOL, PI_WARN, "Required attribute doesn't appear", EXPFILL }},
        { &ei_xmpp_field_unexpected_value, { "xmpp.field.unexpected_value", PI_PROTOCOL, PI_WARN, "Field has unexpected value", EXPFILL }},
    };

    module_t *xmpp_module;
    expert_module_t* expert_xmpp;

    static gint* ett_unknown_ptr[ETT_UNKNOWN_LEN];
    gint i;
    for(i=0;i<ETT_UNKNOWN_LEN;i++)
    {
        ett_unknown[i] = -1;
        ett_unknown_ptr[i] = &ett_unknown[i];
    }

    proto_xmpp = proto_register_protocol(
        "XMPP Protocol", /* name       */
        "XMPP",          /* short name */
        "xmpp"           /* abbrev     */
        );

    xmpp_module = prefs_register_protocol(proto_xmpp, NULL);
    prefs_register_bool_preference(xmpp_module, "desegment",
                                   "Reassemble XMPP messages",
                                   "Whether the XMPP dissector should reassemble messages. "
                                   "To use this option, you must also enable"
                                   " \"Allow subdissectors to reassemble TCP streams\""
                                   " in the TCP protocol settings",
                                   &xmpp_desegment);

    proto_register_field_array(proto_xmpp, hf, array_length(hf));
    proto_register_subtree_array(ett, array_length(ett));
    proto_register_subtree_array(ett_unknown_ptr, array_length(ett_unknown_ptr));
    expert_xmpp = expert_register_protocol(proto_xmpp);
    expert_register_field_array(expert_xmpp, ei, array_length(ei));

    xmpp_handle = register_dissector("xmpp", dissect_xmpp, proto_xmpp);

    xmpp_init_parsers();
}

void
proto_reg_handoff_xmpp(void) {
    xml_handle  = find_dissector_add_dependency("xml", proto_xmpp);

    dissector_add_uint_with_preference("tcp.port", XMPP_PORT, xmpp_handle);

}
/*
* Editor modelines - https://www.wireshark.org/tools/modelines.html
*
* Local variables:
* c-basic-offset: 4
* tab-width: 8
* indent-tabs-mode: nil
* End:
*
* ex: set shiftwidth=4 tabstop=8 expandtab:
* :indentSize=4:tabSize=8:noTabs=true:
*/
