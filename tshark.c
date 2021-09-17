/* tshark.c
 *
 * Text-mode variant of Wireshark, along the lines of tcpdump and snoop,
 * by Gilbert Ramirez <gram@alumni.rice.edu> and Guy Harris <guy@alum.mit.edu>.
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include <config.h>
#include "epan/write_in_files_handlers.h"
#include <sys/wait.h>
#include "dirent.h"
#include "wsutil/codecs.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <limits.h>

#ifdef HAVE_GETOPT_H
#include <getopt.h>
#endif

#include <errno.h>

#ifdef _WIN32
#include <winsock2.h>
#endif

#ifndef _WIN32
#include <signal.h>
#endif

#ifndef HAVE_GETOPT_LONG
#include "wsutil/wsgetopt.h"
#endif

#include <glib.h>

#include <epan/exceptions.h>
#include <epan/epan.h>

#include <ui/clopts_common.h>
#include <ui/cmdarg_err.h>
#include <ui/urls.h>
#include <wsutil/filesystem.h>
#include <wsutil/file_util.h>
#include <wsutil/socket.h>
#include <wsutil/privileges.h>
#include <wsutil/report_message.h>
#include <wsutil/please_report_bug.h>
#include <cli_main.h>
#include <version_info.h>
#include <wiretap/wtap_opttypes.h>
#include <wiretap/pcapng.h>

#include "globals.h"
#include <epan/timestamp.h>
#include <epan/packet.h>

#ifdef HAVE_LUA

#include <epan/wslua/init_wslua.h>

#endif

#include "frame_tvbuff.h"
#include <epan/prefs.h>
#include <epan/column.h>
#include <epan/decode_as.h>
#include <epan/print.h>
#include <epan/addr_resolv.h>

#ifdef HAVE_LIBPCAP
#include "ui/capture_ui_utils.h"
#endif

#include "ui/taps.h"
#include "ui/util.h"
#include "ui/ws_ui_util.h"
#include "ui/decode_as_utils.h"
#include "ui/filter_files.h"
#include "ui/cli/tshark-tap.h"
#include "ui/cli/tap-exportobject.h"
#include "ui/tap_export_pdu.h"
#include "ui/dissect_opts.h"
#include "ui/failure_message.h"

#if defined(HAVE_LIBSMI)
#include "epan/oids.h"
#endif

#include "epan/maxmind_db.h"
#include <epan/epan_dissect.h>
#include <epan/tap.h>
#include <epan/stat_tap_ui.h>
#include <epan/conversation_table.h>
#include <epan/srt_table.h>
#include <epan/rtd_table.h>
#include <epan/ex-opt.h>
#include <epan/exported_pdu.h>
#include <epan/secrets.h>

#include "capture_opts.h"
#include "caputils/capture-pcap-util.h"

#ifdef HAVE_LIBPCAP
#include "caputils/capture_ifinfo.h"

#ifdef _WIN32
#include "caputils/capture-wpcap.h"
#endif /* _WIN32 */

#include <capchild/capture_session.h>
#include <capchild/capture_sync.h>
#include <ui/capture_info.h>

#endif /* HAVE_LIBPCAP */

#include "log.h"
#include <epan/funnel.h>

#include <wsutil/str_util.h>
#include <wsutil/utf8_entities.h>
#include <wsutil/json_dumper.h>

#ifdef _WIN32
#include <wsutil/win32-utils.h>
#endif

#include "extcap.h"

#include <stdio.h>

#ifdef HAVE_PLUGINS

#include <wsutil/plugins.h>
#include "newproto/jsonopt.h"
#include "newproto/register_protocol.h"

#endif

#include "authorize.h"

/* Exit codes */
#define INVALID_OPTION 1
#define INVALID_INTERFACE 2
#define INVALID_FILE 2
#define INVALID_FILTER 2
#define INVALID_EXPORT 2
#define INVALID_CAPABILITY 2
#define INVALID_TAP 2
#define INVALID_DATA_LINK 2
#define INVALID_TIMESTAMP_TYPE 2
#define INVALID_CAPTURE 2
#define INIT_FAILED 2

#define LONGOPT_EXPORT_OBJECTS LONGOPT_BASE_APPLICATION + 1
#define LONGOPT_COLOR LONGOPT_BASE_APPLICATION + 2
#define LONGOPT_NO_DUPLICATE_KEYS LONGOPT_BASE_APPLICATION + 3
#define LONGOPT_ELASTIC_MAPPING_FILTER LONGOPT_BASE_APPLICATION + 4


capture_file cfile;
char READ_FILE_PATH[256] = {0};
gboolean read_Pcap_From_File_Flag = 0;
char CONFIG_FILES_PATH[128] = {0};
char FILE_NAME_T[128] = {0};
char OFFLINE_LINE_NO_REGEX[256];  /* 离线接入数据的识别线路号的正则表达式 */
char REGISTRATION_FILE_PATH[256] = {0};  /* 注册文件的路径 */


static guint32 cum_bytes;
static frame_data ref_frame;
//static frame_data prev_dis_frame;
static frame_data prev_cap_frame;

static gboolean perform_two_pass_analysis;
static guint32 epan_auto_reset_count = 0;
static gboolean epan_auto_reset = FALSE;

/*
 * The way the packet decode is to be written.
 */
typedef enum {
    WRITE_TEXT,     /* summary or detail text */
    WRITE_XML,      /* PDML or PSML */
    WRITE_FIELDS,   /* User defined list of fields */
    WRITE_JSON,     /* JSON */
    WRITE_JSON_RAW, /* JSON only raw hex */
    WRITE_EK        /* JSON bulk insert to Elasticsearch */
    /* Add CSV and the like here */
} output_action_e;

static output_action_e output_action;
static gboolean do_dissection;     /* TRUE if we have to dissect each packet */
static gboolean print_packet_info; /* TRUE if we're to print packet information */
static gboolean print_summary;     /* TRUE if we're to print packet summary information */
static gboolean print_details;     /* TRUE if we're to print packet details information */
static gboolean print_hex;         /* TRUE if we're to print hex/ascii information */
static gboolean line_buffered;
static gboolean quiet = FALSE;
static gboolean really_quiet = FALSE;
static gchar *delimiter_char = " ";
static gboolean dissect_color = FALSE;

static print_format_e print_format = PR_FMT_TEXT;
static print_stream_t *print_stream = NULL;

static char *output_file_name;

static output_fields_t *output_fields = NULL;
static gchar **protocolfilter = NULL;
static pf_flags protocolfilter_flags = PF_NONE;

static gboolean no_duplicate_keys = FALSE;
static proto_node_children_grouper_func node_children_grouper = proto_node_group_children_by_unique;

static json_dumper jdumper;

/* The line separator used between packets, changeable via the -S option */
static const char *separator = "";

static gboolean prefs_loaded = FALSE;

#ifdef HAVE_LIBPCAP
/*
 * TRUE if we're to print packet counts to keep track of captured packets.
 */
static gboolean print_packet_counts;

static capture_options global_capture_opts;
static capture_session global_capture_session;
static info_data_t global_info_data;

#ifdef SIGINFO
static gboolean infodelay; /* if TRUE, don't print capture info in SIGINFO handler */
static gboolean infoprint; /* if TRUE, print capture info after clearing infodelay */
#endif                     /* SIGINFO */

int do_Files_Handlers(capture_file cfile, char *cf_name);

static gboolean capture(void);

static gboolean capture_input_new_file(capture_session *cap_session,
                                       gchar *new_file);

static void capture_input_new_packets(capture_session *cap_session,
                                      int to_read);

static void capture_input_drops(capture_session *cap_session, guint32 dropped,
                                const char *interface_name);

static void capture_input_error(capture_session *cap_session,
                                char *error_msg, char *secondary_error_msg);

static void capture_input_cfilter_error(capture_session *cap_session,
                                        guint i, const char *error_message);

static void capture_input_closed(capture_session *cap_session, gchar *msg);

static void report_counts(void);

#ifdef _WIN32
static BOOL WINAPI capture_cleanup(DWORD);
#else /* _WIN32 */

static void capture_cleanup(int);

#ifdef SIGINFO
static void report_counts_siginfo(int);
#endif /* SIGINFO */
#endif /* _WIN32 */
#endif /* HAVE_LIBPCAP */

static void reset_epan_mem(capture_file *cf, epan_dissect_t *edt, gboolean tree, gboolean visual);

typedef enum {
    PROCESS_FILE_SUCCEEDED,
    PROCESS_FILE_NO_FILE_PROCESSED,
    PROCESS_FILE_ERROR,
    PROCESS_FILE_INTERRUPTED
} process_file_status_t;

static process_file_status_t process_cap_file(capture_file *, char *, int, gboolean, int, gint64);

static gboolean process_packet_single_pass(capture_file *cf,
                                           epan_dissect_t *edt, gint64 offset, wtap_rec *rec, Buffer *buf,
                                           guint tap_flags);

static void show_print_file_io_error(void);

static gboolean write_preamble(capture_file *cf);

static gboolean write_finale(void);

static void failure_warning_message(const char *msg_format, va_list ap);

static void open_failure_message(const char *filename, int err,
                                 gboolean for_writing);

static void read_failure_message(const char *filename, int err);

static void write_failure_message(const char *filename, int err);

static void failure_message_cont(const char *msg_format, va_list ap);

static GHashTable *output_only_tables = NULL;

struct string_elem {
    const char *sstr; /* The short string */
    const char *lstr; /* The long string */
};

static gint
string_compare(gconstpointer a, gconstpointer b) {
    return strcmp(((const struct string_elem *) a)->sstr,
                  ((const struct string_elem *) b)->sstr);
}

static void
string_elem_print(gpointer data) {
    fprintf(stderr, "    %s - %s\n",
            ((struct string_elem *) data)->sstr,
            ((struct string_elem *) data)->lstr);
}

static void
list_capture_types(void) {
    int i;
    struct string_elem *captypes;
    GSList *list = NULL;

    captypes = g_new(struct string_elem, WTAP_NUM_FILE_TYPES_SUBTYPES);

    fprintf(stderr, "Aurora: The available capture file types for the \"-F\" flag are:\n");
    for (i = 0; i < WTAP_NUM_FILE_TYPES_SUBTYPES; i++) {
        if (wtap_dump_can_open(i)) {
            captypes[i].sstr = wtap_file_type_subtype_short_string(i);
            captypes[i].lstr = wtap_file_type_subtype_string(i);
            list = g_slist_insert_sorted(list, &captypes[i], string_compare);
        }
    }
    g_slist_free_full(list, string_elem_print);
    g_free(captypes);
}

static void
list_read_capture_types(void) {
    int i;
    struct string_elem *captypes;
    GSList *list = NULL;
    const char *magic = "Magic-value-based";
    const char *heuristic = "Heuristics-based";

    /* this is a hack, but WTAP_NUM_FILE_TYPES_SUBTYPES is always >= number of open routines so we're safe */
    captypes = g_new(struct string_elem, WTAP_NUM_FILE_TYPES_SUBTYPES);

    fprintf(stderr, "Aurora: The available read file types for the \"-X read_format:\" option are:\n");
    for (i = 0; open_routines[i].name != NULL; i++) {
        captypes[i].sstr = open_routines[i].name;
        captypes[i].lstr = (open_routines[i].type == OPEN_INFO_MAGIC) ? magic : heuristic;
        list = g_slist_insert_sorted(list, &captypes[i], string_compare);
    }
    g_slist_free_full(list, string_elem_print);
    g_free(captypes);
}

static void
list_export_pdu_taps(void) {
    fprintf(stderr, "Aurora: The available export tap names for the \"-U tap_name\" option are:\n");
    for (GSList *export_pdu_tap_name_list = get_export_pdu_tap_list();
         export_pdu_tap_name_list != NULL;
         export_pdu_tap_name_list = g_slist_next(export_pdu_tap_name_list)) {
        fprintf(stderr, "    %s\n", (const char *) (export_pdu_tap_name_list->data));
    }
}

static void
print_usage(FILE *output) {
    fprintf(output, "\n");
    fprintf(output, "Usage: tshark [options] ...\n");
    fprintf(output, "\n");

#ifdef HAVE_LIBPCAP
    fprintf(output, "Capture interface:\n");
    fprintf(output, "  -i <interface>, --interface <interface>\n");
    fprintf(output, "                           name or idx of interface (def: first non-loopback)\n");
    fprintf(output, "  -f <capture filter>      packet filter in libpcap filter syntax\n");
    fprintf(output, "  -s <snaplen>, --snapshot-length <snaplen>\n");
#ifdef HAVE_PCAP_CREATE
    fprintf(output, "                           packet snapshot length (def: appropriate maximum)\n");
#else
    fprintf(output, "                           packet snapshot length (def: %u)\n", WTAP_MAX_PACKET_SIZE_STANDARD);
#endif
    fprintf(output, "  -p, --no-promiscuous-mode\n");
    fprintf(output, "                           don't capture in promiscuous mode\n");
#ifdef HAVE_PCAP_CREATE
    fprintf(output, "  -I, --monitor-mode       capture in monitor mode, if available\n");
#endif
#ifdef CAN_SET_CAPTURE_BUFFER_SIZE
    fprintf(output, "  -B <buffer size>, --buffer-size <buffer size>\n");
    fprintf(output, "                           size of kernel buffer (def: %dMB)\n", DEFAULT_CAPTURE_BUFFER_SIZE);
#endif
    fprintf(output, "  -y <link type>, --linktype <link type>\n");
    fprintf(output, "                           link layer type (def: first appropriate)\n");
    fprintf(output, "  --time-stamp-type <type> timestamp method for interface\n");
    fprintf(output, "  -D, --list-interfaces    print list of interfaces and exit\n");
    fprintf(output, "  -L, --list-data-link-types\n");
    fprintf(output, "                           print list of link-layer types of iface and exit\n");
    fprintf(output, "  --list-time-stamp-types  print list of timestamp types for iface and exit\n");
    fprintf(output, "\n");
    fprintf(output, "Capture stop conditions:\n");
    fprintf(output, "  -c <packet count>        stop after n packets (def: infinite)\n");
    fprintf(output, "  -a <autostop cond.> ..., --autostop <autostop cond.> ...\n");
    fprintf(output, "                           duration:NUM - stop after NUM seconds\n");
    fprintf(output, "                           filesize:NUM - stop this file after NUM KB\n");
    fprintf(output, "                              files:NUM - stop after NUM files\n");
    fprintf(output, "                            packets:NUM - stop after NUM packets\n");
    /*fprintf(output, "\n");*/
    fprintf(output, "Capture output:\n");
    fprintf(output, "  -b <ringbuffer opt.> ..., --ring-buffer <ringbuffer opt.>\n");
    fprintf(output, "                           duration:NUM - switch to next file after NUM secs\n");
    fprintf(output, "                           filesize:NUM - switch to next file after NUM KB\n");
    fprintf(output, "                              files:NUM - ringbuffer: replace after NUM files\n");
    fprintf(output, "                            packets:NUM - switch to next file after NUM packets\n");
    fprintf(output, "                           interval:NUM - switch to next file when the time is\n");
    fprintf(output, "                                          an exact multiple of NUM secs\n");
#endif /* HAVE_LIBPCAP */
#ifdef HAVE_PCAP_REMOTE
    fprintf(output, "RPCAP options:\n");
    fprintf(output, "  -A <user>:<password>     use RPCAP password authentication\n");
#endif
    /*fprintf(output, "\n");*/
    fprintf(output, "Input file:\n");
    fprintf(output, "  -r <infile>, --read-file <infile>\n");
    fprintf(output, "                           set the filename to read from (or '-' for stdin)\n");

    fprintf(output, "\n");
    fprintf(output, "Processing:\n");
    fprintf(output, "  -2                       perform a two-pass analysis\n");
    fprintf(output, "  -M <packet count>        perform session auto reset\n");
    fprintf(output, "  -R <read filter>, --read-filter <read filter>\n");
    fprintf(output, "                           packet Read filter in Wireshark display filter syntax\n");
    fprintf(output, "                           (requires -2)\n");
    fprintf(output, "  -Y <display filter>, --display-filter <display filter>\n");
    fprintf(output, "                           packet displaY filter in Wireshark display filter\n");
    fprintf(output, "                           syntax\n");
    fprintf(output, "  -n                       disable all name resolutions (def: all enabled)\n");
    fprintf(output, "  -N <name resolve flags>  enable specific name resolution(s): \"mnNtdv\"\n");
    fprintf(output, "  -d %s ...\n", DECODE_AS_ARG_TEMPLATE);
    fprintf(output, "                           \"Decode As\", see the man page for details\n");
    fprintf(output, "                           Example: tcp.port==8888,http\n");
    fprintf(output, "  -H <hosts file>          read a list of entries from a hosts file, which will\n");
    fprintf(output, "                           then be written to a capture file. (Implies -W n)\n");
    fprintf(output, "  --enable-protocol <proto_name>\n");
    fprintf(output, "                           enable dissection of proto_name\n");
    fprintf(output, "  --disable-protocol <proto_name>\n");
    fprintf(output, "                           disable dissection of proto_name\n");
    fprintf(output, "  --enable-heuristic <short_name>\n");
    fprintf(output, "                           enable dissection of heuristic protocol\n");
    fprintf(output, "  --disable-heuristic <short_name>\n");
    fprintf(output, "                           disable dissection of heuristic protocol\n");

    /*fprintf(output, "\n");*/
    fprintf(output, "Output:\n");
    fprintf(output, "  -w <outfile|->           write packets to a pcapng-format file named \"outfile\"\n");
    fprintf(output, "                           (or '-' for stdout)\n");
    fprintf(output, "  --capture-comment <comment>\n");
    fprintf(output, "                           set the capture file comment, if supported\n");
    fprintf(output, "  -C <config profile>      start with specified configuration profile\n");
    fprintf(output, "  -F <output file type>    set the output file type, default is pcapng\n");
    fprintf(output, "                           an empty \"-F\" option will list the file types\n");
    fprintf(output, "  -V                       add output of packet tree        (Packet Details)\n");
    fprintf(output, "  -O <protocols>           Only show packet details of these protocols, comma\n");
    fprintf(output, "                           separated\n");
    fprintf(output, "  -P, --print              print packet summary even when writing to a file\n");
    fprintf(output, "  -S <separator>           the line separator to print between packets\n");
    fprintf(output, "  -x                       add output of hex and ASCII dump (Packet Bytes)\n");
    fprintf(output, "  -T pdml|ps|psml|json|jsonraw|ek|tabs|text|fields|?\n");
    fprintf(output, "                           format of text output (def: text)\n");
    fprintf(output, "  -j <protocolfilter>      protocols layers filter if -T ek|pdml|json selected\n");
    fprintf(output, "                           (e.g. \"ip ip.flags text\", filter does not expand child\n");
    fprintf(output, "                           nodes, unless child is specified also in the filter)\n");
    fprintf(output, "  -J <protocolfilter>      top level protocol filter if -T ek|pdml|json selected\n");
    fprintf(output, "                           (e.g. \"http tcp\", filter which expands all child nodes)\n");
    fprintf(output, "  -e <field>               field to print if -Tfields selected (e.g. tcp.port,\n");
    fprintf(output, "                           _ws.col.Info)\n");
    fprintf(output, "                           this option can be repeated to print multiple fields\n");
    fprintf(output, "  -E<fieldsoption>=<value> set options for output when -Tfields selected:\n");
    fprintf(output, "     bom=y|n               print a UTF-8 BOM\n");
    fprintf(output, "     header=y|n            switch headers on and off\n");
    fprintf(output, "     separator=/t|/s|<char> select tab, space, printable character as separator\n");
    fprintf(output, "     occurrence=f|l|a      print first, last or all occurrences of each field\n");
    fprintf(output, "     aggregator=,|/s|<char> select comma, space, printable character as\n");
    fprintf(output, "                           aggregator\n");
    fprintf(output, "     quote=d|s|n           select double, single, no quotes for values\n");
    fprintf(output, "  -t a|ad|adoy|d|dd|e|r|u|ud|udoy\n");
    fprintf(output, "                           output format of time stamps (def: r: rel. to first)\n");
    fprintf(output, "  -u s|hms                 output format of seconds (def: s: seconds)\n");
    fprintf(output, "  -l                       flush standard output after each packet\n");
    fprintf(output, "  -q                       be more quiet on stdout (e.g. when using statistics)\n");
    fprintf(output, "  -Q                       only log true errors to stderr (quieter than -q)\n");
    fprintf(output, "  -g                       enable group read access on the output file(s)\n");
    fprintf(output, "  -W n                     Save extra information in the file, if supported.\n");
    fprintf(output, "                           n = write network address resolution information\n");
    fprintf(output, "  -X <key>:<value>         eXtension options, see the man page for details\n");
    fprintf(output, "  -U tap_name              PDUs export mode, see the man page for details\n");
    fprintf(output, "  -z <statistics>          various statistics, see the man page for details\n");
    fprintf(output, "  --export-objects <protocol>,<destdir>\n");
    fprintf(output, "                           save exported objects for a protocol to a directory\n");
    fprintf(output, "                           named \"destdir\"\n");
    fprintf(output, "  --color                  color output text similarly to the Wireshark GUI,\n");
    fprintf(output, "                           requires a terminal with 24-bit color support\n");
    fprintf(output, "                           Also supplies color attributes to pdml and psml formats\n");
    fprintf(output, "                           (Note that attributes are nonstandard)\n");
    fprintf(output, "  --no-duplicate-keys      If -T json is specified, merge duplicate keys in an object\n");
    fprintf(output, "                           into a single key with as value a json array containing all\n");
    fprintf(output, "                           values\n");
    fprintf(output, "  --elastic-mapping-filter <protocols> If -G elastic-mapping is specified, put only the\n");
    fprintf(output, "                           specified protocols within the mapping file\n");

    fprintf(output, "\n");
    fprintf(output, "Miscellaneous:\n");
    fprintf(output, "  -h, --help               display this help and exit\n");
    fprintf(output, "  -v, --version            display version info and exit\n");
    fprintf(output, "  -o <name>:<value> ...    override preference setting\n");
    fprintf(output, "  -K <keytab>              keytab file to use for kerberos decryption\n");
    fprintf(output, "  -G [report]              dump one of several available reports and exit\n");
    fprintf(output, "                           default report=\"fields\"\n");
    fprintf(output, "                           use \"-G help\" for more help\n");
#ifdef __linux__
    fprintf(output, "\n");
    fprintf(output, "Dumpcap can benefit from an enabled BPF JIT compiler if available.\n");
    fprintf(output, "You might want to enable it by executing:\n");
    fprintf(output, " \"echo 1 > /proc/sys/net/core/bpf_jit_enable\"\n");
    fprintf(output, "Note that this can make your system less secure!\n");
#endif
}

static void
glossary_option_help(void) {
    FILE *output;

    output = stdout;

    fprintf(output, "%s\n", get_appname_and_version());

    fprintf(output, "\n");
    fprintf(output, "Usage: tshark -G [report]\n");
    fprintf(output, "\n");
    fprintf(output, "Glossary table reports:\n");
    fprintf(output, "  -G column-formats        dump column format codes and exit\n");
    fprintf(output, "  -G decodes               dump \"layer type\"/\"decode as\" associations and exit\n");
    fprintf(output, "  -G dissector-tables      dump dissector table names, types, and properties\n");
    fprintf(output, "  -G elastic-mapping       dump ElasticSearch mapping file\n");
    fprintf(output, "  -G fieldcount            dump count of header fields and exit\n");
    fprintf(output, "  -G fields                dump fields glossary and exit\n");
    fprintf(output, "  -G ftypes                dump field type basic and descriptive names\n");
    fprintf(output, "  -G heuristic-decodes     dump heuristic dissector tables\n");
    fprintf(output, "  -G plugins               dump installed plugins and exit\n");
    fprintf(output, "  -G protocols             dump protocols in registration database and exit\n");
    fprintf(output, "  -G values                dump value, range, true/false strings and exit\n");
    fprintf(output, "\n");
    fprintf(output, "Preference reports:\n");
    fprintf(output, "  -G currentprefs          dump current preferences and exit\n");
    fprintf(output, "  -G defaultprefs          dump default preferences and exit\n");
    fprintf(output, "  -G folders               dump about:folders\n");
    fprintf(output, "\n");
}

static void
tshark_log_handler(const gchar *log_domain, GLogLevelFlags log_level,
                   const gchar *message, gpointer user_data) {
    /* ignore log message, if log_level isn't interesting based
       upon the console log preferences.
       If the preferences haven't been loaded yet, display the
       message anyway.

       The default console_log_level preference value is such that only
         ERROR, CRITICAL and WARNING level messages are processed;
         MESSAGE, INFO and DEBUG level messages are ignored.

       XXX: Aug 07, 2009: Prior tshark g_log code was hardwired to process only
             ERROR and CRITICAL level messages so the current code is a behavioral
             change.  The current behavior is the same as in Wireshark.
    */
    if (prefs_loaded && (log_level & G_LOG_LEVEL_MASK & prefs.console_log_level) == 0) {
        return;
    }

    g_log_default_handler(log_domain, log_level, message, user_data);
}

static void
print_current_user(void) {
    gchar *cur_user, *cur_group;

    if (started_with_special_privs()) {
        cur_user = get_cur_username();
        cur_group = get_cur_groupname();
        fprintf(stderr, "Running as user \"%s\" and group \"%s\".",
                cur_user, cur_group);
        g_free(cur_user);
        g_free(cur_group);
        if (running_with_special_privs()) {
//            fprintf(stderr, " This could be dangerous.");
        }
        fprintf(stderr, "\n");
    }
}

static void
get_tshark_compiled_version_info(GString *str) {
    /* Capture libraries */
    get_compiled_caplibs_version(str);
}

static void
get_tshark_runtime_version_info(GString *str) {
#ifdef HAVE_LIBPCAP
    /* Capture libraries */
    g_string_append(str, ", ");
    get_runtime_caplibs_version(str);
#endif

    /* stuff used by libwireshark */
    epan_get_runtime_version_info(str);
}

static void
about_folders(void) {
    const char *constpath;
    char *path;
    gint i;
    gchar **resultArray;

    /* "file open" */

    /*
     * Fetching the "File" dialogs folder not implemented.
     * This is arguably just a pwd for a ui/cli .
     */

    /* temp */
    printf("%-21s\t%s\n", "Temp:", g_get_tmp_dir());

    /* pers conf */
    path = get_persconffile_path("", FALSE);
    printf("%-21s\t%s\n", "Personal configuration:", path);
    g_free(path);

    /* global conf */
    constpath = get_datafile_dir();
    if (constpath != NULL) {
        printf("%-21s\t%s\n", "Global configuration:", constpath);
    }

    /* system */
    constpath = get_systemfile_dir();
    printf("%-21s\t%s\n", "System:", constpath);

    /* program */
    constpath = get_progfile_dir();
    printf("%-21s\t%s\n", "Program:", constpath);

#ifdef HAVE_PLUGINS
    /* pers plugins */
    printf("%-21s\t%s\n", "Personal Plugins:", get_plugins_pers_dir_with_version());

    /* global plugins */
    printf("%-21s\t%s\n", "Global Plugins:", get_plugins_dir_with_version());
#endif

#ifdef HAVE_LUA
    /* pers lua plugins */
    printf("%-21s\t%s\n", "Personal Lua Plugins:", get_plugins_pers_dir());

    /* global lua plugins */
    printf("%-21s\t%s\n", "Global Lua Plugins:", get_plugins_dir());
#endif

    /* Extcap */
    constpath = get_extcap_dir();

    resultArray = g_strsplit(constpath, G_SEARCHPATH_SEPARATOR_S, 10);
    for (i = 0; resultArray[i]; i++)
        printf("%-21s\t%s\n", "Extcap path:", g_strstrip(resultArray[i]));

    g_strfreev(resultArray);

    /* MaxMindDB */
    path = maxmind_db_get_paths();

    resultArray = g_strsplit(path, G_SEARCHPATH_SEPARATOR_S, 10);

    for (i = 0; resultArray[i]; i++)
        printf("%-21s\t%s\n", "MaxMind database path:", g_strstrip(resultArray[i]));

    g_strfreev(resultArray);
    g_free(path);

#ifdef HAVE_LIBSMI
    /* SMI MIBs/PIBs */
    path = oid_get_default_mib_path();

    resultArray = g_strsplit(path, G_SEARCHPATH_SEPARATOR_S, 20);

    for (i = 0; resultArray[i]; i++)
      printf("%-21s\t%s\n", "MIB/PIB path:", g_strstrip(resultArray[i]));

    g_strfreev(resultArray);
    g_free(path);
#endif
}


static gboolean
must_do_dissection(dfilter_t *rfcode, dfilter_t *dfcode,gchar *volatile pdu_export_arg) {
    /* We have to dissect each packet if:

          we're printing information about each packet;

          we're using a read filter on the packets;

          we're using a display filter on the packets;

          we're exporting PDUs;

          we're using any taps that need dissection. */
    return print_packet_info || rfcode || dfcode || pdu_export_arg ||
           tap_listeners_require_dissection() || dissect_color;
}

struct protoInfo *allProtoInfo;

int main(int argc, char *argv[]) {
    printf("\n");
    printf("    ___\n");
    printf("   /   | __  ___________  _________ _\n");
    printf("  / /| |/ / / / ___/ __ \\/ ___/ __ `/\n");
    printf(" / ___ / /_/ / /  / /_/ / /  / /_/ /\n");
    printf("/_/  |_\\__,_/_/   \\____/_/   \\__,_/\n");
    printf("\n");
    struct allExProtocols protos;

    char *err_msg;
    int opt;
    static const struct option long_options[] = {
            {"help", no_argument, NULL, 'h'},
            {"version", no_argument, NULL, 'v'},
            LONGOPT_CAPTURE_COMMON
            LONGOPT_DISSECT_COMMON {"print", no_argument, NULL, 'P'},
            {"export-objects", required_argument, NULL, LONGOPT_EXPORT_OBJECTS},
            {"color", no_argument, NULL, LONGOPT_COLOR},
            {"no-duplicate-keys", no_argument, NULL, LONGOPT_NO_DUPLICATE_KEYS},
            {"elastic-mapping-filter", required_argument, NULL, LONGOPT_ELASTIC_MAPPING_FILTER},
            {0, 0, 0, 0}};
    gboolean arg_error = FALSE;
    gboolean has_extcap_options = FALSE;

    int err;
    gchar *err_info;
    gboolean exp_pdu_status;
    volatile process_file_status_t status;
    volatile gboolean draw_taps = FALSE;
    volatile int exit_status = EXIT_SUCCESS;
#ifdef HAVE_LIBPCAP
    int caps_queries = 0;
    gboolean start_capture = FALSE;
    GList *if_list;
    gchar *err_str;
    struct bpf_program fcode;
#else
    gboolean capture_option_specified = FALSE;
    volatile int max_packet_count = 0;
#endif
    volatile int out_file_type = WTAP_FILE_TYPE_SUBTYPE_PCAPNG;
    volatile gboolean out_file_name_res = FALSE;
    volatile int in_file_type = WTAP_TYPE_AUTO;
    gchar *volatile cf_name = NULL;
    gchar *volatile config_file_path = NULL;
    gchar *rfilter = NULL;
    gchar *dfilter = NULL;
    dfilter_t *rfcode = NULL;
    dfilter_t *dfcode = NULL;
    e_prefs *prefs_p;
    int log_flags;
    gchar *output_only = NULL;
    gchar *volatile pdu_export_arg = NULL;
    char *volatile exp_pdu_filename = NULL;
    exp_pdu_t exp_pdu_tap_data;
    const gchar *elastic_mapping_filter = NULL;
    pfileNameNode headOfDirPath = (pfileNameNode)malloc(sizeof(struct fileNameNode) * 1);
    headOfDirPath->next = NULL;
    memset(headOfDirPath->fileName, '\0', 128);
/*
 * The leading + ensures that getopt_long() does not permute the argv[]
 * entries.
 *
 * We have to make sure that the first getopt_long() preserves the content
 * of argv[] for the subsequent getopt_long() call.
 *
 * We use getopt_long() in both cases to ensure that we're using a routine
 * whose permutation behavior we can control in the same fashion on all
 * platforms, and so that, if we ever need to process a long argument before
 * doing further initialization, we can do so.
 *
 * Glibc and Solaris libc document that a leading + disables permutation
 * of options, regardless of whether POSIXLY_CORRECT is set or not; *BSD
 * and macOS don't document it, but do so anyway.
 *
 * We do *not* use a leading - because the behavior of a leading - is
 * platform-dependent.
 */
#define OPTSTRING "+2" OPTSTRING_CAPTURE_COMMON OPTSTRING_DISSECT_COMMON "M:C:e:E:F:gG:hH:j:J:lo:O:PqQr:R:S:T:U:vVw:W:xX:Y:z:"

    static const char optstring[] = OPTSTRING;

    /*
     * Set the C-language locale to the native environment and set the
     * code page to UTF-8 on Windows.
     */
#ifdef _WIN32
    setlocale(LC_ALL, ".UTF-8");
#else
    setlocale(LC_ALL, "");
#endif

    // tshark_debug("Aurora started with %d args", argc);

    cmdarg_err_init(failure_warning_message, failure_message_cont);

#ifdef _WIN32
    create_app_running_mutex();
#endif /* _WIN32 */

    /*
     * Get credential information for later use, and drop privileges
     * before doing anything else.
     * Let the user know if anything happened.
     */
    init_process_policies();
    relinquish_special_privs_perm();
    print_current_user();

    /*
     * Attempt to get the pathname of the directory containing the
     * executable file.
     */

    err_msg = init_progfile_dir(argv[0]);
    if (err_msg != NULL) {
        fprintf(stderr,
                "Aurora: Can't get pathname of directory containing the tshark program: %s.\n"
                "It won't be possible to capture traffic.\n"
                "Report this to the Wireshark developers.",
                err_msg);
        g_free(err_msg);
    }

    initialize_funnel_ops();

#ifdef _WIN32
    ws_init_dll_search_path();
#ifdef HAVE_LIBPCAP
    /* Load wpcap if possible. Do this before collecting the run-time version information */
    load_wpcap();
#endif /* HAVE_LIBPCAP */
#endif /* _WIN32 */

    /* Initialize the version information. */
    ws_init_version_info("Aurora", get_tshark_compiled_version_info,
                         epan_get_compiled_version_info,
                         get_tshark_runtime_version_info);

    /* Fail sometimes. Useful for testing fuzz scripts. */
    /* if (g_random_int_range(0, 100) < 5) abort(); */

    /*
     * In order to have the -X opts assigned before the wslua machine starts
     * we need to call getopt_long before epan_init() gets called.
     *
     * In order to handle, for example, -o options, we also need to call it
     * *after* epan_init() gets called, so that the dissectors have had a
     * chance to register their preferences.
     *
     * Spawning a bunch of extcap processes can delay program startup,
     * particularly on Windows. Check to see if we have any options that
     * might require extcap and set has_extcap_options = TRUE if that's
     * the case.
     *
     * XXX - can we do this all with one getopt_long() call, saving the
     * arguments we can't handle until after initializing libwireshark,
     * and then process them after initializing libwireshark?
     */
    opterr = 0;

    while ((opt = getopt_long(argc, argv, optstring, long_options, NULL)) != -1) {
        switch (opt) {
            case 'C': /* Configuration Profile */
                if (profile_exists(optarg, FALSE)) {
                    set_profile_name(optarg);
                } else {
                    cmdarg_err("Configuration Profile \"%s\" does not exist", optarg);
                    exit_status = INVALID_OPTION;
                    goto clean_exit;
                }
                break;
            case 'G':
                if (g_str_has_suffix(optarg, "prefs") || strcmp(optarg, "folders") == 0) {
                    has_extcap_options = TRUE;
                }
                break;
            case 'i':
                has_extcap_options = TRUE;
                break;
            case 'o':
                if (g_str_has_prefix(optarg, "extcap.")) {
                    has_extcap_options = TRUE;
                }
                break;
            case 'P': /* Print packet summary info even when writing to a file */
                print_packet_info = TRUE;
                print_summary = TRUE;
                break;
            case 'r': /* Read capture file x */
                config_file_path = g_strdup(optarg);
                strcpy(CONFIG_FILES_PATH, config_file_path);

                if (readConfigFilesStatus()) {
                    g_print("config_files_load !\n");
                } else {
                    g_print("config files load fail!\n");
                    goto clean_exit;
                }
                if (!initWriteJsonFiles(&write_Json_Files_Init_Status)) {
                    g_print("initWriteJsonFiles somthing error !\n");
                }

                /*添加注册码功能*/
                char hname[128];
                gethostname(hname, sizeof(hname));
                char mac[30];
                getMac(mac);
                char id[50];
                cpu_id(id);
                strcat(id, mac);
                calidenty(id);
                addkey1(id);
                printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
                printf("The machine id: %s\n", id);
                char machine_id_path[100] = {'\0'};
                strcpy(machine_id_path, REGISTRATION_FILE_PATH);
                strcat(machine_id_path, "activecode.txt");
                usersee(machine_id_path, id);
                char active[80];
                char *key = addkey2(id);
                char sto[80];
                char regist_path[100] = {"\0"};
                strcpy(regist_path, REGISTRATION_FILE_PATH);
                strcat(regist_path, "regist.txt");
                FILE *infp = fopen(regist_path, "r");  //需要添加文件路径
                if (infp == NULL) {
                    printf("请输入激活码：\n");
                    scanf("%s", active);
                    while (strcmp(active, key) != 0) {
                        printf("请输入激活码：\n");
                        scanf("%s", active);
                    }
                    strcpy(sto, active);
                    writefile(regist_path, sto);
                } else {
                    char sti[80];
                    fscanf(infp, "%s", sti);
                    fclose(infp);
                    strcpy(active, sti);
                    if (strcmp(key, active) != 0) {
                        printf("激活码错误，请重新输入：\n");

                        while (strcmp(key, active) != 0) {
                            printf("激活码错误，请重新输入：\n");
                            scanf("%s", active);
                        }
                        strcpy(sti, active);
                        writefile(regist_path, sti);
                    } else {
                        printf("该设备已永久激活！\n");
                    }

                }
                printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
                /*注册码功能结束*/

                /**
                 * 针对配置文件对项目进行配置
                 */

                if (JSON_ADD_PROTO) {
                    int jsonNum = CountJsonFile(JSON_ADD_PROTO_PATH);
                    protos.exProtocolNum = jsonNum;
                    protos.exProto = (struct exProtocol *) malloc(sizeof(struct exProtocol) * jsonNum);
                    ParseAllJson(JSON_ADD_PROTO_PATH, &protos);
                    allProtoInfo = (struct protoInfo *) malloc(sizeof(struct protoInfo) * jsonNum);
                }

                print_details = TRUE;
                print_packet_info = TRUE;
                if (ONLINE_CAPTURE_DATA_FLAG && READ_PACKET_FROM_FILES_FLAG) {
                    g_print("config.txt ONLINE_CAPTURE_DATA_FLAG and READ_PACKET_FROM_FILES_FLAG are all true!\n");
                    goto clean_exit;
                } else if (!ONLINE_CAPTURE_DATA_FLAG && !READ_PACKET_FROM_FILES_FLAG) {
                    g_print("config.txt ONLINE_CAPTURE_DATA_FLAG and READ_PACKET_FROM_FILES_FLAG are all false!\n");
                    goto clean_exit;
                } else {
                    if (ONLINE_CAPTURE_DATA_FLAG) {
                        has_extcap_options = TRUE;
                    } else if (READ_PACKET_FROM_FILES_FLAG) {
                        cf_name = READ_PACKET_FROM_FILES_PATH;
                        /*这里设置读取文件的标志，同时设置文件路径变量。*/
                        strcpy(READ_FILE_PATH, cf_name);
                        read_Pcap_From_File_Flag = 1;
                    }
                }
                break;
            case 'O': /* Only output these protocols */
                output_only = g_strdup(optarg);
                /* FALLTHROUGH */
            case 'V': /* Verbose */
                print_details = TRUE;
                print_packet_info = TRUE;
                break;
            case 'x': /* Print packet data in hex (and ASCII) */
                print_hex = TRUE;
                /*  The user asked for hex output, so let's ensure they get it,
                 *  even if they're writing to a file.
                 */
                print_packet_info = TRUE;
                break;
            case 'X':
                ex_opt_add(optarg);
                break;
            case LONGOPT_ELASTIC_MAPPING_FILTER:
                elastic_mapping_filter = optarg;
                break;
            default:
                break;
        }
    }

    /** Send All g_log messages to our own handler **/

    log_flags =
            G_LOG_LEVEL_ERROR |
            G_LOG_LEVEL_CRITICAL |
            G_LOG_LEVEL_WARNING |
            G_LOG_LEVEL_MESSAGE |
            G_LOG_LEVEL_INFO |
            G_LOG_LEVEL_DEBUG |
            G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION;

    g_log_set_handler(NULL,
                      (GLogLevelFlags) log_flags,
                      tshark_log_handler, NULL /* user_data */);
    g_log_set_handler(LOG_DOMAIN_MAIN,
                      (GLogLevelFlags) log_flags,
                      tshark_log_handler, NULL /* user_data */);

#ifdef HAVE_LIBPCAP
    g_log_set_handler(LOG_DOMAIN_CAPTURE,
                      (GLogLevelFlags) log_flags,
                      tshark_log_handler, NULL /* user_data */);
    g_log_set_handler(LOG_DOMAIN_CAPTURE_CHILD,
                      (GLogLevelFlags) log_flags,
                      tshark_log_handler, NULL /* user_data */);
#endif

    init_report_message(failure_warning_message, failure_warning_message,
                        open_failure_message, read_failure_message,
                        write_failure_message);

#ifdef HAVE_LIBPCAP
    capture_opts_init(&global_capture_opts);
    capture_session_init(&global_capture_session, &cfile,
                         capture_input_new_file, capture_input_new_packets,
                         capture_input_drops, capture_input_error,
                         capture_input_cfilter_error, capture_input_closed);
#endif

    timestamp_set_type(TS_RELATIVE);
    timestamp_set_precision(TS_PREC_AUTO);
    timestamp_set_seconds_type(TS_SECONDS_DEFAULT);

    wtap_init(TRUE);

    /* Register all dissectors; we must do this before checking for the
       "-G" flag, as the "-G" flag dumps information registered by the
       dissectors, and we must do it before we read the preferences, in
       case any dissectors register preferences. */
    if (!epan_init(NULL, NULL, TRUE)) {
        exit_status = INIT_FAILED;
        goto clean_exit;
    }

    /* Register all audio codecs. */
    codecs_init();

    /* Register all tap listeners; we do this before we parse the arguments,
       as the "-z" argument can specify a registered tap. */

    /* we register the plugin taps before the other taps because
       stats_tree taps plugins will be registered as tap listeners
       by stats_tree_stat.c and need to registered before that */
#ifdef HAVE_PLUGINS
    register_all_plugin_tap_listeners();
#endif
    if (JSON_ADD_PROTO) {
        exproto_register(&protos);
    }
    /* Register all tap listeners. */

#ifdef JSON_ADD_PROTO
    exproto_register(&proto);
    //free struct exProtocol
    // for (int i = 0; i < proto.partsNum; i++)
    // {
    //   free(proto.dataParts[i].data);
    // }
    // free(proto.dataParts);
#endif

    for (tap_reg_t *t = tap_reg_listener; t->cb_func != NULL; t++) {
        t->cb_func();
    }

    /*
     * An empty cf_name indicates that we're capturing, and we might
     * be doing so on an extcap interface.
     */
    if (has_extcap_options || !cf_name) {
        extcap_register_preferences();
    }

    conversation_table_set_gui_info(init_iousers);
    hostlist_table_set_gui_info(init_hostlists);
    srt_table_iterate_tables(register_srt_tables, NULL);
    rtd_table_iterate_tables(register_rtd_tables, NULL);
    stat_tap_iterate_tables(register_simple_stat_tables, NULL);

    /* If invoked with the "-G" flag, we dump out information based on
       the argument to the "-G" flag; if no argument is specified,
       for backwards compatibility we dump out a glossary of display
       filter symbols.

       XXX - we do this here, for now, to support "-G" with no arguments.
       If none of our build or other processes uses "-G" with no arguments,
       we can just process it with the other arguments. */
    if (argc >= 2 && strcmp(argv[1], "-G") == 0) {
        proto_initialize_all_prefixes();

        if (argc == 2)
            proto_registrar_dump_fields();
        else {
            if (strcmp(argv[2], "column-formats") == 0)
                column_dump_column_formats();
            else if (strcmp(argv[2], "currentprefs") == 0) {
                epan_load_settings();
                write_prefs(NULL);
            } else if (strcmp(argv[2], "decodes") == 0)
                dissector_dump_decodes();
            else if (strcmp(argv[2], "defaultprefs") == 0)
                write_prefs(NULL);
            else if (strcmp(argv[2], "dissector-tables") == 0)
                dissector_dump_dissector_tables();
            else if (strcmp(argv[2], "elastic-mapping") == 0)
                proto_registrar_dump_elastic(elastic_mapping_filter);
            else if (strcmp(argv[2], "fieldcount") == 0) {
                /* return value for the test suite */
                exit_status = proto_registrar_dump_fieldcount();
                goto clean_exit;
            } else if (strcmp(argv[2], "fields") == 0)
                proto_registrar_dump_fields();
            else if (strcmp(argv[2], "folders") == 0) {
                epan_load_settings();
                about_folders();
            } else if (strcmp(argv[2], "ftypes") == 0)
                proto_registrar_dump_ftypes();
            else if (strcmp(argv[2], "heuristic-decodes") == 0)
                dissector_dump_heur_decodes();
            else if (strcmp(argv[2], "plugins") == 0) {
#ifdef HAVE_PLUGINS
                plugins_dump_all();
#endif
#ifdef HAVE_LUA
                wslua_plugins_dump_all();
#endif
                extcap_dump_all();
            } else if (strcmp(argv[2], "protocols") == 0)
                proto_registrar_dump_protocols();
            else if (strcmp(argv[2], "values") == 0)
                proto_registrar_dump_values();
            else if (strcmp(argv[2], "help") == 0)
                glossary_option_help();
                /* These are supported only for backwards compatibility and may or may not work
                 * for a given user in a given directory on a given operating system with a given
                 * command-line interpreter.
                 */
            else if (strcmp(argv[2], "?") == 0)
                glossary_option_help();
            else if (strcmp(argv[2], "-?") == 0)
                glossary_option_help();
            else {
                cmdarg_err("Invalid \"%s\" option for -G flag, enter -G help for more help.", argv[2]);
                exit_status = INVALID_OPTION;
                goto clean_exit;
            }
        }
        exit_status = EXIT_SUCCESS;
        goto clean_exit;
    }

    // tshark_debug("Aurora reading settings");

    /* Load libwireshark settings from the current profile. */
    prefs_p = epan_load_settings();
    prefs_loaded = TRUE;

    read_filter_list(CFILTER_LIST);

    cap_file_init(&cfile);

    /* Print format defaults to this. */
    print_format = PR_FMT_TEXT;
    delimiter_char = " ";

    output_fields = output_fields_new();

    /*
     * To reset the options parser, set optreset to 1 on platforms that
     * have optreset (documented in *BSD and macOS, apparently present but
     * not documented in Solaris - the Illumos repository seems to
     * suggest that the first Solaris getopt_long(), at least as of 2004,
     * was based on the NetBSD one, it had optreset) and set optind to 1,
     * and set optind to 0 otherwise (documented as working in the GNU
     * getopt_long().  Setting optind to 0 didn't originally work in the
     * NetBSD one, but that was added later - we don't want to depend on
     * it if we have optreset).
     *
     * Also reset opterr to 1, so that error messages are printed by
     * getopt_long().
     */
#ifdef HAVE_OPTRESET
    optreset = 1;
    optind = 1;
#else
    optind = 0;
#endif
    opterr = 1;

    /* Now get our args */
    /**
     * 通过配置文件对在线设备名称进行设定
     */
    if (ONLINE_CAPTURE_DATA_FLAG) {
        exit_status = capture_opts_add_opt(&global_capture_opts, 105, ONLINE_CAPTURE_DATA_DEVICE_NAME, &start_capture);
        if (exit_status != 0) {
            goto clean_exit;
        }
    }
    while ((opt = getopt_long(argc, argv, optstring, long_options, NULL)) != -1) {
        switch (opt) {
            case '2': /* Perform two pass analysis */
                if (epan_auto_reset) {
                    cmdarg_err("-2 does not support auto session reset.");
                    arg_error = TRUE;
                }
                perform_two_pass_analysis = TRUE;
                break;
            case 'M':
                if (perform_two_pass_analysis) {
                    cmdarg_err("-M does not support two pass analysis.");
                    arg_error = TRUE;
                }
                epan_auto_reset_count = get_positive_int(optarg, "epan reset count");
                epan_auto_reset = TRUE;
                break;
            case 'a':                     /* autostop criteria */
            case 'b':                     /* Ringbuffer option */
            case 'f':                     /* capture filter */
            case 'g':                     /* enable group read access on file(s) */
            case 'i':                     /* Use interface x */
            case LONGOPT_SET_TSTAMP_TYPE: /* Set capture timestamp type */
            case 'p':                     /* Don't capture in promiscuous mode */
#ifdef HAVE_PCAP_REMOTE
                case 'A': /* Authentication */
#endif
#ifdef HAVE_PCAP_CREATE
            case 'I': /* Capture in monitor mode, if available */
#endif
            case 's':                     /* Set the snapshot (capture) length */
            case 'y':                     /* Set the pcap data link type */
            case LONGOPT_NUM_CAP_COMMENT: /* add a capture comment */
#ifdef CAN_SET_CAPTURE_BUFFER_SIZE
            case 'B': /* Buffer size */
#endif
                /* These are options only for packet capture. */
#ifdef HAVE_LIBPCAP
                exit_status = capture_opts_add_opt(&global_capture_opts, opt, optarg, &start_capture);
                if (exit_status != 0) {
                    goto clean_exit;
                }
#else
            capture_option_specified = TRUE;
            arg_error = TRUE;
#endif
                break;
            case 'c': /* Stop after x packets */
#ifdef HAVE_LIBPCAP
                exit_status = capture_opts_add_opt(&global_capture_opts, opt, optarg, &start_capture);
                if (exit_status != 0) {
                    goto clean_exit;
                }
#else
                max_packet_count = get_positive_int(optarg, "packet count");
#endif
                break;
            case 'w': /* Write to file x */
                output_file_name = g_strdup(optarg);
#ifdef HAVE_LIBPCAP
                exit_status = capture_opts_add_opt(&global_capture_opts, opt, optarg, &start_capture);
                if (exit_status != 0) {
                    goto clean_exit;
                }
#endif
                break;
            case 'C':
                /* already processed; just ignore it now */
                break;
            case 'D': /* Print a list of capture devices and exit */
#ifdef HAVE_LIBPCAP
                if_list = capture_interface_list(&err, &err_str, NULL);
                if (if_list == NULL) {
                    if (err == 0)
                        cmdarg_err("There are no interfaces on which a capture can be done");
                    else {
                        cmdarg_err("%s", err_str);
                        g_free(err_str);
                    }
                    exit_status = INVALID_INTERFACE;
                    goto clean_exit;
                }
                capture_opts_print_interfaces(if_list);
                free_interface_list(if_list);
                exit_status = EXIT_SUCCESS;
                goto clean_exit;
#else
            capture_option_specified = TRUE;
            arg_error = TRUE;
#endif
                break;
            case 'e':
                /* Field entry */
                output_fields_add(output_fields, optarg);
                break;
            case 'E':
                /* Field option */
                if (!output_fields_set_option(output_fields, optarg)) {
                    cmdarg_err("\"%s\" is not a valid field output option=value pair.", optarg);
                    output_fields_list_options(stderr);
                    exit_status = INVALID_OPTION;
                    goto clean_exit;
                }
                break;
            case 'F':
                out_file_type = wtap_short_string_to_file_type_subtype(optarg);
                if (out_file_type < 0) {
                    cmdarg_err("\"%s\" isn't a valid capture file type", optarg);
                    list_capture_types();
                    exit_status = INVALID_OPTION;
                    goto clean_exit;
                }
                break;
            case 'j':
                if (protocolfilter) {
                    cmdarg_err("-j or -J was already specified! Overwriting previous protocol filter");
                }
                protocolfilter = wmem_strsplit(wmem_epan_scope(), optarg, " ", -1);
                break;
            case 'J':
                if (protocolfilter) {
                    cmdarg_err("-j or -J was already specified! Overwriting previous protocol filter");
                }
                protocolfilter_flags = PF_INCLUDE_CHILDREN;
                protocolfilter = wmem_strsplit(wmem_epan_scope(), optarg, " ", -1);
                break;
            case 'W': /* Select extra information to save in our capture file */
                /* This is patterned after the -N flag which may not be the best idea. */
                if (strchr(optarg, 'n')) {
                    out_file_name_res = TRUE;
                } else {
                    cmdarg_err("Invalid -W argument \"%s\"; it must be one of:", optarg);
                    cmdarg_err_cont("\t'n' write network address resolution information (pcapng only)");
                    exit_status = INVALID_OPTION;
                    goto clean_exit;
                }
                break;
            case 'H': /* Read address to name mappings from a hosts file */
                if (!add_hosts_file(optarg)) {
                    cmdarg_err("Can't read host entries from \"%s\"", optarg);
                    exit_status = INVALID_OPTION;
                    goto clean_exit;
                }
                out_file_name_res = TRUE;
                break;

            case 'h': /* Print help and exit */
                show_help_header("Dump and analyze network traffic.");
                print_usage(stdout);
                exit_status = EXIT_SUCCESS;
                goto clean_exit;
                break;
            case 'l': /* "Line-buffer" standard output */
                /* The ANSI C standard does not appear to *require* that a line-buffered
                   stream be flushed to the host environment whenever a newline is
                   written, it just says that, on such a stream, characters "are
                   intended to be transmitted to or from the host environment as a
                   block when a new-line character is encountered".

                   The Visual C++ 6.0 C implementation doesn't do what is intended;
                   even if you set a stream to be line-buffered, it still doesn't
                   flush the buffer at the end of every line.

                   The whole reason for the "-l" flag in either tcpdump or TShark
                   is to allow the output of a live capture to be piped to a program
                   or script and to have that script see the information for the
                   packet as soon as it's printed, rather than having to wait until
                   a standard I/O buffer fills up.

                   So, if the "-l" flag is specified, we flush the standard output
                   at the end of a packet.  This will do the right thing if we're
                   printing packet summary lines, and, as we print the entire protocol
                   tree for a single packet without waiting for anything to happen,
                   it should be as good as line-buffered mode if we're printing
                   protocol trees - arguably even better, as it may do fewer
                   writes. */
                line_buffered = TRUE;
                break;
            case 'L': /* Print list of link-layer types and exit */
#ifdef HAVE_LIBPCAP
                caps_queries |= CAPS_QUERY_LINK_TYPES;
#else
            capture_option_specified = TRUE;
            arg_error = TRUE;
#endif
                break;
            case LONGOPT_LIST_TSTAMP_TYPES: /* List possible timestamp types */
#ifdef HAVE_LIBPCAP
                caps_queries |= CAPS_QUERY_TIMESTAMP_TYPES;
#else
            capture_option_specified = TRUE;
            arg_error = TRUE;
#endif
                break;
            case 'o': /* Override preference from command line */
            {
                char *errmsg = NULL;

                switch (prefs_set_pref(optarg, &errmsg)) {

                    case PREFS_SET_OK:
                        break;

                    case PREFS_SET_SYNTAX_ERR:
                        cmdarg_err("Invalid -o flag \"%s\"%s%s", optarg,
                                   errmsg ? ": " : "", errmsg ? errmsg : "");
                        g_free(errmsg);
                        exit_status = INVALID_OPTION;
                        goto clean_exit;
                        break;

                    case PREFS_SET_NO_SUCH_PREF:
                    case PREFS_SET_OBSOLETE:
                        cmdarg_err("-o flag \"%s\" specifies unknown preference", optarg);
                        exit_status = INVALID_OPTION;
                        goto clean_exit;
                        break;
                }
                break;
            }
            case 'q': /* Quiet */
                quiet = TRUE;
                break;
            case 'Q': /* Really quiet */
                quiet = TRUE;
                really_quiet = TRUE;
                break;
            case 'r':
                /* already processed; just ignore it now */
                break;
            case 'R': /* Read file filter */
                rfilter = optarg;
                break;
            case 'P':
                /* already processed; just ignore it now */
                break;
            case 'S': /* Set the line Separator to be printed between packets */
                separator = optarg;
                break;
            case 'T': /* printing Type */
                print_packet_info = TRUE;
                if (strcmp(optarg, "text") == 0) {
                    output_action = WRITE_TEXT;
                    print_format = PR_FMT_TEXT;
                } else if (strcmp(optarg, "tabs") == 0) {
                    output_action = WRITE_TEXT;
                    print_format = PR_FMT_TEXT;
                    delimiter_char = "\t";
                } else if (strcmp(optarg, "ps") == 0) {
                    output_action = WRITE_TEXT;
                    print_format = PR_FMT_PS;
                } else if (strcmp(optarg, "pdml") == 0) {
                    output_action = WRITE_XML;
                    print_details = TRUE;  /* Need details */
                    print_summary = FALSE; /* Don't allow summary */
                } else if (strcmp(optarg, "psml") == 0) {
                    output_action = WRITE_XML;
                    print_details = FALSE; /* Don't allow details */
                    print_summary = TRUE;  /* Need summary */
                } else if (strcmp(optarg, "fields") == 0) {
                    output_action = WRITE_FIELDS;
                    print_details = TRUE;  /* Need full tree info */
                    print_summary = FALSE; /* Don't allow summary */
                } else if (strcmp(optarg, "json") == 0) {
                    output_action = WRITE_JSON;
                    print_details = TRUE;  /* Need details */
                    print_summary = FALSE; /* Don't allow summary */
                } else if (strcmp(optarg, "ek") == 0) {
                    output_action = WRITE_EK;
                    if (!print_summary)
                        print_details = TRUE;
                } else if (strcmp(optarg, "jsonraw") == 0) {
                    output_action = WRITE_JSON_RAW;
                    print_details = TRUE;  /* Need details */
                    print_summary = FALSE; /* Don't allow summary */
                } else {
                    cmdarg_err("Invalid -T parameter \"%s\"; it must be one of:", optarg); /* x */
                    cmdarg_err_cont("\t\"fields\"  The values of fields specified with the -e option, in a form\n"
                                    "\t          specified by the -E option.\n"
                                    "\t\"pdml\"    Packet Details Markup Language, an XML-based format for the\n"
                                    "\t          details of a decoded packet. This information is equivalent to\n"
                                    "\t          the packet details printed with the -V flag.\n"
                                    "\t\"ps\"      PostScript for a human-readable one-line summary of each of\n"
                                    "\t          the packets, or a multi-line view of the details of each of\n"
                                    "\t          the packets, depending on whether the -V flag was specified.\n"
                                    "\t\"psml\"    Packet Summary Markup Language, an XML-based format for the\n"
                                    "\t          summary information of a decoded packet. This information is\n"
                                    "\t          equivalent to the information shown in the one-line summary\n"
                                    "\t          printed by default.\n"
                                    "\t\"json\"    Packet Summary, an JSON-based format for the details\n"
                                    "\t          summary information of a decoded packet. This information is \n"
                                    "\t          equivalent to the packet details printed with the -V flag.\n"
                                    "\t\"jsonraw\" Packet Details, a JSON-based format for machine parsing\n"
                                    "\t          including only raw hex decoded fields (same as -T json -x but\n"
                                    "\t          without text decoding, only raw fields included). \n"
                                    "\t\"ek\"      Packet Details, an EK JSON-based format for the bulk insert \n"
                                    "\t          into elastic search cluster. This information is \n"
                                    "\t          equivalent to the packet details printed with the -V flag.\n"
                                    "\t\"text\"    Text of a human-readable one-line summary of each of the\n"
                                    "\t          packets, or a multi-line view of the details of each of the\n"
                                    "\t          packets, depending on whether the -V flag was specified.\n"
                                    "\t          This is the default.\n"
                                    "\t\"tabs\"    Similar to the text report except that each column of the\n"
                                    "\t          human-readable one-line summary is delimited with an ASCII\n"
                                    "\t          horizontal tab character.");
                    exit_status = INVALID_OPTION;
                    goto clean_exit;
                }
                break;
            case 'U': /* Export PDUs to file */
                if (strcmp(optarg, "") == 0 || strcmp(optarg, "?") == 0) {
                    list_export_pdu_taps();
                    exit_status = INVALID_OPTION;
                    goto clean_exit;
                }
                pdu_export_arg = g_strdup(optarg);
                break;
            case 'v': /* Show version and exit */
                show_version();
                /* We don't really have to cleanup here, but it's a convenient way to test
                 * start-up and shut-down of the epan library without any UI-specific
                 * cruft getting in the way. Makes the results of running
                 * $ ./tools/valgrind-wireshark -n
                 * much more useful. */
                epan_cleanup();
                extcap_cleanup();
                exit_status = EXIT_SUCCESS;
                goto clean_exit;
            case 'O': /* Only output these protocols */
                /* already processed; just ignore it now */
                break;
            case 'V': /* Verbose */
                /* already processed; just ignore it now */
                break;
            case 'x': /* Print packet data in hex (and ASCII) */
                /* already processed; just ignore it now */
                break;
            case 'X':
                /* already processed; just ignore it now */
                break;
            case 'Y':
                dfilter = optarg;
                break;
            case 'z':
                /* We won't call the init function for the stat this soon
                   as it would disallow MATE's fields (which are registered
                   by the preferences set callback) from being used as
                   part of a tap filter.  Instead, we just add the argument
                   to a list of stat arguments. */
                if (strcmp("help", optarg) == 0) {
                    fprintf(stderr, "Aurora: The available statistics for the \"-z\" option are:\n");
                    list_stat_cmd_args();
                    exit_status = EXIT_SUCCESS;
                    goto clean_exit;
                }
                if (!process_stat_cmd_arg(optarg)) {
                    cmdarg_err("Invalid -z argument \"%s\"; it must be one of:", optarg);
                    list_stat_cmd_args();
                    exit_status = INVALID_OPTION;
                    goto clean_exit;
                }
                break;
            case 'd':                       /* Decode as rule */
            case 'K':                       /* Kerberos keytab file */
            case 'n':                       /* No name resolution */
            case 'N':                       /* Select what types of addresses/port #s to resolve */
            case 't':                       /* Time stamp type */
            case 'u':                       /* Seconds type */
            case LONGOPT_DISABLE_PROTOCOL:  /* disable dissection of protocol */
            case LONGOPT_ENABLE_HEURISTIC:  /* enable heuristic dissection of protocol */
            case LONGOPT_DISABLE_HEURISTIC: /* disable heuristic dissection of protocol */
            case LONGOPT_ENABLE_PROTOCOL:   /* enable dissection of protocol (that is disabled by default) */
                if (!dissect_opts_handle_opt(opt, optarg)) {
                    exit_status = INVALID_OPTION;
                    goto clean_exit;
                }
                break;
            case LONGOPT_EXPORT_OBJECTS: /* --export-objects */
                if (strcmp("help", optarg) == 0) {
                    fprintf(stderr,
                            "Aurora: The available export object types for the \"--export-objects\" option are:\n");
                    eo_list_object_types();
                    exit_status = EXIT_SUCCESS;
                    goto clean_exit;
                }
                if (!eo_tap_opt_add(optarg)) {
                    exit_status = INVALID_OPTION;
                    goto clean_exit;
                }
                break;
            case LONGOPT_COLOR: /* print in color where appropriate */
                dissect_color = TRUE;
                break;
            case LONGOPT_NO_DUPLICATE_KEYS:
                no_duplicate_keys = TRUE;
                node_children_grouper = proto_node_group_children_by_json_key;
                break;
            default:
            case '?': /* Bad flag - print usage message */
                switch (optopt) {
                    case 'F':
                        list_capture_types();
                        break;
                    default:
                        print_usage(stderr);
                }
                exit_status = INVALID_OPTION;
                goto clean_exit;
                break;
        }
    }

    if (PACKET_PROTOCOL_FLAG) {  // 是否组包
        char t[24] = {0};
        int len = strlen(PACKET_PROTOCOL_TYPES);
        int j = 0;
        for (int i = 0; i < len; ++i) {
            if (PACKET_PROTOCOL_TYPES[i] == ',') {
                continue;
            }
            t[j++] = PACKET_PROTOCOL_TYPES[i];

            if (i + 1 == len || PACKET_PROTOCOL_TYPES[i + 1] == ',') {
                strcat(t, ",");
                strcat(t, PACKET_PROTOCOL_PATH);
                if (!eo_tap_opt_add(t)) {
                    g_print("somthing error in PACKET_PROTOCOL_TYPES and PACKET_PROTOCOL_PATH !\n but go on \n");
                }
                memset(t, '\0', 24);
                j = 0;
            }
        }
    }
    if (WRITE_IN_CONVERSATIONS_FLAG) {  // 是否统计会话信息
        char *arg_t = "conv,tcp";
        if (!process_stat_cmd_arg(arg_t)) {
            list_stat_cmd_args();
            g_print("someting error in conversation of tcp\n");
        }
    }

    /*
     * Print packet summary information is the default if neither -V or -x
     * were specified. Note that this is new behavior, which allows for the
     * possibility of printing only hex/ascii output without necessarily
     * requiring that either the summary or details be printed too.
     */
    if (!print_summary && !print_details && !print_hex)
        print_summary = TRUE;

    if (no_duplicate_keys && output_action != WRITE_JSON && output_action != WRITE_JSON_RAW) {
        cmdarg_err("--no-duplicate-keys can only be used with \"-T json\" and \"-T jsonraw\"");
        exit_status = INVALID_OPTION;
        goto clean_exit;
    }

    /* If we specified output fields, but not the output field type... */
    if ((WRITE_FIELDS != output_action && WRITE_XML != output_action && WRITE_JSON != output_action &&
         WRITE_EK != output_action) && 0 != output_fields_num_fields(output_fields)) {
        cmdarg_err("Output fields were specified with \"-e\", "
                   "but \"-Tek, -Tfields, -Tjson or -Tpdml\" was not specified.");
        exit_status = INVALID_OPTION;
        goto clean_exit;
    } else if (WRITE_FIELDS == output_action && 0 == output_fields_num_fields(output_fields)) {
        cmdarg_err("\"-Tfields\" was specified, but no fields were "
                   "specified with \"-e\".");

        exit_status = INVALID_OPTION;
        goto clean_exit;
    }

    if (dissect_color) {
        if (!color_filters_init(&err_msg, NULL)) {
            fprintf(stderr, "%s\n", err_msg);
            g_free(err_msg);
        }
    }

    /* If no capture filter or display filter has been specified, and there are
       still command-line arguments, treat them as the tokens of a capture
       filter (if no "-r" flag was specified) or a display filter (if a "-r"
       flag was specified. */
    if (optind < argc) {
        if (cf_name != NULL) {
            if (dfilter != NULL) {
                cmdarg_err("Display filters were specified both with \"-Y\" "
                           "and with additional command-line arguments.");
                exit_status = INVALID_OPTION;
                goto clean_exit;
            }
            dfilter = get_args_as_string(argc, argv, optind);
        } else {
#ifdef HAVE_LIBPCAP
            guint i;

            if (global_capture_opts.default_options.cfilter) {
                cmdarg_err("A default capture filter was specified both with \"-f\""
                           " and with additional command-line arguments.");
                exit_status = INVALID_OPTION;
                goto clean_exit;
            }
            for (i = 0; i < global_capture_opts.ifaces->len; i++) {
                interface_options *interface_opts;
                interface_opts = &g_array_index(global_capture_opts.ifaces, interface_options, i);
                if (interface_opts->cfilter == NULL) {
                    interface_opts->cfilter = get_args_as_string(argc, argv, optind);
                } else {
                    cmdarg_err("A capture filter was specified both with \"-f\""
                               " and with additional command-line arguments.");
                    exit_status = INVALID_OPTION;
                    goto clean_exit;
                }
            }
            global_capture_opts.default_options.cfilter = get_args_as_string(argc, argv, optind);
#else
            capture_option_specified = TRUE;
#endif
        }
    }

    if (!output_file_name) {
        /* We're not saving the capture to a file; if "-q" wasn't specified,
           we should print packet information */
        if (!quiet)
            print_packet_info = TRUE;
    } else {
        const char *save_file = output_file_name;
        /* We're saving to a file; if we're writing to the standard output.
           and we'll also be writing dissected packets to the standard
           output, reject the request.  At best, we could redirect that
           to the standard error; we *can't* write both to the standard
           output and have either of them be useful. */
        if (strcmp(save_file, "-") == 0 && print_packet_info) {
            cmdarg_err("You can't write both raw packet data and dissected packets"
                       " to the standard output.");
            exit_status = INVALID_OPTION;
            goto clean_exit;
        }
    }

#ifndef HAVE_LIBPCAP
    if (capture_option_specified)
      cmdarg_err("This version of TShark was not built with support for capturing packets.");
#endif
    if (arg_error) {
        print_usage(stderr);
        exit_status = INVALID_OPTION;
        goto clean_exit;
    }

    if (print_hex) {
        if (output_action != WRITE_TEXT && output_action != WRITE_JSON && output_action != WRITE_JSON_RAW &&
            output_action != WRITE_EK) {
            cmdarg_err("Raw packet hex data can only be printed as text, PostScript, JSON, JSONRAW or EK JSON");
            exit_status = INVALID_OPTION;
            goto clean_exit;
        }
    }

    if (output_only != NULL) {
        char *ps;

        if (!print_details) {
            cmdarg_err("-O requires -V");
            exit_status = INVALID_OPTION;
            goto clean_exit;
        }

        output_only_tables = g_hash_table_new(g_str_hash, g_str_equal);
        for (ps = strtok(output_only, ","); ps; ps = strtok(NULL, ",")) {
            const char *name = ps;
            header_field_info *hfi = proto_registrar_get_byalias(name);
            if (hfi) {
                name = hfi->abbrev;
            }
            g_hash_table_insert(output_only_tables, (gpointer) name, (gpointer) name);
        }
    }

    if (rfilter != NULL && !perform_two_pass_analysis) {
        cmdarg_err("-R without -2 is deprecated. For single-pass filtering use -Y.");
        exit_status = INVALID_OPTION;
        goto clean_exit;
    }

#ifdef HAVE_LIBPCAP
    if (caps_queries) {
        /* We're supposed to list the link-layer/timestamp types for an interface;
           did the user also specify a capture file to be read? */
        if (cf_name) {
            /* Yes - that's bogus. */
            cmdarg_err("You can't specify %s and a capture file to be read.",
                       caps_queries & CAPS_QUERY_LINK_TYPES ? "-L" : "--list-time-stamp-types");
            exit_status = INVALID_OPTION;
            goto clean_exit;
        }
        /* No - did they specify a ring buffer option? */
        if (global_capture_opts.multi_files_on) {
            cmdarg_err("Ring buffer requested, but a capture isn't being done.");
            exit_status = INVALID_OPTION;
            goto clean_exit;
        }
    } else {
        if (cf_name) {
            /*
             * "-r" was specified, so we're reading a capture file.
             * Capture options don't apply here.
             */

            /* We don't support capture filters when reading from a capture file
               (the BPF compiler doesn't support all link-layer types that we
               support in capture files we read). */
            if (global_capture_opts.default_options.cfilter) {
                cmdarg_err("Only read filters, not capture filters, "
                           "can be specified when reading a capture file.");
                exit_status = INVALID_OPTION;
                goto clean_exit;
            }
            if (global_capture_opts.multi_files_on) {
                cmdarg_err("Multiple capture files requested, but "
                           "a capture isn't being done.");
                exit_status = INVALID_OPTION;
                goto clean_exit;
            }
            if (global_capture_opts.has_file_duration) {
                cmdarg_err("Switching capture files after a time period was specified, but "
                           "a capture isn't being done.");
                exit_status = INVALID_OPTION;
                goto clean_exit;
            }
            if (global_capture_opts.has_file_interval) {
                cmdarg_err("Switching capture files after a time interval was specified, but "
                           "a capture isn't being done.");
                exit_status = INVALID_OPTION;
                goto clean_exit;
            }
            if (global_capture_opts.has_ring_num_files) {
                cmdarg_err("A ring buffer of capture files was specified, but "
                           "a capture isn't being done.");
                exit_status = INVALID_OPTION;
                goto clean_exit;
            }
            if (global_capture_opts.has_autostop_files) {
                cmdarg_err("A maximum number of capture files was specified, but "
                           "a capture isn't being done.");
                exit_status = INVALID_OPTION;
                goto clean_exit;
            }
            if (global_capture_opts.capture_comment) {
                cmdarg_err("A capture comment was specified, but "
                           "a capture isn't being done.\nThere's no support for adding "
                           "a capture comment to an existing capture file.");
                exit_status = INVALID_OPTION;
                goto clean_exit;
            }

            /* Note: TShark now allows the restriction of a _read_ file by packet count
             * and byte count as well as a write file. Other autostop options remain valid
             * only for a write file.
             */
            if (global_capture_opts.has_autostop_duration) {
                cmdarg_err("A maximum capture time was specified, but "
                           "a capture isn't being done.");
                exit_status = INVALID_OPTION;
                goto clean_exit;
            }
        } else {
            /*
             * "-r" wasn't specified, so we're doing a live capture.
             */
            if (perform_two_pass_analysis) {
                /* Two-pass analysis doesn't work with live capture since it requires us
                 * to buffer packets until we've read all of them, but a live capture
                 * has no useful/meaningful definition of "all" */
                cmdarg_err("Live captures do not support two-pass analysis.");
                exit_status = INVALID_OPTION;
                goto clean_exit;
            }

            if (global_capture_opts.saving_to_file) {
                /* They specified a "-w" flag, so we'll be saving to a capture file. */

                /* When capturing, we only support writing pcap or pcapng format. */
                if (out_file_type != WTAP_FILE_TYPE_SUBTYPE_PCAP &&
                    out_file_type != WTAP_FILE_TYPE_SUBTYPE_PCAPNG) {
                    cmdarg_err("Live captures can only be saved in pcap or pcapng format.");
                    exit_status = INVALID_OPTION;
                    goto clean_exit;
                }
                if (global_capture_opts.capture_comment &&
                    out_file_type != WTAP_FILE_TYPE_SUBTYPE_PCAPNG) {
                    cmdarg_err("A capture comment can only be written to a pcapng file.");
                    exit_status = INVALID_OPTION;
                    goto clean_exit;
                }
                if (global_capture_opts.multi_files_on) {
                    /* Multiple-file mode doesn't work under certain conditions:
                       a) it doesn't work if you're writing to the standard output;
                       b) it doesn't work if you're writing to a pipe;
                    */
                    if (strcmp(global_capture_opts.save_file, "-") == 0) {
                        cmdarg_err("Multiple capture files requested, but "
                                   "the capture is being written to the standard output.");
                        exit_status = INVALID_OPTION;
                        goto clean_exit;
                    }
                    if (global_capture_opts.output_to_pipe) {
                        cmdarg_err("Multiple capture files requested, but "
                                   "the capture file is a pipe.");
                        exit_status = INVALID_OPTION;
                        goto clean_exit;
                    }
                    if (!global_capture_opts.has_autostop_filesize &&
                        !global_capture_opts.has_file_duration &&
                        !global_capture_opts.has_file_interval) {
                        cmdarg_err("Multiple capture files requested, but "
                                   "no maximum capture file size, duration or interval was specified.");
                        exit_status = INVALID_OPTION;
                        goto clean_exit;
                    }
                }
                /* Currently, we don't support read or display filters when capturing
                   and saving the packets. */
                if (rfilter != NULL) {
                    cmdarg_err("Read filters aren't supported when capturing and saving the captured packets.");
                    exit_status = INVALID_OPTION;
                    goto clean_exit;
                }
                if (dfilter != NULL) {
                    cmdarg_err("Display filters aren't supported when capturing and saving the captured packets.");
                    exit_status = INVALID_OPTION;
                    goto clean_exit;
                }
                global_capture_opts.use_pcapng = (out_file_type == WTAP_FILE_TYPE_SUBTYPE_PCAPNG) ? TRUE : FALSE;
            } else {
                /* They didn't specify a "-w" flag, so we won't be saving to a
                   capture file.  Check for options that only make sense if
                   we're saving to a file. */
                if (global_capture_opts.has_autostop_filesize) {
                    cmdarg_err("Maximum capture file size specified, but "
                               "capture isn't being saved to a file.");
                    exit_status = INVALID_OPTION;
                    goto clean_exit;
                }
                if (global_capture_opts.multi_files_on) {
                    cmdarg_err("Multiple capture files requested, but "
                               "the capture isn't being saved to a file.");
                    exit_status = INVALID_OPTION;
                    goto clean_exit;
                }
                if (global_capture_opts.capture_comment) {
                    cmdarg_err("A capture comment was specified, but "
                               "the capture isn't being saved to a file.");
                    exit_status = INVALID_OPTION;
                    goto clean_exit;
                }
            }
        }
    }
#endif

    err_msg = ws_init_sockets();
    if (err_msg != NULL) {
        cmdarg_err("%s", err_msg);
        g_free(err_msg);
        cmdarg_err_cont("%s", please_report_bug());
        exit_status = INIT_FAILED;
        goto clean_exit;
    }

    /* Notify all registered modules that have had any of their preferences
       changed either from one of the preferences file or from the command
       line that their preferences have changed. */
    prefs_apply_all();

    /* We can also enable specified taps for export object */
    start_exportobjects();

    /* At this point MATE will have registered its field array so we can
       check if the fields specified by the user are all good.
     */
    {
        GSList *it = NULL;
        GSList *invalid_fields = output_fields_valid(output_fields);
        if (invalid_fields != NULL) {

            cmdarg_err("Some fields aren't valid:");
            for (it = invalid_fields; it != NULL; it = g_slist_next(it)) {
                cmdarg_err_cont("\t%s", (gchar *) it->data);
            }
            g_slist_free(invalid_fields);
            exit_status = INVALID_OPTION;
            goto clean_exit;
        }
    }
#ifdef HAVE_LIBPCAP
    /* We currently don't support taps, or printing dissected packets,
       if we're writing to a pipe. */
    if (global_capture_opts.saving_to_file &&
        global_capture_opts.output_to_pipe) {
        if (tap_listeners_require_dissection()) {
            cmdarg_err("Taps aren't supported when saving to a pipe.");
            exit_status = INVALID_OPTION;
            goto clean_exit;
        }
        if (print_packet_info) {
            cmdarg_err("Printing dissected packets isn't supported when saving to a pipe.");
            exit_status = INVALID_OPTION;
            goto clean_exit;
        }
    }
#endif

    if (ex_opt_count("read_format") > 0) {
        const gchar *name = ex_opt_get_next("read_format");
        in_file_type = open_info_name_to_type(name);
        if (in_file_type == WTAP_TYPE_AUTO) {
            cmdarg_err("\"%s\" isn't a valid read file format type", name ? name : "");
            list_read_capture_types();
            exit_status = INVALID_OPTION;
            goto clean_exit;
        }
    }

    timestamp_set_type(global_dissect_options.time_format);

    /*
     * Enabled and disabled protocols and heuristic dissectors as per
     * command-line options.
     */
    if (!setup_enabled_and_disabled_protocols()) {
        exit_status = INVALID_OPTION;
        goto clean_exit;
    }

    /* Build the column format array */
    build_column_format_array(&cfile.cinfo, prefs_p->num_cols, TRUE);

#ifdef HAVE_LIBPCAP
    capture_opts_trim_snaplen(&global_capture_opts, MIN_PACKET_SIZE);
    capture_opts_trim_ring_num_files(&global_capture_opts);
#endif

    if (rfilter != NULL) {
        // tshark_debug("Compiling read filter: '%s'", rfilter);
        if (!dfilter_compile(rfilter, &rfcode, &err_msg)) {
            cmdarg_err("%s", err_msg);
            g_free(err_msg);
            epan_cleanup();
            extcap_cleanup();

#ifdef HAVE_LIBPCAP
            pcap_t *pc;
            pc = pcap_open_dead(DLT_EN10MB, MIN_PACKET_SIZE);
            if (pc != NULL) {
                if (pcap_compile(pc, &fcode, rfilter, 0, 0) != -1) {
                    cmdarg_err_cont(
                            "  Note: That read filter code looks like a valid capture filter;\n"
                            "        maybe you mixed them up?");
                }
                pcap_close(pc);
            }
#endif

            exit_status = INVALID_INTERFACE;
            goto clean_exit;
        }
    }
    cfile.rfcode = rfcode;

    if (dfilter != NULL) {
        // tshark_debug("Compiling display filter: '%s'", dfilter);
        if (!dfilter_compile(dfilter, &dfcode, &err_msg)) {
            cmdarg_err("%s", err_msg);
            g_free(err_msg);
            epan_cleanup();
            extcap_cleanup();

#ifdef HAVE_LIBPCAP
            pcap_t *pc;
            pc = pcap_open_dead(DLT_EN10MB, MIN_PACKET_SIZE);
            if (pc != NULL) {
                if (pcap_compile(pc, &fcode, dfilter, 0, 0) != -1) {
                    cmdarg_err_cont(
                            "  Note: That display filter code looks like a valid capture filter;\n"
                            "        maybe you mixed them up?");
                }
                pcap_close(pc);
            }
#endif

            exit_status = INVALID_FILTER;
            goto clean_exit;
        }
    }
    cfile.dfcode = dfcode;

    if (print_packet_info) {
        /* If we're printing as text or PostScript, we have
           to create a print stream. */
        if (output_action == WRITE_TEXT) {
            switch (print_format) {

                case PR_FMT_TEXT:
                    print_stream = print_stream_text_stdio_new(stdout);
                    break;

                case PR_FMT_PS:
                    print_stream = print_stream_ps_stdio_new(stdout);
                    break;

                default:
                    g_assert_not_reached();
            }
        }
    }

    /* PDU export requested. Take the ownership of the '-w' file, apply tap
    * filters and start tapping. */
    if (pdu_export_arg) {
        const char *exp_pdu_tap_name = pdu_export_arg;
        const char *exp_pdu_filter = dfilter; /* may be NULL to disable filter */
        char *exp_pdu_error;
        int exp_fd;
        char *comment;

        if (!cf_name) {
            cmdarg_err("PDUs export requires a capture file (specify with -r).");
            exit_status = INVALID_OPTION;
            goto clean_exit;
        }
        /* Take ownership of the '-w' output file. */
        exp_pdu_filename = output_file_name;
        output_file_name = NULL;
#ifdef HAVE_LIBPCAP
        global_capture_opts.save_file = NULL;
#endif
        if (exp_pdu_filename == NULL) {
            cmdarg_err("PDUs export requires an output file (-w).");
            exit_status = INVALID_OPTION;
            goto clean_exit;
        }

        exp_pdu_error = exp_pdu_pre_open(exp_pdu_tap_name, exp_pdu_filter,
                                         &exp_pdu_tap_data);
        if (exp_pdu_error) {
            cmdarg_err("Cannot register tap: %s", exp_pdu_error);
            g_free(exp_pdu_error);
            list_export_pdu_taps();
            exit_status = INVALID_TAP;
            goto clean_exit;
        }

        if (strcmp(exp_pdu_filename, "-") == 0) {
            /* Write to the standard output. */
            exp_fd = 1;
        } else {
            exp_fd = ws_open(exp_pdu_filename, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, 0644);
            if (exp_fd == -1) {
                cmdarg_err("%s: %s", exp_pdu_filename, file_open_error_message(errno, TRUE));
                exit_status = INVALID_FILE;
                goto clean_exit;
            }
        }

        /* Activate the export PDU tap */
        comment = g_strdup_printf("Dump of PDUs from %s", cf_name);
        exp_pdu_status = exp_pdu_open(&exp_pdu_tap_data, exp_fd, comment,
                                      &err, &err_info);
        g_free(comment);
        if (!exp_pdu_status) {
            cfile_dump_open_failure_message("Aurora", exp_pdu_filename,
                                            err, err_info,
                                            WTAP_FILE_TYPE_SUBTYPE_PCAPNG);
            exit_status = INVALID_EXPORT;
            goto clean_exit;
        }
    }

    // tshark_debug("Aurora: do_dissection = %s", do_dissection ? "TRUE" : "FALSE");
//  time_t begin_time = time(NULL);
//  g_print(" begin %ld",begin_time);
    if (cf_name) {
        if (EDIT_FILES_DISSECT_FLAG) {
            /*这里开始调用edit拆分大型pcap包*/
            g_print("split packet begin\n");
            pfileNameNode fName_t;
            fName_t = editcapFileIntoSmalls(cf_name, "./out.pcapng", EDIT_FILES_SIZES);
            g_print("split packet end,next do dissecting\n");
            g_assert(fName_t->next != NULL);
            pfileNameNode pnext = fName_t->next;

//        int edit_files_process_num = 0;
            pid_t fpid;
            while (pnext != NULL) {
                fpid = fork();
                if (fpid < 0) {
                    g_print("error fork\n");
                    pnext = pnext->next;
                    continue;
                }
                else if (fpid == 0) {
                    /*子进程*/
                    cf_name = pnext->fileName;
                    g_print("process %d->%s \n", getpid(), cf_name);
                    if (cf_open(&cfile, cf_name, in_file_type, FALSE, &err) != CF_OK) {
                        epan_cleanup();
                        extcap_cleanup();
                        exit_status = INVALID_FILE;
                        goto clean_exit;
                    }
                    start_requested_stats();
                    do_dissection = must_do_dissection(rfcode, dfcode, pdu_export_arg);
                    TRY {
                                status = process_cap_file(&cfile, output_file_name, out_file_type, out_file_name_res,
#ifdef HAVE_LIBPCAP
                                                          global_capture_opts.has_autostop_packets
                                                          ? global_capture_opts.autostop_packets : 0,
                                                          global_capture_opts.has_autostop_filesize
                                                          ? global_capture_opts.autostop_filesize : 0);
#else
                                max_packet_count,
                                    0);
#endif
                                /*直接清理最终缓存*/
                                clean_Temp_Files_All();
                            }
                            CATCH(OutOfMemoryError) {
                                fprintf(stderr,
                                        "Out Of Memory.\n"
                                        "\n"
                                        "Sorry, but TShark has to terminate now.\n"
                                        "\n"
                                        "More information and workarounds can be found at\n" WS_WIKI_URL(
                                                "KnownBugs/OutOfMemory") "\n");
                                status = PROCESS_FILE_ERROR;
                            }
                    ENDTRY;
                    switch (status) {

                        case PROCESS_FILE_SUCCEEDED:
                            /* Everything worked OK; draw the taps. */
                            draw_taps = TRUE;
                            break;

                        case PROCESS_FILE_NO_FILE_PROCESSED:
                            /* We never got to try to read the file, so there are no tap
                               results to dump.  Exit with an error status. */
                            exit_status = 2;
                            break;

                        case PROCESS_FILE_ERROR:
                            /* We still dump out the results of taps, etc., as we might have
                               read some packets; however, we exit with an error status. */
                            draw_taps = TRUE;
                            exit_status = 2;
                            break;

                        case PROCESS_FILE_INTERRUPTED:
                            /* The user interrupted the read process; Don't dump out the
                               result of taps, etc., and exit with an error status. */
                            exit_status = 2;
                            break;
                    }
                    if (pdu_export_arg) {
                        if (!exp_pdu_close(&exp_pdu_tap_data, &err, &err_info)) {
                            cfile_close_failure_message(exp_pdu_filename, err, err_info);
                            exit_status = 2;
                        }
                        g_free(pdu_export_arg);
                        g_free(exp_pdu_filename);
                    }

                    /*memory clean up*/
                    reset_tap_listeners();
                    funnel_dump_all_text_windows();
                    epan_free(cfile.epan);
                    epan_cleanup();
                    extcap_cleanup();

                    output_fields_free(output_fields);
                    output_fields = NULL;

                    cf_close(&cfile);
                    g_free(cf_name);
                    destroy_print_stream(print_stream);
                    g_free(output_file_name);
#ifdef HAVE_LIBPCAP
                    capture_opts_cleanup(&global_capture_opts);
#endif
                    col_cleanup(&cfile.cinfo);
                    free_filter_lists();
                    wtap_cleanup();
                    free_progdirs();
                    dfilter_free(dfcode);
                    return exit_status;

                    break;

                }
                else {
//                /*父进程*/
                    pnext = pnext->next;
                }
            }
            if (fpid != 0) {
                int status_fpid;
                g_print("waiting processing ! \n");
                waitpid(fpid, &status_fpid, 0);
                g_print("done! \n");
                goto clean_exit;
            }
        }
        else {
            struct stat st;
            stat(cf_name, &st);
            if (S_ISDIR(st.st_mode)) {
                /*文件夹*/
                if (access(cf_name, R_OK) == -1) {
                    /*路径无法访问*/
                    g_print("%s path not true !\n", cf_name);
                    exit(0);
                } else {
                    /*路径正常*/
                    readFileList(cf_name, headOfDirPath);
                    pfileNameNode temp = headOfDirPath->next;
                    gboolean mutex = TRUE;
                    while (temp != NULL) {
                        cf_name = temp->fileName;
                        /*将缓存的文件名字初始化*/
                        memset(FILE_NAME_T, '\0', 128);
                        strcpy(FILE_NAME_T, cf_name);
                        match_line_no(OFFLINE_LINE_NO_REGEX, FILE_NAME_T, OFFLINE_LINE_LINE_NO);  /* 匹配线路号 */
                        if (cf_open(&cfile, cf_name, in_file_type, FALSE, &err) != CF_OK) {
                            temp = temp->next;  //跳过该文件，否则会持续打开该文件，一直报错
                            continue;
                        }
                        if (mutex) {
                            start_requested_stats();
                            do_dissection = must_do_dissection(rfcode, dfcode, pdu_export_arg);
                            mutex = FALSE;
                        }

                        status = process_cap_file(&cfile, output_file_name, out_file_type, out_file_name_res,
#ifdef HAVE_LIBPCAP
                                                  global_capture_opts.has_autostop_packets
                                                  ? global_capture_opts.autostop_packets
                                                  : 0,
                                                  global_capture_opts.has_autostop_filesize
                                                  ? global_capture_opts.autostop_filesize
                                                  : 0);
#else
                        max_packet_count,
                            0);
#endif
                        /*直接清理最终缓存*/
                        mutex_final_clean_flag = FALSE;
                        add_record_in_result_file();  /* 每处理完一个文件就往result文件里面添加记录 */
                        if (temp->next == NULL) {  //文件遍历结束
                            clean_Temp_Files_All();
                            draw_taps = TRUE;
                            if (pdu_export_arg) {
                                if (!exp_pdu_close(&exp_pdu_tap_data, &err, &err_info)) {
                                    cfile_close_failure_message(exp_pdu_filename, err, err_info);
                                    exit_status = 2;
                                }
                                g_free(pdu_export_arg);
                                g_free(exp_pdu_filename);
                            }
                            change_result_file_name();
                        }

                        temp = temp->next;
                        cf_close(&cfile);  //关闭打开的pcap文件
                    }
                }
            } else {
                //只有一个文件
                /*文件名*/
                /*将缓存的文件名字初始化*/
                memset(FILE_NAME_T, '\0', 128);
                strcpy(FILE_NAME_T, cf_name);

                if (cf_open(&cfile, cf_name, in_file_type, FALSE, &err) != CF_OK) {
                    epan_cleanup();
                    extcap_cleanup();
                    exit_status = INVALID_FILE;
                    goto clean_exit;
                }
                match_line_no(OFFLINE_LINE_NO_REGEX, cf_name, OFFLINE_LINE_LINE_NO);  /* 匹配线路号 */
                /* Start statistics taps; we do so after successfully opening the
                   capture file, so we know we have something to compute stats
                   on, and after registering all dissectors, so that MATE will
                   have registered its field array so we can have a tap filter
                   with one of MATE's late-registered fields as part of the
                   filter. */
                start_requested_stats();

                /* Do we need to do dissection of packets?  That depends on, among
                   other things, what taps are listening, so determine that after
                   starting the statistics taps. */
                do_dissection = must_do_dissection(rfcode, dfcode, pdu_export_arg);

                /* Process the packets in the file */
                // tshark_debug("Aurora: invoking process_cap_file() to process the packets");
//        TRY
//                {
                status = process_cap_file(&cfile, output_file_name, out_file_type, out_file_name_res,
#ifdef HAVE_LIBPCAP
                                          global_capture_opts.has_autostop_packets
                                          ? global_capture_opts.autostop_packets
                                          : 0,
                                          global_capture_opts.has_autostop_filesize
                                          ? global_capture_opts.autostop_filesize
                                          : 0);
#else
                max_packet_count,
                            0);
#endif
                /*直接清理最终缓存*/
                clean_Temp_Files_All();
                add_record_in_result_file();  /* 每处理完一个文件就往result文件里面添加记录 */
                change_result_file_name();
                cf_close(&cfile);  //关闭打开的pcap文件

                draw_taps = TRUE;

                if (pdu_export_arg) {
                    if (!exp_pdu_close(&exp_pdu_tap_data, &err, &err_info)) {
                        cfile_close_failure_message(exp_pdu_filename, err, err_info);
                        exit_status = 2;
                    }
                    g_free(pdu_export_arg);
                    g_free(exp_pdu_filename);
                }
            }
        }
    }
    else {
        /* No capture file specified, so we're supposed to do a live capture
           or get a list of link-layer types for a live capture device;
           do we have support for live captures? */
#ifdef HAVE_LIBPCAP
#ifdef _WIN32
        /* Warn the user if npf.sys isn't loaded. */
        if (!npf_sys_is_running())
        {
          fprintf(stderr, "The NPF driver isn't running.  You may have trouble "
                          "capturing or\nlisting interfaces.\n");
        }
#endif /* _WIN32 */

        /* if no interface was specified, pick a default */
        exit_status = capture_opts_default_iface_if_necessary(&global_capture_opts,
                                                              ((prefs_p->capture_device) &&
                                                               (*prefs_p->capture_device != '\0')) ? get_if_name(
                                                                      prefs_p->capture_device) : NULL);
        if (exit_status != 0) {
            goto clean_exit;
        }

        /* if requested, list the link layer types and exit */
        if (caps_queries) {
            guint i;

            /* Get the list of link-layer types for the capture devices. */
            for (i = 0; i < global_capture_opts.ifaces->len; i++) {
                interface_options *interface_opts;
                if_capabilities_t *caps;
                char *auth_str = NULL;
                int if_caps_queries = caps_queries;

                interface_opts = &g_array_index(global_capture_opts.ifaces, interface_options, i);
#ifdef HAVE_PCAP_REMOTE
                if (interface_opts->auth_type == CAPTURE_AUTH_PWD)
                {
                  auth_str = g_strdup_printf("%s:%s", interface_opts->auth_username, interface_opts->auth_password);
                }
#endif
                caps = capture_get_if_capabilities(interface_opts->name, interface_opts->monitor_mode, auth_str,
                                                   &err_str, NULL);
                g_free(auth_str);
                if (caps == NULL) {
                    cmdarg_err("%s", err_str);
                    g_free(err_str);
                    exit_status = INVALID_CAPABILITY;
                    goto clean_exit;
                }
                if ((if_caps_queries & CAPS_QUERY_LINK_TYPES) && caps->data_link_types == NULL) {
                    cmdarg_err("The capture device \"%s\" has no data link types.", interface_opts->name);
                    exit_status = INVALID_DATA_LINK;
                    goto clean_exit;
                }
                if ((if_caps_queries & CAPS_QUERY_TIMESTAMP_TYPES) && caps->timestamp_types == NULL) {
                    cmdarg_err("The capture device \"%s\" has no timestamp types.", interface_opts->name);
                    exit_status = INVALID_TIMESTAMP_TYPE;
                    goto clean_exit;
                }
                if (interface_opts->monitor_mode)
                    if_caps_queries |= CAPS_MONITOR_MODE;
                capture_opts_print_if_capabilities(caps, interface_opts->name, if_caps_queries);
                free_if_capabilities(caps);
            }
            exit_status = EXIT_SUCCESS;
            goto clean_exit;
        }

        /*
         * If the standard error isn't a terminal, don't print packet counts,
         * as they won't show up on the user's terminal and they'll get in
         * the way of error messages in the file (to which we assume the
         * standard error was redirected; if it's redirected to the null
         * device, there's no point in printing packet counts anyway).
         *
         * Otherwise, if we're printing packet information and the standard
         * output is a terminal (which we assume means the standard output and
         * error are going to the same terminal), don't print packet counts,
         * as they'll get in the way of the packet information.
         *
         * Otherwise, if the user specified -q, don't print packet counts.
         *
         * Otherwise, print packet counts.
         *
         * XXX - what if the user wants to do a live capture, doesn't want
         * to save it to a file, doesn't want information printed for each
         * packet, does want some "-z" statistic, and wants packet counts
         * so they know whether they're seeing any packets?  -q will
         * suppress the information printed for each packet, but it'll
         * also suppress the packet counts.
         */
        if (!ws_isatty(ws_fileno(stderr)))
            print_packet_counts = FALSE;
        else if (print_packet_info && ws_isatty(ws_fileno(stdout)))
            print_packet_counts = FALSE;
        else if (quiet)
            print_packet_counts = FALSE;
        else
            print_packet_counts = TRUE;

        if (print_packet_info) {
            if (!write_preamble(&cfile)) {
                show_print_file_io_error();
                exit_status = INVALID_FILE;
                goto clean_exit;
            }
        }

        /* Start statistics taps; we should only do so after the capture
           started successfully, so we know we have something to compute
           stats, but we currently don't check for that - see below.

           We do so after registering all dissectors, so that MATE will
           have registered its field array so we can have a tap filter
           with one of MATE's late-registered fields as part of the
           filter. */
        start_requested_stats();

        /* Do we need to do dissection of packets?  That depends on, among
           other things, what taps are listening, so determine that after
           starting the statistics taps. */
        do_dissection = must_do_dissection(rfcode, dfcode, pdu_export_arg);

        /*
         * XXX - this returns FALSE if an error occurred, but it also
         * returns FALSE if the capture stops because a time limit
         * was reached (and possibly other limits), so we can't assume
         * it means an error.
         *
         * The capture code is a bit twisty, so it doesn't appear to
         * be an easy fix.  We just ignore the return value for now.
         * Instead, pass on the exit status from the capture child.
         */
        capture();
        exit_status = global_capture_session.fork_child_status;

        if (print_packet_info) {
            if (!write_finale()) {
                show_print_file_io_error();
            }
        }

        /*
         * If we never got a capture file, don't draw the taps; we not only
         * didn't capture any packets, we never even did any capturing.
         */
        if (cfile.filename != NULL)
            draw_taps = TRUE;
#else
        /* No - complain. */
        cmdarg_err("This version of TShark was not built with support for capturing packets.");
        exit_status = INVALID_CAPTURE;
        goto clean_exit;
#endif
    }

    if (cfile.provider.frames != NULL) {
        free_frame_data_sequence(cfile.provider.frames);
        cfile.provider.frames = NULL;
    }

    if (draw_taps)
        draw_tap_listeners(TRUE);
    /* Memory cleanup */
    reset_tap_listeners();
    funnel_dump_all_text_windows();
    epan_free(cfile.epan);
    epan_cleanup();
    extcap_cleanup();

    output_fields_free(output_fields);
    output_fields = NULL;

    clean_exit:
    clean_Temp_Files_All();
    cf_close(&cfile);
    if ((cf_name != READ_PACKET_FROM_FILES_PATH) && EDIT_FILES_DISSECT_FLAG == 1) {
        g_free(cf_name);
    } else {
        pfileNameNode t = headOfDirPath->next;
        while (t != NULL) {
            pfileNameNode t_t = t->next;
            free(t);
            t = t_t;
        }
        free(headOfDirPath);
    }
    destroy_print_stream(print_stream);
    g_free(output_file_name);
#ifdef HAVE_LIBPCAP
    capture_opts_cleanup(&global_capture_opts);
#endif
    col_cleanup(&cfile.cinfo);
    free_filter_lists();
    wtap_cleanup();
    free_progdirs();
    dfilter_free(dfcode);
    return exit_status;
}

/*#define USE_BROKEN_G_MAIN_LOOP*/

#ifdef USE_BROKEN_G_MAIN_LOOP
GMainLoop *loop;
#else
gboolean loop_running = FALSE;
#endif
guint32 packet_count = 0;

typedef struct pipe_input_tag {
    gint source;
    gpointer user_data;
    ws_process_id *child_process;
    pipe_input_cb_t input_cb;
    guint pipe_input_id;
#ifdef _WIN32
    GMutex *callback_running;
#endif
} pipe_input_t;

static pipe_input_t pipe_input;

#ifdef _WIN32
/* The timer has expired, see if there's stuff to read from the pipe,
   if so, do the callback */
static gint
pipe_timer_cb(gpointer data)
{
  HANDLE handle;
  DWORD avail = 0;
  gboolean result;
  DWORD childstatus;
  pipe_input_t *pipe_input_p = data;
  gint iterations = 0;

  g_mutex_lock(pipe_input_p->callback_running);

  /* try to read data from the pipe only 5 times, to avoid blocking */
  while (iterations < 5)
  {
    /*g_log(NULL, G_LOG_LEVEL_DEBUG, "pipe_timer_cb: new iteration");*/

    /* Oddly enough although Named pipes don't work on win9x,
       PeekNamedPipe does !!! */
    handle = (HANDLE)_get_osfhandle(pipe_input_p->source);
    result = PeekNamedPipe(handle, NULL, 0, NULL, &avail, NULL);

    /* Get the child process exit status */
    GetExitCodeProcess((HANDLE) * (pipe_input_p->child_process),
                       &childstatus);

    /* If the Peek returned an error, or there are bytes to be read
       or the childwatcher thread has terminated then call the normal
       callback */
    if (!result || avail > 0 || childstatus != STILL_ACTIVE)
    {

      /*g_log(NULL, G_LOG_LEVEL_DEBUG, "pipe_timer_cb: data avail");*/

      /* And call the real handler */
      if (!pipe_input_p->input_cb(pipe_input_p->source, pipe_input_p->user_data))
      {
        g_log(NULL, G_LOG_LEVEL_DEBUG, "pipe_timer_cb: input pipe closed, iterations: %u", iterations);
        /* pipe closed, return false so that the timer is stopped */
        g_mutex_unlock(pipe_input_p->callback_running);
        return FALSE;
      }
    }
    else
    {
      /*g_log(NULL, G_LOG_LEVEL_DEBUG, "pipe_timer_cb: no data avail");*/
      /* No data, stop now */
      break;
    }

    iterations++;
  }

  /*g_log(NULL, G_LOG_LEVEL_DEBUG, "pipe_timer_cb: finished with iterations: %u, new timer", iterations);*/

  g_mutex_unlock(pipe_input_p->callback_running);

  /* we didn't stopped the timer, so let it run */
  return TRUE;
}
#endif

void pipe_input_set_handler(gint source, gpointer user_data, ws_process_id *child_process, pipe_input_cb_t input_cb) {

    pipe_input.source = source;
    pipe_input.child_process = child_process;
    pipe_input.user_data = user_data;
    pipe_input.input_cb = input_cb;

#ifdef _WIN32
    pipe_input.callback_running = g_malloc(sizeof(GMutex));
    g_mutex_init(pipe_input.callback_running);
    /* Tricky to use pipes in win9x, as no concept of wait.  NT can
       do this but that doesn't cover all win32 platforms.  GTK can do
       this but doesn't seem to work over processes.  Attempt to do
       something similar here, start a timer and check for data on every
       timeout. */
    /*g_log(NULL, G_LOG_LEVEL_DEBUG, "pipe_input_set_handler: new");*/
    pipe_input.pipe_input_id = g_timeout_add(200, pipe_timer_cb, &pipe_input);
#endif
}

static const nstime_t *
tshark_get_frame_ts(struct packet_provider_data *prov, guint32 frame_num) {
    if (prov->ref && prov->ref->num == frame_num)
        return &prov->ref->abs_ts;

    if (prov->prev_dis && prov->prev_dis->num == frame_num)
        return &prov->prev_dis->abs_ts;

    if (prov->prev_cap && prov->prev_cap->num == frame_num)
        return &prov->prev_cap->abs_ts;

    if (prov->frames) {
        frame_data *fd = frame_data_sequence_find(prov->frames, frame_num);

        return (fd) ? &fd->abs_ts : NULL;
    }

    return NULL;
}

static epan_t *
tshark_epan_new(capture_file *cf) {
    static const struct packet_provider_funcs funcs = {
            tshark_get_frame_ts,
            cap_file_provider_get_interface_name,
            cap_file_provider_get_interface_description,
            NULL,
    };

    return epan_new(&cf->provider, &funcs);
}

#ifdef HAVE_LIBPCAP

static gboolean
capture(void) {
    volatile gboolean ret = TRUE;
    guint i;
    GString *str;
#ifdef USE_TSHARK_SELECT
    fd_set readfds;
#endif
#ifndef _WIN32
    struct sigaction action, oldaction;
#endif

    /* Create new dissection section. */
    epan_free(cfile.epan);
    cfile.epan = tshark_epan_new(&cfile);

#ifdef _WIN32
    /* Catch a CTRL+C event and, if we get it, clean up and exit. */
    SetConsoleCtrlHandler(capture_cleanup, TRUE);
#else /* _WIN32 */
    /* Catch SIGINT and SIGTERM and, if we get either of them,
       clean up and exit.  If SIGHUP isn't being ignored, catch
       it too and, if we get it, clean up and exit.

       We restart any read that was in progress, so that it doesn't
       disrupt reading from the sync pipe.  The signal handler tells
       the capture child to finish; it will report that it finished,
       or will exit abnormally, so  we'll stop reading from the sync
       pipe, pick up the exit status, and quit. */
    memset(&action, 0, sizeof(action));
    action.sa_handler = capture_cleanup;
    action.sa_flags = SA_RESTART;
    sigemptyset(&action.sa_mask);
    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGHUP, NULL, &oldaction);
    if (oldaction.sa_handler == SIG_DFL)
        sigaction(SIGHUP, &action, NULL);

#ifdef SIGINFO
    /* Catch SIGINFO and, if we get it and we're capturing to a file in
       quiet mode, report the number of packets we've captured.

       Again, restart any read that was in progress, so that it doesn't
       disrupt reading from the sync pipe. */
    action.sa_handler = report_counts_siginfo;
    action.sa_flags = SA_RESTART;
    sigemptyset(&action.sa_mask);
    sigaction(SIGINFO, &action, NULL);
#endif /* SIGINFO */
#endif /* _WIN32 */

    global_capture_session.state = CAPTURE_PREPARING;

    /* Let the user know which interfaces were chosen. */
    for (i = 0; i < global_capture_opts.ifaces->len; i++) {
        interface_options *interface_opts;

        interface_opts = &g_array_index(global_capture_opts.ifaces, interface_options, i);
        g_free(interface_opts->descr);
        interface_opts->descr = get_interface_descriptive_name(interface_opts->name);
    }
    str = get_iface_list_string(&global_capture_opts, IFLIST_QUOTE_IF_DESCRIPTION);
    if (really_quiet == FALSE)
        fprintf(stderr, "Capturing on %s\n", str->str);
    fflush(stderr);
    g_string_free(str, TRUE);

    ret = sync_pipe_start(&global_capture_opts, &global_capture_session, &global_info_data, NULL);

    if (!ret)
        return FALSE;

    /*
     * Force synchronous resolution of IP addresses; we're doing only
     * one pass, so we can't do it in the background and fix up past
     * dissections.
     */
    set_resolution_synchrony(TRUE);

    /* the actual capture loop
     *
     * XXX - glib doesn't seem to provide any event based loop handling.
     *
     * XXX - for whatever reason,
     * calling g_main_loop_new() ends up in 100% cpu load.
     *
     * But that doesn't matter: in UNIX we can use select() to find an input
     * source with something to do.
     *
     * But that doesn't matter because we're in a CLI (that doesn't need to
     * update a GUI or something at the same time) so it's OK if we block
     * trying to read from the pipe.
     *
     * So all the stuff in USE_TSHARK_SELECT could be removed unless I'm
     * wrong (but I leave it there in case I am...).
     */

#ifdef USE_TSHARK_SELECT
    FD_ZERO(&readfds);
    FD_SET(pipe_input.source, &readfds);
#endif

    loop_running = TRUE;

    TRY {
                while (loop_running) {
#ifdef USE_TSHARK_SELECT
                    ret = select(pipe_input.source + 1, &readfds, NULL, NULL, NULL);

                    if (ret == -1)
                    {
                      fprintf(stderr, "%s: %s\n", "select()", g_strerror(errno));
                      ret = TRUE;
                      loop_running = FALSE;
                    }
                    else if (ret == 1)
                    {
#endif
                    /* Call the real handler */
                    if (!pipe_input.input_cb(pipe_input.source, pipe_input.user_data)) {
                        g_log(NULL, G_LOG_LEVEL_DEBUG, "input pipe closed");
                        ret = FALSE;
                        loop_running = FALSE;
                    }
#ifdef USE_TSHARK_SELECT
                    }
#endif
                }
            }
            CATCH(OutOfMemoryError) {
                fprintf(stderr,
                        "Out Of Memory.\n"
                        "\n"
                        "Sorry, but TShark has to terminate now.\n"
                        "\n"
                        "More information and workarounds can be found at\n" WS_WIKI_URL("KnownBugs/OutOfMemory") "\n");
                abort();
            }
    ENDTRY;
    return ret;
}

/* capture child detected an error */
static void
capture_input_error(capture_session *cap_session _U_, char *error_msg, char *secondary_error_msg) {
    cmdarg_err("%s", error_msg);
    cmdarg_err_cont("%s", secondary_error_msg);
}

/* capture child detected an capture filter related error */
static void
capture_input_cfilter_error(capture_session *cap_session, guint i, const char *error_message) {
    capture_options *capture_opts = cap_session->capture_opts;
    dfilter_t *rfcode = NULL;
    interface_options *interface_opts;

    g_assert(i < capture_opts->ifaces->len);
    interface_opts = &g_array_index(capture_opts->ifaces, interface_options, i);

    if (dfilter_compile(interface_opts->cfilter, &rfcode, NULL) && rfcode != NULL) {
        cmdarg_err(
                "Invalid capture filter \"%s\" for interface '%s'.\n"
                "\n"
                "That string looks like a valid display filter; however, it isn't a valid\n"
                "capture filter (%s).\n"
                "\n"
                "Note that display filters and capture filters don't have the same syntax,\n"
                "so you can't use most display filter expressions as capture filters.\n"
                "\n"
                "See the User's Guide for a description of the capture filter syntax.",
                interface_opts->cfilter, interface_opts->descr, error_message);
        dfilter_free(rfcode);
    } else {
        cmdarg_err(
                "Invalid capture filter \"%s\" for interface '%s'.\n"
                "\n"
                "That string isn't a valid capture filter (%s).\n"
                "See the User's Guide for a description of the capture filter syntax.",
                interface_opts->cfilter, interface_opts->descr, error_message);
    }
}

/* capture child tells us we have a new (or the first) capture file */
static gboolean
capture_input_new_file(capture_session *cap_session, gchar *new_file) {
    capture_options *capture_opts = cap_session->capture_opts;
    capture_file *cf = cap_session->cf;
    gboolean is_tempfile;
    int err;

    if (cap_session->state == CAPTURE_PREPARING) {
        g_log(LOG_DOMAIN_CAPTURE, G_LOG_LEVEL_MESSAGE, "Capture started.");
    }
    g_log(LOG_DOMAIN_CAPTURE, G_LOG_LEVEL_MESSAGE, "File: \"%s\"", new_file);

    g_assert(cap_session->state == CAPTURE_PREPARING || cap_session->state == CAPTURE_RUNNING);

    /* free the old filename */
    if (capture_opts->save_file != NULL) {

        /* we start a new capture file, close the old one (if we had one before) */
        if (cf->state != FILE_CLOSED) {
            cf_close(cf);
        }

        g_free(capture_opts->save_file);
        is_tempfile = FALSE;

        epan_free(cf->epan);
        cf->epan = tshark_epan_new(cf);
    } else {
        /* we didn't had a save_file before, must be a tempfile */
        is_tempfile = TRUE;
    }

    /* save the new filename */
    capture_opts->save_file = g_strdup(new_file);

    /* if we are in real-time mode, open the new file now */
    if (do_dissection) {
        /* this is probably unecessary, but better safe than sorry */
        cap_session->cf->open_type = WTAP_TYPE_AUTO;
        /* Attempt to open the capture file and set up to read from it. */
        switch (cf_open(cap_session->cf, capture_opts->save_file, WTAP_TYPE_AUTO, is_tempfile, &err)) {
            case CF_OK:
                break;
            case CF_ERROR:
                /* Don't unlink (delete) the save file - leave it around,
                   for debugging purposes. */
                g_free(capture_opts->save_file);
                capture_opts->save_file = NULL;
                return FALSE;
        }
    } else if (quiet && is_tempfile) {
        cf->state = FILE_READ_ABORTED;
        cf->filename = g_strdup(new_file);
        cf->is_tempfile = is_tempfile;
    }

    cap_session->state = CAPTURE_RUNNING;

    return TRUE;
}

/* capture child tells us we have new packets to read */
static void
capture_input_new_packets(capture_session *cap_session, int to_read) {
    gboolean ret;
    int err;
    gchar *err_info;
    gint64 data_offset;
    capture_file *cf = cap_session->cf;
    gboolean filtering_tap_listeners;
    guint tap_flags;

#ifdef SIGINFO
    /*
     * Prevent a SIGINFO handler from writing to the standard error while
     * we're doing so or writing to the standard output; instead, have it
     * just set a flag telling us to print that information when we're done.
     */
    infodelay = TRUE;
#endif /* SIGINFO */

    /* Do we have any tap listeners with filters? */
    filtering_tap_listeners = have_filtering_tap_listeners();

    /* Get the union of the flags for all tap listeners. */
    tap_flags = union_of_tap_listener_flags();

    if (do_dissection) {
        gboolean create_proto_tree;
        epan_dissect_t *edt;
        wtap_rec rec;
        Buffer buf;

        /*
         * Determine whether we need to create a protocol tree.
         * We do if:
         *
         *    we're going to apply a read filter;
         *
         *    we're going to apply a display filter;
         *
         *    we're going to print the protocol tree;
         *
         *    one of the tap listeners is going to apply a filter;
         *
         *    one of the tap listeners requires a protocol tree;
         *
         *    a postdissector wants field values or protocols
         *    on the first pass;
         *
         *    we have custom columns (which require field values, which
         *    currently requires that we build a protocol tree).
         */
        create_proto_tree =
                (cf->rfcode || cf->dfcode || print_details || filtering_tap_listeners ||
                 (tap_flags & TL_REQUIRES_PROTO_TREE) || postdissectors_want_hfids() ||
                 have_custom_cols(&cf->cinfo) || dissect_color);

        /* The protocol tree will be "visible", i.e., printed, only if we're
           printing packet details, which is true if we're printing stuff
           ("print_packet_info" is true) and we're in verbose mode
           ("packet_details" is true). */
        edt = epan_dissect_new(cf->epan, create_proto_tree, print_packet_info && print_details);  /* 创建协议解析数据结构edt */

        wtap_rec_init(&rec);
        ws_buffer_init(&buf, 1514);

        while (to_read-- && cf->provider.wth) {
            wtap_cleareof(cf->provider.wth);
            ret = wtap_read(cf->provider.wth, &rec, &buf, &err, &err_info, &data_offset);
            reset_epan_mem(cf, edt, create_proto_tree, print_packet_info && print_details);
            if (ret == FALSE) {
                /* read from file failed, tell the capture child to stop */
                sync_pipe_stop(cap_session);
                wtap_close(cf->provider.wth);
                cf->provider.wth = NULL;
            } else {
                ret = process_packet_single_pass(cf, edt, data_offset, &rec, &buf,
                                                 tap_flags);
            }
            if (ret != FALSE) {
                /* packet successfully read and gone through the "Read Filter" */
                packet_count++;
            }
        }

        epan_dissect_free(edt);

        wtap_rec_cleanup(&rec);
        ws_buffer_free(&buf);
    } else {
        /*
         * Dumpcap's doing all the work; we're not doing any dissection.
         * Count all the packets it wrote.
         */
        packet_count += to_read;
    }

    if (print_packet_counts) {
        /* We're printing packet counts. */
        if (packet_count != 0) {
            fprintf(stderr, "\r%u ", packet_count);
            /* stderr could be line buffered */
            fflush(stderr);
        }
    }

#ifdef SIGINFO
    /*
     * Allow SIGINFO handlers to write.
     */
    infodelay = FALSE;

    /*
     * If a SIGINFO handler asked us to write out capture counts, do so.
     */
    if (infoprint)
      report_counts();
#endif /* SIGINFO */
}

static void
report_counts(void) {
    if ((print_packet_counts == FALSE) && (really_quiet == FALSE)) {
        /* Report the count only if we aren't printing a packet count
           as packets arrive. */
        fprintf(stderr, "%u packet%s captured\n", packet_count,
                plurality(packet_count, "", "s"));
    }
#ifdef SIGINFO
    infoprint = FALSE; /* we just reported it */
#endif               /* SIGINFO */
}

#ifdef SIGINFO
static void
report_counts_siginfo(int signum _U_)
{
  int sav_errno = errno;
  /* If we've been told to delay printing, just set a flag asking
     that we print counts (if we're supposed to), otherwise print
     the count of packets captured (if we're supposed to). */
  if (infodelay)
    infoprint = TRUE;
  else
    report_counts();
  errno = sav_errno;
}
#endif /* SIGINFO */

/* capture child detected any packet drops? */
static void
capture_input_drops(capture_session *cap_session _U_, guint32 dropped, const char *interface_name) {
    if (print_packet_counts) {
        /* We're printing packet counts to stderr.
           Send a newline so that we move to the line after the packet count. */
        fprintf(stderr, "\n");
    }

    if (dropped != 0) {
        /* We're printing packet counts to stderr.
           Send a newline so that we move to the line after the packet count. */
        if (interface_name != NULL) {
            fprintf(stderr, "%u packet%s dropped from %s\n", dropped, plurality(dropped, "", "s"), interface_name);
        } else {
            fprintf(stderr, "%u packet%s dropped\n", dropped, plurality(dropped, "", "s"));
        }
    }
}

/*
 * Capture child closed its side of the pipe, report any error and
 * do the required cleanup.
 */
static void
capture_input_closed(capture_session *cap_session _U_, gchar *msg) {
    if (msg != NULL)
        fprintf(stderr, "Aurora: %s\n", msg);

    report_counts();

#ifdef USE_BROKEN_G_MAIN_LOOP
    /*g_main_loop_quit(loop);*/
    g_main_loop_quit(loop);
#else
    loop_running = FALSE;
#endif
}

#ifdef _WIN32
static BOOL WINAPI
capture_cleanup(DWORD ctrltype _U_)
{
  /* CTRL_C_EVENT is sort of like SIGINT, CTRL_BREAK_EVENT is unique to
     Windows, CTRL_CLOSE_EVENT is sort of like SIGHUP, CTRL_LOGOFF_EVENT
     is also sort of like SIGHUP, and CTRL_SHUTDOWN_EVENT is sort of
     like SIGTERM at least when the machine's shutting down.

     For now, we handle them all as indications that we should clean up
     and quit, just as we handle SIGINT, SIGHUP, and SIGTERM in that
     way on UNIX.

     We must return TRUE so that no other handler - such as one that would
     terminate the process - gets called.

     XXX - for some reason, typing ^C to TShark, if you run this in
     a Cygwin console window in at least some versions of Cygwin,
     causes TShark to terminate immediately; this routine gets
     called, but the main loop doesn't get a chance to run and
     exit cleanly, at least if this is compiled with Microsoft Visual
     C++ (i.e., it's a property of the Cygwin console window or Bash;
     it happens if TShark is not built with Cygwin - for all I know,
     building it with Cygwin may make the problem go away). */

  /* tell the capture child to stop */
  sync_pipe_stop(&global_capture_session);

  /* don't stop our own loop already here, otherwise status messages and
   * cleanup wouldn't be done properly. The child will indicate the stop of
   * everything by calling capture_input_closed() later */

  return TRUE;
}
#else

static void
capture_cleanup(int signum _U_) {
    /* tell the capture child to stop */
    sync_pipe_stop(&global_capture_session);

    /* don't stop our own loop already here, otherwise status messages and
     * cleanup wouldn't be done properly. The child will indicate the stop of
     * everything by calling capture_input_closed() later */
}

#endif /* _WIN32 */
#endif /* HAVE_LIBPCAP */

typedef enum {
    PASS_SUCCEEDED,
    PASS_READ_ERROR,
    PASS_WRITE_ERROR,
    PASS_INTERRUPTED
} pass_status_t;

static gboolean
process_new_idbs(wtap *wth, wtap_dumper *pdh, int *err, gchar **err_info) {
    wtap_block_t if_data;

    while ((if_data = wtap_get_next_interface_description(wth)) != NULL) {
        /*
         * Only add IDBs if we're writing to a file and the output file
         * requires interface IDs; otherwise, it doesn't support writing IDBs.
         */
        if (pdh != NULL) {
            if (wtap_uses_interface_ids(wtap_dump_file_type_subtype(pdh))) {
                if (!wtap_dump_add_idb(pdh, if_data, err, err_info))
                    return FALSE;
            }
        }
    }
    return TRUE;
}

static pass_status_t process_cap_file_single_pass(capture_file *cf, wtap_dumper *pdh,
                                                  int unuse1, gint64 unuse2,
                                                  int *err, gchar **err_info,
                                                  volatile guint32 *err_framenum) {
    wtap_rec rec;
    Buffer buf;
    gboolean create_proto_tree = FALSE;
    gboolean filtering_tap_listeners;
    guint tap_flags;
    guint32 framenum;
    epan_dissect_t *edt = NULL;
    gint64 data_offset;
    pass_status_t status = PASS_SUCCEEDED;

    wtap_rec_init(&rec);
    ws_buffer_init(&buf, 1514);
    framenum = 0;

    /* Do we have any tap listeners with filters? */
    filtering_tap_listeners = have_filtering_tap_listeners();

    /* Get the union of the flags for all tap listeners. */
    tap_flags = union_of_tap_listener_flags();

    if (do_dissection) {
        /* TRUE if we have to dissect each packet */
        create_proto_tree =
                (cf->rfcode || cf->dfcode || print_details || filtering_tap_listeners ||
                 (tap_flags & TL_REQUIRES_PROTO_TREE) || postdissectors_want_hfids() ||
                 have_custom_cols(&cf->cinfo) || dissect_color);
    }
    /*
     * Force synchronous resolution of IP addresses; we're doing only
     * one pass, so we can't do it in the background and fix up past
     * dissections.
     */
//    set_resolution_synchrony(TRUE);
    set_resolution_synchrony(FALSE);

    *err = 0;
    while (wtap_read(cf->provider.wth, &rec, &buf, err, err_info, &data_offset)) {

        framenum++;
        /*
         * Process whatever IDBs we haven't seen yet.
         */
        if (!process_new_idbs(cf->provider.wth, pdh, err, err_info)) {
            *err_framenum = framenum;
            status = PASS_WRITE_ERROR;
            break;
        }

//        reset_epan_mem(cf, edt, create_proto_tree, print_packet_info && print_details);

        edt = epan_dissect_new(cf->epan, create_proto_tree, print_packet_info && print_details);
        if (process_packet_single_pass(cf, edt, data_offset, &rec, &buf, tap_flags)) {
            /* Either there's no read filtering or this packet passed the
               filter, so, if we're writing to a capture file, write
               this packet out. */
            if (pdh != NULL) {
                // tshark_debug("Aurora: writing packet #%d to outfile", framenum);
                if (!wtap_dump(pdh, &rec, ws_buffer_start_ptr(&buf), err, err_info)) {
                    /* Error writing to the output file. */
                    // tshark_debug("Aurora: error writing to a capture file (%d)", *err);
                    *err_framenum = framenum;
                    status = PASS_WRITE_ERROR;
                    break;
                }
            }
        }
        epan_dissect_free(edt);
    }
    if (*err != 0 && status == PASS_SUCCEEDED) {
        /* Error reading from the input file. */
        status = PASS_READ_ERROR;
    }

//    if (edt)
//        epan_dissect_free(edt);

    ws_buffer_free(&buf);
    wtap_rec_cleanup(&rec);

    return status;
}

static process_file_status_t
process_cap_file(capture_file *cf, char *unuse1, int unuse2,
                 gboolean unuse3, int max_packet_count, gint64 max_byte_count) {

    process_file_status_t status = PROCESS_FILE_SUCCEEDED;
    wtap_dumper *pdh = NULL;

    int err = 0;
    gchar *err_info = NULL;
    volatile guint32 err_framenum;
    wtap_dump_params params = WTAP_DUMP_PARAMS_INIT;
    pass_status_t second_pass_status;

    second_pass_status = process_cap_file_single_pass(cf, pdh,
                                                      max_packet_count,
                                                      max_byte_count,
                                                      &err, &err_info,
                                                      &err_framenum);

    if (second_pass_status != PASS_SUCCEEDED) {
        g_print("process_cap_file_single_pass error!\n,current fileName is :%s\n", cf->filename);
    }

    wtap_close(cf->provider.wth);
    cf->provider.wth = NULL;

    wtap_dump_params_cleanup(&params);

    return status;
}

int ALL_PACKET_COUNT = 0;  // 全局变量统计总共处理了多少个packet，PACKET和FRAME含义相同
/**
 * 处理每一帧数据
 * @param cf
 * @param edt 存放解析结果的结构体
 * @param offset 偏移量
 * @param rec
 * @param buf 缓存
 * @param tap_flags
 * @return
 */
static gboolean
process_packet_single_pass(capture_file *cf, epan_dissect_t *edt, gint64 offset,
                           wtap_rec *rec, Buffer *buf, guint unuse1) {
    frame_data fdata;
    column_info *cinfo = NULL;
    gboolean passed;

    /* Count this packet. 对处理的帧计数 */
    cf->count++;  // 仅仅针对一个文件
    ALL_PACKET_COUNT++;  // 全局变量统计总共处理了多少个packet

    /* If we're not running a display filter and we're not printing any
       packet information, we don't need to do a dissection. This means
       that all packets can be marked as 'passed'. */
    passed = TRUE;

    frame_data_init(&fdata, cf->count, rec, offset, cum_bytes);

    /* If we're going to print packet information, or we're going to
       run a read filter, or we're going to process taps, set up to
       do a dissection and do so.  (This is the one and only pass
       over the packets, so, if we'll be printing packet information
       or running taps, we'll be doing it here.) */
    if (edt) {
        /* If we're running a filter, prime the epan_dissect_t with that
           filter. */
        /* if (cf->dfcode)
           epan_dissect_prime_with_dfilter(edt, cf->dfcode);*/

        /* This is the first and only pass, so prime the epan_dissect_t
           with the hfids postdissectors want on the first pass. */
        prime_epan_dissect_with_postdissector_wanted_hfids(edt);

        frame_data_set_before_dissect(&fdata, &cf->elapsed_time,
                                      &cf->provider.ref, cf->provider.prev_dis);
        if (cf->provider.ref == &fdata) {
            ref_frame = fdata;
            cf->provider.ref = &ref_frame;
        }

        epan_dissect_run_with_taps(edt, cf->cd_t, rec,
                                   frame_tvbuff_new_buffer(&cf->provider, &fdata, buf),
                                   &fdata, cinfo);  /* 获得edt中的tvbuff_t类型的数据指针，具有链表结构的数据包 */


        if (DISPLAY_PACKET_INFO_FLAG) {
            if (INSERT_MANY_PROTOCOL_STREAM_FLAG) {  // 是否批量写入
                if (ALL_PACKET_COUNT % INSERT_MANY_PROTOCOL_STREAM_NUM == 0) {
                    g_print("have processed %d packets!", ALL_PACKET_COUNT);
                    g_print("\r");
                    fflush(stdout);
                }
            } else {
                g_print("have processed %d packets!", ALL_PACKET_COUNT);
                g_print("\r");
                fflush(stdout);
            }
        }
    }
    prev_cap_frame = fdata;
    cf->provider.prev_cap = &prev_cap_frame;

    if (edt) {
        epan_dissect_reset(edt);
        frame_data_destroy(&fdata);
    }
    return passed;
}

static gboolean
write_preamble(capture_file *cf) {
    switch (output_action) {

        case WRITE_TEXT:
            return print_preamble(print_stream, cf->filename, get_ws_vcs_version_info());

        case WRITE_XML:
            if (print_details)
                write_pdml_preamble(stdout, cf->filename);
            else
                write_psml_preamble(&cf->cinfo, stdout);
            return !ferror(stdout);

        case WRITE_FIELDS:
            write_fields_preamble(output_fields, stdout);
            return !ferror(stdout);

        case WRITE_JSON:
        case WRITE_JSON_RAW:
            jdumper = write_json_preamble(stdout);
            return !ferror(stdout);

        case WRITE_EK:
            return TRUE;

        default:
            g_assert_not_reached();
            return FALSE;
    }
}

static gboolean
write_finale(void) {
    switch (output_action) {

        case WRITE_TEXT:
            return print_finale(print_stream);

        case WRITE_XML:
            if (print_details)
                write_pdml_finale(stdout);
            else
                write_psml_finale(stdout);
            return !ferror(stdout);

        case WRITE_FIELDS:
            write_fields_finale(output_fields, stdout);
            return !ferror(stdout);

        case WRITE_JSON:
        case WRITE_JSON_RAW:
            write_json_finale(&jdumper);
            return !ferror(stdout);

        case WRITE_EK:
            return TRUE;

        default:
            g_assert_not_reached();
            return FALSE;
    }
}

/**
 * 关闭打开的pcap文件
 * @param cf
 */
void cf_close(capture_file *cf) {
    if (cf->state == FILE_CLOSED)
        return; /* Nothing to do */

    if (cf->provider.wth != NULL) {
        wtap_close(cf->provider.wth);
        cf->provider.wth = NULL;
    }
    /* We have no file open... */
    if (cf->filename != NULL) {
        /* If it's a temporary file, remove it. */
        if (cf->is_tempfile)
            ws_unlink(cf->filename);
        g_free(cf->filename);
        cf->filename = NULL;
    }

    /* We have no file open. */
    cf->state = FILE_CLOSED;
}

cf_status_t
cf_open(capture_file *cf, const char *fname, unsigned int type, gboolean is_tempfile, int *err) {
    wtap *wth;
    gchar *err_info;

    wth = wtap_open_offline(fname, type, err, &err_info, perform_two_pass_analysis);

    if (wth == NULL)
        goto fail;

    /* The open succeeded.  Fill in the information for this file. */

    cf->provider.wth = wth;
    cf->f_datalen = 0; /* not used, but set it anyway */

    /* Set the file name because we need it to set the follow stream filter.
       XXX - is that still true?  We need it for other reasons, though,
       in any case. */
    cf->filename = g_strdup(fname);

    /* Indicate whether it's a permanent or temporary file. */
    cf->is_tempfile = is_tempfile;

    /* No user changes yet. */
    cf->unsaved_changes = FALSE;

    cf->cd_t = wtap_file_type_subtype(cf->provider.wth);
    cf->open_type = type;
    cf->count = 0;
    cf->drops_known = FALSE;
    cf->drops = 0;
    cf->snap = wtap_snapshot_length(cf->provider.wth);
    nstime_set_zero(&cf->elapsed_time);
    cf->provider.ref = NULL;
    cf->provider.prev_dis = NULL;
    cf->provider.prev_cap = NULL;

    cf->state = FILE_READ_IN_PROGRESS;

    /* Create new epan session for dissection. */

    /*TODO: 这里有问题*/
    epan_free(cf->epan);
    cf->epan = tshark_epan_new(cf);

    wtap_set_cb_new_ipv4(cf->provider.wth, add_ipv4_name);
    wtap_set_cb_new_ipv6(cf->provider.wth, (wtap_new_ipv6_callback_t) add_ipv6_name);
    wtap_set_cb_new_secrets(cf->provider.wth, secrets_wtap_callback);

    return CF_OK;

    fail:
    cfile_open_failure_message("Aurora", fname, *err, err_info);
    return CF_ERROR;
}

static void
show_print_file_io_error(void) {
    switch (errno) {

        case ENOSPC:
            cmdarg_err("Not all the packets could be printed because there is "
                       "no space left on the file system.");
            break;

#ifdef EDQUOT
        case EDQUOT:
            cmdarg_err("Not all the packets could be printed because you are "
                       "too close to, or over your disk quota.");
            break;
#endif

        case EPIPE:
            /*
             * This almost certainly means "the next program after us in
             * the pipeline exited before we were finished writing", so
             * this isn't a real error, it just means we're done.  (We
             * don't get SIGPIPE because libwireshark ignores SIGPIPE
             * to avoid getting killed if writing to the MaxMind process
             * gets SIGPIPE because that process died.)
             *
             * Presumably either that program exited deliberately (for
             * example, "head -N" read N lines and printed them), in
             * which case there's no error to report, or it terminated
             * due to an error or a signal, in which case *that's* the
             * error and that error has been reported.
             */
            break;

        default:
#ifdef _WIN32
            if (errno == EINVAL && _doserrno == ERROR_NO_DATA)
            {
              /*
               * XXX - on Windows, a write to a pipe where the read side
               * has been closed apparently may return the Windows error
               * ERROR_BROKEN_PIPE, which the Visual Studio C library maps
               * to EPIPE, or may return the Windows error ERROR_NO_DATA,
               * which the Visual Studio C library maps to EINVAL.
               *
               * Either of those almost certainly means "the next program
               * after us in the pipeline exited before we were finished
               * writing", so, if _doserrno is ERROR_NO_DATA, this isn't
               * a real error, it just means we're done.  (Windows doesn't
               * SIGPIPE.)
               *
               * Presumably either that program exited deliberately (for
               * example, "head -N" read N lines and printed them), in
               * which case there's no error to report, or it terminated
               * due to an error or a signal, in which case *that's* the
               * error and that error has been reported.
               */
              break;
            }

            /*
             * It's a different error; report it, but with the error
             * message for _doserrno, which will give more detail
             * than just "Invalid argument".
             */
            cmdarg_err("An error occurred while printing packets: %s.",
                       win32strerror(_doserrno));
#else
            cmdarg_err("An error occurred while printing packets: %s.",
                       g_strerror(errno));
#endif
            break;
    }
}

/*
 * General errors and warnings are reported with an console message
 * in Aurora.
 */
static void
failure_warning_message(const char *msg_format, va_list ap) {
    fprintf(stderr, "Aurora: ");
    vfprintf(stderr, msg_format, ap);
    fprintf(stderr, "\n");
}

/*
 * Open/create errors are reported with an console message in Aurora.
 */
static void
open_failure_message(const char *filename, int err, gboolean for_writing) {
    fprintf(stderr, "Aurora: ");
    fprintf(stderr, file_open_error_message(err, for_writing), filename);
    fprintf(stderr, "\n");
}

/*
 * Read errors are reported with an console message in Aurora.
 */
static void
read_failure_message(const char *filename, int err) {
    cmdarg_err("An error occurred while reading from the file \"%s\": %s.",
               filename, g_strerror(err));
}

/*
 * Write errors are reported with an console message in TShark.
 */
static void
write_failure_message(const char *filename, int err) {
    cmdarg_err("An error occurred while writing to the file \"%s\": %s.",
               filename, g_strerror(err));
}

static void reset_epan_mem(capture_file *cf, epan_dissect_t *edt, gboolean tree, gboolean visual) {
    if (!epan_auto_reset || (cf->count < epan_auto_reset_count))
        return;

    fprintf(stderr, "resetting session.\n");

    epan_dissect_cleanup(edt);
    epan_free(cf->epan);

    cf->epan = tshark_epan_new(cf);
    epan_dissect_init(edt, cf->epan, tree, visual);
    cf->count = 0;
}

/*
 * Report additional information for an error in command-line arguments.
 */
static void
failure_message_cont(const char *msg_format, va_list ap) {
    vfprintf(stderr, msg_format, ap);
    fprintf(stderr, "\n");
}

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 2
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * vi: set shiftwidth=2 tabstop=8 expandtab:
 * :indentSize=2:tabSize=8:noTabs=true:
 */
