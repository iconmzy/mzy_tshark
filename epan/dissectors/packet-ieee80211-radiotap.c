/*
 *  packet-ieee80211-radiotap.c
 *	Decode packets with a Radiotap header
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * Copied from README.developer
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "config.h"

#include <errno.h>

#include <epan/packet.h>
#include <epan/capture_dissectors.h>
#include <wsutil/pint.h>
#include <epan/crc32-tvb.h>
#include <wsutil/frequency-utils.h>
#include <epan/tap.h>
#include <epan/prefs.h>
#include <epan/addr_resolv.h>
#include <epan/expert.h>
#include <epan/arptypes.h>
#include "packet-ieee80211.h"
#include "packet-ieee80211-radiotap-iter.h"

void proto_register_radiotap(void);
void proto_reg_handoff_radiotap(void);

/* protocol */
static int proto_radiotap = -1;

static int hf_radiotap_version = -1;
static int hf_radiotap_pad = -1;
static int hf_radiotap_length = -1;
static int hf_radiotap_present = -1;

static int hf_radiotap_tlv = -1;
static int hf_radiotap_tlv_type = -1;
static int hf_radiotap_tlv_datalen = -1;
static int hf_radiotap_unknown_tlv_data = -1;

static int hf_radiotap_mactime = -1;
/* static int hf_radiotap_channel = -1; */
static int hf_radiotap_channel_frequency = -1;
static int hf_radiotap_channel_flags = -1;
static int hf_radiotap_channel_flags_turbo = -1;
static int hf_radiotap_channel_flags_cck = -1;
static int hf_radiotap_channel_flags_ofdm = -1;
static int hf_radiotap_channel_flags_2ghz = -1;
static int hf_radiotap_channel_flags_5ghz = -1;
static int hf_radiotap_channel_flags_passive = -1;
static int hf_radiotap_channel_flags_dynamic = -1;
static int hf_radiotap_channel_flags_gfsk = -1;
static int hf_radiotap_channel_flags_gsm = -1;
static int hf_radiotap_channel_flags_sturbo = -1;
static int hf_radiotap_channel_flags_half = -1;
static int hf_radiotap_channel_flags_quarter = -1;
static int hf_radiotap_rxflags = -1;
static int hf_radiotap_rxflags_badplcp = -1;
static int hf_radiotap_txflags = -1;
static int hf_radiotap_txflags_fail = -1;
static int hf_radiotap_txflags_cts = -1;
static int hf_radiotap_txflags_rts = -1;
static int hf_radiotap_txflags_noack = -1;
static int hf_radiotap_txflags_noseqno = -1;
static int hf_radiotap_txflags_order = -1;
static int hf_radiotap_xchannel_channel = -1;
static int hf_radiotap_xchannel_frequency = -1;
static int hf_radiotap_xchannel_flags = -1;
static int hf_radiotap_xchannel_flags_turbo = -1;
static int hf_radiotap_xchannel_flags_cck = -1;
static int hf_radiotap_xchannel_flags_ofdm = -1;
static int hf_radiotap_xchannel_flags_2ghz = -1;
static int hf_radiotap_xchannel_flags_5ghz = -1;
static int hf_radiotap_xchannel_flags_passive = -1;
static int hf_radiotap_xchannel_flags_dynamic = -1;
static int hf_radiotap_xchannel_flags_gfsk = -1;
static int hf_radiotap_xchannel_flags_gsm = -1;
static int hf_radiotap_xchannel_flags_sturbo = -1;
static int hf_radiotap_xchannel_flags_half = -1;
static int hf_radiotap_xchannel_flags_quarter = -1;
static int hf_radiotap_xchannel_flags_ht20 = -1;
static int hf_radiotap_xchannel_flags_ht40u = -1;
static int hf_radiotap_xchannel_flags_ht40d = -1;
#if 0
static int hf_radiotap_xchannel_maxpower = -1;
#endif
static int hf_radiotap_fhss_hopset = -1;
static int hf_radiotap_fhss_pattern = -1;
static int hf_radiotap_datarate = -1;
static int hf_radiotap_antenna = -1;
static int hf_radiotap_dbm_antsignal = -1;
static int hf_radiotap_db_antsignal = -1;
static int hf_radiotap_dbm_antnoise = -1;
static int hf_radiotap_db_antnoise = -1;
static int hf_radiotap_tx_attenuation = -1;
static int hf_radiotap_db_tx_attenuation = -1;
static int hf_radiotap_txpower = -1;
static int hf_radiotap_vendor_ns = -1;
static int hf_radiotap_ven_oui = -1;
static int hf_radiotap_ven_subns = -1;
static int hf_radiotap_ven_skip = -1;
static int hf_radiotap_ven_item = -1;
static int hf_radiotap_ven_data = -1;
static int hf_radiotap_mcs = -1;
static int hf_radiotap_mcs_known = -1;
static int hf_radiotap_mcs_have_bw = -1;
static int hf_radiotap_mcs_have_index = -1;
static int hf_radiotap_mcs_have_gi = -1;
static int hf_radiotap_mcs_have_format = -1;
static int hf_radiotap_mcs_have_fec = -1;
static int hf_radiotap_mcs_have_stbc = -1;
static int hf_radiotap_mcs_have_ness = -1;
static int hf_radiotap_mcs_ness_bit1 = -1;
static int hf_radiotap_mcs_bw = -1;
static int hf_radiotap_mcs_index = -1;
static int hf_radiotap_mcs_gi = -1;
static int hf_radiotap_mcs_format = -1;
static int hf_radiotap_mcs_fec = -1;
static int hf_radiotap_mcs_stbc = -1;
static int hf_radiotap_mcs_ness_bit0 = -1;
static int hf_radiotap_ampdu = -1;
static int hf_radiotap_ampdu_ref = -1;
static int hf_radiotap_ampdu_flags = -1;
static int hf_radiotap_ampdu_flags_report_zerolen = -1;
static int hf_radiotap_ampdu_flags_is_zerolen = -1;
static int hf_radiotap_ampdu_flags_last_known = -1;
static int hf_radiotap_ampdu_flags_is_last = -1;
static int hf_radiotap_ampdu_flags_delim_crc_error = -1;
static int hf_radiotap_ampdu_delim_crc = -1;
static int hf_radiotap_ampdu_flags_eof_known = -1;
static int hf_radiotap_ampdu_flags_eof = -1;
static int hf_radiotap_vht = -1;
static int hf_radiotap_vht_known = -1;
static int hf_radiotap_vht_have_stbc = -1;
static int hf_radiotap_vht_have_txop_ps = -1;
static int hf_radiotap_vht_have_gi = -1;
static int hf_radiotap_vht_have_sgi_nsym_da = -1;
static int hf_radiotap_vht_have_ldpc_extra = -1;
static int hf_radiotap_vht_have_bf = -1;
static int hf_radiotap_vht_have_bw = -1;
static int hf_radiotap_vht_have_gid = -1;
static int hf_radiotap_vht_have_p_aid = -1;
static int hf_radiotap_vht_stbc = -1;
static int hf_radiotap_vht_txop_ps = -1;
static int hf_radiotap_vht_gi = -1;
static int hf_radiotap_vht_sgi_nsym_da = -1;
static int hf_radiotap_vht_ldpc_extra = -1;
static int hf_radiotap_vht_bf = -1;
static int hf_radiotap_vht_bw = -1;
static int hf_radiotap_vht_nsts[4] = { -1, -1, -1, -1 };
static int hf_radiotap_vht_mcs[4] = { -1, -1, -1, -1 };
static int hf_radiotap_vht_nss[4] = { -1, -1, -1, -1 };
static int hf_radiotap_vht_coding[4] = { -1, -1, -1, -1 };
static int hf_radiotap_vht_datarate[4] = { -1, -1, -1, -1 };
static int hf_radiotap_vht_gid = -1;
static int hf_radiotap_vht_p_aid = -1;
static int hf_radiotap_vht_user = -1;
static int hf_radiotap_timestamp = -1;
static int hf_radiotap_timestamp_ts = -1;
static int hf_radiotap_timestamp_accuracy = -1;
static int hf_radiotap_timestamp_unit = -1;
static int hf_radiotap_timestamp_spos = -1;
static int hf_radiotap_timestamp_flags_32bit = -1;
static int hf_radiotap_timestamp_flags_accuracy = -1;

/* "Present" flags */
static int hf_radiotap_present_word = -1;
static int hf_radiotap_present_tsft = -1;
static int hf_radiotap_present_flags = -1;
static int hf_radiotap_present_rate = -1;
static int hf_radiotap_present_channel = -1;
static int hf_radiotap_present_fhss = -1;
static int hf_radiotap_present_dbm_antsignal = -1;
static int hf_radiotap_present_dbm_antnoise = -1;
static int hf_radiotap_present_lock_quality = -1;
static int hf_radiotap_present_tx_attenuation = -1;
static int hf_radiotap_present_db_tx_attenuation = -1;
static int hf_radiotap_present_dbm_tx_power = -1;
static int hf_radiotap_present_antenna = -1;
static int hf_radiotap_present_db_antsignal = -1;
static int hf_radiotap_present_db_antnoise = -1;
static int hf_radiotap_present_hdrfcs = -1;
static int hf_radiotap_present_rxflags = -1;
static int hf_radiotap_present_txflags = -1;
static int hf_radiotap_present_xchannel = -1;
static int hf_radiotap_present_mcs = -1;
static int hf_radiotap_present_ampdu = -1;
static int hf_radiotap_present_vht = -1;
static int hf_radiotap_present_timestamp = -1;
static int hf_radiotap_present_he = -1;
static int hf_radiotap_present_he_mu = -1;
static int hf_radiotap_present_0_length_psdu = -1;
static int hf_radiotap_present_l_sig = -1;
static int hf_radiotap_present_tlv = -1;
static int hf_radiotap_present_rtap_ns = -1;
static int hf_radiotap_present_vendor_ns = -1;
static int hf_radiotap_present_ext = -1;

/* "present.flags" flags */
static int hf_radiotap_flags = -1;
static int hf_radiotap_flags_cfp = -1;
static int hf_radiotap_flags_preamble = -1;
static int hf_radiotap_flags_wep = -1;
static int hf_radiotap_flags_frag = -1;
static int hf_radiotap_flags_fcs = -1;
static int hf_radiotap_flags_datapad = -1;
static int hf_radiotap_flags_badfcs = -1;
static int hf_radiotap_flags_shortgi = -1;

static int hf_radiotap_quality = -1;
static int hf_radiotap_fcs = -1;
static int hf_radiotap_fcs_bad = -1;

/* HE Info fields */
static int hf_radiotap_he_ppdu_format = -1;
static int hf_radiotap_he_bss_color_known = -1;
static int hf_radiotap_he_beam_change_known = -1;
static int hf_radiotap_he_ul_dl_known = -1;
static int hf_radiotap_he_data_mcs_known = -1;
static int hf_radiotap_he_data_dcm_known = -1;
static int hf_radiotap_he_coding_known = -1;
static int hf_radiotap_he_ldpc_extra_symbol_segment_known = -1;
static int hf_radiotap_he_stbc_known = -1;
static int hf_radiotap_he_spatial_reuse_1_known = -1;
static int hf_radiotap_he_spatial_reuse_2_known = -1;
static int hf_radiotap_he_spatial_reuse_3_known = -1;
static int hf_radiotap_he_spatial_reuse_4_known = -1;
static int hf_radiotap_he_data_bw_ru_allocation_known = -1;
static int hf_radiotap_he_doppler_known = -1;
static int hf_radiotap_he_pri_sec_80_mhz_known = -1;
static int hf_radiotap_he_gi_known = -1;
static int hf_radiotap_he_num_ltf_symbols_known = -1;
static int hf_radiotap_he_pre_fec_padding_factor_known = -1;
static int hf_radiotap_he_txbf_known = -1;
static int hf_radiotap_he_pe_disambiguity_known = -1;
static int hf_radiotap_he_txop_known = -1;
static int hf_radiotap_he_midamble_periodicity_known = -1;
static int hf_radiotap_he_ru_allocation_offset = -1;
static int hf_radiotap_he_ru_allocation_offset_known = -1;
static int hf_radiotap_he_pri_sec_80_mhz = -1;
static int hf_radiotap_he_bss_color = -1;
static int hf_radiotap_he_bss_color_unknown = -1;
static int hf_radiotap_he_beam_change = -1;
static int hf_radiotap_he_beam_change_unknown = -1;
static int hf_radiotap_he_ul_dl = -1;
static int hf_radiotap_he_ul_dl_unknown = -1;
static int hf_radiotap_he_data_mcs = -1;
static int hf_radiotap_he_data_mcs_unknown = -1;
static int hf_radiotap_he_data_dcm = -1;
static int hf_radiotap_he_data_dcm_unknown = -1;
static int hf_radiotap_he_coding = -1;
static int hf_radiotap_he_coding_unknown = -1;
static int hf_radiotap_he_ldpc_extra_symbol_segment = -1;
static int hf_radiotap_he_ldpc_extra_symbol_segment_unknown = -1;
static int hf_radiotap_he_stbc = -1;
static int hf_radiotap_he_stbc_unknown = -1;
static int hf_radiotap_spatial_reuse = -1;
static int hf_radiotap_spatial_reuse_unknown = -1;
static int hf_radiotap_he_su_reserved = -1;
static int hf_radiotap_spatial_reuse_1 = -1;
static int hf_radiotap_spatial_reuse_1_unknown = -1;
static int hf_radiotap_spatial_reuse_2 = -1;
static int hf_radiotap_spatial_reuse_2_unknown = -1;
static int hf_radiotap_spatial_reuse_3 = -1;
static int hf_radiotap_spatial_reuse_3_unknown = -1;
static int hf_radiotap_spatial_reuse_4 = -1;
static int hf_radiotap_spatial_reuse_4_unknown = -1;
static int hf_radiotap_sta_id_user_captured = -1;
static int hf_radiotap_he_mu_reserved = -1;
static int hf_radiotap_data_bandwidth_ru_allocation = -1;
static int hf_radiotap_data_bandwidth_ru_allocation_unknown = -1;
static int hf_radiotap_gi = -1;
static int hf_radiotap_gi_unknown = -1;
static int hf_radiotap_ltf_symbol_size = -1;
static int hf_radiotap_ltf_symbol_size_unknown = -1;
static int hf_radiotap_num_ltf_symbols = -1;
static int hf_radiotap_num_ltf_symbols_unknown = -1;
static int hf_radiotap_d5_reserved_b11 = -1;
static int hf_radiotap_pre_fec_padding_factor = -1;
static int hf_radiotap_pre_fec_padding_factor_unknown = -1;
static int hf_radiotap_txbf = -1;
static int hf_radiotap_txbf_unknown = -1;
static int hf_radiotap_pe_disambiguity = -1;
static int hf_radiotap_pe_disambiguity_unknown = -1;
static int hf_radiotap_he_nsts = -1;
static int hf_radiotap_he_doppler_value = -1;
static int hf_radiotap_he_doppler_value_unknown = -1;
static int hf_radiotap_he_d6_reserved_00e0 = -1;
static int hf_radiotap_he_txop_value = -1;
static int hf_radiotap_he_txop_value_unknown = -1;
static int hf_radiotap_midamble_periodicity = -1;
static int hf_radiotap_midamble_periodicity_unknown = -1;
static int hf_radiotap_he_info_data_1 = -1;
static int hf_radiotap_he_info_data_2 = -1;
static int hf_radiotap_he_info_data_3 = -1;
static int hf_radiotap_he_info_data_4 = -1;
static int hf_radiotap_he_info_data_5 = -1;
static int hf_radiotap_he_info_data_6 = -1;
static int hf_radiotap_he_mu_sig_b_mcs = -1;
static int hf_radiotap_he_mu_sig_b_mcs_unknown = -1;
static int hf_radiotap_he_mu_sig_b_mcs_known = -1;
static int hf_radiotap_he_mu_sig_b_dcm = -1;
static int hf_radiotap_he_mu_sig_b_dcm_unknown = -1;
static int hf_radiotap_he_mu_sig_b_dcm_known = -1;
static int hf_radiotap_he_mu_chan2_center_26_tone_ru_bit_known = -1;
static int hf_radiotap_he_mu_chan2_center_26_tone_ru_bit_unknown = -1;
static int hf_radiotap_he_mu_chan1_rus_known = -1;
static int hf_radiotap_he_mu_chan1_rus_unknown = -1;
static int hf_radiotap_he_mu_chan2_rus_known = -1;
static int hf_radiotap_he_mu_chan2_rus_unknown = -1;
static int hf_radiotap_he_mu_reserved_f1_b10_b11 = -1;
static int hf_radiotap_he_mu_chan1_center_26_tone_ru_bit_known = -1;
static int hf_radiotap_he_mu_chan1_center_26_tone_ru_bit_unknown = -1;
static int hf_radiotap_he_mu_chan1_center_26_tone_ru_value = -1;
static int hf_radiotap_he_mu_sig_b_compression_known = -1;
static int hf_radiotap_he_mu_sig_b_compression_unknown = -1;
static int hf_radiotap_he_mu_sig_b_compression_from_sig_a = -1;
static int hf_radiotap_he_mu_sig_b_syms_mu_mimo_users_known = -1;
static int hf_radiotap_he_mu_sig_b_syms_mu_mimo_users_unknown = -1;
static int hf_radiotap_he_mu_info_flags_1 = -1;
static int hf_radiotap_he_mu_bw_from_bw_in_sig_a = -1;
static int hf_radiotap_he_mu_bw_from_bw_in_sig_a_unknown = -1;
static int hf_radiotap_he_mu_bw_from_bw_in_sig_a_known = -1;
static int hf_radiotap_he_mu_sig_b_syms_mu_mimo_users = -1;
static int hf_radiotap_he_mu_preamble_puncturing = -1;
static int hf_radiotap_he_mu_preamble_puncturing_unknown = -1;
static int hf_radiotap_he_mu_preamble_puncturing_known = -1;
static int hf_radiotap_he_mu_chan2_center_26_tone_ru_value = -1;
static int hf_radiotap_he_mu_reserved_f2_b12_b15 = -1;
static int hf_radiotap_he_mu_info_flags_2 = -1;
static int hf_radiotap_he_mu_chan1_rus_0 = -1;
static int hf_radiotap_he_mu_chan1_rus_0_unknown = -1;
static int hf_radiotap_he_mu_chan1_rus_1 = -1;
static int hf_radiotap_he_mu_chan1_rus_1_unknown = -1;
static int hf_radiotap_he_mu_chan1_rus_2 = -1;
static int hf_radiotap_he_mu_chan1_rus_2_unknown = -1;
static int hf_radiotap_he_mu_chan1_rus_3 = -1;
static int hf_radiotap_he_mu_chan1_rus_3_unknown = -1;
static int hf_radiotap_he_mu_chan2_rus_0 = -1;
static int hf_radiotap_he_mu_chan2_rus_0_unknown = -1;
static int hf_radiotap_he_mu_chan2_rus_1 = -1;
static int hf_radiotap_he_mu_chan2_rus_1_unknown = -1;
static int hf_radiotap_he_mu_chan2_rus_2 = -1;
static int hf_radiotap_he_mu_chan2_rus_2_unknown = -1;
static int hf_radiotap_he_mu_chan2_rus_3 = -1;
static int hf_radiotap_he_mu_chan2_rus_3_unknown = -1;

/* 0-length-psdu */
static int hf_radiotap_0_length_psdu_type = -1;

/* L-SIG */
static int hf_radiotap_l_sig_data_1 = -1;
static int hf_radiotap_l_sig_rate_known = -1;
static int hf_radiotap_l_sig_length_known = -1;
static int hf_radiotap_l_sig_reserved = -1;
static int hf_radiotap_l_sig_data_2 = -1;
static int hf_radiotap_l_sig_rate = -1;
static int hf_radiotap_l_sig_length = -1;

static gint ett_radiotap = -1;
static gint ett_radiotap_tlv = -1;
static gint ett_radiotap_present = -1;
static gint ett_radiotap_present_word = -1;
static gint ett_radiotap_flags = -1;
static gint ett_radiotap_rxflags = -1;
static gint ett_radiotap_txflags = -1;
static gint ett_radiotap_channel_flags = -1;
static gint ett_radiotap_xchannel_flags = -1;
static gint ett_radiotap_vendor = -1;
static gint ett_radiotap_mcs = -1;
static gint ett_radiotap_mcs_known = -1;
static gint ett_radiotap_ampdu = -1;
static gint ett_radiotap_ampdu_flags = -1;
static gint ett_radiotap_vht = -1;
static gint ett_radiotap_vht_known = -1;
static gint ett_radiotap_vht_user = -1;
static gint ett_radiotap_timestamp = -1;
static gint ett_radiotap_timestamp_flags = -1;
static gint ett_radiotap_he_info = -1;
static gint ett_radiotap_he_info_data_1 = -1;
static gint ett_radiotap_he_info_data_2 = -1;
static gint ett_radiotap_he_info_data_3 = -1;
static gint ett_radiotap_he_info_data_4 = -1;
static gint ett_radiotap_he_info_data_5 = -1;
static gint ett_radiotap_he_info_data_6 = -1;
static gint ett_radiotap_he_mu_info = -1;
static gint ett_radiotap_he_mu_info_flags_1 = -1;
static gint ett_radiotap_he_mu_info_flags_2 = -1;
static gint ett_radiotap_he_mu_chan_rus = -1;
static gint ett_radiotap_0_length_psdu = -1;
static gint ett_radiotap_l_sig = -1;
static gint ett_radiotap_l_sig_data_1 = -1;
static gint ett_radiotap_l_sig_data_2 = -1;
static gint ett_radiotap_unknown_tlv = -1;

static expert_field ei_radiotap_invalid_header_length = EI_INIT;
static expert_field ei_radiotap_data_past_header = EI_INIT;
static expert_field ei_radiotap_present = EI_INIT;
static expert_field ei_radiotap_invalid_data_rate = EI_INIT;

static dissector_handle_t ieee80211_radio_handle;

static capture_dissector_handle_t ieee80211_cap_handle;
static capture_dissector_handle_t ieee80211_datapad_cap_handle;

static dissector_table_t vendor_dissector_table;

/* Settings */
static gboolean radiotap_bit14_fcs = FALSE;
static gboolean radiotap_interpret_high_rates_as_mcs = FALSE;

#define USE_FCS_BIT        0
#define ASSUME_FCS_PRESENT 1
#define ASSUME_FCS_ABSENT  2
static const enum_val_t fcs_handling[] = {
	{ "use_fcs_bit", "Use the FCS bit", USE_FCS_BIT },
	{ "assume_fcs_present",  "Assume all packets have an FCS at the end", ASSUME_FCS_PRESENT },
	{ "assume_fcs_absent",  "Assume all packets don't have an FCS at the end", ASSUME_FCS_ABSENT },
	{ NULL, NULL, 0 }
};
static int radiotap_fcs_handling = USE_FCS_BIT;

#define BITNO_32(x) (((x) >> 16) ? 16 + BITNO_16((x) >> 16) : BITNO_16((x)))
#define BITNO_16(x) (((x) >> 8) ? 8 + BITNO_8((x) >> 8) : BITNO_8((x)))
#define BITNO_8(x)  (((x) >> 4) ? 4 + BITNO_4((x) >> 4) : BITNO_4((x)))
#define BITNO_4(x)  (((x) >> 2) ? 2 + BITNO_2((x) >> 2) : BITNO_2((x)))
#define BITNO_2(x)  (((x) & 2) ? 1 : 0)
#define BIT(n)	(1U << n)

/* not officially defined (yet) */
#define IEEE80211_RADIOTAP_F_SHORTGI	0x80
#define IEEE80211_RADIOTAP_XCHANNEL	18

/* Official specifcation:
 *
 * http://www.radiotap.org/
 *
 * Unofficial and historical specifications:
 * http://madwifi-project.org/wiki/DevDocs/RadiotapHeader
 * NetBSD's ieee80211_radiotap.h file
 */

/*
 * Useful combinations of channel characteristics.
 */
#define	IEEE80211_CHAN_FHSS \
	(IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_GFSK)
#define	IEEE80211_CHAN_DSSS \
	(IEEE80211_CHAN_2GHZ)
#define	IEEE80211_CHAN_A \
	(IEEE80211_CHAN_5GHZ | IEEE80211_CHAN_OFDM)
#define	IEEE80211_CHAN_B \
	(IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_CCK)
#define	IEEE80211_CHAN_PUREG \
	(IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_OFDM)
#define	IEEE80211_CHAN_G \
	(IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_DYN)
#define	IEEE80211_CHAN_108A \
	(IEEE80211_CHAN_A | IEEE80211_CHAN_TURBO)
#define	IEEE80211_CHAN_108G \
	(IEEE80211_CHAN_G | IEEE80211_CHAN_TURBO)
#define	IEEE80211_CHAN_108PUREG \
	(IEEE80211_CHAN_PUREG | IEEE80211_CHAN_TURBO)
#define	IEEE80211_CHAN_ST \
	(IEEE80211_CHAN_108A | IEEE80211_CHAN_STURBO)

#define MAX_MCS_VHT_INDEX	9
#define MAX_VHT_NSS             8

/*
 * Maps a VHT bandwidth index to ieee80211_vhtinfo.rates index.
 */
static const int ieee80211_vht_bw2rate_index[] = {
		/*  20Mhz total */	0,
		/*  40Mhz total */	1, 0, 0,
		/*  80Mhz total */	2, 1, 1, 0, 0, 0, 0,
		/* 160Mhz total */	3, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0
};

struct mcs_vht_valid {
	gboolean valid[4][MAX_VHT_NSS]; /* indexed by bandwidth and NSS-1 */
};

static const struct mcs_vht_valid ieee80211_vhtvalid[MAX_MCS_VHT_INDEX+1] = {
		/* MCS  0  */
		{
			{	/* 20 Mhz */  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
				/* 40 Mhz */  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
				/* 80 Mhz */  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
				/* 160 Mhz */ { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
			}
		},
		/* MCS  1  */
		{
			{	/* 20 Mhz */  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
				/* 40 Mhz */  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
				/* 80 Mhz */  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
				/* 160 Mhz */ { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
			}
		},
		/* MCS  2  */
		{
			{	/* 20 Mhz */  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
				/* 40 Mhz */  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
				/* 80 Mhz */  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
				/* 160 Mhz */ { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
			}
		},
		/* MCS  3  */
		{
			{	/* 20 Mhz */  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
				/* 40 Mhz */  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
				/* 80 Mhz */  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
				/* 160 Mhz */ { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
			}
		},
		/* MCS  4  */
		{
			{	/* 20 Mhz */  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
				/* 40 Mhz */  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
				/* 80 Mhz */  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
				/* 160 Mhz */ { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
			}
		},
		/* MCS  5  */
		{
			{	/* 20 Mhz */  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
				/* 40 Mhz */  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
				/* 80 Mhz */  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
				/* 160 Mhz */ { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
			}
		},
		/* MCS  6  */
		{
			{	/* 20 Mhz */  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
				/* 40 Mhz */  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
				/* 80 Mhz */  { TRUE,  TRUE,  FALSE, TRUE,  TRUE,  TRUE,  FALSE, TRUE },
				/* 160 Mhz */ { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
			}
		},
		/* MCS  7  */
		{
			{	/* 20 Mhz */  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
				/* 40 Mhz */  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
				/* 80 Mhz */  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
				/* 160 Mhz */ { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
			}
		},
		/* MCS  8  */
		{
			{	/* 20 Mhz */  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
				/* 40 Mhz */  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
				/* 80 Mhz */  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
				/* 160 Mhz */ { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
			}
		},
		/* MCS  9  */
		{
			{	/* 20 Mhz */  { FALSE, FALSE, TRUE,  FALSE, FALSE, TRUE,  FALSE, FALSE },
				/* 40 Mhz */  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
				/* 80 Mhz */  { TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  FALSE, TRUE,  TRUE },
				/* 160 Mhz */ { TRUE,  TRUE,  FALSE, TRUE,  TRUE,  TRUE,  TRUE,  TRUE },
			}
		}
};

struct mcs_vht_info {
	const char *modulation;
	const char *coding_rate;
	float       rates[4][2]; /* indexed by bandwidth and GI length */
};

static const struct mcs_vht_info ieee80211_vhtinfo[MAX_MCS_VHT_INDEX+1] = {
		/* MCS  0  */
		{	"BPSK",		"1/2",
				{		/* 20 Mhz */  {    6.5f,		/* SGI */    7.2f, },
						/* 40 Mhz */  {   13.5f,		/* SGI */   15.0f, },
						/* 80 Mhz */  {   29.3f,		/* SGI */   32.5f, },
						/* 160 Mhz */ {   58.5f,		/* SGI */   65.0f, }
				}
		},
		/* MCS  1  */
		{	"QPSK",		"1/2",
				{		/* 20 Mhz */  {   13.0f,		/* SGI */   14.4f, },
						/* 40 Mhz */  {   27.0f,		/* SGI */   30.0f, },
						/* 80 Mhz */  {   58.5f,		/* SGI */   65.0f, },
						/* 160 Mhz */ {  117.0f,		/* SGI */  130.0f, }
				}
		},
		/* MCS  2  */
		{	"QPSK",		"3/4",
				{		/* 20 Mhz */  {   19.5f,		/* SGI */   21.7f, },
						/* 40 Mhz */  {   40.5f,		/* SGI */   45.0f, },
						/* 80 Mhz */  {   87.8f,		/* SGI */   97.5f, },
						/* 160 Mhz */ {  175.5f,		/* SGI */  195.0f, }
				}
		},
		/* MCS  3  */
		{	"16-QAM",	"1/2",
				{		/* 20 Mhz */  {   26.0f,		/* SGI */   28.9f, },
						/* 40 Mhz */  {   54.0f,		/* SGI */   60.0f, },
						/* 80 Mhz */  {  117.0f,		/* SGI */  130.0f, },
						/* 160 Mhz */ {  234.0f,		/* SGI */  260.0f, }
				}
		},
		/* MCS  4  */
		{	"16-QAM",	"3/4",
				{		/* 20 Mhz */  {   39.0f,		/* SGI */   43.3f, },
						/* 40 Mhz */  {   81.0f,		/* SGI */   90.0f, },
						/* 80 Mhz */  {  175.5f,		/* SGI */  195.0f, },
						/* 160 Mhz */ {  351.0f,		/* SGI */  390.0f, }
				}
		},
		/* MCS  5  */
		{	"64-QAM",	"2/3",
				{		/* 20 Mhz */  {   52.0f,		/* SGI */   57.8f, },
						/* 40 Mhz */  {  108.0f,		/* SGI */  120.0f, },
						/* 80 Mhz */  {  234.0f,		/* SGI */  260.0f, },
						/* 160 Mhz */ {  468.0f,		/* SGI */  520.0f, }
				}
		},
		/* MCS  6  */
		{	"64-QAM",	"3/4",
				{		/* 20 Mhz */  {   58.5f,		/* SGI */   65.0f, },
						/* 40 Mhz */  {  121.5f,		/* SGI */  135.0f, },
						/* 80 Mhz */  {  263.3f,		/* SGI */  292.5f, },
						/* 160 Mhz */ {  526.5f,		/* SGI */  585.0f, }
				}
		},
		/* MCS  7  */
		{	"64-QAM",	"5/6",
				{		/* 20 Mhz */  {   65.0f,		/* SGI */   72.2f, },
						/* 40 Mhz */  {  135.0f,		/* SGI */  150.0f, },
						/* 80 Mhz */  {  292.5f,		/* SGI */  325.0f, },
						/* 160 Mhz */ {  585.0f,		/* SGI */  650.0f, }
				}
		},
		/* MCS  8  */
		{	"256-QAM",	"3/4",
				{		/* 20 Mhz */  {   78.0f,		/* SGI */   86.7f, },
						/* 40 Mhz */  {  162.0f,		/* SGI */  180.0f, },
						/* 80 Mhz */  {  351.0f,		/* SGI */  390.0f, },
						/* 160 Mhz */ {  702.0f,		/* SGI */  780.0f, }
				}
		},
		/* MCS  9  */
		{	"256-QAM",	"5/6",
				{		/* 20 Mhz */  {   86.7f,		/* SGI */   96.3f, },
						/* 40 Mhz */  {  180.0f,		/* SGI */  200.0f, },
						/* 80 Mhz */  {  390.0f,		/* SGI */  433.3f, },
						/* 160 Mhz */ {  780.0f,		/* SGI */  866.7f, }
				}
		}
};

/* In order by value */
static const value_string vht_bandwidth[] = {
	{ IEEE80211_RADIOTAP_VHT_BW_20,    "20 MHz" },
	{ IEEE80211_RADIOTAP_VHT_BW_40,    "40 MHz" },
	{ IEEE80211_RADIOTAP_VHT_BW_20L,   "20 MHz lower" },
	{ IEEE80211_RADIOTAP_VHT_BW_20U,   "20 MHz upper" },
	{ IEEE80211_RADIOTAP_VHT_BW_80,    "80 MHz" },
	{ IEEE80211_RADIOTAP_VHT_BW_40L,   "40 MHz lower" },
	{ IEEE80211_RADIOTAP_VHT_BW_40U,   "40 MHz upper" },
	{ IEEE80211_RADIOTAP_VHT_BW_20LL,  "20 MHz, channel 1/4" },
	{ IEEE80211_RADIOTAP_VHT_BW_20LU,  "20 MHz, channel 2/4" },
	{ IEEE80211_RADIOTAP_VHT_BW_20UL,  "20 MHz, channel 3/4" },
	{ IEEE80211_RADIOTAP_VHT_BW_20UU,  "20 MHz, channel 4/4" },
	{ IEEE80211_RADIOTAP_VHT_BW_160,   "160 MHz" },
	{ IEEE80211_RADIOTAP_VHT_BW_80L,   "80 MHz lower" },
	{ IEEE80211_RADIOTAP_VHT_BW_80U,   "80 MHz upper" },
	{ IEEE80211_RADIOTAP_VHT_BW_40LL,  "40 MHz, channel 1/4" },
	{ IEEE80211_RADIOTAP_VHT_BW_40LU,  "40 MHz, channel 2/4" },
	{ IEEE80211_RADIOTAP_VHT_BW_40UL,  "40 MHz, channel 3/4" },
	{ IEEE80211_RADIOTAP_VHT_BW_40UU,  "40 MHz, channel 4/4" },
	{ IEEE80211_RADIOTAP_VHT_BW_20LLL, "20 MHz, channel 1/8" },
	{ IEEE80211_RADIOTAP_VHT_BW_20LLU, "20 MHz, channel 2/8" },
	{ IEEE80211_RADIOTAP_VHT_BW_20LUL, "20 MHz, channel 3/8" },
	{ IEEE80211_RADIOTAP_VHT_BW_20LUU, "20 MHz, channel 4/8" },
	{ IEEE80211_RADIOTAP_VHT_BW_20ULL, "20 MHz, channel 5/8" },
	{ IEEE80211_RADIOTAP_VHT_BW_20ULU, "20 MHz, channel 6/8" },
	{ IEEE80211_RADIOTAP_VHT_BW_20UUL, "20 MHz, channel 7/8" },
	{ IEEE80211_RADIOTAP_VHT_BW_20UUU, "20 MHz, channel 8/8" },
	{ 0, NULL }
};
static value_string_ext vht_bandwidth_ext = VALUE_STRING_EXT_INIT(vht_bandwidth);

static const value_string mcs_bandwidth[] = {
	{ IEEE80211_RADIOTAP_MCS_BW_20,  "20 MHz" },
	{ IEEE80211_RADIOTAP_MCS_BW_40,  "40 MHz" },
	{ IEEE80211_RADIOTAP_MCS_BW_20L, "20 MHz lower" },
	{ IEEE80211_RADIOTAP_MCS_BW_20U, "20 MHz upper" },
	{0, NULL}
};

static const value_string mcs_format[] = {
	{ 0, "mixed" },
	{ 1, "greenfield" },
	{0, NULL},
};

static const value_string mcs_fec[] = {
	{ 0, "BCC" },
	{ 1, "LDPC" },
	{0, NULL}
};

static const value_string mcs_gi[] = {
	{ 0, "long" },
	{ 1, "short" },
	{0, NULL}
};

static const true_false_string preamble_type = {
	"Short",
	"Long",
};

static const value_string timestamp_unit[] = {
	{ IEEE80211_RADIOTAP_TS_UNIT_MSEC, "msec" },
	{ IEEE80211_RADIOTAP_TS_UNIT_USEC, "usec" },
	{ IEEE80211_RADIOTAP_TS_UNIT_NSEC, "nsec" },
	{ 0, NULL }
};

static const value_string timestamp_spos[] = {
	{ IEEE80211_RADIOTAP_TS_SPOS_MPDU, "first MPDU bit/symbol" },
	{ IEEE80211_RADIOTAP_TS_SPOS_ACQ, "signal acquisition" },
	{ IEEE80211_RADIOTAP_TS_SPOS_EOF, "end of frame" },
	{ IEEE80211_RADIOTAP_TS_SPOS_UNDEF, "undefined" },
	{ 0, NULL }
};

/*
 * The NetBSD ieee80211_radiotap man page
 * (http://netbsd.gw.com/cgi-bin/man-cgi?ieee80211_radiotap+9+NetBSD-current)
 * says:
 *
 *    Radiotap capture fields must be naturally aligned.  That is, 16-, 32-,
 *    and 64-bit fields must begin on 16-, 32-, and 64-bit boundaries, respec-
 *    tively.  In this way, drivers can avoid unaligned accesses to radiotap
 *    capture fields.  radiotap-compliant drivers must insert padding before a
 *    capture field to ensure its natural alignment.  radiotap-compliant packet
 *    dissectors, such as tcpdump(8), expect the padding.
 */

static gboolean
capture_radiotap(const guchar * pd, int offset, int len, capture_packet_info_t *cpinfo, const union wtap_pseudo_header *pseudo_header _U_)
{
	guint16 it_len;
	guint32 present, xpresent;
	guint8  rflags;
	const struct ieee80211_radiotap_header *hdr;

	if (!BYTES_ARE_IN_FRAME(offset, len,
				sizeof(struct ieee80211_radiotap_header))) {
		return FALSE;
	}
	hdr = (const struct ieee80211_radiotap_header *)pd;
	it_len = pletoh16(&hdr->it_len);
	if (!BYTES_ARE_IN_FRAME(offset, len, it_len))
		return FALSE;

	if (it_len > len) {
		/* Header length is bigger than total packet length */
		return FALSE;
	}

	if (it_len < sizeof(struct ieee80211_radiotap_header)) {
		/* Header length is shorter than fixed-length portion of header */
		return FALSE;
	}

	present = pletoh32(&hdr->it_present);
	offset += (int)sizeof(struct ieee80211_radiotap_header);
	it_len -= (int)sizeof(struct ieee80211_radiotap_header);

	/* skip over other present bitmaps */
	xpresent = present;
	while (xpresent & BIT(IEEE80211_RADIOTAP_EXT)) {
		if (!BYTES_ARE_IN_FRAME(offset, 4, it_len)) {
			return FALSE;
		}
		xpresent = pletoh32(pd + offset);
		offset += 4;
		it_len -= 4;
	}

	rflags = 0;

	/*
	 * IEEE80211_RADIOTAP_TSFT is the lowest-order bit,
	 * just skip over it.
	 */
	if (present & BIT(IEEE80211_RADIOTAP_TSFT)) {
		/* align it properly */
		if (offset & 7) {
			int pad = 8 - (offset & 7);
			offset += pad;
			it_len -= pad;
		}

		if (it_len < 8) {
			/* No room in header for this field. */
			return FALSE;
		}
		/* That field is present, and it's 8 bytes long. */
		offset += 8;
		it_len -= 8;
	}

	/*
	 * IEEE80211_RADIOTAP_FLAGS is the next bit.
	 */
	if (present & BIT(IEEE80211_RADIOTAP_FLAGS)) {
		if (it_len < 1) {
			/* No room in header for this field. */
			return FALSE;
		}
		/* That field is present; fetch it. */
		if (!BYTES_ARE_IN_FRAME(offset, len, 1)) {
			return FALSE;
		}
		rflags = pd[offset];
	}

	/* 802.11 header follows */
	if (rflags & IEEE80211_RADIOTAP_F_DATAPAD)
		return call_capture_dissector(ieee80211_datapad_cap_handle, pd, offset + it_len, len, cpinfo, pseudo_header);

	return call_capture_dissector(ieee80211_cap_handle, pd, offset + it_len, len, cpinfo, pseudo_header);
}

static const true_false_string tfs_known_unknown = {
	"Known",
	"Unknown"
};

static int * const data1_headers[] = {
	&hf_radiotap_he_ppdu_format,
	&hf_radiotap_he_bss_color_known,
	&hf_radiotap_he_beam_change_known,
	&hf_radiotap_he_ul_dl_known,
	&hf_radiotap_he_data_mcs_known,
	&hf_radiotap_he_data_dcm_known,
	&hf_radiotap_he_coding_known,
	&hf_radiotap_he_ldpc_extra_symbol_segment_known,
	&hf_radiotap_he_stbc_known,
	&hf_radiotap_he_spatial_reuse_1_known,
	&hf_radiotap_he_spatial_reuse_2_known,
	&hf_radiotap_he_spatial_reuse_3_known,
	&hf_radiotap_he_spatial_reuse_4_known,
	&hf_radiotap_he_data_bw_ru_allocation_known,
	&hf_radiotap_he_doppler_known,
	NULL
};

static const value_string he_pdu_format_vals[] = {
	{ IEEE80211_RADIOTAP_HE_PPDU_FORMAT_HE_SU,     "HE_SU" },
	{ IEEE80211_RADIOTAP_HE_PPDU_FORMAT_HE_EXT_SU, "HE_EXT_SU" },
	{ IEEE80211_RADIOTAP_HE_PPDU_FORMAT_HE_MU,     "HE_MU" },
	{ IEEE80211_RADIOTAP_HE_PPDU_FORMAT_HE_TRIG,   "HE_TRIG" },
	{ 0, NULL }
};

static int * const data2_headers[] = {
	&hf_radiotap_he_pri_sec_80_mhz_known,
	&hf_radiotap_he_gi_known,
	&hf_radiotap_he_num_ltf_symbols_known,
	&hf_radiotap_he_pre_fec_padding_factor_known,
	&hf_radiotap_he_txbf_known,
	&hf_radiotap_he_pe_disambiguity_known,
	&hf_radiotap_he_txop_known,
	&hf_radiotap_he_midamble_periodicity_known,
	&hf_radiotap_he_ru_allocation_offset,
	&hf_radiotap_he_ru_allocation_offset_known,
	&hf_radiotap_he_pri_sec_80_mhz,
	NULL
};

static const true_false_string tfs_pri_sec_80_mhz = {
	"secondary",
	"primary"
};

static const value_string he_coding_vals[] = {
	{ 0, "BCC" },
	{ 1, "LDPC" },
	{ 0, NULL }
};

static const value_string he_data_bw_ru_alloc_vals[] = {
	{ 0, "20" },
	{ 1, "40" },
	{ 2, "80" },
	{ 3, "160/80+80" },
	{ 4, "26-tone RU" },
	{ 5, "52-tone RU" },
	{ 6, "106-tone RU" },
	{ 7, "242-tone RU" },
	{ 8, "484-tone RU" },
	{ 9, "996-tone RU" },
	{ 10, "2x996-tone RU" },
	{ 11, "reserved" },
	{ 12, "reserved" },
	{ 13, "reserved" },
	{ 14, "reserved" },
	{ 15, "reserved" },
	{ 0, NULL }
};

static const value_string he_gi_vals[] = {
	{ 0, "0.8us" },
	{ 1, "1.6us" },
	{ 2, "3.2us" },
	{ 3, "reserved" },
	{ 0, NULL }
};

static const value_string he_ltf_symbol_size_vals[] = {
	{ 0, "unknown" },
	{ 1, "1x" },
	{ 2, "2x" },
	{ 3, "4x" },
	{ 0, NULL }
};

static const value_string he_num_ltf_symbols_vals[] = {
	{ 0, "1x" },
	{ 1, "2x" },
	{ 2, "4x" },
	{ 3, "6x" },
	{ 4, "8x" },
	{ 5, "reserved" },
	{ 6, "reserved" },
	{ 7, "reserved" },
	{ 0, NULL }
};

static const value_string he_nsts_vals[] = {
	{ 0, "Unknown" },
	{ 1, "1 space-time stream" },
	{ 2, "2 space-time streams" },
	{ 3, "3 space-time streams" },
	{ 4, "4 space-time streams" },
	{ 5, "5 space-time streams" },
	{ 6, "6 space-time streams" },
	{ 7, "7 space-time streams" },
	{ 8, "8 space-time streams" },
	{ 9, "9 space-time streams" },
	{ 10, "10 space-time streams" },
	{ 11, "11 space-time streams" },
	{ 12, "12 space-time streams" },
	{ 13, "13 space-time streams" },
	{ 14, "14 space-time streams" },
	{ 15, "15 space-time streams" },
	{ 0, NULL }
};

static const value_string he_midamble_periodicity_vals[] = {
	{ 0, "10" },
	{ 1, "20" },
	{ 0, NULL }
};

static void
dissect_radiotap_he_info(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree,
	int offset, struct ieee_802_11ax *info_11ax)
{
	guint16 ppdu_format = tvb_get_letohs(tvb, offset) &
		IEEE80211_RADIOTAP_HE_PPDU_FORMAT_MASK;
	proto_tree *he_info_tree = NULL;
	gboolean bss_color_known = FALSE;
	gboolean beam_change_known = FALSE;
	gboolean ul_dl_known = FALSE;
	gboolean data_mcs_known = FALSE;
	gboolean data_dcm_known = FALSE;
	gboolean coding_known = FALSE;
	gboolean ldpc_extra_symbol_segment_known = FALSE;
	gboolean stbc_known = FALSE;
	gboolean spatial_reuse_1_known = FALSE;
	gboolean spatial_reuse_2_known = FALSE;
	gboolean spatial_reuse_3_known = FALSE;
	gboolean spatial_reuse_4_known = FALSE;
	gboolean data_bw_ru_alloc_known = FALSE;
	gboolean doppler_known = FALSE;
	gboolean gi_known = FALSE;
	gboolean num_ltf_symbols_known = FALSE;
	gboolean ltf_symbol_size_known = FALSE;
	gboolean pre_fec_padding_factor_known = FALSE;
	gboolean txbf_known = FALSE;
	gboolean pe_disambiguity_known = FALSE;
	gboolean txop_known = FALSE;
	gboolean midamble_periodicity_known = FALSE;
	guint16 data1 = tvb_get_letohs(tvb, offset);
	guint16 data2 = 0;
	guint16 data3 = 0;
	guint16 data5 = 0;
	guint16 data6 = 0;

	guint8 ltf_symbol_size = 0;

	/*
	 * This is set differetly for each packet, depending on
	 * which values in data3 are known.  It thus will not
	 * work if it's static.
	 */
	int *data3_headers[] = {
		&hf_radiotap_he_bss_color,
		&hf_radiotap_he_beam_change,
		&hf_radiotap_he_ul_dl,
		&hf_radiotap_he_data_mcs,
		&hf_radiotap_he_data_dcm,
		&hf_radiotap_he_coding,
		&hf_radiotap_he_ldpc_extra_symbol_segment,
		&hf_radiotap_he_stbc,
		NULL
	};

	/*
	 * Same story but for data4.
	 */
	int *data4_he_trig_headers[] = {
		&hf_radiotap_spatial_reuse_1,
		&hf_radiotap_spatial_reuse_2,
		&hf_radiotap_spatial_reuse_3,
		&hf_radiotap_spatial_reuse_4,
		NULL
	};
	int *data4_he_su_and_he_ext_su_headers[] = {
		&hf_radiotap_spatial_reuse,
		&hf_radiotap_he_su_reserved,
		NULL
	};
	int *data4_he_mu_headers[] = {
		&hf_radiotap_spatial_reuse,
		&hf_radiotap_sta_id_user_captured,
		&hf_radiotap_he_mu_reserved,
		NULL
	};
	int *data5_headers[] = {
		&hf_radiotap_data_bandwidth_ru_allocation,
		&hf_radiotap_gi,
		&hf_radiotap_ltf_symbol_size,
		&hf_radiotap_num_ltf_symbols,
		&hf_radiotap_d5_reserved_b11,
		&hf_radiotap_pre_fec_padding_factor,
		&hf_radiotap_txbf,
		&hf_radiotap_pe_disambiguity,
		NULL
	};

	/*
	 * Same story, but for data6.
	 */
	int *data6_headers[] = {
		&hf_radiotap_he_nsts,
		&hf_radiotap_he_doppler_value,
		&hf_radiotap_he_d6_reserved_00e0,
		&hf_radiotap_he_txop_value,
		&hf_radiotap_midamble_periodicity,
		NULL
	};

	/*
	 * Determine what is known.
	 */
	if (data1 & IEEE80211_RADIOTAP_HE_BSS_COLOR_KNOWN)
		bss_color_known = TRUE;
	if (data1 & IEEE80211_RADIOTAP_HE_BEAM_CHANGE_KNOWN)
		beam_change_known = TRUE;
	if (data1 & IEEE80211_RADIOTAP_HE_UL_DL_KNOWN)
		ul_dl_known = TRUE;
	if (data1 & IEEE80211_RADIOTAP_HE_DATA_MCS_KNOWN)
		data_mcs_known = TRUE;
	if (data1 & IEEE80211_RADIOTAP_HE_DATA_DCM_KNOWN)
		data_dcm_known = TRUE;
	if (data1 & IEEE80211_RADIOTAP_HE_CODING_KNOWN)
		coding_known = TRUE;
	if (data1 & IEEE80211_RADIOTAP_HE_LDPC_EXTRA_SYMBOL_SEGMENT_KNOWN)
		ldpc_extra_symbol_segment_known = TRUE;
	if (data1 & IEEE80211_RADIOTAP_HE_STBC_KNOWN)
		stbc_known = TRUE;
	if (data1 & IEEE80211_RADIOTAP_HE_SPATIAL_REUSE_KNOWN)
		spatial_reuse_1_known = TRUE;
	if (data1 & IEEE80211_RADIOTAP_HE_SPATIAL_REUSE_2_KNOWN)
		spatial_reuse_2_known = TRUE;
	if (data1 & IEEE80211_RADIOTAP_HE_SPATIAL_REUSE_3_KNOWN)
		spatial_reuse_3_known = TRUE;
	if (data1 & IEEE80211_RADIOTAP_HE_SPATIAL_REUSE_4_KNOWN)
		spatial_reuse_4_known = TRUE;
	if (data1 & IEEE80211_RADIOTAP_HE_DATA_BW_RU_ALLOCATION_KNOWN)
		data_bw_ru_alloc_known = TRUE;
	if (data1 & IEEE80211_RADIOTAP_HE_DOPPLER_KNOWN)
		doppler_known = TRUE;

	he_info_tree = proto_tree_add_subtree(tree, tvb, offset, 12,
		ett_radiotap_he_info, NULL, "HE information");

	/* Add the bitmasks for each of D1 through D6 */
	proto_tree_add_bitmask(he_info_tree, tvb, offset,
		hf_radiotap_he_info_data_1, ett_radiotap_he_info_data_1,
		data1_headers, ENC_LITTLE_ENDIAN);
	offset += 2;

	data2 = tvb_get_letohs(tvb, offset);
	proto_tree_add_bitmask(he_info_tree, tvb, offset,
		hf_radiotap_he_info_data_2, ett_radiotap_he_info_data_2,
		data2_headers, ENC_LITTLE_ENDIAN);
	offset += 2;

	/*
	 * Second lot of what is known
	 */
	if (data2 & IEEE80211_RADIOTAP_HE_GI_KNOWN)
		gi_known = TRUE;
	if (data2 & IEEE80211_RADIOTAP_HE_NUM_LTF_SYMBOLS_KNOWN)
		num_ltf_symbols_known = TRUE;
	if (data2 & IEEE80211_RADIOTAP_HE_PRE_FEC_PADDING_FACTOR_KNOWN)
		pre_fec_padding_factor_known = TRUE;
	if (data2 & IEEE80211_RADIOTAP_HE_TXBF_KNOWN)
		txbf_known = TRUE;
	if (data2 & IEEE80211_RADIOTAP_HE_PE_DISAMBIGUITY_KNOWN)
		pe_disambiguity_known = TRUE;
	if (data2 & IEEE80211_RADIOTAP_HE_TXOP_KNOWN)
		txop_known = TRUE;
	if (data2 & IEEE80211_RADIOTAP_HE_MIDAMBLE_PERIODICITY_KNOWN)
		midamble_periodicity_known = TRUE;

	/*
	 * Set those fields that should be reserved
	 */
	if (!bss_color_known)
		data3_headers[0] = &hf_radiotap_he_bss_color_unknown;
	if (!beam_change_known)
		data3_headers[1] = &hf_radiotap_he_beam_change_unknown;
	if (!ul_dl_known)
		data3_headers[2] = &hf_radiotap_he_ul_dl_unknown;
	if (!data_mcs_known)
		data3_headers[3] = &hf_radiotap_he_data_mcs_unknown;
	if (!data_dcm_known)
		data3_headers[4] = &hf_radiotap_he_data_dcm_unknown;
	if (!coding_known)
		data3_headers[5] = &hf_radiotap_he_coding_unknown;
	if (!ldpc_extra_symbol_segment_known)
		data3_headers[6] = &hf_radiotap_he_ldpc_extra_symbol_segment_unknown;
	if (!stbc_known)
		data3_headers[7] = &hf_radiotap_he_stbc_unknown;

	data3 = tvb_get_letohs(tvb, offset);
	if (data_mcs_known) {
		info_11ax->has_mcs_index = TRUE;
		info_11ax->mcs = (data3 & IEEE80211_RADIOTAP_HE_DATA_MCS_MASK) >> 8;
	}
	proto_tree_add_bitmask(he_info_tree, tvb, offset,
		hf_radiotap_he_info_data_3, ett_radiotap_he_info_data_3,
		data3_headers, ENC_LITTLE_ENDIAN);
	offset += 2;

	if (ppdu_format == IEEE80211_RADIOTAP_HE_PPDU_FORMAT_HE_SU ||
		ppdu_format == IEEE80211_RADIOTAP_HE_PPDU_FORMAT_HE_EXT_SU) {
		if (!spatial_reuse_1_known)
			data4_he_su_and_he_ext_su_headers[0] =
				&hf_radiotap_spatial_reuse_unknown;
		proto_tree_add_bitmask(he_info_tree, tvb, offset,
			hf_radiotap_he_info_data_4, ett_radiotap_he_info_data_4,
			data4_he_su_and_he_ext_su_headers, ENC_LITTLE_ENDIAN);
	} else if (ppdu_format == IEEE80211_RADIOTAP_HE_PPDU_FORMAT_HE_TRIG) {
		if (!spatial_reuse_1_known)
			data4_he_trig_headers[0] =
				&hf_radiotap_spatial_reuse_1_unknown;
		if (!spatial_reuse_2_known)
			data4_he_trig_headers[1] =
				&hf_radiotap_spatial_reuse_2_unknown;
		if (!spatial_reuse_3_known)
			data4_he_trig_headers[2] =
				&hf_radiotap_spatial_reuse_3_unknown;
		if (!spatial_reuse_4_known)
			data4_he_trig_headers[3] =
				&hf_radiotap_spatial_reuse_4_unknown;
		proto_tree_add_bitmask(he_info_tree, tvb, offset,
			hf_radiotap_he_info_data_4, ett_radiotap_he_info_data_4,
			data4_he_trig_headers, ENC_LITTLE_ENDIAN);
	} else {
		if (!spatial_reuse_1_known)
			data4_he_mu_headers[0] =
				&hf_radiotap_spatial_reuse_unknown;
		proto_tree_add_bitmask(he_info_tree, tvb, offset,
			hf_radiotap_he_info_data_4, ett_radiotap_he_info_data_4,
			data4_he_mu_headers, ENC_LITTLE_ENDIAN);
	}

	//data4 = tvb_get_letohs(tvb, offset);
	offset += 2;

	/*
	 * The LTF Symbol Size field is zero if LFT Symbol size is unknown
	 */
	ltf_symbol_size = (tvb_get_letohs(tvb, offset) >> 6) & 0x03;
	if (ltf_symbol_size != 0)
		ltf_symbol_size_known = TRUE;
	if (!data_bw_ru_alloc_known)
		data5_headers[0] = &hf_radiotap_data_bandwidth_ru_allocation_unknown;
	if (!gi_known)
		data5_headers[1] = &hf_radiotap_gi_unknown;
	if (!ltf_symbol_size_known)
		data5_headers[2] = &hf_radiotap_ltf_symbol_size_unknown;
	if (!num_ltf_symbols_known)
		data5_headers[3] = &hf_radiotap_num_ltf_symbols_unknown;
	if (!pre_fec_padding_factor_known)
		data5_headers[5] = &hf_radiotap_pre_fec_padding_factor_unknown;
	if (!txbf_known)
		data5_headers[6] = &hf_radiotap_txbf_unknown;
	if (!pe_disambiguity_known)
		data5_headers[7] = &hf_radiotap_pe_disambiguity_unknown;
	data5 = tvb_get_letohs(tvb, offset);
	if (gi_known) {
		info_11ax->has_gi = TRUE;
		info_11ax->gi = (data5 & IEEE80211_RADIOTAP_HE_GI_MASK) >> 4;
	}
	if (data_bw_ru_alloc_known) {
		info_11ax->has_bwru = TRUE;
		info_11ax->bwru = (data5 & IEEE80211_RADIOTAP_HE_DATA_BANDWIDTH_RU_ALLOC_MASK);
	}
	proto_tree_add_bitmask(he_info_tree, tvb, offset,
		hf_radiotap_he_info_data_5, ett_radiotap_he_info_data_5,
		data5_headers, ENC_LITTLE_ENDIAN);
	offset += 2;

	if (!doppler_known)
		data6_headers[1] = &hf_radiotap_he_doppler_value_unknown;
	if (!txop_known)
		data6_headers[3] = &hf_radiotap_he_txop_value_unknown;
	if (!midamble_periodicity_known)
		data6_headers[4] = &hf_radiotap_midamble_periodicity_unknown;
	proto_tree_add_bitmask(he_info_tree, tvb, offset,
		hf_radiotap_he_info_data_6, ett_radiotap_he_info_data_6,
		data6_headers, ENC_LITTLE_ENDIAN);
	data6 = tvb_get_letohs(tvb, offset);

	info_11ax->nsts = data6 & IEEE80211_RADIOTAP_HE_NSTS_MASK;

}

static void
not_captured_custom(gchar *result, guint32 value _U_)
{
	g_snprintf(result, ITEM_LABEL_LENGTH,
		"NOT CAPTURED BY CAPTURE SOFTWARE");
}

static void
he_sig_b_symbols_custom(gchar *result, guint32 value)
{
	g_snprintf(result, ITEM_LABEL_LENGTH, "%d", value+1);
}

static void
dissect_radiotap_he_mu_info(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree,
	int offset)
{
	proto_tree *he_mu_info_tree = NULL;
	guint16 flags1 = tvb_get_letohs(tvb, offset);
	gboolean sig_b_mcs_known = FALSE;
	gboolean sig_b_dcm_known = FALSE;
	proto_tree *mu_chan1_rus = NULL;
	proto_tree *mu_chan2_rus = NULL;
	int mu_rus_chan1_rus_0 = -1;
	int mu_rus_chan1_rus_1 = -1;
	int mu_rus_chan1_rus_2 = -1;
	int mu_rus_chan1_rus_3 = -1;
	int mu_rus_chan2_rus_0 = -1;
	int mu_rus_chan2_rus_1 = -1;
	int mu_rus_chan2_rus_2 = -1;
	int mu_rus_chan2_rus_3 = -1;
	gboolean mu_chan2_center_26_tone_ru_bit_known = FALSE;
	gboolean mu_chan1_rus_known = FALSE;
	gboolean mu_chan2_rus_known = FALSE;
	gboolean mu_chan1_center_26_tone_ru_bit_known = FALSE;
	gboolean mu_sig_b_compression_known = FALSE;
	gboolean mu_symbol_cnt_or_user_cnt_known = FALSE;
	gboolean mu_preamble_puncturing_known = FALSE;
	gboolean mu_bw_from_bw_sig_a_known = FALSE;
	guint8 bw_from_sig_a = 0;
	guint16 flags2;

	/*
	 * This is set differetly for each packet, depending on
	 * which values in flags1 are known.  It thus will not
	 * work if it's static.
	 */
	int *flags1_headers[] = {
		&hf_radiotap_he_mu_sig_b_mcs,
		&hf_radiotap_he_mu_sig_b_mcs_known,
		&hf_radiotap_he_mu_sig_b_dcm,
		&hf_radiotap_he_mu_sig_b_dcm_known,
		&hf_radiotap_he_mu_chan2_center_26_tone_ru_bit_known,
		&hf_radiotap_he_mu_chan1_rus_known,
		&hf_radiotap_he_mu_chan2_rus_known,
		&hf_radiotap_he_mu_reserved_f1_b10_b11,
		&hf_radiotap_he_mu_chan1_center_26_tone_ru_bit_known,
		&hf_radiotap_he_mu_chan1_center_26_tone_ru_value,
		&hf_radiotap_he_mu_sig_b_compression_known,
		&hf_radiotap_he_mu_sig_b_syms_mu_mimo_users_known,
		NULL
	};

	/*
	 * Same story but for flags2.
	 */
	int *flags2_headers[] = {
		&hf_radiotap_he_mu_bw_from_bw_in_sig_a,
		&hf_radiotap_he_mu_bw_from_bw_in_sig_a_known,
		&hf_radiotap_he_mu_sig_b_compression_from_sig_a,
		&hf_radiotap_he_mu_sig_b_syms_mu_mimo_users,
		&hf_radiotap_he_mu_preamble_puncturing,
		&hf_radiotap_he_mu_preamble_puncturing_known,
		&hf_radiotap_he_mu_chan2_center_26_tone_ru_value,
		&hf_radiotap_he_mu_reserved_f2_b12_b15,
		NULL
	};

	if (flags1 & IEEE80211_RADIOTAP_HE_MU_SIG_B_MCS_KNOWN)
		sig_b_mcs_known = TRUE;
	if (flags1 & IEEE80211_RADIOTAP_HE_MU_SIG_B_DCM_KNOWN)
		sig_b_dcm_known = TRUE;
	if (flags1 & IEEE80211_RADIOTAP_HE_MU_CHAN2_CENTER_26_TONE_RU_BIT_KNOWN)
		mu_chan2_center_26_tone_ru_bit_known = TRUE;
	if (flags1 & IEEE80211_RADIOTAP_HE_MU_CHAN1_RUS_KNOWN)
		mu_chan1_rus_known = TRUE;
	if (flags1 & IEEE80211_RADIOTAP_HE_MU_CHAN2_RUS_KNOWN)
		mu_chan2_rus_known = TRUE;
	if (flags1 & IEEE80211_RADIOTAP_HE_MU_CHAN1_CENTER_26_TONE_RU_BIT_KNOWN)
		mu_chan1_center_26_tone_ru_bit_known = TRUE;
	if (flags1 & IEEE80211_RADIOTAP_HE_MU_SIG_B_COMPRESSION_KNOWN)
		mu_sig_b_compression_known = TRUE;
	if (flags1 & IEEE80211_RADIOTAP_HE_MU_SYMBOL_CNT_OR_USER_CNT_KNOWN)
		mu_symbol_cnt_or_user_cnt_known = TRUE;

	if (!sig_b_mcs_known) {
		flags1_headers[1] = &hf_radiotap_he_mu_sig_b_mcs_unknown;
	} else {
		flags1_headers[1] = &hf_radiotap_he_mu_sig_b_mcs_known;
	}
	if (!sig_b_dcm_known) {
		flags1_headers[3] = &hf_radiotap_he_mu_sig_b_dcm_unknown;
	} else {
		flags1_headers[3] = &hf_radiotap_he_mu_sig_b_dcm_known;
	}
	if (!mu_chan2_center_26_tone_ru_bit_known) {
		flags1_headers[4] = &hf_radiotap_he_mu_chan2_center_26_tone_ru_bit_unknown;
	} else {
		flags1_headers[4] = &hf_radiotap_he_mu_chan2_center_26_tone_ru_bit_known;
	}
	if (!mu_chan1_rus_known) {
		flags1_headers[5] = &hf_radiotap_he_mu_chan1_rus_unknown;
	} else {
		flags1_headers[5] = &hf_radiotap_he_mu_chan1_rus_known;
	}
	if (!mu_chan1_center_26_tone_ru_bit_known) {
		flags1_headers[8] = &hf_radiotap_he_mu_chan1_center_26_tone_ru_bit_unknown;
	} else {
		flags1_headers[8] = &hf_radiotap_he_mu_chan1_center_26_tone_ru_bit_known;
	}
	if (!mu_symbol_cnt_or_user_cnt_known) {
		flags1_headers[11] = &hf_radiotap_he_mu_sig_b_syms_mu_mimo_users_unknown;
	} else {
		flags1_headers[11] = &hf_radiotap_he_mu_sig_b_syms_mu_mimo_users_known;
	}

	if (!mu_chan1_center_26_tone_ru_bit_known) {
		flags1_headers[9] = &hf_radiotap_he_mu_chan1_center_26_tone_ru_bit_unknown;
	} else {
		flags1_headers[9] = &hf_radiotap_he_mu_chan1_center_26_tone_ru_value;
	}
	if (!mu_symbol_cnt_or_user_cnt_known) {
		flags1_headers[11] = &hf_radiotap_he_mu_sig_b_syms_mu_mimo_users_unknown;
	} else {
		flags1_headers[11] = &hf_radiotap_he_mu_sig_b_syms_mu_mimo_users_known;
	}

	flags2 = tvb_get_letohs(tvb, offset + 2);
	if (flags2 & IEEE80211_RADIOTAP_HE_MU_BW_FROM_BW_IN_SIG_A_KNOWN)
		mu_bw_from_bw_sig_a_known = TRUE;
	if (flags2 & IEEE80211_RADIOTAP_HE_MU_PREAMBLE_PUNCTURING_KNOWN)
		mu_preamble_puncturing_known = TRUE;

	if (!mu_bw_from_bw_sig_a_known) {
		flags2_headers[0] = &hf_radiotap_he_mu_bw_from_bw_in_sig_a_unknown;
	} else {
		flags2_headers[0] = &hf_radiotap_he_mu_bw_from_bw_in_sig_a;
	}
	if (!mu_sig_b_compression_known) {
		flags2_headers[2] = &hf_radiotap_he_mu_sig_b_compression_unknown;
	} else {
		flags2_headers[2] = &hf_radiotap_he_mu_sig_b_compression_from_sig_a;
	}
	if (!mu_symbol_cnt_or_user_cnt_known) {
		flags2_headers[3] = &hf_radiotap_he_mu_sig_b_syms_mu_mimo_users_unknown;
	} else {
		flags2_headers[3] = &hf_radiotap_he_mu_sig_b_syms_mu_mimo_users;
	}
	if (!mu_preamble_puncturing_known) {
		flags2_headers[4] = &hf_radiotap_he_mu_preamble_puncturing_unknown;
	} else {
		flags2_headers[4] = &hf_radiotap_he_mu_preamble_puncturing;
	}
	if (!mu_chan2_center_26_tone_ru_bit_known) {
		flags2_headers[6] = &hf_radiotap_he_mu_chan2_center_26_tone_ru_bit_unknown;
	} else {
		flags2_headers[6] = &hf_radiotap_he_mu_chan2_center_26_tone_ru_value;
	}

	bw_from_sig_a = flags2 & IEEE80211_RADIOTAP_HE_MU_BW_FROM_BW_IN_SIG_A_MASK;

	/*
	 * We have to hold of on displaying stuff until we have figured
	 * everything out because the display of fields in flags1 depends
	 *  on bandwidth from flags2.
	 */

	/* Set the header fields depending on the bw and known fields */
	if (bw_from_sig_a < 3) {
		if (mu_chan1_rus_known) {
			mu_rus_chan1_rus_0 = hf_radiotap_he_mu_chan1_rus_0;
			mu_rus_chan1_rus_1 = hf_radiotap_he_mu_chan1_rus_1;
			mu_rus_chan1_rus_2 = hf_radiotap_he_mu_chan1_rus_2;
			mu_rus_chan1_rus_3 = hf_radiotap_he_mu_chan1_rus_3;
		} else {
			mu_rus_chan1_rus_0 = hf_radiotap_he_mu_chan1_rus_0_unknown;
			mu_rus_chan1_rus_1 = hf_radiotap_he_mu_chan1_rus_1_unknown;
			mu_rus_chan1_rus_2 = hf_radiotap_he_mu_chan1_rus_2_unknown;
			mu_rus_chan1_rus_3 = hf_radiotap_he_mu_chan1_rus_3_unknown;
		}
		if (mu_chan2_rus_known) {
			mu_rus_chan2_rus_0 = hf_radiotap_he_mu_chan2_rus_0;
			mu_rus_chan2_rus_1 = hf_radiotap_he_mu_chan2_rus_1;
			mu_rus_chan2_rus_2 = hf_radiotap_he_mu_chan2_rus_2;
			mu_rus_chan2_rus_3 = hf_radiotap_he_mu_chan2_rus_3;
		} else {
			mu_rus_chan2_rus_0 = hf_radiotap_he_mu_chan2_rus_0_unknown;
			mu_rus_chan2_rus_1 = hf_radiotap_he_mu_chan2_rus_1_unknown;
			mu_rus_chan2_rus_2 = hf_radiotap_he_mu_chan2_rus_2_unknown;
			mu_rus_chan2_rus_3 = hf_radiotap_he_mu_chan2_rus_3_unknown;
		}
	} else {
		mu_rus_chan1_rus_0 = hf_radiotap_he_mu_chan1_rus_0;
		mu_rus_chan1_rus_1 = hf_radiotap_he_mu_chan1_rus_1;
		mu_rus_chan1_rus_2 = hf_radiotap_he_mu_chan1_rus_2;
		mu_rus_chan1_rus_3 = hf_radiotap_he_mu_chan1_rus_3;
		mu_rus_chan2_rus_0 = hf_radiotap_he_mu_chan2_rus_0;
		mu_rus_chan2_rus_1 = hf_radiotap_he_mu_chan2_rus_1;
		mu_rus_chan2_rus_2 = hf_radiotap_he_mu_chan2_rus_2;
		mu_rus_chan2_rus_3 = hf_radiotap_he_mu_chan2_rus_3;
	}

	he_mu_info_tree = proto_tree_add_subtree(tree, tvb, offset, 12,
		ett_radiotap_he_mu_info, NULL, "HE-MU information");

	proto_tree_add_bitmask(he_mu_info_tree, tvb, offset,
				hf_radiotap_he_mu_info_flags_1,
				ett_radiotap_he_mu_info_flags_1,
				flags1_headers, ENC_LITTLE_ENDIAN);
	offset += 2;

	proto_tree_add_bitmask(he_mu_info_tree, tvb, offset,
				hf_radiotap_he_mu_info_flags_2,
				ett_radiotap_he_mu_info_flags_2,
				flags2_headers, ENC_LITTLE_ENDIAN);
	offset += 2;

	mu_chan1_rus = proto_tree_add_subtree(he_mu_info_tree, tvb, offset, 4,
				ett_radiotap_he_mu_chan_rus, NULL,
				"Channel 1 RUs");

	proto_tree_add_item(mu_chan1_rus, mu_rus_chan1_rus_0, tvb, offset, 1,
				ENC_NA);
	offset++;

	proto_tree_add_item(mu_chan1_rus, mu_rus_chan1_rus_1, tvb, offset, 1,
				ENC_NA);
	offset++;

	proto_tree_add_item(mu_chan1_rus, mu_rus_chan1_rus_2, tvb, offset, 1,
				ENC_NA);
	offset++;

	proto_tree_add_item(mu_chan1_rus, mu_rus_chan1_rus_3, tvb, offset, 1,
				ENC_NA);
	offset++;

	mu_chan2_rus = proto_tree_add_subtree(he_mu_info_tree, tvb, offset, 4,
				ett_radiotap_he_mu_chan_rus, NULL,
				"Channel 2 RUs");

	proto_tree_add_item(mu_chan2_rus, mu_rus_chan2_rus_0, tvb, offset, 1,
				ENC_NA);
	offset++;

	proto_tree_add_item(mu_chan2_rus, mu_rus_chan2_rus_1, tvb, offset, 1,
				ENC_NA);
	offset++;

	proto_tree_add_item(mu_chan2_rus, mu_rus_chan2_rus_2, tvb, offset, 1,
				ENC_NA);
	offset++;

	proto_tree_add_item(mu_chan2_rus, mu_rus_chan2_rus_3, tvb, offset, 1,
				ENC_NA);
}

static const range_string zero_length_psdu_rsvals[] = {
	{ 0, 0, "sounding PPDU" },
	{ 1, 254, "reserved" },
	{ 255, 255, "vendor-specific" },
	{ 0, 0, NULL }
};

static void
dissect_radiotap_0_length_psdu(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree,
	int offset, struct ieee_802_11_phdr *phdr)
{
	proto_tree *zero_len_tree = NULL;
	guint32 psdu_type;

	zero_len_tree = proto_tree_add_subtree(tree, tvb, offset, 1,
		ett_radiotap_0_length_psdu, NULL, "0-length PSDU");

	proto_tree_add_item_ret_uint(zero_len_tree, hf_radiotap_0_length_psdu_type,
		tvb, offset, 1, ENC_NA, &psdu_type);
	switch (psdu_type) {

	case 0:
		phdr->has_zero_length_psdu_type = TRUE;
		phdr->zero_length_psdu_type = PHDR_802_11_SOUNDING_PSDU;
		break;

	case 1:
		phdr->has_zero_length_psdu_type = TRUE;
		phdr->zero_length_psdu_type = PHDR_802_11_DATA_NOT_CAPTURED;
		break;

	case 0xff:
		phdr->has_zero_length_psdu_type = TRUE;
		phdr->zero_length_psdu_type = PHDR_802_11_0_LENGTH_PSDU_VENDOR_SPECIFIC;
		break;
	}
}

static int * const l_sig_data1_headers[] = {
	&hf_radiotap_l_sig_rate_known,
	&hf_radiotap_l_sig_length_known,
	&hf_radiotap_l_sig_reserved,
	NULL
};

static int * const l_sig_data2_headers[] = {
	&hf_radiotap_l_sig_rate,
	&hf_radiotap_l_sig_length,
	NULL
};

static void
dissect_radiotap_l_sig(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree,
	int offset)
{
	proto_tree *l_sig_tree = NULL;

	l_sig_tree = proto_tree_add_subtree(tree, tvb, offset, 4,
		ett_radiotap_l_sig, NULL, "L-SIG");

	proto_tree_add_bitmask(l_sig_tree, tvb, offset,
		hf_radiotap_l_sig_data_1, ett_radiotap_l_sig_data_1,
		l_sig_data1_headers, ENC_LITTLE_ENDIAN);
	offset += 2;

	proto_tree_add_bitmask(l_sig_tree, tvb, offset,
		hf_radiotap_l_sig_data_2, ett_radiotap_l_sig_data_2,
		l_sig_data2_headers, ENC_LITTLE_ENDIAN);
}

static void
dissect_radiotap_tlv(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree,
        int offset, struct ieee_802_11_phdr *phdr _U_)
{
	guint16 type = tvb_get_letohs(tvb, offset);
	guint16 length = tvb_get_letohs(tvb, offset + 2);
	proto_tree *unknown_tlv = NULL;

	/* Insert code here to call the dissector for your TLV type */
	switch (type) {

	default:
		unknown_tlv = proto_tree_add_subtree(tree, tvb, offset,
						    length + 4,
						    ett_radiotap_unknown_tlv,
						    NULL, "Unknown TLV");
		proto_tree_add_item(unknown_tlv, hf_radiotap_tlv_type, tvb,
				    offset, 2, ENC_LITTLE_ENDIAN);
		offset += 2;

		proto_tree_add_item(unknown_tlv, hf_radiotap_tlv_datalen, tvb,
				    offset, 2, ENC_LITTLE_ENDIAN);
		offset += 2;

		proto_tree_add_item(unknown_tlv, hf_radiotap_unknown_tlv_data,
				    tvb, offset, length, ENC_NA);
		break;
	}
}

static void
dissect_radiotap_tsft(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree,
	int offset, struct ieee_802_11_phdr *phdr)
{
	phdr->tsf_timestamp = tvb_get_letoh64(tvb, offset);
	phdr->has_tsf_timestamp = TRUE;
	proto_tree_add_uint64(tree, hf_radiotap_mactime, tvb, offset, 8,
			      phdr->tsf_timestamp);
}

static void
dissect_radiotap_flags(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree,
	int offset, guint8 *rflags, struct ieee_802_11_phdr *phdr)
{
	proto_tree *ft;
	proto_tree *flags_tree;

	*rflags = tvb_get_guint8(tvb, offset);
	if (*rflags & IEEE80211_RADIOTAP_F_DATAPAD)
		phdr->datapad = TRUE;
	switch (radiotap_fcs_handling) {

	case USE_FCS_BIT:
		if (*rflags & IEEE80211_RADIOTAP_F_FCS)
			phdr->fcs_len = 4;
		else
			phdr->fcs_len = 0;
		break;

	case ASSUME_FCS_PRESENT:
		phdr->fcs_len = 4;
		break;

	case ASSUME_FCS_ABSENT:
		phdr->fcs_len = 0;
		break;
	}
	ft = proto_tree_add_item(tree, hf_radiotap_flags, tvb, offset,
				1, ENC_LITTLE_ENDIAN);
	flags_tree = proto_item_add_subtree(ft, ett_radiotap_flags);

	proto_tree_add_item(flags_tree, hf_radiotap_flags_cfp, tvb, offset,
				1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(flags_tree, hf_radiotap_flags_preamble, tvb, offset,
				1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(flags_tree, hf_radiotap_flags_wep, tvb, offset, 1,
				ENC_LITTLE_ENDIAN);
	proto_tree_add_item(flags_tree, hf_radiotap_flags_frag, tvb, offset, 1,
				ENC_LITTLE_ENDIAN);
	proto_tree_add_item(flags_tree, hf_radiotap_flags_fcs, tvb, offset, 1,
				ENC_LITTLE_ENDIAN);
	proto_tree_add_item(flags_tree, hf_radiotap_flags_datapad, tvb, offset,
				1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(flags_tree, hf_radiotap_flags_badfcs, tvb, offset,
				1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(flags_tree, hf_radiotap_flags_shortgi, tvb, offset,
				1, ENC_LITTLE_ENDIAN);
}

static void
dissect_radiotap_rate(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree,
	int offset, struct ieee_802_11_phdr *phdr)
{
	guint32 rate;

	rate = tvb_get_guint8(tvb, offset);
	/*
	 * XXX On FreeBSD rate & 0x80 means we have an MCS. On
	 * Linux and AirPcap it does not.  (What about
	 * macOS, NetBSD, OpenBSD, and DragonFly BSD?)
	 *
	 * This is an issue either for proprietary extensions
	 * to 11a or 11g, which do exist, or for 11n
	 * implementations that stuff a rate value into
	 * this field, which also appear to exist.
	 */
	if (radiotap_interpret_high_rates_as_mcs &&
			rate >= 0x80 && rate <= (0x80+76)) {
		/*
		 * XXX - we don't know the channel width
		 * or guard interval length, so we can't
		 * convert this to a data rate.
		 *
		 * If you want us to show a data rate,
		 * use the MCS field, not the Rate field;
		 * the MCS field includes not only the
		 * MCS index, it also includes bandwidth
		 * and guard interval information.
		 *
		 * XXX - can we get the channel width
		 * from XChannel and the guard interval
		 * information from Flags, at least on
		 * FreeBSD?
		 */
		proto_tree_add_uint(tree, hf_radiotap_mcs_index, tvb, offset,
				1, rate & 0x7f);
	} else {
		col_add_fstr(pinfo->cinfo, COL_TX_RATE, "%d.%d",
			     rate / 2, rate & 1 ? 5 : 0);
		proto_tree_add_float_format(tree, hf_radiotap_datarate,
					    tvb, offset, 1, (float)rate / 2,
					    "Data Rate: %.1f Mb/s",
					    (float)rate / 2);
		phdr->has_data_rate = TRUE;
		phdr->data_rate = rate;
	}
}

static void
dissect_radiotap_channel(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree,
	int offset, guint8 rflags, gboolean have_rflags,
	struct ieee_802_11_phdr *phdr)
{
	guint32     freq;
	guint16     cflags;

	freq = tvb_get_letohs(tvb, offset);
	if (freq != 0) {
		/*
		 * XXX - some captures have 0, which is
		 * obviously bogus.
		 */
		gint calc_channel;

		phdr->has_frequency = TRUE;
		phdr->frequency = freq;
		calc_channel = ieee80211_mhz_to_chan(freq);
		if (calc_channel != -1) {
			phdr->has_channel = TRUE;
			phdr->channel = calc_channel;
		}
	}
	memset(&phdr->phy_info, 0, sizeof(phdr->phy_info));
	cflags = tvb_get_letohs(tvb, offset + 2);
	switch (cflags & IEEE80211_CHAN_ALLTURBO) {

	case IEEE80211_CHAN_FHSS:
		phdr->phy = PHDR_802_11_PHY_11_FHSS;
		break;

	case IEEE80211_CHAN_DSSS:
		phdr->phy = PHDR_802_11_PHY_11_DSSS;
		break;

	case IEEE80211_CHAN_A:
		phdr->phy = PHDR_802_11_PHY_11A;
		phdr->phy_info.info_11a.has_turbo_type = TRUE;
		phdr->phy_info.info_11a.turbo_type = PHDR_802_11A_TURBO_TYPE_NORMAL;
		break;

	case IEEE80211_CHAN_B:
		phdr->phy = PHDR_802_11_PHY_11B;
		if (have_rflags) {
			phdr->phy_info.info_11b.has_short_preamble = TRUE;
			phdr->phy_info.info_11b.short_preamble = (rflags & IEEE80211_RADIOTAP_F_SHORTPRE) != 0;
		}
		break;

	case IEEE80211_CHAN_PUREG:
		phdr->phy = PHDR_802_11_PHY_11G;
		phdr->phy_info.info_11g.has_mode = TRUE;
		phdr->phy_info.info_11g.mode = PHDR_802_11G_MODE_NORMAL;
		if (have_rflags) {
			phdr->phy_info.info_11g.has_short_preamble = TRUE;
			phdr->phy_info.info_11g.short_preamble = (rflags & IEEE80211_RADIOTAP_F_SHORTPRE) != 0;
		}
		break;

	case IEEE80211_CHAN_G:
		phdr->phy = PHDR_802_11_PHY_11G;
		phdr->phy_info.info_11g.has_mode = TRUE;
		phdr->phy_info.info_11g.mode = PHDR_802_11G_MODE_NORMAL;
		if (have_rflags) {
			phdr->phy_info.info_11g.has_short_preamble = TRUE;
			phdr->phy_info.info_11g.short_preamble = (rflags & IEEE80211_RADIOTAP_F_SHORTPRE) != 0;
		}
		break;

	case IEEE80211_CHAN_108A:
		phdr->phy = PHDR_802_11_PHY_11A;
		phdr->phy_info.info_11a.has_turbo_type = TRUE;
		/* We assume non-STURBO is dynamic turbo */
		phdr->phy_info.info_11a.turbo_type = PHDR_802_11A_TURBO_TYPE_DYNAMIC_TURBO;
		break;

	case IEEE80211_CHAN_108PUREG:
		phdr->phy = PHDR_802_11_PHY_11G;
		phdr->phy_info.info_11g.has_mode = TRUE;
		phdr->phy_info.info_11g.mode = PHDR_802_11G_MODE_SUPER_G;
		if (have_rflags) {
			phdr->phy_info.info_11g.has_short_preamble = TRUE;
			phdr->phy_info.info_11g.short_preamble = (rflags & IEEE80211_RADIOTAP_F_SHORTPRE) != 0;
		}
		break;
	}

	/*
	 * XXX - special-case 11ad; there's no field to explicitly indicate
	 * an 11ad packet.  Anything with a frequency in the 802.11ad range
	 * is treated as 11ad.
	 */
	if (IS_80211AD(freq))
		phdr->phy = PHDR_802_11_PHY_11AD;

	if (tree) {
		gchar	   *chan_str;
		static int * const channel_flags[] = {
			&hf_radiotap_channel_flags_turbo,
			&hf_radiotap_channel_flags_cck,
			&hf_radiotap_channel_flags_ofdm,
			&hf_radiotap_channel_flags_2ghz,
			&hf_radiotap_channel_flags_5ghz,
			&hf_radiotap_channel_flags_passive,
			&hf_radiotap_channel_flags_dynamic,
			&hf_radiotap_channel_flags_gfsk,
			&hf_radiotap_channel_flags_gsm,
			&hf_radiotap_channel_flags_sturbo,
			&hf_radiotap_channel_flags_half,
			&hf_radiotap_channel_flags_quarter,
			NULL
		};

		chan_str = ieee80211_mhz_to_str(freq);
		col_add_fstr(pinfo->cinfo,
			     COL_FREQ_CHAN, "%s", chan_str);
		proto_tree_add_uint_format_value(tree,
					   hf_radiotap_channel_frequency,
					   tvb, offset, 2, freq,
					   "%s",
					   chan_str);
		g_free(chan_str);

		/* We're already 2-byte aligned. */
		proto_tree_add_bitmask(tree, tvb, offset + 2,
				hf_radiotap_channel_flags,
				ett_radiotap_channel_flags,
				channel_flags, ENC_LITTLE_ENDIAN);
	}
}

static void
dissect_radiotap_fhss(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree,
	int offset, struct ieee_802_11_phdr *phdr)
{
	/*
	 * Just in case we didn't have a Channel field or
	 * it said this was something other than 11 legacy
	 * FHSS.
	 */
	phdr->phy = PHDR_802_11_PHY_11_FHSS;
	phdr->phy_info.info_11_fhss.has_hop_set = TRUE;
	phdr->phy_info.info_11_fhss.hop_set = tvb_get_guint8(tvb, offset);
	phdr->phy_info.info_11_fhss.has_hop_pattern = TRUE;
	phdr->phy_info.info_11_fhss.hop_pattern = tvb_get_guint8(tvb, offset + 1);
	proto_tree_add_item(tree, hf_radiotap_fhss_hopset, tvb, offset, 1,
			    ENC_LITTLE_ENDIAN);
	proto_tree_add_item(tree, hf_radiotap_fhss_pattern, tvb, offset + 1, 1,
			    ENC_LITTLE_ENDIAN);
}

static void
dissect_radiotap_dbm_antsignal(tvbuff_t *tvb, packet_info *pinfo _U_,
	proto_tree *tree, int offset, struct ieee_802_11_phdr *phdr)
{
	gint8 dbm = tvb_get_gint8(tvb, offset);

	phdr->has_signal_dbm = TRUE;
	phdr->signal_dbm = dbm;
	col_add_fstr(pinfo->cinfo, COL_RSSI, "%d dBm", dbm);
	proto_tree_add_int(tree, hf_radiotap_dbm_antsignal, tvb, offset, 1, dbm);

}

static void
dissect_radiotap_dbm_antnoise(tvbuff_t *tvb, packet_info *pinfo _U_,
	proto_tree *tree, int offset, struct ieee_802_11_phdr *phdr)
{
	gint dbm = tvb_get_gint8(tvb, offset);

	phdr->has_noise_dbm = TRUE;
	phdr->noise_dbm = dbm;
	if (tree) {
		proto_tree_add_int(tree, hf_radiotap_dbm_antnoise, tvb, offset,
				1, dbm);
	}
}

static void
dissect_radiotap_db_antsignal(tvbuff_t *tvb, packet_info *pinfo _U_,
	proto_tree *tree, int offset, struct ieee_802_11_phdr *phdr)
{
	guint8 db = tvb_get_guint8(tvb, offset);

	phdr->has_signal_db = TRUE;
	phdr->signal_db = db;
	col_add_fstr(pinfo->cinfo, COL_RSSI, "%u dB", db);
	proto_tree_add_uint(tree, hf_radiotap_db_antsignal, tvb, offset, 1, db);
}

static void
dissect_radiotap_db_antnoise(tvbuff_t *tvb, packet_info *pinfo _U_,
	proto_tree *tree, int offset, struct ieee_802_11_phdr *phdr)
{
	guint db = tvb_get_guint8(tvb, offset);

	phdr->has_noise_db = TRUE;
	phdr->noise_db = db;
	if (tree) {
		proto_tree_add_uint(tree, hf_radiotap_db_antnoise, tvb, offset,
				1, db);
	}
}

static void
dissect_radiotap_rx_flags(tvbuff_t *tvb, packet_info *pinfo _U_,
	proto_tree *tree, int offset, proto_item **hdr_fcs_ti,
	int *hdr_fcs_offset, int *sent_fcs)
{
	if (radiotap_bit14_fcs) {
		if (tree) {
			*sent_fcs   = tvb_get_ntohl(tvb, offset);
			*hdr_fcs_ti = proto_tree_add_uint(tree,
							 hf_radiotap_fcs, tvb,
							 offset, 4, *sent_fcs);
			*hdr_fcs_offset = offset;
		}
	} else {
		static int * const rxflags[] = {
			&hf_radiotap_rxflags_badplcp,
			NULL
		};

		proto_tree_add_bitmask(tree, tvb, offset,
				hf_radiotap_rxflags, ett_radiotap_rxflags,
				rxflags, ENC_LITTLE_ENDIAN);
	}
}


static void
dissect_radiotap_tx_flags(tvbuff_t *tvb, packet_info *pinfo _U_,
	proto_tree *tree, int offset)
{
	static int * const txflags[] = {
		&hf_radiotap_txflags_fail,
		&hf_radiotap_txflags_cts,
		&hf_radiotap_txflags_rts,
		&hf_radiotap_txflags_noack,
		&hf_radiotap_txflags_noseqno,
		&hf_radiotap_txflags_order,
		NULL
	};

	proto_tree_add_bitmask(tree, tvb, offset,
			hf_radiotap_txflags, ett_radiotap_txflags,
			txflags, ENC_LITTLE_ENDIAN);
}

static void
dissect_radiotap_xchannel(tvbuff_t *tvb, packet_info *pinfo _U_,
	proto_tree *tree, int offset, guint8 rflags, gboolean have_rflags,
	struct ieee_802_11_phdr *phdr)
{
	guint32     xcflags = tvb_get_letohl(tvb, offset);
	guint32     freq;

	switch (xcflags & IEEE80211_CHAN_ALLTURBO) {

	case IEEE80211_CHAN_FHSS:
		/*
		 * Don't overwrite any FHSS information
		 * we've seen before this.
		 */
		if (phdr->phy != PHDR_802_11_PHY_11_FHSS) {
			phdr->phy = PHDR_802_11_PHY_11_FHSS;
		}
		break;

	case IEEE80211_CHAN_DSSS:
		phdr->phy = PHDR_802_11_PHY_11_DSSS;
		break;

	case IEEE80211_CHAN_A:
		phdr->phy = PHDR_802_11_PHY_11A;
		phdr->phy_info.info_11a.has_turbo_type = TRUE;
		phdr->phy_info.info_11a.turbo_type = PHDR_802_11A_TURBO_TYPE_NORMAL;
		break;

	case IEEE80211_CHAN_B:
		phdr->phy = PHDR_802_11_PHY_11B;
		if (have_rflags) {
			phdr->phy_info.info_11b.has_short_preamble = TRUE;
			phdr->phy_info.info_11b.short_preamble = (rflags & IEEE80211_RADIOTAP_F_SHORTPRE) != 0;
		}
		break;

	case IEEE80211_CHAN_PUREG:
		phdr->phy = PHDR_802_11_PHY_11G;
		phdr->phy_info.info_11g.has_mode = TRUE;
		phdr->phy_info.info_11g.mode = PHDR_802_11G_MODE_NORMAL;
		if (have_rflags) {
			phdr->phy_info.info_11g.has_short_preamble = TRUE;
			phdr->phy_info.info_11g.short_preamble = (rflags & IEEE80211_RADIOTAP_F_SHORTPRE) != 0;
		}
		break;

	case IEEE80211_CHAN_G:
		phdr->phy = PHDR_802_11_PHY_11G;
		phdr->phy_info.info_11g.has_mode = TRUE;
		phdr->phy_info.info_11g.mode = PHDR_802_11G_MODE_NORMAL;
		if (have_rflags) {
			phdr->phy_info.info_11g.has_short_preamble = TRUE;
			phdr->phy_info.info_11g.short_preamble = (rflags & IEEE80211_RADIOTAP_F_SHORTPRE) != 0;
		}
		break;

	case IEEE80211_CHAN_108A:
		phdr->phy = PHDR_802_11_PHY_11A;
		phdr->phy_info.info_11a.has_turbo_type = TRUE;
		/* We assume non-STURBO is dynamic turbo */
		phdr->phy_info.info_11a.turbo_type = PHDR_802_11A_TURBO_TYPE_DYNAMIC_TURBO;
		break;

	case IEEE80211_CHAN_108PUREG:
		phdr->phy = PHDR_802_11_PHY_11G;
		phdr->phy_info.info_11g.has_mode = TRUE;
		phdr->phy_info.info_11g.mode = PHDR_802_11G_MODE_SUPER_G;
		if (have_rflags) {
			phdr->phy_info.info_11g.has_short_preamble = TRUE;
			phdr->phy_info.info_11g.short_preamble = (rflags & IEEE80211_RADIOTAP_F_SHORTPRE) != 0;
		}
		break;

	case IEEE80211_CHAN_ST:
		phdr->phy = PHDR_802_11_PHY_11A;
		phdr->phy_info.info_11a.has_turbo_type = TRUE;
		phdr->phy_info.info_11a.turbo_type = PHDR_802_11A_TURBO_TYPE_STATIC_TURBO;
		break;

	case IEEE80211_CHAN_A|IEEE80211_CHAN_HT20:
	case IEEE80211_CHAN_A|IEEE80211_CHAN_HT40D:
	case IEEE80211_CHAN_A|IEEE80211_CHAN_HT40U:
	case IEEE80211_CHAN_G|IEEE80211_CHAN_HT20:
	case IEEE80211_CHAN_G|IEEE80211_CHAN_HT40U:
	case IEEE80211_CHAN_G|IEEE80211_CHAN_HT40D:
		phdr->phy = PHDR_802_11_PHY_11N;

		/*
		 * This doesn't supply "short GI" information,
		 * so use the 0x80 bit in the Flags field,
		 * if we have it; it's "Currently unspecified
		 * but used" for that purpose, according to
		 * the radiotap.org page for that field.
		 */
		if (have_rflags) {
			phdr->phy_info.info_11n.has_short_gi = TRUE;
			if (rflags & 0x80)
				phdr->phy_info.info_11n.short_gi = 1;
			else
				phdr->phy_info.info_11n.short_gi = 0;
		}
		break;
	}
	freq = tvb_get_letohs(tvb, offset + 4);
	if (freq != 0) {
		/*
		 * XXX - some captures have 0, which is
		 * obviously bogus.
		 */
		phdr->has_frequency = TRUE;
		phdr->frequency = freq;

		/*
		 * XXX - special-case 11ad; there's no field to explicitly
		 * indicate an 11ad packet.  Anything with a frequency in
		 * the 802.11ad range is treated as 11ad.
		 */
		if (IS_80211AD(freq))
			phdr->phy = PHDR_802_11_PHY_11AD;
	}
	phdr->has_channel = TRUE;
	phdr->channel = tvb_get_guint8(tvb, offset + 6);
	if (tree) {
		static int * const xchannel_flags[] = {
			&hf_radiotap_xchannel_flags_turbo,
			&hf_radiotap_xchannel_flags_cck,
			&hf_radiotap_xchannel_flags_ofdm,
			&hf_radiotap_xchannel_flags_2ghz,
			&hf_radiotap_xchannel_flags_5ghz,
			&hf_radiotap_xchannel_flags_passive,
			&hf_radiotap_xchannel_flags_dynamic,
			&hf_radiotap_xchannel_flags_gfsk,
			&hf_radiotap_xchannel_flags_gsm,
			&hf_radiotap_xchannel_flags_sturbo,
			&hf_radiotap_xchannel_flags_half,
			&hf_radiotap_xchannel_flags_quarter,
			&hf_radiotap_xchannel_flags_ht20,
			&hf_radiotap_xchannel_flags_ht40u,
			&hf_radiotap_xchannel_flags_ht40d,
			NULL
		};

		proto_tree_add_item(tree, hf_radiotap_xchannel_channel,
					tvb, offset + 6, 1,
					ENC_LITTLE_ENDIAN);
		proto_tree_add_item(tree, hf_radiotap_xchannel_frequency,
					tvb, offset + 4, 2, ENC_LITTLE_ENDIAN);

		proto_tree_add_bitmask(tree, tvb, offset, hf_radiotap_xchannel_flags,
					ett_radiotap_xchannel_flags,
					xchannel_flags, ENC_LITTLE_ENDIAN);


#if 0
		proto_tree_add_uint(tree, hf_radiotap_xchannel_maxpower,
					tvb, offset + 7, 1, maxpower);
#endif
	}
}

static void
dissect_radiotap_timestamp(tvbuff_t *tvb, packet_info *pinfo _U_,
	proto_tree *tree, int offset, struct ieee_802_11_phdr *phdr _U_)
{
	proto_item *it_root;
	proto_tree *ts_tree, *flg_tree;

	it_root = proto_tree_add_item(tree, hf_radiotap_timestamp, tvb, offset,
			12, ENC_NA);
	ts_tree = proto_item_add_subtree(it_root, ett_radiotap_timestamp);

	proto_tree_add_item(ts_tree, hf_radiotap_timestamp_ts, tvb, offset, 8,
			ENC_LITTLE_ENDIAN);
	if (tvb_get_letohs(tvb, offset + 11) & IEEE80211_RADIOTAP_TS_FLG_ACCURACY)
		proto_tree_add_item(ts_tree, hf_radiotap_timestamp_accuracy,
				tvb, offset + 8, 2, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(ts_tree, hf_radiotap_timestamp_unit, tvb,
			offset + 10, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(ts_tree, hf_radiotap_timestamp_spos, tvb,
			offset + 10, 1, ENC_LITTLE_ENDIAN);
	flg_tree = proto_item_add_subtree(ts_tree, ett_radiotap_timestamp_flags);
	proto_tree_add_item(flg_tree, hf_radiotap_timestamp_flags_32bit, tvb,
			offset + 11, 1, ENC_LITTLE_ENDIAN);
	proto_tree_add_item(flg_tree, hf_radiotap_timestamp_flags_accuracy, tvb,
			offset + 11, 1, ENC_LITTLE_ENDIAN);
}

static int
dissect_radiotap(tvbuff_t * tvb, packet_info * pinfo, proto_tree * tree, void* unused_data _U_)
{
	proto_tree *radiotap_tree     = NULL;
	proto_item *length_item       = NULL;
	proto_item *present_item      = NULL;
	proto_tree *present_tree      = NULL;
	proto_item *present_word_item = NULL;
	proto_tree *present_word_tree = NULL;
	proto_item *ti                = NULL;
	proto_item *hidden_item;
	int         offset;
	tvbuff_t   *next_tvb;
	guint8      version;
	guint       length;
	proto_item *rate_ti;
	gboolean    have_rflags       = FALSE;
	guint8      rflags            = 0;
	/* backward compat with bit 14 == fcs in header */
	proto_item *hdr_fcs_ti        = NULL;
	int         hdr_fcs_offset    = 0;
	guint32     sent_fcs          = 0;
	guint32     calc_fcs;
	gint        err               = -ENOENT;
	void       *data;
	struct ieee80211_radiotap_iterator  iter;
	struct ieee_802_11_phdr phdr;
	guchar	 *bmap_start;
	guint	  n_bitmaps;
	guint	  i;
	gboolean  rtap_ns;
	gboolean  rtap_ns_next;
	guint	  rtap_ns_offset;
	guint	  rtap_ns_offset_next;
	gboolean  zero_length_psdu = FALSE;
	guint32   ven_ns_id;
	tvbuff_t  *ven_data_tvb;

	/* our non-standard overrides */
	static struct radiotap_override overrides[] = {
		{IEEE80211_RADIOTAP_XCHANNEL, 4, 8},	/* xchannel */

		/* keep last */
		{14, 4, 4},	/* FCS in header */
	};
	guint n_overrides = array_length(overrides);

	if (!radiotap_bit14_fcs)
		n_overrides--;

	/* We don't have any 802.11 metadata yet. */
	memset(&phdr, 0, sizeof(phdr));
	phdr.fcs_len = -1;
	phdr.decrypted = FALSE;
	phdr.datapad = FALSE;
	phdr.phy = PHDR_802_11_PHY_UNKNOWN;

	col_set_str(pinfo->cinfo, COL_PROTOCOL, "WLAN");
	col_clear(pinfo->cinfo, COL_INFO);

	version = tvb_get_guint8(tvb, 0);
	length = tvb_get_letohs(tvb, 2);

	col_add_fstr(pinfo->cinfo, COL_INFO, "Radiotap Capture v%u, Length %u",
		     version, length);

	/* Dissect the packet */
	if (tree) {
		ti = proto_tree_add_protocol_format(tree, proto_radiotap,
						    tvb, 0, length,
						    "Radiotap Header v%u, Length %u",
						    version, length);
		radiotap_tree = proto_item_add_subtree(ti, ett_radiotap);
		proto_tree_add_uint(radiotap_tree, hf_radiotap_version,
				    tvb, 0, 1, version);
		proto_tree_add_item(radiotap_tree, hf_radiotap_pad,
				    tvb, 1, 1, ENC_LITTLE_ENDIAN);
		length_item = proto_tree_add_uint(radiotap_tree, hf_radiotap_length,
						  tvb, 2, 2, length);
	}

	/*
	 * The length is the length of the entire radiotap header, so it
	 * must be at least 8, for the version, padding, length, and first
	 * presence flags word.
	 */
	if (length < 8) {
		expert_add_info(pinfo, length_item,
		    &ei_radiotap_invalid_header_length);
		return tvb_captured_length(tvb);
	}

	data = tvb_memdup(wmem_packet_scope(), tvb, 0, length);

	if (ieee80211_radiotap_iterator_init(&iter, (struct ieee80211_radiotap_header *)data, length, NULL)) {
		if (tree)
			proto_item_append_text(ti, " (invalid)");
		/* maybe the length was correct anyway ... */
		goto hand_off_to_80211;
	}

	iter.overrides = overrides;
	iter.n_overrides = n_overrides;

	/*
	 * Check the "present flags" bitmaps, and add them if we're
	 * building a tree.
	 */
	bmap_start = (guchar *)data + 4;
	n_bitmaps = (guint)(iter.this_arg - bmap_start) / 4;
	rtap_ns_next = TRUE;
	rtap_ns_offset_next = 0;
	present_item = proto_tree_add_item(radiotap_tree,
	    hf_radiotap_present, tvb, 4, n_bitmaps * 4, ENC_NA);
	present_tree = proto_item_add_subtree(present_item,
	    ett_radiotap_present);

	for (i = 0; i < n_bitmaps; i++) {
		guint32 bmap = pletoh32(bmap_start + 4 * i);

		rtap_ns_offset = rtap_ns_offset_next;
		rtap_ns_offset_next += 32;

		offset = 4 * i;

		present_word_item =
		    proto_tree_add_item(present_tree,
		      hf_radiotap_present_word,
		      tvb, offset + 4, 4, ENC_LITTLE_ENDIAN);

		present_word_tree =
		    proto_item_add_subtree(present_word_item,
		      ett_radiotap_present_word);

		rtap_ns = rtap_ns_next;

		/* Evaluate what kind of namespaces will come next */
		if (bmap & BIT(IEEE80211_RADIOTAP_RADIOTAP_NAMESPACE)) {
			rtap_ns_next = TRUE;
			rtap_ns_offset_next = 0;
		}
		if (bmap & BIT(IEEE80211_RADIOTAP_VENDOR_NAMESPACE))
			rtap_ns_next = FALSE;
		if ((bmap & (BIT(IEEE80211_RADIOTAP_RADIOTAP_NAMESPACE) |
			     BIT(IEEE80211_RADIOTAP_VENDOR_NAMESPACE)))
			== (BIT(IEEE80211_RADIOTAP_RADIOTAP_NAMESPACE) |
			    BIT(IEEE80211_RADIOTAP_VENDOR_NAMESPACE))) {
			expert_add_info_format(pinfo, present_word_item,
			    &ei_radiotap_present,
			    "Both radiotap and vendor namespace specified in bitmask word %u",
			    i);
			goto malformed;
		}

		if (!rtap_ns)
			goto always_bits;

		/* Currently, we don't know anything about bits >= 32 */
		if (rtap_ns_offset)
			goto always_bits;

		if (tree) {
			proto_tree_add_item(present_word_tree,
					    hf_radiotap_present_tsft, tvb,
					    offset + 4, 4, ENC_LITTLE_ENDIAN);
			proto_tree_add_item(present_word_tree,
					    hf_radiotap_present_flags, tvb,
					    offset + 4, 4, ENC_LITTLE_ENDIAN);
			proto_tree_add_item(present_word_tree,
					    hf_radiotap_present_rate, tvb,
					    offset + 4, 4, ENC_LITTLE_ENDIAN);
			proto_tree_add_item(present_word_tree,
					    hf_radiotap_present_channel, tvb,
					    offset + 4, 4, ENC_LITTLE_ENDIAN);
			proto_tree_add_item(present_word_tree,
					    hf_radiotap_present_fhss, tvb,
					    offset + 4, 4, ENC_LITTLE_ENDIAN);
			proto_tree_add_item(present_word_tree,
					    hf_radiotap_present_dbm_antsignal,
					    tvb, offset + 4, 4, ENC_LITTLE_ENDIAN);
			proto_tree_add_item(present_word_tree,
					    hf_radiotap_present_dbm_antnoise,
					    tvb, offset + 4, 4, ENC_LITTLE_ENDIAN);
			proto_tree_add_item(present_word_tree,
					    hf_radiotap_present_lock_quality,
					    tvb, offset + 4, 4, ENC_LITTLE_ENDIAN);
			proto_tree_add_item(present_word_tree,
					    hf_radiotap_present_tx_attenuation,
					    tvb, offset + 4, 4, ENC_LITTLE_ENDIAN);
			proto_tree_add_item(present_word_tree,
					    hf_radiotap_present_db_tx_attenuation,
					    tvb, offset + 4, 4, ENC_LITTLE_ENDIAN);
			proto_tree_add_item(present_word_tree,
					    hf_radiotap_present_dbm_tx_power,
					    tvb, offset + 4, 4, ENC_LITTLE_ENDIAN);
			proto_tree_add_item(present_word_tree,
					    hf_radiotap_present_antenna, tvb,
					    offset + 4, 4, ENC_LITTLE_ENDIAN);
			proto_tree_add_item(present_word_tree,
					    hf_radiotap_present_db_antsignal,
					    tvb, offset + 4, 4, ENC_LITTLE_ENDIAN);
			proto_tree_add_item(present_word_tree,
					    hf_radiotap_present_db_antnoise,
					    tvb, offset + 4, 4, ENC_LITTLE_ENDIAN);
			if (radiotap_bit14_fcs) {
				proto_tree_add_item(present_word_tree,
						    hf_radiotap_present_hdrfcs,
						    tvb, offset + 4, 4, ENC_LITTLE_ENDIAN);
			} else {
				proto_tree_add_item(present_word_tree,
						    hf_radiotap_present_rxflags,
						    tvb, offset + 4, 4, ENC_LITTLE_ENDIAN);
			}
			proto_tree_add_item(present_word_tree,
					    hf_radiotap_present_txflags, tvb,
					    offset + 4, 4, ENC_LITTLE_ENDIAN);
			proto_tree_add_item(present_word_tree,
					    hf_radiotap_present_xchannel, tvb,
					    offset + 4, 4, ENC_LITTLE_ENDIAN);

			proto_tree_add_item(present_word_tree,
					    hf_radiotap_present_mcs, tvb,
					    offset + 4, 4, ENC_LITTLE_ENDIAN);
			proto_tree_add_item(present_word_tree,
					    hf_radiotap_present_ampdu, tvb,
					    offset + 4, 4, ENC_LITTLE_ENDIAN);
			proto_tree_add_item(present_word_tree,
					    hf_radiotap_present_vht, tvb,
					    offset + 4, 4, ENC_LITTLE_ENDIAN);
			proto_tree_add_item(present_word_tree,
					    hf_radiotap_present_timestamp, tvb,
					    offset + 4, 4, ENC_LITTLE_ENDIAN);
			proto_tree_add_item(present_word_tree,
					    hf_radiotap_present_he, tvb,
					    offset + 4, 4, ENC_LITTLE_ENDIAN);
			proto_tree_add_item(present_word_tree,
					    hf_radiotap_present_he_mu, tvb,
					    offset + 4, 4, ENC_LITTLE_ENDIAN);
			proto_tree_add_item(present_word_tree,
					    hf_radiotap_present_0_length_psdu,
					    tvb, offset + 4, 4, ENC_LITTLE_ENDIAN);
			proto_tree_add_item(present_word_tree,
					    hf_radiotap_present_l_sig, tvb,
					    offset + 4, 4, ENC_LITTLE_ENDIAN);
			proto_tree_add_item(present_word_tree,
					    hf_radiotap_present_tlv, tvb,
					    offset + 4, 4, ENC_LITTLE_ENDIAN);
		}
 always_bits:
		if (tree) {
			proto_tree_add_item(present_word_tree,
					    hf_radiotap_present_rtap_ns, tvb,
					    offset + 4, 4, ENC_LITTLE_ENDIAN);
			proto_tree_add_item(present_word_tree,
					    hf_radiotap_present_vendor_ns, tvb,
					    offset + 4, 4, ENC_LITTLE_ENDIAN);
			proto_tree_add_item(present_word_tree,
					    hf_radiotap_present_ext, tvb,
					    offset + 4, 4, ENC_LITTLE_ENDIAN);
		}
	}

	while (!(err = ieee80211_radiotap_iterator_next(&iter))) {
		proto_tree *item_tree = radiotap_tree;

		offset = (int)((guchar *) iter.this_arg - (guchar *) data);

		if (iter.tlv_mode) {

			offset -= sizeof(struct ieee80211_radiotap_tlv);

			dissect_radiotap_tlv(tvb, pinfo, radiotap_tree, offset,
					     &phdr);

			continue;
		}

		if (iter.this_arg_index == IEEE80211_RADIOTAP_VENDOR_NAMESPACE
		    && tree) {
			proto_tree *ven_tree;
			proto_item *vt;
			const gchar *manuf_name;
			guint8 subns;

			manuf_name = tvb_get_manuf_name(tvb, offset);
			subns = tvb_get_guint8(tvb, offset+3);

			vt = proto_tree_add_bytes_format_value(item_tree,
							 hf_radiotap_vendor_ns,
							 tvb, offset,
							 iter.this_arg_size,
							 NULL,
							 "%s-%d",
							 manuf_name, subns);
			ven_tree = proto_item_add_subtree(vt, ett_radiotap_vendor);
			/*
			 * This is defined on the Radiotap site as an array
			 * of 3 octets, containing an OUI, but we show fields
			 * of that sort as a 24-bit big-endian field, so
			 * ENC_BIG_ENDIAN is correct here.
			 */
			proto_tree_add_item(ven_tree, hf_radiotap_ven_oui,
					    tvb, offset, 3, ENC_BIG_ENDIAN);
			proto_tree_add_item(ven_tree, hf_radiotap_ven_subns,
					    tvb, offset + 3, 1, ENC_LITTLE_ENDIAN);
			/* Get OUI and sub namespace as UINT32 */
			ven_ns_id = tvb_get_guint32(tvb, offset, ENC_BIG_ENDIAN);
			if (iter.tlv_mode) {
				proto_tree_add_item(ven_tree, hf_radiotap_ven_item, tvb,
						    offset + 4, 2, ENC_LITTLE_ENDIAN);
				ven_data_tvb = tvb_new_subset_length(tvb, offset + 8, iter.this_arg_size - 8);
			} else {
				proto_tree_add_item(ven_tree, hf_radiotap_ven_skip, tvb,
						    offset + 4, 2, ENC_LITTLE_ENDIAN);
				ven_data_tvb = tvb_new_subset_length(tvb, offset + 6, iter.this_arg_size - 6);
			}
			if (!dissector_try_uint_new(vendor_dissector_table, ven_ns_id, ven_data_tvb, pinfo, ven_tree, TRUE, NULL)) {
				proto_tree_add_item(ven_tree, hf_radiotap_ven_data, ven_data_tvb, 0, -1, ENC_NA);
			}
		}

		if (!iter.is_radiotap_ns)
			continue;

		switch (iter.this_arg_index) {

		case IEEE80211_RADIOTAP_TSFT:
			dissect_radiotap_tsft(tvb, pinfo, item_tree, offset,
					&phdr);
			break;

		case IEEE80211_RADIOTAP_FLAGS:
			have_rflags = TRUE;
			dissect_radiotap_flags(tvb, pinfo, item_tree, offset,
					&rflags, &phdr);
			break;

		case IEEE80211_RADIOTAP_RATE:
			dissect_radiotap_rate(tvb, pinfo, item_tree, offset,
					&phdr);
			break;

		case IEEE80211_RADIOTAP_CHANNEL:
			dissect_radiotap_channel(tvb, pinfo, item_tree, offset,
					rflags, have_rflags, &phdr);
			break;

		case IEEE80211_RADIOTAP_FHSS:
			dissect_radiotap_fhss(tvb, pinfo, item_tree, offset,
					&phdr);
			break;

		case IEEE80211_RADIOTAP_DBM_ANTSIGNAL:
			dissect_radiotap_dbm_antsignal(tvb, pinfo, item_tree,
					offset, &phdr);
			break;

		case IEEE80211_RADIOTAP_DBM_ANTNOISE:
			dissect_radiotap_dbm_antnoise(tvb, pinfo, item_tree,
					offset, &phdr);
			break;

		case IEEE80211_RADIOTAP_LOCK_QUALITY:
			proto_tree_add_item(item_tree,
						    hf_radiotap_quality, tvb,
						    offset, 2, ENC_LITTLE_ENDIAN);
			break;

		case IEEE80211_RADIOTAP_TX_ATTENUATION:
			proto_tree_add_item(item_tree,
					    hf_radiotap_tx_attenuation, tvb,
					    offset, 2, ENC_LITTLE_ENDIAN);
			break;

		case IEEE80211_RADIOTAP_DB_TX_ATTENUATION:
			proto_tree_add_item(item_tree,
					    hf_radiotap_db_tx_attenuation, tvb,
					    offset, 2, ENC_LITTLE_ENDIAN);
			break;

		case IEEE80211_RADIOTAP_DBM_TX_POWER:
			proto_tree_add_item(item_tree,
						   hf_radiotap_txpower, tvb,
						   offset, 1, ENC_NA);
			break;

		case IEEE80211_RADIOTAP_ANTENNA:
			proto_tree_add_item(item_tree,
						    hf_radiotap_antenna, tvb,
						    offset, 1, ENC_NA);
			break;

		case IEEE80211_RADIOTAP_DB_ANTSIGNAL:
			dissect_radiotap_db_antsignal(tvb, pinfo, item_tree,
					offset, &phdr);
			break;

		case IEEE80211_RADIOTAP_DB_ANTNOISE:
			dissect_radiotap_db_antnoise(tvb, pinfo, item_tree,
					offset, &phdr);
			break;

		case IEEE80211_RADIOTAP_RX_FLAGS:
			dissect_radiotap_rx_flags(tvb, pinfo, item_tree,
						offset, &hdr_fcs_ti,
						&hdr_fcs_offset, &sent_fcs);
			break;

		case IEEE80211_RADIOTAP_TX_FLAGS:
			dissect_radiotap_tx_flags(tvb, pinfo, item_tree,
						offset);
			break;

		case IEEE80211_RADIOTAP_XCHANNEL:
			dissect_radiotap_xchannel(tvb, pinfo, item_tree,
						offset, rflags, have_rflags,
						&phdr);
			break;

		case IEEE80211_RADIOTAP_MCS: {
			proto_tree *mcs_tree = NULL;
			guint8	    mcs_known, mcs_flags;
			guint8	    mcs;
			guint	    bandwidth;
			guint	    gi_length;
			gboolean    can_calculate_rate;

			/*
			 * Start out assuming that we can calculate the rate;
			 * if we are missing any of the MCS index, channel
			 * width, or guard interval length, we can't.
			 */
			can_calculate_rate = TRUE;

			mcs_known = tvb_get_guint8(tvb, offset);
			/*
			 * If there's actually any data here, not an
			 * empty field, this is 802.11n - unless we've
			 * seen a frequency >= 60 GHz and already set
			 * it to 802.11ad.
			 */
			if (mcs_known != 0 &&
			    phdr.phy != PHDR_802_11_PHY_11AD) {
				phdr.phy = PHDR_802_11_PHY_11N;
				memset(&phdr.phy_info.info_11n, 0, sizeof(phdr.phy_info.info_11n));
			}

			mcs_flags = tvb_get_guint8(tvb, offset + 1);
			if (mcs_known & IEEE80211_RADIOTAP_MCS_HAVE_MCS) {
				mcs = tvb_get_guint8(tvb, offset + 2);
				phdr.phy_info.info_11n.has_mcs_index = TRUE;
				phdr.phy_info.info_11n.mcs_index = mcs;
			} else {
				mcs = 0;
				can_calculate_rate = FALSE;	/* no MCS index */
			}
			if (mcs_known & IEEE80211_RADIOTAP_MCS_HAVE_BW) {
				phdr.phy_info.info_11n.has_bandwidth = TRUE;
				phdr.phy_info.info_11n.bandwidth = (mcs_flags & IEEE80211_RADIOTAP_MCS_BW_MASK);
			}
			if (mcs_known & IEEE80211_RADIOTAP_MCS_HAVE_GI) {
				gi_length = (mcs_flags & IEEE80211_RADIOTAP_MCS_SGI) ?
				    1 : 0;
				phdr.phy_info.info_11n.has_short_gi = TRUE;
				phdr.phy_info.info_11n.short_gi = gi_length;
			} else {
				gi_length = 0;
				can_calculate_rate = FALSE;	/* no GI width */
			}
			if (mcs_known & IEEE80211_RADIOTAP_MCS_HAVE_FMT) {
				phdr.phy_info.info_11n.has_greenfield = TRUE;
				phdr.phy_info.info_11n.greenfield = (mcs_flags & IEEE80211_RADIOTAP_MCS_FMT_GF) != 0;
			}
			if (mcs_known & IEEE80211_RADIOTAP_MCS_HAVE_FEC) {
				phdr.phy_info.info_11n.has_fec = TRUE;
				phdr.phy_info.info_11n.fec = (mcs_flags & IEEE80211_RADIOTAP_MCS_FEC_LDPC) ? 1 : 0;
			}
			if (mcs_known & IEEE80211_RADIOTAP_MCS_HAVE_STBC) {
				phdr.phy_info.info_11n.has_stbc_streams = TRUE;
				phdr.phy_info.info_11n.stbc_streams = (mcs_flags & IEEE80211_RADIOTAP_MCS_STBC_MASK) >> IEEE80211_RADIOTAP_MCS_STBC_SHIFT;
			}
			if (mcs_known & IEEE80211_RADIOTAP_MCS_HAVE_NESS) {
				phdr.phy_info.info_11n.has_ness = TRUE;
				/* This is stored a bit weirdly */
				phdr.phy_info.info_11n.ness =
				    ((mcs_known & IEEE80211_RADIOTAP_MCS_NESS_BIT1) >> 6) |
				    ((mcs_flags & IEEE80211_RADIOTAP_MCS_NESS_BIT0) >> 7);
			}

			if (tree) {
				proto_item *it;
				static int * const mcs_haves_with_ness_bit1[] = {
					&hf_radiotap_mcs_have_bw,
					&hf_radiotap_mcs_have_index,
					&hf_radiotap_mcs_have_gi,
					&hf_radiotap_mcs_have_format,
					&hf_radiotap_mcs_have_fec,
					&hf_radiotap_mcs_have_stbc,
					&hf_radiotap_mcs_have_ness,
					&hf_radiotap_mcs_ness_bit1,
					NULL
				};
				static int * const mcs_haves_without_ness_bit1[] = {
					&hf_radiotap_mcs_have_bw,
					&hf_radiotap_mcs_have_index,
					&hf_radiotap_mcs_have_gi,
					&hf_radiotap_mcs_have_format,
					&hf_radiotap_mcs_have_fec,
					&hf_radiotap_mcs_have_stbc,
					&hf_radiotap_mcs_have_ness,
					NULL
				};

				it = proto_tree_add_item(item_tree, hf_radiotap_mcs,
							 tvb, offset, 3, ENC_NA);
				mcs_tree = proto_item_add_subtree(it, ett_radiotap_mcs);

				if (mcs_known & IEEE80211_RADIOTAP_MCS_HAVE_NESS)
					proto_tree_add_bitmask(mcs_tree, tvb, offset, hf_radiotap_mcs_known, ett_radiotap_mcs_known, mcs_haves_with_ness_bit1, ENC_LITTLE_ENDIAN);
				else
					proto_tree_add_bitmask(mcs_tree, tvb, offset, hf_radiotap_mcs_known, ett_radiotap_mcs_known, mcs_haves_without_ness_bit1, ENC_LITTLE_ENDIAN);
			}
			if (mcs_known & IEEE80211_RADIOTAP_MCS_HAVE_BW) {
				bandwidth = ((mcs_flags & IEEE80211_RADIOTAP_MCS_BW_MASK) == IEEE80211_RADIOTAP_MCS_BW_40) ?
				    1 : 0;
				proto_tree_add_uint(mcs_tree, hf_radiotap_mcs_bw,
							    tvb, offset + 1, 1, mcs_flags);
			} else {
				bandwidth = 0;
				can_calculate_rate = FALSE;	/* no bandwidth */
			}
			if (mcs_known & IEEE80211_RADIOTAP_MCS_HAVE_GI) {
				proto_tree_add_uint(mcs_tree, hf_radiotap_mcs_gi,
							    tvb, offset + 1, 1, mcs_flags);
			}
			if (mcs_known & IEEE80211_RADIOTAP_MCS_HAVE_FMT) {
				proto_tree_add_uint(mcs_tree, hf_radiotap_mcs_format,
							    tvb, offset + 1, 1, mcs_flags);
			}
			if (mcs_known & IEEE80211_RADIOTAP_MCS_HAVE_FEC) {
				proto_tree_add_uint(mcs_tree, hf_radiotap_mcs_fec,
							    tvb, offset + 1, 1, mcs_flags);
			}
			if (mcs_known & IEEE80211_RADIOTAP_MCS_HAVE_STBC) {
				proto_tree_add_uint(mcs_tree, hf_radiotap_mcs_stbc,
							    tvb, offset + 1, 1, mcs_flags);
			}
			if (mcs_known & IEEE80211_RADIOTAP_MCS_HAVE_NESS) {
				proto_tree_add_uint(mcs_tree, hf_radiotap_mcs_ness_bit0,
							    tvb, offset + 1, 1, mcs_flags);
			}
			if (mcs_known & IEEE80211_RADIOTAP_MCS_HAVE_MCS) {
				proto_tree_add_uint(mcs_tree, hf_radiotap_mcs_index,
							    tvb, offset + 2, 1, mcs);
			}

			/*
			 * If we have the MCS index, channel width, and
			 * guard interval length, and the MCS index is
			 * valid, we can compute the rate.  If the resulting
			 * rate is non-zero, report it.  (If it's zero,
			 * it's an MCS/channel width/GI combination that
			 * 802.11n doesn't support.)
			 */
			if (can_calculate_rate && mcs <= MAX_MCS_INDEX
					&& ieee80211_ht_Dbps[mcs] != 0) {
				float rate = ieee80211_htrate(mcs, bandwidth, gi_length);
				col_add_fstr(pinfo->cinfo, COL_TX_RATE, "%.1f", rate);
				if (tree) {
					rate_ti = proto_tree_add_float_format(item_tree,
						hf_radiotap_datarate,
						tvb, offset, 3, rate,
						"Data Rate: %.1f Mb/s", rate);
					proto_item_set_generated(rate_ti);
				}
			}
			break;
		}
		case IEEE80211_RADIOTAP_AMPDU_STATUS: {
			proto_item *it;
			proto_tree *ampdu_tree = NULL, *ampdu_flags_tree;
			guint16	    ampdu_flags;

			phdr.has_aggregate_info = 1;
			phdr.aggregate_flags = 0;
			phdr.aggregate_id = tvb_get_letohl(tvb, offset);

			ampdu_flags = tvb_get_letohs(tvb, offset + 4);
			if (ampdu_flags & IEEE80211_RADIOTAP_AMPDU_IS_LAST)
				phdr.aggregate_flags |= PHDR_802_11_LAST_PART_OF_A_MPDU;
			if (ampdu_flags & IEEE80211_RADIOTAP_AMPDU_DELIM_CRC_ERR)
				phdr.aggregate_flags |= PHDR_802_11_A_MPDU_DELIM_CRC_ERROR;

			if (tree) {
				it = proto_tree_add_item(item_tree, hf_radiotap_ampdu,
							 tvb, offset, 8, ENC_NA);
				ampdu_tree = proto_item_add_subtree(it, ett_radiotap_ampdu);

				proto_tree_add_item(ampdu_tree, hf_radiotap_ampdu_ref,
						    tvb, offset, 4, ENC_LITTLE_ENDIAN);

				it = proto_tree_add_item(ampdu_tree, hf_radiotap_ampdu_flags,
							 tvb, offset + 4, 2, ENC_LITTLE_ENDIAN);
				ampdu_flags_tree = proto_item_add_subtree(it, ett_radiotap_ampdu_flags);
				proto_tree_add_item(ampdu_flags_tree, hf_radiotap_ampdu_flags_report_zerolen,
						    tvb, offset + 4, 2, ENC_LITTLE_ENDIAN);
				proto_tree_add_item(ampdu_flags_tree, hf_radiotap_ampdu_flags_is_zerolen,
						    tvb, offset + 4, 2, ENC_LITTLE_ENDIAN);
				proto_tree_add_item(ampdu_flags_tree, hf_radiotap_ampdu_flags_last_known,
						    tvb, offset + 4, 2, ENC_LITTLE_ENDIAN);
				proto_tree_add_item(ampdu_flags_tree, hf_radiotap_ampdu_flags_is_last,
						    tvb, offset + 4, 2, ENC_LITTLE_ENDIAN);
				proto_tree_add_item(ampdu_flags_tree, hf_radiotap_ampdu_flags_delim_crc_error,
						    tvb, offset + 4, 2, ENC_LITTLE_ENDIAN);
				proto_tree_add_item(ampdu_flags_tree, hf_radiotap_ampdu_flags_eof,
						    tvb, offset + 4, 2, ENC_LITTLE_ENDIAN);
				proto_tree_add_item(ampdu_flags_tree, hf_radiotap_ampdu_flags_eof_known,
						    tvb, offset + 4, 2, ENC_LITTLE_ENDIAN);
			}
			if (ampdu_flags & IEEE80211_RADIOTAP_AMPDU_DELIM_CRC_KNOWN) {
				if (ampdu_tree)
					proto_tree_add_item(ampdu_tree, hf_radiotap_ampdu_delim_crc,
							    tvb, offset + 6, 1, ENC_NA);
			}
			break;
		}
		case IEEE80211_RADIOTAP_VHT: {
			proto_item *it, *it_root = NULL;
			proto_tree *vht_tree	 = NULL, *vht_known_tree = NULL, *user_tree = NULL;
			guint16	    known;
			guint8	    vht_flags, bw, mcs_nss;
			guint	    bandwidth	 = 0;
			guint	    gi_length	 = 0;
			guint	    nss		 = 0;
			guint	    mcs		 = 0;
			gboolean    can_calculate_rate;
			guint	    user;

			/*
			 * Start out assuming that we can calculate the rate;
			 * if we are missing any of the MCS index, channel
			 * width, or guard interval length, we can't.
			 */
			can_calculate_rate = TRUE;

			known = tvb_get_letohs(tvb, offset);
			/*
			 * If there's actually any data here, not an
			 * empty field, this is 802.11ac.
			 */
			if (known != 0) {
				phdr.phy = PHDR_802_11_PHY_11AC;
			}
			vht_flags = tvb_get_guint8(tvb, offset + 2);
			if (tree) {
				it_root = proto_tree_add_item(item_tree, hf_radiotap_vht,
						tvb, offset, 12, ENC_NA);
				vht_tree = proto_item_add_subtree(it_root, ett_radiotap_vht);
				it = proto_tree_add_item(vht_tree, hf_radiotap_vht_known,
						tvb, offset, 2, known);
				vht_known_tree = proto_item_add_subtree(it, ett_radiotap_vht_known);

				proto_tree_add_item(vht_known_tree, hf_radiotap_vht_have_stbc,
						tvb, offset, 2, ENC_LITTLE_ENDIAN);
				proto_tree_add_item(vht_known_tree, hf_radiotap_vht_have_txop_ps,
						tvb, offset, 2, ENC_LITTLE_ENDIAN);
				proto_tree_add_item(vht_known_tree, hf_radiotap_vht_have_gi,
						tvb, offset, 2, ENC_LITTLE_ENDIAN);
				proto_tree_add_item(vht_known_tree, hf_radiotap_vht_have_sgi_nsym_da,
						tvb, offset, 2, ENC_LITTLE_ENDIAN);
				proto_tree_add_item(vht_known_tree, hf_radiotap_vht_have_ldpc_extra,
						tvb, offset, 2, ENC_LITTLE_ENDIAN);
				proto_tree_add_item(vht_known_tree, hf_radiotap_vht_have_bf,
						tvb, offset, 2, ENC_LITTLE_ENDIAN);
				proto_tree_add_item(vht_known_tree, hf_radiotap_vht_have_bw,
						tvb, offset, 2, ENC_LITTLE_ENDIAN);
				proto_tree_add_item(vht_known_tree, hf_radiotap_vht_have_gid,
						tvb, offset, 2, ENC_LITTLE_ENDIAN);
				proto_tree_add_item(vht_known_tree, hf_radiotap_vht_have_p_aid,
						tvb, offset, 2, ENC_LITTLE_ENDIAN);
			}

			if (known & IEEE80211_RADIOTAP_VHT_HAVE_STBC) {
				phdr.phy_info.info_11ac.has_stbc = TRUE;
				phdr.phy_info.info_11ac.stbc = (vht_flags & IEEE80211_RADIOTAP_VHT_STBC) != 0;
				if (vht_tree)
					proto_tree_add_item(vht_tree, hf_radiotap_vht_stbc,
							tvb, offset + 2, 1, ENC_LITTLE_ENDIAN);
			}

			if (known & IEEE80211_RADIOTAP_VHT_HAVE_TXOP_PS) {
				phdr.phy_info.info_11ac.has_txop_ps_not_allowed = TRUE;
				phdr.phy_info.info_11ac.txop_ps_not_allowed = (vht_flags & IEEE80211_RADIOTAP_VHT_TXOP_PS) != 0;
				if (vht_tree)
					proto_tree_add_item(vht_tree, hf_radiotap_vht_txop_ps,
							tvb, offset + 2, 1, ENC_LITTLE_ENDIAN);
			}

			if (known & IEEE80211_RADIOTAP_VHT_HAVE_GI) {
				gi_length = (vht_flags & IEEE80211_RADIOTAP_VHT_SGI) ? 1 : 0;
				phdr.phy_info.info_11ac.has_short_gi = TRUE;
				phdr.phy_info.info_11ac.short_gi = gi_length;
				if (vht_tree) {
					proto_tree_add_item(vht_tree, hf_radiotap_vht_gi,
							tvb, offset + 2, 1, ENC_LITTLE_ENDIAN);
				}
			} else {
				can_calculate_rate = FALSE;	/* no GI width */
			}

			if (known & IEEE80211_RADIOTAP_VHT_HAVE_SGI_NSYM_DA) {
				phdr.phy_info.info_11ac.has_short_gi_nsym_disambig = TRUE;
				phdr.phy_info.info_11ac.short_gi_nsym_disambig = (vht_flags & IEEE80211_RADIOTAP_VHT_SGI_NSYM_DA) != 0;
				if (vht_tree) {
					it = proto_tree_add_item(vht_tree, hf_radiotap_vht_sgi_nsym_da,
							tvb, offset + 2, 1, ENC_LITTLE_ENDIAN);
					if ((vht_flags & IEEE80211_RADIOTAP_VHT_SGI_NSYM_DA) &&
						(known & IEEE80211_RADIOTAP_VHT_HAVE_GI) &&
						!(vht_flags & IEEE80211_RADIOTAP_VHT_SGI))
						proto_item_append_text(it, " (invalid)");
				}
			}

			if (known & IEEE80211_RADIOTAP_VHT_HAVE_LDPC_EXTRA) {
				phdr.phy_info.info_11ac.has_ldpc_extra_ofdm_symbol = TRUE;
				phdr.phy_info.info_11ac.ldpc_extra_ofdm_symbol = (vht_flags & IEEE80211_RADIOTAP_VHT_LDPC_EXTRA) != 0;
				if (vht_tree) {
					proto_tree_add_item(vht_tree, hf_radiotap_vht_ldpc_extra,
							tvb, offset + 2, 1, ENC_LITTLE_ENDIAN);
				}
			}

			if (known & IEEE80211_RADIOTAP_VHT_HAVE_BF) {
				phdr.phy_info.info_11ac.has_beamformed = TRUE;
				phdr.phy_info.info_11ac.beamformed = (vht_flags & IEEE80211_RADIOTAP_VHT_BF) != 0;
				if (vht_tree)
					proto_tree_add_item(vht_tree, hf_radiotap_vht_bf,
							tvb, offset + 2, 1, ENC_LITTLE_ENDIAN);
			}

			if (known & IEEE80211_RADIOTAP_VHT_HAVE_BW) {
				bw = tvb_get_guint8(tvb, offset + 3) & IEEE80211_RADIOTAP_VHT_BW_MASK;
				phdr.phy_info.info_11ac.has_bandwidth = TRUE;
				phdr.phy_info.info_11ac.bandwidth = bw;
				if (bw < sizeof(ieee80211_vht_bw2rate_index)/sizeof(ieee80211_vht_bw2rate_index[0]))
					bandwidth = ieee80211_vht_bw2rate_index[bw];
				else
					can_calculate_rate = FALSE; /* unknown bandwidth */

				if (vht_tree)
					proto_tree_add_item(vht_tree, hf_radiotap_vht_bw,
							tvb, offset + 3, 1, ENC_LITTLE_ENDIAN);
			} else {
				can_calculate_rate = FALSE;	/* no bandwidth */
			}

			phdr.phy_info.info_11ac.has_fec = TRUE;
			phdr.phy_info.info_11ac.fec = tvb_get_guint8(tvb, offset + 8);

			for (user = 0; user < 4; user++) {
				mcs_nss = tvb_get_guint8(tvb, offset + 4 + user);
				nss = (mcs_nss & IEEE80211_RADIOTAP_VHT_NSS);
				mcs = (mcs_nss & IEEE80211_RADIOTAP_VHT_MCS) >> 4;
				phdr.phy_info.info_11ac.mcs[user] = mcs;
				phdr.phy_info.info_11ac.nss[user] = nss;

				if (nss) {
					/*
					 * OK, there's some data here.
					 * If we haven't already flagged this
					 * as VHT, do so.
					 */
					if (phdr.phy != PHDR_802_11_PHY_11AC) {
						phdr.phy = PHDR_802_11_PHY_11AC;
					}
					if (vht_tree) {
						it = proto_tree_add_item(vht_tree, hf_radiotap_vht_user,
							tvb, offset + 4, 5, ENC_NA);
						proto_item_append_text(it, " %d: MCS %u", user, mcs);
						user_tree = proto_item_add_subtree(it, ett_radiotap_vht_user);

						it = proto_tree_add_item(user_tree, hf_radiotap_vht_mcs[user],
							tvb, offset + 4 + user, 1,
							ENC_LITTLE_ENDIAN);
						if (mcs > MAX_MCS_VHT_INDEX) {
							proto_item_append_text(it, " (invalid)");
						} else {
							proto_item_append_text(it, " (%s %s)",
								ieee80211_vhtinfo[mcs].modulation,
								ieee80211_vhtinfo[mcs].coding_rate);
						}

						proto_tree_add_item(user_tree, hf_radiotap_vht_nss[user],
							tvb, offset + 4 + user, 1, ENC_LITTLE_ENDIAN);
						if (known & IEEE80211_RADIOTAP_VHT_HAVE_STBC) {
							guint nsts;
							proto_item *nsts_ti;

							if (vht_flags & IEEE80211_RADIOTAP_VHT_STBC)
								nsts = 2 * nss;
							else
								nsts = nss;
							nsts_ti = proto_tree_add_uint(user_tree, hf_radiotap_vht_nsts[user],
								tvb, offset + 4 + user, 1, nsts);
							proto_item_set_generated(nsts_ti);
						}
						proto_tree_add_item(user_tree, hf_radiotap_vht_coding[user],
							tvb, offset + 8, 1,ENC_LITTLE_ENDIAN);
					}

					if (can_calculate_rate && mcs <= MAX_MCS_VHT_INDEX &&
					    nss <= MAX_VHT_NSS ) {
						float rate = ieee80211_vhtinfo[mcs].rates[bandwidth][gi_length] * nss;
						if (rate != 0.0f ) {
							rate_ti = proto_tree_add_float_format(user_tree,
									hf_radiotap_vht_datarate[user],
									tvb, offset, 12, rate,
									"Data Rate: %.1f Mb/s", rate);
							proto_item_set_generated(rate_ti);
							if (ieee80211_vhtvalid[mcs].valid[bandwidth][nss-1] == FALSE)
								expert_add_info(pinfo, rate_ti, &ei_radiotap_invalid_data_rate);

						}
					}
				}
			}

			if (known & IEEE80211_RADIOTAP_VHT_HAVE_GID) {
				phdr.phy_info.info_11ac.has_group_id = TRUE;
				phdr.phy_info.info_11ac.group_id = tvb_get_guint8(tvb, offset + 9);
				if (vht_tree)
					proto_tree_add_item(vht_tree, hf_radiotap_vht_gid,
							tvb, offset+9, 1, ENC_LITTLE_ENDIAN);
			}

			if (known & IEEE80211_RADIOTAP_VHT_HAVE_PAID) {
				phdr.phy_info.info_11ac.has_partial_aid = TRUE;
				phdr.phy_info.info_11ac.partial_aid = tvb_get_letohs(tvb, offset + 10);
				if (vht_tree) {
					proto_tree_add_item(vht_tree, hf_radiotap_vht_p_aid,
							tvb, offset+10, 2, ENC_LITTLE_ENDIAN);
				}
			}

			break;
		}
		case IEEE80211_RADIOTAP_TIMESTAMP: {
			dissect_radiotap_timestamp(tvb, pinfo, item_tree,
					offset, &phdr);
			break;
		}
		case IEEE80211_RADIOTAP_HE:
			/*
			 * Presumably this is (whatever draft of) 802.11ax.
			 * Also, presumably, you won't get the HE_MU field
			 * without this field.
			 */
			phdr.phy = PHDR_802_11_PHY_11AX;
			dissect_radiotap_he_info(tvb, pinfo, radiotap_tree, offset, &phdr.phy_info.info_11ax);
			break;
		case IEEE80211_RADIOTAP_HE_MU:
			dissect_radiotap_he_mu_info(tvb, pinfo, item_tree, offset);
			break;
		case IEEE80211_RADIOTAP_0_LENGTH_PSDU:
			dissect_radiotap_0_length_psdu(tvb, pinfo, item_tree, offset, &phdr);
			zero_length_psdu = TRUE;
			break;
		case IEEE80211_RADIOTAP_L_SIG:
			dissect_radiotap_l_sig(tvb, pinfo, item_tree, offset);
			break;
		case IEEE80211_RADIOTAP_TLVS:
			/* used for padding */
			break;
		default:
			proto_tree_add_item(item_tree, hf_radiotap_unknown_tlv_data, tvb,
					    offset, iter.this_arg_size, ENC_NA);
			break;
		}
	}

	if (err != -ENOENT) {
		expert_add_info(pinfo, present_item,
		    &ei_radiotap_data_past_header);
 malformed:
		proto_item_append_text(ti, " (malformed)");
	}

	/*
	 * Is there any more there?
	 */
	if (zero_length_psdu) {
		return tvb_captured_length(tvb);
	}

 hand_off_to_80211:
	/* Grab the rest of the frame. */
	next_tvb = tvb_new_subset_remaining(tvb, length);

	/* If we had an in-header FCS, check it.
	 * This can only happen if the backward-compat configuration option
	 * is chosen by the user. */
	if (hdr_fcs_ti) {
		guint captured_length = tvb_captured_length(next_tvb);
		guint reported_length = tvb_reported_length(next_tvb);
		guint fcs_len = (phdr.fcs_len > 0) ? phdr.fcs_len : 0;

		/* It would be very strange for the header to have an FCS for the
		 * frame *and* the frame to have the FCS at the end, but it's possible, so
		 * take that into account by using the FCS length recorded in pinfo. */

		/* Watch out for [erroneously] short frames */
		if (captured_length >= reported_length &&
		    captured_length > fcs_len) {
			calc_fcs =
			    crc32_802_tvb(next_tvb, tvb_captured_length(next_tvb) - fcs_len);

			/* By virtue of hdr_fcs_ti being set, we know that 'tree' is set,
			 * so there's no need to check it here. */
			if (calc_fcs == sent_fcs) {
				proto_item_append_text(hdr_fcs_ti,
						       " [correct]");
			} else {
				proto_item_append_text(hdr_fcs_ti,
						       " [incorrect, should be 0x%08x]",
						       calc_fcs);
				hidden_item =
				    proto_tree_add_boolean(radiotap_tree,
							   hf_radiotap_fcs_bad,
							   tvb, hdr_fcs_offset,
							   4, TRUE);
				proto_item_set_hidden(hidden_item);
			}
		} else {
			proto_item_append_text(hdr_fcs_ti,
					       " [cannot verify - not enough data]");
		}
	}

	/* dissect the 802.11 packet next */
	call_dissector_with_data(ieee80211_radio_handle, next_tvb, pinfo,
	    tree, &phdr);

	return tvb_captured_length(tvb);
}

void proto_register_radiotap(void)
{

	static hf_register_info hf[] = {
		{&hf_radiotap_version,
		 {"Header revision", "radiotap_version",
		  FT_UINT8, BASE_DEC, NULL, 0x0,
		  "Version of radiotap header format", HFILL}},

		{&hf_radiotap_pad,
		 {"Header pad", "radiotap_pad",
		  FT_UINT8, BASE_DEC, NULL, 0x0,
		  "Padding", HFILL}},

		{&hf_radiotap_length,
		 {"Header length", "radiotap_length",
		  FT_UINT16, BASE_DEC, NULL, 0x0,
		  "Length of header including version, pad, length and data fields", HFILL}},

		{&hf_radiotap_present,
		 {"Present flags", "radiotap_present",
		  FT_NONE, BASE_NONE, NULL, 0x0,
		  "Bitmask indicating which fields are present", HFILL}},

		{&hf_radiotap_present_word,
		 {"Present flags word", "radiotap_present_word",
		  FT_UINT32, BASE_HEX, NULL, 0x0,
		  "Word from present flags bitmask", HFILL}},

		{&hf_radiotap_tlv,
		 {"TLV", "radiotap_tlv",
		  FT_BYTES, BASE_NONE, NULL, 0x0,
		  NULL, HFILL}},

		{&hf_radiotap_tlv_type,
		 {"TLV type", "radiotap_tlv_type",
		  FT_UINT32, BASE_DEC, NULL, 0x0,
		  NULL, HFILL}},

		{&hf_radiotap_tlv_datalen,
		 {"TLV datalen", "radiotap_tlv_datalen",
		  FT_UINT32, BASE_DEC, NULL, 0x0,
		  NULL, HFILL}},

		{&hf_radiotap_unknown_tlv_data,
		 {"unknown TLV data", "radiotap_tlv_unknown_data",
		  FT_BYTES, BASE_NONE, NULL, 0x0,
		  NULL, HFILL}},

#define RADIOTAP_MASK(name)	BIT(IEEE80211_RADIOTAP_ ##name)

		/* Boolean 'present' flags */
		{&hf_radiotap_present_tsft,
		 {"TSFT", "radiotap_present_tsft",
		  FT_BOOLEAN, 32, TFS(&tfs_present_absent), RADIOTAP_MASK(TSFT),
		  "Specifies if the Time Synchronization Function Timer field is present", HFILL}},

		{&hf_radiotap_present_flags,
		 {"Flags", "radiotap_present_flags",
		  FT_BOOLEAN, 32, TFS(&tfs_present_absent), RADIOTAP_MASK(FLAGS),
		  "Specifies if the channel flags field is present", HFILL}},

		{&hf_radiotap_present_rate,
		 {"Rate", "radiotap_present_rate",
		  FT_BOOLEAN, 32, TFS(&tfs_present_absent), RADIOTAP_MASK(RATE),
		  "Specifies if the transmit/receive rate field is present", HFILL}},

		{&hf_radiotap_present_channel,
		 {"Channel", "radiotap_present_channel",
		  FT_BOOLEAN, 32, TFS(&tfs_present_absent), RADIOTAP_MASK(CHANNEL),
		  "Specifies if the transmit/receive frequency field is present", HFILL}},

		{&hf_radiotap_present_fhss,
		 {"FHSS", "radiotap_present_fhss",
		  FT_BOOLEAN, 32, TFS(&tfs_present_absent), RADIOTAP_MASK(FHSS),
		  "Specifies if the hop set and pattern is present for frequency hopping radios", HFILL}},

		{&hf_radiotap_present_dbm_antsignal,
		 {"dBm Antenna Signal", "radiotap_present_dbm_antsignal",
		  FT_BOOLEAN, 32, TFS(&tfs_present_absent), RADIOTAP_MASK(DBM_ANTSIGNAL),
		  "Specifies if the antenna signal strength in dBm is present", HFILL}},

		{&hf_radiotap_present_dbm_antnoise,
		 {"dBm Antenna Noise", "radiotap_present_dbm_antnoise",
		  FT_BOOLEAN, 32, TFS(&tfs_present_absent), RADIOTAP_MASK(DBM_ANTNOISE),
		  "Specifies if the RF noise power at antenna field is present", HFILL}},

		{&hf_radiotap_present_lock_quality,
		 {"Lock Quality", "radiotap_present_lock_quality",
		  FT_BOOLEAN, 32, TFS(&tfs_present_absent), RADIOTAP_MASK(LOCK_QUALITY),
		  "Specifies if the signal quality field is present", HFILL}},

		{&hf_radiotap_present_tx_attenuation,
		 {"TX Attenuation", "radiotap_present_tx_attenuation",
		  FT_BOOLEAN, 32, TFS(&tfs_present_absent), RADIOTAP_MASK(TX_ATTENUATION),
		  "Specifies if the transmit power distance from max power field is present", HFILL}},

		{&hf_radiotap_present_db_tx_attenuation,
		 {"dB TX Attenuation", "radiotap_present_db_tx_attenuation",
		  FT_BOOLEAN, 32, TFS(&tfs_present_absent), RADIOTAP_MASK(DB_TX_ATTENUATION),
		  "Specifies if the transmit power distance from max power (in dB) field is present", HFILL}},

		{&hf_radiotap_present_dbm_tx_power,
		 {"dBm TX Power", "radiotap_present_dbm_tx_power",
		  FT_BOOLEAN, 32, TFS(&tfs_present_absent), RADIOTAP_MASK(DBM_TX_POWER),
		  "Specifies if the transmit power (in dBm) field is present", HFILL}},

		{&hf_radiotap_present_antenna,
		 {"Antenna", "radiotap_present_antenna",
		  FT_BOOLEAN, 32, TFS(&tfs_present_absent), RADIOTAP_MASK(ANTENNA),
		  "Specifies if the antenna number field is present", HFILL}},

		{&hf_radiotap_present_db_antsignal,
		 {"dB Antenna Signal", "radiotap_present_db_antsignal",
		  FT_BOOLEAN, 32, TFS(&tfs_present_absent), RADIOTAP_MASK(DB_ANTSIGNAL),
		  "Specifies if the RF signal power at antenna in dB field is present", HFILL}},

		{&hf_radiotap_present_db_antnoise,
		 {"dB Antenna Noise", "radiotap_present_db_antnoise",
		  FT_BOOLEAN, 32, TFS(&tfs_present_absent), RADIOTAP_MASK(DB_ANTNOISE),
		  "Specifies if the RF signal power at antenna in dBm field is present", HFILL}},

		{&hf_radiotap_present_rxflags,
		 {"RX flags", "radiotap_present_rxflags",
		  FT_BOOLEAN, 32, TFS(&tfs_present_absent), RADIOTAP_MASK(RX_FLAGS),
		  "Specifies if the RX flags field is present", HFILL}},

		{&hf_radiotap_present_txflags,
		 {"TX flags", "radiotap_present_txflags",
		  FT_BOOLEAN, 32, TFS(&tfs_present_absent), RADIOTAP_MASK(TX_FLAGS),
		  "Specifies if the TX flags field is present", HFILL}},

		{&hf_radiotap_present_hdrfcs,
		 {"FCS in header", "radiotap_present_fcs",
		  FT_BOOLEAN, 32, TFS(&tfs_present_absent), RADIOTAP_MASK(RX_FLAGS),
		  "Specifies if the FCS field is present", HFILL}},

		{&hf_radiotap_present_xchannel,
		 {"Channel+", "radiotap_present_xchannel",
		  FT_BOOLEAN, 32, TFS(&tfs_present_absent), RADIOTAP_MASK(XCHANNEL),
		  "Specifies if the extended channel info field is present", HFILL}},

		{&hf_radiotap_present_mcs,
		 {"MCS information", "radiotap_present_mcs",
		  FT_BOOLEAN, 32, TFS(&tfs_present_absent), RADIOTAP_MASK(MCS),
		  "Specifies if the MCS field is present", HFILL}},

		{&hf_radiotap_present_ampdu,
		 {"A-MPDU Status", "radiotap_present_ampdu",
		  FT_BOOLEAN, 32, TFS(&tfs_present_absent), RADIOTAP_MASK(AMPDU_STATUS),
		  "Specifies if the A-MPDU status field is present", HFILL}},

		{&hf_radiotap_present_vht,
		 {"VHT information", "radiotap_present_vht",
		  FT_BOOLEAN, 32, TFS(&tfs_present_absent), RADIOTAP_MASK(VHT),
		  "Specifies if the VHT field is present", HFILL}},

		{&hf_radiotap_present_timestamp,
		 {"frame timestamp", "radiotap_present_timestamp",
		  FT_BOOLEAN, 32, TFS(&tfs_present_absent), RADIOTAP_MASK(TIMESTAMP),
		  "Specifies if the timestamp field is present", HFILL}},

		{&hf_radiotap_present_he,
		 {"HE information", "radiotap_present_he",
		  FT_BOOLEAN, 32, TFS(&tfs_present_absent), RADIOTAP_MASK(HE),
		  "Specifies if the HE field is present", HFILL}},

		{&hf_radiotap_present_he_mu,
		 {"HE-MU information", "radiotap_present_he_mu",
		  FT_BOOLEAN, 32, TFS(&tfs_present_absent), RADIOTAP_MASK(HE_MU),
		  "Specifies if the HE field is present", HFILL}},

		{&hf_radiotap_present_0_length_psdu,
		 {"0 Length PSDU", "radiotap_present_0_length_psdu",
		   FT_BOOLEAN, 32, TFS(&tfs_present_absent), RADIOTAP_MASK(0_LENGTH_PSDU),
		   "Specifies whether or not the 0-Length PSDU field is present", HFILL}},

		{&hf_radiotap_present_l_sig,
		 {"L-SIG", "radiotap_present_l_sig",
		  FT_BOOLEAN, 32, TFS(&tfs_present_absent), RADIOTAP_MASK(L_SIG),
		  "Specifies whether or not the L-SIG field is present", HFILL}},

		{&hf_radiotap_present_tlv,
		 {"TLVs", "radiotap_present_tlv",
		  FT_BOOLEAN, 32, TFS(&tfs_present_absent), RADIOTAP_MASK(TLVS),
		  "Specifies switch to TLV fields", HFILL}},

		{&hf_radiotap_present_rtap_ns,
		 {"Radiotap NS next", "radiotap_present_rtap_ns",
		  FT_BOOLEAN, 32, NULL, RADIOTAP_MASK(RADIOTAP_NAMESPACE),
		  "Specifies a reset to the radiotap namespace", HFILL}},

		{&hf_radiotap_present_vendor_ns,
		 {"Vendor NS next", "radiotap_present_vendor_ns",
		  FT_BOOLEAN, 32, NULL, RADIOTAP_MASK(VENDOR_NAMESPACE),
		  "Specifies that the next bitmap is in a vendor namespace", HFILL}},

		{&hf_radiotap_present_ext,
		 {"Ext", "radiotap_present_ext",
		  FT_BOOLEAN, 32, TFS(&tfs_present_absent), RADIOTAP_MASK(EXT),
		  "Specifies if there are any extensions to the header present", HFILL}},

		/* Boolean 'present.flags' flags */
		{&hf_radiotap_flags,
		 {"Flags", "radiotap_flags",
		  FT_UINT8, BASE_HEX, NULL, 0x0, NULL, HFILL}},

		{&hf_radiotap_flags_cfp,
		 {"CFP", "radiotap_flags_cfp",
		  FT_BOOLEAN, 8, NULL, IEEE80211_RADIOTAP_F_CFP,
		  "Sent/Received during CFP", HFILL}},

		{&hf_radiotap_flags_preamble,
		 {"Preamble", "radiotap_flags_preamble",
		  FT_BOOLEAN, 8, TFS(&preamble_type),
		  IEEE80211_RADIOTAP_F_SHORTPRE,
		  "Sent/Received with short preamble", HFILL}},

		{&hf_radiotap_flags_wep,
		 {"WEP", "radiotap_flags_wep",
		  FT_BOOLEAN, 8, NULL, IEEE80211_RADIOTAP_F_WEP,
		  "Sent/Received with WEP encryption", HFILL}},

		{&hf_radiotap_flags_frag,
		 {"Fragmentation", "radiotap_flags_frag",
		  FT_BOOLEAN, 8, NULL, IEEE80211_RADIOTAP_F_FRAG,
		  "Sent/Received with fragmentation", HFILL}},

		{&hf_radiotap_flags_fcs,
		 {"FCS at end", "radiotap_flags_fcs",
		  FT_BOOLEAN, 8, NULL, IEEE80211_RADIOTAP_F_FCS,
		  "Frame includes FCS at end", HFILL}},

		{&hf_radiotap_flags_datapad,
		 {"Data Pad", "radiotap_flags_datapad",
		  FT_BOOLEAN, 8, NULL, IEEE80211_RADIOTAP_F_DATAPAD,
		  "Frame has padding between 802.11 header and payload", HFILL}},

		{&hf_radiotap_flags_badfcs,
		 {"Bad FCS", "radiotap_flags_badfcs",
		  FT_BOOLEAN, 8, NULL, IEEE80211_RADIOTAP_F_BADFCS,
		  "Frame received with bad FCS", HFILL}},

		{&hf_radiotap_flags_shortgi,
		 {"Short GI", "radiotap_flags_shortgi",
		  FT_BOOLEAN, 8, NULL, IEEE80211_RADIOTAP_F_SHORTGI,
		  "Frame Sent/Received with HT short Guard Interval", HFILL}},

		{&hf_radiotap_mactime,
		 {"MAC timestamp", "radiotap_mactime",
		  FT_UINT64, BASE_DEC, NULL, 0x0,
		  "Value in microseconds of the MAC's Time Synchronization Function timer"
		  " when the first bit of the MPDU arrived at the MAC.",
		  HFILL}},

		{&hf_radiotap_quality,
		 {"Signal Quality", "radiotap_quality",
		  FT_UINT16, BASE_DEC, NULL, 0x0,
		  "Signal quality (unitless measure)", HFILL}},

		{&hf_radiotap_fcs,
		 {"802.11 FCS", "radiotap_fcs",
		  FT_UINT32, BASE_HEX, NULL, 0x0,
		  "Frame check sequence of this frame", HFILL}},

#if 0
		{&hf_radiotap_channel,
		 {"Channel", "radiotap_channel",
		  FT_UINT32, BASE_DEC, NULL, 0x0,
		  "802.11 channel number that this frame was sent/received on", HFILL}},
#endif

		{&hf_radiotap_channel_frequency,
		 {"Channel frequency", "radiotap_channel_freq",
		  FT_UINT32, BASE_DEC, NULL, 0x0,
		  "Channel frequency in megahertz that this frame was sent/received on", HFILL}},

		{&hf_radiotap_channel_flags,
		 {"Channel flags", "radiotap_channel_flags",
		  FT_UINT16, BASE_HEX, NULL, 0x0,
		  NULL, HFILL}},

		{&hf_radiotap_channel_flags_turbo,
		 {"Turbo", "radiotap_channel_flags_turbo",
		  FT_BOOLEAN, 16, NULL, 0x0010, "Channel Flags Turbo", HFILL}},

		{&hf_radiotap_channel_flags_cck,
		 {"Complementary Code Keying (CCK)", "radiotap_channel_flags_cck",
		  FT_BOOLEAN, 16, NULL, 0x0020,
		  "Channel Flags Complementary Code Keying (CCK) Modulation", HFILL}},

		{&hf_radiotap_channel_flags_ofdm,
		 {"Orthogonal Frequency-Division Multiplexing (OFDM)", "radiotap_channel_flags_ofdm",
		  FT_BOOLEAN, 16, NULL, 0x0040,
		  "Channel Flags Orthogonal Frequency-Division Multiplexing (OFDM)", HFILL}},

		{&hf_radiotap_channel_flags_2ghz,
		 {"2 GHz spectrum", "radiotap_channel_flags_2ghz",
		  FT_BOOLEAN, 16, NULL, 0x0080, "Channel Flags 2 GHz spectrum", HFILL}},

		{&hf_radiotap_channel_flags_5ghz,
		 {"5 GHz spectrum", "radiotap_channel_flags_5ghz",
		  FT_BOOLEAN, 16, NULL, 0x0100, "Channel Flags 5 GHz spectrum", HFILL}},

		{&hf_radiotap_channel_flags_passive,
		 {"Passive", "radiotap_channel_flags_passive",
		  FT_BOOLEAN, 16, NULL, 0x0200,
		  "Channel Flags Passive", HFILL}},

		{&hf_radiotap_channel_flags_dynamic,
		 {"Dynamic CCK-OFDM", "radiotap_channel_flags_dynamic",
		  FT_BOOLEAN, 16, NULL, 0x0400,
		  "Channel Flags Dynamic CCK-OFDM Channel", HFILL}},

		{&hf_radiotap_channel_flags_gfsk,
		 {"Gaussian Frequency Shift Keying (GFSK)", "radiotap_channel_flags_gfsk",
		  FT_BOOLEAN, 16, NULL, 0x0800,
		  "Channel Flags Gaussian Frequency Shift Keying (GFSK) Modulation", HFILL}},

		{&hf_radiotap_channel_flags_gsm,
		 {"GSM (900MHz)", "radiotap_channel_flags_gsm",
		  FT_BOOLEAN, 16, NULL, 0x1000,
		  "Channel Flags GSM", HFILL}},

		{&hf_radiotap_channel_flags_sturbo,
		 {"Static Turbo", "radiotap_channel_flags_sturbo",
		  FT_BOOLEAN, 16, NULL, 0x2000,
		  "Channel Flags Status Turbo", HFILL}},

		{&hf_radiotap_channel_flags_half,
		 {"Half Rate Channel (10MHz Channel Width)", "radiotap_channel_flags_half",
		  FT_BOOLEAN, 16, NULL, 0x4000,
		  "Channel Flags Half Rate", HFILL}},

		{&hf_radiotap_channel_flags_quarter,
		 {"Quarter Rate Channel (5MHz Channel Width)", "radiotap_channel_flags_quarter",
		  FT_BOOLEAN, 16, NULL, 0x8000,
		  "Channel Flags Quarter Rate", HFILL}},

		{&hf_radiotap_rxflags,
		 {"RX flags", "radiotap_rxflags",
		  FT_UINT16, BASE_HEX, NULL, 0x0,
		  NULL, HFILL}},

		{&hf_radiotap_rxflags_badplcp,
		 {"Bad PLCP", "radiotap_rxflags_badplcp",
		  FT_BOOLEAN, 24, NULL, IEEE80211_RADIOTAP_F_RX_BADPLCP,
		  "Frame with bad PLCP", HFILL}},

		{&hf_radiotap_txflags,
		 {"TX flags", "radiotap_txflags",
		  FT_UINT16, BASE_HEX, NULL, 0x0,
		  NULL, HFILL}},

		{&hf_radiotap_txflags_fail,
		 {"Fail", "radiotap_rxflags_fail",
		  FT_BOOLEAN, 24, NULL, IEEE80211_RADIOTAP_F_TX_FAIL,
		  "Transmission failed due to excessive retries", HFILL}},

		{&hf_radiotap_txflags_cts,
		 {"CTS", "radiotap_rxflags_cts",
		  FT_BOOLEAN, 24, NULL, IEEE80211_RADIOTAP_F_TX_CTS,
		  "Transmission used CTS-to-self protection", HFILL}},

		{&hf_radiotap_txflags_rts,
		 {"RTS/CTS", "radiotap_rxflags_rts",
		  FT_BOOLEAN, 24, NULL, IEEE80211_RADIOTAP_F_TX_RTS,
		  "Transmission used RTS/CTS handshake", HFILL}},

		{&hf_radiotap_txflags_noack,
		 {"No ACK", "radiotap_rxflags_noack",
		  FT_BOOLEAN, 24, NULL, IEEE80211_RADIOTAP_F_TX_NOACK,
		  "Transmission shall not expect an ACK frame", HFILL}},

		{&hf_radiotap_txflags_noseqno,
		 {"Has Seqnum", "radiotap_rxflags_noseqno",
		  FT_BOOLEAN, 24, NULL, IEEE80211_RADIOTAP_F_TX_NOSEQNO,
		  "Frame includes a pre-configured sequence number", HFILL}},

		{&hf_radiotap_txflags_order,
		 {"Order", "radiotap_rxflags_order",
		  FT_BOOLEAN, 24, NULL, IEEE80211_RADIOTAP_F_TX_ORDER,
		  "Frame must not be reordered relative to others with this flag", HFILL}},

		{&hf_radiotap_xchannel_channel,
		 {"Channel number", "radiotap_xchannel_channel",
		  FT_UINT32, BASE_DEC, NULL, 0x0,
		  NULL, HFILL}},

		{&hf_radiotap_xchannel_frequency,
		 {"Channel frequency", "radiotap_xchannel_freq",
		  FT_UINT32, BASE_DEC, NULL, 0x0,
		  NULL, HFILL}},

		{&hf_radiotap_xchannel_flags,
		 {"Channel flags", "radiotap_xchannel_flags",
		  FT_UINT32, BASE_HEX, NULL, 0x0,
		  NULL, HFILL}},

		{&hf_radiotap_xchannel_flags_turbo,
		 {"Turbo", "radiotap_xchannel_flags_turbo",
		  FT_BOOLEAN, 24, NULL, 0x0010,
		  "Channel Flags Turbo", HFILL}},

		{&hf_radiotap_xchannel_flags_cck,
		 {"Complementary Code Keying (CCK)", "radiotap_xchannel_flags_cck",
		  FT_BOOLEAN, 24, NULL, 0x0020,
		  "Channel Flags Complementary Code Keying (CCK) Modulation", HFILL}},

		{&hf_radiotap_xchannel_flags_ofdm,
		 {"Orthogonal Frequency-Division Multiplexing (OFDM)", "radiotap_xchannel_flags_ofdm",
		  FT_BOOLEAN, 24, NULL, 0x0040,
		  "Channel Flags Orthogonal Frequency-Division Multiplexing (OFDM)", HFILL}},

		{&hf_radiotap_xchannel_flags_2ghz,
		 {"2 GHz spectrum", "radiotap_xchannel_flags_2ghz",
		  FT_BOOLEAN, 24, NULL, 0x0080,
		  "Channel Flags 2 GHz spectrum", HFILL}},

		{&hf_radiotap_xchannel_flags_5ghz,
		 {"5 GHz spectrum", "radiotap_xchannel_flags_5ghz",
		  FT_BOOLEAN, 24, NULL, 0x0100,
		  "Channel Flags 5 GHz spectrum", HFILL}},

		{&hf_radiotap_xchannel_flags_passive,
		 {"Passive", "radiotap_channel_xtype_passive",
		  FT_BOOLEAN, 24, NULL, 0x0200,
		  "Channel Flags Passive", HFILL}},

		{&hf_radiotap_xchannel_flags_dynamic,
		 {"Dynamic CCK-OFDM", "radiotap_xchannel_flags_dynamic",
		  FT_BOOLEAN, 24, NULL, 0x0400,
		  "Channel Flags Dynamic CCK-OFDM Channel", HFILL}},

		{&hf_radiotap_xchannel_flags_gfsk,
		 {"Gaussian Frequency Shift Keying (GFSK)",
		  "radiotap_xchannel_flags_gfsk",
		  FT_BOOLEAN, 24, NULL, 0x0800,
		  "Channel Flags Gaussian Frequency Shift Keying (GFSK) Modulation",
		  HFILL}},

		{&hf_radiotap_xchannel_flags_gsm,
		 {"GSM (900MHz)", "radiotap_xchannel_flags_gsm",
		  FT_BOOLEAN, 24, NULL, 0x1000,
		  "Channel Flags GSM", HFILL}},

		{&hf_radiotap_xchannel_flags_sturbo,
		 {"Static Turbo", "radiotap_xchannel_flags_sturbo",
		  FT_BOOLEAN, 24, NULL, 0x2000,
		  "Channel Flags Status Turbo", HFILL}},

		{&hf_radiotap_xchannel_flags_half,
		 {"Half Rate Channel (10MHz Channel Width)", "radiotap_xchannel_flags_half",
		  FT_BOOLEAN, 24, NULL, 0x4000,
		  "Channel Flags Half Rate", HFILL}},

		{&hf_radiotap_xchannel_flags_quarter,
		 {"Quarter Rate Channel (5MHz Channel Width)", "radiotap_xchannel_flags_quarter",
		  FT_BOOLEAN, 24, NULL, 0x8000,
		  "Channel Flags Quarter Rate", HFILL}},

		{&hf_radiotap_xchannel_flags_ht20,
		 {"HT Channel (20MHz Channel Width)", "radiotap_xchannel_flags_ht20",
		  FT_BOOLEAN, 24, NULL, 0x10000,
		  "Channel Flags HT/20", HFILL}},

		{&hf_radiotap_xchannel_flags_ht40u,
		 {"HT Channel (40MHz Channel Width with Extension channel above)", "radiotap_xchannel_flags_ht40u",
		  FT_BOOLEAN, 24, NULL, 0x20000,
		  "Channel Flags HT/40+", HFILL}},

		{&hf_radiotap_xchannel_flags_ht40d,
		 {"HT Channel (40MHz Channel Width with Extension channel below)", "radiotap_xchannel_flags_ht40d",
		  FT_BOOLEAN, 24, NULL, 0x40000,
		  "Channel Flags HT/40-", HFILL}},
#if 0
		{&hf_radiotap_xchannel_maxpower,
		 {"Max transmit power", "radiotap_xchannel_maxpower",
		  FT_UINT32, BASE_DEC, NULL, 0x0,
		  NULL, HFILL}},
#endif
		{&hf_radiotap_fhss_hopset,
		 {"FHSS Hop Set", "radiotap_fhss_hopset",
		  FT_UINT8, BASE_DEC, NULL, 0x0,
		  "Frequency Hopping Spread Spectrum hopset", HFILL}},

		{&hf_radiotap_fhss_pattern,
		 {"FHSS Pattern", "radiotap_fhss_pattern",
		  FT_UINT8, BASE_DEC, NULL, 0x0,
		  "Frequency Hopping Spread Spectrum hop pattern", HFILL}},

		{&hf_radiotap_datarate,
		 {"Data rate (Mb/s)", "radiotap_datarate",
		  FT_FLOAT, BASE_NONE, NULL, 0x0,
		  "Speed this frame was sent/received at", HFILL}},

		{&hf_radiotap_antenna,
		 {"Antenna", "radiotap_antenna",
		  FT_UINT32, BASE_DEC, NULL, 0x0,
		  "Antenna number this frame was sent/received over (starting at 0)", HFILL}},

		{&hf_radiotap_dbm_antsignal,
		 {"Antenna signal", "radiotap_dbm_antsignal",
		  FT_INT8, BASE_DEC|BASE_UNIT_STRING, &units_dbm, 0x0,
		  "RF signal power at the antenna expressed as decibels"
		  " from one milliwatt", HFILL}},

		{&hf_radiotap_db_antsignal,
		 {"dB antenna signal", "radiotap_db_antsignal",
		  FT_UINT8, BASE_DEC|BASE_UNIT_STRING, &units_decibels, 0x0,
		  "RF signal power at the antenna expressed as decibels"
		  " from a fixed, arbitrary value", HFILL}},

		{&hf_radiotap_dbm_antnoise,
		 {"Antenna noise", "radiotap_dbm_antnoise",
		  FT_INT8, BASE_DEC|BASE_UNIT_STRING, &units_dbm, 0x0,
		  "RF noise power at the antenna expressed as decibels"
		  " from one milliwatt", HFILL}},

		{&hf_radiotap_db_antnoise,
		 {"dB antenna noise", "radiotap_db_antnoise",
		  FT_UINT8, BASE_DEC|BASE_UNIT_STRING, &units_decibels, 0x0,
		  "RF noise power at the antenna expressed as decibels"
		  " from a fixed, arbitrary value", HFILL}},

		{&hf_radiotap_tx_attenuation,
		 {"TX attenuation", "radiotap_txattenuation",
		  FT_UINT16, BASE_DEC, NULL, 0x0,
		  "Transmit power expressed as unitless distance from max power"
		  " set at factory calibration (0 is max power)", HFILL}},

		{&hf_radiotap_db_tx_attenuation,
		 {"dB TX attenuation", "radiotap_db_txattenuation",
		  FT_UINT16, BASE_DEC|BASE_UNIT_STRING, &units_decibels, 0x0,
		  "Transmit power expressed as decibels from max power"
		  " set at factory calibration (0 is max power)", HFILL}},

		{&hf_radiotap_txpower,
		 {"Transmit power", "radiotap_txpower",
		  FT_INT8, BASE_DEC|BASE_UNIT_STRING, &units_dbm, 0x0,
		  "Transmit power at the antenna port expressed as decibels"
		  " from one milliwatt", HFILL}},

		{&hf_radiotap_mcs,
		 {"MCS information", "radiotap_mcs",
		  FT_NONE, BASE_NONE, NULL, 0x0,
		  NULL, HFILL}},

		{&hf_radiotap_mcs_known,
		 {"Known MCS information", "radiotap_mcs_known",
		  FT_UINT8, BASE_HEX, NULL, 0x0,
		  "Bit mask indicating what MCS information is present", HFILL}},

		{&hf_radiotap_mcs_have_bw,
		 {"Bandwidth", "radiotap_mcs_have_bw",
		  FT_BOOLEAN, 8, TFS(&tfs_present_absent), IEEE80211_RADIOTAP_MCS_HAVE_BW,
		  "Bandwidth information present", HFILL}},

		{&hf_radiotap_mcs_have_index,
		 {"MCS index", "radiotap_mcs_have_index",
		  FT_BOOLEAN, 8, TFS(&tfs_present_absent), IEEE80211_RADIOTAP_MCS_HAVE_MCS,
		  "MCS index information present", HFILL}},

		{&hf_radiotap_mcs_have_gi,
		 {"Guard interval", "radiotap_mcs_have_gi",
		  FT_BOOLEAN, 8, TFS(&tfs_present_absent), IEEE80211_RADIOTAP_MCS_HAVE_GI,
		  "Sent/Received guard interval information present", HFILL}},

		{&hf_radiotap_mcs_have_format,
		 {"Format", "radiotap_mcs_have_format",
		  FT_BOOLEAN, 8, TFS(&tfs_present_absent), IEEE80211_RADIOTAP_MCS_HAVE_FMT,
		  "Format information present", HFILL}},

		{&hf_radiotap_mcs_have_fec,
		 {"FEC type", "radiotap_mcs_have_fec",
		  FT_BOOLEAN, 8, TFS(&tfs_present_absent), IEEE80211_RADIOTAP_MCS_HAVE_FEC,
		  "Forward error correction type information present", HFILL}},

		{&hf_radiotap_mcs_have_stbc,
		 {"STBC streams", "radiotap_mcs_have_stbc",
		  FT_BOOLEAN, 8, TFS(&tfs_present_absent), IEEE80211_RADIOTAP_MCS_HAVE_STBC,
		  "Space Time Block Coding streams information present", HFILL}},

		{&hf_radiotap_mcs_have_ness,
		 {"Number of extension spatial streams", "radiotap_mcs_have_ness",
		  FT_BOOLEAN, 8, TFS(&tfs_present_absent), IEEE80211_RADIOTAP_MCS_HAVE_NESS,
		  "Number of extension spatial streams information present", HFILL}},

		{&hf_radiotap_mcs_ness_bit1,
		 {"Number of extension spatial streams bit 1", "radiotap_mcs_ness_bit1",
		  FT_UINT8, BASE_DEC, NULL, IEEE80211_RADIOTAP_MCS_NESS_BIT1,
		  "Bit 1 of number of extension spatial streams information", HFILL}},

		{&hf_radiotap_mcs_bw,
		 {"Bandwidth", "radiotap_mcs_bw",
		  FT_UINT8, BASE_DEC, VALS(mcs_bandwidth),
		  IEEE80211_RADIOTAP_MCS_BW_MASK, NULL, HFILL}},

		{&hf_radiotap_mcs_gi,
		 {"Guard interval", "radiotap_mcs_gi",
		  FT_UINT8, BASE_DEC, VALS(mcs_gi), IEEE80211_RADIOTAP_MCS_SGI,
		  "Sent/Received guard interval", HFILL}},

		{&hf_radiotap_mcs_format,
		 {"Format", "radiotap_mcs_format",
		  FT_UINT8, BASE_DEC, VALS(mcs_format), IEEE80211_RADIOTAP_MCS_FMT_GF,
		  NULL, HFILL}},

		{&hf_radiotap_mcs_fec,
		 {"FEC type", "radiotap_mcs_fec",
		  FT_UINT8, BASE_DEC, VALS(mcs_fec), IEEE80211_RADIOTAP_MCS_FEC_LDPC,
		  "Forward error correction type", HFILL}},

		{&hf_radiotap_mcs_stbc,
		 {"STBC streams", "radiotap_mcs_stbc",
		  FT_UINT8, BASE_DEC, NULL, IEEE80211_RADIOTAP_MCS_STBC_MASK,
		  "Number of Space Time Block Code streams", HFILL}},

		{&hf_radiotap_mcs_ness_bit0,
		 {"Number of extension spatial streams bit 0", "radiotap_mcs_ness_bit1",
		  FT_UINT8, BASE_DEC, NULL, IEEE80211_RADIOTAP_MCS_NESS_BIT1,
		  "Bit 0 of number of extension spatial streams information", HFILL}},

		{&hf_radiotap_mcs_index,
		 {"MCS index", "radiotap_mcs_index",
		  FT_UINT8, BASE_DEC, NULL, 0x0,
		  NULL, HFILL}},

		{&hf_radiotap_ampdu,
		 {"A-MPDU status", "radiotap_ampdu",
		  FT_NONE, BASE_NONE, NULL, 0x0,
		  NULL, HFILL}},

		{&hf_radiotap_ampdu_ref,
		 {"A-MPDU reference number", "radiotap_ampdu_reference",
		  FT_UINT32, BASE_DEC, NULL, 0x0,
		  NULL, HFILL}},

		{&hf_radiotap_ampdu_flags,
		 {"A-MPDU flags", "radiotap_ampdu_flags",
		  FT_UINT16, BASE_HEX, NULL, 0x0,
		  "A-MPDU status flags", HFILL}},

		{&hf_radiotap_ampdu_flags_report_zerolen,
		 {"Driver reports 0-length subframes in this A-MPDU", "radiotap_ampdu_flags_report_zerolen",
		  FT_BOOLEAN, 16, NULL, IEEE80211_RADIOTAP_AMPDU_REPORT_ZEROLEN,
		  NULL, HFILL}},

		{&hf_radiotap_ampdu_flags_is_zerolen,
		 {"This is a 0-length subframe", "radiotap_ampdu_flags_is_zerolen",
		  FT_BOOLEAN, 16, NULL, IEEE80211_RADIOTAP_AMPDU_IS_ZEROLEN,
		  NULL, HFILL}},

		{&hf_radiotap_ampdu_flags_last_known,
		 {"Last subframe of this A-MPDU is known", "radiotap_ampdu_flags_lastknown",
		  FT_BOOLEAN, 16, NULL, IEEE80211_RADIOTAP_AMPDU_LAST_KNOWN,
		  NULL, HFILL}},

		{&hf_radiotap_ampdu_flags_is_last,
		 {"This is the last subframe of this A-MPDU", "radiotap_ampdu_flags_last",
		  FT_BOOLEAN, 16, NULL, IEEE80211_RADIOTAP_AMPDU_IS_LAST,
		  NULL, HFILL}},

		{&hf_radiotap_ampdu_flags_delim_crc_error,
		 {"Delimiter CRC error on this subframe", "radiotap_ampdu_flags_delim_crc_error",
		  FT_BOOLEAN, 16, NULL, IEEE80211_RADIOTAP_AMPDU_DELIM_CRC_ERR,
		  NULL, HFILL}},

		{&hf_radiotap_ampdu_flags_eof,
		 {"EOF on this subframe", "radiotap_ampdu_flags_eof",
		  FT_BOOLEAN, 16, NULL, IEEE80211_RADIOTAP_AMPDU_EOF,
		  NULL, HFILL}},

		{&hf_radiotap_ampdu_flags_eof_known,
		 {"EOF of this A-MPDU is known", "radiotap_ampdu_flags_eof_known",
		  FT_BOOLEAN, 16, NULL, IEEE80211_RADIOTAP_AMPDU_EOF_KNOWN,
		  NULL, HFILL}},

		{&hf_radiotap_ampdu_delim_crc,
		 {"A-MPDU subframe delimiter CRC", "radiotap_ampdu_delim_crc",
		  FT_UINT8, BASE_HEX, NULL, 0x0,
		  NULL, HFILL}},

		{&hf_radiotap_vht,
		 {"VHT information", "radiotap_vht",
		  FT_NONE, BASE_NONE, NULL, 0x0,
		  NULL, HFILL}},

		{&hf_radiotap_vht_known,
		 {"Known VHT information", "radiotap_vht_known",
		  FT_UINT8, BASE_HEX, NULL, 0x0,
		  "Bit mask indicating what VHT information is present", HFILL}},

		{&hf_radiotap_vht_user,
		 {"User", "radiotap_vht_user",
		  FT_NONE, BASE_NONE, NULL, 0x0,
		  NULL, HFILL}},

		{&hf_radiotap_vht_have_stbc,
		 {"STBC", "radiotap_vht_have_stbc",
		  FT_BOOLEAN, 16, TFS(&tfs_present_absent), IEEE80211_RADIOTAP_VHT_HAVE_STBC,
		  "Space Time Block Coding information present", HFILL}},

		{&hf_radiotap_vht_have_txop_ps,
		 {"TXOP_PS_NOT_ALLOWED", "radiotap_vht_have_txop_ps",
		  FT_BOOLEAN, 16, TFS(&tfs_present_absent), IEEE80211_RADIOTAP_VHT_HAVE_TXOP_PS,
		  "TXOP_PS_NOT_ALLOWED information present", HFILL}},

		{&hf_radiotap_vht_have_gi,
		 {"Guard interval", "radiotap_vht_have_gi",
		  FT_BOOLEAN, 16, TFS(&tfs_present_absent), IEEE80211_RADIOTAP_VHT_HAVE_GI,
		  "Short/Long guard interval information present", HFILL}},

		{&hf_radiotap_vht_have_sgi_nsym_da,
		 {"SGI Nsym disambiguation", "radiotap_vht_have_sgi_nsym_da",
		  FT_BOOLEAN, 16, TFS(&tfs_present_absent), IEEE80211_RADIOTAP_VHT_HAVE_SGI_NSYM_DA,
		  "Short guard interval Nsym disambiguation information present", HFILL}},

		{&hf_radiotap_vht_have_ldpc_extra,
		 {"LDPC extra OFDM symbol", "radiotap_vht_ldpc_extra",
		  FT_BOOLEAN, 16, TFS(&tfs_present_absent), IEEE80211_RADIOTAP_VHT_HAVE_LDPC_EXTRA,
		  NULL, HFILL}},

		{&hf_radiotap_vht_have_bf,
		 {"Beamformed", "radiotap_vht_have_beamformed",
		  FT_BOOLEAN, 16, TFS(&tfs_present_absent), IEEE80211_RADIOTAP_VHT_HAVE_BF,
		  NULL, HFILL}},

		{&hf_radiotap_vht_have_bw,
		 {"Bandwidth", "radiotap_mcs_have_bw",
		  FT_BOOLEAN, 16, TFS(&tfs_present_absent), IEEE80211_RADIOTAP_VHT_HAVE_BW,
		  NULL, HFILL}},

		{&hf_radiotap_vht_have_gid,
		 {"Group ID", "radiotap_mcs_have_gid",
		  FT_BOOLEAN, 16, TFS(&tfs_present_absent), IEEE80211_RADIOTAP_VHT_HAVE_GID,
		  NULL, HFILL}},

		{&hf_radiotap_vht_have_p_aid,
		 {"Partial AID", "radiotap_mcs_have_paid",
		  FT_BOOLEAN, 16, TFS(&tfs_present_absent), IEEE80211_RADIOTAP_VHT_HAVE_PAID,
		  NULL, HFILL}},

		{&hf_radiotap_vht_stbc,
		 {"STBC", "radiotap_vht_stbc",
		  FT_BOOLEAN, 8, TFS(&tfs_on_off), IEEE80211_RADIOTAP_VHT_STBC,
		  "Space Time Block Coding flag", HFILL}},

		{&hf_radiotap_vht_txop_ps,
		 {"TXOP_PS_NOT_ALLOWED", "radiotap_vht_txop_ps",
		  FT_BOOLEAN, 8, NULL, IEEE80211_RADIOTAP_VHT_TXOP_PS,
		  "Flag indicating whether STAs may doze during TXOP", HFILL}},

		{&hf_radiotap_vht_gi,
		 {"Guard interval", "radiotap_vht_gi",
		  FT_UINT8, BASE_DEC, VALS(mcs_gi), IEEE80211_RADIOTAP_VHT_SGI,
		  "Short/Long guard interval", HFILL}},

		{&hf_radiotap_vht_sgi_nsym_da,
		 {"SGI Nsym disambiguation", "radiotap_vht_sgi_nsym_da",
		  FT_BOOLEAN, 8, NULL, IEEE80211_RADIOTAP_VHT_SGI_NSYM_DA,
		  "Short Guard Interval Nsym disambiguation", HFILL}},

		{&hf_radiotap_vht_ldpc_extra,
		 {"LDPC extra OFDM symbol", "radiotap_vht_ldpc_extra",
		  FT_BOOLEAN, 8, NULL, IEEE80211_RADIOTAP_VHT_LDPC_EXTRA,
		  NULL, HFILL}},

		{&hf_radiotap_vht_bf,
		 {"Beamformed", "radiotap_vht_beamformed",
		  FT_BOOLEAN, 8, NULL, IEEE80211_RADIOTAP_VHT_BF,
		  NULL, HFILL}},

		{&hf_radiotap_vht_bw,
		 {"Bandwidth", "radiotap_vht_bw",
		  FT_UINT8, BASE_DEC | BASE_EXT_STRING, &vht_bandwidth_ext, 0x0,
		  NULL, HFILL}},

		{&hf_radiotap_vht_nsts[0],
		 {"Space-time streams 0", "radiotap_vht_nsts_0",
		  FT_UINT8, BASE_DEC, NULL, 0x0,
		  "Number of Space-time streams", HFILL}},

		{&hf_radiotap_vht_nsts[1],
		 {"Space-time streams 1", "radiotap_vht_nsts_1",
		  FT_UINT8, BASE_DEC, NULL, 0x0,
		  "Number of Space-time streams", HFILL}},

		{&hf_radiotap_vht_nsts[2],
		 {"Space-time streams 2", "radiotap_vht_nsts_2",
		  FT_UINT8, BASE_DEC, NULL, 0x0,
		  "Number of Space-time streams", HFILL}},

		{&hf_radiotap_vht_nsts[3],
		 {"Space-time streams 3", "radiotap_vht_nsts_3",
		  FT_UINT8, BASE_DEC, NULL, 0x0,
		  "Number of Space-time streams", HFILL}},

		{&hf_radiotap_vht_mcs[0],
		 {"MCS index 0", "radiotap_vht_mcs_0",
		  FT_UINT8, BASE_DEC, NULL, IEEE80211_RADIOTAP_VHT_MCS,
		  "MCS index", HFILL}},

		{&hf_radiotap_vht_mcs[1],
		 {"MCS index 1", "radiotap_vht_mcs_1",
		  FT_UINT8, BASE_DEC, NULL, IEEE80211_RADIOTAP_VHT_MCS,
		  "MCS index", HFILL}},

		{&hf_radiotap_vht_mcs[2],
		 {"MCS index 2", "radiotap_vht_mcs_2",
		  FT_UINT8, BASE_DEC, NULL, IEEE80211_RADIOTAP_VHT_MCS,
		  "MCS index", HFILL}},

		{&hf_radiotap_vht_mcs[3],
		 {"MCS index 3", "radiotap_vht_mcs_3",
		  FT_UINT8, BASE_DEC, NULL, IEEE80211_RADIOTAP_VHT_MCS,
		  "MCS index", HFILL}},

		{&hf_radiotap_vht_nss[0],
		 {"Spatial streams 0", "radiotap_vht_nss_0",
		  FT_UINT8, BASE_DEC, NULL, IEEE80211_RADIOTAP_VHT_NSS,
		  "Number of spatial streams", HFILL}},

		{&hf_radiotap_vht_nss[1],
		 {"Spatial streams 1", "radiotap_vht_nss_1",
		  FT_UINT8, BASE_DEC, NULL, IEEE80211_RADIOTAP_VHT_NSS,
		  "Number of spatial streams", HFILL}},

		{&hf_radiotap_vht_nss[2],
		 {"Spatial streams 2", "radiotap_vht_nss_2",
		  FT_UINT8, BASE_DEC, NULL, IEEE80211_RADIOTAP_VHT_NSS,
		  "Number of spatial streams", HFILL}},

		{&hf_radiotap_vht_nss[3],
		 {"Spatial streams 3", "radiotap_vht_nss_3",
		  FT_UINT8, BASE_DEC, NULL, IEEE80211_RADIOTAP_VHT_NSS,
		  "Number of spatial streams", HFILL}},

		{&hf_radiotap_vht_coding[0],
		 {"Coding 0", "radiotap_vht_coding_0",
		  FT_UINT8, BASE_DEC, VALS(mcs_fec), 0x01,
		  "Coding", HFILL}},

		{&hf_radiotap_vht_coding[1],
		 {"Coding 1", "radiotap_vht_coding_1",
		  FT_UINT8, BASE_DEC, VALS(mcs_fec), 0x02,
		  "Coding", HFILL}},

		{&hf_radiotap_vht_coding[2],
		 {"Coding 2", "radiotap_vht_coding_2",
		  FT_UINT8, BASE_DEC, VALS(mcs_fec), 0x04,
		  "Coding", HFILL}},

		{&hf_radiotap_vht_coding[3],
		 {"Coding 3", "radiotap_vht_coding_3",
		  FT_UINT8, BASE_DEC, VALS(mcs_fec), 0x08,
		  "Coding", HFILL}},

		{&hf_radiotap_vht_datarate[0],
		 {"Data rate (Mb/s) 0", "radiotap_vht_datarate_0",
		  FT_FLOAT, BASE_NONE, NULL, 0x0,
		  "Speed this frame was sent/received at", HFILL}},

		{&hf_radiotap_vht_datarate[1],
		 {"Data rate (Mb/s) 1", "radiotap_vht_datarate_1",
		  FT_FLOAT, BASE_NONE, NULL, 0x0,
		  "Speed this frame was sent/received at", HFILL}},

		{&hf_radiotap_vht_datarate[2],
		 {"Data rate (Mb/s) 2", "radiotap_vht_datarate_2",
		  FT_FLOAT, BASE_NONE, NULL, 0x0,
		  "Speed this frame was sent/received at", HFILL}},

		{&hf_radiotap_vht_datarate[3],
		 {"Data rate (Mb/s) 3", "radiotap_vht_datarate_3",
		  FT_FLOAT, BASE_NONE, NULL, 0x0,
		  "Speed this frame was sent/received at", HFILL}},

		{&hf_radiotap_vht_gid,
		 {"Group Id", "radiotap_vht_gid",
		  FT_UINT8, BASE_DEC, NULL, 0x0,
		  NULL, HFILL}},

		{&hf_radiotap_vht_p_aid,
		 {"Partial AID", "radiotap_vht_paid",
		  FT_UINT16, BASE_DEC, NULL, 0x0,
		  NULL, HFILL}},

		{&hf_radiotap_timestamp,
		 {"timestamp information", "radiotap_timestamp",
		  FT_NONE, BASE_NONE, NULL, 0x0,
		  NULL, HFILL}},

		{&hf_radiotap_timestamp_ts,
		 {"timestamp", "radiotap_timestamp_ts",
		  FT_UINT64, BASE_DEC, NULL, 0x0,
		  NULL, HFILL}},

		{&hf_radiotap_timestamp_accuracy,
		 {"accuracy", "radiotap_timestamp_accuracy",
		  FT_UINT16, BASE_DEC, NULL, 0x0,
		  NULL, HFILL}},

		{&hf_radiotap_timestamp_unit,
		 {"time unit", "radiotap_timestamp_unit",
		  FT_UINT8, BASE_DEC, VALS(timestamp_unit),
		  IEEE80211_RADIOTAP_TS_UNIT_MASK,
		  NULL, HFILL}},

		{&hf_radiotap_timestamp_spos,
		 {"sampling position", "radiotap_timestamp_samplingpos",
		  FT_UINT8, BASE_DEC, VALS(timestamp_spos),
		  IEEE80211_RADIOTAP_TS_SPOS_MASK,
		  NULL, HFILL}},

		{&hf_radiotap_timestamp_flags_32bit,
		 {"32-bit counter", "radiotap_timestamp_flags_32bit",
		  FT_BOOLEAN, 8, TFS(&tfs_yes_no), IEEE80211_RADIOTAP_TS_FLG_32BIT,
		  NULL, HFILL}},

		{&hf_radiotap_timestamp_flags_accuracy,
		 {"accuracy field", "radiotap_timestamp_flags_accuracy",
		  FT_BOOLEAN, 8, TFS(&tfs_present_absent), IEEE80211_RADIOTAP_TS_FLG_ACCURACY,
		  NULL, HFILL}},

		{&hf_radiotap_vendor_ns,
		 {"Vendor namespace", "radiotap_vendor_namespace",
		  FT_BYTES, BASE_NONE, NULL, 0x0,
		  NULL, HFILL}},

		{&hf_radiotap_ven_oui,
		 {"Vendor OUI", "radiotap_vendor_oui",
		  FT_UINT24, BASE_OUI, NULL, 0x0,
		  NULL, HFILL}},

		{&hf_radiotap_ven_subns,
		 {"Vendor sub namespace", "radiotap_vendor_subns",
		  FT_UINT8, BASE_DEC, NULL, 0x0,
		  "Vendor-specified sub namespace", HFILL}},

		{&hf_radiotap_ven_skip,
		 {"Vendor data length", "radiotap_vendor_data_len",
		  FT_UINT16, BASE_DEC, NULL, 0x0,
		  "Length of vendor-specified data", HFILL}},

		{&hf_radiotap_ven_item,
		 {"Vendor data item type", "radiotap_vendor_data_item_type",
		  FT_UINT16, BASE_DEC, NULL, 0x0,
		  "Item type of vendor-specific data", HFILL}},

		{&hf_radiotap_ven_data,
		 {"Vendor data", "radiotap_vendor_data",
		  FT_NONE, BASE_NONE, NULL, 0x0,
		  "Vendor-specified data", HFILL}},

		/* Special variables */
		{&hf_radiotap_fcs_bad,
		 {"Bad FCS", "radiotap_fcs_bad",
		  FT_BOOLEAN, BASE_NONE, NULL, 0x0,
		  "Specifies if this frame has a bad frame check sequence", HFILL}},

		{&hf_radiotap_he_info_data_1,
		 {"HE Data 1", "radiotap_he_data_1",
		  FT_UINT16, BASE_HEX, NULL, 0x0,
		  "Data 1 of the HE Info field", HFILL}},

		{&hf_radiotap_he_ppdu_format,
		 {"PPDU Format", "radiotap_he_data_1_ppdu_format",
		  FT_UINT16, BASE_HEX, VALS(he_pdu_format_vals),
		  IEEE80211_RADIOTAP_HE_PPDU_FORMAT_MASK, NULL, HFILL}},

		{&hf_radiotap_he_bss_color_known,
		 {"BSS Color known", "radiotap_he_data_1_bss_color_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown),
		  IEEE80211_RADIOTAP_HE_BSS_COLOR_KNOWN, NULL, HFILL}},

		{&hf_radiotap_he_beam_change_known,
		 {"Beam Change known", "radiotap_he_data_1_beam_change_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown),
		  IEEE80211_RADIOTAP_HE_BEAM_CHANGE_KNOWN, NULL, HFILL}},

		{&hf_radiotap_he_ul_dl_known,
		 {"UL/DL known", "radiotap_he_data_1_ul_dl_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown),
		  IEEE80211_RADIOTAP_HE_UL_DL_KNOWN, NULL, HFILL}},

		{&hf_radiotap_he_data_mcs_known,
		 {"data MCS known", "radiotap_he_data_1_data_mcs_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown),
		  IEEE80211_RADIOTAP_HE_DATA_MCS_KNOWN, NULL, HFILL}},

		{&hf_radiotap_he_data_dcm_known,
		 {"data DCM known", "radiotap_he_data_1_data_dcm_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown),
		  IEEE80211_RADIOTAP_HE_DATA_DCM_KNOWN, NULL, HFILL}},

		{&hf_radiotap_he_coding_known,
		 {"Coding known", "radiotap_he_data_1_coding_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown),
		  IEEE80211_RADIOTAP_HE_CODING_KNOWN, NULL, HFILL}},

		{&hf_radiotap_he_ldpc_extra_symbol_segment_known,
		 {"LDPC extra symbol segment known", "radiotap_he_data_1_ldpc_extra_symbol_segment_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown),
		  IEEE80211_RADIOTAP_HE_LDPC_EXTRA_SYMBOL_SEGMENT_KNOWN, NULL, HFILL}},

		{&hf_radiotap_he_stbc_known,
		 {"STBC known", "radiotap_he_data_1_stbc_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown),
		  IEEE80211_RADIOTAP_HE_STBC_KNOWN, NULL, HFILL}},

		{&hf_radiotap_he_spatial_reuse_1_known,
		 {"Spatial Reuse 1 known", "radiotap_he_data_1_spatial_reuse_1_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown),
		  IEEE80211_RADIOTAP_HE_SPATIAL_REUSE_KNOWN, NULL, HFILL}},

		{&hf_radiotap_he_spatial_reuse_2_known,
		 {"Spatial Reuse 2 known", "radiotap_he_data_1_spatial_reuse_2_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown),
		  IEEE80211_RADIOTAP_HE_SPATIAL_REUSE_2_KNOWN, NULL, HFILL}},

		{&hf_radiotap_he_spatial_reuse_3_known,
		 {"Spatial Reuse 3 known", "radiotap_he_data_1_spatial_reuse_3_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown),
		  IEEE80211_RADIOTAP_HE_SPATIAL_REUSE_3_KNOWN, NULL, HFILL}},

		{&hf_radiotap_he_spatial_reuse_4_known,
		 {"Spatial Reuse 4 known", "radiotap_he_data_1_spatial_reuse_4_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown),
		  IEEE80211_RADIOTAP_HE_SPATIAL_REUSE_4_KNOWN, NULL, HFILL}},

		{&hf_radiotap_he_data_bw_ru_allocation_known,
		 {"dat BW/RU allocation known", "radiotap_he_data_1_data_bw_ru_allocation_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown),
		  IEEE80211_RADIOTAP_HE_DATA_BW_RU_ALLOCATION_KNOWN, NULL, HFILL}},

		{&hf_radiotap_he_doppler_known,
		 {"Doppler known", "radiotap_he_data_1_doppler_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown),
		  IEEE80211_RADIOTAP_HE_DOPPLER_KNOWN, NULL, HFILL}},

		{&hf_radiotap_he_info_data_2,
		 {"HE Data 2", "radiotap_he_data_2",
		  FT_UINT16, BASE_HEX, NULL, 0x0,
		  "Data 1 of the HE Info field", HFILL}},

		{&hf_radiotap_he_pri_sec_80_mhz_known,
		 {"pri/sec 80 MHz known", "radiotap_he_data_2_pri_sec_80_mhz_known",
		  FT_BOOLEAN, 16, NULL, IEEE80211_RADIOTAP_HE_PRI_SEC_80_MHZ_KNOWN,
		  NULL, HFILL}},

		{&hf_radiotap_he_gi_known,
		 {"GI known", "radiotap_he_data_2_gi_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown), IEEE80211_RADIOTAP_HE_GI_KNOWN,
		  NULL, HFILL}},

		{&hf_radiotap_he_num_ltf_symbols_known,
		 {"LTF symbols known", "radiotap_he_data_2_num_ltf_symbols_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown), IEEE80211_RADIOTAP_HE_NUM_LTF_SYMBOLS_KNOWN,
		  NULL, HFILL}},

		{&hf_radiotap_he_pre_fec_padding_factor_known,
		 {"Pre-FEC Padding Factor known", "radiotap_he_data_2_pre_fec_padding_factor_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown), IEEE80211_RADIOTAP_HE_PRE_FEC_PADDING_FACTOR_KNOWN,
		  NULL, HFILL}},

		{&hf_radiotap_he_txbf_known,
		 {"TxBF known", "radiotap_he_data_2_txbf_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown), IEEE80211_RADIOTAP_HE_TXBF_KNOWN,
		  NULL, HFILL}},

		{&hf_radiotap_he_pe_disambiguity_known,
		 {"PE Disambiguity known", "radiotap_he_data_2_pe_disambiguity_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown), IEEE80211_RADIOTAP_HE_PE_DISAMBIGUITY_KNOWN,
		  NULL, HFILL}},

		{&hf_radiotap_he_txop_known,
		 {"TXOP known", "radiotap_he_data_2_txop_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown), IEEE80211_RADIOTAP_HE_TXOP_KNOWN,
		  NULL, HFILL}},

		{&hf_radiotap_he_midamble_periodicity_known,
		 {"midamble periodicity known", "radiotap_he_data_2_midamble_periodicity_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown), IEEE80211_RADIOTAP_HE_MIDAMBLE_PERIODICITY_KNOWN,
		  NULL, HFILL}},

		{&hf_radiotap_he_ru_allocation_offset,
		 {"RU allocation offset", "radiotap_he_data_2_ru_allocation_offset",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_RU_ALLOCATION_OFFSET,
		  NULL, HFILL}},

		{&hf_radiotap_he_ru_allocation_offset_known,
		 {"RU allocation offset known", "radiotap_he_data_2_ru_allocation_offseti_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown),
			IEEE80211_RADIOTAP_HE_RU_ALLOCATION_OFFSET_KNOWN,
		  NULL, HFILL}},

		{&hf_radiotap_he_pri_sec_80_mhz,
		 {"pri/sec 80 MHz", "radiotap_he_data_2_pri_sec_80_mhz",
		  FT_BOOLEAN, 16, TFS(&tfs_pri_sec_80_mhz),
			IEEE80211_RADIOTAP_HE_PRI_SEC_80_MHZ,
		  NULL, HFILL}},

		{&hf_radiotap_he_bss_color,
		 {"BSS Color", "radiotap_he_data_3_bss_color",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_BSS_COLOR_MASK,
		  NULL, HFILL}},

		{&hf_radiotap_he_bss_color_unknown,
		 {"BSS Color unknown", "radiotap_he_data_3_bss_color_unknown",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_BSS_COLOR_MASK,
		  NULL, HFILL}},

		{&hf_radiotap_he_beam_change,
		 {"Beam Change", "radiotap_he_data_3_beam_change",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_BEAM_CHANGE,
		  NULL, HFILL}},

		{&hf_radiotap_he_beam_change_unknown,
		 {"Beam Change unknown", "radiotap_he_data_3_beam_change_unknown",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_BEAM_CHANGE,
		  NULL, HFILL}},

		{&hf_radiotap_he_ul_dl,
		 {"UL/DL", "radiotap_he_data_3_ul_dl",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_UL_DL,
		  NULL, HFILL}},

		{&hf_radiotap_he_ul_dl_unknown,
		 {"UL/DL unknown", "radiotap_he_data_3_ul_dl_unknown",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_UL_DL,
		  NULL, HFILL}},

		{&hf_radiotap_he_data_mcs,
		 {"data MCS", "radiotap_he_data_3_data_mcs",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_DATA_MCS_MASK,
		  NULL, HFILL}},

		{&hf_radiotap_he_data_mcs_unknown,
		 {"data MCS unknown", "radiotap_he_data_3_data_mcs_unknown",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_DATA_MCS_MASK,
		  NULL, HFILL}},

		{&hf_radiotap_he_data_dcm,
		 {"data DCM", "radiotap_he_data_3_data_dcm",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_DATA_DCM,
		  NULL, HFILL}},

		{&hf_radiotap_he_data_dcm_unknown,
		 {"data DCM unknown", "radiotap_he_data_3_data_dcm_unknown",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_DATA_DCM,
		  NULL, HFILL}},

		{&hf_radiotap_he_coding,
		 {"Coding", "radiotap_he_data_3_coding",
		  FT_UINT16, BASE_HEX, VALS(he_coding_vals),
		  IEEE80211_RADIOTAP_HE_CODING, NULL, HFILL}},

		{&hf_radiotap_he_coding_unknown,
		 {"Coding unknown", "radiotap_he_data_3_coding_unknown",
		  FT_UINT16, BASE_HEX, NULL,
		  IEEE80211_RADIOTAP_HE_CODING, NULL, HFILL}},

		{&hf_radiotap_he_ldpc_extra_symbol_segment,
		 {"LDPC extra symbol segment", "radiotap_he_data_3_ldpc_extra_symbol_segment",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_LDPC_EXTRA_SYMBOL_SEGMENT,
		  NULL, HFILL}},

		{&hf_radiotap_he_ldpc_extra_symbol_segment_unknown,
		 {"LDPC extra symbol segment unknown",
		   "radiotap_he_data_3_ldpc_extra_symbol_segment_unknown",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_LDPC_EXTRA_SYMBOL_SEGMENT,
		  NULL, HFILL}},

		{&hf_radiotap_he_stbc,
		 {"STBC", "radiotap_he_data_3_stbc",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_STBC,
		  NULL, HFILL}},

		{&hf_radiotap_he_stbc_unknown,
		 {"STBC unknown", "radiotap_he_data_3_stbc_unknown",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_STBC,
		  NULL, HFILL}},

		{&hf_radiotap_he_info_data_3,
		 {"HE Data 3", "radiotap_he_data_3",
		  FT_UINT16, BASE_HEX, NULL, 0x0,
		  "Data 1 of the HE Info field", HFILL}},

		{&hf_radiotap_spatial_reuse,
		 {"Spatial Reuse", "radiotap_he_data_4_spatial_reuse",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_SPATIAL_REUSE_MASK,
		  NULL, HFILL}},

		{&hf_radiotap_spatial_reuse_unknown,
		 {"Spatial Reuse unknown", "radiotap_he_data_4_spatial_reuse_unknown",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_SPATIAL_REUSE_MASK,
		  NULL, HFILL}},

		{&hf_radiotap_he_su_reserved,
		 {"Reserved", "radiotap_he_data_4_reserved_d4_fff0",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_D4_FFF0,
		  NULL, HFILL}},

		{&hf_radiotap_spatial_reuse_1,
		 {"Spatial Reuse 1", "radiotap_he_data_4_spatial_reuse_1",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_SPATIAL_REUSE_1_MASK,
		  NULL, HFILL}},

		{&hf_radiotap_spatial_reuse_1_unknown,
		 {"Spatial Reuse 1 unknown", "radiotap_he_data_4_spatial_reuse_1_unknown",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_SPATIAL_REUSE_1_MASK,
		  NULL, HFILL}},

		{&hf_radiotap_spatial_reuse_2,
		 {"Spatial Reuse 2", "radiotap_he_data_4_spatial_reuse_2",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_SPATIAL_REUSE_2_MASK,
		  NULL, HFILL}},

		{&hf_radiotap_spatial_reuse_2_unknown,
		 {"Spatial Reuse 2 unknown", "radiotap_he_data_4_spatial_reuse_2_unknown",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_SPATIAL_REUSE_2_MASK,
		  NULL, HFILL}},

		{&hf_radiotap_spatial_reuse_3,
		 {"Spatial Reuse 3", "radiotap_he_data_4_spatial_reuse_3",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_SPATIAL_REUSE_3_MASK,
		  NULL, HFILL}},

		{&hf_radiotap_spatial_reuse_3_unknown,
		 {"Spatial Reuse 3 unknown", "radiotap_he_data_4_spatial_reuse_3_unknown",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_SPATIAL_REUSE_3_MASK,
		  NULL, HFILL}},

		{&hf_radiotap_spatial_reuse_4,
		 {"Spatial Reuse 4", "radiotap_he_data_4_spatial_reuse_4",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_SPATIAL_REUSE_4_MASK,
		  NULL, HFILL}},

		{&hf_radiotap_spatial_reuse_4_unknown,
		 {"Spatial Reuse 4 unknown", "radiotap_he_data_4_spatial_reuse_4_unknown",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_SPATIAL_REUSE_4_MASK,
		  NULL, HFILL}},

		{&hf_radiotap_sta_id_user_captured,
		 {"STA-ID of user data captured for", "radiotap_he_data_4_sta_id_user",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_STA_ID_MASK,
		  NULL, HFILL}},

		{&hf_radiotap_he_mu_reserved,
		 {"Reserved", "radiotap_he_data_4_reserved_d4_b15",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_RESERVED_D4_B15,
		  NULL, HFILL}},

		{&hf_radiotap_he_info_data_4,
		 {"HE Data 4", "radiotap_he_data_4",
		  FT_UINT16, BASE_HEX, NULL, 0x0,
		  "Data 1 of the HE Info field", HFILL}},

		{&hf_radiotap_data_bandwidth_ru_allocation,
		 {"data Bandwidth/RU allocation", "radiotap_he_data_5_data_bw_ru_allocation",
		  FT_UINT16, BASE_HEX, VALS(he_data_bw_ru_alloc_vals),
		  IEEE80211_RADIOTAP_HE_DATA_BANDWIDTH_RU_ALLOC_MASK, NULL, HFILL}},

		{&hf_radiotap_data_bandwidth_ru_allocation_unknown,
		 {"data Bandwidth/RU allocation unknown",
		   "radiotap_he_data_5_data_bw_ru_allocation_unknown",
		  FT_UINT16, BASE_HEX, NULL,
		  IEEE80211_RADIOTAP_HE_DATA_BANDWIDTH_RU_ALLOC_MASK, NULL, HFILL}},

		{&hf_radiotap_gi,
		 {"GI", "radiotap_he_data_5_gi",
		 FT_UINT16, BASE_HEX, VALS(he_gi_vals), IEEE80211_RADIOTAP_HE_GI_MASK,
		 NULL, HFILL}},

		{&hf_radiotap_gi_unknown,
		 {"GI unknown", "radiotap_he_data_5_gi_unknown",
		 FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_GI_MASK,
		 NULL, HFILL}},

		{&hf_radiotap_ltf_symbol_size,
		 {"LTF symbol size", "radiotap_he_data_5_ltf_symbol_size",
		 FT_UINT16, BASE_HEX, VALS(he_ltf_symbol_size_vals),
		 IEEE80211_RADIOTAP_HE_LTF_SYMBOL_SIZE, NULL, HFILL}},

		{&hf_radiotap_ltf_symbol_size_unknown,
		 {"LTF symbol size unknown", "radiotap_he_data_5_ltf_symbol_size_unknown",
		 FT_UINT16, BASE_HEX, NULL,
		 IEEE80211_RADIOTAP_HE_LTF_SYMBOL_SIZE, NULL, HFILL}},

		{&hf_radiotap_num_ltf_symbols,
		 {"LTF symbols", "radiotap_he_num_ltf_symbols",
		  FT_UINT16, BASE_HEX, VALS(he_num_ltf_symbols_vals),
		  IEEE80211_RADIOTAP_HE_NUM_LTF_SYMBOLS_MASK, NULL, HFILL}},

		{&hf_radiotap_num_ltf_symbols_unknown,
		 {"LTF symbols unknown", "radiotap_he_num_ltf_symbols_unknown",
		  FT_UINT16, BASE_HEX, NULL,
		  IEEE80211_RADIOTAP_HE_NUM_LTF_SYMBOLS_MASK, NULL, HFILL}},

		{&hf_radiotap_d5_reserved_b11,
		 {"reserved", "radiotap_he_data_5_reserved_d5_b11",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_RESERVED_D5_B11,
		  NULL, HFILL}},

		{&hf_radiotap_pre_fec_padding_factor,
		 {"Pre-FEC Padding Factor", "radiotap_he_pre_fec_padding_factor",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_PRE_FEC_PADDING_FACTOR_MASK,
		 NULL, HFILL}},

		{&hf_radiotap_pre_fec_padding_factor_unknown,
		 {"Pre-FEC Padding Factor unknown", "radiotap_he_pre_fec_padding_factor_unknown",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_PRE_FEC_PADDING_FACTOR_MASK,
		 NULL, HFILL}},

		{&hf_radiotap_txbf,
		 {"TxBF", "radiotap_he_txbf",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_TXBF,
		  NULL, HFILL}},

		{&hf_radiotap_txbf_unknown,
		 {"TxBF unknown", "radiotap_he_txbf_unknown",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_TXBF,
		  NULL, HFILL}},

		{&hf_radiotap_pe_disambiguity,
		 {"PE Disambiguity", "radiotap_he_pe_disambiguity",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_PE_DISAMBIGUITY,
		  NULL, HFILL}},

		{&hf_radiotap_pe_disambiguity_unknown,
		 {"PE Disambiguity unknown", "radiotap_he_pe_disambiguity_unknown",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_PE_DISAMBIGUITY,
		  NULL, HFILL}},

		{&hf_radiotap_he_info_data_5,
		 {"HE Data 5", "radiotap_he_data_5",
		  FT_UINT16, BASE_HEX, NULL, 0x0,
		  "Data 1 of the HE Info field", HFILL}},

		{&hf_radiotap_he_nsts,
		 {"NSTS", "radiotap_he_data_6_nsts",
		  FT_UINT16, BASE_HEX, VALS(he_nsts_vals),IEEE80211_RADIOTAP_HE_NSTS_MASK,
		  NULL, HFILL}},

		{&hf_radiotap_he_doppler_value,
		 {"Doppler value", "radiotap_he_data_6_doppler_value",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_DOPLER_VALUE,
		  NULL, HFILL}},

		{&hf_radiotap_he_doppler_value_unknown,
		 {"Doppler value unknown", "radiotap_he_data_6_doppler_value_unknown",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_DOPLER_VALUE,
		  NULL, HFILL}},

		{&hf_radiotap_he_d6_reserved_00e0,
		 {"Reserved", "radiotap_he_data_6_reserved_d6_00e0",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_RESERVED_D6_00E0,
		  NULL, HFILL}},

		{&hf_radiotap_he_txop_value,
		 {"TXOP value", "radiotap_he_data_6_txop_value",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_TXOP_VALUE_MASK,
		  NULL, HFILL}},

		{&hf_radiotap_he_txop_value_unknown,
		 {"TXOP value unknown", "radiotap_he_data_6_txop_value_unknown",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_TXOP_VALUE_MASK,
		  NULL, HFILL}},

		{&hf_radiotap_midamble_periodicity,
		 {"midamble periodicity", "radiotap_he_data_6_midamble_periodicity",
		  FT_UINT16, BASE_HEX, VALS(he_midamble_periodicity_vals),
		  IEEE80211_RADIOTAP_HE_MIDAMBLE_PERIODICITY, NULL, HFILL}},

		{&hf_radiotap_midamble_periodicity_unknown,
		 {"midamble periodicity unknown",
		   "radiotap_he_data_6_midamble_periodicity_unknown",
		  FT_UINT16, BASE_HEX, NULL,
		  IEEE80211_RADIOTAP_HE_MIDAMBLE_PERIODICITY, NULL, HFILL}},

		{&hf_radiotap_he_info_data_6,
		 {"HE Data 6", "radiotap_he_data_6",
		  FT_UINT16, BASE_HEX, NULL, 0x0,
		  "Data 1 of the HE Info field", HFILL}},

		{&hf_radiotap_he_mu_sig_b_mcs,
		 {"SIG-B MCS (from SIG-A)", "radiotap_he_mu_sig_b_mcs",
		  FT_UINT16, BASE_HEX, NULL,
		  IEEE80211_RADIOTAP_HE_MU_SIG_B_MCS_MASK, NULL, HFILL}},

		{&hf_radiotap_he_mu_sig_b_mcs_unknown,
		 {"SIG-B MCS (from SIG-A) unknown",
		  "radiotap_he_mu_sig_b_mcs_unknown",
		  FT_UINT16, BASE_HEX, NULL,
		  IEEE80211_RADIOTAP_HE_MU_SIG_B_MCS_MASK, NULL, HFILL}},

		{&hf_radiotap_he_mu_sig_b_mcs_known,
		 {"SIG-B MCS known", "radiotap_he_mu_sig_b_mcs_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown),
		  IEEE80211_RADIOTAP_HE_MU_SIG_B_MCS_KNOWN, NULL, HFILL}},

		{&hf_radiotap_he_mu_sig_b_dcm,
		 {"SIG-B DCM (from SIG-A)", "radiotap_he_mu_sig_b_dcm",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_MU_SIG_B_DCM,
		  NULL, HFILL}},

		{&hf_radiotap_he_mu_sig_b_dcm_unknown,
		 {"SIG-B DCM (from SIG-A) unknown",
		  "radiotap_he_mu_sig_b_dcm_unknown",
		  FT_UINT16, BASE_HEX, NULL, IEEE80211_RADIOTAP_HE_MU_SIG_B_DCM,
		  NULL, HFILL}},

		{&hf_radiotap_he_mu_sig_b_dcm_known,
		 {"SIG-B DCM known", "radiotap_he_mu_sig_b_dmc_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown),
		  IEEE80211_RADIOTAP_HE_MU_SIG_B_DCM_KNOWN, NULL, HFILL}},

		{&hf_radiotap_he_mu_chan2_center_26_tone_ru_bit_known,
		 {"Channel2 center 26-tone RU bit known", "radiotap_he_mu_chan2_center_26_tone_ru_bit_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown),
		  IEEE80211_RADIOTAP_HE_MU_CHAN2_CENTER_26_TONE_RU_BIT_KNOWN, NULL, HFILL}},

		{&hf_radiotap_he_mu_chan2_center_26_tone_ru_bit_unknown,
		 {"Channel2 center 26-tone RU bit known", "radiotap_he_mu_chan2_center_26_tone_ru_bit_unknown",
		  FT_UINT16, BASE_CUSTOM, CF_FUNC(not_captured_custom),
		  IEEE80211_RADIOTAP_HE_MU_CHAN2_CENTER_26_TONE_RU_BIT_KNOWN, NULL, HFILL}},

		{&hf_radiotap_he_mu_chan1_rus_known,
		 {"Channel 1 RUs known", "radiotap_he_mu_chan1_rus_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown),
		  IEEE80211_RADIOTAP_HE_MU_CHAN1_RUS_KNOWN, NULL, HFILL}},

		{&hf_radiotap_he_mu_chan1_rus_unknown,
		 {"Channel 1 RUs unknown", "radiotap_he_mu_chan1_rus_unknown",
		  FT_UINT16, BASE_CUSTOM, CF_FUNC(not_captured_custom),
		  IEEE80211_RADIOTAP_HE_MU_CHAN1_RUS_KNOWN, NULL, HFILL}},

		{&hf_radiotap_he_mu_chan2_rus_known,
		 {"Channel 2 RUs known", "radiotap_he_mu_chan2_rus_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown),
		  IEEE80211_RADIOTAP_HE_MU_CHAN2_RUS_KNOWN, NULL, HFILL}},

		{&hf_radiotap_he_mu_chan2_rus_unknown,
		 {"Channel 2 RUs unknown", "radiotap_he_mu_chan2_rus_unknown",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown),
		  IEEE80211_RADIOTAP_HE_MU_CHAN2_RUS_KNOWN, NULL, HFILL}},

		{&hf_radiotap_he_mu_reserved_f1_b10_b11,
		 {"Reserved", "radiotap_he_mu_reserved_f1_b10_b11",
		  FT_UINT16, BASE_HEX, NULL,
		  IEEE80211_RADIOTAP_HE_MU_RESERVED_F1_B10_B11, NULL, HFILL}},

		{&hf_radiotap_he_mu_chan1_center_26_tone_ru_bit_known,
		 {"Channel1 center 26-tone RU bit known", "radiotap_he_mu_chan1_center_26_tone_ru_bit_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown),
		  IEEE80211_RADIOTAP_HE_MU_CHAN1_CENTER_26_TONE_RU_BIT_KNOWN, NULL, HFILL}},

		{&hf_radiotap_he_mu_chan1_center_26_tone_ru_bit_unknown,
		 {"Channel1 center 26-tone RU bit known", "radiotap_he_mu_chan1_center_26_tone_ru_bit_unknown",
		  FT_UINT16, BASE_CUSTOM, CF_FUNC(not_captured_custom),
		  IEEE80211_RADIOTAP_HE_MU_CHAN1_CENTER_26_TONE_RU_BIT_KNOWN, NULL, HFILL}},

		{&hf_radiotap_he_mu_chan1_center_26_tone_ru_value,
		 {"Channel1 center 26-tone RU value", "radiotap_he_mu_chan1_center_26_tone_ru_value",
		  FT_UINT16, BASE_HEX, NULL,
		  IEEE80211_RADIOTAP_HE_MU_CHAN1_CENTER_26_TONE_RU_VALUE, NULL, HFILL}},

		{&hf_radiotap_he_mu_sig_b_syms_mu_mimo_users_known,
		 {"# of HE-SIG-B Symbols/MU-MINO users known",
		  "radiotap_he_mu_symbol_cnt_or_user_cnt_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown),
		  IEEE80211_RADIOTAP_HE_MU_SYMBOL_CNT_OR_USER_CNT_KNOWN,
		  NULL, HFILL}},

		{&hf_radiotap_he_mu_info_flags_1,
		 {"HE-MU Flags 1", "radiotap_he_mu_flags_1",
		  FT_UINT16, BASE_HEX, NULL, 0x0,
		  "Flags 1 of the HE-MU Info field", HFILL}},

		{&hf_radiotap_he_mu_bw_from_bw_in_sig_a,
		 {"bandwidth from Bandwidth field in SIG-A",
			"radiotap_he_mu_bw_from_sig_a",
		  FT_UINT16, BASE_DEC, NULL,
		  IEEE80211_RADIOTAP_HE_MU_BW_FROM_BW_IN_SIG_A_MASK, NULL, HFILL}},

		{&hf_radiotap_he_mu_bw_from_bw_in_sig_a_unknown,
		 {"bandwidth from Bandwidth field in SIG-A unknown",
			"radiotap_he_mu_bw_from_sig_a_unknown",
		  FT_UINT16, BASE_DEC, NULL,
		  IEEE80211_RADIOTAP_HE_MU_BW_FROM_BW_IN_SIG_A_MASK, NULL, HFILL}},

		{&hf_radiotap_he_mu_bw_from_bw_in_sig_a_known,
		 {"bandwidth from Bandwidth field in SIG-A known",
			"radiotap_he_mu_bw_from_sig_a_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown),
		  IEEE80211_RADIOTAP_HE_MU_BW_FROM_BW_IN_SIG_A_KNOWN, NULL, HFILL}},

		{&hf_radiotap_he_mu_sig_b_compression_from_sig_a,
		 {"SIG-B compression from SIG-A", "radiotap_he_mu_sig_b_compression",
		  FT_BOOLEAN, 16, NULL,
		  IEEE80211_RADIOTAP_HE_MU_SIG_B_COMPRESSION_FROM_SIG_A,
		  NULL, HFILL}},

		{&hf_radiotap_he_mu_sig_b_compression_known,
		 {"SIG-B compression known", "radiotap_he_mu_sig_b_compression_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown),
		  IEEE80211_RADIOTAP_HE_MU_SIG_B_COMPRESSION_KNOWN, NULL, HFILL}},

		{&hf_radiotap_he_mu_sig_b_compression_unknown,
		 {"SIG-B compression unknown", "radiotap_he_mu_sig_b_compression_unknown",
		  FT_UINT16, BASE_CUSTOM, CF_FUNC(not_captured_custom),
		  IEEE80211_RADIOTAP_HE_MU_SIG_B_COMPRESSION_FROM_SIG_A, NULL, HFILL}},

		{&hf_radiotap_he_mu_sig_b_syms_mu_mimo_users,
		 {"# of HE-SIG-B Symbols or # of MU-MIMO Users",
		  "radiotap_he_mu_sig_b_syms_or_mu_mimo_users",
		  FT_UINT16, BASE_CUSTOM, CF_FUNC(he_sig_b_symbols_custom),
		  IEEE80211_RADIOTAP_HE_MU_SYMBOL_CNT_OR_USER_CNT, NULL, HFILL}},

		{&hf_radiotap_he_mu_sig_b_syms_mu_mimo_users_unknown,
		 {"# of HE-SIG-B Symbols or # of MU-MIMO Users unknown",
		  "radiotap_he_mu_sig_b_syms_or_mu_mimo_users_unknown",
		  FT_UINT16, BASE_DEC, NULL,
		  IEEE80211_RADIOTAP_HE_MU_SYMBOL_CNT_OR_USER_CNT, NULL, HFILL}},

		{&hf_radiotap_he_mu_preamble_puncturing,
		 {"preamble puncturing from Bandwidth field in HE-SIG-A",
		  "radiotap_he_mu_preamble_puncturing",
		  FT_UINT16, BASE_HEX, NULL,
		  IEEE80211_RADIOTAP_HE_MU_PREAMBLE_PUNCTURING_MASK, NULL, HFILL}},

		{&hf_radiotap_he_mu_preamble_puncturing_unknown,
		 {"preamble puncturing from Bandwidth field in HE-SIG-A unknown",
		  "radiotap_he_mu_preamble_puncturing",
		  FT_UINT16, BASE_HEX, NULL,
		  IEEE80211_RADIOTAP_HE_MU_PREAMBLE_PUNCTURING_MASK, NULL, HFILL}},

		{&hf_radiotap_he_mu_preamble_puncturing_known,
		 {"preamble puncturing from Bandwidth field in HE-SIG-A known",
		  "radiotap_he_mu_preamble_puncturing_known",
		  FT_BOOLEAN, 16, TFS(&tfs_known_unknown),
		  IEEE80211_RADIOTAP_HE_MU_PREAMBLE_PUNCTURING_KNOWN, NULL, HFILL}},

		{&hf_radiotap_he_mu_chan2_center_26_tone_ru_value,
		 {"Chan2 Center 26 Tone RU Value",
		  "radiotap_he_mu_chan2_center_26_tone_ru_value",
		  FT_UINT16, BASE_HEX, NULL,
		  IEEE80211_RADIOTAP_HE_MU_CHAN2_CENTER_26_TONE_RU_VALUE,
		  NULL, HFILL }},

		{&hf_radiotap_he_mu_reserved_f2_b12_b15,
		 {"Reserved", "radiotap_he_mu_reserved_f2_b12_b15",
		  FT_UINT16, BASE_HEX, NULL,
		  IEEE80211_RADIOTAP_HE_MU_RESERVED_F2_B12_B15, NULL, HFILL}},

		{&hf_radiotap_he_mu_info_flags_2,
		 {"HE-MU Flags 2", "radiotap_he_mu_flags_2",
		  FT_UINT16, BASE_HEX, NULL, 0x0,
		  "Flags 2 of the HE-MU Info field", HFILL}},

		{&hf_radiotap_he_mu_chan1_rus_0,
		 {"Chan1 RU[0] index", "radiotap_he_mu_chan1_rus_0_index",
		  FT_UINT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},

		{&hf_radiotap_he_mu_chan1_rus_0_unknown,
		 {"Chan1 RU[0] index unknown",
		  "radiotap_he_mu_chan1_rus_0_index_unknown",
		  FT_UINT8, BASE_CUSTOM, CF_FUNC(not_captured_custom),
		  0x0, NULL, HFILL}},

		{&hf_radiotap_he_mu_chan1_rus_1,
		 {"Chan1 RU[1] index", "radiotap_he_mu_chan1_rus_1_index",
		  FT_UINT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},

		{&hf_radiotap_he_mu_chan1_rus_1_unknown,
		 {"Chan1 RU[1] index unknown",
		  "radiotap_he_mu_chan1_rus_1_index_unknown",
		  FT_UINT8, BASE_CUSTOM, CF_FUNC(not_captured_custom),
		  0x0, NULL, HFILL}},

		{&hf_radiotap_he_mu_chan1_rus_2,
		 {"Chan1 RU[2] index", "radiotap_he_mu_chan1_rus_2_index",
		  FT_UINT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},

		{&hf_radiotap_he_mu_chan1_rus_2_unknown,
		 {"Chan1 RU[2] index unknown",
		  "radiotap_he_mu_chan1_rus_2_index_unknown",
		  FT_UINT8, BASE_CUSTOM, CF_FUNC(not_captured_custom),
		  0x0, NULL, HFILL}},

		{&hf_radiotap_he_mu_chan1_rus_3,
		 {"Chan1 RU[3] index", "radiotap_he_mu_chan1_rus_3_index",
		  FT_UINT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},

		{&hf_radiotap_he_mu_chan1_rus_3_unknown,
		 {"Chan1 RU[3] index unknown",
		  "radiotap_he_mu_chan1_rus_3_index_unknown",
		  FT_UINT8, BASE_CUSTOM, CF_FUNC(not_captured_custom),
		  0x0, NULL, HFILL}},

		{&hf_radiotap_he_mu_chan2_rus_0,
		 {"Chan2 RU[0] index", "radiotap_he_mu_chan2_rus_0_index",
		  FT_UINT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},

		{&hf_radiotap_he_mu_chan2_rus_0_unknown,
		 {"Chan2 RU[0] index unknown",
		  "radiotap_he_mu_chan2_rus_0_index_unknown",
		  FT_UINT8, BASE_CUSTOM,
		  CF_FUNC(not_captured_custom), 0x0, NULL, HFILL}},

		{&hf_radiotap_he_mu_chan2_rus_1,
		 {"Chan2 RU[1] index", "radiotap_he_mu_chan2_rus_1_index",
		  FT_UINT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},

		{&hf_radiotap_he_mu_chan2_rus_1_unknown,
		 {"Chan2 RU[1] index unknown",
		  "radiotap_he_mu_chan2_rus_1_index_unknown",
		  FT_UINT8, BASE_CUSTOM,
		  CF_FUNC(not_captured_custom), 0x0, NULL, HFILL}},

		{&hf_radiotap_he_mu_chan2_rus_2,
		 {"Chan2 RU[2] index", "radiotap_he_mu_chan2_rus_2_index",
		  FT_UINT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},

		{&hf_radiotap_he_mu_chan2_rus_2_unknown,
		 {"Chan2 RU[2] index unknown",
		  "radiotap_he_mu_chan2_rus_2_index_unknown",
		  FT_UINT8, BASE_CUSTOM,
		  CF_FUNC(not_captured_custom), 0x0, NULL, HFILL}},

		{&hf_radiotap_he_mu_chan2_rus_3,
		 {"Chan2 RU[3] index", "radiotap_he_mu_chan2_rus_3_index",
		  FT_UINT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},

		{&hf_radiotap_he_mu_chan2_rus_3_unknown,
		 {"Chan2 RU[3] index unknown",
		  "radiotap_he_mu_chan2_rus_3_index_unknown",
		  FT_UINT8, BASE_CUSTOM,
		  CF_FUNC(not_captured_custom), 0x0, NULL, HFILL}},

		{&hf_radiotap_0_length_psdu_type,
		 {"Type", "radiotap_0_len_psdu_type",
		  FT_UINT8, BASE_HEX|BASE_RANGE_STRING,
		  RVALS(zero_length_psdu_rsvals), 0x0, NULL, HFILL}},

		{&hf_radiotap_l_sig_data_1,
		 {"Data1", "radiotap_l_sig_data1",
		  FT_UINT16, BASE_HEX, NULL, 0, NULL, HFILL}},

		{&hf_radiotap_l_sig_rate_known,
		 {"rate known", "radiotap_l_sig_rate_known",
		  FT_BOOLEAN, 16, NULL,
		  IEEE80211_RADIOTAP_L_SIG_RATE_KNOWN, NULL, HFILL}},

		{&hf_radiotap_l_sig_length_known,
		 {"length known", "radiotap_l_sig_length_known",
		  FT_BOOLEAN, 16, NULL,
		  IEEE80211_RADIOTAP_L_SIG_LENGTH_KNOWN, NULL, HFILL}},

		{&hf_radiotap_l_sig_reserved,
		 {"reserved", "radiotap_l_sig_reserved",
		  FT_UINT16, BASE_HEX, NULL,
		  IEEE80211_RADIOTAP_L_SIG_RESERVED_MASK, NULL, HFILL}},

		{&hf_radiotap_l_sig_data_2,
		 {"Data2", "radiotap_l_sig_data2",
		  FT_UINT16, BASE_HEX, NULL, 0x0, NULL, HFILL}},

		{&hf_radiotap_l_sig_rate,
		 {"rate", "radiotap_l_sig_rate",
		  FT_UINT16, BASE_DEC, NULL,
		  IEEE80211_RADIOTAP_L_SIG_RATE_MASK, NULL, HFILL}},

		{&hf_radiotap_l_sig_length,
		 {"length", "radiotap_l_sig_length",
		  FT_UINT16, BASE_DEC, NULL,
		  IEEE80211_RADIOTAP_L_SIG_LENGTH_MASK, NULL, HFILL}},
	};
	static gint *ett[] = {
		&ett_radiotap,
		&ett_radiotap_tlv,
		&ett_radiotap_present,
		&ett_radiotap_present_word,
		&ett_radiotap_flags,
		&ett_radiotap_rxflags,
		&ett_radiotap_txflags,
		&ett_radiotap_channel_flags,
		&ett_radiotap_xchannel_flags,
		&ett_radiotap_vendor,
		&ett_radiotap_mcs,
		&ett_radiotap_mcs_known,
		&ett_radiotap_ampdu,
		&ett_radiotap_ampdu_flags,
		&ett_radiotap_vht,
		&ett_radiotap_vht_known,
		&ett_radiotap_vht_user,
		&ett_radiotap_timestamp,
		&ett_radiotap_timestamp_flags,
		&ett_radiotap_he_info,
		&ett_radiotap_he_info_data_1,
		&ett_radiotap_he_info_data_2,
		&ett_radiotap_he_info_data_3,
		&ett_radiotap_he_info_data_4,
		&ett_radiotap_he_info_data_5,
		&ett_radiotap_he_info_data_6,
		&ett_radiotap_he_mu_info,
		&ett_radiotap_he_mu_info_flags_1,
		&ett_radiotap_he_mu_info_flags_2,
		&ett_radiotap_he_mu_chan_rus,
		&ett_radiotap_0_length_psdu,
		&ett_radiotap_l_sig,
		&ett_radiotap_l_sig_data_1,
		&ett_radiotap_l_sig_data_2,
		&ett_radiotap_unknown_tlv,
	};
	static ei_register_info ei[] = {
		{ &ei_radiotap_invalid_header_length, { "radiotap.length.invalid", PI_MALFORMED, PI_ERROR, "The radiotap header length is less than 8 bytes", EXPFILL }},
		{ &ei_radiotap_present, { "radiotap.present.radiotap_and_vendor", PI_MALFORMED, PI_ERROR, "Both radiotap and vendor namespace specified in bitmask word", EXPFILL }},
		{ &ei_radiotap_data_past_header, { "radiotap.data_past_header", PI_MALFORMED, PI_ERROR, "Radiotap data goes past the end of the radiotap header", EXPFILL }},
		{ &ei_radiotap_invalid_data_rate, { "radiotap.vht.datarate.invalid", PI_PROTOCOL, PI_WARN, "Data rate invalid", EXPFILL }},
	};

	module_t *radiotap_module;
	expert_module_t* expert_radiotap;

	proto_radiotap =
	    proto_register_protocol("IEEE 802.11 Radiotap Capture header", "802.11 Radiotap", "radiotap");
	proto_register_field_array(proto_radiotap, hf, array_length(hf));
	proto_register_subtree_array(ett, array_length(ett));
	expert_radiotap = expert_register_protocol(proto_radiotap);
	expert_register_field_array(expert_radiotap, ei, array_length(ei));
	register_dissector("radiotap", dissect_radiotap, proto_radiotap);

	/* Subdissector table for vendor namespace, the key is OUI with sub namespace (4 bytes) */
	vendor_dissector_table = register_dissector_table("radiotap.vendor",
		"Vendor namespace", proto_radiotap, FT_UINT32, BASE_HEX);

	radiotap_module = prefs_register_protocol(proto_radiotap, NULL);
	prefs_register_bool_preference(radiotap_module, "bit14_fcs_in_header",
				       "Assume bit 14 means FCS in header",
				       "Radiotap has a bit to indicate whether the FCS is still on the frame or not. "
				       "Some generators (e.g. AirPcap) use a non-standard radiotap flag 14 to put "
				       "the FCS into the header.",
				       &radiotap_bit14_fcs);

	prefs_register_bool_preference(radiotap_module, "interpret_high_rates_as_mcs",
				       "Interpret high rates as MCS",
				       "Some generators use rates with bit 7 set to indicate an MCS, e.g. BSD. "
					   "others (Linux, AirPcap) do not.",
				       &radiotap_interpret_high_rates_as_mcs);

	prefs_register_enum_preference(radiotap_module, "fcs_handling",
				       "Whether and how to override the FCS bit",
				       "Whether to use the FCS bit, assume the FCS is always present, "
					   "or assume the FCS is never present.",
				       &radiotap_fcs_handling,
				       fcs_handling, FALSE);
}

void proto_reg_handoff_radiotap(void)
{
	dissector_handle_t radiotap_handle;
	capture_dissector_handle_t radiotap_cap_handle;

	/* handle for 802.11+radio information dissector */
	ieee80211_radio_handle = find_dissector_add_dependency("wlan_radio", proto_radiotap);

	radiotap_handle = find_dissector_add_dependency("radiotap", proto_radiotap);

	dissector_add_uint("wtap_encap", WTAP_ENCAP_IEEE_802_11_RADIOTAP,
			   radiotap_handle);

	/*
	 * The radiotap and 802.11 headers aren't stripped off for
	 * monitor-mode packets in Linux cooked captures, so dissect
	 * those frames.
	 */
	dissector_add_uint("sll.hatype", ARPHRD_IEEE80211_RADIOTAP,
			   radiotap_handle);

	radiotap_cap_handle = create_capture_dissector_handle(capture_radiotap, proto_radiotap);
	capture_dissector_add_uint("wtap_encap", WTAP_ENCAP_IEEE_802_11_RADIOTAP, radiotap_cap_handle);

	ieee80211_cap_handle = find_capture_dissector("ieee80211");
	ieee80211_datapad_cap_handle = find_capture_dissector("ieee80211_datapad");
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
