/* tap-iousers.c
 * iostat   2003 Ronnie Sahlberg
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "config.h"
#include "epan/write_in_files_handlers.h"

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <epan/packet.h>
#include <epan/timestamp.h>
#include <epan/strutil.h>
#include <ui/cmdarg_err.h>
#include <ui/cli/tshark-tap.h>

typedef struct _io_users_t {
    const char *type;
    const char *filter;
    conv_hash_t hash;
} io_users_t;


static void
iousers_draw(void *arg) {
    conv_hash_t *hash = (conv_hash_t *) arg;
    io_users_t *iu = (io_users_t *) hash->user_data;
    conv_item_t *iui;
    guint64 last_frames, max_frames;
    struct tm *tm_time;
    int nsec_tm;
    guint i;
    gboolean display_ports = (!strncmp(iu->type, "TCP", 3) || !strncmp(iu->type, "UDP", 3) ||
                              !strncmp(iu->type, "SCTP", 4)) ? TRUE : FALSE;

//	printf("================================================================================\n");
//	printf("%s Conversations\n", iu->type);
//	printf("Filter:%s\n", iu->filter ? iu->filter : "<No Filter>");

//	switch (timestamp_get_type()) {
//	case TS_ABSOLUTE:
//	case TS_UTC:
//		printf("%s                                               |       <-      | |       ->      | |     Total     | Absolute Time  |   Duration   |\n",
//			display_ports ? "            " : "");
//		printf("%s                                               | Frames  Size  | | Frames  Size  | | Frames  Size  |      Start     |              |\n",
//			display_ports ? "            " : "");
//		break;
//	case TS_ABSOLUTE_WITH_YMD:
//	case TS_ABSOLUTE_WITH_YDOY:
//	case TS_UTC_WITH_YMD:
//	case TS_UTC_WITH_YDOY:
//		printf("%s                                               |       <-      | |       ->      | |     Total     | Absolute Date  |   Duration   |\n",
//			display_ports ? "            " : "");
//		printf("%s                                               | Frames  Size  | | Frames  Size  | | Frames  Size  |     Start      |              |\n",
//			display_ports ? "            " : "");
//		break;
//	case TS_EPOCH:
//		printf("%s                                               |       <-      | |       ->      | |     Total     |       Relative       |   Duration   |\n",
//			display_ports ? "            " : "");
//		printf("%s                                               | Frames  Bytes | | Frames  Bytes | | Frames  Bytes |         Start        |              |\n",
//			display_ports ? "            " : "");
//		break;
//	case TS_RELATIVE:
//	case TS_NOT_SET:
//	default:
//		printf("%s                                               |       <-      | |       ->      | |     Total     |    Relative    |   Duration   |\n",
//			display_ports ? "            " : "");
//		printf("%s                                               | Frames  Bytes | | Frames  Bytes | | Frames  Bytes |      Start     |              |\n",
//			display_ports ? "            " : "");
//		break;
//	}

    max_frames = UINT_MAX;
    do {
        last_frames = 0;
        for (i = 0; (iu->hash.conv_array && i < iu->hash.conv_array->len); i++) {
            guint64 tot_frames;

            iui = &g_array_index(iu->hash.conv_array, conv_item_t, i);
            tot_frames = iui->rx_frames + iui->tx_frames;

            if ((tot_frames > last_frames) && (tot_frames < max_frames)) {
                last_frames = tot_frames;
            }
        }

        for (i = 0; (iu->hash.conv_array && i < iu->hash.conv_array->len); i++) {
            guint64 tot_frames;
            char *src_addr, *dst_addr;

            iui = &g_array_index(iu->hash.conv_array, conv_item_t, i);
            tot_frames = iui->rx_frames + iui->tx_frames;

            if (tot_frames == last_frames) {

                char *rx_bytes, *tx_bytes, *total_bytes;
                long int m_rx_bytes, m_tx_bytes, m_total_bytes;
                long int m_rx_frame, m_tx_frames, m_total_frames;
                char abs_start[32] = {0};
                m_rx_bytes = iui->rx_bytes;
                m_tx_bytes = iui->tx_bytes;
                m_total_bytes = iui->rx_bytes + iui->tx_bytes;
                m_rx_frame = iui->rx_frames;
                m_tx_frames = iui->tx_frames;
                m_total_frames = m_rx_frame + m_tx_frames;

                rx_bytes = format_size_wmem(NULL, iui->rx_bytes, (format_size_flags_e) (format_size_unit_bytes |
                                                                                        format_size_suffix_no_space));
                tx_bytes = format_size_wmem(NULL, iui->tx_bytes, (format_size_flags_e) (format_size_unit_bytes |
                                                                                        format_size_suffix_no_space));
                total_bytes = format_size_wmem(NULL, iui->tx_bytes + iui->rx_bytes,
                                               (format_size_flags_e) (format_size_unit_bytes |
                                                                      format_size_suffix_no_space));

                /* XXX - TODO: make name / port resolution configurable (through gbl_resolv_flags?) */
                src_addr = get_conversation_address(NULL, &iui->src_address, TRUE);
                dst_addr = get_conversation_address(NULL, &iui->dst_address, TRUE);
                if (display_ports) {
                    char *src, *dst, *src_port, *dst_port;
                    src_port = get_conversation_port(NULL, iui->src_port, iui->etype, TRUE);
                    dst_port = get_conversation_port(NULL, iui->dst_port, iui->etype, TRUE);
                    src = wmem_strconcat(NULL, src_addr, ":", src_port, NULL);
                    dst = wmem_strconcat(NULL, dst_addr, ":", dst_port, NULL);
//					printf("%-26s <-> %-26s  %6" G_GINT64_MODIFIER "u %-9s"
//					       "  %6" G_GINT64_MODIFIER "u %-9s"
//					       "  %6" G_GINT64_MODIFIER "u %-9s  ",
//						src, dst,
//						iui->rx_frames, rx_bytes,
//						iui->tx_frames, tx_bytes,
//						iui->tx_frames+iui->rx_frames,
//						total_bytes
//					);
                    if (WRITE_IN_CONVERSATIONS_FLAG) {
                        do_write_in_conversation_handler("src_ip", src_addr);
                        do_write_in_conversation_handler("src_port", src_port);
                        do_write_in_conversation_handler("dst_ip", dst_addr);
                        do_write_in_conversation_handler("dst_port", dst_port);
                        do_write_in_conversation_handler("recv_frames", my_itoa(m_rx_frame));
                        do_write_in_conversation_handler("recv_bytes", my_itoa(m_rx_bytes));
                        do_write_in_conversation_handler("send_frames", my_itoa(m_tx_frames));
                        do_write_in_conversation_handler("send_bytes", my_itoa(m_tx_bytes));
                        do_write_in_conversation_handler("total_frames", my_itoa(m_total_frames));
                        do_write_in_conversation_handler("total_bytes", my_itoa(m_total_bytes));
                    }

                    wmem_free(NULL, src_port);
                    wmem_free(NULL, dst_port);
                    wmem_free(NULL, src);
                    wmem_free(NULL, dst);
                } else {
                    printf("%-20s <-> %-20s  %6" G_GINT64_MODIFIER "u %-9s"
                           "  %6" G_GINT64_MODIFIER "u %-9s"
                           "  %6" G_GINT64_MODIFIER "u %-9s  ",
                           src_addr, dst_addr,
                           iui->rx_frames, rx_bytes,
                           iui->tx_frames, tx_bytes,
                           iui->tx_frames + iui->rx_frames,
                           total_bytes
                    );
                }

                wmem_free(NULL, src_addr);
                wmem_free(NULL, dst_addr);
                wmem_free(NULL, rx_bytes);
                wmem_free(NULL, tx_bytes);
                wmem_free(NULL, total_bytes);
                char t[32] = {0};

                switch (timestamp_get_type()) {
                    case TS_ABSOLUTE:
                        tm_time = localtime(&iui->start_abs_time.secs);
                        if (tm_time != NULL) {
                            printf("%02d:%02d:%02d",
                                   tm_time->tm_hour,
                                   tm_time->tm_min,
                                   tm_time->tm_sec);
                        } else
                            printf("XX:XX:XX");
                        break;
                    case TS_ABSOLUTE_WITH_YMD:
                        tm_time = localtime(&iui->start_abs_time.secs);
                        if (tm_time != NULL) {
                            printf("%04d-%02d-%02d %02d:%02d:%02d",
                                   tm_time->tm_year + 1900,
                                   tm_time->tm_mon + 1,
                                   tm_time->tm_mday,
                                   tm_time->tm_hour,
                                   tm_time->tm_min,
                                   tm_time->tm_sec);
                        } else
                            printf("XXXX-XX-XX XX:XX:XX");
                        break;
                    case TS_ABSOLUTE_WITH_YDOY:
                        tm_time = localtime(&iui->start_abs_time.secs);
                        if (tm_time != NULL) {
                            printf("%04d/%03d %02d:%02d:%02d",
                                   tm_time->tm_year + 1900,
                                   tm_time->tm_yday + 1,
                                   tm_time->tm_hour,
                                   tm_time->tm_min,
                                   tm_time->tm_sec);
                        } else
                            printf("XXXX/XXX XX:XX:XX");
                        break;
                    case TS_UTC:
                        tm_time = gmtime(&iui->start_abs_time.secs);
                        if (tm_time != NULL) {
                            printf("%02d:%02d:%02d",
                                   tm_time->tm_hour,
                                   tm_time->tm_min,
                                   tm_time->tm_sec);
                        } else
                            printf("XX:XX:XX");
                        break;
                    case TS_UTC_WITH_YMD:
                        tm_time = gmtime(&iui->start_abs_time.secs);
                        if (tm_time != NULL) {
                            printf("%04d-%02d-%02d %02d:%02d:%02d",
                                   tm_time->tm_year + 1900,
                                   tm_time->tm_mon + 1,
                                   tm_time->tm_mday,
                                   tm_time->tm_hour,
                                   tm_time->tm_min,
                                   tm_time->tm_sec);
                        } else
                            printf("XXXX-XX-XX XX:XX:XX");
                        break;
                    case TS_UTC_WITH_YDOY:
                        tm_time = gmtime(&iui->start_abs_time.secs);
                        if (tm_time != NULL) {
                            printf("%04d/%03d %02d:%02d:%02d",
                                   tm_time->tm_year + 1900,
                                   tm_time->tm_yday + 1,
                                   tm_time->tm_hour,
                                   tm_time->tm_min,
                                   tm_time->tm_sec);
                        } else
                            printf("XXXX/XXX XX:XX:XX");
                        break;
                    case TS_EPOCH:
                        printf("%20.9f", nstime_to_sec(&iui->start_abs_time));
                        break;
                    case TS_RELATIVE:
                    case TS_NOT_SET:
                    default:
//					printf("%14.9f",nstime_to_sec(&iui->start_time));
                        tm_time = gmtime(&iui->start_abs_time.secs);
//                        nsec_tm = iui->start_abs_time.nsecs;
//                        strcat(abs_start,my_itoa(tm_time->tm_year+1900));
//                        strcat(abs_start,"y");
//                        strcat(abs_start,my_itoa(tm_time->tm_mon+1));
//                        strcat(abs_start,"m");
//                        strcat(abs_start,my_itoa(tm_time->tm_mday));
//                        strcat(abs_start,"d ");
//                        strcat(abs_start,my_itoa(tm_time->tm_hour +8));
//                        strcat(abs_start,"h");
//                        strcat(abs_start,my_itoa(tm_time->tm_min));
//                        strcat(abs_start,"m");
//                        strcat(abs_start,my_itoa(tm_time->tm_sec));

//                        strcat(abs_start,my_itoa((int)iui->start_abs_time.secs));
//                        strcat(abs_start,".");
//                        strcat(abs_start,my_itoa(nsec_tm));
//                        strcat(abs_start,"s");

//                        sprintf(abs_start, "%d.%d", (int)iui->start_abs_time.secs, nsec_tm);  // 格式化数据写入字符串
                        // 将时间戳的秒部分转换为 yyyy-MM-dd HH-mm-SS
                        sprintf(abs_start, "%4d-%02d-%02d %02d:%02d:%02d", tm_time->tm_year + 1900, tm_time->tm_mon + 1,
                                tm_time->tm_mday, tm_time->tm_hour + 8, tm_time->tm_min, tm_time->tm_sec);

                        do_write_in_conversation_handler("start_abs_time", abs_start);

                        float2char(nstime_to_sec(&iui->start_time), t, 11);
                        do_write_in_conversation_handler("relative_start", t);
                        memset(t, '\0', 32);
                        break;
                }
//				printf("   %12.4f\n",nstime_to_sec(&iui->stop_time) - nstime_to_sec(&iui->start_time));

                float2char(nstime_to_sec(&iui->stop_time) - nstime_to_sec(&iui->start_time), t, 11);
                do_write_in_conversation_handler("duration", t);
                memset(t, '\0', 32);
                /*一个会话统计结束标志。*/
                do_write_in_conversation_handler("1END", "-1END");
            }
        }

        max_frames = last_frames;
    } while (last_frames);
//	printf("================================================================================\n");
}

void init_iousers(struct register_ct *ct, const char *filter) {
    io_users_t *iu;
    GString *error_string;

    iu = g_new0(io_users_t, 1);
    iu->type = proto_get_protocol_short_name(find_protocol_by_id(get_conversation_proto_id(ct)));
    iu->filter = g_strdup(filter);
    iu->hash.user_data = iu;

    error_string = register_tap_listener(proto_get_protocol_filter_name(get_conversation_proto_id(ct)), &iu->hash,
                                         filter, 0, NULL, get_conversation_packet_func(ct), iousers_draw, NULL);
    if (error_string) {
        g_free(iu);
        cmdarg_err("Couldn't register conversations tap: %s",
                   error_string->str);
        g_string_free(error_string, TRUE);
        exit(1);
    }

}

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 8
 * tab-width: 8
 * indent-tabs-mode: t
 * End:
 *
 * vi: set shiftwidth=8 tabstop=8 noexpandtab:
 * :indentSize=8:tabSize=8:noTabs=false:
 */
