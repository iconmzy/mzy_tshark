/* editcap.c
 * Edit capture files.  We can delete packets, adjust timestamps, or
 * simply convert from one format to another format.
 *
 * Originally written by Richard Sharpe.
 * Improved by Guy Harris.
 * Further improved by Richard Sharpe.
 *
 * Copyright 2013, Richard Sharpe <realrichardsharpe[AT]gmail.com>
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
#include <stdarg.h>
#include <math.h>

/*
 * Just make sure we include the prototype for strptime as well
 * (needed for glibc 2.2) but make sure we do this only if not
 * yet defined.
 */

#ifndef __USE_XOPEN
#  define __USE_XOPEN
#endif

#include <time.h>
#include <glib.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef HAVE_GETOPT_H
#include <getopt.h>
#endif

#include <wiretap/secrets-types.h>
#include <wiretap/wtap.h>

#include "epan/etypes.h"
#include "epan/dissectors/packet-ieee80211-radiotap-defs.h"

#ifndef HAVE_GETOPT_LONG
#include "wsutil/wsgetopt.h"
#endif

#ifdef _WIN32
#include <process.h>    /* getpid */
#include <winsock2.h>
#endif

#ifndef HAVE_STRPTIME
# include "wsutil/strptime.h"
#endif

#include <ui/clopts_common.h>
#include <ui/cmdarg_err.h>
#include <wsutil/filesystem.h>
#include <wsutil/file_util.h>
#include <wsutil/wsgcrypt.h>
#include <wsutil/plugins.h>
#include <wsutil/privileges.h>
#include <wsutil/report_message.h>
#include <wsutil/strnatcmp.h>
#include <wsutil/str_util.h>
#include <cli_main.h>
#include <version_info.h>
#include <wsutil/pint.h>
#include <wsutil/strtoi.h>
#include <wiretap/wtap_opttypes.h>
#include <wiretap/pcapng.h>

#include "ui/failure_message.h"

#include "ringbuffer.h" /* For RINGBUFFER_MAX_NUM_FILES */
#include "file.h"

#define INVALID_OPTION 1
#define INVALID_FILE 2
#define CANT_EXTRACT_PREFIX 2
#define WRITE_ERROR 2
#define DUMP_ERROR 2
#define NANOSECS_PER_SEC 1000000000

/*
 * Some globals so we can pass things to various routines
 */

struct select_item {
    gboolean inclusive;
    guint first, second;
};

/*
 * Duplicate frame detection
 */
typedef struct _fd_hash_t {
    guint8     digest[16];
    guint32    len;
    nstime_t   frame_time;
} fd_hash_t;

#define DEFAULT_DUP_DEPTH       5   /* Used with -d */
#define MAX_DUP_DEPTH     1000000   /* the maximum window (and actual size of fd_hash[]) for de-duplication */

static fd_hash_t fd_hash[MAX_DUP_DEPTH];
static int       dup_window    = DEFAULT_DUP_DEPTH;
static int       cur_dup_entry = 0;

static guint32   ignored_bytes  = 0;  /* Used with -I */

#define ONE_BILLION 1000000000

/* Weights of different errors we can introduce */
/* We should probably make these command-line arguments */
/* XXX - Should we add a bit-level error? */
#define ERR_WT_BIT      5   /* Flip a random bit */
#define ERR_WT_BYTE     5   /* Substitute a random byte */
#define ERR_WT_ALNUM    5   /* Substitute a random character in [A-Za-z0-9] */
#define ERR_WT_FMT      2   /* Substitute "%s" */
#define ERR_WT_AA       1   /* Fill the remainder of the buffer with 0xAA */
#define ERR_WT_TOTAL    (ERR_WT_BIT + ERR_WT_BYTE + ERR_WT_ALNUM + ERR_WT_FMT + ERR_WT_AA)

#define ALNUM_CHARS     "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
#define ALNUM_LEN       (sizeof(ALNUM_CHARS) - 1)

struct time_adjustment {
    nstime_t tv;
    int is_negative;
};

typedef struct _chop_t {
    int len_begin;
    int off_begin_pos;
    int off_begin_neg;
    int len_end;
    int off_end_pos;
    int off_end_neg;
} chop_t;


#define MAX_SELECTIONS 512
static struct select_item     selectfrm[MAX_SELECTIONS];
static guint                  max_selected              = 0;
static gboolean               keep_em                   = FALSE;
static int                    out_file_type_subtype     = WTAP_FILE_TYPE_SUBTYPE_PCAPNG; /* default to pcapng   */
static int                    out_frame_type            = -2; /* Leave frame type alone */
static gboolean               verbose                   = FALSE; /* Not so verbose         */
static struct time_adjustment time_adj                  = {NSTIME_INIT_ZERO, 0}; /* no adjustment */
static nstime_t               relative_time_window      = NSTIME_INIT_ZERO; /* de-dup time window */
//static nstime_t               starttime                 = NSTIME_INIT_ZERO;
//static nstime_t               stoptime                  = NSTIME_INIT_ZERO;
static gboolean               rem_vlan                  = FALSE;
static gboolean               dup_detect                = FALSE;
static gboolean               dup_detect_by_time        = FALSE;
static gboolean               discard_all_secrets       = FALSE;

static int                    do_strict_time_adjustment = FALSE;
static struct time_adjustment strict_time_adj           = {NSTIME_INIT_ZERO, 0}; /* strict time adjustment */
static nstime_t               previous_time             = NSTIME_INIT_ZERO; /* previous time */

static void handle_chopping(chop_t chop, wtap_packet_header *out_phdr,
                            const wtap_packet_header *in_phdr, guint8 **buf,
                            gboolean adjlen);

static gchar *
abs_time_to_str_with_sec_resolution(const nstime_t *abs_time)
{
    struct tm *tmp;
    gchar     *buf = (gchar *)g_malloc(16);

    tmp = localtime(&abs_time->secs);

    if (tmp) {
        g_snprintf(buf, 16, "%d%02d%02d%02d%02d%02d",
            tmp->tm_year + 1900,
            tmp->tm_mon+1,
            tmp->tm_mday,
            tmp->tm_hour,
            tmp->tm_min,
            tmp->tm_sec);
    } else {
        buf[0] = '\0';
    }

    return buf;
}

static gchar *
fileset_get_filename_by_pattern(guint idx, const wtap_rec *rec,
                                gchar *fprefix, gchar *fsuffix)
{
    gchar  filenum[5+1];
    gchar *timestr;
    gchar *abs_str;

    g_snprintf(filenum, sizeof(filenum), "%05u", idx % RINGBUFFER_MAX_NUM_FILES);
    if (rec->presence_flags & WTAP_HAS_TS) {
        timestr = abs_time_to_str_with_sec_resolution(&rec->ts);
        abs_str = g_strconcat(fprefix, "_", filenum, "_", timestr, fsuffix, NULL);
        g_free(timestr);
    } else
        abs_str = g_strconcat(fprefix, "_", filenum, fsuffix, NULL);

    return abs_str;
}

static gboolean
fileset_extract_prefix_suffix(const char *fname, gchar **fprefix, gchar **fsuffix)
{
    char  *pfx, *last_pathsep;
    gchar *save_file;

    save_file = g_strdup(fname);
    if (save_file == NULL) {
        fprintf(stderr, "editcap: Out of memory\n");
        return FALSE;
    }

    last_pathsep = strrchr(save_file, G_DIR_SEPARATOR);
    pfx = strrchr(save_file,'.');
    if (pfx != NULL && (last_pathsep == NULL || pfx > last_pathsep)) {
        /* The pathname has a "." in it, and it's in the last component
         * of the pathname (because there is either only one component,
         * i.e. last_pathsep is null as there are no path separators,
         * or the "." is after the path separator before the last
         * component.

         * Treat it as a separator between the rest of the file name and
         * the file name suffix, and arrange that the names given to the
         * ring buffer files have the specified suffix, i.e. put the
         * changing part of the name *before* the suffix. */
        pfx[0] = '\0';
        *fprefix = g_strdup(save_file);
        pfx[0] = '.'; /* restore capfile_name */
        *fsuffix = g_strdup(pfx);
    } else {
        /* Either there's no "." in the pathname, or it's in a directory
         * component, so the last component has no suffix. */
        *fprefix = g_strdup(save_file);
        *fsuffix = NULL;
    }
    g_free(save_file);
    return TRUE;
}

/* Was the packet selected? */

static gboolean
selected(guint recno)
{
    guint i;

    for (i = 0; i < max_selected; i++) {
        if (selectfrm[i].inclusive) {
            if (selectfrm[i].first <= recno && selectfrm[i].second >= recno)
                return TRUE;
        } else {
            if (recno == selectfrm[i].first)
                return TRUE;
        }
    }

    return FALSE;
}

#define LINUX_SLL_OFFSETP 14
#define VLAN_SIZE 4
static void
sll_remove_vlan_info(guint8* fd, guint32* len) {
    if (pntoh16(fd + LINUX_SLL_OFFSETP) == ETHERTYPE_VLAN) {
        int rest_len;
        /* point to start of vlan */
        fd = fd + LINUX_SLL_OFFSETP;
        /* bytes to read after vlan info */
        rest_len = *len - (LINUX_SLL_OFFSETP + VLAN_SIZE);
        /* remove vlan info from packet */
        memmove(fd, fd + VLAN_SIZE, rest_len);
        *len -= 4;
    }
}

static void
remove_vlan_info(const wtap_packet_header *phdr, guint8* fd, guint32* len) {
    switch (phdr->pkt_encap) {
        case WTAP_ENCAP_SLL:
            sll_remove_vlan_info(fd, len);
            break;
        default:
            /* no support for current pkt_encap */
            break;
    }
}

static gboolean
is_duplicate(guint8* fd, guint32 len) {
    int i;
//    const struct ieee80211_radiotap_header* tap_header;

    /*Hint to ignore some bytes at the start of the frame for the digest calculation(-I option) */
    guint32 offset = ignored_bytes;
    guint32 new_len;
    guint8 *new_fd;

    if (len <= ignored_bytes) {
        offset = 0;
    }

    new_fd  = &fd[offset];
    new_len = len - (offset);

    cur_dup_entry++;
    if (cur_dup_entry >= dup_window)
        cur_dup_entry = 0;

    /* Calculate our digest */
    gcry_md_hash_buffer(GCRY_MD_MD5, fd_hash[cur_dup_entry].digest, new_fd, new_len);

    fd_hash[cur_dup_entry].len = len;

    /* Look for duplicates */
    for (i = 0; i < dup_window; i++) {
        if (i == cur_dup_entry)
            continue;

        if (fd_hash[i].len == fd_hash[cur_dup_entry].len
            && memcmp(fd_hash[i].digest, fd_hash[cur_dup_entry].digest, 16) == 0) {
            return TRUE;
        }
    }

    return FALSE;
}

static gboolean
is_duplicate_rel_time(guint8* fd, guint32 len, const nstime_t *current) {
    int i;

    /*Hint to ignore some bytes at the start of the frame for the digest calculation(-I option) */
    guint32 offset = ignored_bytes;
    guint32 new_len;
    guint8 *new_fd;

    if (len <= ignored_bytes) {
        offset = 0;
    }

    new_fd  = &fd[offset];
    new_len = len - (offset);

    cur_dup_entry++;
    if (cur_dup_entry >= dup_window)
        cur_dup_entry = 0;

    /* Calculate our digest */
    gcry_md_hash_buffer(GCRY_MD_MD5, fd_hash[cur_dup_entry].digest, new_fd, new_len);

    fd_hash[cur_dup_entry].len = len;
    fd_hash[cur_dup_entry].frame_time.secs = current->secs;
    fd_hash[cur_dup_entry].frame_time.nsecs = current->nsecs;

    /*
     * Look for relative time related duplicates.
     * This is hopefully a reasonably efficient mechanism for
     * finding duplicates by rel time in the fd_hash[] cache.
     * We check starting from the most recently added hash
     * entries and work backwards towards older packets.
     * This approach allows the dup test to be terminated
     * when the relative time of a cached entry is found to
     * be beyond the dup time window.
     *
     * Of course this assumes that the input trace file is
     * "well-formed" in the sense that the packet timestamps are
     * in strict chronologically increasing order (which is NOT
     * always the case!!).
     *
     * The fd_hash[] table was deliberately created large (1,000,000).
     * Looking for time related duplicates in large trace files with
     * non-fractional dup time window values can potentially take
     * a long time to complete.
     */

    for (i = cur_dup_entry - 1;; i--) {
        nstime_t delta;
        int cmp;

        if (i < 0)
            i = dup_window - 1;

        if (i == cur_dup_entry) {
            /*
             * We've decremented back to where we started.
             * Check no more!
             */
            break;
        }

        if (nstime_is_unset(&(fd_hash[i].frame_time))) {
            /*
             * We've decremented to an unused fd_hash[] entry.
             * Check no more!
             */
            break;
        }

        nstime_delta(&delta, current, &fd_hash[i].frame_time);

        if (delta.secs < 0 || delta.nsecs < 0) {
            /*
             * A negative delta implies that the current packet
             * has an absolute timestamp less than the cached packet
             * that it is being compared to.  This is NOT a normal
             * situation since trace files usually have packets in
             * chronological order (oldest to newest).
             *
             * There are several possible ways to deal with this:
             * 1. 'continue' dup checking with the next cached frame.
             * 2. 'break' from looking for a duplicate of the current frame.
             * 3. Take the absolute value of the delta and see if that
             * falls within the specifed dup time window.
             *
             * Currently this code does option 1.  But it would pretty
             * easy to add yet-another-editcap-option to select one of
             * the other behaviors for dealing with out-of-sequence
             * packets.
             */
            continue;
        }

        cmp = nstime_cmp(&delta, &relative_time_window);

        if (cmp > 0) {
            /*
             * The delta time indicates that we are now looking at
             * cached packets beyond the specified dup time window.
             * Check no more!
             */
            break;
        } else if (fd_hash[i].len == fd_hash[cur_dup_entry].len
                   && memcmp(fd_hash[i].digest, fd_hash[cur_dup_entry].digest, 16) == 0) {
            return TRUE;
        }
    }

    return FALSE;
}

static wtap_dumper *
editcap_dump_open(const char *filename, const wtap_dump_params *params,
                  GArray *idbs_seen, int *err, gchar **err_info)
{
    wtap_dumper *pdh;

    if (strcmp(filename, "-") == 0) {
        /* Write to the standard output. */
        pdh = wtap_dump_open_stdout(out_file_type_subtype, WTAP_UNCOMPRESSED,
                                    params, err, err_info);
    } else {
        pdh = wtap_dump_open(filename, out_file_type_subtype, WTAP_UNCOMPRESSED,
                             params, err, err_info);
    }
    if (pdh == NULL)
        return NULL;

    /*
     * If the output file requires interface IDs, add all the IDBs we've
     * seen so far.
     */
    if (wtap_uses_interface_ids(wtap_dump_file_type_subtype(pdh))) {
        for (guint i = 0; i < idbs_seen->len; i++) {
            wtap_block_t if_data = g_array_index(idbs_seen, wtap_block_t, i);

            /*
             * Add this IDB to the file to which we're currently writing.
             */
            if (!wtap_dump_add_idb(pdh, if_data, err, err_info)) {
                int close_err;
                gchar *close_err_info;

                wtap_dump_close(pdh, &close_err, &close_err_info);
                g_free(close_err_info);
                return NULL;
            }
        }
    }
    return pdh;
}

static gboolean
process_new_idbs(wtap *wth, wtap_dumper *pdh, GArray *idbs_seen,
                 int *err, gchar **err_info)
{
    wtap_block_t if_data;

    while ((if_data = wtap_get_next_interface_description(wth)) != NULL) {
        /*
         * Only add IDBs if the output file requires interface IDs;
         * otherwise, it doesn't support writing IDBs.
         */
        if (wtap_uses_interface_ids(wtap_dump_file_type_subtype(pdh))) {
            wtap_block_t if_data_copy;

            /*
             * Add this IDB to the file to which we're currently writing.
             */
            if (!wtap_dump_add_idb(pdh, if_data, err, err_info))
                return FALSE;

            /*
             * Also add it to the set of IDBs we've seen, in case we
             * start writing to another file (which would be of the
             * same type as the current file, and thus will also require
             * interface IDs).
             */
            if_data_copy = wtap_block_make_copy(if_data);
            g_array_append_val(idbs_seen, if_data_copy);
        }
    }
    return TRUE;
}

#define LONGOPT_NO_VLAN              (LONGOPT_BASE_APPLICATION+1)
#define LONGOPT_SKIP_RADIOTAP_HEADER (LONGOPT_BASE_APPLICATION+2)
#define LONGOPT_SEED                 (LONGOPT_BASE_APPLICATION+3)
#define LONGOPT_INJECT_SECRETS       (LONGOPT_BASE_APPLICATION+4)
#define LONGOPT_DISCARD_ALL_SECRETS  (LONGOPT_BASE_APPLICATION+5)
#define LONGOPT_CAPTURE_COMMENT      (LONGOPT_BASE_APPLICATION+6)
#define LONGOPT_DISCARD_CAPTURE_COMMENT (LONGOPT_BASE_APPLICATION+7)

pfileNameNode editcapFileIntoSmalls(char * File_Names_In,char* FIle_Name_out, int num)
{
    wtap         *wth = NULL;
    int           i, read_err, write_err;
    gchar        *read_err_info, *write_err_info;

    guint32       snaplen            = 0; /* No limit               */
    chop_t        chop               = {0, 0, 0, 0, 0, 0}; /* No chop */
    gboolean      adjlen             = FALSE;
    wtap_dumper  *pdh                = NULL;
    GArray       *idbs_seen          = NULL;
    unsigned int  count              = 1;
    unsigned int  duplicate_count    = 0;
    gint64        data_offset;
    guint8       *buf;
    guint32       read_count         = 0;
    guint32       split_packet_count = 0;
    int           written_count      = 0;
    char         *filename           = NULL;
    gboolean      ts_okay;
    nstime_t      secs_per_block     = NSTIME_INIT_UNSET;
    int           block_cnt          = 0;
    nstime_t      block_next         = NSTIME_INIT_UNSET;
    gchar        *fprefix            = NULL;
    gchar        *fsuffix            = NULL;
    guint         max_packet_number  = 0;
    GArray       *dsb_types          = NULL;
    GPtrArray    *dsb_filenames      = NULL;
    wtap_rec                     read_rec;
    Buffer                       read_buf;
    const wtap_rec              *rec;
    wtap_rec                     temp_rec;
    wtap_dump_params             params = WTAP_DUMP_PARAMS_INIT;
    char                        *shb_user_appl;

    /*
     * Get credential information for later use.
     */
    init_process_policies();

//    wtap_init(TRUE);

    split_packet_count = num;

    /*拿到读取文件句柄*/
    wth = wtap_open_offline(File_Names_In, WTAP_TYPE_AUTO, &read_err, &read_err_info, FALSE);

	/*初始化名称头节点*/
	pfileNameNode fileNameNode_Head = (pfileNameNode)malloc(sizeof(struct fileNameNode));
	fileNameNode_Head->next = NULL;
	strcpy(fileNameNode_Head->fileName,"");

    if (!wth) {
        cfile_open_failure_message("editcap", File_Names_In, read_err,
                                   read_err_info);
        goto clean_exit;
    }

    wtap_dump_params_init_no_idbs(&params, wth);
    if (!keep_em)
        max_packet_number = G_MAXUINT;

    /* Set up an array of all IDBs seen */
    idbs_seen = g_array_new(FALSE, FALSE, sizeof(wtap_block_t));

    /* Read all of the packets in turn */
    wtap_rec_init(&read_rec);
    ws_buffer_init(&read_buf, 1514);
    while (wtap_read(wth, &read_rec, &read_buf, &read_err, &read_err_info, &data_offset)) {
        /*
         * XXX - what about non-packet records in the file after this?
         * We can *probably* ignore IDBs after this point, as they
         * presumably indicate that we weren't capturing on that
         * interface at this point, but what about, for example, NRBs?
         */
        if (max_packet_number <= read_count)
            break;

        read_count++;

        rec = &read_rec;

        /* Extra actions for the first packet */
        if (read_count == 1) {
            if (split_packet_count != 0 || !nstime_is_unset(&secs_per_block)) {
                if (!fileset_extract_prefix_suffix(FIle_Name_out, &fprefix, &fsuffix)) {
                    goto clean_exit;
                }

                filename = fileset_get_filename_by_pattern(block_cnt++, rec, fprefix, fsuffix);
            } else {
                filename = g_strdup(FIle_Name_out);
            }
            g_assert(filename);

            /*插入名称节点*/
            pfileNameNode temp = (pfileNameNode)malloc(sizeof(struct fileNameNode));
            strcpy(temp->fileName, filename);
            temp->next = fileNameNode_Head->next;
            fileNameNode_Head->next = temp;

            /* If we don't have an application name add one */
            if (wtap_block_get_string_option_value(g_array_index(params.shb_hdrs, wtap_block_t, 0), OPT_SHB_USERAPPL, &shb_user_appl) != WTAP_OPTTYPE_SUCCESS) {
                wtap_block_add_string_option_format(g_array_index(params.shb_hdrs, wtap_block_t, 0), OPT_SHB_USERAPPL, "%s", get_appname_and_version());
            }

            pdh = editcap_dump_open(filename, &params, idbs_seen, &write_err,
                                    &write_err_info);

            if (pdh == NULL) {
                cfile_dump_open_failure_message("editcap", filename,
                                                write_err, write_err_info,
                                                out_file_type_subtype);
                goto clean_exit;
            }
        } /* first packet only handling */

        /*
         * Process whatever IDBs we haven't seen yet.
         */
        if (!process_new_idbs(wth, pdh, idbs_seen, &write_err, &write_err_info)) {
            cfile_write_failure_message("editcap", File_Names_In,
                                        filename,
                                        write_err, write_err_info,
                                        read_count,
                                        out_file_type_subtype);
            goto clean_exit;
        }

        buf = ws_buffer_start_ptr(&read_buf);

        /*
         * Not all packets have time stamps. Only process the time
         * stamp if we have one.
         */
        if (rec->presence_flags & WTAP_HAS_TS) {
            if (!nstime_is_unset(&secs_per_block)) {
                if (nstime_is_unset(&block_next)) {
                    block_next = rec->ts;
                    nstime_add(&block_next, &secs_per_block);
                }
                while (nstime_cmp(&rec->ts, &block_next) > 0) { /* time for the next file */

                    if (!wtap_dump_close(pdh, &write_err, &write_err_info)) {
                        cfile_close_failure_message(filename, write_err,
                                                    write_err_info);
                        goto clean_exit;
                    }
                    nstime_add(&block_next, &secs_per_block); /* reset for next interval */
                    g_free(filename);
                    filename = fileset_get_filename_by_pattern(block_cnt++, rec, fprefix, fsuffix);
                    g_assert(filename);

                    if (verbose)
                        fprintf(stderr, "Continuing writing in file %s\n", filename);

                    pdh = editcap_dump_open(filename, &params, idbs_seen,
                                            &write_err, &write_err_info);

                    if (pdh == NULL) {
                        cfile_dump_open_failure_message("editcap", filename,
                                                        write_err,
                                                        write_err_info,
                                                        out_file_type_subtype);
                        goto clean_exit;
                    }
                }
            }
        }  /* time stamp handling */

        if (split_packet_count != 0) {
            /* time for the next file? */
            if (written_count > 0 && (written_count % split_packet_count) == 0) {
                if (!wtap_dump_close(pdh, &write_err, &write_err_info)) {
                    cfile_close_failure_message(filename, write_err,
                                                write_err_info);
                    goto clean_exit;
                }

                g_free(filename);
                filename = fileset_get_filename_by_pattern(block_cnt++, rec, fprefix, fsuffix);
                g_assert(filename);

                /*插入名称节点*/
                pfileNameNode temp = (pfileNameNode)malloc(sizeof(struct fileNameNode));
                strcpy(temp->fileName,filename);
                temp->next = fileNameNode_Head->next;
                fileNameNode_Head->next = temp;

                if (verbose)
                    fprintf(stderr, "Continuing writing in file %s\n", filename);

                pdh = editcap_dump_open(filename, &params, idbs_seen,
                                        &write_err, &write_err_info);
                if (pdh == NULL) {
                    cfile_dump_open_failure_message("editcap", filename,
                                                    write_err, write_err_info,
                                                    out_file_type_subtype);
                    goto clean_exit;
                }
            }
        } /* split packet handling */

        /*
         * No selected timeframe, so all packets are "in the
         * selected timeframe".
         */
        ts_okay = TRUE;

        if (ts_okay && ((!selected(count) && !keep_em)
                        || (selected(count) && keep_em))) {

            if (verbose && !dup_detect && !dup_detect_by_time)
                fprintf(stderr, "Packet: %u\n", count);

            rec = &read_rec;

            if (rec->presence_flags & WTAP_HAS_TS) {
                /* Do we adjust timestamps to ensure strict chronological
                 * order? */
                if (do_strict_time_adjustment) {
                    if (previous_time.secs || previous_time.nsecs) {
                        if (!strict_time_adj.is_negative) {
                            nstime_t current;
                            nstime_t delta;

                            current = rec->ts;

                            nstime_delta(&delta, &current, &previous_time);

                            if (delta.secs < 0 || delta.nsecs < 0) {
                                /*
                                 * A negative delta indicates that the current packet
                                 * has an absolute timestamp less than the previous packet
                                 * that it is being compared to.  This is NOT a normal
                                 * situation since trace files usually have packets in
                                 * chronological order (oldest to newest).
                                 * Copy and change rather than modify
                                 * returned rec.
                                 */
                                /* fprintf(stderr, "++out of order, need to adjust this packet!\n"); */
                                temp_rec = *rec;
                                temp_rec.ts.secs = previous_time.secs + strict_time_adj.tv.secs;
                                temp_rec.ts.nsecs = previous_time.nsecs;
                                if (temp_rec.ts.nsecs + strict_time_adj.tv.nsecs >= ONE_BILLION) {
                                    /* carry */
                                    temp_rec.ts.secs++;
                                    temp_rec.ts.nsecs += strict_time_adj.tv.nsecs - ONE_BILLION;
                                } else {
                                    temp_rec.ts.nsecs += strict_time_adj.tv.nsecs;
                                }
                                rec = &temp_rec;
                            }
                        } else {
                            /*
                             * A negative strict time adjustment is requested.
                             * Unconditionally set each timestamp to previous
                             * packet's timestamp plus delta.
                             * Copy and change rather than modify returned
                             * rec.
                             */
                            temp_rec = *rec;
                            temp_rec.ts.secs = previous_time.secs + strict_time_adj.tv.secs;
                            temp_rec.ts.nsecs = previous_time.nsecs;
                            if (temp_rec.ts.nsecs + strict_time_adj.tv.nsecs >= ONE_BILLION) {
                                /* carry */
                                temp_rec.ts.secs++;
                                temp_rec.ts.nsecs += strict_time_adj.tv.nsecs - ONE_BILLION;
                            } else {
                                temp_rec.ts.nsecs += strict_time_adj.tv.nsecs;
                            }
                            rec = &temp_rec;
                        }
                    }
                    previous_time = rec->ts;
                }

                if (time_adj.tv.secs != 0) {
                    /* Copy and change rather than modify returned rec */
                    temp_rec = *rec;
                    if (time_adj.is_negative)
                        temp_rec.ts.secs -= time_adj.tv.secs;
                    else
                        temp_rec.ts.secs += time_adj.tv.secs;
                    rec = &temp_rec;
                }

                if (time_adj.tv.nsecs != 0) {
                    /* Copy and change rather than modify returned rec */
                    temp_rec = *rec;
                    if (time_adj.is_negative) { /* subtract */
                        if (temp_rec.ts.nsecs < time_adj.tv.nsecs) { /* borrow */
                            temp_rec.ts.secs--;
                            temp_rec.ts.nsecs += ONE_BILLION;
                        }
                        temp_rec.ts.nsecs -= time_adj.tv.nsecs;
                    } else {                  /* add */
                        if (temp_rec.ts.nsecs + time_adj.tv.nsecs >= ONE_BILLION) {
                            /* carry */
                            temp_rec.ts.secs++;
                            temp_rec.ts.nsecs += time_adj.tv.nsecs - ONE_BILLION;
                        } else {
                            temp_rec.ts.nsecs += time_adj.tv.nsecs;
                        }
                    }
                    rec = &temp_rec;
                }
            } /* time stamp adjustment */

            if (rec->rec_type == REC_TYPE_PACKET) {
                if (snaplen != 0) {
                    /* Limit capture length to snaplen */
                    if (rec->rec_header.packet_header.caplen > snaplen) {
                        /* Copy and change rather than modify returned wtap_rec */
                        temp_rec = *rec;
                        temp_rec.rec_header.packet_header.caplen = snaplen;
                        rec = &temp_rec;
                    }
                    /* If -L, also set reported length to snaplen */
                    if (adjlen && rec->rec_header.packet_header.len > snaplen) {
                        /* Copy and change rather than modify returned phdr */
                        temp_rec = *rec;
                        temp_rec.rec_header.packet_header.len = snaplen;
                        rec = &temp_rec;
                    }
                }

                /*
                 * If an encapsulation type was specified, override the
                 * encapsulation type of the packet.
                 * Copy and change rather than modify returned rec.
                 */
                if (out_frame_type != -2) {
                    temp_rec = *rec;
                    temp_rec.rec_header.packet_header.pkt_encap = out_frame_type;
                    rec = &temp_rec;
                }

                /*
                 * CHOP
                 * Copy and change rather than modify returned rec.
                 */
                temp_rec = *rec;
                handle_chopping(chop, &temp_rec.rec_header.packet_header,
                                &rec->rec_header.packet_header, &buf,
                                adjlen);
                rec = &temp_rec;

                /* remove vlan info */
                if (rem_vlan) {
                    /* Copy and change rather than modify returned rec */
                    temp_rec = *rec;
                    remove_vlan_info(&rec->rec_header.packet_header, buf,
                                     &temp_rec.rec_header.packet_header.caplen);
                    rec = &temp_rec;
                }

                /* suppress duplicates by packet window */
                if (dup_detect) {
                    if (is_duplicate(buf, rec->rec_header.packet_header.caplen)) {
                        if (verbose) {
                            fprintf(stderr, "Skipped: %u, Len: %u, MD5 Hash: ",
                                    count,
                                    rec->rec_header.packet_header.caplen);
                            for (i = 0; i < 16; i++)
                                fprintf(stderr, "%02x",
                                        (unsigned char)fd_hash[cur_dup_entry].digest[i]);
                            fprintf(stderr, "\n");
                        }
                        duplicate_count++;
                        count++;
                        continue;
                    } else {
                        if (verbose) {
                            fprintf(stderr, "Packet: %u, Len: %u, MD5 Hash: ",
                                    count,
                                    rec->rec_header.packet_header.caplen);
                            for (i = 0; i < 16; i++)
                                fprintf(stderr, "%02x",
                                        (unsigned char)fd_hash[cur_dup_entry].digest[i]);
                            fprintf(stderr, "\n");
                        }
                    }
                } /* suppression of duplicates */

                if (rec->presence_flags & WTAP_HAS_TS) {
                    /* suppress duplicates by time window */
                    if (dup_detect_by_time) {
                        nstime_t current;

                        current.secs  = rec->ts.secs;
                        current.nsecs = rec->ts.nsecs;

                        if (is_duplicate_rel_time(buf,
                                                  rec->rec_header.packet_header.caplen,
                                                  &current)) {
                            if (verbose) {
                                fprintf(stderr, "Skipped: %u, Len: %u, MD5 Hash: ",
                                        count,
                                        rec->rec_header.packet_header.caplen);
                                for (i = 0; i < 16; i++)
                                    fprintf(stderr, "%02x",
                                            (unsigned char)fd_hash[cur_dup_entry].digest[i]);
                                fprintf(stderr, "\n");
                            }
                            duplicate_count++;
                            count++;
                            continue;
                        } else {
                            if (verbose) {
                                fprintf(stderr, "Packet: %u, Len: %u, MD5 Hash: ",
                                        count,
                                        rec->rec_header.packet_header.caplen);
                                for (i = 0; i < 16; i++)
                                    fprintf(stderr, "%02x",
                                            (unsigned char)fd_hash[cur_dup_entry].digest[i]);
                                fprintf(stderr, "\n");
                            }
                        }
                    }
                } /* suppress duplicates by time window */
            }

            if (discard_all_secrets) {
                /*
                 * Discard any secrets we've read since the last packet
                 * we wrote.
                 */
                wtap_dump_discard_decryption_secrets(pdh);
            }

            /* Attempt to dump out current frame to the output file */
            if (!wtap_dump(pdh, rec, buf, &write_err, &write_err_info)) {
                cfile_write_failure_message("editcap", File_Names_In,
                                            filename,
                                            write_err, write_err_info,
                                            read_count,
                                            out_file_type_subtype);
                goto clean_exit;
            }
            written_count++;
        }
        count++;
    }

    wtap_rec_cleanup(&read_rec);
    ws_buffer_free(&read_buf);

    g_free(fprefix);
    g_free(fsuffix);

    if (read_err != 0) {
        /* Print a message noting that the read failed somewhere along the
         * line. */
        cfile_read_failure_message("editcap", File_Names_In, read_err,
                                   read_err_info);
    }

    if (!pdh) {
        /* No valid packages found, open the outfile so we can write an
         * empty header */
        g_free (filename);
        filename = g_strdup(FIle_Name_out);

        pdh = editcap_dump_open(filename, &params, idbs_seen, &write_err,
                                &write_err_info);
        if (pdh == NULL) {
            cfile_dump_open_failure_message("editcap", filename,
                                            write_err, write_err_info,
                                            out_file_type_subtype);
            goto clean_exit;
        }
    }

    if (!wtap_dump_close(pdh, &write_err, &write_err_info)) {
        cfile_close_failure_message(filename, write_err, write_err_info);
        goto clean_exit;
    }
    g_free(filename);

	clean_exit:
    if (dsb_filenames) {
        g_array_free(dsb_types, TRUE);
        g_ptr_array_free(dsb_filenames, TRUE);
    }
    if (idbs_seen != NULL) {
        for (guint b = 0; b < idbs_seen->len; b++) {
            wtap_block_t if_data = g_array_index(idbs_seen, wtap_block_t, b);
            wtap_block_free(if_data);
        }
        g_array_free(idbs_seen, TRUE);
    }
//    g_free(params.idb_inf);
//    wtap_dump_params_cleanup(&params);
    if (wth != NULL)
        wtap_close(wth);
//    wtap_cleanup();
//    free_progdirs();
    return fileNameNode_Head;
}

static void
handle_chopping(chop_t chop, wtap_packet_header *out_phdr,
                const wtap_packet_header *in_phdr, guint8 **buf,
                gboolean adjlen)
{
    /* If we're not chopping anything from one side, then the offset for that
     * side is meaningless. */
    if (chop.len_begin == 0)
        chop.off_begin_pos = chop.off_begin_neg = 0;
    if (chop.len_end == 0)
        chop.off_end_pos = chop.off_end_neg = 0;

    if (chop.off_begin_neg < 0) {
        chop.off_begin_pos += in_phdr->caplen + chop.off_begin_neg;
        chop.off_begin_neg = 0;
    }
    if (chop.off_end_pos > 0) {
        chop.off_end_neg += chop.off_end_pos - in_phdr->caplen;
        chop.off_end_pos = 0;
    }

    /* If we've crossed chopping regions, swap them */
    if (chop.len_begin && chop.len_end) {
        if (chop.off_begin_pos > ((int)in_phdr->caplen + chop.off_end_neg)) {
            int tmp_len, tmp_off;

            tmp_off = in_phdr->caplen + chop.off_end_neg + chop.len_end;
            tmp_len = -chop.len_end;

            chop.off_end_neg = chop.len_begin + chop.off_begin_pos - in_phdr->caplen;
            chop.len_end = -chop.len_begin;

            chop.len_begin = tmp_len;
            chop.off_begin_pos = tmp_off;
        }
    }

    /* Make sure we don't chop off more than we have available */
    if (in_phdr->caplen < (guint32)(chop.off_begin_pos - chop.off_end_neg)) {
        chop.len_begin = 0;
        chop.len_end = 0;
    }
    if ((guint32)(chop.len_begin - chop.len_end) >
        (in_phdr->caplen - (guint32)(chop.off_begin_pos - chop.off_end_neg))) {
        chop.len_begin = in_phdr->caplen - (chop.off_begin_pos - chop.off_end_neg);
        chop.len_end = 0;
    }

    /* Handle chopping from the beginning.  Note that if a beginning offset
     * was specified, we need to keep that piece */
    if (chop.len_begin > 0) {
        *out_phdr = *in_phdr;

        if (chop.off_begin_pos > 0) {
            memmove(*buf + chop.off_begin_pos,
                    *buf + chop.off_begin_pos + chop.len_begin,
                    out_phdr->caplen - chop.len_begin);
        } else {
            *buf += chop.len_begin;
        }
        out_phdr->caplen -= chop.len_begin;

        if (adjlen) {
            if (in_phdr->len > (guint32)chop.len_begin)
                out_phdr->len -= chop.len_begin;
            else
                out_phdr->len = 0;
        }
        in_phdr = out_phdr;
    }

    /* Handle chopping from the end.  Note that if an ending offset was
     * specified, we need to keep that piece */
    if (chop.len_end < 0) {
        *out_phdr = *in_phdr;

        if (chop.off_end_neg < 0) {
            memmove(*buf + (gint)out_phdr->caplen + (chop.len_end + chop.off_end_neg),
                    *buf + (gint)out_phdr->caplen + chop.off_end_neg,
                    -chop.off_end_neg);
        }
        out_phdr->caplen += chop.len_end;

        if (adjlen) {
            if (((signed int) in_phdr->len + chop.len_end) > 0)
                out_phdr->len += chop.len_end;
            else
                out_phdr->len = 0;
        }
        /*in_phdr = out_phdr;*/
    }
}

int readFileList(char *basePath,pfileNameNode head){
        DIR *dir;
        struct dirent *ptr;
        char base[256];

        int len = strlen(basePath);
        if (basePath[len - 1] != '/') {
            strcat(basePath, "/");
        }
        if ((dir=opendir(basePath)) == NULL)
        {
            g_print("Open dir:%s error ...",basePath);
            exit(1);
        }
        while ((ptr=readdir(dir)) != NULL)
        {
            char *cc_ptr = strrchr(ptr->d_name, '.');
            if(NULL != cc_ptr &&  !(strcmp(cc_ptr, ".cap")==0 || strcmp(cc_ptr, ".pcap")==0 || strcmp(cc_ptr, ".pcapng")==0)) continue;

            if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)    ///current dir OR parrent dir
                continue;
            else if(ptr->d_type == 8)   ///file
            {
                pfileNameNode temp = (pfileNameNode)malloc(sizeof(struct fileNameNode));
                char basePath_t[256] = {0};
                strcpy(basePath_t,basePath);
                memset(temp->fileName,'\0',256);
                strcpy(temp->fileName,ptr->d_name);
                strcat(basePath_t,ptr->d_name);
                temp->next = head->next;
                memset(temp->fileName_path,'\0',256);
                strcpy(temp->fileName_path,basePath_t);
                head->next = temp;
//                printf("d_name:%s/%s\n", basePath, ptr->d_name);
            }
            else if(ptr->d_type == 10)    ///link file
            {
                char basePath_t[256] = {0};
                strcpy(basePath_t,basePath);
                strcat(basePath_t,ptr->d_name);
                pfileNameNode temp = (pfileNameNode)malloc(sizeof(struct fileNameNode));
                temp->next = head->next;
                memset(temp->fileName_path,'\0',128);
                strcpy(temp->fileName_path,basePath_t);
                head->next = temp;
//                printf("d_name:%s/%s\n",basePath,ptr->d_name);
            }
            else if(ptr->d_type == 4)    ///dir
            {
                memset(base,'\0',sizeof(base));
                strcpy(base,basePath);
                int lenb = strlen(base);
                if (base[lenb - 1] != '/') {
                    strcat(base, "/");
                }
                strcat(base,ptr->d_name);
                readFileList(base,head);
            }
        }
        closedir(dir);
        return 1;
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
