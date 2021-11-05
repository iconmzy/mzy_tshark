/* packet_info.h
 * Definitions for packet info structures and routines
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef __PACKET_INFO_H__
#define __PACKET_INFO_H__

#include "frame_data.h"
#include "tvbuff.h"
#include "address.h"

struct endpoint;

/** @file
 * Dissected packet data and metadata.
 */

/** @defgroup packetinfo Packet Data and Metadata
 *
 * @{
 */

/* Also defined in wiretap/wtap.h */
#define P2P_DIR_UNKNOWN -1
#define P2P_DIR_SENT    0
#define P2P_DIR_RECV    1

/* Link direction */
#define LINK_DIR_UNKNOWN    -1
#define P2P_DIR_UL  0
#define P2P_DIR_DL  1

/*
 * Presence flags.
 */
#define PINFO_HAS_TS            0x00000001  /**< time stamp */

typedef struct _packet_info {
    const char *current_proto;        /**< 当前正在解析的协议名称 name of protocol currently being dissected */
    struct epan_column_info *cinfo;   /**< /wireshark显示的信息 Column formatting information */
    guint32 presence_flags;           /**< Presence flags for some items */
    guint32 num;                      /**< Frame number */
    nstime_t abs_ts;                  /**< Packet absolute time stamp */
    nstime_t rel_ts;                  /**< Relative timestamp (yes, it can be negative) */
    frame_data *fd;                   /** 现在分析的原始数据指针 */
    union wtap_pseudo_header *pseudo_header;  /** frame类型信息 */
    wtap_rec *rec;                    /**< Record metadata */
    GSList *data_src;                 /**< frame层信息 Frame data sources */
    address dl_src;                   /**< 源MAC link-layer source address */
    address dl_dst;                   /**< 目的MAC link-layer destination address */
    address net_src;                  /**< 源IP network-layer source address */
    address net_dst;                  /**< 目的IP network-layer destination address */
    address src;                      /**< 源IP source address (net if present, DL otherwise )*/
    address dst;                      /**< 目的IP destination address (net if present, DL otherwise )*/
    guint32 vlan_id;                  /**< First encountered VLAN Id if present otherwise 0 */
    const char *noreassembly_reason;  /**< 重组失败原因 reason why reassembly wasn't done, if any */
    gboolean fragmented;              /**< 为真表示未分片 TRUE if the protocol is only a fragment */
    struct {
        guint32 in_error_pkt:1;         /**< TRUE if we're inside an {ICMP,CLNP,...} error packet */
        guint32 in_gre_pkt:1;           /**< TRUE if we're encapsulated inside a GRE packet */
    } flags;
    port_type ptype;                  /**< 端口类型 type of the following two port numbers */
    guint32 srcport;                  /**< 源端口 source port */
    guint32 destport;                 /**< 目的端口 destination port */
    guint32 match_uint;               /**< matched uint for calling subdissector from table */
    const char *match_string;         /**< 调用子解析引擎时匹配的协议字段指针 matched string for calling subdissector from table */
    gboolean use_endpoint;            /**< TRUE if endpoint member should be used for conversations */
    struct endpoint *conv_endpoint;   /**< Data that can be used for conversations */
    guint16 can_desegment;            /**< 能否分段标志 >0 if this segment could be desegmented.
                                         A dissector that can offer this API (e.g.
                                         TCP) sets can_desegment=2, then
                                         can_desegment is decremented by 1 each time
                                         we pass to the next subdissector. Thus only
                                         the dissector immediately above the
                                         protocol which sets the flag can use it*/
    guint16 saved_can_desegment;      /**< Value of can_desegment before current
                                         dissector was called.  Supplied so that
                                         dissectors for proxy protocols such as
                                         SOCKS can restore it, allowing the
                                         dissectors that they call to use the
                                         TCP dissector's desegmentation (SOCKS
                                         just retransmits TCP segments once it's
                                         finished setting things up, so the TCP
                                         desegmentor can desegment its payload). */
    int desegment_offset;             /**< 分段大小 offset to stuff needing desegmentation */
#define DESEGMENT_ONE_MORE_SEGMENT 0x0fffffff
#define DESEGMENT_UNTIL_FIN        0x0ffffffe
    guint32 desegment_len;            /**< requested desegmentation additional length
                                       or
                                       DESEGMENT_ONE_MORE_SEGMENT:
                                         Desegment one more full segment
                                         (warning! only partially implemented)
                                       DESEGMENT_UNTIL_FIN:
                                         Desgment all data for this tcp session
                                         until the FIN segment.
                                    */
    guint16 want_pdu_tracking;    /**< >0 if the subdissector has specified
                                   a value in 'bytes_until_next_pdu'.
                                   When a dissector detects that the next PDU
                                   will start beyond the start of the next
                                   segment, it can set this value to 2
                                   and 'bytes_until_next_pdu' to the number of
                                   bytes beyond the next segment where the
                                   next PDU starts.

                                   If the protocol dissector below this
                                   one is capable of PDU tracking it can
                                   use this hint to detect PDUs that starts
                                   unaligned to the segment boundaries.
                                   The TCP dissector is using this hint from
                                   (some) protocols to detect when a new PDU
                                   starts in the middle of a tcp segment.

                                   There is intelligence in the glue between
                                   dissector layers to make sure that this
                                   request is only passed down to the protocol
                                   immediately below the current one and not
                                   any further.
                                */
    guint32 bytes_until_next_pdu;

    int p2p_dir;              /**< Packet was captured as an
                                       outbound (P2P_DIR_SENT)
                                       inbound (P2P_DIR_RECV)
                                       unknown (P2P_DIR_UNKNOWN) */

    GHashTable *private_table;    /**< a hash table passed from one dissector to another */

    wmem_list_t *layers;      /**< layers of each protocol */
    guint8 curr_layer_num;       /**< The current "depth" or layer number in the current frame */
    guint16 link_number;

    guint16 clnp_srcref;          /**< clnp/cotp source reference (can't use srcport, this would confuse tpkt) */
    guint16 clnp_dstref;          /**< clnp/cotp destination reference (can't use dstport, this would confuse tpkt) */

    int link_dir;                 /**< 3GPP messages are sometime different UP link(UL) or Downlink(DL) */

    GSList *proto_data;          /**< Per packet proto data */

    GSList *dependent_frames;     /**< A list of frames which this one depends on */

    GSList *frame_end_routines;

    wmem_allocator_t *pool;      /**< Memory pool scoped to the pinfo struct */
    struct epan_session *epan;
    const gchar *heur_list_name;    /**< name of heur list if this packet is being heuristically dissected */
} packet_info;

/** @} */

#endif /* __PACKET_INFO_H__ */

/*
 * Editor modelines
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
