/* packet-ipmi-transport.c
 * Sub-dissectors for IPMI messages (netFn=Transport)
 * Copyright 2007-2008, Alexey Neyman, Pigeon Point Systems <avn@pigeonpoint.com>
 * Copyright 2015, Dmitry Bazhenov, Pigeon Point Systems <dima_b@pigeonpoint.com>
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "config.h"

#include <epan/packet.h>

#include "packet-ipmi.h"

void proto_register_ipmi_transport(void);

static gint ett_ipmi_trn_lan00_byte1 = -1;
static gint ett_ipmi_trn_lan01_byte1 = -1;
static gint ett_ipmi_trn_lan02_byte1 = -1;
static gint ett_ipmi_trn_lan02_byte2 = -1;
static gint ett_ipmi_trn_lan02_byte3 = -1;
static gint ett_ipmi_trn_lan02_byte4 = -1;
static gint ett_ipmi_trn_lan02_byte5 = -1;
static gint ett_ipmi_trn_lan04_byte1 = -1;
static gint ett_ipmi_trn_lan07_byte2 = -1;
static gint ett_ipmi_trn_lan07_byte3 = -1;
static gint ett_ipmi_trn_lan10_byte1 = -1;
static gint ett_ipmi_trn_lan17_byte1 = -1;
static gint ett_ipmi_trn_lan18_byte1 = -1;
static gint ett_ipmi_trn_lan18_byte2 = -1;
static gint ett_ipmi_trn_lan18_byte4 = -1;
static gint ett_ipmi_trn_lan19_byte1 = -1;
static gint ett_ipmi_trn_lan19_byte2 = -1;
static gint ett_ipmi_trn_lan19_byte3 = -1;
static gint ett_ipmi_trn_lan20_byte12 = -1;
static gint ett_ipmi_trn_lan21_byte1 = -1;
static gint ett_ipmi_trn_lan22_byte1 = -1;
static gint ett_ipmi_trn_lan24_byte1 = -1;
static gint ett_ipmi_trn_lan24_byte2 = -1;
static gint ett_ipmi_trn_lan24_byte3 = -1;
static gint ett_ipmi_trn_lan24_byte4 = -1;
static gint ett_ipmi_trn_lan24_byte5 = -1;
static gint ett_ipmi_trn_lan24_byte6 = -1;
static gint ett_ipmi_trn_lan24_byte7 = -1;
static gint ett_ipmi_trn_lan24_byte8 = -1;
static gint ett_ipmi_trn_lan25_byte1 = -1;
static gint ett_ipmi_trn_lan25_byte2 = -1;
static gint ett_ipmi_trn_lan25_byte34 = -1;
static gint ett_ipmi_trn_lan50_byte1 = -1;
static gint ett_ipmi_trn_lan55_byte3 = -1;
static gint ett_ipmi_trn_lan56_byte2 = -1;
static gint ett_ipmi_trn_lan64_byte1 = -1;
static gint ett_ipmi_trn_serial03_byte1 = -1;
static gint ett_ipmi_trn_serial04_byte1 = -1;
static gint ett_ipmi_trn_serial05_byte1 = -1;
static gint ett_ipmi_trn_serial05_byte2 = -1;
static gint ett_ipmi_trn_serial06_byte1 = -1;
static gint ett_ipmi_trn_serial07_byte1 = -1;
static gint ett_ipmi_trn_serial07_byte2 = -1;
static gint ett_ipmi_trn_serial08_byte1 = -1;
static gint ett_ipmi_trn_serial08_byte2 = -1;
static gint ett_ipmi_trn_serial09_byte1 = -1;
static gint ett_ipmi_trn_serial09_byte2 = -1;
static gint ett_ipmi_trn_serial16_byte1 = -1;
static gint ett_ipmi_trn_serial17_byte1 = -1;
static gint ett_ipmi_trn_serial17_byte2 = -1;
static gint ett_ipmi_trn_serial17_byte4 = -1;
static gint ett_ipmi_trn_serial17_byte5 = -1;
static gint ett_ipmi_trn_serial19_byte1 = -1;
static gint ett_ipmi_trn_serial19_byte2 = -1;
static gint ett_ipmi_trn_serial19_byte3 = -1;
static gint ett_ipmi_trn_serial20_byte1 = -1;
static gint ett_ipmi_trn_serial21_byte1 = -1;
static gint ett_ipmi_trn_serial22_byte1 = -1;
static gint ett_ipmi_trn_serial23_byte1 = -1;
static gint ett_ipmi_trn_serial24_byte1 = -1;
static gint ett_ipmi_trn_serial25_byte2 = -1;
static gint ett_ipmi_trn_serial28_byte1 = -1;
static gint ett_ipmi_trn_serial28_byte2 = -1;
static gint ett_ipmi_trn_serial28_byte10 = -1;
static gint ett_ipmi_trn_serial28_byte11 = -1;
static gint ett_ipmi_trn_serial28_byte12 = -1;
static gint ett_ipmi_trn_serial28_byte13 = -1;
static gint ett_ipmi_trn_serial28_byte14 = -1;
static gint ett_ipmi_trn_serial29_byte1 = -1;
static gint ett_ipmi_trn_serial29_byte2 = -1;
static gint ett_ipmi_trn_serial30_byte1 = -1;
static gint ett_ipmi_trn_serial30_byte2 = -1;
static gint ett_ipmi_trn_serial30_byte3 = -1;
static gint ett_ipmi_trn_serial33_byte1 = -1;
static gint ett_ipmi_trn_serial37_byte1 = -1;
static gint ett_ipmi_trn_serial43_byte1 = -1;
static gint ett_ipmi_trn_serial50_byte1 = -1;
static gint ett_ipmi_trn_serial51_byte2 = -1;
static gint ett_ipmi_trn_serial51_byte3 = -1;
static gint ett_ipmi_trn_01_byte1 = -1;
static gint ett_ipmi_trn_02_byte1 = -1;
static gint ett_ipmi_trn_02_rev = -1;
static gint ett_ipmi_trn_03_rq_byte1 = -1;
static gint ett_ipmi_trn_03_rq_byte2 = -1;
static gint ett_ipmi_trn_03_rs_byte1 = -1;
static gint ett_ipmi_trn_04_byte1 = -1;
static gint ett_ipmi_trn_04_byte2 = -1;
static gint ett_ipmi_trn_10_byte1 = -1;
static gint ett_ipmi_trn_11_byte1 = -1;
static gint ett_ipmi_trn_11_rev = -1;
static gint ett_ipmi_trn_12_rq_byte1 = -1;
static gint ett_ipmi_trn_12_rq_byte2 = -1;
static gint ett_ipmi_trn_12_rs_byte1 = -1;
static gint ett_ipmi_trn_13_byte1 = -1;
static gint ett_ipmi_trn_14_byte1 = -1;
static gint ett_ipmi_trn_15_byte1 = -1;
static gint ett_ipmi_trn_16_byte1 = -1;
static gint ett_ipmi_trn_17_byte1 = -1;
static gint ett_ipmi_trn_17_byte2 = -1;
static gint ett_ipmi_trn_18_byte1 = -1;
static gint ett_ipmi_trn_19_byte1 = -1;
static gint ett_ipmi_trn_19_byte2 = -1;
static gint ett_ipmi_trn_XX_usercap = -1;
static gint ett_ipmi_trn_XX_cbcp = -1;
static gint ett_ipmi_trn_1a_byte1 = -1;
static gint ett_ipmi_trn_1a_byte2 = -1;
static gint ett_ipmi_trn_1b_byte1 = -1;
static gint ett_ipmi_trn_1b_byte2 = -1;
static gint ett_ipmi_trn_parameter = -1;

static gint hf_ipmi_trn_lan00_sip = -1;

static gint hf_ipmi_trn_lanXX_oem = -1;
static gint hf_ipmi_trn_lanXX_passwd = -1;
static gint hf_ipmi_trn_lanXX_md5 = -1;
static gint hf_ipmi_trn_lanXX_md2 = -1;
static gint hf_ipmi_trn_lanXX_none = -1;

static gint hf_ipmi_trn_lan03_ip = -1;

static gint hf_ipmi_trn_lan04_ipsrc = -1;

static gint hf_ipmi_trn_lan05_ether = -1;

static gint hf_ipmi_trn_lan06_subnet = -1;

static gint hf_ipmi_trn_lan07_ttl = -1;
static gint hf_ipmi_trn_lan07_flags = -1;
static gint hf_ipmi_trn_lan07_precedence = -1;
static gint hf_ipmi_trn_lan07_tos = -1;

static gint hf_ipmi_trn_lan08_rmcp_port = -1;

static gint hf_ipmi_trn_lan09_rmcp_port = -1;

static gint hf_ipmi_trn_lan10_responses = -1;
static gint hf_ipmi_trn_lan10_gratuitous = -1;

static gint hf_ipmi_trn_lan11_arp_interval = -1;

static gint hf_ipmi_trn_lan12_def_gw_ip = -1;

static gint hf_ipmi_trn_lan13_def_gw_mac = -1;

static gint hf_ipmi_trn_lan14_bkp_gw_ip = -1;

static gint hf_ipmi_trn_lan15_bkp_gw_mac = -1;

static gint hf_ipmi_trn_lan16_comm_string = -1;

static gint hf_ipmi_trn_lan17_num_dst = -1;

static gint hf_ipmi_trn_lan18_dst_selector = -1;
static gint hf_ipmi_trn_lan18_ack = -1;
static gint hf_ipmi_trn_lan18_dst_type = -1;
static gint hf_ipmi_trn_lan18_tout = -1;
static gint hf_ipmi_trn_lan18_retries = -1;

static gint hf_ipmi_trn_lan19_dst_selector = -1;
static gint hf_ipmi_trn_lan19_addr_format = -1;
static gint hf_ipmi_trn_lan19_address = -1;
static gint hf_ipmi_trn_lan19_gw_sel = -1;
static gint hf_ipmi_trn_lan19_ip = -1;
static gint hf_ipmi_trn_lan19_mac = -1;

static gint hf_ipmi_trn_lan20_vlan_id_enable = -1;
static gint hf_ipmi_trn_lan20_vlan_id = -1;

static gint hf_ipmi_trn_lan21_vlan_prio = -1;

static gint hf_ipmi_trn_lan22_num_cs_entries = -1;

static gint hf_ipmi_trn_lan23_cs_entry = -1;

static gint hf_ipmi_trn_lan24_priv1 = -1;
static gint hf_ipmi_trn_lan24_priv2 = -1;

static gint hf_ipmi_trn_lan25_dst_selector = -1;
static gint hf_ipmi_trn_lan25_addr_format = -1;
static gint hf_ipmi_trn_lan25_address = -1;
static gint hf_ipmi_trn_lan25_uprio = -1;
static gint hf_ipmi_trn_lan25_cfi = -1;
static gint hf_ipmi_trn_lan25_vlan_id = -1;

static gint hf_ipmi_trn_lan26_gen_event = -1;
static gint hf_ipmi_trn_lan26_thresh_number = -1;
static gint hf_ipmi_trn_lan26_reset_interval = -1;
static gint hf_ipmi_trn_lan26_lock_interval = -1;

static gint hf_ipmi_trn_lan50_ipv6_only = -1;
static gint hf_ipmi_trn_lan50_both_ipv4_ipv6 = -1;
static gint hf_ipmi_trn_lan50_ipv6_alerting = -1;

static gint hf_ipmi_trn_lan51_enables = -1;

static gint hf_ipmi_trn_lan52_traffic_class = -1;

static gint hf_ipmi_trn_lanXX_hop_limit = -1;

static gint hf_ipmi_trn_lan54_flow_label = -1;

static gint hf_ipmi_trn_lan55_static_addr_max = -1;
static gint hf_ipmi_trn_lan55_dynamic_addr_max = -1;
static gint hf_ipmi_trn_lan55_dhcpv6_support = -1;
static gint hf_ipmi_trn_lan55_slaac_support = -1;

static gint hf_ipmi_trn_lanXX_addr_selector = -1;
static gint hf_ipmi_trn_lanXX_addr_type = -1;
static gint hf_ipmi_trn_lanXX_addr_enable = -1;
static gint hf_ipmi_trn_lanXX_addr = -1;
static gint hf_ipmi_trn_lanXX_prefix_len = -1;
static gint hf_ipmi_trn_lanXX_addr_status = -1;

static gint hf_ipmi_trn_lanXX_max_duid_blocks = -1;

static gint hf_ipmi_trn_lanXX_duid_selector = -1;
static gint hf_ipmi_trn_lanXX_block_selector = -1;
static gint hf_ipmi_trn_lanXX_duid = -1;

static gint hf_ipmi_trn_lanXX_timing_support = -1;

static gint hf_ipmi_trn_lanXX_iface_selector = -1;
static gint hf_ipmi_trn_lan63_sol_max_delay = -1;
static gint hf_ipmi_trn_lan63_sol_timeout = -1;
static gint hf_ipmi_trn_lan63_sol_max_rt = -1;
static gint hf_ipmi_trn_lan63_req_timeout = -1;
static gint hf_ipmi_trn_lan63_req_max_rt = -1;
static gint hf_ipmi_trn_lan63_req_max_rc = -1;
static gint hf_ipmi_trn_lan63_cnf_max_delay = -1;
static gint hf_ipmi_trn_lan63_cnf_timeout = -1;
static gint hf_ipmi_trn_lan63_cnf_max_rt = -1;
static gint hf_ipmi_trn_lan63_cnf_max_rd = -1;
static gint hf_ipmi_trn_lan63_ren_timeout = -1;
static gint hf_ipmi_trn_lan63_ren_max_rt = -1;
static gint hf_ipmi_trn_lan63_reb_timeout = -1;
static gint hf_ipmi_trn_lan63_reb_max_rt = -1;
static gint hf_ipmi_trn_lan63_inf_max_delay = -1;
static gint hf_ipmi_trn_lan63_inf_timeout = -1;
static gint hf_ipmi_trn_lan63_inf_max_rt = -1;
static gint hf_ipmi_trn_lan63_rel_timeout = -1;
static gint hf_ipmi_trn_lan63_rel_max_rc = -1;
static gint hf_ipmi_trn_lan63_dec_timeout = -1;
static gint hf_ipmi_trn_lan63_dec_max_rc = -1;
static gint hf_ipmi_trn_lan63_hop_count_limit = -1;

static gint hf_ipmi_trn_lan64_static_cfg = -1;
static gint hf_ipmi_trn_lan64_dynamic_cfg = -1;

static gint hf_ipmi_trn_lanXX_router_selector = -1;
static gint hf_ipmi_trn_lanXX_router_mac = -1;
static gint hf_ipmi_trn_lanXX_router_prefix = -1;

static gint hf_ipmi_trn_lan73_num_dynamic_sets = -1;

static gint hf_ipmi_trn_lan80_max_rtr_solicitation_delay = -1;
static gint hf_ipmi_trn_lan80_rtr_solicitation_interval = -1;
static gint hf_ipmi_trn_lan80_max_rtr_solicitations = -1;
static gint hf_ipmi_trn_lan80_dup_addr_detect_transmits = -1;
static gint hf_ipmi_trn_lan80_max_multicast_solicit = -1;
static gint hf_ipmi_trn_lan80_max_unicast_solicit = -1;
static gint hf_ipmi_trn_lan80_max_anycast_delay_time = -1;
static gint hf_ipmi_trn_lan80_max_neighbor_advertisement = -1;
static gint hf_ipmi_trn_lan80_reachable_time = -1;
static gint hf_ipmi_trn_lan80_retrans_timer = -1;
static gint hf_ipmi_trn_lan80_delay_first_probe_time = -1;
static gint hf_ipmi_trn_lan80_max_random_factor = -1;
static gint hf_ipmi_trn_lan80_min_random_factor = -1;

static gint hf_ipmi_trn_serial03_connmode = -1;
static gint hf_ipmi_trn_serial03_terminal = -1;
static gint hf_ipmi_trn_serial03_ppp = -1;
static gint hf_ipmi_trn_serial03_basic = -1;

static gint hf_ipmi_trn_serial04_timeout = -1;

static gint hf_ipmi_trn_serial05_cbcp_callback = -1;
static gint hf_ipmi_trn_serial05_ipmi_callback = -1;
static gint hf_ipmi_trn_serial05_cb_list = -1;
static gint hf_ipmi_trn_serial05_cb_user = -1;
static gint hf_ipmi_trn_serial05_cb_prespec = -1;
static gint hf_ipmi_trn_serial05_no_cb = -1;
static gint hf_ipmi_trn_serial05_cb_dest1 = -1;
static gint hf_ipmi_trn_serial05_cb_dest2 = -1;
static gint hf_ipmi_trn_serial05_cb_dest3 = -1;

static gint hf_ipmi_trn_serial06_inactivity = -1;
static gint hf_ipmi_trn_serial06_dcd = -1;

static gint hf_ipmi_trn_serial07_flowctl = -1;
static gint hf_ipmi_trn_serial07_dtrhangup = -1;
static gint hf_ipmi_trn_serial07_bitrate = -1;

static gint hf_ipmi_trn_serial08_esc_powerup = -1;
static gint hf_ipmi_trn_serial08_esc_reset = -1;
static gint hf_ipmi_trn_serial08_switch_authcap = -1;
static gint hf_ipmi_trn_serial08_switch_rmcp = -1;
static gint hf_ipmi_trn_serial08_esc_switch1 = -1;
static gint hf_ipmi_trn_serial08_esc_switch2 = -1;
static gint hf_ipmi_trn_serial08_switch_dcdloss = -1;
static gint hf_ipmi_trn_serial08_sharing = -1;
static gint hf_ipmi_trn_serial08_ping_callback = -1;
static gint hf_ipmi_trn_serial08_ping_direct = -1;
static gint hf_ipmi_trn_serial08_ping_retry = -1;

static gint hf_ipmi_trn_serial09_ring_duration = -1;
static gint hf_ipmi_trn_serial09_ring_dead = -1;

static gint hf_ipmi_trn_serial10_set_sel = -1;
static gint hf_ipmi_trn_serial10_init_str = -1;
static gint hf_ipmi_trn_serial11_esc_seq = -1;
static gint hf_ipmi_trn_serial12_hangup_seq = -1;
static gint hf_ipmi_trn_serial13_dial_cmd = -1;
static gint hf_ipmi_trn_serial14_page_blackout = -1;
static gint hf_ipmi_trn_serial15_comm_string = -1;

static gint hf_ipmi_trn_serial16_ndest = -1;

static gint hf_ipmi_trn_serial17_dest_sel = -1;
static gint hf_ipmi_trn_serial17_ack = -1;
static gint hf_ipmi_trn_serial17_dest_type = -1;
/* static gint hf_ipmi_trn_serial17_ack_timeout = -1; */
static gint hf_ipmi_trn_serial17_alert_retries = -1;
static gint hf_ipmi_trn_serial17_call_retries = -1;
static gint hf_ipmi_trn_serial17_alert_ack_timeout = -1;
static gint hf_ipmi_trn_serial17_dialstr_sel = -1;
static gint hf_ipmi_trn_serial17_tap_sel = -1;
static gint hf_ipmi_trn_serial17_ipaddr_sel = -1;
static gint hf_ipmi_trn_serial17_ppp_sel = -1;
static gint hf_ipmi_trn_serial17_unknown = -1;

static gint hf_ipmi_trn_serial18_call_retry = -1;

static gint hf_ipmi_trn_serial19_destsel = -1;
static gint hf_ipmi_trn_serial19_flowctl = -1;
static gint hf_ipmi_trn_serial19_dtrhangup = -1;
static gint hf_ipmi_trn_serial19_stopbits = -1;
static gint hf_ipmi_trn_serial19_charsize = -1;
static gint hf_ipmi_trn_serial19_parity = -1;
static gint hf_ipmi_trn_serial19_bitrate = -1;

static gint hf_ipmi_trn_serial20_num_dial_strings = -1;
static gint hf_ipmi_trn_serial21_dialsel = -1;
static gint hf_ipmi_trn_serial21_blockno = -1;
static gint hf_ipmi_trn_serial21_dialstr = -1;
static gint hf_ipmi_trn_serial22_num_ipaddrs = -1;
static gint hf_ipmi_trn_serial23_destsel = -1;
static gint hf_ipmi_trn_serial23_ipaddr = -1;
static gint hf_ipmi_trn_serial24_num_tap_accounts = -1;
static gint hf_ipmi_trn_serial25_tap_acct = -1;
static gint hf_ipmi_trn_serial25_dialstr_sel = -1;
static gint hf_ipmi_trn_serial25_tapsrv_sel = -1;
static gint hf_ipmi_trn_serial26_tap_acct = -1;
static gint hf_ipmi_trn_serial26_tap_passwd = -1;
static gint hf_ipmi_trn_serial27_tap_acct = -1;
static gint hf_ipmi_trn_serial27_tap_pager_id = -1;

static gint hf_ipmi_trn_serial28_tapsrv_sel = -1;
static gint hf_ipmi_trn_serial28_confirm = -1;
static gint hf_ipmi_trn_serial28_srvtype = -1;
static gint hf_ipmi_trn_serial28_ctrl_esc = -1;
static gint hf_ipmi_trn_serial28_t2 = -1;
static gint hf_ipmi_trn_serial28_t1 = -1;
static gint hf_ipmi_trn_serial28_t4 = -1;
static gint hf_ipmi_trn_serial28_t3 = -1;
static gint hf_ipmi_trn_serial28_t6 = -1;
static gint hf_ipmi_trn_serial28_t5 = -1;
static gint hf_ipmi_trn_serial28_n2 = -1;
static gint hf_ipmi_trn_serial28_n1 = -1;
static gint hf_ipmi_trn_serial28_n4 = -1;
static gint hf_ipmi_trn_serial28_n3 = -1;

static gint hf_ipmi_trn_serial29_op = -1;
static gint hf_ipmi_trn_serial29_lineedit = -1;
static gint hf_ipmi_trn_serial29_deletectl = -1;
static gint hf_ipmi_trn_serial29_echo = -1;
static gint hf_ipmi_trn_serial29_handshake = -1;
static gint hf_ipmi_trn_serial29_o_newline = -1;
static gint hf_ipmi_trn_serial29_i_newline = -1;
static gint hf_ipmi_trn_serial30_snooping = -1;
static gint hf_ipmi_trn_serial30_snoopctl = -1;
static gint hf_ipmi_trn_serial30_negot_ctl = -1;
static gint hf_ipmi_trn_serial30_use_xmit_accm = -1;
static gint hf_ipmi_trn_serial30_xmit_addr_comp = -1;
static gint hf_ipmi_trn_serial30_xmit_proto_comp = -1;
static gint hf_ipmi_trn_serial30_ipaddr = -1;
static gint hf_ipmi_trn_serial30_accm = -1;
static gint hf_ipmi_trn_serial30_addr_comp = -1;
static gint hf_ipmi_trn_serial30_proto_comp = -1;
static gint hf_ipmi_trn_serial31_port = -1;
static gint hf_ipmi_trn_serial32_port = -1;
static gint hf_ipmi_trn_serial33_auth_proto = -1;
static gint hf_ipmi_trn_serial34_chap_name = -1;

static gint hf_ipmi_trn_serial35_recv_accm = -1;
static gint hf_ipmi_trn_serial35_xmit_accm = -1;
static gint hf_ipmi_trn_serial36_snoop_accm = -1;
static gint hf_ipmi_trn_serial37_num_ppp = -1;
static gint hf_ipmi_trn_serial38_acct_sel = -1;
static gint hf_ipmi_trn_serial38_dialstr_sel = -1;
static gint hf_ipmi_trn_serial39_acct_sel = -1;
static gint hf_ipmi_trn_serial39_ipaddr = -1;
static gint hf_ipmi_trn_serial40_acct_sel = -1;
static gint hf_ipmi_trn_serial40_username = -1;
static gint hf_ipmi_trn_serial41_acct_sel = -1;
static gint hf_ipmi_trn_serial41_userdomain = -1;
static gint hf_ipmi_trn_serial42_acct_sel = -1;
static gint hf_ipmi_trn_serial42_userpass = -1;
static gint hf_ipmi_trn_serial43_acct_sel = -1;
static gint hf_ipmi_trn_serial43_auth_proto = -1;
static gint hf_ipmi_trn_serial44_acct_sel = -1;
static gint hf_ipmi_trn_serial44_hold_time = -1;

static gint hf_ipmi_trn_serial45_src_ipaddr = -1;
static gint hf_ipmi_trn_serial45_dst_ipaddr = -1;
static gint hf_ipmi_trn_serial46_tx_bufsize = -1;
static gint hf_ipmi_trn_serial47_rx_bufsize = -1;
static gint hf_ipmi_trn_serial48_ipaddr = -1;
static gint hf_ipmi_trn_serial49_blockno = -1;
static gint hf_ipmi_trn_serial49_dialstr = -1;
static gint hf_ipmi_trn_serial50_115200 = -1;
static gint hf_ipmi_trn_serial50_57600 = -1;
static gint hf_ipmi_trn_serial50_38400 = -1;
static gint hf_ipmi_trn_serial50_19200 = -1;
static gint hf_ipmi_trn_serial50_9600 = -1;

static gint hf_ipmi_trn_serial51_port_assoc_sel = -1;
static gint hf_ipmi_trn_serial51_ipmi_channel = -1;
static gint hf_ipmi_trn_serial51_conn_num = -1;
static gint hf_ipmi_trn_serial51_ipmi_sharing = -1;
static gint hf_ipmi_trn_serial51_ipmi_sol = -1;
static gint hf_ipmi_trn_serial51_chan_num = -1;
static gint hf_ipmi_trn_serial52_port_assoc_sel = -1;
static gint hf_ipmi_trn_serial52_conn_name = -1;
static gint hf_ipmi_trn_serial53_port_assoc_sel = -1;
static gint hf_ipmi_trn_serial53_chan_name = -1;

static gint hf_ipmi_trn_01_chan = -1;
static gint hf_ipmi_trn_01_param = -1;
static gint hf_ipmi_trn_01_param_data = -1;

static gint hf_ipmi_trn_02_getrev = -1;
static gint hf_ipmi_trn_02_chan = -1;
static gint hf_ipmi_trn_02_param = -1;
static gint hf_ipmi_trn_02_set = -1;
static gint hf_ipmi_trn_02_block = -1;
static gint hf_ipmi_trn_02_rev_present = -1;
static gint hf_ipmi_trn_02_rev_compat = -1;
static gint hf_ipmi_trn_02_param_data = -1;

static gint hf_ipmi_trn_03_chan = -1;
static gint hf_ipmi_trn_03_arp_resp = -1;
static gint hf_ipmi_trn_03_gratuitous_arp = -1;
static gint hf_ipmi_trn_03_status_arp_resp = -1;
static gint hf_ipmi_trn_03_status_gratuitous_arp = -1;

static gint hf_ipmi_trn_04_chan = -1;
static gint hf_ipmi_trn_04_clear = -1;
static gint hf_ipmi_trn_04_rx_ippkts = -1;
static gint hf_ipmi_trn_04_rx_iphdr_err = -1;
static gint hf_ipmi_trn_04_rx_ipaddr_err = -1;
static gint hf_ipmi_trn_04_rx_ippkts_frag = -1;
static gint hf_ipmi_trn_04_tx_ippkts = -1;
static gint hf_ipmi_trn_04_rx_udppkts = -1;
static gint hf_ipmi_trn_04_rx_validrmcp = -1;
static gint hf_ipmi_trn_04_rx_udpproxy = -1;
static gint hf_ipmi_trn_04_dr_udpproxy = -1;

static gint hf_ipmi_trn_10_chan = -1;
static gint hf_ipmi_trn_10_param = -1;
static gint hf_ipmi_trn_10_param_data = -1;

static gint hf_ipmi_trn_11_getrev = -1;
static gint hf_ipmi_trn_11_chan = -1;
static gint hf_ipmi_trn_11_param = -1;
static gint hf_ipmi_trn_11_set = -1;
static gint hf_ipmi_trn_11_block = -1;
static gint hf_ipmi_trn_11_rev_present = -1;
static gint hf_ipmi_trn_11_rev_compat = -1;
static gint hf_ipmi_trn_11_param_data = -1;

static gint hf_ipmi_trn_12_chan = -1;
static gint hf_ipmi_trn_12_mux_setting = -1;
static gint hf_ipmi_trn_12_sw_to_sys = -1;
static gint hf_ipmi_trn_12_sw_to_bmc = -1;
static gint hf_ipmi_trn_12_alert = -1;
static gint hf_ipmi_trn_12_msg = -1;
static gint hf_ipmi_trn_12_req = -1;
static gint hf_ipmi_trn_12_mux_state = -1;

static gint hf_ipmi_trn_13_chan = -1;
static gint hf_ipmi_trn_13_code1 = -1;
static gint hf_ipmi_trn_13_code2 = -1;
static gint hf_ipmi_trn_13_code3 = -1;
static gint hf_ipmi_trn_13_code4 = -1;
static gint hf_ipmi_trn_13_code5 = -1;

static gint hf_ipmi_trn_14_chan = -1;
static gint hf_ipmi_trn_14_block = -1;
static gint hf_ipmi_trn_14_data = -1;

static gint hf_ipmi_trn_15_chan = -1;
static gint hf_ipmi_trn_15_block = -1;
static gint hf_ipmi_trn_15_data = -1;

static gint hf_ipmi_trn_16_chan = -1;
static gint hf_ipmi_trn_16_src_port = -1;
static gint hf_ipmi_trn_16_dst_port = -1;
static gint hf_ipmi_trn_16_src_addr = -1;
static gint hf_ipmi_trn_16_dst_addr = -1;
static gint hf_ipmi_trn_16_bytes = -1;

static gint hf_ipmi_trn_17_chan = -1;
static gint hf_ipmi_trn_17_clear = -1;
static gint hf_ipmi_trn_17_block_num = -1;
static gint hf_ipmi_trn_17_size = -1;
static gint hf_ipmi_trn_17_data = -1;

static gint hf_ipmi_trn_18_state = -1;
static gint hf_ipmi_trn_18_ipmi_ver = -1;

static gint hf_ipmi_trn_19_chan = -1;
static gint hf_ipmi_trn_19_dest_sel = -1;

static gint hf_ipmi_trn_XX_cap_cbcp = -1;
static gint hf_ipmi_trn_XX_cap_ipmi = -1;
static gint hf_ipmi_trn_XX_cbcp_from_list = -1;
static gint hf_ipmi_trn_XX_cbcp_user = -1;
static gint hf_ipmi_trn_XX_cbcp_prespec = -1;
static gint hf_ipmi_trn_XX_cbcp_nocb = -1;
static gint hf_ipmi_trn_XX_dst1 = -1;
static gint hf_ipmi_trn_XX_dst2 = -1;
static gint hf_ipmi_trn_XX_dst3 = -1;

static gint hf_ipmi_trn_1a_user = -1;
static gint hf_ipmi_trn_1a_chan = -1;

static gint hf_ipmi_trn_1b_user = -1;
static gint hf_ipmi_trn_1b_chan = -1;

static expert_field ei_ipmi_trn_02_request_param_rev = EI_INIT;
static expert_field ei_ipmi_trn_02_request_param_data = EI_INIT;
static expert_field ei_ipmi_trn_11_request_param_rev = EI_INIT;
static expert_field ei_ipmi_trn_11_request_param_data = EI_INIT;

static const value_string lan00_sip_vals[] = {
	{ 0x00, "Set complete" },
	{ 0x01, "Set in progress" },
	{ 0x02, "Commit write" },
	{ 0x03, "Reserved" },
	{ 0, NULL }
};

static const value_string lan04_ipsrc_vals[] = {
	{ 0x00, "Unspecified" },
	{ 0x01, "Static address (manually configured)" },
	{ 0x02, "Address obtained by BMC running DHCP" },
	{ 0x03, "Address loaded by BIOS or system software" },
	{ 0x04, "Address obtained by BMC running other address assignment protocol" },
	{ 0, NULL }
};

static const struct true_false_string lan18_ack_tfs = {
	"Acknowledged", "Unacknowledged"
};

static const value_string lan18_dst_type_vals[] = {
	{ 0x00, "PET Trap destination" },
	{ 0x06, "OEM 1" },
	{ 0x07, "OEM 2" },
	{ 0, NULL }
};

static const value_string lan19_af_vals[] = {
	{ 0x00, "IPv4 Address followed by Ethernet/802.3 MAC Address" },
	{ 0x01, "IPv6 Address" },
	{ 0, NULL }
};

static const struct true_false_string lan19_gw_sel_tfs = {
	"Use backup gateway", "Use default gateway"
};

static const struct true_false_string lan20_enable_tfs = {
	"Enabled", "Disabled"
};

static const value_string lan24_priv_vals[] = {
	{ 0x00, "Unspecified" },
	{ 0x01, "Callback" },
	{ 0x02, "User" },
	{ 0x03, "Operator" },
	{ 0x04, "Administrator" },
	{ 0x05, "OEM" },
	{ 0, NULL }
};

static const value_string lan25_af_vals[] = {
	{ 0x00, "VLAN ID not used" },
	{ 0x01, "802.1q VLAN TAG" },
	{ 0, NULL }
};

static const value_string lan51_enables[] = {
	{ 0, "IPv6 addressing disabled" },
	{ 1, "Enable IPv6 addressing only. IPv5 addressing is disabled" },
	{ 2, "Enable IPv6 and IPv4 addressing simultaneously" },
	{ 0, NULL }
};

static const value_string lanXX_addr_type[] = {
	{ 0, "Static" },
	{ 1, "SLAAC" },
	{ 2, "DHCPv6" },
	{ 0, NULL }
};

static const value_string lanXX_addr_status[] = {
	{ 0, "Active (in-use)" },
	{ 1, "Disabled" },
	{ 2, "Pending" },
	{ 3, "Failed" },
	{ 4, "Deprecated" },
	{ 5, "Invalid" },
	{ 0, NULL }
};

static const value_string lanXX_timing_support[] = {
	{ 0, "Not supported" },
	{ 1, "Global" },
	{ 2, "Per interface" },
	{ 0, NULL }
};

static const value_string serialXX_flowctl_vals[] = {
	{ 0x00, "No flow control" },
	{ 0x01, "RTS/CTS flow control" },
	{ 0x02, "XON/XOFF flow control" },
	{ 0x03, "Reserved" },
	{ 0, NULL }
};

static const value_string serialXX_bitrate_vals[] = {
	{ 0x06, "9600 bps" },
	{ 0x07, "19.2 kbps" },
	{ 0x08, "38.4 kbps" },
	{ 0x09, "57.6 kbps" },
	{ 0x0A, "115.2 kbps" },
	{ 0, NULL }
};

static const struct true_false_string serial03_connmode_tfs = {
	"Direct Connect", "Modem Connect"
};

static const value_string serial17_dest_type_vals[] = {
	{ 0x00, "Dial Page" },
	{ 0x01, "TAP Page" },
	{ 0x02, "PPP Alert" },
	{ 0x03, "Basic Mode Callback" },
	{ 0x04, "PPP Mode Callback" },
	{ 0x0e, "OEM 1" },
	{ 0x0f, "OEM 2" },
	{ 0, NULL }
};

static const struct true_false_string serial19_stopbits_tfs = {
	"2 stop bits", "1 stop bit"
};

static const struct true_false_string serial19_charsize_tfs = {
	"7-bit", "8-bit"
};

static const value_string serial19_parity_vals[] = {
	{ 0x00, "No" },
	{ 0x01, "Odd" },
	{ 0x02, "Even" },
	{ 0, NULL }
};

static const value_string serial28_confirm_vals[] = {
	{ 0x00, "ACK received after end-of-transaction only" },
	{ 0x01, "Code 211 and ACK received after ETX" },
	{ 0x02, "Code 211 or 213, and ACK received after ETX" },
	{ 0, NULL }
};

static const value_string serial29_op_vals[] = {
	{ 0x00, "Set volatile settings" },
	{ 0x01, "Set non-volatile settings" },
	{ 0x02, "Restore default" },
	{ 0, NULL }
};

static const value_string serial29_delete_vals[] = {
	{ 0x00, "<del>" },
	{ 0x01, "<bksp><sp><bksp>" },
	{ 0, NULL }
};

static const value_string serial29_o_nl_vals[] = {
	{ 0x00, "None" },
	{ 0x01, "<CR><LF>" },
	{ 0x02, "<NUL>" },
	{ 0x03, "<CR>" },
	{ 0x04, "<LF><CR>" },
	{ 0x05, "<LF>" },
	{ 0, NULL }
};

static const value_string serial29_i_nl_vals[] = {
	{ 0x01, "<CR>" },
	{ 0x02, "<NUL>" },
	{ 0, NULL }
};

static const value_string serial30_snoopctl_vals[] = {
	{ 0x00, "BMC uses Transmit ACCM" },
	{ 0x01, "BMC uses Snoop ACCM" },
	{ 0, NULL }
};

static const value_string serial30_negoctl_vals[] = {
	{ 0x00, "On initial connection and mux switch" },
	{ 0x01, "On initial connection" },
	{ 0x02, "Never" },
	{ 0, NULL }
};

static const struct true_false_string serial30_filter_tfs = {
	"Using Transmit ACCM", "Assuming all control chars escaped"
};

static const value_string serial30_ipaddr_val[] = {
	{ 0x00, "Request IP Address" },
	{ 0x01, "Request Fixed IP Address" },
	{ 0x02, "No Negotiation" },
	{ 0, NULL }
};

static const value_string serialXX_proto_vals[] = {
	{ 0x00, "None" },
	{ 0x01, "CHAP" },
	{ 0x02, "PAP" },
	{ 0x03, "MS-CHAP v1, Windows NT" },
	{ 0x04, "MS-CHAP v1, Lan Manager" },
	{ 0x05, "MS-CHAP v2" },
	{ 0, NULL }
};

static const struct true_false_string tfs_03_suspend = {
	"Suspend", "Do not suspend"
};

static const struct true_false_string tfs_03_arp_status = {
	"Occurring", "Suspended"
};

static const struct true_false_string tfs_04_clear = {
	"Clear", "Do not clear"
};

static const value_string vals_12_mux[] = {
	{ 0x00, "Get present status" },
	{ 0x01, "Request switch to system" },
	{ 0x02, "Request switch to BMC" },
	{ 0x03, "Force switch to system" },
	{ 0x04, "Force switch to BMC" },
	{ 0x05, "Block requests to switch to system" },
	{ 0x06, "Allow requests to switch to system" },
	{ 0x07, "Block requests to switch to BMC" },
	{ 0x08, "Allow requests to switch to BMC" },
	{ 0, NULL }
};

static const struct true_false_string tfs_12_blocked = {
	"blocked", "allowed"
};

static const struct true_false_string tfs_12_req = {
	"accepted/forced", "rejected"
};

static const struct true_false_string tfs_12_mux_state = {
	"BMC", "system"
};

static const value_string vals_18_state[] = {
	{ 0x00, "No session active" },
	{ 0x01, "Session active (mux switched to BMC)" },
	{ 0x02, "Switching mux to system" },
	{ 0, NULL }
};

static int * const lanXX_authtypes_byte[] = { &hf_ipmi_trn_lanXX_oem, &hf_ipmi_trn_lanXX_passwd, &hf_ipmi_trn_lanXX_md5,
		&hf_ipmi_trn_lanXX_md2, &hf_ipmi_trn_lanXX_none, NULL };

static void
lan_serial_00(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_lan00_sip, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL, ett_ipmi_trn_lan00_byte1,
			byte1, ENC_LITTLE_ENDIAN, 0);
}

static void
lan_serial_01(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_bitmask_text(tree, tvb, 0, 1, "Authentication types supported: ",
			"No authentication types supported for this channel", ett_ipmi_trn_lan01_byte1,
			lanXX_authtypes_byte, ENC_LITTLE_ENDIAN, 0);
}

static void
lan_serial_02(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_bitmask_text(tree, tvb, 0, 1, "Authentication types for Callback level: ",
			"No authentication types enabled", ett_ipmi_trn_lan02_byte1,
			lanXX_authtypes_byte, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_bitmask_text(tree, tvb, 1, 1, "Authentication types for User level: ",
			"No authentication types enabled", ett_ipmi_trn_lan02_byte2,
			lanXX_authtypes_byte, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_bitmask_text(tree, tvb, 2, 1, "Authentication types for Operator level: ",
			"No authentication types enabled", ett_ipmi_trn_lan02_byte3,
			lanXX_authtypes_byte, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_bitmask_text(tree, tvb, 3, 1, "Authentication types for Administrator level: ",
			"No authentication types enabled", ett_ipmi_trn_lan02_byte4,
			lanXX_authtypes_byte, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_bitmask_text(tree, tvb, 4, 1, "Authentication types for OEM level: ",
			"No authentication types enabled", ett_ipmi_trn_lan02_byte5,
			lanXX_authtypes_byte, ENC_LITTLE_ENDIAN, 0);
}

static void
lan_03(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_lan03_ip, tvb, 0, 4, ENC_BIG_ENDIAN);
}

static void
lan_04(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_lan04_ipsrc, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL, ett_ipmi_trn_lan04_byte1,
			byte1, ENC_LITTLE_ENDIAN, 0);
}

static void
lan_05(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_lan05_ether, tvb, 0, 6, ENC_NA);
}

static void
lan_06(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_lan06_subnet, tvb, 0, 4, ENC_BIG_ENDIAN);
}

static void
lan_07(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte2[] = { &hf_ipmi_trn_lan07_flags, NULL };
	static int * const byte3[] = { &hf_ipmi_trn_lan07_precedence, &hf_ipmi_trn_lan07_tos, NULL };

	proto_tree_add_item(tree, hf_ipmi_trn_lan07_ttl, tvb, 0, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_bitmask_text(tree, tvb, 1, 1, NULL, NULL, ett_ipmi_trn_lan07_byte2, byte2, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_bitmask_text(tree, tvb, 2, 1, NULL, NULL, ett_ipmi_trn_lan07_byte3, byte3, ENC_LITTLE_ENDIAN, 0);
}

static void
lan_08(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_lan08_rmcp_port, tvb, 0, 2, ENC_LITTLE_ENDIAN);
}

static void
lan_09(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_lan09_rmcp_port, tvb, 0, 2, ENC_LITTLE_ENDIAN);
}

static void
lan_10(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_lan10_responses, &hf_ipmi_trn_lan10_gratuitous, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL, ett_ipmi_trn_lan10_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
}

static void
lan_11(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_lan11_arp_interval, tvb, 0, 1, ENC_LITTLE_ENDIAN);
}

static void
lan_12(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_lan12_def_gw_ip, tvb, 0, 4, ENC_BIG_ENDIAN);
}

static void
lan_13(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_lan13_def_gw_mac, tvb, 0, 6, ENC_NA);
}

static void
lan_14(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_lan14_bkp_gw_ip, tvb, 0, 4, ENC_BIG_ENDIAN);
}

static void
lan_15(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_lan15_bkp_gw_mac, tvb, 0, 6, ENC_NA);
}

static void
lan_16(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_lan16_comm_string, tvb, 0, 18, ENC_ASCII|ENC_NA);
}

static void
lan_17(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_lan17_num_dst, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL, ett_ipmi_trn_lan17_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
}

static void
lan_18(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_lan18_dst_selector, NULL };
	static int * const byte2[] = { &hf_ipmi_trn_lan18_ack, &hf_ipmi_trn_lan18_dst_type, NULL };
	static int * const byte4[] = { &hf_ipmi_trn_lan18_retries, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL, ett_ipmi_trn_lan18_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_bitmask_text(tree, tvb, 1, 1, NULL, NULL, ett_ipmi_trn_lan18_byte2, byte2, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_item(tree, hf_ipmi_trn_lan18_tout, tvb, 2, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_bitmask_text(tree, tvb, 1, 1, NULL, NULL, ett_ipmi_trn_lan18_byte4, byte4, ENC_LITTLE_ENDIAN, 0);
}

static void
lan_19(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_lan19_dst_selector, NULL };
	static int * const byte2[] = { &hf_ipmi_trn_lan19_addr_format, NULL };
	static int * const byte3[] = { &hf_ipmi_trn_lan19_gw_sel, NULL };
	guint8 v;

	v = tvb_get_guint8(tvb, 1) >> 4;
	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL, ett_ipmi_trn_lan19_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_bitmask_text(tree, tvb, 1, 1, NULL, NULL, ett_ipmi_trn_lan19_byte2, byte2, ENC_LITTLE_ENDIAN, 0);

	if (v == 0) {
		proto_tree_add_bitmask_text(tree, tvb, 2, 1, NULL, NULL, ett_ipmi_trn_lan19_byte3, byte3, ENC_LITTLE_ENDIAN, 0);
		proto_tree_add_item(tree, hf_ipmi_trn_lan19_ip, tvb, 3, 4, ENC_BIG_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan19_mac, tvb, 7, 6, ENC_NA);
		return;
	} else if (v == 1) {
		proto_tree_add_item(tree, hf_ipmi_trn_lanXX_addr, tvb, 2, 16, ENC_NA);
		return;
	}

	proto_tree_add_item(tree, hf_ipmi_trn_lan19_address, tvb, 2, -1, ENC_NA);
}

static void
lan_20(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte12[] = { &hf_ipmi_trn_lan20_vlan_id_enable, &hf_ipmi_trn_lan20_vlan_id, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 2, NULL, NULL, ett_ipmi_trn_lan20_byte12, byte12, ENC_LITTLE_ENDIAN, 0);
}

static void
lan_21(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_lan21_vlan_prio, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL, ett_ipmi_trn_lan21_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
}

static void
lan_22(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_lan22_num_cs_entries, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL, ett_ipmi_trn_lan22_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
}

static void
lan_23(tvbuff_t *tvb, proto_tree *tree)
{
	guint i;
	guint8 v;

	for (i = 0; i < 16; i++) {
		v = tvb_get_guint8(tvb, i + 1);
		proto_tree_add_uint_format(tree, hf_ipmi_trn_lan23_cs_entry, tvb, i + 1, 1,
				v, "Cipher Suite ID entry %c: %u", 'A' + i, v);
	}
}

static void
lan_24(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const ett[] = { &ett_ipmi_trn_lan24_byte1, &ett_ipmi_trn_lan24_byte2, &ett_ipmi_trn_lan24_byte3,
		&ett_ipmi_trn_lan24_byte4, &ett_ipmi_trn_lan24_byte5, &ett_ipmi_trn_lan24_byte6, &ett_ipmi_trn_lan24_byte7,
		&ett_ipmi_trn_lan24_byte8 };
	proto_tree *s_tree;
	guint i;
	guint8 v, v1, v2;

	for (i = 0; i < 8; i++) {
		v = tvb_get_guint8(tvb, i + 1);
		v1 = v & 0x0f;
		v2 = v >> 4;
		s_tree = proto_tree_add_subtree_format(tree, tvb, i + 1, 1,
				*ett[i], NULL, "Cipher Suite #%d: %s (0x%02x), Cipher Suite #%d: %s (0x%02x)",
				i * 2 + 1, val_to_str_const(v1, lan24_priv_vals, "Reserved"), v1,
				i * 2 + 2, val_to_str_const(v2, lan24_priv_vals, "Reserved"), v2);
		proto_tree_add_uint_format_value(s_tree, hf_ipmi_trn_lan24_priv1, tvb, i + 1, 1,
				v2 << 4, " #%d: %s (0x%02x)", i * 2 + 2, val_to_str_const(v2, lan24_priv_vals, "Reserved"), v2);
		proto_tree_add_uint_format_value(s_tree, hf_ipmi_trn_lan24_priv2, tvb, i + 1, 1,
				v1, " #%d: %s (0x%02x)", i * 2 + 1, val_to_str_const(v1, lan24_priv_vals, "Reserved"), v1);
	}
}

static void
lan_25(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_lan25_dst_selector, NULL };
	static int * const byte2[] = { &hf_ipmi_trn_lan25_addr_format, NULL };
	static int * const byte34[] = { &hf_ipmi_trn_lan25_uprio, &hf_ipmi_trn_lan25_cfi, &hf_ipmi_trn_lan25_vlan_id, NULL };
	guint8 v;

	v = tvb_get_guint8(tvb, 1) >> 4;
	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL, ett_ipmi_trn_lan25_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_bitmask_text(tree, tvb, 1, 1, NULL, NULL, ett_ipmi_trn_lan25_byte2, byte2, ENC_LITTLE_ENDIAN, 0);
	switch (v) {
		case 0:
			break;
		case 1:
			proto_tree_add_bitmask_text(tree, tvb, 2, 2, NULL, NULL, ett_ipmi_trn_lan25_byte34,
					byte34, ENC_LITTLE_ENDIAN, 0);
			break;
		default:
			proto_tree_add_item(tree, hf_ipmi_trn_lan25_address, tvb, 2, -1, ENC_LITTLE_ENDIAN);
			break;
	}
}

static void
lan_26(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_lan26_gen_event, tvb, 0, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_lan26_thresh_number, tvb, 1, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_lan26_reset_interval, tvb, 2, 2, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_lan26_lock_interval, tvb, 4, 2, ENC_LITTLE_ENDIAN);
}

static void
lan_50(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_lan50_ipv6_only,
			&hf_ipmi_trn_lan50_both_ipv4_ipv6,
			&hf_ipmi_trn_lan50_ipv6_alerting, NULL };
	proto_tree_add_bitmask_text(tree, tvb, 0, 1, "Data 1",  NULL, ett_ipmi_trn_lan50_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
}

static void
lan_51(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_lan51_enables, tvb, 0, 1, ENC_LITTLE_ENDIAN);
}

static void
lan_52(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_lan52_traffic_class, tvb, 0, 1, ENC_LITTLE_ENDIAN);
}

static void
lan_53_78(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_hop_limit, tvb, 0, 1, ENC_LITTLE_ENDIAN);
}

static void
lan_54(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_lan54_flow_label, tvb, 0, 3, ENC_BIG_ENDIAN);
}

static void
lan_55(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte3[] = { &hf_ipmi_trn_lan55_dhcpv6_support,
			&hf_ipmi_trn_lan55_slaac_support, NULL };
	proto_tree_add_item(tree, hf_ipmi_trn_lan55_static_addr_max, tvb, 0, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_lan55_dynamic_addr_max, tvb, 1, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_bitmask_text(tree, tvb, 2, 1, NULL,  NULL, ett_ipmi_trn_lan55_byte3, byte3, ENC_LITTLE_ENDIAN, 0);
}

static void
lan_56(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte2[] = { &hf_ipmi_trn_lanXX_addr_type,
			&hf_ipmi_trn_lanXX_addr_enable, NULL };
	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_addr_selector, tvb, 0, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_bitmask_text(tree, tvb, 1, 1, NULL,  NULL, ett_ipmi_trn_lan56_byte2, byte2, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_addr, tvb, 2, 16, ENC_NA);
	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_prefix_len, tvb, 18, 1, ENC_LITTLE_ENDIAN);
	if (tvb_captured_length(tvb) > 19) {
		proto_tree_add_item(tree, hf_ipmi_trn_lanXX_addr_status, tvb, 19, 1, ENC_LITTLE_ENDIAN);
	}
}

static void
lan_57_60(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_max_duid_blocks, tvb, 0, 1, ENC_LITTLE_ENDIAN);
}

static void
lan_58_61(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_duid_selector, tvb, 0, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_block_selector, tvb, 1, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_duid, tvb, 2, -1, ENC_NA);
}

static void
lan_59(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_addr_selector, tvb, 0, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_addr_type, tvb, 1, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_addr, tvb, 2, 16, ENC_NA);
	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_prefix_len, tvb, 18, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_addr_status, tvb, 19, 1, ENC_LITTLE_ENDIAN);
}

static void
lan_62_79(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_timing_support, tvb, 0, 1, ENC_LITTLE_ENDIAN);
}

static void
lan_63(tvbuff_t *tvb, proto_tree *tree)
{
	guint8 v;

	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_iface_selector, tvb, 0, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_block_selector, tvb, 1, 1, ENC_LITTLE_ENDIAN);

	v = tvb_get_guint8(tvb, 1);
	if (v == 0) {
		proto_tree_add_item(tree, hf_ipmi_trn_lan63_sol_max_delay, tvb, 2, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan63_sol_timeout, tvb, 3, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan63_sol_max_rt, tvb, 4, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan63_req_timeout, tvb, 5, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan63_req_max_rt, tvb, 6, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan63_req_max_rc, tvb, 7, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan63_cnf_max_delay, tvb, 8, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan63_cnf_timeout, tvb, 9, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan63_cnf_max_rt, tvb, 10, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan63_cnf_max_rd, tvb, 11, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan63_ren_timeout, tvb, 12, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan63_ren_max_rt, tvb, 13, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan63_reb_timeout, tvb, 14, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan63_reb_max_rt, tvb, 15, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan63_inf_max_delay, tvb, 16, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan63_inf_timeout, tvb, 17, 1, ENC_LITTLE_ENDIAN);
	} else if (v == 1) {
		proto_tree_add_item(tree, hf_ipmi_trn_lan63_inf_max_rt, tvb, 2, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan63_rel_timeout, tvb, 3, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan63_rel_max_rc, tvb, 4, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan63_dec_timeout, tvb, 5, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan63_dec_max_rc, tvb, 6, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan63_hop_count_limit, tvb, 7, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_01_param_data, tvb, 8, -1, ENC_NA);
	} else {
		proto_tree_add_item(tree, hf_ipmi_trn_01_param_data, tvb, 2, -1, ENC_NA);
	}
}

static void
lan_64(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_lan64_static_cfg,
			&hf_ipmi_trn_lan64_dynamic_cfg, NULL };
	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL,  NULL, ett_ipmi_trn_lan64_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
}

static void
lan_65_69(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_addr, tvb, 0, 16, ENC_NA);
}

static void
lan_66_70(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_router_mac, tvb, 0, 6, ENC_NA);
}

static void
lan_67_71(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_prefix_len, tvb, 0, 1, ENC_LITTLE_ENDIAN);
}

static void
lan_68_72(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_router_prefix, tvb, 0, 16, ENC_NA);
}

static void
lan_73(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_lan73_num_dynamic_sets, tvb, 0, 1, ENC_LITTLE_ENDIAN);
}

static void
lan_74(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_router_selector, tvb, 0, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_addr, tvb, 1, 16, ENC_NA);
}

static void
lan_75(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_router_selector, tvb, 0, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_router_mac, tvb, 1, 6, ENC_NA);
}

static void
lan_76(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_router_selector, tvb, 0, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_prefix_len, tvb, 1, 1, ENC_LITTLE_ENDIAN);
}

static void
lan_77(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_router_selector, tvb, 0, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_router_prefix, tvb, 1, 16, ENC_NA);
}

static void
lan_80(tvbuff_t *tvb, proto_tree *tree)
{
	guint8 v;

	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_iface_selector, tvb, 0, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_lanXX_block_selector, tvb, 1, 1, ENC_LITTLE_ENDIAN);

	v = tvb_get_guint8(tvb, 1);
	if (v == 0) {
		proto_tree_add_item(tree, hf_ipmi_trn_lan80_max_rtr_solicitation_delay, tvb, 2, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan80_rtr_solicitation_interval, tvb, 3, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan80_max_rtr_solicitations, tvb, 4, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan80_dup_addr_detect_transmits, tvb, 5, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan80_max_multicast_solicit, tvb, 6, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan80_max_unicast_solicit, tvb, 7, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan80_max_anycast_delay_time, tvb, 8, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan80_max_neighbor_advertisement, tvb, 9, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan80_reachable_time, tvb, 10, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan80_retrans_timer, tvb, 11, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan80_delay_first_probe_time, tvb, 12, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan80_max_random_factor, tvb, 13, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_lan80_min_random_factor, tvb, 14, 1, ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_ipmi_trn_01_param_data, tvb, 15, -1, ENC_NA);
	} else {
		proto_tree_add_item(tree, hf_ipmi_trn_01_param_data, tvb, 2, -1, ENC_NA);
	}
}

static struct {
	void (*intrp)(tvbuff_t *tvb, proto_tree *tree);
	const char *name;
} lan_options[] = {
	{ lan_serial_00, "Set In Progress" },
	{ lan_serial_01, "Authentication Type Support" },
	{ lan_serial_02, "Authentication Type Enables" },
	{ lan_03, "IP Address" },
	{ lan_04, "IP Address Source" },
	{ lan_05, "MAC Address" },
	{ lan_06, "Subnet Mask" },
	{ lan_07, "IPv4 Header Parameters" },
	{ lan_08, "Primary RMCP Port Number" },
	{ lan_09, "Secondary RMCP Port Number" },
	{ lan_10, "BMC-generated ARP Control" },
	{ lan_11, "Gratuitous ARP Interval" },
	{ lan_12, "Default Gateway Address" },
	{ lan_13, "Default Gateway MAC Address" },
	{ lan_14, "Backup Gateway Address" },
	{ lan_15, "Backup Gateway MAC Address" },
	{ lan_16, "Community String" },
	{ lan_17, "Number of Destinations" },
	{ lan_18, "Destination Type" },
	{ lan_19, "Destination Addresses" },
	{ lan_20, "VLAN ID (802.1q)" },
	{ lan_21, "VLAN Priority (802.1q)" },
	{ lan_22, "Cipher Suite Entry Support (RMCP+)" },
	{ lan_23, "Cipher Suite Entries (RMCP+)" },
	{ lan_24, "Cipher Suite Privilege Levels (RMCP+)" },
	{ lan_25, "Destination Address VLAN TAGs" },
	{ lan_26, "Bad Password Threshold" },
	{ NULL, "Reserved" },
	{ NULL, "Reserved" },
	{ NULL, "Reserved" },
	{ NULL, "Reserved" },
	{ NULL, "Reserved" },
	{ NULL, "Reserved" },
	{ NULL, "Reserved" },
	{ NULL, "Reserved" },
	{ NULL, "Reserved" },
	{ NULL, "Reserved" },
	{ NULL, "Reserved" },
	{ NULL, "Reserved" },
	{ NULL, "Reserved" },
	{ NULL, "Reserved" },
	{ NULL, "Reserved" },
	{ NULL, "Reserved" },
	{ NULL, "Reserved" },
	{ NULL, "Reserved" },
	{ NULL, "Reserved" },
	{ NULL, "Reserved" },
	{ NULL, "Reserved" },
	{ NULL, "Reserved" },
	{ NULL, "Reserved" },
	{ lan_50, "IPv6/IPv4 Support" },
	{ lan_51, "IPv6/IPv4 Addressing enables" },
	{ lan_52, "IPv6 Header Static Traffic Class" },
	{ lan_53_78, "IPv6 Header Static Hop Limit" },
	{ lan_54, "IPv6 Header Flow Label" },
	{ lan_55, "IPv6 Status" },
	{ lan_56, "IPv6 Static Addresses" },
	{ lan_57_60, "IPv6 DHCPv6 Static DUID storage length" },
	{ lan_58_61, "IPv6 DHCPv6 Static DUIDs" },
	{ lan_59, "IPv6 Dynamic Addresses" },
	{ lan_57_60, "IPv6 DHCPv6 Dynamic DUID storage length" },
	{ lan_58_61, "IPv6 DHCPv6 Dynamic DUIDs" },
	{ lan_62_79, "IPv6 DHCPv6 Timing Configuration Support" },
	{ lan_63, "IPv6 DHCPv6 Timing Configuration" },
	{ lan_64, "IPv6 Router Address Configuration Control" },
	{ lan_65_69, "IPv6 Static Router 1 IP Address" },
	{ lan_66_70, "IPv6 Static Router 1 MAC Address" },
	{ lan_67_71, "IPv6 Static Router 1 Prefix Length" },
	{ lan_68_72, "IPv6 Static Router 1 Prefix Value" },
	{ lan_65_69, "IPv6 Static Router 2 IP Address" },
	{ lan_66_70, "IPv6 Static Router 2 MAC Address" },
	{ lan_67_71, "IPv6 Static Router 2 Prefix Length" },
	{ lan_68_72, "IPv6 Static Router 2 Prefix Value" },
	{ lan_73, "Number of Dynamic Router Info Sets" },
	{ lan_74, "IPv6 Dynamic Router Info IP Address" },
	{ lan_75, "IPv6 Dynamic Router Info MAC Address" },
	{ lan_76, "IPv6 Dynamic Router Info Prefix Length" },
	{ lan_77, "IPv6 Dynamic Router Info Prefix Value" },
	{ lan_53_78, "IPv6 Dynamic Router Received Hop Limit" },
	{ lan_62_79, "IPv6 NDISC/SLAAC Timing Configuration Support" },
	{ lan_80, "IPv6 NDISC/SLAAC Timing Configuration" },
};

/* Set LAN Configuration Parameters
 */
static void
rq01(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_01_chan, NULL };
	tvbuff_t *next;
	const char *desc;
	guint8 pno;

	pno = tvb_get_guint8(tvb, 1);
	if (pno < array_length(lan_options)) {
		desc = lan_options[pno].name;
	} else if (pno >= 0xC0) {
		desc = "OEM";
	} else {
		desc = "Reserved";
	}

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL, ett_ipmi_trn_01_byte1,
			byte1, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_uint_format_value(tree, hf_ipmi_trn_01_param, tvb, 1, 1,
			pno, "%s (0x%02x)", desc, pno);
	if (pno < array_length(lan_options) && lan_options[pno].intrp) {
		next = tvb_new_subset_remaining(tvb, 2);
		lan_options[pno].intrp(next, tree);
	} else {
		proto_tree_add_item(tree, hf_ipmi_trn_01_param_data, tvb, 2, -1, ENC_NA);
	}
}

static const value_string cc01[] = {
	{ 0x80, "Parameter not supported" },
	{ 0x81, "Attempt to set the 'set in progress' value (in parameter #0) when not in the 'set complete' state" },
	{ 0x82, "Attempt to write read-only parameter" },
	{ 0, NULL }
};

/* Get LAN Configuration Parameters
 */
static void
rq02(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_02_getrev, &hf_ipmi_trn_02_chan, NULL };
	const char *desc;
	guint8 pno;

	pno = tvb_get_guint8(tvb, 1);

	ipmi_set_data(pinfo, 0, pno);
	ipmi_set_data(pinfo, 1, tvb_get_guint8(tvb, 0) & 0x80);

	if (!tree) {
		return;
	}

	if (pno < array_length(lan_options)) {
		desc = lan_options[pno].name;
	} else if (pno >= 0xC0) {
		desc = "OEM";
	} else {
		desc = "Reserved";
	}

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_02_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_uint_format_value(tree, hf_ipmi_trn_02_param, tvb, 1, 1,
			pno, "%s (0x%02x)", desc, pno);
	proto_tree_add_item(tree, hf_ipmi_trn_02_set, tvb, 2, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_02_block, tvb, 3, 1, ENC_LITTLE_ENDIAN);
}

static void
rs02(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_02_rev_present, &hf_ipmi_trn_02_rev_compat, NULL };
	proto_item *ti;
	proto_tree *subtree;
	tvbuff_t *next;
	const char *desc;
	guint32 pno, req;

	ti = proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_02_rev, byte1, ENC_LITTLE_ENDIAN, 0);

	if (!ipmi_get_data(pinfo, 0, &pno) || !ipmi_get_data(pinfo, 1, &req)) {
		/* No request found - cannot parse further */
		if (tvb_captured_length(tvb) > 1) {
			proto_tree_add_item(tree, hf_ipmi_trn_02_param_data, tvb, 1, -1, ENC_NA);
		};
		return;
	}

	if ((req & 0x80) && tvb_captured_length(tvb) > 1) {
		expert_add_info(pinfo, ti, &ei_ipmi_trn_02_request_param_rev);
	} else if (!(req & 0x80) && tvb_captured_length(tvb) == 1) {
		expert_add_info(pinfo, ti, &ei_ipmi_trn_02_request_param_data);
	}

	if (pno < array_length(lan_options)) {
		desc = lan_options[pno].name;
	} else if (pno >= 0xC0) {
		desc = "OEM";
	} else {
		desc = "Reserved";
	}

	subtree = proto_tree_add_subtree_format(tree, tvb, 0, 0, ett_ipmi_trn_parameter, NULL, "Parameter: %s", desc);

	if (tvb_captured_length(tvb) > 1) {
		if (pno < array_length(lan_options) && lan_options[pno].intrp) {
			next = tvb_new_subset_remaining(tvb, 1);
			lan_options[pno].intrp(next, subtree);
		} else {
			proto_tree_add_item(subtree, hf_ipmi_trn_02_param_data, tvb, 1, -1, ENC_NA);
		}
	}
}

static const value_string cc02[] = {
	{ 0x80, "Parameter not supported" },
	{ 0x83, "Attempt to read write-only parameter" },
	{ 0, NULL }
};

static void
rq03(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_03_chan, NULL };
	static int * const byte2[] = { &hf_ipmi_trn_03_arp_resp, &hf_ipmi_trn_03_gratuitous_arp, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_03_rq_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_bitmask_text(tree, tvb, 1, 1, NULL, NULL,
			ett_ipmi_trn_03_rq_byte2, byte2, ENC_LITTLE_ENDIAN, 0);
}

static void
rs03(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_03_status_arp_resp,
		&hf_ipmi_trn_03_status_gratuitous_arp, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_03_rs_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
}

static void
rq04(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_04_chan, NULL };
	static int * const byte2[] = { &hf_ipmi_trn_04_clear, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_04_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_bitmask_text(tree, tvb, 1, 1, NULL, NULL,
			ett_ipmi_trn_04_byte2, byte2, ENC_LITTLE_ENDIAN, 0);
}

static void
rs04(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_04_rx_ippkts, tvb, 0, 2, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_04_rx_iphdr_err, tvb, 2, 2, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_04_rx_ipaddr_err, tvb, 4, 2, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_04_rx_ippkts_frag, tvb, 6, 2, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_04_tx_ippkts, tvb, 8, 2, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_04_rx_udppkts, tvb, 10, 2, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_04_rx_validrmcp, tvb, 12, 2, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_04_rx_udpproxy, tvb, 14, 2, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_04_dr_udpproxy, tvb, 16, 2, ENC_LITTLE_ENDIAN);
}

static void
serial_03(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_serial03_connmode, &hf_ipmi_trn_serial03_terminal,
		&hf_ipmi_trn_serial03_ppp, &hf_ipmi_trn_serial03_basic, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_serial03_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
}

static void
serial04_timeout_fmt(gchar *s, guint32 v)
{
	if (v) {
		g_snprintf(s, ITEM_LABEL_LENGTH, "%d sec", 30 * v);
	}
	else {
		g_snprintf(s, ITEM_LABEL_LENGTH, "Does not timeout");
	}
}

static void
serial_04(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_serial04_timeout, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_serial04_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
}

static void
serial_05(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_serial05_cbcp_callback,
		&hf_ipmi_trn_serial05_ipmi_callback, NULL };
	static int * const byte2[] = { &hf_ipmi_trn_serial05_cb_list, &hf_ipmi_trn_serial05_cb_user,
		&hf_ipmi_trn_serial05_cb_prespec, &hf_ipmi_trn_serial05_no_cb, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, "Callback capabilities: ", "None",
			ett_ipmi_trn_serial05_byte1, byte1, ENC_LITTLE_ENDIAN, BMT_NO_TFS);
	proto_tree_add_bitmask_text(tree, tvb, 1, 1, "CBCP negotiation options: ", "None",
			ett_ipmi_trn_serial05_byte2, byte2, ENC_LITTLE_ENDIAN, BMT_NO_TFS);
	proto_tree_add_item(tree, hf_ipmi_trn_serial05_cb_dest1, tvb, 2, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_serial05_cb_dest2, tvb, 3, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_serial05_cb_dest3, tvb, 4, 1, ENC_LITTLE_ENDIAN);
}

static void
serial_06(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_serial06_inactivity,
		&hf_ipmi_trn_serial06_dcd, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_serial06_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
}

static void
serial_07(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_serial07_flowctl, &hf_ipmi_trn_serial07_dtrhangup, NULL };
	static int * const byte2[] = { &hf_ipmi_trn_serial07_bitrate, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_serial07_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_bitmask_text(tree, tvb, 1, 1, NULL, NULL,
			ett_ipmi_trn_serial07_byte2, byte2, ENC_LITTLE_ENDIAN, 0);
}

static void
serial_08(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_serial08_esc_powerup,
		&hf_ipmi_trn_serial08_esc_reset, &hf_ipmi_trn_serial08_switch_authcap,
		&hf_ipmi_trn_serial08_switch_rmcp, &hf_ipmi_trn_serial08_esc_switch1,
		&hf_ipmi_trn_serial08_esc_switch2, &hf_ipmi_trn_serial08_switch_dcdloss, NULL };
	static int * const byte2[] = { &hf_ipmi_trn_serial08_sharing,
		&hf_ipmi_trn_serial08_ping_callback, &hf_ipmi_trn_serial08_ping_direct,
		&hf_ipmi_trn_serial08_ping_retry, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, "Switch/escape settings", NULL,
			ett_ipmi_trn_serial08_byte1, byte1, ENC_LITTLE_ENDIAN, BMT_NO_APPEND);
	proto_tree_add_bitmask_text(tree, tvb, 1, 1, "Sharing/ping settings", NULL,
			ett_ipmi_trn_serial08_byte2, byte2, ENC_LITTLE_ENDIAN, BMT_NO_APPEND);
}

static void
serial_09(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_serial09_ring_duration, NULL };
	static int * const byte2[] = { &hf_ipmi_trn_serial09_ring_dead, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_serial09_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_bitmask_text(tree, tvb, 1, 1, NULL, NULL,
			ett_ipmi_trn_serial09_byte2, byte2, ENC_LITTLE_ENDIAN, 0);
}

static void
serial_10(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_serial10_set_sel, tvb, 0, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_serial10_init_str, tvb, 1, -1, ENC_ASCII|ENC_NA);
}

static void
serial_11(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_serial11_esc_seq, tvb, 0, 5, ENC_ASCII|ENC_NA);
}

static void
serial_12(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_serial12_hangup_seq, tvb, 0, 8, ENC_ASCII|ENC_NA);
}

static void
serial_13(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_serial13_dial_cmd, tvb, 0, 8, ENC_ASCII|ENC_NA);
}

static void
serial_14(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_serial14_page_blackout, tvb, 0, 1, ENC_LITTLE_ENDIAN);
}

static void
serial_15(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_serial15_comm_string, tvb, 0, 18, ENC_ASCII|ENC_NA);
}

static void
serial_16(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_serial16_ndest, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_serial16_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
}

static void
serial_17(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_serial17_dest_sel, NULL };
	static int * const byte2[] = { &hf_ipmi_trn_serial17_ack, &hf_ipmi_trn_serial17_dest_type, NULL };
	static int * const byte4[] = { &hf_ipmi_trn_serial17_alert_retries, &hf_ipmi_trn_serial17_call_retries, NULL };
	int * byte5[3] = { NULL, NULL, NULL };
	guint8 v;

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_serial17_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_bitmask_text(tree, tvb, 1, 1, NULL, NULL,
			ett_ipmi_trn_serial17_byte2, byte2, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_item(tree, hf_ipmi_trn_serial17_alert_ack_timeout, tvb, 2, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_bitmask_text(tree, tvb, 3, 1, NULL, NULL,
			ett_ipmi_trn_serial17_byte4, byte4, ENC_LITTLE_ENDIAN, 0);

	v = tvb_get_guint8(tvb, 1) & 0x0f;
	switch (v) {
		case 0: /* Dial Page */
		case 3: /* Basic Mode Callback */
			byte5[0] = &hf_ipmi_trn_serial17_dialstr_sel;
			break;
		case 1: /* TAP Page */
			byte5[0] = &hf_ipmi_trn_serial17_tap_sel;
			break;
		case 2: /* PPP Alert */
		case 4: /* PPP Callback */
			byte5[0] = &hf_ipmi_trn_serial17_ipaddr_sel;
			byte5[1] = &hf_ipmi_trn_serial17_ppp_sel;
			break;
		default:
			proto_tree_add_item(tree, hf_ipmi_trn_serial17_unknown, tvb, 4, 1, ENC_LITTLE_ENDIAN);
			return;
	}
	proto_tree_add_bitmask_text(tree, tvb, 4, 1, NULL, NULL,
			ett_ipmi_trn_serial17_byte5, byte5, ENC_LITTLE_ENDIAN, 0);
}

static void
serial_18(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_serial18_call_retry, tvb, 0, 1, ENC_LITTLE_ENDIAN);
}

static void
serial_19(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_serial19_destsel, NULL };
	static int * const byte2[] = { &hf_ipmi_trn_serial19_flowctl, &hf_ipmi_trn_serial19_dtrhangup,
		&hf_ipmi_trn_serial19_stopbits, &hf_ipmi_trn_serial19_charsize, &hf_ipmi_trn_serial19_parity, NULL };
	static int * const byte3[] = { &hf_ipmi_trn_serial19_bitrate, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_serial19_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_bitmask_text(tree, tvb, 1, 1, NULL, NULL,
			ett_ipmi_trn_serial19_byte2, byte2, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_bitmask_text(tree, tvb, 2, 1, NULL, NULL,
			ett_ipmi_trn_serial19_byte3, byte3, ENC_LITTLE_ENDIAN, 0);
}

static void
serial_20(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_serial20_num_dial_strings, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_serial20_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
}

static void
serial_21(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_serial21_dialsel, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_serial21_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_item(tree, hf_ipmi_trn_serial21_blockno, tvb, 1, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_serial21_dialstr, tvb, 2, 1, ENC_ASCII|ENC_NA);
}

static void
serial_22(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_serial22_num_ipaddrs, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_serial22_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
}

static void
serial_23(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_serial23_destsel, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_serial23_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_item(tree, hf_ipmi_trn_serial23_ipaddr, tvb, 1, 4, ENC_BIG_ENDIAN);
}

static void
serial_24(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_serial24_num_tap_accounts, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_serial24_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
}

static void
serial_25(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte2[] = { &hf_ipmi_trn_serial25_dialstr_sel, &hf_ipmi_trn_serial25_tapsrv_sel, NULL };

	proto_tree_add_item(tree, hf_ipmi_trn_serial25_tap_acct, tvb, 0, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_bitmask_text(tree, tvb, 1, 1, NULL, NULL,
			ett_ipmi_trn_serial25_byte2, byte2, ENC_LITTLE_ENDIAN, 0);
}

static void
serial_26(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_serial26_tap_acct, tvb, 0, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_serial26_tap_passwd, tvb, 1, 6, ENC_ASCII|ENC_NA);
}

static void
serial_27(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_serial27_tap_acct, tvb, 0, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_serial27_tap_pager_id, tvb, 1, 16, ENC_ASCII|ENC_NA);
}

static void
serial_28(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_serial28_tapsrv_sel, NULL };
	static int * const byte2[] = { &hf_ipmi_trn_serial28_confirm, NULL };
	static int * const byte10[] = { &hf_ipmi_trn_serial28_t2, &hf_ipmi_trn_serial28_t1, NULL };
	static int * const byte11[] = { &hf_ipmi_trn_serial28_t4, &hf_ipmi_trn_serial28_t3, NULL };
	static int * const byte12[] = { &hf_ipmi_trn_serial28_t6, &hf_ipmi_trn_serial28_t5, NULL };
	static int * const byte13[] = { &hf_ipmi_trn_serial28_n2, &hf_ipmi_trn_serial28_n1, NULL };
	static int * const byte14[] = { &hf_ipmi_trn_serial28_n4, &hf_ipmi_trn_serial28_n3, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_serial28_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_bitmask_text(tree, tvb, 1, 1, NULL, NULL,
			ett_ipmi_trn_serial28_byte2, byte2, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_item(tree, hf_ipmi_trn_serial28_srvtype, tvb, 2, 3, ENC_ASCII|ENC_NA);
	proto_tree_add_item(tree, hf_ipmi_trn_serial28_ctrl_esc, tvb, 5, 4, ENC_LITTLE_ENDIAN);
	proto_tree_add_bitmask_text(tree, tvb, 9, 1, NULL, NULL,
			ett_ipmi_trn_serial28_byte10, byte10, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_bitmask_text(tree, tvb, 10, 1, NULL, NULL,
			ett_ipmi_trn_serial28_byte11, byte11, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_bitmask_text(tree, tvb, 11, 1, NULL, NULL,
			ett_ipmi_trn_serial28_byte12, byte12, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_bitmask_text(tree, tvb, 12, 1, NULL, NULL,
			ett_ipmi_trn_serial28_byte13, byte13, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_bitmask_text(tree, tvb, 13, 1, NULL, NULL,
			ett_ipmi_trn_serial28_byte14, byte14, ENC_LITTLE_ENDIAN, 0);
}

static void
serial_29(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_serial29_op, &hf_ipmi_trn_serial29_lineedit,
		&hf_ipmi_trn_serial29_deletectl, &hf_ipmi_trn_serial29_echo, &hf_ipmi_trn_serial29_handshake, NULL };
	static int * const byte2[] = { &hf_ipmi_trn_serial29_o_newline, &hf_ipmi_trn_serial29_i_newline, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_serial29_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_bitmask_text(tree, tvb, 1, 1, NULL, NULL,
			ett_ipmi_trn_serial29_byte2, byte2, ENC_LITTLE_ENDIAN, 0);
}

static void
serial_30(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_serial30_snooping, &hf_ipmi_trn_serial30_snoopctl, NULL };
	static int * const byte2[] = { &hf_ipmi_trn_serial30_negot_ctl, &hf_ipmi_trn_serial30_use_xmit_accm,
		&hf_ipmi_trn_serial30_xmit_addr_comp, &hf_ipmi_trn_serial30_xmit_proto_comp, NULL };
	static int * const byte3[] = { &hf_ipmi_trn_serial30_ipaddr, &hf_ipmi_trn_serial30_accm,
		&hf_ipmi_trn_serial30_addr_comp, &hf_ipmi_trn_serial30_proto_comp, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_serial30_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_bitmask_text(tree, tvb, 1, 1, NULL, NULL,
			ett_ipmi_trn_serial30_byte2, byte2, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_bitmask_text(tree, tvb, 2, 1, NULL, NULL,
			ett_ipmi_trn_serial30_byte3, byte3, ENC_LITTLE_ENDIAN, 0);
}

static void
serial_31(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_serial31_port, tvb, 0, 2, ENC_LITTLE_ENDIAN);
}

static void
serial_32(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_serial32_port, tvb, 0, 2, ENC_LITTLE_ENDIAN);
}

static void
serial_33(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_serial33_auth_proto, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_serial33_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
}

static void
serial_34(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_serial34_chap_name, tvb, 0, 16, ENC_ASCII|ENC_NA);
}

static void
serial_35(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_serial35_recv_accm, tvb, 0, 4, ENC_BIG_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_serial35_xmit_accm, tvb, 4, 4, ENC_BIG_ENDIAN);
}

static void
serial_36(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_serial36_snoop_accm, tvb, 0, 4, ENC_BIG_ENDIAN);
}

static void
serial_37(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_serial37_num_ppp, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_serial37_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
}

static void
serial_38(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_serial38_acct_sel, tvb, 0, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_serial38_dialstr_sel, tvb, 1, 1, ENC_LITTLE_ENDIAN);
}

static void
serial_39(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_serial39_acct_sel, tvb, 0, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_serial39_ipaddr, tvb, 1, 4, ENC_BIG_ENDIAN);
}

static void
serial_40(tvbuff_t *tvb, proto_tree *tree)
{
	int slen;

	proto_tree_add_item(tree, hf_ipmi_trn_serial40_acct_sel, tvb, 0, 1, ENC_LITTLE_ENDIAN);
	slen = tvb_captured_length(tvb) - 1;
	if (slen > 16) {
		slen = 16;
	}
	proto_tree_add_item(tree, hf_ipmi_trn_serial40_username, tvb, 1, slen, ENC_ASCII|ENC_NA);
}

static void
serial_41(tvbuff_t *tvb, proto_tree *tree)
{
	int slen;

	proto_tree_add_item(tree, hf_ipmi_trn_serial41_acct_sel, tvb, 0, 1, ENC_LITTLE_ENDIAN);
	slen = tvb_captured_length(tvb) - 1;
	if (slen > 16) {
		slen = 16;
	}
	proto_tree_add_item(tree, hf_ipmi_trn_serial41_userdomain, tvb, 1, slen, ENC_ASCII|ENC_NA);
}

static void
serial_42(tvbuff_t *tvb, proto_tree *tree)
{
	int slen;

	proto_tree_add_item(tree, hf_ipmi_trn_serial42_acct_sel, tvb, 0, 1, ENC_LITTLE_ENDIAN);
	slen = tvb_captured_length(tvb) - 1;
	if (slen > 16) {
		slen = 16;
	}
	proto_tree_add_item(tree, hf_ipmi_trn_serial42_userpass, tvb, 1, slen, ENC_ASCII|ENC_NA);
}

static void
serial_43(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_serial43_auth_proto, NULL };

	proto_tree_add_item(tree, hf_ipmi_trn_serial43_acct_sel, tvb, 0, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_bitmask_text(tree, tvb, 1, 1, NULL, NULL,
			ett_ipmi_trn_serial43_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
}

static void
serial_44(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_serial44_acct_sel, tvb, 0, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_serial44_hold_time, tvb, 1, 1, ENC_LITTLE_ENDIAN);
}

static void
serial_45(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_serial45_src_ipaddr, tvb, 0, 4, ENC_BIG_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_serial45_dst_ipaddr, tvb, 4, 4, ENC_BIG_ENDIAN);
}

static void
serial_46(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_serial46_tx_bufsize, tvb, 0, 2, ENC_LITTLE_ENDIAN);
}

static void
serial_47(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_serial47_rx_bufsize, tvb, 0, 2, ENC_LITTLE_ENDIAN);
}

static void
serial_48(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_serial48_ipaddr, tvb, 0, 4, ENC_BIG_ENDIAN);
}

static void
serial_49(tvbuff_t *tvb, proto_tree *tree)
{
	int slen;

	proto_tree_add_item(tree, hf_ipmi_trn_serial49_blockno, tvb, 0, 1, ENC_LITTLE_ENDIAN);
	slen = tvb_captured_length(tvb) - 1;
	if (slen > 16) {
		slen = 16;
	}
	proto_tree_add_item(tree, hf_ipmi_trn_serial49_dialstr, tvb, 1, slen, ENC_ASCII|ENC_NA);
}

static void
serial_50(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_serial50_115200, &hf_ipmi_trn_serial50_57600,
		&hf_ipmi_trn_serial50_38400, &hf_ipmi_trn_serial50_19200, &hf_ipmi_trn_serial50_9600, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, "Bit rate support: ", "None",
			ett_ipmi_trn_serial50_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
}

static void
serial_51(tvbuff_t *tvb, proto_tree *tree)
{
	static int * const byte2[] = { &hf_ipmi_trn_serial51_ipmi_channel, &hf_ipmi_trn_serial51_conn_num, NULL };
	static int * const byte3[] = { &hf_ipmi_trn_serial51_ipmi_sharing,
		&hf_ipmi_trn_serial51_ipmi_sol, &hf_ipmi_trn_serial51_chan_num, NULL };

	proto_tree_add_item(tree, hf_ipmi_trn_serial51_port_assoc_sel, tvb, 0, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_bitmask_text(tree, tvb, 1, 1, NULL, NULL,
			ett_ipmi_trn_serial51_byte2, byte2, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_bitmask_text(tree, tvb, 2, 1, NULL, NULL,
			ett_ipmi_trn_serial51_byte3, byte3, ENC_LITTLE_ENDIAN, 0);
}

static void
serial_52(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_serial52_port_assoc_sel, tvb, 0, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_serial52_conn_name, tvb, 1, 16, ENC_NA);
}

static void
serial_53(tvbuff_t *tvb, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_serial53_port_assoc_sel, tvb, 0, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_serial53_chan_name, tvb, 1, 16, ENC_NA);
}

static struct {
	void (*intrp)(tvbuff_t *tvb, proto_tree *tree);
	const char *name;
} serial_options[] = {
	{ lan_serial_00, "Set In Progress" },
	{ lan_serial_01, "Authentication Type Support" },
	{ lan_serial_02, "Authentication Type Enables" },
	{ serial_03, "Connection Mode" },
	{ serial_04, "Session Inactivity Timeout" },
	{ serial_05, "Channel Callback Control" },
	{ serial_06, "Session Termination" },
	{ serial_07, "IPMI Messaging Comm Settings" },
	{ serial_08, "Mux Switch Control" },
	{ serial_09, "Modem Ring Time" },
	{ serial_10, "Modem Init String" },
	{ serial_11, "Modem Escape Sequence" },
	{ serial_12, "Modem Hang-up Sequence" },
	{ serial_13, "Modem Dial Command" },
	{ serial_14, "Page Blackout Interval" },
	{ serial_15, "Community String" },
	{ serial_16, "Number of Alert Destinations" },
	{ serial_17, "Destination Info" },
	{ serial_18, "Call Retry Interval" },
	{ serial_19, "Destination Comm Settings" },
	{ serial_20, "Number of Dial Strings" },
	{ serial_21, "Destination Dial Strings" },
	{ serial_22, "Number of Alert Destination IP Addresses" },
	{ serial_23, "Destination IP Addresses" },
	{ serial_24, "Number of TAP Accounts" },
	{ serial_25, "TAP Account" },
	{ serial_26, "TAP Passwords" },
	{ serial_27, "TAP Pager ID Strings" },
	{ serial_28, "TAP Service Settings" },
	{ serial_29, "Terminal Mode Configuration" },
	{ serial_30, "PPP Protocol Options" },
	{ serial_31, "PPP Primary RMCP Port" },
	{ serial_32, "PPP Secondary RMCP Port" },
	{ serial_33, "PPP Link Authentication" },
	{ serial_34, "CHAP Name" },
	{ serial_35, "PPP ACCM" },
	{ serial_36, "PPP Snoop ACCM" },
	{ serial_37, "Number of PPP Accounts" },
	{ serial_38, "PPP Account Dial String Selector" },
	{ serial_39, "PPP Account IP Addresses" },
	{ serial_40, "PPP Account User Names" },
	{ serial_41, "PPP Account User Domains" },
	{ serial_42, "PPP Account User Passwords" },
	{ serial_43, "PPP Account Authentication Settings" },
	{ serial_44, "PPP Account Connection Hold Times" },
	{ serial_45, "PPP UDP Proxy IP Header" },
	{ serial_46, "PPP UDP Proxy Transmit Buffer Size" },
	{ serial_47, "PPP UDP Proxy Receive Buffer Size" },
	{ serial_48, "PPP Remote Console IP Address" },
	{ serial_49, "System Phone Number" },
	{ serial_50, "Bitrate Support" },
	{ serial_51, "System Serial Port Association" },
	{ serial_52, "System Connector Names" },
	{ serial_53, "System Serial Channel Names" }
};

/* Set Serial/Modem Configuration Parameters
 */
static void
rq10(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_10_chan, NULL };
	tvbuff_t *next;
	const char *desc;
	guint8 pno;

	pno = tvb_get_guint8(tvb, 1);
	if (pno < array_length(serial_options)) {
		desc = serial_options[pno].name;
	} else if (pno >= 0xC0) {
		desc = "OEM";
	} else {
		desc = "Reserved";
	}

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL, ett_ipmi_trn_10_byte1,
			byte1, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_uint_format_value(tree, hf_ipmi_trn_10_param, tvb, 1, 1,
			pno, "%s (0x%02x)", desc, pno);
	if (pno < array_length(serial_options)) {
		next = tvb_new_subset_remaining(tvb, 2);
		serial_options[pno].intrp(next, tree);
	} else {
		proto_tree_add_item(tree, hf_ipmi_trn_10_param_data, tvb, 2, -1, ENC_NA);
	}
}

static const value_string cc10[] = {
	{ 0x80, "Parameter not supported" },
	{ 0x81, "Attempt to set the 'set in progress' value (in parameter #0) when not in the 'set complete' state" },
	{ 0x82, "Attempt to write read-only parameter" },
	{ 0x83, "Attempt to read write-only parameter" },
	{ 0, NULL }
};

/* Get LAN Configuration Parameters
 */
static void
rq11(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_11_getrev, &hf_ipmi_trn_11_chan, NULL };
	const char *desc;
	guint8 pno;

	pno = tvb_get_guint8(tvb, 1);

	ipmi_set_data(pinfo, 0, pno);
	ipmi_set_data(pinfo, 1, tvb_get_guint8(tvb, 0));

	if (!tree) {
		return;
	}

	if (pno < array_length(serial_options)) {
		desc = serial_options[pno].name;
	} else if (pno >= 0xC0) {
		desc = "OEM";
	} else {
		desc = "Reserved";
	}

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_11_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_uint_format_value(tree, hf_ipmi_trn_11_param, tvb, 1, 1,
			pno, "%s (0x%02x)", desc, pno);
	proto_tree_add_item(tree, hf_ipmi_trn_11_set, tvb, 2, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_11_block, tvb, 2, 1, ENC_LITTLE_ENDIAN);
}

static void
rs11(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_11_rev_present, &hf_ipmi_trn_11_rev_compat, NULL };
	proto_item *ti;
	proto_tree *subtree;
	tvbuff_t *next;
	const char *desc;
	guint32 pno, req;

	ti = proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_11_rev, byte1, ENC_LITTLE_ENDIAN, 0);

	if (!ipmi_get_data(pinfo, 0, &pno) || !ipmi_get_data(pinfo, 1, &req)) {
		/* No request found - cannot parse further */
		if (tvb_captured_length(tvb) > 1) {
			proto_tree_add_item(tree, hf_ipmi_trn_11_param_data, tvb, 1, -1, ENC_NA);
		};
		return;
	}

	if (pno < array_length(serial_options)) {
		desc = serial_options[pno].name;
	} else if (pno >= 0xC0) {
		desc = "OEM";
	} else {
		desc = "Reserved";
	}

	if ((req & 0x80) && tvb_captured_length(tvb) > 1) {
		expert_add_info(pinfo, ti, &ei_ipmi_trn_11_request_param_rev);
	} else if (!(req & 0x80) && tvb_captured_length(tvb) == 1) {
		expert_add_info(pinfo, ti, &ei_ipmi_trn_11_request_param_data);
	}

	subtree = proto_tree_add_subtree_format(tree, tvb, 0, 0, ett_ipmi_trn_parameter, NULL, "Parameter: %s", desc);

	if (tvb_captured_length(tvb) > 1) {
		if (pno < array_length(serial_options)) {
			next = tvb_new_subset_remaining(tvb, 1);
			serial_options[pno].intrp(next, subtree);
		} else {
			proto_tree_add_item(subtree, hf_ipmi_trn_11_param_data, tvb, 1, -1, ENC_NA);
		}
	}
}

static const value_string cc11[] = {
	{ 0x80, "Parameter not supported" },
	{ 0, NULL }
};

/* Set Serial/Modem Mux
 */
static void
rq12(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_12_chan, NULL };
	static int * const byte2[] = { &hf_ipmi_trn_12_mux_setting, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_12_rq_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_bitmask_text(tree, tvb, 1, 1, NULL, NULL,
			ett_ipmi_trn_12_rq_byte2, byte2, ENC_LITTLE_ENDIAN, 0);
}

static void
rs12(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_12_sw_to_sys, &hf_ipmi_trn_12_sw_to_bmc,
		&hf_ipmi_trn_12_alert, &hf_ipmi_trn_12_msg, &hf_ipmi_trn_12_req, &hf_ipmi_trn_12_mux_state, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_12_rs_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
}

/* Get TAP Response Codes
 */
static void
rq13(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_13_chan, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_13_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
}

static void
rs13(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_13_code1, tvb, 0, 3, ENC_ASCII|ENC_NA);
	proto_tree_add_item(tree, hf_ipmi_trn_13_code2, tvb, 3, 3, ENC_ASCII|ENC_NA);
	proto_tree_add_item(tree, hf_ipmi_trn_13_code3, tvb, 6, 3, ENC_ASCII|ENC_NA);
	proto_tree_add_item(tree, hf_ipmi_trn_13_code4, tvb, 9, 3, ENC_ASCII|ENC_NA);
	proto_tree_add_item(tree, hf_ipmi_trn_13_code5, tvb, 12, 3, ENC_ASCII|ENC_NA);
}

/* Set PPP UDP Proxy Transmit Data
 */
static void
rq14(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_14_chan, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_14_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_item(tree, hf_ipmi_trn_14_block, tvb, 1, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_14_data, tvb, 2, 16, ENC_NA);
}

/* Get PPP UDP Proxy Transmit Data
 */
static void
rq15(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_15_chan, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_15_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_item(tree, hf_ipmi_trn_15_block, tvb, 1, 1, ENC_LITTLE_ENDIAN);
}

static void
rs15(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree)
{
	proto_tree_add_item(tree, hf_ipmi_trn_15_data, tvb, 0, 16, ENC_NA);
}

/* Send PPP UDP Proxy Packet
 */
static void
rq16(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_16_chan, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_16_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_item(tree, hf_ipmi_trn_16_src_port, tvb, 1, 2, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_16_dst_port, tvb, 3, 2, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_16_src_addr, tvb, 5, 4, ENC_BIG_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_16_dst_addr, tvb, 9, 4, ENC_BIG_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_16_bytes, tvb, 13, 2, ENC_LITTLE_ENDIAN);
}

static const value_string cc16[] = {
	{ 0x80, "PPP link is not up" },
	{ 0x81, "IP protocol is not up" },
	{ 0, NULL }
};

/* Get PPP UDP Proxy Receive Data
 */
static void
tr17_fmt_blockno(gchar *s, guint32 v)
{
	g_snprintf(s, ITEM_LABEL_LENGTH, "%d%s",
			v, v ? "" : " (get received data length)");
}

static void
rq17(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_17_chan, NULL };
	static int * const byte2[] = { &hf_ipmi_trn_17_clear, &hf_ipmi_trn_17_block_num, NULL };

	ipmi_set_data(pinfo, 0, tvb_get_guint8(tvb, 1) & 0x7f);
	if (!tree) {
		/* Save block number */
		return;
	}

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_17_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_bitmask_text(tree, tvb, 1, 1, NULL, NULL,
			ett_ipmi_trn_17_byte2, byte2, ENC_LITTLE_ENDIAN, 0);
}

static void
rs17(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree)
{
	guint32 bno;

	if (ipmi_get_data(pinfo, 0, &bno) && bno == 0) {
		/* Request for length */
		proto_tree_add_item(tree, hf_ipmi_trn_17_size, tvb, 0, 2, ENC_LITTLE_ENDIAN);
	} else {
		proto_tree_add_item(tree, hf_ipmi_trn_17_data, tvb, 0,
				tvb_captured_length(tvb) < 16 ? tvb_captured_length(tvb) : 16, ENC_NA);
	}
}

static const value_string cc17[] = {
	{ 0x80, "No packet data available" },
	{ 0, NULL }
};

/* Serial/Modem Connection Active
 */
static void
rq18(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_18_state, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_18_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_item(tree, hf_ipmi_trn_18_ipmi_ver, tvb, 1, 1, ENC_LITTLE_ENDIAN);
}

/* Callback
 */
static void
rq19(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_19_chan, NULL };
	static int * const byte2[] = { &hf_ipmi_trn_19_dest_sel, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_19_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_bitmask_text(tree, tvb, 1, 1, NULL, NULL,
			ett_ipmi_trn_19_byte2, byte2, ENC_LITTLE_ENDIAN, 0);
}

static const value_string cc19[] = {
	{ 0x81, "Callback rejected, alert in progress on this channel" },
	{ 0x82, "Callback rejected, IPMI messaging active on this channel" },
	{ 0, NULL }
};

/* Common for Set/Get User Callback Options
 */
static void
parse_callback_options(tvbuff_t *tvb, guint offs, proto_tree *tree)
{
	static int * const usercap[] = { &hf_ipmi_trn_XX_cap_cbcp, &hf_ipmi_trn_XX_cap_ipmi, NULL };
	static int * const cbcp[] = { &hf_ipmi_trn_XX_cbcp_from_list, &hf_ipmi_trn_XX_cbcp_user,
		&hf_ipmi_trn_XX_cbcp_prespec, &hf_ipmi_trn_XX_cbcp_nocb, NULL };

	proto_tree_add_bitmask_text(tree, tvb, offs, 1,
			"User callback capabilities: ", "None",
			ett_ipmi_trn_XX_usercap, usercap, ENC_LITTLE_ENDIAN, BMT_NO_TFS);
	proto_tree_add_bitmask_text(tree, tvb, offs + 1, 1,
			"CBCP negotiation options: ", "None",
			ett_ipmi_trn_XX_cbcp, cbcp, ENC_LITTLE_ENDIAN, BMT_NO_TFS);
	proto_tree_add_item(tree, hf_ipmi_trn_XX_dst1, tvb, offs + 2, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_XX_dst2, tvb, offs + 3, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_ipmi_trn_XX_dst3, tvb, offs + 4, 1, ENC_LITTLE_ENDIAN);
}

/* Set User Callback Options
 */
static void
rq1a(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_1a_user, NULL };
	static int * const byte2[] = { &hf_ipmi_trn_1a_chan, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_1a_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_bitmask_text(tree, tvb, 1, 1, NULL, NULL,
			ett_ipmi_trn_1a_byte2, byte2, ENC_LITTLE_ENDIAN, 0);
	parse_callback_options(tvb, 2, tree);
}

/* Get User Callback Options
 */
static void
rq1b(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree)
{
	static int * const byte1[] = { &hf_ipmi_trn_1b_user, NULL };
	static int * const byte2[] = { &hf_ipmi_trn_1b_chan, NULL };

	proto_tree_add_bitmask_text(tree, tvb, 0, 1, NULL, NULL,
			ett_ipmi_trn_1b_byte1, byte1, ENC_LITTLE_ENDIAN, 0);
	proto_tree_add_bitmask_text(tree, tvb, 1, 1, NULL, NULL,
			ett_ipmi_trn_1b_byte2, byte2, ENC_LITTLE_ENDIAN, 0);
}

static void
rs1b(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree)
{
	parse_callback_options(tvb, 0, tree);
}

static const value_string cc21[] = {
	{ 0x80, "Parameter not supported" },
	{ 0x81, "Attempt to set the 'set in progress' value (in parameter #0) when not in the 'set complete' state" },
	{ 0x82, "Attempt to write read-only parameter" },
	{ 0x83, "Attempt to read write-only parameter" },
	{ 0, NULL }
};

static const value_string cc22[] = {
	{ 0x80, "Parameter not supported" },
	{ 0, NULL }
};

static const value_string cc33[] = {
	{ 0x80, "Target controller unavailable" },
	{ 0, NULL }
};

static ipmi_cmd_t cmd_transport[] = {
	/* LAN Device Commands */
	{ 0x01, rq01, NULL, cc01, NULL, "Set LAN Configuration Parameters", 0 },
	{ 0x02, rq02, rs02, cc02, NULL, "Get LAN Configuration Parameters", CMD_CALLRQ },
	{ 0x03, rq03, rs03, NULL, NULL, "Suspend BMC ARPs", 0 },
	{ 0x04, rq04, rs04, NULL, NULL, "Get IP/UDP/RMCP Statistics", 0 },

	/* Serial/Modem Device Commands */
	{ 0x10, rq10, NULL, cc10, NULL, "Set Serial/Modem Configuration", 0 },
	{ 0x11, rq11, rs11, cc11, NULL, "Get Serial/Modem Configuration", CMD_CALLRQ },
	{ 0x12, rq12, rs12, NULL, NULL, "Set Serial/Modem Mux", 0 },
	{ 0x13, rq13, rs13, NULL, NULL, "Get TAP Response Codes", 0 },
	{ 0x14, rq14, NULL, NULL, NULL, "Set PPP UDP Proxy Transmit Data", 0 },
	{ 0x15, rq15, rs15, NULL, NULL, "Get PPP UDP Proxy Transmit Data", 0 },
	{ 0x16, rq16, NULL, cc16, NULL, "Send PPP UDP Proxy Packet", 0 },
	{ 0x17, rq17, rs17, cc17, NULL, "Get PPP UDP Proxy Receive Data", CMD_CALLRQ },
	{ 0x18, rq18, NULL, NULL, NULL, "Serial/Modem Connection Active", 0 },
	{ 0x19, rq19, NULL, cc19, NULL, "Callback", 0 },
	{ 0x1a, rq1a, NULL, NULL, NULL, "Set User Callback Options", 0 },
	{ 0x1b, rq1b, rs1b, NULL, NULL, "Get User Callback Options", 0 },
	{ 0x1c, IPMI_TBD,   NULL, NULL, "Set Serial Routing Mux", 0 },

	/* Serial-Over-LAN Commands */
	{ 0x20, IPMI_TBD,   NULL, NULL, "SOL Activating", 0 },
	{ 0x21, IPMI_TBD,   cc21, NULL, "Set SOL Configuration Parameters", 0 },
	{ 0x22, IPMI_TBD,   cc22, NULL, "Get SOL Configuration Parameters", CMD_CALLRQ },

	/* Command Forwarding Commands */
	{ 0x30, IPMI_TBD,   NULL, NULL, "Forwarded Command", 0 },
	{ 0x31, IPMI_TBD,   NULL, NULL, "Set Forwarded Commands", 0 },
	{ 0x32, IPMI_TBD,   NULL, NULL, "Get Forwarded Commands", 0 },
	{ 0x33, IPMI_TBD,   cc33, NULL, "Enable Forwarded Commands", 0 },
};

void
proto_register_ipmi_transport(void)
{
	static hf_register_info hf[] = {
		{ &hf_ipmi_trn_lan00_sip,
			{ "Set In Progress",
				"ipmi_lan00_sip", FT_UINT8, BASE_HEX, VALS(lan00_sip_vals), 0x03, NULL, HFILL }},

		{ &hf_ipmi_trn_lanXX_oem,
			{ "OEM Proprietary",
				"ipmi_lanXX_oem", FT_BOOLEAN, 8, NULL, 0x20, NULL, HFILL }},
		{ &hf_ipmi_trn_lanXX_passwd,
			{ "Straight password/key",
				"ipmi_lanXX_passwd", FT_BOOLEAN, 8, NULL, 0x10, NULL, HFILL }},
		{ &hf_ipmi_trn_lanXX_md5,
			{ "MD5",
				"ipmi_lanXX_md5", FT_BOOLEAN, 8, NULL, 0x04, NULL, HFILL }},
		{ &hf_ipmi_trn_lanXX_md2,
			{ "MD2",
				"ipmi_lanXX_md2", FT_BOOLEAN, 8, NULL, 0x02, NULL, HFILL }},
		{ &hf_ipmi_trn_lanXX_none,
			{ "None",
				"ipmi_lanXX_none", FT_BOOLEAN, 8, NULL, 0x01, NULL, HFILL }},

		{ &hf_ipmi_trn_lan03_ip,
			{ "IP Address",
				"ipmi_lan03_ip", FT_IPv4, BASE_NONE, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_lan04_ipsrc,
			{ "IP Address Source",
				"ipmi_lan04_ipsrc", FT_UINT8, BASE_HEX, VALS(lan04_ipsrc_vals), 0x0f, NULL, HFILL }},

		{ &hf_ipmi_trn_lan05_ether,
			{ "MAC Address",
				"ipmi_lan05_mac", FT_ETHER, BASE_NONE, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_lan06_subnet,
			{ "Subnet Mask",
				"ipmi_lan06_subnet", FT_IPv4, BASE_NONE, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_lan07_ttl,
			{ "Time-to-live",
				"ipmi_lan07_ttl", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan07_flags,
			{ "Flags",
				"ipmi_lan07_flags", FT_UINT8, BASE_HEX, NULL, 0xe0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan07_precedence,
			{ "Precedence",
				"ipmi_lan07_precedence", FT_UINT8, BASE_DEC, NULL, 0xe0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan07_tos,
			{ "Type of service",
				"ipmi_lan07_tos", FT_UINT8, BASE_HEX, NULL, 0x1e, NULL, HFILL }},

		{ &hf_ipmi_trn_lan08_rmcp_port,
			{ "Primary RMCP Port Number",
				"ipmi_lan08_rmcp_port", FT_UINT16, BASE_CUSTOM, CF_FUNC(ipmi_fmt_udpport), 0, NULL, HFILL }},

		{ &hf_ipmi_trn_lan09_rmcp_port,
			{ "Secondary RMCP Port Number",
				"ipmi_lan09_rmcp_port", FT_UINT16, BASE_CUSTOM, CF_FUNC(ipmi_fmt_udpport), 0, NULL, HFILL }},

		{ &hf_ipmi_trn_lan10_responses,
			{ "ARP responses",
				"ipmi_lan10_responses", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x02, NULL, HFILL }},
		{ &hf_ipmi_trn_lan10_gratuitous,
			{ "Gratuitous ARPs",
				"ipmi_lan10_gratuitous", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x01, NULL, HFILL }},

		{ &hf_ipmi_trn_lan11_arp_interval,
			{ "Gratuitous ARP interval",
				"ipmi_lan10_arp_interval", FT_UINT8, BASE_CUSTOM, CF_FUNC(ipmi_fmt_500ms_0based), 0, NULL, HFILL }},

		{ &hf_ipmi_trn_lan12_def_gw_ip,
			{ "Default Gateway Address",
				"ipmi_lan12_def_gw_ip", FT_IPv4, BASE_NONE, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_lan13_def_gw_mac,
			{ "Default Gateway MAC Address",
				"ipmi_lan13_def_gw_mac", FT_ETHER, BASE_NONE, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_lan14_bkp_gw_ip,
			{ "Backup Gateway Address",
				"ipmi_lan14_bkp_gw_ip", FT_IPv4, BASE_NONE, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_lan15_bkp_gw_mac,
			{ "Backup Gateway MAC Address",
				"ipmi_lan15_bkp_gw_mac", FT_ETHER, BASE_NONE, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_lan16_comm_string,
			{ "Community String",
				"ipmi_lan16_comm_string", FT_STRING, BASE_NONE, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_lan17_num_dst,
			{ "Number of Destinations",
				"ipmi_lan17_num_dst", FT_UINT8, BASE_DEC, NULL, 0x0f, NULL, HFILL }},

		{ &hf_ipmi_trn_lan18_dst_selector,
			{ "Destination Selector",
				"ipmi_lan18_dst_selector", FT_UINT8, BASE_DEC, NULL, 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_lan18_ack,
			{ "Alert Acknowledged",
				"ipmi_lan18_ack", FT_BOOLEAN, 8, TFS(&lan18_ack_tfs), 0x80, NULL, HFILL }},
		{ &hf_ipmi_trn_lan18_dst_type,
			{ "Destination Type",
				"ipmi_lan18_dst_type", FT_UINT8, BASE_HEX, VALS(lan18_dst_type_vals), 0x07, NULL, HFILL }},
		{ &hf_ipmi_trn_lan18_tout,
			{ "Timeout/Retry Interval",
				"ipmi_lan18_tout", FT_UINT8, BASE_CUSTOM, CF_FUNC(ipmi_fmt_1s_0based), 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan18_retries,
			{ "Retries",
				"ipmi_lan18_retries", FT_UINT8, BASE_DEC, NULL, 0x07, NULL, HFILL }},

		{ &hf_ipmi_trn_lan19_dst_selector,
			{ "Destination Selector",
				"ipmi_lan19_dst_selector", FT_UINT8, BASE_DEC, NULL, 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_lan19_addr_format,
			{ "Address Format",
				"ipmi_lan19_addr_format", FT_UINT8, BASE_HEX, VALS(lan19_af_vals), 0xf0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan19_address,
			{ "Address (format unknown)",
				"ipmi_lan19_address", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan19_gw_sel,
			{ "Gateway selector",
				"ipmi_lan19_gw_sel", FT_BOOLEAN, 8, TFS(&lan19_gw_sel_tfs), 0x01, NULL, HFILL }},
		{ &hf_ipmi_trn_lan19_ip,
			{ "Alerting IP Address",
				"ipmi_lan19_ip", FT_IPv4, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan19_mac,
			{ "Alerting MAC Address",
				"ipmi_lan19_mac", FT_ETHER, BASE_NONE, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_lan20_vlan_id_enable,
			{ "VLAN ID Enable",
				"ipmi_lan20_vlan_id_enable", FT_BOOLEAN, 16, TFS(&lan20_enable_tfs), 0x8000, NULL, HFILL }},
		{ &hf_ipmi_trn_lan20_vlan_id,
			{ "VLAN ID",
				"ipmi_lan20_vlan_id", FT_UINT16, BASE_HEX, NULL, 0x0fff, NULL, HFILL }},

		{ &hf_ipmi_trn_lan21_vlan_prio,
			{ "VLAN Priority",
				"ipmi_lan21_vlan_prio", FT_UINT8, BASE_DEC, NULL, 0x07, NULL, HFILL }},

		{ &hf_ipmi_trn_lan22_num_cs_entries,
			{ "Number of Cipher Suite Entries",
				"ipmi_lan22_num_cs_entries", FT_UINT8, BASE_DEC, NULL, 0x1f, NULL, HFILL }},

		{ &hf_ipmi_trn_lan23_cs_entry,
			{ "Cipher Suite ID",
				"ipmi_lan23_cs_entry", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_lan24_priv1,
			{ "Maximum Privilege Level for Cipher Suite",
				"ipmi_lan24_priv", FT_UINT8, BASE_HEX, NULL, 0xF0, NULL, HFILL }},

		{ &hf_ipmi_trn_lan24_priv2,
			{ "Maximum Privilege Level for Cipher Suite",
				"ipmi_lan24_priv", FT_UINT8, BASE_HEX, NULL, 0x0F, NULL, HFILL }},

		{ &hf_ipmi_trn_lan25_dst_selector,
			{ "Destination Selector",
				"ipmi_lan25_dst_selector", FT_UINT8, BASE_DEC, NULL, 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_lan25_addr_format,
			{ "Address Format",
				"ipmi_lan25_addr_format", FT_UINT8, BASE_HEX, VALS(lan25_af_vals), 0xf0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan25_address,
			{ "Address (format unknown)",
				"ipmi_lan25_address", FT_UINT8, BASE_HEX, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan25_uprio,
			{ "User priority",
				"ipmi_lan25_uprio", FT_UINT16, BASE_DEC, NULL, 0xe000, NULL, HFILL }},
		{ &hf_ipmi_trn_lan25_cfi,
			{ "CFI",
				"ipmi_lan25_cfi", FT_BOOLEAN, 16, NULL, 0x1000, NULL, HFILL }},
		{ &hf_ipmi_trn_lan25_vlan_id,
			{ "VLAN ID",
				"ipmi_lan25_vlan_id", FT_UINT16, BASE_HEX, NULL, 0x0fff, NULL, HFILL }},

		{ &hf_ipmi_trn_lan26_gen_event,
			{ "Generate a Session Audit sensor \"Invalid password disable\" event message",
				"ipmi_lan26_gen_event", FT_BOOLEAN, 8, NULL, 0x01, NULL, HFILL }},
		{ &hf_ipmi_trn_lan26_thresh_number,
			{ "Bad Password Threshold number",
				"ipmi_lan26_thresh_number", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan26_reset_interval,
			{ "Attempt Count Reset Interval",
				"ipmi_lan26_reset_interval", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan26_lock_interval,
			{ "User Lockout Interval",
				"ipmi_lan26_lock_interval", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_lan50_ipv6_only,
			{ "Support IPv6 addressing only",
				"ipmi_lan50_ipv6_only", FT_BOOLEAN, 8, NULL, 0x01, NULL, HFILL }},
		{ &hf_ipmi_trn_lan50_both_ipv4_ipv6,
			{ "Support both IPv4 and IPv6 simultaneously",
				"ipmi_lan50_both", FT_BOOLEAN, 8, NULL, 0x02, NULL, HFILL }},
		{ &hf_ipmi_trn_lan50_ipv6_alerting,
			{ "Support IPv6 destinations for LAN Alerting",
				"ipmi_lan50_ipv6_alerting", FT_BOOLEAN, 8, NULL, 0x04, NULL, HFILL }},

		{ &hf_ipmi_trn_lan51_enables,
			{ "Enables",
				"ipmi_lan51_enables", FT_UINT8, BASE_HEX, VALS(lan51_enables), 0, NULL, HFILL }},

		{ &hf_ipmi_trn_lan52_traffic_class,
			{ "Traffic Class",
				"ipmi_lan52_class", FT_UINT8, BASE_HEX, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_lanXX_hop_limit,
			{ "Hop Limit",
				"ipmi_lanXX_hop_limit", FT_UINT8, BASE_DEC_HEX, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_lan54_flow_label,
			{ "Flow Label",
				"ipmi_lan_flow_label", FT_UINT24, BASE_HEX, NULL, 0xFFFFF, NULL, HFILL }},

		{ &hf_ipmi_trn_lan55_static_addr_max,
			{ "Static Address Max",
				"ipmi_lan55_static_max", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan55_dynamic_addr_max,
			{ "Dynamic Address Max",
				"ipmi_lan55_dynamic_max", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan55_dhcpv6_support,
			{ "DHCPv6 is supported",
				"ipmi_lan55_dhcpv6", FT_BOOLEAN, 8, NULL, 0x01, NULL, HFILL }},
		{ &hf_ipmi_trn_lan55_slaac_support,
			{ "SLAAC is supported",
				"ipmi_lan55_slaac", FT_BOOLEAN, 8, NULL, 0x02, NULL, HFILL }},

		{ &hf_ipmi_trn_lanXX_addr_selector,
			{ "Address Selector",
				"ipmi_lanXX_addr_sel", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lanXX_addr_type,
			{ "Address source/type",
				"ipmi_lanXX_addr_type", FT_UINT8, BASE_DEC, VALS(lanXX_addr_type), 0xF, NULL, HFILL }},
		{ &hf_ipmi_trn_lanXX_addr_enable,
			{ "Address is enabled",
				"ipmi_lanXX_addr_enable", FT_BOOLEAN, 8, NULL, 0x80, NULL, HFILL }},
		{ &hf_ipmi_trn_lanXX_addr,
			{ "IPv6 Address",
				"ipmi_lanXX_addr", FT_IPv6, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lanXX_prefix_len,
			{ "Prefix Length",
				"ipmi_lanXX_prefix_len", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lanXX_addr_status,
			{ "Address status",
				"ipmi_lanXX_addr_status", FT_UINT8, BASE_DEC, VALS(lanXX_addr_status), 0, NULL, HFILL }},

		{ &hf_ipmi_trn_lanXX_max_duid_blocks,
			{ "Maximum number of 16-byte blocks",
				"ipmi_lanXX_max_duid_blocks", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_lanXX_duid_selector,
			{ "DUID selector",
				"ipmi_lanXX_duid_sel", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lanXX_block_selector,
			{ "Block selector",
				"ipmi_lanXX_block_sel", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lanXX_duid,
			{ "DUID data",
				"ipmi_lanXX_duid", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_lanXX_timing_support,
			{ "Timing Configuration Support",
				"ipmi_lanXX_timing_support", FT_UINT8, BASE_DEC, VALS(lanXX_timing_support), 0, NULL, HFILL }},

		{ &hf_ipmi_trn_lanXX_iface_selector,
			{ "IPv6 Interface selector",
				"ipmi_lanXX_iface_sel", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan63_sol_max_delay,
			{ "SOL_MAX_DELAY",
				"ipmi_lan63_sol_max_delay", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan63_sol_timeout,
			{ "SOL_TIMEOUT",
				"ipmi_lan63_sol_timeout", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan63_sol_max_rt,
			{ "SOL_MAX_RT",
				"ipmi_lan63_sol_max_rt", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan63_req_timeout,
			{ "REQ_TIMEOUT",
				"ipmi_lan63_req_timeout", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan63_req_max_rt,
			{ "REQ_MAX_RT",
				"ipmi_lan63_req_max_rt", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan63_req_max_rc,
			{ "REQ_MAX_RC",
				"ipmi_lan63_req_max_rc", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan63_cnf_max_delay,
			{ "CNF_MAX_DELAY",
				"ipmi_lan63_cnf_max_delay", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan63_cnf_timeout,
			{ "CNF_TIMEOUT",
				"ipmi_lan63_cnf_timeout", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan63_cnf_max_rt,
			{ "CNF_MAX_RT",
				"ipmi_lan63_cnf_max_rt", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan63_cnf_max_rd,
			{ "CNF_MAX_RD",
				"ipmi_lan63_cnf_max_rd", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan63_ren_timeout,
			{ "REN_TIMEOUT",
				"ipmi_lan63_ren_timeout", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan63_ren_max_rt,
			{ "REN_MAX_RT",
				"ipmi_lan63_ren_max_rt", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan63_reb_timeout,
			{ "REB_TIMEOUT",
				"ipmi_lan63_reb_timeout", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan63_reb_max_rt,
			{ "REB_MAX_RT",
				"ipmi_lan63_reb_max_rt", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan63_inf_max_delay,
			{ "INF_MAX_DELAY",
				"ipmi_lan63_inf_max_delay", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan63_inf_timeout,
			{ "INF_TIMEOUT",
				"ipmi_lan63_inf_timeout", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan63_inf_max_rt,
			{ "INF_MAX_RT",
				"ipmi_lan63_inf_max_rt", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan63_rel_timeout,
			{ "REL_TIMEOUT",
				"ipmi_lan63_rel_timeout", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan63_rel_max_rc,
			{ "REL_MAX_RC",
				"ipmi_lan63_rel_max_rc", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan63_dec_timeout,
			{ "DEC_TIMEOUT",
				"ipmi_lan63_dec_timeout", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan63_dec_max_rc,
			{ "DEC_MAX_RC",
				"ipmi_lan63_dec_max_rc", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan63_hop_count_limit,
			{ "HOP_COUNT_LIMIT",
				"ipmi_lan63_hop_count_limit", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_lan64_static_cfg,
			{ "Enable static router address",
				"ipmi_lan64_static_cfg", FT_BOOLEAN, 8, NULL, 0x01, NULL, HFILL }},
		{ &hf_ipmi_trn_lan64_dynamic_cfg,
			{ "Enable dynamic router address configuration",
				"ipmi_lan64_dynamic_cfg", FT_BOOLEAN, 8, NULL, 0x02, NULL, HFILL }},

		{ &hf_ipmi_trn_lanXX_router_selector,
			{ "Router selector",
				"ipmi_lanXX_router_sel", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lanXX_router_mac,
			{ "MAC Address",
				"ipmi_lanXX_mac", FT_ETHER, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lanXX_router_prefix,
			{ "Prefix Value",
				"ipmi_lanXX_prefix", FT_IPv6, BASE_NONE, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_lan73_num_dynamic_sets,
			{ "Number of Dynamic Router Info sets",
				"ipmi_lanXX_num_dynamic_sets", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_lan80_max_rtr_solicitation_delay,
			{ "MAX_RTR_SOLICITATION_DELAY",
				"ipmi_lan80_max_rtr_sol_delay", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan80_rtr_solicitation_interval,
			{ "RTR_SOLICITATION_INTERVAL",
				"ipmi_lan80_rtr_sol_interval", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan80_max_rtr_solicitations,
			{ "MAX_RTR_SOLICITATIONS",
				"ipmi_lan80_max_rtr_sols", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan80_dup_addr_detect_transmits,
			{ "DupAddrDetectTransmits",
				"ipmi_lan80_dup_addr_transmits", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan80_max_multicast_solicit,
			{ "MAX_MULTICAST_SOLICIT",
				"ipmi_lan80_max_mcast_sol", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan80_max_unicast_solicit,
			{ "MAX_UNICAST_SOLICIT",
				"ipmi_lan80_max_ucast_sol", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan80_max_anycast_delay_time,
			{ "MAX_ANYCAST_DELAY_TIME",
				"ipmi_lan80_max_anycast_delay", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan80_max_neighbor_advertisement,
			{ "MAX_NEIGHBOR_ADVERTISEMENT",
				"ipmi_lan80_max_neigh_adv", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan80_reachable_time,
			{ "REACHABLE_TIME",
				"ipmi_lan80_reach_time", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan80_retrans_timer,
			{ "RETRANS_TIMER",
				"ipmi_lan80_retrans_timer", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan80_delay_first_probe_time,
			{ "DELAY_FIRST_PROBE_TIME",
				"ipmi_lan80_delay_first_probe", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan80_max_random_factor,
			{ "MAX_RANDOM_FACTOR",
				"ipmi_lan80_max_rand", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_lan80_min_random_factor,
			{ "MIN_RANDOM_FACTOR",
				"ipmi_lan80_min_rand", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_serial03_connmode,
			{ "Connection Mode",
				"ipmi_serial03_connmode", FT_BOOLEAN, 8, TFS(&serial03_connmode_tfs), 0x80, NULL, HFILL }},
		{ &hf_ipmi_trn_serial03_terminal,
			{ "Terminal Mode",
				"ipmi_serial03_terminal", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x04, NULL, HFILL }},
		{ &hf_ipmi_trn_serial03_ppp,
			{ "PPP Mode",
				"ipmi_serial03_ppp", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x02, NULL, HFILL }},
		{ &hf_ipmi_trn_serial03_basic,
			{ "Basic Mode",
				"ipmi_serial03_basic", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x01, NULL, HFILL }},
		{ &hf_ipmi_trn_serial04_timeout,
			{ "Session Inactivity Timeout",
				"ipmi_serial04_timeout", FT_UINT8, BASE_CUSTOM, CF_FUNC(serial04_timeout_fmt), 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_serial05_cbcp_callback,
			{ "CBCP Callback",
				"ipmi_serial05_cbcp", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x02, NULL, HFILL }},
		{ &hf_ipmi_trn_serial05_ipmi_callback,
			{ "IPMI Callback",
				"ipmi_serial05_ipmi", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x01, NULL, HFILL }},
		{ &hf_ipmi_trn_serial05_cb_list,
			{ "Callback to list of possible numbers",
				"ipmi_serial05_cb_list", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x08, NULL, HFILL }},
		{ &hf_ipmi_trn_serial05_cb_user,
			{ "Callback to user-specifiable number",
				"ipmi_serial05_cb_user", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x04, NULL, HFILL }},
		{ &hf_ipmi_trn_serial05_cb_prespec,
			{ "Callback to pre-specified number",
				"ipmi_serial05_cb_prespec", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x02, NULL, HFILL }},
		{ &hf_ipmi_trn_serial05_no_cb,
			{ "No callback",
				"ipmi_serial05_no_cb", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x01, NULL, HFILL }},
		{ &hf_ipmi_trn_serial05_cb_dest1,
			{ "Callback destination 1",
				"ipmi_serial05_cb_dest1", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial05_cb_dest2,
			{ "Callback destination 2",
				"ipmi_serial05_cb_dest2", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial05_cb_dest3,
			{ "Callback destination 3",
				"ipmi_serial05_cb_dest3", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial06_inactivity,
			{ "Session Inactivity Timeout",
				"ipmi_serial06_inactivity", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x02, NULL, HFILL }},
		{ &hf_ipmi_trn_serial06_dcd,
			{ "Close on DCD Loss",
				"ipmi_serial06_dcd", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x01, NULL, HFILL }},
		{ &hf_ipmi_trn_serial07_flowctl,
			{ "Flow Control",
				"ipmi_serial07_flowctl", FT_UINT8, BASE_HEX, VALS(serialXX_flowctl_vals), 0xc0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial07_dtrhangup,
			{ "DTR Hang-up",
				"ipmi_serial07_dtrhangup", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x20, NULL, HFILL }},
		{ &hf_ipmi_trn_serial07_bitrate,
			{ "Bit rate",
				"ipmi_serial07_bitrate", FT_UINT8, BASE_HEX, VALS(serialXX_bitrate_vals), 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_serial08_esc_powerup,
			{ "Power-up/wakeup via ESC-^",
				"ipmi_serial08_esc_powerup", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x40, NULL, HFILL }},
		{ &hf_ipmi_trn_serial08_esc_reset,
			{ "Hard reset via ESC-R-ESC-r-ESC-R",
				"ipmi_serial08_esc_reset", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x20, NULL, HFILL }},
		{ &hf_ipmi_trn_serial08_switch_authcap,
			{ "Baseboard-to-BMC switch on Get Channel Auth Capabilities",
				"ipmi_serial08_switch_authcap", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x10, NULL, HFILL }},
		{ &hf_ipmi_trn_serial08_switch_rmcp,
			{ "Switch to BMC on IPMI-RMCP pattern",
				"ipmi_serial08_switch_rmcp", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x08, NULL, HFILL }},
		{ &hf_ipmi_trn_serial08_esc_switch1,
			{ "BMC-to-Baseboard switch via ESC-Q",
				"ipmi_serial08_esc_switch1", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x04, NULL, HFILL }},
		{ &hf_ipmi_trn_serial08_esc_switch2,
			{ "Baseboard-to-BMC switch via ESC-(",
				"ipmi_serial08_esc_switch2", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x02, NULL, HFILL }},
		{ &hf_ipmi_trn_serial08_switch_dcdloss,
			{ "Switch to BMC on DCD loss",
				"ipmi_serial08_switch_dcdloss", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x01, NULL, HFILL }},
		{ &hf_ipmi_trn_serial08_sharing,
			{ "Serial Port Sharing",
				"ipmi_serial08_sharing", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x08, NULL, HFILL }},
		{ &hf_ipmi_trn_serial08_ping_callback,
			{ "Serial/Modem Connection Active during callback",
				"ipmi_serial08_ping_callback", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x04, NULL, HFILL }},
		{ &hf_ipmi_trn_serial08_ping_direct,
			{ "Serial/Modem Connection Active during direct call",
				"ipmi_serial08_ping_direct", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x02, NULL, HFILL }},
		{ &hf_ipmi_trn_serial08_ping_retry,
			{ "Retry Serial/Modem Connection Active",
				"ipmi_serial08_ping_retry", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x01, NULL, HFILL }},
		{ &hf_ipmi_trn_serial09_ring_duration,
			{ "Ring Duration",
				"ipmi_serial09_ring_duration", FT_UINT8, BASE_CUSTOM, CF_FUNC(ipmi_fmt_500ms_1based), 0x3f, NULL, HFILL }},
		{ &hf_ipmi_trn_serial09_ring_dead,
			{ "Ring Dead Time",
				"ipmi_serial09_ring_dead", FT_UINT8, BASE_CUSTOM, CF_FUNC(ipmi_fmt_500ms_0based), 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_serial10_set_sel,
			{ "Set selector (16-byte block #)",
				"ipmi_serial10_set_sel", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial10_init_str,
			{ "Modem Init String",
				"ipmi_serial10_init_str", FT_STRING, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial11_esc_seq,
			{ "Modem Escape Sequence",
				"ipmi_serial11_esc_seq", FT_STRING, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial12_hangup_seq,
			{ "Modem Hang-up Sequence",
				"ipmi_serial12_hangup_seq", FT_STRING, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial13_dial_cmd,
			{ "Modem Dial Command",
				"ipmi_serial13_dial_cmd", FT_STRING, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial14_page_blackout,
			{ "Page Blackout Interval (minutes)",
				"ipmi_serial14_page_blackout", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial15_comm_string,
			{ "Community String",
				"ipmi_serial15_comm_string", FT_STRING, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial16_ndest,
			{ "Number of non-volatile Alert Destinations",
				"ipmi_serial16_ndest", FT_UINT8, BASE_DEC, NULL, 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_serial17_dest_sel,
			{ "Destination Selector",
				"ipmi_serial17_dest_sel", FT_UINT8, BASE_DEC, NULL, 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_serial17_ack,
			{ "Alert Acknowledge",
				"ipmi_serial17_ack", FT_BOOLEAN, 8, NULL, 0x80, NULL, HFILL }},
		{ &hf_ipmi_trn_serial17_dest_type,
			{ "Destination Type",
				"ipmi_serial17_dest_type", FT_UINT8, BASE_HEX, VALS(serial17_dest_type_vals), 0x0f, NULL, HFILL }},
#if 0
		{ &hf_ipmi_trn_serial17_ack_timeout,
			{ "Alert Acknowledge Timeout",
				"ipmi_serial17_ack_timeout", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
#endif
		{ &hf_ipmi_trn_serial17_alert_retries,
			{ "Alert retries",
				"ipmi_serial17_alert_retries", FT_UINT8, BASE_DEC, NULL, 0x70, NULL, HFILL }},
		{ &hf_ipmi_trn_serial17_call_retries,
			{ "Call retries",
				"ipmi_serial17_call_retries", FT_UINT8, BASE_DEC, NULL, 0x07, NULL, HFILL }},
		{ &hf_ipmi_trn_serial17_alert_ack_timeout,
			{ "Alert Acknowledge Timeout",
				"ipmi_serial17_alert_ack_timeout", FT_UINT8, BASE_CUSTOM, CF_FUNC(ipmi_fmt_1s_0based), 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial17_dialstr_sel,
			{ "Dial String Selector",
				"ipmi_serial17_dialstr_sel", FT_UINT8, BASE_DEC, NULL, 0xf0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial17_tap_sel,
			{ "TAP Account Selector",
				"ipmi_serial17_tap_sel", FT_UINT8, BASE_DEC, NULL, 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_serial17_ipaddr_sel,
			{ "Destination IP Address Selector",
				"ipmi_serial17_ipaddr_sel", FT_UINT8, BASE_DEC, NULL, 0xf0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial17_ppp_sel,
			{ "PPP Account Set Selector",
				"ipmi_serial17_ppp_sel", FT_UINT8, BASE_DEC, NULL, 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_serial17_unknown,
			{ "Destination-specific (format unknown)",
				"ipmi_serial17_unknown", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial18_call_retry,
			{ "Call Retry Interval",
				"ipmi_serial18_call_retry", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial19_destsel,
			{ "Destination selector",
				"ipmi_serial19_destsel", FT_UINT8, BASE_DEC, NULL, 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_serial19_flowctl,
			{ "Flow Control",
				"ipmi_serial19_flowctl", FT_UINT8, BASE_HEX, VALS(serialXX_flowctl_vals), 0xc0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial19_dtrhangup,
			{ "DTR Hang-up",
				"ipmi_serial19_dtrhangup", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x20, NULL, HFILL }},
		{ &hf_ipmi_trn_serial19_stopbits,
			{ "Stop bits",
				"ipmi_serial19_stopbits", FT_BOOLEAN, 8, TFS(&serial19_stopbits_tfs), 0x10, NULL, HFILL }},
		{ &hf_ipmi_trn_serial19_charsize,
			{ "Character size",
				"ipmi_serial19_charsize", FT_BOOLEAN, 8, TFS(&serial19_charsize_tfs), 0x08, NULL, HFILL }},
		{ &hf_ipmi_trn_serial19_parity,
			{ "Parity",
				"ipmi_serial19_parity", FT_UINT8, BASE_HEX, VALS(serial19_parity_vals), 0x07, NULL, HFILL }},
		{ &hf_ipmi_trn_serial19_bitrate,
			{ "Bit rate",
				"ipmi_serial19_bitrate", FT_UINT8, BASE_HEX, VALS(serialXX_bitrate_vals), 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_serial20_num_dial_strings,
			{ "Number of Dial Strings",
				"ipmi_serial20_num_dial_strings", FT_UINT8, BASE_DEC, NULL, 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_serial21_dialsel,
			{ "Dial String Selector",
				"ipmi_serial21_dialsel", FT_UINT8, BASE_DEC, NULL, 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_serial21_blockno,
			{ "Block number",
				"ipmi_serial21_blockno", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial21_dialstr,
			{ "Dial string",
				"ipmi_serial21_dialstr", FT_STRING, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial22_num_ipaddrs,
			{ "Number of Alert Destination IP Addresses",
				"ipmi_serial22_num_ipaddrs", FT_UINT8, BASE_DEC, NULL, 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_serial23_destsel,
			{ "Destination IP Address selector",
				"ipmi_serial23_destsel", FT_UINT8, BASE_DEC, NULL, 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_serial23_ipaddr,
			{ "Destination IP Address",
				"ipmi_serial23_ipaddr", FT_IPv4, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial24_num_tap_accounts,
			{ "Number of TAP Accounts",
				"ipmi_serial24_num_tap_accounts", FT_UINT8, BASE_DEC, NULL, 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_serial25_tap_acct,
			{ "TAP Account Selector",
				"ipmi_serial25_tap_acct", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial25_dialstr_sel,
			{ "Dial String Selector",
				"ipmi_serial25_dialstr_sel", FT_UINT8, BASE_DEC, NULL, 0xf0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial25_tapsrv_sel,
			{ "TAP Service Settings Selector",
				"ipmi_serial25_tapsrv_sel", FT_UINT8, BASE_DEC, NULL, 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_serial26_tap_acct,
			{ "TAP Account Selector",
				"ipmi_serial26_tap_acct", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial26_tap_passwd,
			{ "TAP Password",
				"ipmi_serial26_tap_passwd", FT_STRING, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial27_tap_acct,
			{ "TAP Account Selector",
				"ipmi_serial27_tap_acct", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial27_tap_pager_id,
			{ "TAP Pager ID String",
				"ipmi_serial27_tap_pager_id", FT_STRING, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial28_tapsrv_sel,
			{ "TAP Service Settings Selector",
				"ipmi_serial28_tapsrv_sel", FT_UINT8, BASE_DEC, NULL, 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_serial28_confirm,
			{ "TAP Confirmation",
				"ipmi_serial28_confirm", FT_UINT8, BASE_HEX, VALS(serial28_confirm_vals), 0x03, NULL, HFILL }},
		{ &hf_ipmi_trn_serial28_srvtype,
			{ "TAP 'SST' Service Type",
				"ipmi_serial28_srvtype", FT_STRING, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial28_ctrl_esc,
			{ "TAP Control-character escaping mask",
				"ipmi_serial28_ctrl_esc", FT_UINT32, BASE_HEX, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial28_t2,
			{ "TAP T2",
				"ipmi_serial28_tap_t2", FT_UINT8, BASE_CUSTOM, CF_FUNC(ipmi_fmt_500ms_0based), 0xf0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial28_t1,
			{ "TAP T1",
				"ipmi_serial28_tap_t1", FT_UINT8, BASE_CUSTOM, CF_FUNC(ipmi_fmt_1s_0based), 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_serial28_t4,
			{ "TAP T4",
				"ipmi_serial28_tap_t4", FT_UINT8, BASE_CUSTOM, CF_FUNC(ipmi_fmt_1s_0based), 0xf0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial28_t3,
			{ "TAP T3",
				"ipmi_serial28_tap_t3", FT_UINT8, BASE_CUSTOM, CF_FUNC(ipmi_fmt_2s_0based), 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_serial28_t6,
			{ "IPMI T6",
				"ipmi_serial28_ipmi_t6", FT_UINT8, BASE_CUSTOM, CF_FUNC(ipmi_fmt_1s_0based), 0xf0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial28_t5,
			{ "TAP T5",
				"ipmi_serial28_tap_t5", FT_UINT8, BASE_CUSTOM, CF_FUNC(ipmi_fmt_2s_0based), 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_serial28_n2,
			{ "TAP N2",
				"ipmi_serial28_tap_n2", FT_UINT8, BASE_DEC, NULL, 0xf0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial28_n1,
			{ "TAP N1",
				"ipmi_serial28_tap_n1", FT_UINT8, BASE_DEC, NULL, 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_serial28_n4,
			{ "IPMI N4",
				"ipmi_serial28_ipmi_n4", FT_UINT8, BASE_DEC, NULL, 0xf0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial28_n3,
			{ "TAP N3",
				"ipmi_serial28_tap_n3", FT_UINT8, BASE_DEC, NULL, 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_serial29_op,
			{ "Parameter Operation",
				"ipmi_serial29_op", FT_UINT8, BASE_HEX, VALS(serial29_op_vals), 0xc0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial29_lineedit,
			{ "Line Editing",
				"ipmi_serial29_lineedit", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x20, NULL, HFILL }},
		{ &hf_ipmi_trn_serial29_deletectl,
			{ "Delete control",
				"ipmi_serial29_deletectl", FT_UINT8, BASE_HEX, VALS(serial29_delete_vals), 0x0c, NULL, HFILL }},
		{ &hf_ipmi_trn_serial29_echo,
			{ "Echo",
				"ipmi_serial29_echo", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x02, NULL, HFILL }},
		{ &hf_ipmi_trn_serial29_handshake,
			{ "Handshake",
				"ipmi_serial29_handshake", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x01, NULL, HFILL }},
		{ &hf_ipmi_trn_serial29_o_newline,
			{ "Output newline sequence",
				"ipmi_serial29_o_newline", FT_UINT8, BASE_HEX, VALS(serial29_o_nl_vals), 0xf0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial29_i_newline,
			{ "Input newline sequence",
				"ipmi_serial29_i_newline", FT_UINT8, BASE_HEX, VALS(serial29_i_nl_vals), 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_serial30_snooping,
			{ "System Negotiation Snooping",
				"ipmi_serial30_snooping", FT_BOOLEAN, 8, NULL, 0x04, NULL, HFILL }},
		{ &hf_ipmi_trn_serial30_snoopctl,
			{ "Snoop ACCM Control",
				"ipmi_serial30_snoopctl", FT_UINT8, BASE_HEX, VALS(serial30_snoopctl_vals), 0x03, NULL, HFILL }},
		{ &hf_ipmi_trn_serial30_negot_ctl,
			{ "BMC negotiates link parameters",
				"ipmi_serial30_negot_ctl", FT_UINT8, BASE_HEX, VALS(serial30_negoctl_vals), 0x30, NULL, HFILL }},
		{ &hf_ipmi_trn_serial30_use_xmit_accm,
			{ "Filtering incoming chars",
				"ipmi_serial30_filter", FT_BOOLEAN, 8, TFS(&serial30_filter_tfs), 0x04, NULL, HFILL }},
		{ &hf_ipmi_trn_serial30_xmit_addr_comp,
			{ "Transmit with Address and Ctl Field Compression",
				"ipmi_serial30_xmit_addr_comp", FT_BOOLEAN, 8, NULL, 0x02, NULL, HFILL }},
		{ &hf_ipmi_trn_serial30_xmit_proto_comp,
			{ "Transmit with Protocol Field Compression",
				"ipmi_serial30_xmit_proto_comp", FT_BOOLEAN, 8, NULL, 0x01, NULL, HFILL }},
		{ &hf_ipmi_trn_serial30_ipaddr,
			{ "IP Address negotiation",
				"ipmi_serial30_ipaddr", FT_UINT8, BASE_HEX, VALS(serial30_ipaddr_val), 0x18, NULL, HFILL }},
		{ &hf_ipmi_trn_serial30_accm,
			{ "ACCM Negotiation",
				"ipmi_serial30_accm", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x04, NULL, HFILL }},
		{ &hf_ipmi_trn_serial30_addr_comp,
			{ "Address and Ctl Field Compression",
				"ipmi_serial30_addr_comp", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x02, NULL, HFILL }},
		{ &hf_ipmi_trn_serial30_proto_comp,
			{ "Protocol Field Compression",
				"ipmi_serial30_proto_comp", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x01, NULL, HFILL }},
		{ &hf_ipmi_trn_serial31_port,
			{ "Primary RMCP Port Number",
				"ipmi_serial31_port", FT_UINT16, BASE_CUSTOM, CF_FUNC(ipmi_fmt_udpport), 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial32_port,
			{ "Secondary RMCP Port Number",
				"ipmi_serial32_port", FT_UINT16, BASE_CUSTOM, CF_FUNC(ipmi_fmt_udpport), 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial33_auth_proto,
			{ "PPP Link Authentication Protocol",
				"ipmi_serial33_auth_proto", FT_UINT8, BASE_HEX, VALS(serialXX_proto_vals), 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_serial34_chap_name,
			{ "CHAP Name",
				"ipmi_serial34_chap_name", FT_STRING, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial35_recv_accm,
			{ "Receive ACCM",
				"ipmi_serial35_recv_accm", FT_UINT32, BASE_HEX, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial35_xmit_accm,
			{ "Transmit ACCM",
				"ipmi_serial35_xmit_accm", FT_UINT32, BASE_HEX, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial36_snoop_accm,
			{ "Snoop Receive ACCM",
				"ipmi_serial36_snoop_accm", FT_UINT32, BASE_HEX, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial37_num_ppp,
			{ "Number of PPP Accounts",
				"ipmi_serial37_num_ppp", FT_UINT8, BASE_DEC, NULL, 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_serial38_acct_sel,
			{ "PPP Account Selector",
				"ipmi_serial38_acct_sel", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial38_dialstr_sel,
			{ "Dial String Selector",
				"ipmi_serial38_dialstr_sel", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial39_acct_sel,
			{ "PPP Account Selector",
				"ipmi_serial39_acct_sel", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial39_ipaddr,
			{ "IP Address",
				"ipmi_serial39_ipaddr", FT_IPv4, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial40_acct_sel,
			{ "PPP Account Selector",
				"ipmi_serial40_acct_sel", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial40_username,
			{ "User Name",
				"ipmi_serial40_username", FT_STRING, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial41_acct_sel,
			{ "PPP Account Selector",
				"ipmi_serial41_acct_sel", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial41_userdomain,
			{ "User Domain",
				"ipmi_serial41_userdomain", FT_STRING, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial42_acct_sel,
			{ "PPP Account Selector",
				"ipmi_serial42_acct_sel", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial42_userpass,
			{ "User Password",
				"ipmi_serial42_userpass", FT_STRING, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial43_acct_sel,
			{ "PPP Account Selector",
				"ipmi_serial43_acct_sel", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial43_auth_proto,
			{ "Link Auth Type",
				"ipmi_serial43_auth_proto", FT_UINT8, BASE_HEX, VALS(serialXX_proto_vals), 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_serial44_acct_sel,
			{ "PPP Account Selector",
				"ipmi_serial44_acct_sel", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial44_hold_time,
			{ "Connection Hold Time",
				"ipmi_serial44_hold_time", FT_UINT8, BASE_CUSTOM, CF_FUNC(ipmi_fmt_1s_1based), 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial45_src_ipaddr,
			{ "Source IP Address",
				"ipmi_serial45_src_ipaddr", FT_IPv4, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial45_dst_ipaddr,
			{ "Destination IP Address",
				"ipmi_serial45_dst_ipaddr", FT_IPv4, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial46_tx_bufsize,
			{ "Transmit Buffer Size",
				"ipmi_serial46_tx_size", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial47_rx_bufsize,
			{ "Receive Buffer Size",
				"ipmi_serial47_rx_size", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial48_ipaddr,
			{ "Remote Console IP Address",
				"ipmi_serial48_ipaddr", FT_IPv4, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial49_blockno,
			{ "Block number",
				"ipmi_serial49_blockno", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial49_dialstr,
			{ "Dial string",
				"ipmi_serial49_dialstr", FT_STRING, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial50_115200,
			{ "115200",
				"ipmi_serial50_115200", FT_BOOLEAN, 8, NULL, 0x10, NULL, HFILL }},
		{ &hf_ipmi_trn_serial50_57600,
			{ "57600",
				"ipmi_serial50_57600", FT_BOOLEAN, 8, NULL, 0x08, NULL, HFILL }},
		{ &hf_ipmi_trn_serial50_38400,
			{ "38400",
				"ipmi_serial50_38400", FT_BOOLEAN, 8, NULL, 0x04, NULL, HFILL }},
		{ &hf_ipmi_trn_serial50_19200,
			{ "19200",
				"ipmi_serial50_19200", FT_BOOLEAN, 8, NULL, 0x02, NULL, HFILL }},
		{ &hf_ipmi_trn_serial50_9600,
			{ "9600",
				"ipmi_serial50_9600", FT_BOOLEAN, 8, NULL, 0x01, NULL, HFILL }},
		{ &hf_ipmi_trn_serial51_port_assoc_sel,
			{ "Serial Port Association Entry",
				"ipmi_serial51_port_assoc_sel", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial51_ipmi_channel,
			{ "IPMI Channel",
				"ipmi_serial51_ipmi_channel", FT_UINT8, BASE_CUSTOM, CF_FUNC(ipmi_fmt_channel), 0xf0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial51_conn_num,
			{ "Connector number",
				"ipmi_serial51_conn_num", FT_UINT8, BASE_DEC, NULL, 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_serial51_ipmi_sharing,
			{ "Used with IPMI Serial Port Sharing",
				"ipmi_serial51_ipmi_sharing", FT_BOOLEAN, 8, NULL, 0x80, NULL, HFILL }},
		{ &hf_ipmi_trn_serial51_ipmi_sol,
			{ "Used with IPMI Serial-over-LAN",
				"ipmi_serial51_ipmi_sol", FT_BOOLEAN, 8, NULL, 0x40, NULL, HFILL }},
		{ &hf_ipmi_trn_serial51_chan_num,
			{ "Serial controller channel number",
				"ipmi_serial51_chan_num", FT_UINT8, BASE_DEC, NULL, 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_serial52_port_assoc_sel,
			{ "Serial Port Association Entry",
				"ipmi_serial52_port_assoc_sel", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial52_conn_name,
			{ "Connector Name",
				"ipmi_serial52_conn_name", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial53_port_assoc_sel,
			{ "Serial Port Association Entry",
				"ipmi_serial53_port_assoc_sel", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_serial53_chan_name,
			{ "Channel Name",
				"ipmi_serial52_chan_name", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_01_chan,
			{ "Channel",
				"ipmi_tr01_chan", FT_UINT8, BASE_CUSTOM, CF_FUNC(ipmi_fmt_channel), 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_01_param,
			{ "Parameter Selector",
				"ipmi_tr01_param", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_01_param_data,
			{ "Parameter data",
				"ipmi_tr01_param_data", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_02_getrev,
			{ "Get parameter revision only",
				"ipmi_tr02_getrev", FT_BOOLEAN, 8, NULL, 0x80, NULL, HFILL }},
		{ &hf_ipmi_trn_02_chan,
			{ "Channel",
				"ipmi_tr02_chan", FT_UINT8, BASE_CUSTOM, CF_FUNC(ipmi_fmt_channel), 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_02_param,
			{ "Parameter selector",
				"ipmi_tr02_param", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_02_set,
			{ "Set selector",
				"ipmi_tr02_set", FT_UINT8, BASE_HEX, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_02_block,
			{ "Block selector",
				"ipmi_tr02_block", FT_UINT8, BASE_HEX, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_02_rev_present,
			{ "Present parameter revision",
				"ipmi_tr02_rev_present", FT_UINT8, BASE_DEC, NULL, 0xf0, NULL, HFILL }},
		{ &hf_ipmi_trn_02_rev_compat,
			{ "Oldest forward-compatible",
				"ipmi_tr02_rev_compat", FT_UINT8, BASE_DEC, NULL, 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_02_param_data,
			{ "Parameter data",
				"ipmi_tr02_param_data", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_03_chan,
			{ "Channel",
				"ipmi_tr03_chan", FT_UINT8, BASE_CUSTOM, CF_FUNC(ipmi_fmt_channel), 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_03_arp_resp,
			{ "BMC-generated ARP responses",
				"ipmi_tr03_arp_resp", FT_BOOLEAN, 8, TFS(&tfs_03_suspend), 0x02, NULL, HFILL }},
		{ &hf_ipmi_trn_03_gratuitous_arp,
			{ "Gratuitous ARPs",
				"ipmi_tr03_gratuitous_arp", FT_BOOLEAN, 8, TFS(&tfs_03_suspend), 0x01, NULL, HFILL }},
		{ &hf_ipmi_trn_03_status_arp_resp,
			{ "ARP Response status",
				"ipmi_tr03_status_arp_resp", FT_BOOLEAN, 8, TFS(&tfs_03_arp_status), 0x02, NULL, HFILL }},
		{ &hf_ipmi_trn_03_status_gratuitous_arp,
			{ "Gratuitous ARP status",
				"ipmi_tr03_status_gratuitous_arp", FT_BOOLEAN, 8, TFS(&tfs_03_arp_status), 0x01, NULL, HFILL }},

		{ &hf_ipmi_trn_04_chan,
			{ "Channel",
				"ipmi_tr04_chan", FT_UINT8, BASE_CUSTOM, CF_FUNC(ipmi_fmt_channel), 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_04_clear,
			{ "Statistics",
				"ipmi_tr04_clear", FT_BOOLEAN, 8, TFS(&tfs_04_clear), 0x01, NULL, HFILL }},
		{ &hf_ipmi_trn_04_rx_ippkts,
			{ "Received IP Packets",
				"ipmi_tr04_rx_ippkts", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_04_rx_iphdr_err,
			{ "Received IP Header Errors",
				"ipmi_tr04_rx_iphdr_err", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_04_rx_ipaddr_err,
			{ "Received IP Address Errors",
				"ipmi_tr04_rx_ipaddr_err", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_04_rx_ippkts_frag,
			{ "Received Fragmented IP Packets",
				"ipmi_tr04_rx_ippkts_frag", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_04_tx_ippkts,
			{ "Transmitted IP Packets",
				"ipmi_tr04_tx_ippkts", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_04_rx_udppkts,
			{ "Received UDP Packets",
				"ipmi_tr04_rx_udppkts", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_04_rx_validrmcp,
			{ "Received Valid RMCP Packets",
				"ipmi_tr04_rx_validrmcp", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_04_rx_udpproxy,
			{ "Received UDP Proxy Packets",
				"ipmi_tr04_rx_udpproxy", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_04_dr_udpproxy,
			{ "Dropped UDP Proxy Packets",
				"ipmi_tr04_dr_udpproxy", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_10_chan,
			{ "Channel",
				"ipmi_tr10_chan", FT_UINT8, BASE_CUSTOM, CF_FUNC(ipmi_fmt_channel), 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_10_param,
			{ "Parameter Selector",
				"ipmi_tr10_param", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_10_param_data,
			{ "Parameter data",
				"ipmi_tr10_param_data", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_11_getrev,
			{ "Get parameter revision only",
				"ipmi_tr11_getrev", FT_BOOLEAN, 8, NULL, 0x80, NULL, HFILL }},
		{ &hf_ipmi_trn_11_chan,
			{ "Channel",
				"ipmi_tr11_chan", FT_UINT8, BASE_CUSTOM, CF_FUNC(ipmi_fmt_channel), 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_11_param,
			{ "Parameter selector",
				"ipmi_tr11_param", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_11_set,
			{ "Set selector",
				"ipmi_tr11_set", FT_UINT8, BASE_HEX, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_11_block,
			{ "Block selector",
				"ipmi_tr11_block", FT_UINT8, BASE_HEX, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_11_rev_present,
			{ "Present parameter revision",
				"ipmi_tr11_rev_present", FT_UINT8, BASE_DEC, NULL, 0xf0, NULL, HFILL }},
		{ &hf_ipmi_trn_11_rev_compat,
			{ "Oldest forward-compatible",
				"ipmi_tr11_rev_compat", FT_UINT8, BASE_DEC, NULL, 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_11_param_data,
			{ "Parameter data",
				"ipmi_tr11_param_data", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_12_chan,
			{ "Channel",
				"ipmi_tr12_chan", FT_UINT8, BASE_CUSTOM, CF_FUNC(ipmi_fmt_channel), 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_12_mux_setting,
			{ "Mux Setting",
				"ipmi_tr12_mux_setting", FT_UINT8, BASE_HEX, VALS(vals_12_mux), 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_12_sw_to_sys,
			{ "Requests to switch to system",
				"ipmi_tr12_sw_to_sys", FT_BOOLEAN, 8, TFS(&tfs_12_blocked), 0x80, NULL, HFILL }},
		{ &hf_ipmi_trn_12_sw_to_bmc,
			{ "Requests to switch to BMC",
				"ipmi_tr12_sw_to_bmc", FT_BOOLEAN, 8, TFS(&tfs_12_blocked), 0x40, NULL, HFILL }},
		{ &hf_ipmi_trn_12_alert,
			{ "Alert in progress",
				"ipmi_tr12_alert", FT_BOOLEAN, 8, NULL, 0x08, NULL, HFILL }},
		{ &hf_ipmi_trn_12_msg,
			{ "IPMI/OEM messaging active",
				"ipmi_tr12_msg", FT_BOOLEAN, 8, NULL, 0x04, NULL, HFILL }},
		{ &hf_ipmi_trn_12_req,
			{ "Request",
				"ipmi_tr12_req", FT_BOOLEAN, 8, TFS(&tfs_12_req), 0x02, NULL, HFILL }},
		{ &hf_ipmi_trn_12_mux_state,
			{ "Mux set to",
				"ipmi_tr12_mux_state", FT_BOOLEAN, 8, TFS(&tfs_12_mux_state), 0x01, NULL, HFILL }},

		{ &hf_ipmi_trn_13_chan,
			{ "Channel",
				"ipmi_tr13_chan", FT_UINT8, BASE_CUSTOM, CF_FUNC(ipmi_fmt_channel), 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_13_code1,
			{ "Last code",
				"ipmi_tr13_code1", FT_STRING, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_13_code2,
			{ "2nd code",
				"ipmi_tr13_code2", FT_STRING, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_13_code3,
			{ "3rd code",
				"ipmi_tr13_code3", FT_STRING, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_13_code4,
			{ "4th code",
				"ipmi_tr13_code4", FT_STRING, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_13_code5,
			{ "5th code",
				"ipmi_tr13_code5", FT_STRING, BASE_NONE, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_14_chan,
			{ "Channel",
				"ipmi_tr14_chan", FT_UINT8, BASE_CUSTOM, CF_FUNC(ipmi_fmt_channel), 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_14_block,
			{ "Block number",
				"ipmi_tr14_block", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_14_data,
			{ "Block data",
				"ipmi_tr14_data", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_15_chan,
			{ "Channel",
				"ipmi_tr15_chan", FT_UINT8, BASE_CUSTOM, CF_FUNC(ipmi_fmt_channel), 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_15_block,
			{ "Block number",
				"ipmi_tr15_block", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_15_data,
			{ "Block data",
				"ipmi_tr15_data", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_16_chan,
			{ "Channel",
				"ipmi_tr16_chan", FT_UINT8, BASE_CUSTOM, CF_FUNC(ipmi_fmt_channel), 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_16_src_port,
			{ "Source Port",
				"ipmi_tr16_src_port", FT_UINT16, BASE_CUSTOM, CF_FUNC(ipmi_fmt_udpport), 0, NULL, HFILL }},
		{ &hf_ipmi_trn_16_dst_port,
			{ "Destination Port",
				"ipmi_tr16_dst_port", FT_UINT16, BASE_CUSTOM, CF_FUNC(ipmi_fmt_udpport), 0, NULL, HFILL }},
		{ &hf_ipmi_trn_16_src_addr,
			{ "Source IP Address",
				"ipmi_tr16_src_addr", FT_IPv4, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_16_dst_addr,
			{ "Destination IP Address",
				"ipmi_tr16_dst_addr", FT_IPv4, BASE_NONE, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_16_bytes,
			{ "Bytes to send",
				"ipmi_tr16_bytes", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_17_chan,
			{ "Channel",
				"ipmi_tr17_chan", FT_UINT8, BASE_CUSTOM, CF_FUNC(ipmi_fmt_channel), 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_17_clear,
			{ "Clear buffer",
				"ipmi_tr17_clear", FT_BOOLEAN, 8, NULL, 0x80, NULL, HFILL }},
		{ &hf_ipmi_trn_17_block_num,
			{ "Block number",
				"ipmi_tr17_block_num", FT_UINT8, BASE_CUSTOM, CF_FUNC(tr17_fmt_blockno), 0x7f, NULL, HFILL }},
		{ &hf_ipmi_trn_17_size,
			{ "Number of received bytes",
				"ipmi_tr17_size", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_17_data,
			{ "Block Data",
				"ipmi_tr17_data", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_18_state,
			{ "Session state",
				"ipmi_tr18_state", FT_UINT8, BASE_HEX, VALS(vals_18_state), 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_18_ipmi_ver,
			{ "IPMI Version",
				"ipmi_tr18_ipmi_ver", FT_UINT8, BASE_CUSTOM, CF_FUNC(ipmi_fmt_version), 0, NULL, HFILL }},

		{ &hf_ipmi_trn_19_chan,
			{ "Channel",
				"ipmi_tr19_chan", FT_UINT8, BASE_CUSTOM, CF_FUNC(ipmi_fmt_channel), 0x0f, NULL, HFILL }},
		{ &hf_ipmi_trn_19_dest_sel,
			{ "Destination selector",
				"ipmi_tr19_dest_sel", FT_UINT8, BASE_DEC, NULL, 0x0f, NULL, HFILL }},

		{ &hf_ipmi_trn_XX_cap_cbcp,
			{ "CBCP callback",
				"ipmi_trXX_cap_cbcp", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x02, NULL, HFILL }},
		{ &hf_ipmi_trn_XX_cap_ipmi,
			{ "IPMI callback",
				"ipmi_trXX_cap_ipmi", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x01, NULL, HFILL }},
		{ &hf_ipmi_trn_XX_cbcp_from_list,
			{ "Callback to one from list of numbers",
				"ipmi_trXX_cbcp_from_list", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x08, NULL, HFILL }},
		{ &hf_ipmi_trn_XX_cbcp_user,
			{ "Callback to user-specified number",
				"ipmi_trXX_cbcp_user", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x04, NULL, HFILL }},
		{ &hf_ipmi_trn_XX_cbcp_prespec,
			{ "Callback to pre-specified number",
				"ipmi_trXX_cbcp_prespec", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x02, NULL, HFILL }},
		{ &hf_ipmi_trn_XX_cbcp_nocb,
			{ "No callback",
				"ipmi_trXX_cbcp_nocb", FT_BOOLEAN, 8, TFS(&tfs_enabled_disabled), 0x01, NULL, HFILL }},
		{ &hf_ipmi_trn_XX_dst1,
			{ "Callback destination 1",
				"ipmi_trXX_dst1", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_XX_dst2,
			{ "Callback destination 2",
				"ipmi_trXX_dst2", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
		{ &hf_ipmi_trn_XX_dst3,
			{ "Callback destination 3",
				"ipmi_trXX_dst3", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},

		{ &hf_ipmi_trn_1a_user,
			{ "User ID",
				"ipmi_tr1a_user", FT_UINT8, BASE_DEC, NULL, 0x3f, NULL, HFILL }},
		{ &hf_ipmi_trn_1a_chan,
			{ "Channel",
				"ipmi_tr1a_chan", FT_UINT8, BASE_CUSTOM, CF_FUNC(ipmi_fmt_channel), 0x0f, NULL, HFILL }},

		{ &hf_ipmi_trn_1b_user,
			{ "User ID",
				"ipmi_tr1b_user", FT_UINT8, BASE_DEC, NULL, 0x3f, NULL, HFILL }},
		{ &hf_ipmi_trn_1b_chan,
			{ "Channel",
				"ipmi_tr1b_chan", FT_UINT8, BASE_CUSTOM, CF_FUNC(ipmi_fmt_channel), 0x0f, NULL, HFILL }},

	};
	static gint *ett[] = {
		&ett_ipmi_trn_lan00_byte1,
		&ett_ipmi_trn_lan01_byte1,
		&ett_ipmi_trn_lan02_byte1,
		&ett_ipmi_trn_lan02_byte2,
		&ett_ipmi_trn_lan02_byte3,
		&ett_ipmi_trn_lan02_byte4,
		&ett_ipmi_trn_lan02_byte5,
		&ett_ipmi_trn_lan04_byte1,
		&ett_ipmi_trn_lan07_byte2,
		&ett_ipmi_trn_lan07_byte3,
		&ett_ipmi_trn_lan10_byte1,
		&ett_ipmi_trn_lan17_byte1,
		&ett_ipmi_trn_lan18_byte1,
		&ett_ipmi_trn_lan18_byte2,
		&ett_ipmi_trn_lan18_byte4,
		&ett_ipmi_trn_lan19_byte1,
		&ett_ipmi_trn_lan19_byte2,
		&ett_ipmi_trn_lan19_byte3,
		&ett_ipmi_trn_lan20_byte12,
		&ett_ipmi_trn_lan21_byte1,
		&ett_ipmi_trn_lan22_byte1,
		&ett_ipmi_trn_lan24_byte1,
		&ett_ipmi_trn_lan24_byte2,
		&ett_ipmi_trn_lan24_byte3,
		&ett_ipmi_trn_lan24_byte4,
		&ett_ipmi_trn_lan24_byte5,
		&ett_ipmi_trn_lan24_byte6,
		&ett_ipmi_trn_lan24_byte7,
		&ett_ipmi_trn_lan24_byte8,
		&ett_ipmi_trn_lan25_byte1,
		&ett_ipmi_trn_lan25_byte2,
		&ett_ipmi_trn_lan25_byte34,
		&ett_ipmi_trn_lan50_byte1,
		&ett_ipmi_trn_lan55_byte3,
		&ett_ipmi_trn_lan56_byte2,
		&ett_ipmi_trn_lan64_byte1,
		&ett_ipmi_trn_serial03_byte1,
		&ett_ipmi_trn_serial04_byte1,
		&ett_ipmi_trn_serial05_byte1,
		&ett_ipmi_trn_serial05_byte2,
		&ett_ipmi_trn_serial06_byte1,
		&ett_ipmi_trn_serial07_byte1,
		&ett_ipmi_trn_serial07_byte2,
		&ett_ipmi_trn_serial08_byte1,
		&ett_ipmi_trn_serial08_byte2,
		&ett_ipmi_trn_serial09_byte1,
		&ett_ipmi_trn_serial09_byte2,
		&ett_ipmi_trn_serial16_byte1,
		&ett_ipmi_trn_serial17_byte1,
		&ett_ipmi_trn_serial17_byte2,
		&ett_ipmi_trn_serial17_byte4,
		&ett_ipmi_trn_serial17_byte5,
		&ett_ipmi_trn_serial19_byte1,
		&ett_ipmi_trn_serial19_byte2,
		&ett_ipmi_trn_serial19_byte3,
		&ett_ipmi_trn_serial20_byte1,
		&ett_ipmi_trn_serial21_byte1,
		&ett_ipmi_trn_serial22_byte1,
		&ett_ipmi_trn_serial23_byte1,
		&ett_ipmi_trn_serial24_byte1,
		&ett_ipmi_trn_serial25_byte2,
		&ett_ipmi_trn_serial28_byte1,
		&ett_ipmi_trn_serial28_byte2,
		&ett_ipmi_trn_serial28_byte10,
		&ett_ipmi_trn_serial28_byte11,
		&ett_ipmi_trn_serial28_byte12,
		&ett_ipmi_trn_serial28_byte13,
		&ett_ipmi_trn_serial28_byte14,
		&ett_ipmi_trn_serial29_byte1,
		&ett_ipmi_trn_serial29_byte2,
		&ett_ipmi_trn_serial30_byte1,
		&ett_ipmi_trn_serial30_byte2,
		&ett_ipmi_trn_serial30_byte3,
		&ett_ipmi_trn_serial33_byte1,
		&ett_ipmi_trn_serial37_byte1,
		&ett_ipmi_trn_serial43_byte1,
		&ett_ipmi_trn_serial50_byte1,
		&ett_ipmi_trn_serial51_byte2,
		&ett_ipmi_trn_serial51_byte3,
		&ett_ipmi_trn_01_byte1,
		&ett_ipmi_trn_02_byte1,
		&ett_ipmi_trn_02_rev,
		&ett_ipmi_trn_03_rq_byte1,
		&ett_ipmi_trn_03_rq_byte2,
		&ett_ipmi_trn_03_rs_byte1,
		&ett_ipmi_trn_04_byte1,
		&ett_ipmi_trn_04_byte2,
		&ett_ipmi_trn_10_byte1,
		&ett_ipmi_trn_11_byte1,
		&ett_ipmi_trn_11_rev,
		&ett_ipmi_trn_12_rq_byte1,
		&ett_ipmi_trn_12_rq_byte2,
		&ett_ipmi_trn_12_rs_byte1,
		&ett_ipmi_trn_13_byte1,
		&ett_ipmi_trn_14_byte1,
		&ett_ipmi_trn_15_byte1,
		&ett_ipmi_trn_16_byte1,
		&ett_ipmi_trn_17_byte1,
		&ett_ipmi_trn_17_byte2,
		&ett_ipmi_trn_18_byte1,
		&ett_ipmi_trn_19_byte1,
		&ett_ipmi_trn_19_byte2,
		&ett_ipmi_trn_XX_usercap,
		&ett_ipmi_trn_XX_cbcp,
		&ett_ipmi_trn_1a_byte1,
		&ett_ipmi_trn_1a_byte2,
		&ett_ipmi_trn_1b_byte1,
		&ett_ipmi_trn_1b_byte2,
		&ett_ipmi_trn_parameter
	};

	static ei_register_info ei[] = {
		{ &ei_ipmi_trn_02_request_param_rev, { "ipmi.tr02.request_param_rev", PI_PROTOCOL, PI_NOTE, "Requested parameter revision; parameter data returned", EXPFILL }},
		{ &ei_ipmi_trn_02_request_param_data, { "ipmi.tr02.mrequest_param_data", PI_PROTOCOL, PI_NOTE, "Requested parameter data; only parameter version returned", EXPFILL }},
		{ &ei_ipmi_trn_11_request_param_rev, { "ipmi.tr11.request_param_rev", PI_PROTOCOL, PI_NOTE, "Requested parameter revision; parameter data returned", EXPFILL }},
		{ &ei_ipmi_trn_11_request_param_data, { "ipmi.tr11.mrequest_param_data", PI_PROTOCOL, PI_NOTE, "Requested parameter data; only parameter version returned", EXPFILL }},
	};

	expert_module_t* expert_ipmi_trn;

	proto_register_field_array(proto_ipmi, hf, array_length(hf));
	proto_register_subtree_array(ett, array_length(ett));
	expert_ipmi_trn = expert_register_protocol(proto_ipmi);
	expert_register_field_array(expert_ipmi_trn, ei, array_length(ei));
	ipmi_register_netfn_cmdtab(IPMI_TRANSPORT_REQ, IPMI_OEM_NONE, NULL, 0, NULL,
			cmd_transport, array_length(cmd_transport));
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
