/* dissect_opts.c
 * Routines for dissection options setting
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include <config.h>

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <errno.h>

#include <glib.h>

#include <epan/prefs.h>
#include <epan/timestamp.h>
#include <epan/addr_resolv.h>
#include <epan/disabled_protos.h>

#include "ui/decode_as_utils.h"

#if defined(HAVE_HEIMDAL_KERBEROS) || defined(HAVE_MIT_KERBEROS)

#include <epan/dissectors/read_keytab_file.h>

#endif

#include <ui/clopts_common.h>
#include <ui/cmdarg_err.h>
#include <wsutil/file_util.h>

#include "ui/dissect_opts.h"

dissect_options global_dissect_options;

void
dissect_opts_init(void) {
    global_dissect_options.time_format = TS_NOT_SET;
    global_dissect_options.disable_protocol_slist = NULL;
    global_dissect_options.enable_protocol_slist = NULL;
    global_dissect_options.enable_heur_slist = NULL;
    global_dissect_options.disable_heur_slist = NULL;
}

gboolean
dissect_opts_handle_opt(int opt, char *optarg_str_p) {
    char badopt;

    switch (opt) {
        case 'd':        /* Decode as rule */
            if (!decode_as_command_option(optarg_str_p))
                return FALSE;
            break;
        case 'K':        /* Kerberos keytab file */
#if defined(HAVE_HEIMDAL_KERBEROS) || defined(HAVE_MIT_KERBEROS)
            read_keytab_file(optarg_str_p);
#else
        cmdarg_err("-K specified, but Kerberos keytab file support isn't present");
        return FALSE;
#endif
            break;
        case 'n':        /* No name resolution */
            disable_name_resolution();
            break;
        case 'N':        /* Select what types of addresses/port #s to resolve */
            badopt = string_to_name_resolve(optarg_str_p, &gbl_resolv_flags);
            if (badopt != '\0') {
                cmdarg_err("-N specifies unknown resolving option '%c'; valid options are:",
                           badopt);
                cmdarg_err_cont("\t'd' to enable address resolution from captured DNS packets\n"
                                "\t'm' to enable MAC address resolution\n"
                                "\t'n' to enable network address resolution\n"
                                "\t'N' to enable using external resolvers (e.g., DNS)\n"
                                "\t    for network address resolution\n"
                                "\t't' to enable transport-layer port number resolution\n"
                                "\t'v' to enable VLAN IDs to names resolution");
                return FALSE;
            }
            break;
        case 't':        /* Time stamp type */
            if (strcmp(optarg_str_p, "r") == 0)
                global_dissect_options.time_format = TS_RELATIVE;
            else if (strcmp(optarg_str_p, "a") == 0)
                global_dissect_options.time_format = TS_ABSOLUTE;
            else if (strcmp(optarg_str_p, "ad") == 0)
                global_dissect_options.time_format = TS_ABSOLUTE_WITH_YMD;
            else if (strcmp(optarg_str_p, "adoy") == 0)
                global_dissect_options.time_format = TS_ABSOLUTE_WITH_YDOY;
            else if (strcmp(optarg_str_p, "d") == 0)
                global_dissect_options.time_format = TS_DELTA;
            else if (strcmp(optarg_str_p, "dd") == 0)
                global_dissect_options.time_format = TS_DELTA_DIS;
            else if (strcmp(optarg_str_p, "e") == 0)
                global_dissect_options.time_format = TS_EPOCH;
            else if (strcmp(optarg_str_p, "u") == 0)
                global_dissect_options.time_format = TS_UTC;
            else if (strcmp(optarg_str_p, "ud") == 0)
                global_dissect_options.time_format = TS_UTC_WITH_YMD;
            else if (strcmp(optarg_str_p, "udoy") == 0)
                global_dissect_options.time_format = TS_UTC_WITH_YDOY;
            else {
                cmdarg_err("Invalid time stamp type \"%s\"; it must be one of:", optarg_str_p);
                cmdarg_err_cont("\t\"a\"    for absolute\n"
                                "\t\"ad\"   for absolute with YYYY-MM-DD date\n"
                                "\t\"adoy\" for absolute with YYYY/DOY date\n"
                                "\t\"d\"    for delta\n"
                                "\t\"dd\"   for delta displayed\n"
                                "\t\"e\"    for epoch\n"
                                "\t\"r\"    for relative\n"
                                "\t\"u\"    for absolute UTC\n"
                                "\t\"ud\"   for absolute UTC with YYYY-MM-DD date\n"
                                "\t\"udoy\" for absolute UTC with YYYY/DOY date");
                return FALSE;
            }
            break;
        case 'u':        /* Seconds type */
            if (strcmp(optarg_str_p, "s") == 0)
                timestamp_set_seconds_type(TS_SECONDS_DEFAULT);
            else if (strcmp(optarg_str_p, "hms") == 0)
                timestamp_set_seconds_type(TS_SECONDS_HOUR_MIN_SEC);
            else {
                cmdarg_err("Invalid seconds type \"%s\"; it must be one of:", optarg_str_p);
                cmdarg_err_cont("\t\"s\"   for seconds\n"
                                "\t\"hms\" for hours, minutes and seconds");
                return FALSE;
            }
            break;
        case LONGOPT_DISABLE_PROTOCOL: /* disable dissection of protocol */
            global_dissect_options.disable_protocol_slist = g_slist_append(
                    global_dissect_options.disable_protocol_slist, optarg_str_p);
            break;
        case LONGOPT_ENABLE_HEURISTIC: /* enable heuristic dissection of protocol */
            global_dissect_options.enable_heur_slist = g_slist_append(global_dissect_options.enable_heur_slist,
                                                                      optarg_str_p);
            break;
        case LONGOPT_DISABLE_HEURISTIC: /* disable heuristic dissection of protocol */
            global_dissect_options.disable_heur_slist = g_slist_append(global_dissect_options.disable_heur_slist,
                                                                       optarg_str_p);
            break;
        case LONGOPT_ENABLE_PROTOCOL: /* enable dissection of protocol (that is disableed by default) */
            global_dissect_options.enable_protocol_slist = g_slist_append(global_dissect_options.enable_protocol_slist,
                                                                          optarg_str_p);
            break;
        default:
            /* the caller is responsible to send us only the right opt's */
            g_assert_not_reached();
    }
    return TRUE;
}

gboolean
setup_enabled_and_disabled_protocols(void) {
    gboolean success = TRUE;
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "arp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "9p");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aarp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "acse");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "adwin_config");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "afs");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ajns");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "amt");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "asap");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "asphodel");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ax4000");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "babel");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bacapp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bacnet");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bicc");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bitcoin");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bvlc");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "c1222");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ccp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cdpcp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cflow");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cfm");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "chap");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "chargen");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cimetrics");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cmp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cnip");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "coap");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cotp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "couchbase");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cvspserver");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dec_dna");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dect");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dis");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "distcc");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "djiuav");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dlep");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dnp3");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dof");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dof_dnp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dof_dpp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dof_esp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dof_tep1");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dof_trp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dtps");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dvb-ci");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dvmrp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "eap");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "eapol");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "elmi");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "epl");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "epl_v1");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "epm");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "exec");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fip");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fix");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "frame");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gearman");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gift");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "glbp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gnutella");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gnw");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "goose");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gopher");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gsm_a_bssmap");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gtpv2");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "h225");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "h248");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hcrt");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hiqnet");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hsrp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "icap");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "imf");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "infiniband");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipaccess");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipars");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipcp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipv6cp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipxsap");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "irc");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "iscsi");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ixveriwave");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "kink");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "kip");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "kismet");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "knet");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "kpasswd");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lapb");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lcp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lisp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "llrp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lmi");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lon");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lsd");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "m2pa");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mac");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "manolito");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mcpe");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mdns");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "messenger");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mih");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mikey");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mms");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mndp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mount");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "msnlb");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "msnms");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mstp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nano");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nbap");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nbipx");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nbss");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ndmp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "netlink");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "netlink-netfilter");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "netlink-route");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "netmon_filter");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "netmon_network_info");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nfs");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "oampdu");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ocsp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "oicq");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "openflow");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "openflow_v1");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "openflow_v4");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "opensafety");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "opensafety_udp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "openvpn");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "osi");    //20211208MZY isis协议的解析依赖于osi协议 //
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pagp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pap");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pfcp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pppoed");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pres");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ptp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pvfs");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "q931");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "q933");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "quake");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "quake3");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "quic");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "r3");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "raknet");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ranap");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ripng");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rmi");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rpc");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rsh");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rsync");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rx");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "s101");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "s5066dts");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "s5066sis");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "s7comm");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sabp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "samr");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "scsi");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ses");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sflow");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "slarp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "smb2");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "smpp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "socks");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "srvloc");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "steam_ihs_discovery");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sv");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "syscall");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sysdig");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "t38");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tacplus");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tetra");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tfp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tipc");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tns");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tpkt");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tpm");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ts2");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tte");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tzsp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ua");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "uaudp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "udld");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "uftp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "uftp4");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "uftp5");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ulp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "usb");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "usbaudio");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "usbccid");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "usbcom");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "usbdfu");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "usbhid");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "usbhub");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "usbms");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "usbport");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "uts");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vicp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vssmonitoring");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wbxml");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wccp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wg");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "whois");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "winsrepl");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wol");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wow");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "x11");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "x25");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "x509af");  /*解析TLS1.2协议的证书时需要用到x509系列协议，否则证书内容无法解析*/
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_aps");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_beacon");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_nwk");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zebra");

    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "amqp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "asterix");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "atm");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bfd");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bgp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cdp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "classicstun");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cldap");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dhcp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dhcpv6");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dns");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dtls");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dtp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "edonkey");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "eigrp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "erf");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "esp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "eth");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "etherip");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ethertype");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "finger");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fr");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ftp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ftp-data");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gre");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gtp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "h261");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "h263");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "h264");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "h323");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "http");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "http2");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "http3");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "iax2");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "icmp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "icmpv6");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "igmp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "imap");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ip");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipfc");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipv6");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "isakmp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "isis");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "isis_csnp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "isis_hello");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "isis_lsp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "isis_psnp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "isl");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "isup");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "kafka");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "kerberos");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "l2tp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lacp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lapd");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ldap");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ldp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "llc");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "llcgprs");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lldp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "llmnr");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "m3ua");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "megaco");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mgcp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mongo");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mpls");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mqtt");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "msdp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mtp2");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mtp3");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mysql");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nbns");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ndp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "netbios");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nhrp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nntp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ntp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ospf");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ospf");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pgsql");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pim");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pop");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ppp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ppp_hdlc");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pppoe");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pptp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "prism");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "radius");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rdp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rip");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rip");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rsvp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rtcp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rtp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rtp_rfc2198");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rtps");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rtsp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "s1ap");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sap");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sccp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sctp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sdp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sip");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sita");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "skinny");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "skype");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "smb");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "smtp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "snmp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ssdp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ssh");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "stp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "stun");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "syslog");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tacacs");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcap");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tdma");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tds");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "telnet");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tftp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tls");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "twamp_control");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "twamp_test");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "udp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vlan");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vrrp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wlan");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wlan_aggregate");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wlan_centrino");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wlan_ext");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wlan_radio");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wlan_rsna_eapol");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wpan");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wpan-nonask-phy");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wpan-tap");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wpan-zboss");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "xmpp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "xtp");

//global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bssap");
//global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bssap_plus");
//global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gsm_a_dtap");
//global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gsm-r-uus1");
//global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ah");
//global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aodv");
//global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bfd_echo");
//global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bootparams");
//global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cgmp");
//global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "chdlc");
//global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dap");
//global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "data-l1-events");
//global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dcerpc");
//global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "6lowpan");
//global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "adp");
   // global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "adwin");
   // global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "amf");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "amp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ancp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aoe");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bicc_mst");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bittorrent");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "browser");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btl2cap");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btpb");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btsdp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "capwap");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "capwap_data");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cattp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cbor");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cigi");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cops");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "diameter");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dicom");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dof_oap");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dplay");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "drbd");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "drda");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dsi");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dsr");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "e1ap");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "epmd");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "esio");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "f1ap");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "f5ethtrailer");
   //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fc");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fcels");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ftam");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gsm_ipa");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gvrp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "h223");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "h245");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "homeplug");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "i1d3");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "iec60870_104");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipx");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "its");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "jxta");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "jxta_message");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "kdsp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lat");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "llt");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lpp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "macc");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "magic");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mailslot");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mapi");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "misc");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mmse");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mp2t");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mpeg");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nbdgm");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nbp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "netlink-sock_diag");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ngap");


    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "openflow_v5");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "openflow_v6");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "osinlcp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "osinlcp_opt_def_pid");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "p1");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pana");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pgm");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pwethcw");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "qllc");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "quake2");
   // global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "radiotap");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "redback");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "remunk");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "remunk2");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rlogin");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rmcp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rpl");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rtmp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rudp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sbus");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "siii");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "slow");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sna");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tali");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "teredo");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "trill");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tte_pcf");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "u3v");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "uma");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vnc");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vtp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wlccp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wsp");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "x509ce");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "x509if");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "x509sat");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "xml");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "xnap");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "xot");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zip");


    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hdcp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hdcp2");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ieee8021ad");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ieee8021cb");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ieee802a");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nl80211");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ieee1722");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ieee17221");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "iec61883");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aaf");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "acf");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "acf-can");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "acf-lin");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "crf");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cvf");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ntscf");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tscf");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "2dparityfec");
    //global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "3comxns");



    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aj");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ardp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hi2operations");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "isystemactivator");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "a11");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "a21");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "a615a");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aasp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gsm_abis_om2000");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gsm_abis_oml");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gsm_abis_pgsl");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gsm_abis_tfp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "acap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "acdr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "acn");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rdmnet");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "acp133");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "acr122");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "clacse");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "actrace");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "adb");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "adb_cs");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "adb_service");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aeron");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "afp");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "agentx");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aim");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aim_admin");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aim_adverts");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aim_bos");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aim_buddylist");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aim_chat");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aim_chatnav");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aim_dir");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aim_email");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aim_generic");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aim_icq");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aim_invitation");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aim_location");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aim_messaging");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aim_popup");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aim_signon");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aim_ssi");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aim_sst");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aim_stats");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aim_translate");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aim_lookup");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ain");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ajp13");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "alc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "alcap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "amqp_version_v0_9");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "amqp_version_v0_10");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "amqp_version_v1_0");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "amr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "amr_wb");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ans");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ansi_637_tele");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ansi_637_trans");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ansi_683");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ansi_801");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ansi_a_bsmap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ansi_a_dtap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ansi_map");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ansi_tcap");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aol");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ap1394");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "applemidi");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aprs");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aptx");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ar_drone");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "arcnet");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "armagetronad");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "atmarp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "artemis");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "artnet");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aruba_erm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aruba_erm_type0");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aruba_erm_type1");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aruba_erm_type2");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aruba_erm_type3");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aruba_erm_type4");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aruba_erm_type5");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aruba_erm_type6");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aruba_iap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ascend");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "asf");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "at");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "llap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ddp");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "atp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "asp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "prap");


    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ath");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aal1");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "aal3_4");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "oamaal");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ilmi");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lane");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "atmtcp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "atn-cm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "atn-cpdlc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "atn-ulcs");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "auto_rp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "autosar-nm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "avsp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "awdl_data");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "awdl");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ax25");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ax25_kiss");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ax25_nol3");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dx");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ayiya");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bacp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bacp_opt_favored_peer");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "banana");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bap_opt_link_type");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bap_opt_phone_delta");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bap_opt_no_phone");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bap_opt_reason");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bap_opt_link_disc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bap_opt_call_status");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "basicxid");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bat");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bat_gw");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bat_vis");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "batadv");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bcp_bpdu");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bcp_ncp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bcp_ncp_opt_bridge_id");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bcp_ncp_opt_line_id");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bcp_ncp_opt_mac_sup");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bcp_ncp_opt_tinygram_comp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bcp_ncp_opt_lan_id");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bcp_ncp_opt_mac_addr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bcp_ncp_opt_stp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bcp_ncp_opt_ieee_802_tagged_frame");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bcp_ncp_opt_management_inline");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bcp_ncp_opt_bcp_ind");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bctp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "beep");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bencode");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ber");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bfcp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bjnp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "blip");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bluecom");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bluetooth");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bmc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bmp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bofl");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bpq");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "brcm-tag");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "brdwlk");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "brp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bssgp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bt3ds");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bt-dht");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bt-utp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bta2dp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bta2dp_content_protection_header_scms_t");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "alt_beacon");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ibeacon");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bluetooth_gaen");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btamp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btatt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btavctp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btavdtp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btavrcp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btbnep");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btbredr_rf");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btcommon");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btdun");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgnss");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bthci_acl");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bthci_cmd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bthci_evt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bthci_iso");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bthci_sco");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bthci_vendor_broadcom");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bthci_vendor_intel");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bthcrp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bthfp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bthid");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bthsp");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btle");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btle_rf");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btmcap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btmesh");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "beacon");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pbadv");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "provisioning");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btmproxy");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btpa");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btrfcomm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btsap");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btsmp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btsnoop");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btspp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btvdp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btvdp_content_protection_header_scms_t");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "budb");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bundle");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcpcl");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "butc");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bzr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "c15_ch");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "c15");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "c15_tone");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "c15_inc_gwe");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "c15_out_gwe");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "c15hbeat");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "calcappprotocol");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "camel");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "canopen");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "etsi_cat");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "carp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cast");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dct2000");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cbcp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cbcp_opt_no_callback");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cbcp_opt_callback_user");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cbcp_opt_callback_admin");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cbcp_opt_callback_list");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cbrs_oids");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gsm_cbs");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cbsp");


    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ccp_opt_oui");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ccp_opt_predict1");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ccp_opt_predict2");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ccp_opt_puddle");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ccp_opt_hpppc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ccp_opt_stac");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ccp_opt_stac_ascend");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ccp_opt_mppe");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ccp_opt_gfza");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ccp_opt_v42bis");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ccp_opt_bsdcomp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ccp_opt_lzsdcp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ccp_opt_mvrca");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ccp_opt_dce");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ccp_opt_deflate");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ccp_opt_v44lzjh");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ccsds");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ccsrl");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cdma2k");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cds_clerkserver");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cds_solicit");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cdt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cemi");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ceph");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pkix-cert");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cesoeth");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cfdp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "chargingase");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cimd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cip");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cipcls");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cipcm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cippccc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cipmb");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cipcco");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cipm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cipm3");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cipsafety");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cipsafety_bd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cipsafety_ed");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cipsafety_bt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cipsafety_et");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cipssupervisor");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cipsvalidator");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cl3");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cl3dcw");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "clearcase");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "clip");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "clique-rm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "clnp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "clsp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cltp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cmd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cmip");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cmpp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cms");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "collectd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "communityid");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "comp_data");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "componentstatusprotocol");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "conv");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "corosync_totemnet");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "corosync_totemsrp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cosine");


    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cp2179");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cpfi");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cpha");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cprpc_server");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cql");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "credssp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "crmf");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "csm_encaps");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "csn1");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ctdb");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cups");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cwids");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "daap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "data");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "daytime");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "db-lsp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "db-lsp-disc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dbus");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dcc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dccp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dce_update");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "atsvc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bossvr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rpc_browser");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "clusapi");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dnsserver");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dssetup");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "efs");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "eventlog");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "frsapi");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "frsrpc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "frstrans");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fsrvp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "initshutdown");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "iremotewinspool");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lsarpc");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mdssvc");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "netdfs");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rpc_netlogon");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nspi");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pnp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rfr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rras");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rs_plcy");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "spoolss");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "srvsvc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "svcctl");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tapi");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "trksvr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "winreg");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "witness");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wkssvc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wzcsvc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dcom");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dispatch");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "provideclassinfo");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "typeinfo");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dcp-etsi");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dcp-af");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dcp-pft");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dcp-tpl");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ddtp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dec_stp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "devicenet");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dhcpfo");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dhcpv6_bulk_leasequery");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "diameter_3gpp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "disp");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dlm3");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dlsw");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dlt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dmp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dmx");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dmx_chan");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dmx_sip");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dmx_test");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dmx_text");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_mgmt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_sync");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_ucd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_map");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_map");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_rngreq");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_rngrsp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_regreq");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_regrsp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_uccreq");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_uccrsp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_bpkm_req");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_bpkm_rsp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_regack");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_dsareq");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_dsarsp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_dsaack");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_dscreq");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_dscrsp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_dscack");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_dsdreq");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_dsdrsp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_dccreq");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_dccrsp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_dccack");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_type29ucd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_intrngreq");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_dcd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_mdd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_bintrngreq");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_type35ucd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_dbcreq");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_dbcrsp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_dbcack");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_dpv_req");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_dpv_rsp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_cmstatus");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_cmstatusack");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_cmctrl_req");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_cmctrlrsp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_regreqmp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_regrspmp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_emreq");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_emrsp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_ocd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_dpd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_type51ucd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_optreq");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_optrsp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_optack");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_rba");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_tlv");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_vsif");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dof-tcp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dof-udp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dof_oid");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dof_dnp_v0");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dof_dnp_v1");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dof_dpp_v0");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dof_dpp_v2");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dof_dpp_v2s");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dof_app");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dof_ccm_app");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dof_ccm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dof_ccm_dsp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dof_oap_dsp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dof_sgmp");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dof_tep1_dsp");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dof_trp_dsp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "doip");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dop");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dpaux");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dpauxmon");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dpnet");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dpnss");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dpnss_link");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "drb");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "drsuapi");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mpeg_dsmcc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dsp");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dtcp-ip");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dtpt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dtsprovider");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dtsstime_req");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dua");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dvb_ait");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dvb_bat");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dvb_data_mpe");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dvb_eit");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dvb_ipdc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dvb_nit");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dvb-s2_modeadapt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dvb-s2_bb");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dvb-s2_gse");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dvb-s2_table");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dvb_sdt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dvb_tdt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dvb_tot");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dxl");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "e100");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "e164");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "e212");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ebhscr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "echo");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ecmp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ecp21");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ecp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ecpri");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "edp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "eero");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "egd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ehdlc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ehs");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "eiss");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "elasticsearch");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "elcom");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "elf");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "enc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "enip");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cipio");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cipio1");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dlr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "enrp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "enttec");


    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "epm4");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "epon");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "erldp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "erspan");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cisco-erspan3-marker");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "esis");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ess");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "etag");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "etch");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "etv-dii");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "etv-ddb");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "evrc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "evrcb");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "evrcwb");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "evrcnw");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "evrcnw2k");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "evrc_legacy");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "evs");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "exablaze");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "exported_pdu");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "f5ethtrailer_provider_noise");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "f5ethtrailer_tls");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "f5fileinfo");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fb_zero");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fcsof");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fc00");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fcct");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fcdns");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fcs");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fcfzs");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fcgi");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fcip");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fcoe");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fcoib");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fcp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fcsb3");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fcsp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "swils");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fddi");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fdp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fefd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "felica");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ff");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "file");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "file-pcap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fileexp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fldb");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "flexnet");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "flexray");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "flip");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fmp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fmp_notify");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fmtp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "forces");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fortinet_sso");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fp_hint");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fp_mux");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fpp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fractalgeneratorprotocol");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pkt_comment");


    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ftdi-ft");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ftdi-mpsse");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ftserver");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "fw1");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "g723");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gadu-gadu");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gbcs_gbz");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gbcs_message");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gbcs_tunnel");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gcsna");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gdb");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gdsdb");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ged125");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gelf");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "geneve");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gfp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "image-gif");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "giop");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "giop-coseventcomm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "giop-cosnaming");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "giop-gias");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "giop-parlay");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "giop-tango");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "git");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "glow");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "glusterfs_cbk");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gluster_cli");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gluster_dump");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "glusterd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "glusterd_mgmt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "glusterd_brick");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "glusterd_friend");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "glusterfs_hndsk");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gluster_pmap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "glusterfs");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gmhdr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gmtrailer");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gmr1_bcch");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gmr1_common");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gmr1_dtap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gmr1_rach");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gmr1_rr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gmr1_ccch");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gmrp");


    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gpef");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gprscdr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gquic");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "grpc");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gsm_a");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "3gpp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gsm_a_gm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gsm_a_rp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gsm_a_rr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gsm_a_ccch");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gsm_a_sacch");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gsm_a_ec_ccch");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bsslap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gsm_bssmap_le");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gsm_cbch");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gsm_map");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gsm_rlcmac");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gsm_sim");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gsm_sms");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gsm_sms_ud");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gsm_um");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gsmtap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gsmtap_log");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gss-api");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gsup");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gtpprime");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nrup");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gvcp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gvsp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "h1");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "h223_bitswapped");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "h225_ras");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "h235");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "h248_3gpp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "h248_an");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "h248_annexc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "h248e");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "h248_chp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "h248_2");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "h263p");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "h265");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rdc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lct");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "h450");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "h450_ros");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "h460");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "h501");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hart_ip");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hzlcst");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hbbak");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hci_h1");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hci_h4");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hci_mon");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hci_usb");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hclnfsd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hdfs");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hdfsdata");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hdmi");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hip");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hislip");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hl7");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hnbap");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "homeplug-av");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hpna");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hp_erm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hpext");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hpfeeds");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hpsw");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hpteam");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hsms");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hsr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hsr_prp_supervision");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "urlencoded-form");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "hyperscsi");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "i2c");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "i2c_event");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "i2c_data");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "iapp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "infiniband_sdp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "icall");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "icep");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "icl_rpc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "icp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "icq");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "idmp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "idn");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "idp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "idrp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "iec60870_101");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "iec60870_asdu");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ieee1609dot2");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ieee1905");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wlancap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ieee8021ah");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ifcp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "igap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "igrp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ilp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "inap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "infiniband_link");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "infiniband_eoib");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "interlink");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ip_options_eol");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ip_options_nop");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ip_options_security");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ip_options_route");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ip_options_timestamp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ip_options_ext_security");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ip_options_cipso");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ip_options_record_route");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ip_options_sid");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ip_options_source_route");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ip_options_mtu_probe");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ip_options_mtu_reply");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ip_options_traceroute");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ip_options_routeralert");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ip_options_sdb");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ip_options_qs");


    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipcp_opt_addrs");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipcp_opt_compress");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipcp_opt_addr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipcp_opt_mobileipv4");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipcp_opt_pri_dns");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipcp_opt_pri_nbns");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipcp_opt_sec_dns");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipcp_opt_sec_nbns");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipcp_opt_rohc_profile_bytes");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipcp_opt_iphc_rtp_compress");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipcp_opt_iphc_enhanced_rtp_compress");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipcp_opt_iphc_neghdrcomp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipdc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipdr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipdr_samis_type_1");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "iperf2");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "crtp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "crtp_cudp16");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "crtp_cudp8");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "crtp_cs");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "crtp_cntcp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipmi");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipmb");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "kcs");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tmode");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipmi_session");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipmi_trace");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipnet");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipoib");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipos");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ippusb");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipcomp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipsictl");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipv6_hopopts");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipv6_routing");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipv6_routing_type_rt0");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipv6_routing_type_mipv6");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipv6_routing_type_mipv6");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipv6_routing_type_srh");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipv6_fraghdr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipv6_dstopts");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipv6cp_opt_interface_identifier");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipv6cp_opt_compress");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipvs");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "spx");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipxrip");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nw_serial");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipxmsg");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ipxwan");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "isdn");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "isdn_sup");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "iser");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "isi");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ismacryp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ismacryp_v11");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ismacryp_v20");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ismp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "isns");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "iso14443");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "iso15765");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "iso7816");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "iso7816_atr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "iso8583");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "bthci_iso_data");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "isobus");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "isobus_vt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "itdm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "its_message_denm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "its_message_denmv1");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "its_message_cam");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "its_message_camv1");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "its_message_spatemv1");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "its_message_spatem");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "its_message_mapemv1");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "its_message_mapem");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "its_message_ivimv1");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "its_message_ivim");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "its_message_evrsr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "its_message_srem");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "its_message_ssem");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "its_message_rtcmem");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "its_message_evcsn");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "its_message_tistpg");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dsrc_addgrpc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "iua");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "iuup");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "iwarp_ddp_rdmap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ixiatrailer");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "j1939");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "jdwp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "image-jfif");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "jmirror");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "jpeg");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "json");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "juniper");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "k12");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "kadm5");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "kdp");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "kf");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "klm");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "krb4");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "krb5rpc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "kt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lanforge");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lapbether");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lapdm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "laplink");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lapsat");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "29west");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lbmc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lbmpdm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lbmpdm_tcp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lbmr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lbmsrs");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lbtrm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lbtru");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lbttcp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lcp_opt_vendor");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lcp_opt_mtu_bytes");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lcp_opt_asyncmap_bytes");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lcp_opt_auth_protocol_bytes");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lcp_opt_quality_protocol_bytes");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lcp_opt_magic_number_bytes");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lcp_opt_linkqualmon");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lcp_opt_field_compress");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lcp_opt_addr_field_compress");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lcp_opt_fcs_alternatives_bytes");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lcp_opt_self_desc_pad");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lcp_opt_numbered_mode");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lcp_opt_callback");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lcp_opt_compound_frames");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lcp_opt_nomdataencap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lcp_opt_multilink_mrru");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lcp_opt_multilink_ssnh");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lcp_opt_multilink_ep_disc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lcp_opt_dce_identifier");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lcp_opt_multilink_pp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lcp_opt_link_discrim_bytes");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lcp_opt_auth");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lcp_opt_cobs");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lcp_opt_prefix_elision");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lcp_opt_multilink_hdr_fmt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lcp_opt_internationalization");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lcp_opt_sonet_sdh");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lcsap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ldac");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ldss");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lg8979");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lge_monitor");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "link16");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "linx");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "linxtcp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lisp-data");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lisp-tcp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lithionics_bms");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "llb");


    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lltd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lmp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lnet");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lnpdqp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "log3gpp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "logcat");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "logcat_text");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "logotypecertextn");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "loop");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "loratap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lorawan");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lpd");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lppa");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lppe");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lsc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lte_rrc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ltp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lustre");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lwapp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lwapp-l3");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lwapp-cntl");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lwm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lwm2mtlv");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lwres");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "m2ap");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "m2tp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "m2ua");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "m3ap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "maap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mac-lte");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mac-lte-framed");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mac-nr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "macsec");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mactelnet");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "marker");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mausb");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mbim");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mc-nmf");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mcp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mdp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mdshdr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "media");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "memcache");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mesh");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "message_analyzer_wfp_capture_v4");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "message_analyzer_wfp_capture2_v4");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "message_analyzer_wfp_capture_v6");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "message_analyzer_wfp_capture2_v6");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "message_analyzer_wfp_capture_auth_v4");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "message_analyzer_wfp_capture_auth_v6");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "etw_wfp_capture");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "etw_ndis");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "message-http");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "meta");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "metamako");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mgmt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mifare");


    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "cfp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mime_dlt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mint");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mint_data");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "miop");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mipv6");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_pad1");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_padn");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_bra");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_acoa");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_ni");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_bad_auth");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_mnp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_mhlla");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_mnid");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_auth");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_mseg_id");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_cgapr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_cgar");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_sign");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_phkt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_coti");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_cot");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_dnsu");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_em");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_vsm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_ssm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_badff");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_hnp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_hi");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_att");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_mnlli");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_lla");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_ts");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_rc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_ipv4ha");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_ipv4aa");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_natd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_ipv4coa");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_grek");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_mhipv6ap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_bi");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_ipv4hareq");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_ipv4harep");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_ipv4dra");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_ipv4dsm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_cr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_lmaa");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_recap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_redir");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_load_inf");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_alt_ip4");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_mng");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_mag_ipv6");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_acc_net_id");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mip6_options_dmnp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mka");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mle");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mbtcp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mbudp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mbrtu");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "modbus");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mojito");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "moldudp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "moldudp64");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sgimount");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mp");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mp4");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mp4v-es");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "iwarp_mpa");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mpeg1");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mpeg-audio");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mpeg_ca");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mpeg_descr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mpeg_pat");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mpeg-pes");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mpeg_pmt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mpeg_sect");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pwach");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pwmcw");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mcc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mpls-echo");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mpls_mac");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mplspmdlm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mplspmilm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mplspmdm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mplspmdlmdm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mplspmilmdm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mpls_psc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mpls_y1711");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mplscp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mplstp_fm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mplstp_lock");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mq");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mqpcf");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mqttsn");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mrcpv2");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mrdisc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mrp-mmrp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mrp-msrp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mrp-mvrp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "msgpack");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "msmms");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "msnip");


    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "msproxy");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "msrp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mswsp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mtp3mg");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mudurl");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mime_multipart");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mux27010");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nw_mtp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nas-5gs");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nas-eps");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nasdaq_itch");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nasdaq_soup");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nat-pmp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "portcontrol");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nb_rtpmux");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nbd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nbifom");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ncp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ncs");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ncsi");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ndps");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "negoex");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "netanalyzer");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "netdump");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "genl");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "net_dm");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "netmon_header");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "netmon_event");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "netmon_system_trace");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "netmon_system_config");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "netmon_process");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "netmon_802_11");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "netrix");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "netrom");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "netsync");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nettl");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "newmail");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nfapi");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nflog");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nfs_unknown");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nfs_svr4");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nfs_knfsd_le");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nfs_nfsd_le");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nfs_knfsd_new");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nfs_ontap_v3");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nfs_ontap_v4");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nfs_ontap_gx_v3");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nfs_celerra_vnx");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nfs_gluster");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nfs_dcache");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nfs_primary_data");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nfs_cb");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nfsacl");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nfsauth");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nge");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nisplus");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nispluscb");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nist_csor");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "njack");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nlm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nlsp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nmas");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nmpi");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ms-nns");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "noe");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "h221nonstd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nordic_ble");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "norm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "novell_pkis");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "npmp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nr-rrc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nrppa");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ns");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ns_cert_exts");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nstrace_ha");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nstrace_mep");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nstrace_rpc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nsh");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gprs-ns");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nsrp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ntlmssp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nvme");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nvme-rdma");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nvme-tcp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nwp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nxp_802154_sniffer");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "obd-ii");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "obex");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "obex_parameter_raw");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "obex_parameter_bt_bpp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "obex_parameter_bt_bip");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "obex_parameter_bt_map");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "obex_parameter_bt_gpp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "obex_parameter_bt_ctn");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "obex_parameter_bt_pbap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ocfs2");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "oer");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "oipf_ciplus");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pflog-old");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "olsr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "omapi");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "omron");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "opa");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "opa_fe");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "opa_mad");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "opa_snc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "openthread");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "openwire");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "opsi");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "optommp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "osc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "oscore");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "osmo_trxd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "osmo_trxc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "osmux");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ossp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ouch");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "oxid");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "p3");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "p22");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wifi_p2p");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "p7");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "p772");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "p_mul");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "packetbb");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "packetcable_avps");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "packetlogger");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "paltalk");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "papi");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pathport");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pcap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pcap_pktdata");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "file-pcapng");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pcapng");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pcep");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pcli");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pcli8");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pcli12");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pcli20");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pcnfsd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pcomtcp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pcomascii");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pcombinary");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pcp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pdc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pdcp-lte");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pdcp-nr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sdap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "peekremote");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "per");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pflog");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pingpongprotocol");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pkcs-1");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pkcs10");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pkcs12");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pkinit");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pkix1explicit");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pkix1implicit");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pkixac");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pkixproxy");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pkixqualified");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pkixtsp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pkt_ccc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pktap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pktc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pktc_mtafqdn");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pktgen");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pmproxy");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pn532");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pn532_hci");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "png");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pnrp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "portmap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ppcap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ppi");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ppi_antenna");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ppi_gps");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ppi_sensor");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ppi_vector");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pppmux");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pppmuxcp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pppmuxcp_opt_def_pid");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pppoes");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "clpres");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "protobuf");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "proxy");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "prp");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ptpip");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pulse");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mplspwatmn1cw");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mplspwatm11_or_aal5pdu");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mplspwatmaal5sdu");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mplspwatmn1nocw");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mplspwatmcontrolword");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mplspwatmcellheader");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mplspwatmcell");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pwcesopsn");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pwethnocw");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pwethheuristic");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pwfr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pw_hdlc_nocw_fr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pw_hdlc_nocw_hdlc_ppp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pw_oam");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pw_padding");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "pwsatopcw");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "h248q1950");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "q2931");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "q708");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "q932");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "q932_ros");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lwl4");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "qos");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "kif");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "nr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "qsig");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "quakeworld");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "raw");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rbm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rdaclif");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rdm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rdt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "redbackli");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "reload");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "reload-framing");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "remact");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rep_proc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "r-stp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rfc2190");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rfc7468");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rftap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rgmp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "riemann");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rlc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rlc-lte");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rlc-nr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rlm");


    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "serialization");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rmp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rmt-fec");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rmt-lct");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rnsap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rohc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "roofnet");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ros");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "roverride");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rpcap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rpcordma");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rpkirtr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rpriv");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rquota");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rrc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rrlp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rs_acct");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rs_attr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rs_attr_schema");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rs_bind");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rs_misc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rs_pgo");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rs_prop_acct");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rs_prop_acl");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rs_prop_attr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rs_prop_pgo");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rs_prop_plcy");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rs_pwd_mgmt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rs_repadm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rs_replist");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rs_repmgr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rs_unix");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rsec_login");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rsip");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "gsm_abis_rsl");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rsp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rstat");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rsvd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rsvp-e2ei");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rtacser");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rtcdc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rtcfg");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rtitcp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rtls");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rtmac");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rtmpt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rtp_ext_ed137");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rtpevent");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rtpmidi");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rtpproxy");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rtse");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rua");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "rwall");


    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sadmind");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sametime");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sasp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sbc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sbcap");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sccpmg");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "scop");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "scsi_mmc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "scsi_osd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "scsi_sbc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "scsi_smc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "scsi_ssc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "scte35");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "scte35_private_command");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "scte35_si");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "scte35_splice_schedule");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "scte35_time");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "scylla");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sdh");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sdlc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sebek");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "secidmap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "selfm");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sgsap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "shim6");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sigcomp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "raw_sigcomp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "simple");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "simulcrypt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "raw_sip");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sipfrag");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wap-sir");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "slimp3");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sll");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "slsk");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "lanman");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "smb_direct");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "smb_netlogon");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "smb_pipe");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "smcr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sml");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "smp");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "smrse");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "smux");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sna_xid");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "snaeth");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sndcp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sndcpxid");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "snort");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "caneth");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "can");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "canfd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "solaredge");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "someip");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "someipsd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "soupbintcp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "spdy");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "spice");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "spnego");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "spnego-krb5");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "spp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "spray");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sprt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "srp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "srt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sscf-nni");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sscop");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ssp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sss");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sstp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "s4607");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "starteam");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "stat");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "statnotify");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "stcsig");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "stt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sua");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "swipe");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "symantec");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sync");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "synergy");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "synphasor");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sysex");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "sysex_digitech");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "systemd_journal");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "t124");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "t125");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "t30");


    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tapa");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcg_cp_oids");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcp_options_nop");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcp_options_eol");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcp_options_timestamp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcp_options_mss");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcp_options_wscale");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcp_options_sack_perm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcp_options_sack");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcp_options_echo");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcp_options_echoreply");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcp_options_cc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcp_options_ccnew");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcp_options_ccecho");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcp_options_md5");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcp_options_scps");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcp_options_snack");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcp_options_scpsrec");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcp_options_scpscor");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcp_options_qs");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcp_options_user_to");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcp_options_tfo");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcp_options_rvbd_probe");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcp_options_rvbd_trpy");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcp_options_experimental");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcp_options_unknown");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "mptcp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcpencap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tcpros");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tdmoe");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tdmop");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "teap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tecmp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tecmp_payload");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tei_management");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "teklink");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "telkonet");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "data-text-lines");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "thread");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "thread_address");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "thread_bcn");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "thread_coap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "thread_diagnostic");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "thread_meshcop");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "thread_nwd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "thrift");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tibia");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "time");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tivoconnect");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tkn4int");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tn3270");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tn5250");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tnef");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tpcp");


    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tpncp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tr");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "trmac");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tsdns");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tsp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ttag");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "turbocell");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "turbocell_aggregate");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "turnchannel");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "tuxedo");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "owamp_test");


    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ua3g");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "uasip");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ubdp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ubertooth");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ubikdisk");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ubikvote");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ucp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "udplite");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "udpcp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "udpencap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "uds");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "udt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "uhd");







    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "usbprinter");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "usbvideo");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "usbip");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "usbll");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "user_dlt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "userlog");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "v120");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "v150fw");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "v52");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "v5dl");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "v5ef");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "v5ua");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vcdu");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vdp21");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vines_arp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vines_echo");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vines_frp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vines_icp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vines");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vines_ip");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vines_ipc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vines_llc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vines_rtp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vines_spp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vmlab");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vntag");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vp8");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vpp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vpp-metadata");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vpp-opaque");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vpp-opaque2");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vpp-trace");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vrt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vsip");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vsncp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vsncp_opt_pdnid");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vsncp_opt_apname");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vsncp_opt_pdntype");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vsncp_opt_pdnaddress");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vsncp_opt_pco");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vsncp_opt_errorcode");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vsncp_opt_attachtype");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vsncp_opt_ipv4address");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vsncp_opt_addressalloc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vsncp_opt_apn_ambr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vsncp_opt_ipv6_hsgw_lla_iid");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vsnp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vsock");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vuze-dht");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vxi11_async");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vxi11_core");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vxi11_intr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vxlan");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "vxlan_gpe");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wai");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wassp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "waveagent");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wcp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "websocket");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "whdlc");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "who");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wifi_display");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "dpp");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wisun");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wisun_sec");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wisun_eapol_relay");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wisun_netricity_sc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wlancertextn");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wps");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wreth");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wsmp");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wtls");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "wtp");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "x29");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "x2ap");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "xcsl");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "xdmcp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "xip");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "xipserval");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "xmcp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "xra");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_segment");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_plc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_ncp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "docsis_init_ranging");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "xyplex");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "yami");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "yhoo");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ymsg");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ypbind");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "yppasswd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ypserv");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ypxfr");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "z3950");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_apf");


    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbip_beacon");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_ie");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_nwk_gp");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_general_alarms");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_general_analog_input_basic");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_general_analog_output_basic");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_general_analog_value_basic");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_general_applctrl");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_ha_applevtalt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_ha_applident");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_ha_applstats");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_lighting_ballast_ctrl");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_general_basic");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_general_binary_input_basic");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_general_binary_output_basic");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_general_binary_value_basic");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_se_calendar");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_lighting_color_ctrl");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_general_commissioning");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_se_daily_schedule");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_hvac_dehum_ctrl");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_se_dm");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_general_device_temperature_config");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_closures_door_lock");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_se_drlc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_meas_sensing_elecmes");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_se_em");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_se_events");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_hvac_fan_ctrl");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_meas_sensing_flowmeas");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_general_gp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_general_groups");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_ias_ace");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_ias_wd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_ias_zone");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_general_identify");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_meas_sensing_illumlevelsen");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_meas_sensing_illummeas");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_se_ke");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_se_keep_alive");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_general_level_control");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_se_mdu_pairing");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_se_met");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_ha_metidt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_se_msg");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_general_multistate_input_basic");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_general_multistate_output_basic");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_general_multistate_value_basic");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_meas_sensing_occsen");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_general_onoff");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_general_onoff_switch_configuration");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_general_ota");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_general_part");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_general_poll");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_general_power_config");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_se_pp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_meas_sensing_pressmeas");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_se_price");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_hvac_pump_config_ctrl");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_general_pwrprof");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_meas_sensing_relhummeas");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_general_rssi_location");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_general_scenes");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_closures_shade_config");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_se_sub_ghz");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_meas_sensing_tempmeas");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_hvac_thermostat");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_hvac_thermo_ui_config");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_general_time");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_general_touchlink");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zcl_se_tun");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zbee_zdp");

    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zep");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "ziop");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zrtp");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "zvt");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x1800");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x1801");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x1802");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x1803");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x1804");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x1805");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x1806");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x1807");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x1808");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x1809");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x180a");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x180d");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x180e");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x180f");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x1810");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x1811");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x1812");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x1813");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x1814");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x1815");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x1816");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x1818");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x1819");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x181a");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x181b");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x181c");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x181d");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x181e");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x181f");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x1820");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x1821");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x1822");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x1823");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x1824");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x1825");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x1826");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x1827");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x1828");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x1829");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x183a");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x183b");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x183c");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2800");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2801");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2802");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2803");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2900");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2901");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2902");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2903");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2904");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2905");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2906");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2907");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2908");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2909");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x290a");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x290b");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x290c");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x290d");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x290e");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a00");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a01");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a02");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a03");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a04");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a05");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a06");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a07");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a08");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a09");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a0a");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a0b");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a0c");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a0d");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a0e");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a0f");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a10");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a11");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a12");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a13");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a14");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a15");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a16");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a17");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a18");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a19");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a1a");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a1b");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a1c");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a1d");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a1e");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a1f");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a20");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a21");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a22");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a23");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a24");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a25");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a26");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a27");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a28");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a29");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a2a");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a2b");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a2c");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a2f");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a30");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a31");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a32");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a33");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a34");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a35");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a36");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a37");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a38");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a39");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a3a");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a3b");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a3c");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a3d");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a3e");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a3f");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a40");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a41");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a42");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a43");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a44");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a45");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a46");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a47");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a48");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a49");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a4a");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a4b");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a4c");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a4d");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a4e");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a4f");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a50");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a51");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a52");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a53");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a54");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a55");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a56");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a57");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a58");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a59");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a5a");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a5b");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a5c");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a5d");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a5e");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a5f");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a60");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a62");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a63");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a64");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a65");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a66");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a67");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a68");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a69");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a6a");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a6b");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a6c");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a6d");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a6e");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a6f");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a70");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a71");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a72");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a73");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a74");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a75");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a76");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a77");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a78");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a79");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a7a");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a7b");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a7d");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a7e");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a7f");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a80");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a81");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a82");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a83");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a84");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a85");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a86");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a87");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a88");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a89");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a8a");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a8b");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a8c");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a8d");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a8e");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a8f");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a90");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a91");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a92");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a93");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a94");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a95");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a96");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a97");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a98");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a99");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a9a");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a9b");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a9c");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a9d");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a9e");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2a9f");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2aa0");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2aa1");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2aa2");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2aa3");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2aa4");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2aa5");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2aa6");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2aa7");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2aa8");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2aa9");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2aaa");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2aab");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2aac");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2aad");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2aae");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2aaf");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ab0");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ab1");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ab2");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ab3");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ab4");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ab5");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ab6");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ab7");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ab8");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ab9");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2aba");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2abb");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2abc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2abd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2abe");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2abf");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ac0");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ac1");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ac2");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ac3");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ac4");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ac5");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ac6");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ac7");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ac8");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ac9");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2acc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2acd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ace");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2acf");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ad0");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ad1");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ad2");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ad3");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ad4");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ad5");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ad6");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ad7");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ad8");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ad9");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ada");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2adb");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2adc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2add");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ade");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ae0");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ae1");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ae2");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ae3");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ae4");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ae5");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ae6");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ae7");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ae8");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2ae9");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2aea");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2aeb");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2aec");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2aed");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2aee");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2aef");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2af0");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2af1");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2af2");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2af3");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2af4");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2af5");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2af6");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2af7");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2af8");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2af9");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2afa");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2afb");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2afc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2afd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2afe");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2aff");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b00");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b01");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b02");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b03");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b04");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b05");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b06");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b07");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b08");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b09");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b0a");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b0b");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b0c");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b0d");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b0e");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b0f");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b10");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b11");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b12");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b13");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b14");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b15");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b16");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b17");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b18");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b19");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b1a");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b1b");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b1c");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b1d");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b1e");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b1f");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b20");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b21");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b22");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b23");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b24");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b25");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b26");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b27");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b28");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b29");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b2a");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b2b");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b2c");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b2d");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b2e");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b37");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0x2b3a");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0xfff8");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0xfff9");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0xfffa");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0xfffb");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0xfffc");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0xfffd");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "btgatt_uuid0xfffe");
    global_dissect_options.disable_protocol_slist = g_slist_append(global_dissect_options.disable_protocol_slist, "_au_expert");

    if (global_dissect_options.disable_protocol_slist) {
        GSList *proto_disable;

        for (proto_disable = global_dissect_options.disable_protocol_slist;
             proto_disable != NULL; proto_disable = g_slist_next(proto_disable))
            proto_disable_proto_by_name((char *) proto_disable->data);
    }

    if (global_dissect_options.enable_protocol_slist) {
        GSList *proto_enable;

        for (proto_enable = global_dissect_options.enable_protocol_slist;
             proto_enable != NULL; proto_enable = g_slist_next(proto_enable))
            proto_enable_proto_by_name((char *) proto_enable->data);
    }

    if (global_dissect_options.enable_heur_slist) {
        GSList *heur_enable;

        for (heur_enable = global_dissect_options.enable_heur_slist;
             heur_enable != NULL; heur_enable = g_slist_next(heur_enable)) {
            if (!proto_enable_heuristic_by_name((char *) heur_enable->data, TRUE)) {
                cmdarg_err("No such protocol %s, can't enable", (char *) heur_enable->data);
                success = FALSE;
            }
        }
    }

    if (global_dissect_options.disable_heur_slist) {
        GSList *heur_disable;

        for (heur_disable = global_dissect_options.disable_heur_slist;
             heur_disable != NULL; heur_disable = g_slist_next(heur_disable)) {
            if (!proto_enable_heuristic_by_name((char *) heur_disable->data, FALSE)) {
                cmdarg_err("No such protocol %s, can't disable", (char *) heur_disable->data);
                success = FALSE;
            }
        }
    }
    return success;
}

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 4
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * vi: set shiftwidth=4 tabstop=8 expandtab:
 * :indentSize=4:tabSize=8:noTabs=true:
 */
