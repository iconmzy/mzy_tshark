/*
 * Do not modify this file. Changes will be overwritten.
 *
 * Generated automatically using "make-regs.py".
 */

#include "ui/taps.h"

const gulong tap_reg_listener_count = 10;

void register_tap_listener_qt_expert_info(void);
void register_tap_listener_qt_funnel(void);
void register_tap_listener_qt_gsm_map_summary(void);
void register_tap_listener_qt_iostat(void);
void register_tap_listener_qt_lte_mac_statistics(void);
void register_tap_listener_qt_lte_rlc_statistics(void);
void register_tap_listener_qt_mtp3_summary(void);
void register_tap_listener_qt_multicast_statistics(void);
void register_tap_listener_qt_stats_tree_stat(void);
void register_tap_listener_qt_wlan_statistics(void);

tap_reg_t tap_reg_listener[] = {
    { "register_tap_listener_qt_expert_info", register_tap_listener_qt_expert_info },
    { "register_tap_listener_qt_funnel", register_tap_listener_qt_funnel },
    { "register_tap_listener_qt_gsm_map_summary", register_tap_listener_qt_gsm_map_summary },
    { "register_tap_listener_qt_iostat", register_tap_listener_qt_iostat },
    { "register_tap_listener_qt_lte_mac_statistics", register_tap_listener_qt_lte_mac_statistics },
    { "register_tap_listener_qt_lte_rlc_statistics", register_tap_listener_qt_lte_rlc_statistics },
    { "register_tap_listener_qt_mtp3_summary", register_tap_listener_qt_mtp3_summary },
    { "register_tap_listener_qt_multicast_statistics", register_tap_listener_qt_multicast_statistics },
    { "register_tap_listener_qt_stats_tree_stat", register_tap_listener_qt_stats_tree_stat },
    { "register_tap_listener_qt_wlan_statistics", register_tap_listener_qt_wlan_statistics },
    { NULL, NULL }
};
