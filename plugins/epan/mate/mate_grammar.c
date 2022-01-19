/*
** 2000-05-29
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** Driver template for the LEMON parser generator.
**
** The "lemon" program processes an LALR(1) input grammar file, then uses
** this template to construct a parser.  The "lemon" program inserts text
** at each "%%" line.  Also, any "P-a-r-s-e" identifer prefix (without the
** interstitial "-" characters) contained in this template is changed into
** the value of the %name directive from the grammar.  Otherwise, the content
** of this template is copied straight through into the generate parser
** source file.
**
** The following is the concatenation of all %include directives from the
** input grammar file:
*/
#include <stdio.h>
/************ Begin %include sections from the grammar ************************/
#line 1 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"


/* mate_grammar.lemon
 * MATE's configuration language grammar
 *
 * Copyright 2005, Luis E. Garcia Ontanon <luis@ontanon.org>
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

/*
 * XXX - there's a Lemon bug where this grammar produces a parser that
 * fails assertions; to work around it, we disable assert() failures.
 */
#ifndef NDEBUG
#define NDEBUG
#endif

#include "mate.h"
#include "mate_grammar.h"
#include <wsutil/file_util.h>
#include <wsutil/str_util.h>

#define DUMMY void*

typedef struct _extraction {
	gchar* as;
	header_field_info* hfi;
	struct _extraction* next;
	struct _extraction* last;
} extraction_t;

typedef struct _pdu_criteria_t {
	AVPL* criterium_avpl;
	avpl_match_mode criterium_match_mode;
	accept_mode_t criterium_accept_mode;
} pdu_criteria_t;

typedef struct _gop_options {
	gop_tree_mode_t pdu_tree_mode;
	gboolean drop_unassigned;
	gboolean show_times;
	float expiration;
	float idle_timeout;
	float lifetime;
	AVPL* start;
	AVPL* stop;
	AVPL* extras;
} gop_options_t;

typedef struct _gog_statements {
	float expiration;
	gop_tree_mode_t gop_tree_mode;
	GPtrArray* transform_list;
	AVPL* extras;
	LoAL* current_gogkeys;
} gog_statement_t;

typedef struct _transf_match_t {
	avpl_match_mode match_mode;
	AVPL* avpl;
} transf_match_t;

typedef struct _transf_action_t {
	avpl_replace_mode replace_mode;
	AVPL* avpl;
} transf_action_t;

static void configuration_error(mate_config* mc, const gchar* fmt, ...) {
	static gchar error_buffer[256];
	const gchar* incl;
	gint i;
	mate_config_frame* current_frame;
	va_list list;

	va_start( list, fmt );
	g_vsnprintf(error_buffer,sizeof(error_buffer),fmt,list);
	va_end( list );

	i = (gint) mc->config_stack->len;

	while (i--) {

		if (i>0) {
			incl = "\n   included from: ";
		} else {
			incl = " ";
		}

		current_frame = (mate_config_frame *)g_ptr_array_index(mc->config_stack,(guint)i);

		g_string_append_printf(mc->config_error,"%s%s at line %u",incl, current_frame->filename, current_frame->linenum);
	}

	g_string_append_printf(mc->config_error,": %s\n",error_buffer);

	THROW(MateConfigError);

}

static AVPL_Transf* new_transform_elem(AVPL* match, AVPL* replace, avpl_match_mode match_mode, avpl_replace_mode replace_mode) {
	 AVPL_Transf* t = (AVPL_Transf *)g_malloc(sizeof(AVPL_Transf));

	 t->name = NULL;
	 t->match = match;
	 t->replace = replace;
	 t->match_mode = match_mode;
	 t->replace_mode = replace_mode;

	 t->map = NULL;
	 t->next = NULL;

	 return t;
}

static gchar* recolonize(mate_config* mc, gchar* s) {
	GString* str = g_string_new("");
	gchar** vec;
	gchar* r;
	guint i,v;
	gchar c;

	vec = g_strsplit(s,":",0);

	for (i = 0; vec[i]; i++) {
		ascii_strdown_inplace(vec[i]);

		v = 0;
		switch ( strlen(vec[i]) ) {
		 case 2:
			c = vec[i][1];
			vec[i][1] = vec[i][0];
			vec[i][0] = c;
			if (vec[i][0] >= '0' && vec[i][0] <= '9') {
				v += (vec[i][1] - '0' )*16;
			} else {
				v += (vec[i][1] - 'a' + 10)*16;
			}
		/* FALL THROUGH */
		 case 1:
			if (vec[i][0] >= '0' && vec[i][0] <= '9') {
				v += (vec[i][0] - '0' );
			} else {
				v += (vec[i][0] - 'a' + 10);
			}
		 case 0:
			break;
		 default:
			configuration_error(mc,"bad token %s",s);
		}

		g_string_append_printf(str,":%.2X",v);
	}

	g_strfreev(vec);

	g_string_erase(str,0,1);

	r = str->str;

	g_string_free(str,FALSE);

	return r;
}

#line 198 "./mate_grammar.c"
/**************** End of %include directives **********************************/
/* These constants specify the various numeric values for terminal symbols
** in a format understandable to "makeheaders".  This section is blank unless
** "lemon" is run with the "-m" command-line option.
***************** Begin makeheaders token definitions *************************/
/**************** End makeheaders token definitions ***************************/

/* The next sections is a series of control #defines.
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used to store the integer codes
**                       that represent terminal and non-terminal symbols.
**                       "unsigned char" is used if there are fewer than
**                       256 symbols.  Larger types otherwise.
**    YYNOCODE           is a number of type YYCODETYPE that is not used for
**                       any terminal or nonterminal symbol.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       (also known as: "terminal symbols") have fall-back
**                       values which should be used if the original symbol
**                       would not parse.  This permits keywords to sometimes
**                       be used as identifiers, for example.
**    YYACTIONTYPE       is the data type used for "action codes" - numbers
**                       that indicate what to do in response to the next
**                       token.
**    MateParserTOKENTYPE     is the data type used for minor type for terminal
**                       symbols.  Background: A "minor type" is a semantic
**                       value associated with a terminal or non-terminal
**                       symbols.  For example, for an "ID" terminal symbol,
**                       the minor type might be the name of the identifier.
**                       Each non-terminal can have a different minor type.
**                       Terminal symbols all have the same minor type, though.
**                       This macros defines the minor type for terminal
**                       symbols.
**    YYMINORTYPE        is the data type used for all minor types.
**                       This is typically a union of many types, one of
**                       which is MateParserTOKENTYPE.  The entry in the union
**                       for terminal symbols is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    MateParserARG_SDECL     A static variable declaration for the %extra_argument
**    MateParserARG_PDECL     A parameter declaration for the %extra_argument
**    MateParserARG_PARAM     Code to pass %extra_argument as a subroutine parameter
**    MateParserARG_STORE     Code to store %extra_argument into yypParser
**    MateParserARG_FETCH     Code to extract %extra_argument from yypParser
**    MateParserCTX_*         As MateParserARG_ except for %extra_context
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYNTOKEN           Number of terminal symbols
**    YY_MAX_SHIFT       Maximum value for shift actions
**    YY_MIN_SHIFTREDUCE Minimum value for shift-reduce actions
**    YY_MAX_SHIFTREDUCE Maximum value for shift-reduce actions
**    YY_ERROR_ACTION    The yy_action[] code for syntax error
**    YY_ACCEPT_ACTION   The yy_action[] code for accept
**    YY_NO_ACTION       The yy_action[] code for no-op
**    YY_MIN_REDUCE      Minimum value for reduce actions
**    YY_MAX_REDUCE      Maximum value for reduce actions
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/************* Begin control #defines *****************************************/
#define YYCODETYPE unsigned char
#define YYNOCODE 137
#define YYACTIONTYPE unsigned short int
#define MateParserTOKENTYPE  gchar* 
typedef union {
  int yyinit;
  MateParserTOKENTYPE yy0;
  AVPL_Transf* yy11;
  AVPL* yy70;
  LoAL* yy77;
  transf_action_t* yy85;
  avpl_replace_mode yy143;
  transf_match_t* yy146;
  GPtrArray* yy147;
  accept_mode_t yy148;
  gop_options_t* yy155;
  extraction_t* yy179;
  gboolean yy182;
  header_field_info* yy210;
  gchar* yy212;
  AVP* yy226;
  gog_statement_t* yy229;
  pdu_criteria_t* yy231;
  float yy255;
  gop_tree_mode_t yy256;
  avpl_match_mode yy274;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define MateParserARG_SDECL  mate_config* mc ;
#define MateParserARG_PDECL , mate_config* mc 
#define MateParserARG_PARAM ,mc 
#define MateParserARG_FETCH  mate_config* mc =yypParser->mc ;
#define MateParserARG_STORE yypParser->mc =mc ;
#define MateParserCTX_SDECL
#define MateParserCTX_PDECL
#define MateParserCTX_PARAM
#define MateParserCTX_FETCH
#define MateParserCTX_STORE
#define YYNSTATE             183
#define YYNRULE              149
#define YYNTOKEN             62
#define YY_MAX_SHIFT         182
#define YY_MIN_SHIFTREDUCE   287
#define YY_MAX_SHIFTREDUCE   435
#define YY_ERROR_ACTION      436
#define YY_ACCEPT_ACTION     437
#define YY_NO_ACTION         438
#define YY_MIN_REDUCE        439
#define YY_MAX_REDUCE        587
/************* End control #defines *******************************************/
#define YY_NLOOKAHEAD ((int)(sizeof(yy_lookahead)/sizeof(yy_lookahead[0])))

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N <= YY_MAX_SHIFT             Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   N between YY_MIN_SHIFTREDUCE       Shift to an arbitrary state then
**     and YY_MAX_SHIFTREDUCE           reduce by rule N-YY_MIN_SHIFTREDUCE.
**
**   N == YY_ERROR_ACTION               A syntax error has occurred.
**
**   N == YY_ACCEPT_ACTION              The parser accepts its input.
**
**   N == YY_NO_ACTION                  No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
**   N between YY_MIN_REDUCE            Reduce by rule N-YY_MIN_REDUCE
**     and YY_MAX_REDUCE
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as either:
**
**    (A)   N = yy_action[ yy_shift_ofst[S] + X ]
**    (B)   N = yy_default[S]
**
** The (A) formula is preferred.  The B formula is used instead if
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X.
**
** The formulas above are for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
**
*********** Begin parsing tables **********************************************/
#define YY_ACTTAB_COUNT (309)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   553,  182,  554,  181,  545,    8,  460,    4,  437,    1,
 /*    10 */   542,  138,  126,  111,  165,  546,  101,   47,  381,  395,
 /*    20 */   396,  139,  398,   75,  141,  481,  102,   11,  527,  103,
 /*    30 */   541,  318,  319,  315,  316,  317,  536,  306,  459,    4,
 /*    40 */   129,   99,   70,    5,  528,  358,  359,  360,  361,  482,
 /*    50 */     6,  554,  554,  554,  554,  554,  554,   20,  472,  366,
 /*    60 */   374,   71,  397,  323,  372,  373,    3,   43,   50,   98,
 /*    70 */   491,   64,  399,  400,  392,  387,  100,  491,  362,  363,
 /*    80 */   327,  328,   74,   20,  386,  167,  166,   43,  340,  385,
 /*    90 */   129,  107,  119,  161,   66,  157,   73,   63,  118,  365,
 /*   100 */   106,   63,  115,    7,  116,  378,  117,   27,  105,   42,
 /*   110 */   120,  109,  131,   19,  132,  133,  142,  143,  144,  148,
 /*   120 */    15,  149,  150,   18,   22,  156,  151,   11,   14,  152,
 /*   130 */   158,   16,   26,   25,   24,   23,   50,   49,   48,  364,
 /*   140 */    44,   31,   30,   29,  102,   28,    2,   10,  146,  124,
 /*   150 */    34,   33,   45,   52,  122,   51,   32,   46,   59,   57,
 /*   160 */    55,   53,   54,   58,   69,   39,   67,  112,  113,  114,
 /*   170 */    56,  135,   68,   17,   38,  140,   37,   41,   36,   35,
 /*   180 */   123,   40,  535,   21,  162,  490,  155,  147,  127,  175,
 /*   190 */    12,  130,  178,  136,  172,  169,  104,  462,  377,  370,
 /*   200 */   368,  367,  110,  465,  540,  108,    9,  344,  346,  379,
 /*   210 */   352,  354,  356,  342,  348,  350,  341,   61,   65,   62,
 /*   220 */   121,   60,  331,  325,  125,  332,  128,   77,  334,   78,
 /*   230 */   336,  321,  134,   13,   72,  145,  309,   83,  154,   80,
 /*   240 */    81,  137,  305,   76,  293,  294,   90,   84,   82,  180,
 /*   250 */   164,   91,   93,   87,  295,   95,  160,   86,   88,   94,
 /*   260 */   418,   96,  296,   79,  297,  298,  299,  301,  423,  438,
 /*   270 */   302,  168,  153,   85,  290,  303,  304,  291,  431,  438,
 /*   280 */   171,  300,  159,  438,  438,  417,   89,  438,  173,  288,
 /*   290 */   174,  163,  287,  292,  438,  289,   92,  438,  438,  176,
 /*   300 */   438,   97,  411,  177,  410,  438,  170,  438,  179,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     0,    1,   62,    3,  107,   64,   65,   66,  109,  110,
 /*    10 */   107,   11,   12,   13,   14,  107,  108,   85,    2,    7,
 /*    20 */     8,   67,   10,   69,   24,   80,    8,   24,   96,  105,
 /*    30 */   106,   29,   30,   26,   27,   28,   98,    5,   65,   66,
 /*    40 */    37,  103,   97,   95,   96,   44,   45,   46,   47,   80,
 /*    50 */    81,  111,  112,  113,  114,  115,  116,   25,   56,   10,
 /*    60 */    47,    4,   50,    2,   51,   52,    4,   53,   54,  101,
 /*    70 */   102,   55,   60,   61,    5,   57,  101,  102,   48,   49,
 /*    80 */    35,   36,   55,   25,   57,    7,    8,   53,    8,    8,
 /*    90 */    37,   99,   73,   73,   68,   99,   68,   40,   74,   50,
 /*   100 */    71,   40,   71,   56,   71,    8,   71,   22,  104,   70,
 /*   110 */    74,   88,   74,   76,   74,   74,   74,   74,   74,   71,
 /*   120 */    58,   71,   71,   23,   18,   71,   74,   24,   59,   74,
 /*   130 */    74,   21,   16,   20,   19,   18,   54,   43,   42,    8,
 /*   140 */    94,   39,   17,   16,    8,   34,    4,   33,  127,   72,
 /*   150 */    17,   16,   93,   86,   88,   87,   15,   97,   83,   85,
 /*   160 */    89,   91,   90,   84,   75,   22,   78,  104,  104,  104,
 /*   170 */    97,   79,   77,   21,   16,   63,   20,   22,   19,   18,
 /*   180 */   104,   18,   98,   23,   13,  102,   12,   11,  102,   12,
 /*   190 */   100,  104,   13,  102,   11,    9,    6,  104,    2,    2,
 /*   200 */     2,    2,    8,  104,  106,    5,    4,    2,    2,    2,
 /*   210 */     2,    2,    2,    2,    2,    2,    2,   25,   38,   41,
 /*   220 */     5,    4,    2,    2,    8,    2,    8,  126,    2,  125,
 /*   230 */     2,    2,    5,   32,   31,    5,    2,  129,  133,  132,
 /*   240 */   131,    8,    2,    8,    2,    2,  123,  128,  130,  121,
 /*   250 */   124,  122,  120,  132,    2,  118,  136,  135,  134,  119,
 /*   260 */     2,  117,    2,    4,    2,    2,    2,    2,    2,  137,
 /*   270 */     2,   10,    5,    4,    2,    2,    2,    2,    2,  137,
 /*   280 */     9,    2,    5,  137,  137,    2,    4,  137,   10,    2,
 /*   290 */     9,    5,    2,    2,  137,    2,    4,  137,  137,   10,
 /*   300 */   137,    4,    2,    9,    2,  137,   10,  137,    5,  137,
 /*   310 */   137,  137,  137,  137,  137,  137,  137,  137,  137,  137,
 /*   320 */   137,  137,  137,  137,  137,  137,  137,  137,  137,  137,
 /*   330 */   137,  137,  137,  137,  137,  137,  137,  137,  137,  137,
 /*   340 */   137,  137,  137,  137,  137,  137,  137,  137,  137,  137,
 /*   350 */   137,  137,  137,  137,  137,  137,  137,  137,  137,  137,
 /*   360 */   137,  137,  137,  137,  137,  137,  137,  137,  137,  137,
 /*   370 */   137,
};
#define YY_SHIFT_COUNT    (182)
#define YY_SHIFT_MIN      (0)
#define YY_SHIFT_MAX      (303)
static const unsigned short int yy_shift_ofst[] = {
 /*     0 */   309,    0,   58,   12,    2,   14,    3,   18,   32,   34,
 /*    10 */    80,   81,   53,   80,   12,   12,    1,    1,   13,    7,
 /*    20 */     7,   13,   49,   49,   49,   49,   30,   30,   45,   30,
 /*    30 */    30,   30,   30,   30,   30,   49,   49,   49,   30,   30,
 /*    40 */    49,   30,   47,   97,   85,  100,  106,  103,   47,   47,
 /*    50 */    47,   85,  110,  116,  113,  115,  117,  103,   82,   94,
 /*    60 */    96,   47,  131,   80,   81,   80,   47,  102,  125,  127,
 /*    70 */   111,  114,   80,   47,  136,   47,  142,  133,  135,  141,
 /*    80 */   143,  152,  158,  156,  159,  161,  155,  160,  152,  163,
 /*    90 */   171,  174,  176,  179,  177,  183,  186,  190,   61,   16,
 /*   100 */    57,   69,   62,   27,   78,  196,  197,  198,  199,  200,
 /*   110 */   202,  194,  205,  206,  207,  208,  209,  210,  211,  212,
 /*   120 */   213,  214,  215,  217,  192,  178,  216,  220,  180,  218,
 /*   130 */   221,  223,  226,  228,  229,  227,  201,  203,  233,  234,
 /*   140 */   240,  235,  242,  243,  252,  258,  230,  259,  260,  262,
 /*   150 */   263,  264,  265,  266,  267,  269,  268,  273,  274,  276,
 /*   160 */   277,  279,  282,  283,  286,  292,  287,  290,  293,  261,
 /*   170 */   272,  296,  271,  275,  278,  281,  291,  289,  294,  300,
 /*   180 */   303,  297,  302,
};
#define YY_REDUCE_COUNT (97)
#define YY_REDUCE_MIN   (-103)
#define YY_REDUCE_MAX   (144)
static const short yy_reduce_ofst[] = {
 /*     0 */  -101,  -60,  -59,  -92,  -46,  -68,  -55,  -76,  -27,  -52,
 /*    10 */   -32,  -62,  -31,  -25, -103,  -97,   19,   20,   -8,   26,
 /*    20 */    28,   -4,   29,   31,   33,   35,   24,   36,   37,   38,
 /*    30 */    40,   41,   42,   43,   44,   48,   50,   51,   52,   55,
 /*    40 */    54,   56,    4,   39,   23,   46,   59,   60,   63,   64,
 /*    50 */    65,   66,   68,   67,   70,   72,   71,   73,   74,   79,
 /*    60 */    75,   76,   77,   83,   84,   86,   87,   92,   88,   95,
 /*    70 */    89,   90,   91,   93,   98,   99,  112,   21,  101,  104,
 /*    80 */   105,  107,  109,  118,  108,  119,  120,  122,  121,  124,
 /*    90 */   126,  123,  129,  128,  132,  140,  137,  144,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   555,  436,  463,  436,  464,  532,  534,  436,  463,  436,
 /*    10 */   436,  436,  436,  436,  436,  436,  436,  436,  436,  466,
 /*    20 */   466,  436,  436,  436,  436,  436,  436,  436,  478,  436,
 /*    30 */   436,  436,  436,  436,  436,  436,  436,  436,  436,  436,
 /*    40 */   436,  436,  436,  436,  503,  521,  523,  534,  436,  436,
 /*    50 */   436,  503,  501,  495,  509,  507,  505,  534,  532,  499,
 /*    60 */   497,  436,  436,  436,  436,  436,  436,  489,  487,  485,
 /*    70 */   476,  474,  436,  436,  436,  436,  436,  574,  573,  572,
 /*    80 */   582,  581,  580,  579,  578,  577,  587,  586,  581,  585,
 /*    90 */   584,  576,  571,  568,  567,  566,  565,  564,  436,  436,
 /*   100 */   436,  436,  543,  436,  436,  436,  436,  436,  436,  436,
 /*   110 */   436,  436,  436,  436,  436,  436,  436,  436,  436,  436,
 /*   120 */   436,  436,  436,  436,  436,  436,  436,  436,  436,  436,
 /*   130 */   436,  436,  436,  436,  436,  436,  436,  436,  436,  436,
 /*   140 */   436,  436,  436,  436,  436,  436,  436,  436,  436,  436,
 /*   150 */   436,  436,  436,  436,  436,  436,  436,  436,  436,  436,
 /*   160 */   436,  436,  436,  436,  436,  436,  436,  436,  436,  436,
 /*   170 */   436,  436,  436,  436,  436,  436,  436,  436,  436,  436,
 /*   180 */   436,  436,  436,
};
/********** End of lemon-generated parsing tables *****************************/

/* The next table maps tokens (terminal symbols) into fallback tokens.
** If a construct like the following:
**
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
**
** This feature can be used, for example, to cause some keywords in a language
** to revert to identifiers if they keyword does not apply in the context where
** it appears.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
**
** After the "shift" half of a SHIFTREDUCE action, the stateno field
** actually contains the reduce action for the second half of the
** SHIFTREDUCE.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number, or reduce action in SHIFTREDUCE */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  yyStackEntry *yytos;          /* Pointer to top element of the stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyhwm;                    /* High-water mark of the stack */
#endif
#ifndef YYNOERRORRECOVERY
  int yyerrcnt;                 /* Shifts left before out of the error */
#endif
  MateParserARG_SDECL                /* A place to hold %extra_argument */
  MateParserCTX_SDECL                /* A place to hold %extra_context */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
  yyStackEntry yystk0;          /* First stack entry */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
  yyStackEntry *yystackEnd;            /* Last entry in the stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/*
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void MateParserTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#if defined(YYCOVERAGE) || !defined(NDEBUG)
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = {
  /*    0 */ "$",
  /*    1 */ "DONE_KW",
  /*    2 */ "SEMICOLON",
  /*    3 */ "DEBUG_KW",
  /*    4 */ "OPEN_BRACE",
  /*    5 */ "CLOSE_BRACE",
  /*    6 */ "FILENAME_KW",
  /*    7 */ "QUOTED",
  /*    8 */ "NAME",
  /*    9 */ "LEVEL_KW",
  /*   10 */ "INTEGER",
  /*   11 */ "PDU_KW",
  /*   12 */ "GOP_KW",
  /*   13 */ "GOG_KW",
  /*   14 */ "DEFAULT_KW",
  /*   15 */ "LAST_EXTRACTED_KW",
  /*   16 */ "DROP_UNASSIGNED_KW",
  /*   17 */ "DISCARD_PDU_DATA_KW",
  /*   18 */ "EXPIRATION_KW",
  /*   19 */ "IDLE_TIMEOUT_KW",
  /*   20 */ "LIFETIME_KW",
  /*   21 */ "SHOW_TREE_KW",
  /*   22 */ "SHOW_TIMES_KW",
  /*   23 */ "GOP_TREE_KW",
  /*   24 */ "TRANSFORM_KW",
  /*   25 */ "MATCH_KW",
  /*   26 */ "STRICT_KW",
  /*   27 */ "EVERY_KW",
  /*   28 */ "LOOSE_KW",
  /*   29 */ "REPLACE_KW",
  /*   30 */ "INSERT_KW",
  /*   31 */ "PROTO_KW",
  /*   32 */ "TRANSPORT_KW",
  /*   33 */ "PAYLOAD_KW",
  /*   34 */ "CRITERIA_KW",
  /*   35 */ "ACCEPT_KW",
  /*   36 */ "REJECT_KW",
  /*   37 */ "EXTRACT_KW",
  /*   38 */ "FROM_KW",
  /*   39 */ "LAST_PDU_KW",
  /*   40 */ "SLASH",
  /*   41 */ "ON_KW",
  /*   42 */ "START_KW",
  /*   43 */ "STOP_KW",
  /*   44 */ "NO_TREE_KW",
  /*   45 */ "PDU_TREE_KW",
  /*   46 */ "FRAME_TREE_KW",
  /*   47 */ "BASIC_TREE_KW",
  /*   48 */ "TRUE_KW",
  /*   49 */ "FALSE_KW",
  /*   50 */ "FLOATING",
  /*   51 */ "NULL_TREE_KW",
  /*   52 */ "FULL_TREE_KW",
  /*   53 */ "MEMBER_KW",
  /*   54 */ "EXTRA_KW",
  /*   55 */ "COMMA",
  /*   56 */ "OPEN_PARENS",
  /*   57 */ "CLOSE_PARENS",
  /*   58 */ "AVP_OPERATOR",
  /*   59 */ "PIPE",
  /*   60 */ "DOTED_IP",
  /*   61 */ "COLONIZED",
  /*   62 */ "transform_decl",
  /*   63 */ "transform_body",
  /*   64 */ "transform_statements",
  /*   65 */ "transform_statement",
  /*   66 */ "transform_match",
  /*   67 */ "transform_action",
  /*   68 */ "match_mode",
  /*   69 */ "action_mode",
  /*   70 */ "gop_name",
  /*   71 */ "time_value",
  /*   72 */ "pdu_name",
  /*   73 */ "gop_tree_mode",
  /*   74 */ "true_false",
  /*   75 */ "criteria_statement",
  /*   76 */ "accept_mode",
  /*   77 */ "pdu_drop_unassigned_statement",
  /*   78 */ "discard_pdu_data_statement",
  /*   79 */ "last_extracted_statement",
  /*   80 */ "extraction_statement",
  /*   81 */ "extraction_statements",
  /*   82 */ "gop_options",
  /*   83 */ "gop_start_statement",
  /*   84 */ "gop_stop_statement",
  /*   85 */ "extra_statement",
  /*   86 */ "gop_drop_unassigned_statement",
  /*   87 */ "show_goptree_statement",
  /*   88 */ "show_times_statement",
  /*   89 */ "gop_expiration_statement",
  /*   90 */ "idle_timeout_statement",
  /*   91 */ "lifetime_statement",
  /*   92 */ "gog_statements",
  /*   93 */ "gog_expiration_statement",
  /*   94 */ "gog_goptree_statement",
  /*   95 */ "gog_key_statements",
  /*   96 */ "gog_key_statement",
  /*   97 */ "transform_list_statement",
  /*   98 */ "transform",
  /*   99 */ "gop_tree_type",
  /*  100 */ "payload_statement",
  /*  101 */ "proto_stack",
  /*  102 */ "field",
  /*  103 */ "transform_list",
  /*  104 */ "avpl",
  /*  105 */ "avps",
  /*  106 */ "avp",
  /*  107 */ "value",
  /*  108 */ "avp_oneoff",
  /*  109 */ "mate_config",
  /*  110 */ "decls",
  /*  111 */ "decl",
  /*  112 */ "pdu_decl",
  /*  113 */ "gop_decl",
  /*  114 */ "gog_decl",
  /*  115 */ "defaults_decl",
  /*  116 */ "debug_decl",
  /*  117 */ "dbgfile_default",
  /*  118 */ "dbglevel_default",
  /*  119 */ "pdu_dbglevel_default",
  /*  120 */ "gop_dbglevel_default",
  /*  121 */ "gog_dbglevel_default",
  /*  122 */ "pdu_defaults",
  /*  123 */ "gop_defaults",
  /*  124 */ "gog_defaults",
  /*  125 */ "pdu_last_extracted_default",
  /*  126 */ "pdu_drop_unassigned_default",
  /*  127 */ "pdu_discard_default",
  /*  128 */ "gop_expiration_default",
  /*  129 */ "gop_idle_timeout_default",
  /*  130 */ "gop_lifetime_default",
  /*  131 */ "gop_drop_unassigned_default",
  /*  132 */ "gop_tree_mode_default",
  /*  133 */ "gop_show_times_default",
  /*  134 */ "gog_expiration_default",
  /*  135 */ "gog_goptree_default",
  /*  136 */ "gog_show_times_default",
};
#endif /* defined(YYCOVERAGE) || !defined(NDEBUG) */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "dbgfile_default ::= FILENAME_KW QUOTED SEMICOLON",
 /*   1 */ "dbgfile_default ::= FILENAME_KW NAME SEMICOLON",
 /*   2 */ "dbglevel_default ::= LEVEL_KW INTEGER SEMICOLON",
 /*   3 */ "pdu_dbglevel_default ::= PDU_KW LEVEL_KW INTEGER SEMICOLON",
 /*   4 */ "gop_dbglevel_default ::= GOP_KW LEVEL_KW INTEGER SEMICOLON",
 /*   5 */ "gog_dbglevel_default ::= GOG_KW LEVEL_KW INTEGER SEMICOLON",
 /*   6 */ "pdu_last_extracted_default ::= LAST_EXTRACTED_KW true_false SEMICOLON",
 /*   7 */ "pdu_drop_unassigned_default ::= DROP_UNASSIGNED_KW true_false SEMICOLON",
 /*   8 */ "pdu_discard_default ::= DISCARD_PDU_DATA_KW true_false SEMICOLON",
 /*   9 */ "gop_expiration_default ::= EXPIRATION_KW time_value SEMICOLON",
 /*  10 */ "gop_idle_timeout_default ::= IDLE_TIMEOUT_KW time_value SEMICOLON",
 /*  11 */ "gop_lifetime_default ::= LIFETIME_KW time_value SEMICOLON",
 /*  12 */ "gop_drop_unassigned_default ::= DROP_UNASSIGNED_KW true_false SEMICOLON",
 /*  13 */ "gop_tree_mode_default ::= SHOW_TREE_KW gop_tree_mode SEMICOLON",
 /*  14 */ "gop_show_times_default ::= SHOW_TIMES_KW true_false SEMICOLON",
 /*  15 */ "gog_expiration_default ::= EXPIRATION_KW time_value SEMICOLON",
 /*  16 */ "gog_goptree_default ::= GOP_TREE_KW gop_tree_type SEMICOLON",
 /*  17 */ "gog_show_times_default ::= SHOW_TIMES_KW true_false SEMICOLON",
 /*  18 */ "transform_decl ::= TRANSFORM_KW NAME transform_body SEMICOLON",
 /*  19 */ "transform_body ::= OPEN_BRACE transform_statements CLOSE_BRACE",
 /*  20 */ "transform_statements ::= transform_statements transform_statement",
 /*  21 */ "transform_statements ::= transform_statement",
 /*  22 */ "transform_statement ::= transform_match transform_action SEMICOLON",
 /*  23 */ "transform_match ::= MATCH_KW match_mode avpl",
 /*  24 */ "transform_match ::=",
 /*  25 */ "transform_action ::=",
 /*  26 */ "transform_action ::= action_mode avpl",
 /*  27 */ "match_mode ::=",
 /*  28 */ "match_mode ::= STRICT_KW",
 /*  29 */ "match_mode ::= EVERY_KW",
 /*  30 */ "match_mode ::= LOOSE_KW",
 /*  31 */ "action_mode ::= REPLACE_KW",
 /*  32 */ "action_mode ::= INSERT_KW",
 /*  33 */ "action_mode ::=",
 /*  34 */ "pdu_decl ::= PDU_KW NAME PROTO_KW field TRANSPORT_KW proto_stack OPEN_BRACE payload_statement extraction_statements transform_list_statement criteria_statement pdu_drop_unassigned_statement discard_pdu_data_statement last_extracted_statement CLOSE_BRACE SEMICOLON",
 /*  35 */ "payload_statement ::=",
 /*  36 */ "payload_statement ::= PAYLOAD_KW proto_stack SEMICOLON",
 /*  37 */ "criteria_statement ::=",
 /*  38 */ "criteria_statement ::= CRITERIA_KW accept_mode match_mode avpl SEMICOLON",
 /*  39 */ "accept_mode ::=",
 /*  40 */ "accept_mode ::= ACCEPT_KW",
 /*  41 */ "accept_mode ::= REJECT_KW",
 /*  42 */ "extraction_statements ::= extraction_statements extraction_statement",
 /*  43 */ "extraction_statements ::= extraction_statement",
 /*  44 */ "extraction_statement ::= EXTRACT_KW NAME FROM_KW field SEMICOLON",
 /*  45 */ "pdu_drop_unassigned_statement ::= DROP_UNASSIGNED_KW true_false SEMICOLON",
 /*  46 */ "pdu_drop_unassigned_statement ::=",
 /*  47 */ "discard_pdu_data_statement ::= DISCARD_PDU_DATA_KW true_false SEMICOLON",
 /*  48 */ "discard_pdu_data_statement ::=",
 /*  49 */ "last_extracted_statement ::= LAST_PDU_KW true_false SEMICOLON",
 /*  50 */ "last_extracted_statement ::=",
 /*  51 */ "proto_stack ::= proto_stack SLASH field",
 /*  52 */ "proto_stack ::= field",
 /*  53 */ "field ::= NAME",
 /*  54 */ "gop_decl ::= GOP_KW NAME ON_KW pdu_name MATCH_KW avpl OPEN_BRACE gop_start_statement gop_stop_statement extra_statement transform_list_statement gop_expiration_statement idle_timeout_statement lifetime_statement gop_drop_unassigned_statement show_goptree_statement show_times_statement CLOSE_BRACE SEMICOLON",
 /*  55 */ "gop_drop_unassigned_statement ::= DROP_UNASSIGNED_KW true_false SEMICOLON",
 /*  56 */ "gop_drop_unassigned_statement ::=",
 /*  57 */ "gop_start_statement ::= START_KW avpl SEMICOLON",
 /*  58 */ "gop_start_statement ::=",
 /*  59 */ "gop_stop_statement ::= STOP_KW avpl SEMICOLON",
 /*  60 */ "gop_stop_statement ::=",
 /*  61 */ "show_goptree_statement ::= SHOW_TREE_KW gop_tree_mode SEMICOLON",
 /*  62 */ "show_goptree_statement ::=",
 /*  63 */ "show_times_statement ::= SHOW_TIMES_KW true_false SEMICOLON",
 /*  64 */ "show_times_statement ::=",
 /*  65 */ "gop_expiration_statement ::= EXPIRATION_KW time_value SEMICOLON",
 /*  66 */ "gop_expiration_statement ::=",
 /*  67 */ "idle_timeout_statement ::= IDLE_TIMEOUT_KW time_value SEMICOLON",
 /*  68 */ "idle_timeout_statement ::=",
 /*  69 */ "lifetime_statement ::= LIFETIME_KW time_value SEMICOLON",
 /*  70 */ "lifetime_statement ::=",
 /*  71 */ "gop_tree_mode ::= NO_TREE_KW",
 /*  72 */ "gop_tree_mode ::= PDU_TREE_KW",
 /*  73 */ "gop_tree_mode ::= FRAME_TREE_KW",
 /*  74 */ "gop_tree_mode ::= BASIC_TREE_KW",
 /*  75 */ "true_false ::= TRUE_KW",
 /*  76 */ "true_false ::= FALSE_KW",
 /*  77 */ "pdu_name ::= NAME",
 /*  78 */ "time_value ::= FLOATING",
 /*  79 */ "time_value ::= INTEGER",
 /*  80 */ "gog_decl ::= GOG_KW NAME OPEN_BRACE gog_key_statements extra_statement transform_list_statement gog_expiration_statement gog_goptree_statement show_times_statement CLOSE_BRACE SEMICOLON",
 /*  81 */ "gog_goptree_statement ::= GOP_TREE_KW gop_tree_type SEMICOLON",
 /*  82 */ "gog_goptree_statement ::=",
 /*  83 */ "gog_expiration_statement ::= EXPIRATION_KW time_value SEMICOLON",
 /*  84 */ "gog_expiration_statement ::=",
 /*  85 */ "gop_tree_type ::= NULL_TREE_KW",
 /*  86 */ "gop_tree_type ::= FULL_TREE_KW",
 /*  87 */ "gop_tree_type ::= BASIC_TREE_KW",
 /*  88 */ "gog_key_statements ::= gog_key_statements gog_key_statement",
 /*  89 */ "gog_key_statements ::= gog_key_statement",
 /*  90 */ "gog_key_statement ::= MEMBER_KW gop_name avpl SEMICOLON",
 /*  91 */ "gop_name ::= NAME",
 /*  92 */ "extra_statement ::= EXTRA_KW avpl SEMICOLON",
 /*  93 */ "extra_statement ::=",
 /*  94 */ "transform_list_statement ::= TRANSFORM_KW transform_list SEMICOLON",
 /*  95 */ "transform_list_statement ::=",
 /*  96 */ "transform_list ::= transform_list COMMA transform",
 /*  97 */ "transform_list ::= transform",
 /*  98 */ "transform ::= NAME",
 /*  99 */ "avpl ::= OPEN_PARENS avps CLOSE_PARENS",
 /* 100 */ "avpl ::= OPEN_PARENS CLOSE_PARENS",
 /* 101 */ "avps ::= avps COMMA avp",
 /* 102 */ "avps ::= avp",
 /* 103 */ "avp ::= NAME AVP_OPERATOR value",
 /* 104 */ "avp ::= NAME",
 /* 105 */ "avp ::= NAME OPEN_BRACE avp_oneoff CLOSE_BRACE",
 /* 106 */ "avp_oneoff ::= avp_oneoff PIPE value",
 /* 107 */ "avp_oneoff ::= value",
 /* 108 */ "value ::= QUOTED",
 /* 109 */ "value ::= NAME",
 /* 110 */ "value ::= FLOATING",
 /* 111 */ "value ::= INTEGER",
 /* 112 */ "value ::= DOTED_IP",
 /* 113 */ "value ::= COLONIZED",
 /* 114 */ "mate_config ::= decls",
 /* 115 */ "decls ::= decls decl",
 /* 116 */ "decls ::=",
 /* 117 */ "decl ::= pdu_decl",
 /* 118 */ "decl ::= gop_decl",
 /* 119 */ "decl ::= gog_decl",
 /* 120 */ "decl ::= transform_decl",
 /* 121 */ "decl ::= defaults_decl",
 /* 122 */ "decl ::= debug_decl",
 /* 123 */ "decl ::= DONE_KW SEMICOLON",
 /* 124 */ "debug_decl ::= DEBUG_KW OPEN_BRACE dbgfile_default dbglevel_default pdu_dbglevel_default gop_dbglevel_default gog_dbglevel_default CLOSE_BRACE SEMICOLON",
 /* 125 */ "dbgfile_default ::=",
 /* 126 */ "dbglevel_default ::=",
 /* 127 */ "pdu_dbglevel_default ::=",
 /* 128 */ "gop_dbglevel_default ::=",
 /* 129 */ "gog_dbglevel_default ::=",
 /* 130 */ "defaults_decl ::= DEFAULT_KW OPEN_BRACE pdu_defaults gop_defaults gog_defaults CLOSE_BRACE SEMICOLON",
 /* 131 */ "pdu_defaults ::= PDU_KW OPEN_BRACE pdu_last_extracted_default pdu_drop_unassigned_default pdu_discard_default CLOSE_BRACE SEMICOLON",
 /* 132 */ "pdu_defaults ::=",
 /* 133 */ "pdu_last_extracted_default ::=",
 /* 134 */ "pdu_drop_unassigned_default ::=",
 /* 135 */ "pdu_discard_default ::=",
 /* 136 */ "gop_defaults ::= GOP_KW OPEN_BRACE gop_expiration_default gop_idle_timeout_default gop_lifetime_default gop_drop_unassigned_default gop_tree_mode_default gop_show_times_default CLOSE_BRACE SEMICOLON",
 /* 137 */ "gop_defaults ::=",
 /* 138 */ "gop_expiration_default ::=",
 /* 139 */ "gop_idle_timeout_default ::=",
 /* 140 */ "gop_lifetime_default ::=",
 /* 141 */ "gop_drop_unassigned_default ::=",
 /* 142 */ "gop_tree_mode_default ::=",
 /* 143 */ "gop_show_times_default ::=",
 /* 144 */ "gog_defaults ::= GOG_KW OPEN_BRACE gog_expiration_default gop_tree_mode_default gog_goptree_default gog_show_times_default CLOSE_BRACE SEMICOLON",
 /* 145 */ "gog_defaults ::=",
 /* 146 */ "gog_expiration_default ::=",
 /* 147 */ "gog_goptree_default ::=",
 /* 148 */ "gog_show_times_default ::=",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.  Return the number
** of errors.  Return 0 on success.
*/
static int yyGrowStack(yyParser *p){
  int newSize;
  int idx;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  idx = p->yytos ? (int)(p->yytos - p->yystack) : 0;
  if( p->yystack==&p->yystk0 ){
    pNew = malloc(newSize*sizeof(pNew[0]));
    if( pNew ) pNew[0] = p->yystk0;
  }else{
    pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  }
  if( pNew ){
    p->yystack = pNew;
    p->yytos = &p->yystack[idx];
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows from %d to %d entries.\n",
              yyTracePrompt, p->yystksz, newSize);
    }
#endif
    p->yystksz = newSize;
  }
  return pNew==0;
}
#endif

/* Datatype of the argument to the memory allocated passed as the
** second argument to MateParserAlloc() below.  This can be changed by
** putting an appropriate #define in the %include section of the input
** grammar.
*/
#ifndef YYMALLOCARGTYPE
# define YYMALLOCARGTYPE size_t
#endif

/* Initialize a new parser that has already been allocated.
*/
static void MateParserInit(void *yypRawParser MateParserCTX_PDECL){
  yyParser *yypParser = (yyParser*)yypRawParser;
  MateParserCTX_STORE
#ifdef YYTRACKMAXSTACKDEPTH
  yypParser->yyhwm = 0;
#endif
#if YYSTACKDEPTH<=0
  yypParser->yytos = NULL;
  yypParser->yystack = NULL;
  yypParser->yystksz = 0;
  if( yyGrowStack(yypParser) ){
    yypParser->yystack = &yypParser->yystk0;
    yypParser->yystksz = 1;
  }
#endif
#ifndef YYNOERRORRECOVERY
  yypParser->yyerrcnt = -1;
#endif
  yypParser->yytos = yypParser->yystack;
  yypParser->yystack[0].stateno = 0;
  yypParser->yystack[0].major = 0;
#if YYSTACKDEPTH>0
  yypParser->yystackEnd = &yypParser->yystack[YYSTACKDEPTH-1];
#endif
}

#ifndef MateParser_ENGINEALWAYSONSTACK
/*
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to MateParser and MateParserFree.
*/
void *MateParserAlloc(void *(*mallocProc)(YYMALLOCARGTYPE) MateParserCTX_PDECL){
  yyParser *yypParser;
  yypParser = (yyParser*)(*mallocProc)( (YYMALLOCARGTYPE)sizeof(yyParser) );
  if( yypParser ){
    MateParserCTX_STORE
    MateParserInit(yypParser MateParserCTX_PARAM);
  }
  return (void*)yypParser;
}
#endif /* MateParser_ENGINEALWAYSONSTACK */


/* The following function deletes the "minor type" or semantic value
** associated with a symbol.  The symbol can be either a terminal
** or nonterminal. "yymajor" is the symbol code, and "yypminor" is
** a pointer to the value to be deleted.  The code used to do the
** deletions is derived from the %destructor and/or %token_destructor
** directives of the input grammar.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  MateParserARG_FETCH
  MateParserCTX_FETCH
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are *not* used
    ** inside the C code.
    */
/********* Begin destructor definitions ***************************************/
      /* TERMINAL Destructor */
    case 1: /* DONE_KW */
    case 2: /* SEMICOLON */
    case 3: /* DEBUG_KW */
    case 4: /* OPEN_BRACE */
    case 5: /* CLOSE_BRACE */
    case 6: /* FILENAME_KW */
    case 7: /* QUOTED */
    case 8: /* NAME */
    case 9: /* LEVEL_KW */
    case 10: /* INTEGER */
    case 11: /* PDU_KW */
    case 12: /* GOP_KW */
    case 13: /* GOG_KW */
    case 14: /* DEFAULT_KW */
    case 15: /* LAST_EXTRACTED_KW */
    case 16: /* DROP_UNASSIGNED_KW */
    case 17: /* DISCARD_PDU_DATA_KW */
    case 18: /* EXPIRATION_KW */
    case 19: /* IDLE_TIMEOUT_KW */
    case 20: /* LIFETIME_KW */
    case 21: /* SHOW_TREE_KW */
    case 22: /* SHOW_TIMES_KW */
    case 23: /* GOP_TREE_KW */
    case 24: /* TRANSFORM_KW */
    case 25: /* MATCH_KW */
    case 26: /* STRICT_KW */
    case 27: /* EVERY_KW */
    case 28: /* LOOSE_KW */
    case 29: /* REPLACE_KW */
    case 30: /* INSERT_KW */
    case 31: /* PROTO_KW */
    case 32: /* TRANSPORT_KW */
    case 33: /* PAYLOAD_KW */
    case 34: /* CRITERIA_KW */
    case 35: /* ACCEPT_KW */
    case 36: /* REJECT_KW */
    case 37: /* EXTRACT_KW */
    case 38: /* FROM_KW */
    case 39: /* LAST_PDU_KW */
    case 40: /* SLASH */
    case 41: /* ON_KW */
    case 42: /* START_KW */
    case 43: /* STOP_KW */
    case 44: /* NO_TREE_KW */
    case 45: /* PDU_TREE_KW */
    case 46: /* FRAME_TREE_KW */
    case 47: /* BASIC_TREE_KW */
    case 48: /* TRUE_KW */
    case 49: /* FALSE_KW */
    case 50: /* FLOATING */
    case 51: /* NULL_TREE_KW */
    case 52: /* FULL_TREE_KW */
    case 53: /* MEMBER_KW */
    case 54: /* EXTRA_KW */
    case 55: /* COMMA */
    case 56: /* OPEN_PARENS */
    case 57: /* CLOSE_PARENS */
    case 58: /* AVP_OPERATOR */
    case 59: /* PIPE */
    case 60: /* DOTED_IP */
    case 61: /* COLONIZED */
{
#line 177 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"

	(void) mc; /* Mark unused, similar to Q_UNUSED */
	g_free((yypminor->yy0));

#line 1103 "./mate_grammar.c"
}
      break;
/********* End destructor definitions *****************************************/
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
*/
static void yy_pop_parser_stack(yyParser *pParser){
  yyStackEntry *yytos;
  assert( pParser->yytos!=0 );
  assert( pParser->yytos > pParser->yystack );
  yytos = pParser->yytos--;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yy_destructor(pParser, yytos->major, &yytos->minor);
}

/*
** Clear all secondary memory allocations from the parser
*/
static void MateParserFinalize(void *p){
  yyParser *pParser = (yyParser*)p;
  while( pParser->yytos>pParser->yystack ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  if( pParser->yystack!=&pParser->yystk0 ) free(pParser->yystack);
#endif
}

#ifndef MateParser_ENGINEALWAYSONSTACK
/*
** Deallocate and destroy a parser.  Destructors are called for
** all stack elements before shutting the parser down.
**
** If the YYPARSEFREENEVERNULL macro exists (for example because it
** is defined in a %include section of the input grammar) then it is
** assumed that the input pointer is never NULL.
*/
void MateParserFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
#ifndef YYPARSEFREENEVERNULL
  if( p==0 ) return;
#endif
  MateParserFinalize(p);
  (*freeProc)(p);
}
#endif /* MateParser_ENGINEALWAYSONSTACK */

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int MateParserStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyhwm;
}
#endif

/* This array of booleans keeps track of the parser statement
** coverage.  The element yycoverage[X][Y] is set when the parser
** is in state X and has a lookahead token Y.  In a well-tested
** systems, every element of this matrix should end up being set.
*/
#if defined(YYCOVERAGE)
static unsigned char yycoverage[YYNSTATE][YYNTOKEN];
#endif

/*
** Write into out a description of every state/lookahead combination that
**
**   (1)  has not been used by the parser, and
**   (2)  is not a syntax error.
**
** Return the number of missed state/lookahead combinations.
*/
#if defined(YYCOVERAGE)
int MateParserCoverage(FILE *out){
  int stateno, iLookAhead, i;
  int nMissed = 0;
  for(stateno=0; stateno<YYNSTATE; stateno++){
    i = yy_shift_ofst[stateno];
    for(iLookAhead=0; iLookAhead<YYNTOKEN; iLookAhead++){
      if( yy_lookahead[i+iLookAhead]!=iLookAhead ) continue;
      if( yycoverage[stateno][iLookAhead]==0 ) nMissed++;
      if( out ){
        fprintf(out,"State %d lookahead %s %s\n", stateno,
                yyTokenName[iLookAhead],
                yycoverage[stateno][iLookAhead] ? "ok" : "missed");
      }
    }
  }
  return nMissed;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
*/
static YYACTIONTYPE yy_find_shift_action(
  YYCODETYPE iLookAhead,    /* The look-ahead token */
  YYACTIONTYPE stateno      /* Current state number */
){
  int i;

  if( stateno>YY_MAX_SHIFT ) return stateno;
  assert( stateno <= YY_SHIFT_COUNT );
#if defined(YYCOVERAGE)
  yycoverage[stateno][iLookAhead] = 1;
#endif
  do{
    i = yy_shift_ofst[stateno];
    assert( i>=0 );
    /* assert( i+YYNTOKEN<=(int)YY_NLOOKAHEAD ); */
    assert( iLookAhead!=YYNOCODE );
    assert( iLookAhead < YYNTOKEN );
    i += iLookAhead;
    if( i>=YY_NLOOKAHEAD || yy_lookahead[i]!=iLookAhead ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
             && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        assert( yyFallback[iFallback]==0 ); /* Fallback loop must terminate */
        iLookAhead = iFallback;
        continue;
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if(
#if YY_SHIFT_MIN+YYWILDCARD<0
          j>=0 &&
#endif
#if YY_SHIFT_MAX+YYWILDCARD>=YY_ACTTAB_COUNT
          j<YY_ACTTAB_COUNT &&
#endif
          j<(int)(sizeof(yy_lookahead)/sizeof(yy_lookahead[0])) &&
          yy_lookahead[j]==YYWILDCARD && iLookAhead>0
        ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead],
               yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
      return yy_default[stateno];
    }else{
      return yy_action[i];
    }
  }while(1);
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
*/
static YYACTIONTYPE yy_find_reduce_action(
  YYACTIONTYPE stateno,     /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_COUNT ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_COUNT );
#endif
  i = yy_reduce_ofst[stateno];
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_ACTTAB_COUNT );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser){
   MateParserARG_FETCH
   MateParserCTX_FETCH
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
/******** Begin %stack_overflow code ******************************************/
/******** End %stack_overflow code ********************************************/
   MateParserARG_STORE /* Suppress warning about unused %extra_argument var */
   MateParserCTX_STORE
}

/*
** Print tracing information for a SHIFT action
*/
#ifndef NDEBUG
static void yyTraceShift(yyParser *yypParser, int yyNewState, const char *zTag){
  if( yyTraceFILE ){
    if( yyNewState<YYNSTATE ){
      fprintf(yyTraceFILE,"%s%s '%s', go to state %d\n",
         yyTracePrompt, zTag, yyTokenName[yypParser->yytos->major],
         yyNewState);
    }else{
      fprintf(yyTraceFILE,"%s%s '%s', pending reduce %d\n",
         yyTracePrompt, zTag, yyTokenName[yypParser->yytos->major],
         yyNewState - YY_MIN_REDUCE);
    }
  }
}
#else
# define yyTraceShift(X,Y,Z)
#endif

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  YYACTIONTYPE yyNewState,      /* The new state to shift in */
  YYCODETYPE yyMajor,           /* The major token to shift in */
  MateParserTOKENTYPE yyMinor        /* The minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yytos++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
    yypParser->yyhwm++;
    assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack) );
  }
#endif
#if YYSTACKDEPTH>0
  if( yypParser->yytos>yypParser->yystackEnd ){
    yypParser->yytos--;
    yyStackOverflow(yypParser);
    return;
  }
#else
  if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz] ){
    if( yyGrowStack(yypParser) ){
      yypParser->yytos--;
      yyStackOverflow(yypParser);
      return;
    }
  }
#endif
  if( yyNewState > YY_MAX_SHIFT ){
    yyNewState += YY_MIN_REDUCE - YY_MIN_SHIFTREDUCE;
  }
  yytos = yypParser->yytos;
  yytos->stateno = yyNewState;
  yytos->major = yyMajor;
  yytos->minor.yy0 = yyMinor;
  yyTraceShift(yypParser, yyNewState, "Shift");
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;       /* Symbol on the left-hand side of the rule */
  signed char nrhs;     /* Negative of the number of RHS symbols in the rule */
} yyRuleInfo[] = {
  {  117,   -3 }, /* (0) dbgfile_default ::= FILENAME_KW QUOTED SEMICOLON */
  {  117,   -3 }, /* (1) dbgfile_default ::= FILENAME_KW NAME SEMICOLON */
  {  118,   -3 }, /* (2) dbglevel_default ::= LEVEL_KW INTEGER SEMICOLON */
  {  119,   -4 }, /* (3) pdu_dbglevel_default ::= PDU_KW LEVEL_KW INTEGER SEMICOLON */
  {  120,   -4 }, /* (4) gop_dbglevel_default ::= GOP_KW LEVEL_KW INTEGER SEMICOLON */
  {  121,   -4 }, /* (5) gog_dbglevel_default ::= GOG_KW LEVEL_KW INTEGER SEMICOLON */
  {  125,   -3 }, /* (6) pdu_last_extracted_default ::= LAST_EXTRACTED_KW true_false SEMICOLON */
  {  126,   -3 }, /* (7) pdu_drop_unassigned_default ::= DROP_UNASSIGNED_KW true_false SEMICOLON */
  {  127,   -3 }, /* (8) pdu_discard_default ::= DISCARD_PDU_DATA_KW true_false SEMICOLON */
  {  128,   -3 }, /* (9) gop_expiration_default ::= EXPIRATION_KW time_value SEMICOLON */
  {  129,   -3 }, /* (10) gop_idle_timeout_default ::= IDLE_TIMEOUT_KW time_value SEMICOLON */
  {  130,   -3 }, /* (11) gop_lifetime_default ::= LIFETIME_KW time_value SEMICOLON */
  {  131,   -3 }, /* (12) gop_drop_unassigned_default ::= DROP_UNASSIGNED_KW true_false SEMICOLON */
  {  132,   -3 }, /* (13) gop_tree_mode_default ::= SHOW_TREE_KW gop_tree_mode SEMICOLON */
  {  133,   -3 }, /* (14) gop_show_times_default ::= SHOW_TIMES_KW true_false SEMICOLON */
  {  134,   -3 }, /* (15) gog_expiration_default ::= EXPIRATION_KW time_value SEMICOLON */
  {  135,   -3 }, /* (16) gog_goptree_default ::= GOP_TREE_KW gop_tree_type SEMICOLON */
  {  136,   -3 }, /* (17) gog_show_times_default ::= SHOW_TIMES_KW true_false SEMICOLON */
  {   62,   -4 }, /* (18) transform_decl ::= TRANSFORM_KW NAME transform_body SEMICOLON */
  {   63,   -3 }, /* (19) transform_body ::= OPEN_BRACE transform_statements CLOSE_BRACE */
  {   64,   -2 }, /* (20) transform_statements ::= transform_statements transform_statement */
  {   64,   -1 }, /* (21) transform_statements ::= transform_statement */
  {   65,   -3 }, /* (22) transform_statement ::= transform_match transform_action SEMICOLON */
  {   66,   -3 }, /* (23) transform_match ::= MATCH_KW match_mode avpl */
  {   66,    0 }, /* (24) transform_match ::= */
  {   67,    0 }, /* (25) transform_action ::= */
  {   67,   -2 }, /* (26) transform_action ::= action_mode avpl */
  {   68,    0 }, /* (27) match_mode ::= */
  {   68,   -1 }, /* (28) match_mode ::= STRICT_KW */
  {   68,   -1 }, /* (29) match_mode ::= EVERY_KW */
  {   68,   -1 }, /* (30) match_mode ::= LOOSE_KW */
  {   69,   -1 }, /* (31) action_mode ::= REPLACE_KW */
  {   69,   -1 }, /* (32) action_mode ::= INSERT_KW */
  {   69,    0 }, /* (33) action_mode ::= */
  {  112,  -16 }, /* (34) pdu_decl ::= PDU_KW NAME PROTO_KW field TRANSPORT_KW proto_stack OPEN_BRACE payload_statement extraction_statements transform_list_statement criteria_statement pdu_drop_unassigned_statement discard_pdu_data_statement last_extracted_statement CLOSE_BRACE SEMICOLON */
  {  100,    0 }, /* (35) payload_statement ::= */
  {  100,   -3 }, /* (36) payload_statement ::= PAYLOAD_KW proto_stack SEMICOLON */
  {   75,    0 }, /* (37) criteria_statement ::= */
  {   75,   -5 }, /* (38) criteria_statement ::= CRITERIA_KW accept_mode match_mode avpl SEMICOLON */
  {   76,    0 }, /* (39) accept_mode ::= */
  {   76,   -1 }, /* (40) accept_mode ::= ACCEPT_KW */
  {   76,   -1 }, /* (41) accept_mode ::= REJECT_KW */
  {   81,   -2 }, /* (42) extraction_statements ::= extraction_statements extraction_statement */
  {   81,   -1 }, /* (43) extraction_statements ::= extraction_statement */
  {   80,   -5 }, /* (44) extraction_statement ::= EXTRACT_KW NAME FROM_KW field SEMICOLON */
  {   77,   -3 }, /* (45) pdu_drop_unassigned_statement ::= DROP_UNASSIGNED_KW true_false SEMICOLON */
  {   77,    0 }, /* (46) pdu_drop_unassigned_statement ::= */
  {   78,   -3 }, /* (47) discard_pdu_data_statement ::= DISCARD_PDU_DATA_KW true_false SEMICOLON */
  {   78,    0 }, /* (48) discard_pdu_data_statement ::= */
  {   79,   -3 }, /* (49) last_extracted_statement ::= LAST_PDU_KW true_false SEMICOLON */
  {   79,    0 }, /* (50) last_extracted_statement ::= */
  {  101,   -3 }, /* (51) proto_stack ::= proto_stack SLASH field */
  {  101,   -1 }, /* (52) proto_stack ::= field */
  {  102,   -1 }, /* (53) field ::= NAME */
  {  113,  -19 }, /* (54) gop_decl ::= GOP_KW NAME ON_KW pdu_name MATCH_KW avpl OPEN_BRACE gop_start_statement gop_stop_statement extra_statement transform_list_statement gop_expiration_statement idle_timeout_statement lifetime_statement gop_drop_unassigned_statement show_goptree_statement show_times_statement CLOSE_BRACE SEMICOLON */
  {   86,   -3 }, /* (55) gop_drop_unassigned_statement ::= DROP_UNASSIGNED_KW true_false SEMICOLON */
  {   86,    0 }, /* (56) gop_drop_unassigned_statement ::= */
  {   83,   -3 }, /* (57) gop_start_statement ::= START_KW avpl SEMICOLON */
  {   83,    0 }, /* (58) gop_start_statement ::= */
  {   84,   -3 }, /* (59) gop_stop_statement ::= STOP_KW avpl SEMICOLON */
  {   84,    0 }, /* (60) gop_stop_statement ::= */
  {   87,   -3 }, /* (61) show_goptree_statement ::= SHOW_TREE_KW gop_tree_mode SEMICOLON */
  {   87,    0 }, /* (62) show_goptree_statement ::= */
  {   88,   -3 }, /* (63) show_times_statement ::= SHOW_TIMES_KW true_false SEMICOLON */
  {   88,    0 }, /* (64) show_times_statement ::= */
  {   89,   -3 }, /* (65) gop_expiration_statement ::= EXPIRATION_KW time_value SEMICOLON */
  {   89,    0 }, /* (66) gop_expiration_statement ::= */
  {   90,   -3 }, /* (67) idle_timeout_statement ::= IDLE_TIMEOUT_KW time_value SEMICOLON */
  {   90,    0 }, /* (68) idle_timeout_statement ::= */
  {   91,   -3 }, /* (69) lifetime_statement ::= LIFETIME_KW time_value SEMICOLON */
  {   91,    0 }, /* (70) lifetime_statement ::= */
  {   73,   -1 }, /* (71) gop_tree_mode ::= NO_TREE_KW */
  {   73,   -1 }, /* (72) gop_tree_mode ::= PDU_TREE_KW */
  {   73,   -1 }, /* (73) gop_tree_mode ::= FRAME_TREE_KW */
  {   73,   -1 }, /* (74) gop_tree_mode ::= BASIC_TREE_KW */
  {   74,   -1 }, /* (75) true_false ::= TRUE_KW */
  {   74,   -1 }, /* (76) true_false ::= FALSE_KW */
  {   72,   -1 }, /* (77) pdu_name ::= NAME */
  {   71,   -1 }, /* (78) time_value ::= FLOATING */
  {   71,   -1 }, /* (79) time_value ::= INTEGER */
  {  114,  -11 }, /* (80) gog_decl ::= GOG_KW NAME OPEN_BRACE gog_key_statements extra_statement transform_list_statement gog_expiration_statement gog_goptree_statement show_times_statement CLOSE_BRACE SEMICOLON */
  {   94,   -3 }, /* (81) gog_goptree_statement ::= GOP_TREE_KW gop_tree_type SEMICOLON */
  {   94,    0 }, /* (82) gog_goptree_statement ::= */
  {   93,   -3 }, /* (83) gog_expiration_statement ::= EXPIRATION_KW time_value SEMICOLON */
  {   93,    0 }, /* (84) gog_expiration_statement ::= */
  {   99,   -1 }, /* (85) gop_tree_type ::= NULL_TREE_KW */
  {   99,   -1 }, /* (86) gop_tree_type ::= FULL_TREE_KW */
  {   99,   -1 }, /* (87) gop_tree_type ::= BASIC_TREE_KW */
  {   95,   -2 }, /* (88) gog_key_statements ::= gog_key_statements gog_key_statement */
  {   95,   -1 }, /* (89) gog_key_statements ::= gog_key_statement */
  {   96,   -4 }, /* (90) gog_key_statement ::= MEMBER_KW gop_name avpl SEMICOLON */
  {   70,   -1 }, /* (91) gop_name ::= NAME */
  {   85,   -3 }, /* (92) extra_statement ::= EXTRA_KW avpl SEMICOLON */
  {   85,    0 }, /* (93) extra_statement ::= */
  {   97,   -3 }, /* (94) transform_list_statement ::= TRANSFORM_KW transform_list SEMICOLON */
  {   97,    0 }, /* (95) transform_list_statement ::= */
  {  103,   -3 }, /* (96) transform_list ::= transform_list COMMA transform */
  {  103,   -1 }, /* (97) transform_list ::= transform */
  {   98,   -1 }, /* (98) transform ::= NAME */
  {  104,   -3 }, /* (99) avpl ::= OPEN_PARENS avps CLOSE_PARENS */
  {  104,   -2 }, /* (100) avpl ::= OPEN_PARENS CLOSE_PARENS */
  {  105,   -3 }, /* (101) avps ::= avps COMMA avp */
  {  105,   -1 }, /* (102) avps ::= avp */
  {  106,   -3 }, /* (103) avp ::= NAME AVP_OPERATOR value */
  {  106,   -1 }, /* (104) avp ::= NAME */
  {  106,   -4 }, /* (105) avp ::= NAME OPEN_BRACE avp_oneoff CLOSE_BRACE */
  {  108,   -3 }, /* (106) avp_oneoff ::= avp_oneoff PIPE value */
  {  108,   -1 }, /* (107) avp_oneoff ::= value */
  {  107,   -1 }, /* (108) value ::= QUOTED */
  {  107,   -1 }, /* (109) value ::= NAME */
  {  107,   -1 }, /* (110) value ::= FLOATING */
  {  107,   -1 }, /* (111) value ::= INTEGER */
  {  107,   -1 }, /* (112) value ::= DOTED_IP */
  {  107,   -1 }, /* (113) value ::= COLONIZED */
  {  109,   -1 }, /* (114) mate_config ::= decls */
  {  110,   -2 }, /* (115) decls ::= decls decl */
  {  110,    0 }, /* (116) decls ::= */
  {  111,   -1 }, /* (117) decl ::= pdu_decl */
  {  111,   -1 }, /* (118) decl ::= gop_decl */
  {  111,   -1 }, /* (119) decl ::= gog_decl */
  {  111,   -1 }, /* (120) decl ::= transform_decl */
  {  111,   -1 }, /* (121) decl ::= defaults_decl */
  {  111,   -1 }, /* (122) decl ::= debug_decl */
  {  111,   -2 }, /* (123) decl ::= DONE_KW SEMICOLON */
  {  116,   -9 }, /* (124) debug_decl ::= DEBUG_KW OPEN_BRACE dbgfile_default dbglevel_default pdu_dbglevel_default gop_dbglevel_default gog_dbglevel_default CLOSE_BRACE SEMICOLON */
  {  117,    0 }, /* (125) dbgfile_default ::= */
  {  118,    0 }, /* (126) dbglevel_default ::= */
  {  119,    0 }, /* (127) pdu_dbglevel_default ::= */
  {  120,    0 }, /* (128) gop_dbglevel_default ::= */
  {  121,    0 }, /* (129) gog_dbglevel_default ::= */
  {  115,   -7 }, /* (130) defaults_decl ::= DEFAULT_KW OPEN_BRACE pdu_defaults gop_defaults gog_defaults CLOSE_BRACE SEMICOLON */
  {  122,   -7 }, /* (131) pdu_defaults ::= PDU_KW OPEN_BRACE pdu_last_extracted_default pdu_drop_unassigned_default pdu_discard_default CLOSE_BRACE SEMICOLON */
  {  122,    0 }, /* (132) pdu_defaults ::= */
  {  125,    0 }, /* (133) pdu_last_extracted_default ::= */
  {  126,    0 }, /* (134) pdu_drop_unassigned_default ::= */
  {  127,    0 }, /* (135) pdu_discard_default ::= */
  {  123,  -10 }, /* (136) gop_defaults ::= GOP_KW OPEN_BRACE gop_expiration_default gop_idle_timeout_default gop_lifetime_default gop_drop_unassigned_default gop_tree_mode_default gop_show_times_default CLOSE_BRACE SEMICOLON */
  {  123,    0 }, /* (137) gop_defaults ::= */
  {  128,    0 }, /* (138) gop_expiration_default ::= */
  {  129,    0 }, /* (139) gop_idle_timeout_default ::= */
  {  130,    0 }, /* (140) gop_lifetime_default ::= */
  {  131,    0 }, /* (141) gop_drop_unassigned_default ::= */
  {  132,    0 }, /* (142) gop_tree_mode_default ::= */
  {  133,    0 }, /* (143) gop_show_times_default ::= */
  {  124,   -8 }, /* (144) gog_defaults ::= GOG_KW OPEN_BRACE gog_expiration_default gop_tree_mode_default gog_goptree_default gog_show_times_default CLOSE_BRACE SEMICOLON */
  {  124,    0 }, /* (145) gog_defaults ::= */
  {  134,    0 }, /* (146) gog_expiration_default ::= */
  {  135,    0 }, /* (147) gog_goptree_default ::= */
  {  136,    0 }, /* (148) gog_show_times_default ::= */
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
**
** The yyLookahead and yyLookaheadToken parameters provide reduce actions
** access to the lookahead token (if any).  The yyLookahead will be YYNOCODE
** if the lookahead token has already been consumed.  As this procedure is
** only called from one place, optimizing compilers will in-line it, which
** means that the extra parameters have no performance impact.
*/
static YYACTIONTYPE yy_reduce(
  yyParser *yypParser,         /* The parser */
  unsigned int yyruleno,       /* Number of the rule by which to reduce */
  int yyLookahead,             /* Lookahead token, or YYNOCODE if none */
  MateParserTOKENTYPE yyLookaheadToken  /* Value of the lookahead token */
  MateParserCTX_PDECL                   /* %extra_context */
){
  int yygoto;                     /* The next state */
  YYACTIONTYPE yyact;             /* The next action */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  MateParserARG_FETCH
  (void)yyLookahead;
  (void)yyLookaheadToken;
  yymsp = yypParser->yytos;
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    yysize = yyRuleInfo[yyruleno].nrhs;
    if( yysize ){
      fprintf(yyTraceFILE, "%sReduce %d [%s], go to state %d.\n",
        yyTracePrompt,
        yyruleno, yyRuleName[yyruleno], yymsp[yysize].stateno);
    }else{
      fprintf(yyTraceFILE, "%sReduce %d [%s].\n",
        yyTracePrompt, yyruleno, yyRuleName[yyruleno]);
    }
  }
#endif /* NDEBUG */

  /* Check that the stack is large enough to grow by a single entry
  ** if the RHS of the rule is empty.  This ensures that there is room
  ** enough on the stack to push the LHS value */
  if( yyRuleInfo[yyruleno].nrhs==0 ){
#ifdef YYTRACKMAXSTACKDEPTH
    if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
      yypParser->yyhwm++;
      assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack));
    }
#endif
#if YYSTACKDEPTH>0
    if( yypParser->yytos>=yypParser->yystackEnd ){
      yyStackOverflow(yypParser);
      /* The call to yyStackOverflow() above pops the stack until it is
      ** empty, causing the main parser loop to exit.  So the return value
      ** is never used and does not matter. */
      return 0;
    }
#else
    if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz-1] ){
      if( yyGrowStack(yypParser) ){
        yyStackOverflow(yypParser);
        /* The call to yyStackOverflow() above pops the stack until it is
        ** empty, causing the main parser loop to exit.  So the return value
        ** is never used and does not matter. */
        return 0;
      }
      yymsp = yypParser->yytos;
    }
#endif
  }

  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
/********** Begin reduce actions **********************************************/
        YYMINORTYPE yylhsminor;
      case 0: /* dbgfile_default ::= FILENAME_KW QUOTED SEMICOLON */
{  yy_destructor(yypParser,6,&yymsp[-2].minor);
#line 266 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ mc->dbg_facility = ws_fopen(yymsp[-1].minor.yy0,"w"); if (mc->dbg_facility == NULL) report_open_failure(yymsp[-1].minor.yy0,errno,TRUE); }
#line 1639 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 1: /* dbgfile_default ::= FILENAME_KW NAME SEMICOLON */
{  yy_destructor(yypParser,6,&yymsp[-2].minor);
#line 267 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ mc->dbg_facility = ws_fopen(yymsp[-1].minor.yy0,"w"); if (mc->dbg_facility == NULL) report_open_failure(yymsp[-1].minor.yy0,errno,TRUE);  }
#line 1647 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 2: /* dbglevel_default ::= LEVEL_KW INTEGER SEMICOLON */
{  yy_destructor(yypParser,9,&yymsp[-2].minor);
#line 270 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ mc->dbg_lvl = (int) strtol(yymsp[-1].minor.yy0,NULL,10); }
#line 1655 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 3: /* pdu_dbglevel_default ::= PDU_KW LEVEL_KW INTEGER SEMICOLON */
{  yy_destructor(yypParser,11,&yymsp[-3].minor);
#line 273 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ mc->dbg_pdu_lvl = (int) strtol(yymsp[-1].minor.yy0,NULL,10); }
#line 1663 "./mate_grammar.c"
  yy_destructor(yypParser,9,&yymsp[-2].minor);
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 4: /* gop_dbglevel_default ::= GOP_KW LEVEL_KW INTEGER SEMICOLON */
{  yy_destructor(yypParser,12,&yymsp[-3].minor);
#line 276 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ mc->dbg_gop_lvl = (int) strtol(yymsp[-1].minor.yy0,NULL,10); }
#line 1672 "./mate_grammar.c"
  yy_destructor(yypParser,9,&yymsp[-2].minor);
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 5: /* gog_dbglevel_default ::= GOG_KW LEVEL_KW INTEGER SEMICOLON */
{  yy_destructor(yypParser,13,&yymsp[-3].minor);
#line 279 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ mc->dbg_gog_lvl = (int) strtol(yymsp[-1].minor.yy0,NULL,10); }
#line 1681 "./mate_grammar.c"
  yy_destructor(yypParser,9,&yymsp[-2].minor);
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 6: /* pdu_last_extracted_default ::= LAST_EXTRACTED_KW true_false SEMICOLON */
{  yy_destructor(yypParser,15,&yymsp[-2].minor);
#line 291 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ mc->defaults.pdu.last_extracted = yymsp[-1].minor.yy182; }
#line 1690 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 7: /* pdu_drop_unassigned_default ::= DROP_UNASSIGNED_KW true_false SEMICOLON */
{  yy_destructor(yypParser,16,&yymsp[-2].minor);
#line 294 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ mc->defaults.pdu.drop_unassigned = yymsp[-1].minor.yy182; }
#line 1698 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 8: /* pdu_discard_default ::= DISCARD_PDU_DATA_KW true_false SEMICOLON */
{  yy_destructor(yypParser,17,&yymsp[-2].minor);
#line 297 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ mc->defaults.pdu.discard = yymsp[-1].minor.yy182; }
#line 1706 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 9: /* gop_expiration_default ::= EXPIRATION_KW time_value SEMICOLON */
      case 15: /* gog_expiration_default ::= EXPIRATION_KW time_value SEMICOLON */ yytestcase(yyruleno==15);
{  yy_destructor(yypParser,18,&yymsp[-2].minor);
#line 303 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ mc->defaults.gop.expiration = yymsp[-1].minor.yy255; }
#line 1715 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 10: /* gop_idle_timeout_default ::= IDLE_TIMEOUT_KW time_value SEMICOLON */
{  yy_destructor(yypParser,19,&yymsp[-2].minor);
#line 306 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ mc->defaults.gop.idle_timeout = yymsp[-1].minor.yy255; }
#line 1723 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 11: /* gop_lifetime_default ::= LIFETIME_KW time_value SEMICOLON */
{  yy_destructor(yypParser,20,&yymsp[-2].minor);
#line 309 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ mc->defaults.gop.lifetime = yymsp[-1].minor.yy255; }
#line 1731 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 12: /* gop_drop_unassigned_default ::= DROP_UNASSIGNED_KW true_false SEMICOLON */
{  yy_destructor(yypParser,16,&yymsp[-2].minor);
#line 312 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ mc->defaults.gop.drop_unassigned = yymsp[-1].minor.yy182; }
#line 1739 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 13: /* gop_tree_mode_default ::= SHOW_TREE_KW gop_tree_mode SEMICOLON */
{  yy_destructor(yypParser,21,&yymsp[-2].minor);
#line 315 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ mc->defaults.gop.pdu_tree_mode = (gop_pdu_tree_t)yymsp[-1].minor.yy256; }
#line 1747 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 14: /* gop_show_times_default ::= SHOW_TIMES_KW true_false SEMICOLON */
{  yy_destructor(yypParser,22,&yymsp[-2].minor);
#line 318 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ mc->defaults.gop.show_times = yymsp[-1].minor.yy182; }
#line 1755 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 16: /* gog_goptree_default ::= GOP_TREE_KW gop_tree_type SEMICOLON */
{  yy_destructor(yypParser,23,&yymsp[-2].minor);
#line 327 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ mc->defaults.gog.gop_tree_mode = yymsp[-1].minor.yy256; }
#line 1763 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 17: /* gog_show_times_default ::= SHOW_TIMES_KW true_false SEMICOLON */
{  yy_destructor(yypParser,22,&yymsp[-2].minor);
#line 330 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ mc->defaults.gog.show_times = yymsp[-1].minor.yy182; }
#line 1771 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 18: /* transform_decl ::= TRANSFORM_KW NAME transform_body SEMICOLON */
{  yy_destructor(yypParser,24,&yymsp[-3].minor);
#line 337 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{
	AVPL_Transf* c;

	if ( g_hash_table_lookup(mc->transfs,yymsp[-2].minor.yy0) ) {
		configuration_error(mc,"yymsp[-3].minor.yy11 transformation called '%s' exists already",yymsp[-2].minor.yy0);
	}

	for ( c = yymsp[-1].minor.yy11; c; c = c->next )
		c->name = g_strdup(yymsp[-2].minor.yy0);

	g_hash_table_insert(mc->transfs,yymsp[-1].minor.yy11->name,yymsp[-1].minor.yy11);

	yymsp[-3].minor.yy11 = NULL;
}
#line 1792 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 19: /* transform_body ::= OPEN_BRACE transform_statements CLOSE_BRACE */
{  yy_destructor(yypParser,4,&yymsp[-2].minor);
#line 352 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[-2].minor.yy11 = yymsp[-1].minor.yy11; }
#line 1800 "./mate_grammar.c"
  yy_destructor(yypParser,5,&yymsp[0].minor);
}
        break;
      case 20: /* transform_statements ::= transform_statements transform_statement */
#line 354 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{
	AVPL_Transf* c;

	for ( c = yymsp[-1].minor.yy11; c->next; c = c->next ) ;
	c->next = yymsp[0].minor.yy11;
	yylhsminor.yy11 = yymsp[-1].minor.yy11;
}
#line 1813 "./mate_grammar.c"
  yymsp[-1].minor.yy11 = yylhsminor.yy11;
        break;
      case 21: /* transform_statements ::= transform_statement */
#line 362 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yylhsminor.yy11 = yymsp[0].minor.yy11; }
#line 1819 "./mate_grammar.c"
  yymsp[0].minor.yy11 = yylhsminor.yy11;
        break;
      case 22: /* transform_statement ::= transform_match transform_action SEMICOLON */
#line 364 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{
	yylhsminor.yy11 = new_transform_elem(yymsp[-2].minor.yy146->avpl,yymsp[-1].minor.yy85->avpl,yymsp[-2].minor.yy146->match_mode,yymsp[-1].minor.yy85->replace_mode);
}
#line 1827 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
  yymsp[-2].minor.yy11 = yylhsminor.yy11;
        break;
      case 23: /* transform_match ::= MATCH_KW match_mode avpl */
{  yy_destructor(yypParser,25,&yymsp[-2].minor);
#line 368 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{
	yymsp[-2].minor.yy146 = (transf_match_t *)g_malloc(sizeof(transf_match_t));
	yymsp[-2].minor.yy146->match_mode = yymsp[-1].minor.yy274;
	yymsp[-2].minor.yy146->avpl = yymsp[0].minor.yy70;
}
#line 1839 "./mate_grammar.c"
}
        break;
      case 24: /* transform_match ::= */
#line 374 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{
	yymsp[1].minor.yy146 = (transf_match_t *)g_malloc(sizeof(transf_match_t));
	yymsp[1].minor.yy146->match_mode = AVPL_STRICT;
	yymsp[1].minor.yy146->avpl = new_avpl("");

}
#line 1850 "./mate_grammar.c"
        break;
      case 25: /* transform_action ::= */
#line 381 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{
	yymsp[1].minor.yy85 = (transf_action_t *)g_malloc(sizeof(transf_action_t));
	yymsp[1].minor.yy85->replace_mode = AVPL_INSERT;
	yymsp[1].minor.yy85->avpl = new_avpl("");
}
#line 1859 "./mate_grammar.c"
        break;
      case 26: /* transform_action ::= action_mode avpl */
#line 386 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{
	yylhsminor.yy85 = (transf_action_t *)g_malloc(sizeof(transf_action_t));
	yylhsminor.yy85->replace_mode = yymsp[-1].minor.yy143;
	yylhsminor.yy85->avpl = yymsp[0].minor.yy70;
}
#line 1868 "./mate_grammar.c"
  yymsp[-1].minor.yy85 = yylhsminor.yy85;
        break;
      case 27: /* match_mode ::= */
#line 392 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[1].minor.yy274 = AVPL_STRICT; }
#line 1874 "./mate_grammar.c"
        break;
      case 28: /* match_mode ::= STRICT_KW */
{  yy_destructor(yypParser,26,&yymsp[0].minor);
#line 393 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[0].minor.yy274 = AVPL_STRICT; }
#line 1880 "./mate_grammar.c"
}
        break;
      case 29: /* match_mode ::= EVERY_KW */
{  yy_destructor(yypParser,27,&yymsp[0].minor);
#line 394 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[0].minor.yy274 = AVPL_EVERY; }
#line 1887 "./mate_grammar.c"
}
        break;
      case 30: /* match_mode ::= LOOSE_KW */
{  yy_destructor(yypParser,28,&yymsp[0].minor);
#line 395 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[0].minor.yy274 = AVPL_LOOSE; }
#line 1894 "./mate_grammar.c"
}
        break;
      case 31: /* action_mode ::= REPLACE_KW */
{  yy_destructor(yypParser,29,&yymsp[0].minor);
#line 397 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[0].minor.yy143 = AVPL_REPLACE; }
#line 1901 "./mate_grammar.c"
}
        break;
      case 32: /* action_mode ::= INSERT_KW */
{  yy_destructor(yypParser,30,&yymsp[0].minor);
#line 398 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[0].minor.yy143 = AVPL_INSERT; }
#line 1908 "./mate_grammar.c"
}
        break;
      case 33: /* action_mode ::= */
#line 399 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[1].minor.yy143 = AVPL_INSERT; }
#line 1914 "./mate_grammar.c"
        break;
      case 34: /* pdu_decl ::= PDU_KW NAME PROTO_KW field TRANSPORT_KW proto_stack OPEN_BRACE payload_statement extraction_statements transform_list_statement criteria_statement pdu_drop_unassigned_statement discard_pdu_data_statement last_extracted_statement CLOSE_BRACE SEMICOLON */
{  yy_destructor(yypParser,11,&yymsp[-15].minor);
#line 415 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{

	mate_cfg_pdu* cfg  = new_pducfg(mc, yymsp[-14].minor.yy0);
	extraction_t *extraction, *next_extraction;
	GPtrArray* transport_stack = g_ptr_array_new();
	int i;

	if (! cfg ) configuration_error(mc,"could not create Pdu %s.",yymsp[-14].minor.yy0);

	cfg->hfid_proto = yymsp[-12].minor.yy210->id;

	cfg->last_extracted = yymsp[-2].minor.yy182;
	cfg->discard = yymsp[-3].minor.yy182;
	cfg->drop_unassigned = yymsp[-4].minor.yy182;

	/*
	 * Add this protocol to our table of wanted hfids.
	 */
	mc->wanted_hfids = g_array_append_val(mc->wanted_hfids, yymsp[-12].minor.yy210->id);

	/* flip the transport_stack */
	for (i = yymsp[-10].minor.yy147->len - 1; yymsp[-10].minor.yy147->len; i--) {
		g_ptr_array_add(transport_stack,g_ptr_array_remove_index(yymsp[-10].minor.yy147,i));
	}

	g_ptr_array_free(yymsp[-10].minor.yy147, TRUE);

	cfg->transport_ranges = transport_stack;
	cfg->payload_ranges = yymsp[-8].minor.yy147;

	if (yymsp[-5].minor.yy231) {
		cfg->criterium = yymsp[-5].minor.yy231->criterium_avpl;
		cfg->criterium_match_mode = yymsp[-5].minor.yy231->criterium_match_mode;
		cfg->criterium_accept_mode = yymsp[-5].minor.yy231->criterium_accept_mode;
	}

	cfg->transforms = yymsp[-6].minor.yy147;

	for (extraction = yymsp[-7].minor.yy179; extraction; extraction = next_extraction) {
		next_extraction = extraction->next;

		if ( ! add_hfid(mc, extraction->hfi, extraction->as, cfg->hfids_attr) ) {
			configuration_error(mc,"MATE: failed to create extraction rule '%s'",extraction->as);
		}

		g_free(extraction);
	}
}
#line 1967 "./mate_grammar.c"
  yy_destructor(yypParser,31,&yymsp[-13].minor);
  yy_destructor(yypParser,32,&yymsp[-11].minor);
  yy_destructor(yypParser,4,&yymsp[-9].minor);
  yy_destructor(yypParser,5,&yymsp[-1].minor);
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 35: /* payload_statement ::= */
#line 464 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[1].minor.yy147 = NULL; }
#line 1978 "./mate_grammar.c"
        break;
      case 36: /* payload_statement ::= PAYLOAD_KW proto_stack SEMICOLON */
{  yy_destructor(yypParser,33,&yymsp[-2].minor);
#line 465 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[-2].minor.yy147 = yymsp[-1].minor.yy147; }
#line 1984 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 37: /* criteria_statement ::= */
#line 467 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[1].minor.yy231 = NULL; }
#line 1991 "./mate_grammar.c"
        break;
      case 38: /* criteria_statement ::= CRITERIA_KW accept_mode match_mode avpl SEMICOLON */
{  yy_destructor(yypParser,34,&yymsp[-4].minor);
#line 468 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{
	yymsp[-4].minor.yy231 = (pdu_criteria_t *)g_malloc(sizeof(pdu_criteria_t));
	yymsp[-4].minor.yy231->criterium_avpl = yymsp[-1].minor.yy70;
	yymsp[-4].minor.yy231->criterium_match_mode = yymsp[-2].minor.yy274;
	yymsp[-4].minor.yy231->criterium_accept_mode = yymsp[-3].minor.yy148;
}
#line 2002 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 39: /* accept_mode ::= */
#line 475 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[1].minor.yy148 = ACCEPT_MODE; }
#line 2009 "./mate_grammar.c"
        break;
      case 40: /* accept_mode ::= ACCEPT_KW */
{  yy_destructor(yypParser,35,&yymsp[0].minor);
#line 476 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[0].minor.yy148 = ACCEPT_MODE; }
#line 2015 "./mate_grammar.c"
}
        break;
      case 41: /* accept_mode ::= REJECT_KW */
{  yy_destructor(yypParser,36,&yymsp[0].minor);
#line 477 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[0].minor.yy148 = REJECT_MODE; }
#line 2022 "./mate_grammar.c"
}
        break;
      case 42: /* extraction_statements ::= extraction_statements extraction_statement */
#line 479 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yylhsminor.yy179 = yymsp[-1].minor.yy179; yylhsminor.yy179->last = yylhsminor.yy179->last->next = yymsp[0].minor.yy179; }
#line 2028 "./mate_grammar.c"
  yymsp[-1].minor.yy179 = yylhsminor.yy179;
        break;
      case 43: /* extraction_statements ::= extraction_statement */
#line 480 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yylhsminor.yy179 = yymsp[0].minor.yy179; yylhsminor.yy179->last = yylhsminor.yy179; }
#line 2034 "./mate_grammar.c"
  yymsp[0].minor.yy179 = yylhsminor.yy179;
        break;
      case 44: /* extraction_statement ::= EXTRACT_KW NAME FROM_KW field SEMICOLON */
{  yy_destructor(yypParser,37,&yymsp[-4].minor);
#line 482 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{
	yymsp[-4].minor.yy179 = (extraction_t *)g_malloc(sizeof(extraction_t));
	yymsp[-4].minor.yy179->as = yymsp[-3].minor.yy0;
	yymsp[-4].minor.yy179->hfi = yymsp[-1].minor.yy210;
	yymsp[-4].minor.yy179->next = yymsp[-4].minor.yy179->last = NULL;
}
#line 2046 "./mate_grammar.c"
  yy_destructor(yypParser,38,&yymsp[-2].minor);
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 45: /* pdu_drop_unassigned_statement ::= DROP_UNASSIGNED_KW true_false SEMICOLON */
      case 55: /* gop_drop_unassigned_statement ::= DROP_UNASSIGNED_KW true_false SEMICOLON */ yytestcase(yyruleno==55);
{  yy_destructor(yypParser,16,&yymsp[-2].minor);
#line 490 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[-2].minor.yy182 = yymsp[-1].minor.yy182; }
#line 2056 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 46: /* pdu_drop_unassigned_statement ::= */
#line 491 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[1].minor.yy182 =  mc->defaults.pdu.drop_unassigned; }
#line 2063 "./mate_grammar.c"
        break;
      case 47: /* discard_pdu_data_statement ::= DISCARD_PDU_DATA_KW true_false SEMICOLON */
{  yy_destructor(yypParser,17,&yymsp[-2].minor);
#line 493 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[-2].minor.yy182 = yymsp[-1].minor.yy182; }
#line 2069 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 48: /* discard_pdu_data_statement ::= */
#line 494 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[1].minor.yy182 =  mc->defaults.pdu.discard; }
#line 2076 "./mate_grammar.c"
        break;
      case 49: /* last_extracted_statement ::= LAST_PDU_KW true_false SEMICOLON */
{  yy_destructor(yypParser,39,&yymsp[-2].minor);
#line 496 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[-2].minor.yy182 = yymsp[-1].minor.yy182; }
#line 2082 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 50: /* last_extracted_statement ::= */
#line 497 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[1].minor.yy182 = mc->defaults.pdu.last_extracted; }
#line 2089 "./mate_grammar.c"
        break;
      case 51: /* proto_stack ::= proto_stack SLASH field */
#line 499 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{
	int* hfidp = (int *)g_malloc(sizeof(int));

	*hfidp = yymsp[0].minor.yy210->id;
	g_ptr_array_add(yymsp[-2].minor.yy147,hfidp);
	yylhsminor.yy147 = yymsp[-2].minor.yy147;
}
#line 2100 "./mate_grammar.c"
  yy_destructor(yypParser,40,&yymsp[-1].minor);
  yymsp[-2].minor.yy147 = yylhsminor.yy147;
        break;
      case 52: /* proto_stack ::= field */
#line 507 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{
	int* hfidp = (int *)g_malloc(sizeof(int));
	*hfidp = yymsp[0].minor.yy210->id;

	yylhsminor.yy147 = g_ptr_array_new();
	g_ptr_array_add(yylhsminor.yy147,hfidp);
}
#line 2113 "./mate_grammar.c"
  yymsp[0].minor.yy147 = yylhsminor.yy147;
        break;
      case 53: /* field ::= NAME */
#line 515 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{
	yylhsminor.yy210 = proto_registrar_get_byname(yymsp[0].minor.yy0);
}
#line 2121 "./mate_grammar.c"
  yymsp[0].minor.yy210 = yylhsminor.yy210;
        break;
      case 54: /* gop_decl ::= GOP_KW NAME ON_KW pdu_name MATCH_KW avpl OPEN_BRACE gop_start_statement gop_stop_statement extra_statement transform_list_statement gop_expiration_statement idle_timeout_statement lifetime_statement gop_drop_unassigned_statement show_goptree_statement show_times_statement CLOSE_BRACE SEMICOLON */
{  yy_destructor(yypParser,12,&yymsp[-18].minor);
#line 533 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{
		mate_cfg_gop* cfg;

	if (g_hash_table_lookup(mc->gopcfgs,yymsp[-17].minor.yy0)) configuration_error(mc,"yymsp[-18].minor.yy0 Gop Named '%s' exists already.",yymsp[-17].minor.yy0);
	if (g_hash_table_lookup(mc->gops_by_pduname,yymsp[-15].minor.yy212) ) configuration_error(mc,"Gop for Pdu '%s' exists already",yymsp[-15].minor.yy212);

	cfg = new_gopcfg(mc, yymsp[-17].minor.yy0);
	g_hash_table_insert(mc->gops_by_pduname,yymsp[-15].minor.yy212,cfg);
	g_hash_table_insert(mc->gopcfgs,cfg->name,cfg);

	cfg->on_pdu = yymsp[-15].minor.yy212;
	cfg->key = yymsp[-13].minor.yy70;
	cfg->drop_unassigned = yymsp[-4].minor.yy182;
	cfg->show_times = yymsp[-2].minor.yy182;
	cfg->pdu_tree_mode = (gop_pdu_tree_t)yymsp[-3].minor.yy256;
	cfg->expiration = yymsp[-7].minor.yy255;
	cfg->idle_timeout = yymsp[-6].minor.yy255;
	cfg->lifetime = yymsp[-5].minor.yy255;
	cfg->start = yymsp[-11].minor.yy70;
	cfg->stop = yymsp[-10].minor.yy70;
	cfg->transforms = yymsp[-8].minor.yy147;

	merge_avpl(cfg->extra,yymsp[-9].minor.yy70,TRUE);
	delete_avpl(yymsp[-9].minor.yy70,TRUE);
}
#line 2152 "./mate_grammar.c"
  yy_destructor(yypParser,41,&yymsp[-16].minor);
  yy_destructor(yypParser,25,&yymsp[-14].minor);
  yy_destructor(yypParser,4,&yymsp[-12].minor);
  yy_destructor(yypParser,5,&yymsp[-1].minor);
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 56: /* gop_drop_unassigned_statement ::= */
#line 560 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[1].minor.yy182 =  mc->defaults.gop.drop_unassigned; }
#line 2163 "./mate_grammar.c"
        break;
      case 57: /* gop_start_statement ::= START_KW avpl SEMICOLON */
{  yy_destructor(yypParser,42,&yymsp[-2].minor);
#line 562 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[-2].minor.yy70 = yymsp[-1].minor.yy70; }
#line 2169 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 58: /* gop_start_statement ::= */
      case 60: /* gop_stop_statement ::= */ yytestcase(yyruleno==60);
#line 563 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[1].minor.yy70 = NULL; }
#line 2177 "./mate_grammar.c"
        break;
      case 59: /* gop_stop_statement ::= STOP_KW avpl SEMICOLON */
{  yy_destructor(yypParser,43,&yymsp[-2].minor);
#line 565 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[-2].minor.yy70 = yymsp[-1].minor.yy70; }
#line 2183 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 61: /* show_goptree_statement ::= SHOW_TREE_KW gop_tree_mode SEMICOLON */
{  yy_destructor(yypParser,21,&yymsp[-2].minor);
#line 568 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[-2].minor.yy256 = yymsp[-1].minor.yy256; }
#line 2191 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 62: /* show_goptree_statement ::= */
#line 569 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[1].minor.yy256 = (gop_tree_mode_t)mc->defaults.gop.pdu_tree_mode; }
#line 2198 "./mate_grammar.c"
        break;
      case 63: /* show_times_statement ::= SHOW_TIMES_KW true_false SEMICOLON */
{  yy_destructor(yypParser,22,&yymsp[-2].minor);
#line 571 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[-2].minor.yy182 = yymsp[-1].minor.yy182; }
#line 2204 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 64: /* show_times_statement ::= */
#line 572 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[1].minor.yy182 = mc->defaults.gop.show_times; }
#line 2211 "./mate_grammar.c"
        break;
      case 65: /* gop_expiration_statement ::= EXPIRATION_KW time_value SEMICOLON */
      case 83: /* gog_expiration_statement ::= EXPIRATION_KW time_value SEMICOLON */ yytestcase(yyruleno==83);
{  yy_destructor(yypParser,18,&yymsp[-2].minor);
#line 574 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[-2].minor.yy255 = yymsp[-1].minor.yy255; }
#line 2218 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 66: /* gop_expiration_statement ::= */
      case 68: /* idle_timeout_statement ::= */ yytestcase(yyruleno==68);
      case 70: /* lifetime_statement ::= */ yytestcase(yyruleno==70);
#line 575 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[1].minor.yy255 = mc->defaults.gop.lifetime; }
#line 2227 "./mate_grammar.c"
        break;
      case 67: /* idle_timeout_statement ::= IDLE_TIMEOUT_KW time_value SEMICOLON */
{  yy_destructor(yypParser,19,&yymsp[-2].minor);
#line 577 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[-2].minor.yy255 = yymsp[-1].minor.yy255; }
#line 2233 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 69: /* lifetime_statement ::= LIFETIME_KW time_value SEMICOLON */
{  yy_destructor(yypParser,20,&yymsp[-2].minor);
#line 580 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[-2].minor.yy255 = yymsp[-1].minor.yy255; }
#line 2241 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 71: /* gop_tree_mode ::= NO_TREE_KW */
{  yy_destructor(yypParser,44,&yymsp[0].minor);
#line 583 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[0].minor.yy256 = (gop_tree_mode_t)GOP_NO_TREE; }
#line 2249 "./mate_grammar.c"
}
        break;
      case 72: /* gop_tree_mode ::= PDU_TREE_KW */
{  yy_destructor(yypParser,45,&yymsp[0].minor);
#line 584 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[0].minor.yy256 = (gop_tree_mode_t)GOP_PDU_TREE; }
#line 2256 "./mate_grammar.c"
}
        break;
      case 73: /* gop_tree_mode ::= FRAME_TREE_KW */
{  yy_destructor(yypParser,46,&yymsp[0].minor);
#line 585 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[0].minor.yy256 = (gop_tree_mode_t)GOP_FRAME_TREE; }
#line 2263 "./mate_grammar.c"
}
        break;
      case 74: /* gop_tree_mode ::= BASIC_TREE_KW */
{  yy_destructor(yypParser,47,&yymsp[0].minor);
#line 586 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[0].minor.yy256 = (gop_tree_mode_t)GOP_BASIC_PDU_TREE; }
#line 2270 "./mate_grammar.c"
}
        break;
      case 75: /* true_false ::= TRUE_KW */
{  yy_destructor(yypParser,48,&yymsp[0].minor);
#line 588 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[0].minor.yy182 = TRUE; }
#line 2277 "./mate_grammar.c"
}
        break;
      case 76: /* true_false ::= FALSE_KW */
{  yy_destructor(yypParser,49,&yymsp[0].minor);
#line 589 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[0].minor.yy182 = FALSE; }
#line 2284 "./mate_grammar.c"
}
        break;
      case 77: /* pdu_name ::= NAME */
#line 591 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{
	mate_cfg_pdu* c;
	if (( c =  (mate_cfg_pdu *)g_hash_table_lookup(mc->pducfgs,yymsp[0].minor.yy0) )) {
		yylhsminor.yy212 = c->name;
	} else {
		configuration_error(mc,"No such Pdu: '%s'",yymsp[0].minor.yy0);
	}
}
#line 2297 "./mate_grammar.c"
  yymsp[0].minor.yy212 = yylhsminor.yy212;
        break;
      case 78: /* time_value ::= FLOATING */
      case 79: /* time_value ::= INTEGER */ yytestcase(yyruleno==79);
#line 601 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{
	yylhsminor.yy255 = (float) g_ascii_strtod(yymsp[0].minor.yy0,NULL);
}
#line 2306 "./mate_grammar.c"
  yymsp[0].minor.yy255 = yylhsminor.yy255;
        break;
      case 80: /* gog_decl ::= GOG_KW NAME OPEN_BRACE gog_key_statements extra_statement transform_list_statement gog_expiration_statement gog_goptree_statement show_times_statement CLOSE_BRACE SEMICOLON */
{  yy_destructor(yypParser,13,&yymsp[-10].minor);
#line 619 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{
		mate_cfg_gog* cfg = NULL;

		if ( g_hash_table_lookup(mc->gogcfgs,yymsp[-9].minor.yy0) ) {
			configuration_error(mc,"Gog '%s' exists already ",yymsp[-9].minor.yy0);
		}

		cfg = new_gogcfg(mc, yymsp[-9].minor.yy0);

		cfg->expiration = yymsp[-4].minor.yy255;
		cfg->gop_tree_mode = yymsp[-3].minor.yy256;
		cfg->transforms = yymsp[-5].minor.yy147;
		cfg->keys = yymsp[-7].minor.yy77;
		cfg->show_times = yymsp[-2].minor.yy182;

		merge_avpl(cfg->extra,yymsp[-6].minor.yy70,TRUE);
		delete_avpl(yymsp[-6].minor.yy70,TRUE);
}
#line 2330 "./mate_grammar.c"
  yy_destructor(yypParser,4,&yymsp[-8].minor);
  yy_destructor(yypParser,5,&yymsp[-1].minor);
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 81: /* gog_goptree_statement ::= GOP_TREE_KW gop_tree_type SEMICOLON */
{  yy_destructor(yypParser,23,&yymsp[-2].minor);
#line 638 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[-2].minor.yy256 = yymsp[-1].minor.yy256; }
#line 2340 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 82: /* gog_goptree_statement ::= */
#line 639 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[1].minor.yy256 = mc->defaults.gog.gop_tree_mode; }
#line 2347 "./mate_grammar.c"
        break;
      case 84: /* gog_expiration_statement ::= */
#line 642 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[1].minor.yy255 = mc->defaults.gog.expiration; }
#line 2352 "./mate_grammar.c"
        break;
      case 85: /* gop_tree_type ::= NULL_TREE_KW */
{  yy_destructor(yypParser,51,&yymsp[0].minor);
#line 644 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[0].minor.yy256 = GOP_NULL_TREE; }
#line 2358 "./mate_grammar.c"
}
        break;
      case 86: /* gop_tree_type ::= FULL_TREE_KW */
{  yy_destructor(yypParser,52,&yymsp[0].minor);
#line 645 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[0].minor.yy256 = GOP_FULL_TREE; }
#line 2365 "./mate_grammar.c"
}
        break;
      case 87: /* gop_tree_type ::= BASIC_TREE_KW */
{  yy_destructor(yypParser,47,&yymsp[0].minor);
#line 646 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[0].minor.yy256 = GOP_BASIC_TREE; }
#line 2372 "./mate_grammar.c"
}
        break;
      case 88: /* gog_key_statements ::= gog_key_statements gog_key_statement */
#line 648 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{
	loal_append(yymsp[-1].minor.yy77,yymsp[0].minor.yy70);
	yylhsminor.yy77 = yymsp[-1].minor.yy77;
}
#line 2381 "./mate_grammar.c"
  yymsp[-1].minor.yy77 = yylhsminor.yy77;
        break;
      case 89: /* gog_key_statements ::= gog_key_statement */
#line 653 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{
	yylhsminor.yy77 = new_loal("");
	loal_append(yylhsminor.yy77,yymsp[0].minor.yy70);
}
#line 2390 "./mate_grammar.c"
  yymsp[0].minor.yy77 = yylhsminor.yy77;
        break;
      case 90: /* gog_key_statement ::= MEMBER_KW gop_name avpl SEMICOLON */
{  yy_destructor(yypParser,53,&yymsp[-3].minor);
#line 659 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{
	rename_avpl(yymsp[-1].minor.yy70,yymsp[-2].minor.yy212);
	yymsp[-3].minor.yy70 = yymsp[-1].minor.yy70;
}
#line 2400 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 91: /* gop_name ::= NAME */
#line 664 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{
	mate_cfg_gop* c;
	if (( c = (mate_cfg_gop *)g_hash_table_lookup(mc->gopcfgs,yymsp[0].minor.yy0) )) {
		yylhsminor.yy212 = c->name;
	} else {
		configuration_error(mc,"No Gop called '%s' has been already declared",yymsp[0].minor.yy0);
	}
}
#line 2414 "./mate_grammar.c"
  yymsp[0].minor.yy212 = yylhsminor.yy212;
        break;
      case 92: /* extra_statement ::= EXTRA_KW avpl SEMICOLON */
{  yy_destructor(yypParser,54,&yymsp[-2].minor);
#line 676 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[-2].minor.yy70 = yymsp[-1].minor.yy70; }
#line 2421 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 93: /* extra_statement ::= */
#line 677 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[1].minor.yy70 = new_avpl(""); }
#line 2428 "./mate_grammar.c"
        break;
      case 94: /* transform_list_statement ::= TRANSFORM_KW transform_list SEMICOLON */
{  yy_destructor(yypParser,24,&yymsp[-2].minor);
#line 679 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[-2].minor.yy147 = yymsp[-1].minor.yy147; }
#line 2434 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 95: /* transform_list_statement ::= */
#line 680 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[1].minor.yy147 = g_ptr_array_new(); }
#line 2441 "./mate_grammar.c"
        break;
      case 96: /* transform_list ::= transform_list COMMA transform */
#line 682 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{
	yylhsminor.yy147 = yymsp[-2].minor.yy147;
	g_ptr_array_add(yymsp[-2].minor.yy147,yymsp[0].minor.yy11);
}
#line 2449 "./mate_grammar.c"
  yy_destructor(yypParser,55,&yymsp[-1].minor);
  yymsp[-2].minor.yy147 = yylhsminor.yy147;
        break;
      case 97: /* transform_list ::= transform */
#line 687 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{
	yylhsminor.yy147 = g_ptr_array_new();
	g_ptr_array_add(yylhsminor.yy147,yymsp[0].minor.yy11);
}
#line 2459 "./mate_grammar.c"
  yymsp[0].minor.yy147 = yylhsminor.yy147;
        break;
      case 98: /* transform ::= NAME */
#line 692 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{
	AVPL_Transf* t;

	if (( t = (AVPL_Transf *)g_hash_table_lookup(mc->transfs,yymsp[0].minor.yy0) )) {
		yylhsminor.yy11 = t;
	} else {
		configuration_error(mc,"There's no such Transformation: %s",yymsp[0].minor.yy0);
	}
}
#line 2473 "./mate_grammar.c"
  yymsp[0].minor.yy11 = yylhsminor.yy11;
        break;
      case 99: /* avpl ::= OPEN_PARENS avps CLOSE_PARENS */
{  yy_destructor(yypParser,56,&yymsp[-2].minor);
#line 702 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[-2].minor.yy70 = yymsp[-1].minor.yy70; }
#line 2480 "./mate_grammar.c"
  yy_destructor(yypParser,57,&yymsp[0].minor);
}
        break;
      case 100: /* avpl ::= OPEN_PARENS CLOSE_PARENS */
{  yy_destructor(yypParser,56,&yymsp[-1].minor);
#line 703 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yymsp[-1].minor.yy70 = new_avpl(""); }
#line 2488 "./mate_grammar.c"
  yy_destructor(yypParser,57,&yymsp[0].minor);
}
        break;
      case 101: /* avps ::= avps COMMA avp */
#line 705 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yylhsminor.yy70 = yymsp[-2].minor.yy70; if ( ! insert_avp(yymsp[-2].minor.yy70,yymsp[0].minor.yy226) ) delete_avp(yymsp[0].minor.yy226); }
#line 2495 "./mate_grammar.c"
  yy_destructor(yypParser,55,&yymsp[-1].minor);
  yymsp[-2].minor.yy70 = yylhsminor.yy70;
        break;
      case 102: /* avps ::= avp */
#line 706 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yylhsminor.yy70 = new_avpl(""); if ( ! insert_avp(yylhsminor.yy70,yymsp[0].minor.yy226) ) delete_avp(yymsp[0].minor.yy226); }
#line 2502 "./mate_grammar.c"
  yymsp[0].minor.yy70 = yylhsminor.yy70;
        break;
      case 103: /* avp ::= NAME AVP_OPERATOR value */
#line 708 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yylhsminor.yy226 = new_avp(yymsp[-2].minor.yy0,yymsp[0].minor.yy212,*yymsp[-1].minor.yy0); }
#line 2508 "./mate_grammar.c"
  yymsp[-2].minor.yy226 = yylhsminor.yy226;
        break;
      case 104: /* avp ::= NAME */
#line 709 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yylhsminor.yy226 = new_avp(yymsp[0].minor.yy0,"",'?'); }
#line 2514 "./mate_grammar.c"
  yymsp[0].minor.yy226 = yylhsminor.yy226;
        break;
      case 105: /* avp ::= NAME OPEN_BRACE avp_oneoff CLOSE_BRACE */
#line 710 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yylhsminor.yy226 = new_avp(yymsp[-3].minor.yy0,yymsp[-1].minor.yy212,'|'); }
#line 2520 "./mate_grammar.c"
  yy_destructor(yypParser,4,&yymsp[-2].minor);
  yy_destructor(yypParser,5,&yymsp[0].minor);
  yymsp[-3].minor.yy226 = yylhsminor.yy226;
        break;
      case 106: /* avp_oneoff ::= avp_oneoff PIPE value */
#line 712 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yylhsminor.yy212 = g_strdup_printf("%s|%s",yymsp[-2].minor.yy212,yymsp[0].minor.yy212); }
#line 2528 "./mate_grammar.c"
  yy_destructor(yypParser,59,&yymsp[-1].minor);
  yymsp[-2].minor.yy212 = yylhsminor.yy212;
        break;
      case 107: /* avp_oneoff ::= value */
#line 713 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yylhsminor.yy212 = g_strdup(yymsp[0].minor.yy212); }
#line 2535 "./mate_grammar.c"
  yymsp[0].minor.yy212 = yylhsminor.yy212;
        break;
      case 108: /* value ::= QUOTED */
      case 109: /* value ::= NAME */ yytestcase(yyruleno==109);
      case 110: /* value ::= FLOATING */ yytestcase(yyruleno==110);
      case 111: /* value ::= INTEGER */ yytestcase(yyruleno==111);
      case 112: /* value ::= DOTED_IP */ yytestcase(yyruleno==112);
#line 715 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yylhsminor.yy212 = g_strdup(yymsp[0].minor.yy0); }
#line 2545 "./mate_grammar.c"
  yymsp[0].minor.yy212 = yylhsminor.yy212;
        break;
      case 113: /* value ::= COLONIZED */
#line 720 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{ yylhsminor.yy212 = recolonize(mc,yymsp[0].minor.yy0); }
#line 2551 "./mate_grammar.c"
  yymsp[0].minor.yy212 = yylhsminor.yy212;
        break;
      case 123: /* decl ::= DONE_KW SEMICOLON */
{  yy_destructor(yypParser,1,&yymsp[-1].minor);
#line 259 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{
}
#line 2559 "./mate_grammar.c"
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 124: /* debug_decl ::= DEBUG_KW OPEN_BRACE dbgfile_default dbglevel_default pdu_dbglevel_default gop_dbglevel_default gog_dbglevel_default CLOSE_BRACE SEMICOLON */
{  yy_destructor(yypParser,3,&yymsp[-8].minor);
#line 264 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{
}
#line 2568 "./mate_grammar.c"
  yy_destructor(yypParser,4,&yymsp[-7].minor);
  yy_destructor(yypParser,5,&yymsp[-1].minor);
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 130: /* defaults_decl ::= DEFAULT_KW OPEN_BRACE pdu_defaults gop_defaults gog_defaults CLOSE_BRACE SEMICOLON */
{  yy_destructor(yypParser,14,&yymsp[-6].minor);
#line 286 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{
}
#line 2579 "./mate_grammar.c"
  yy_destructor(yypParser,4,&yymsp[-5].minor);
  yy_destructor(yypParser,5,&yymsp[-1].minor);
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 131: /* pdu_defaults ::= PDU_KW OPEN_BRACE pdu_last_extracted_default pdu_drop_unassigned_default pdu_discard_default CLOSE_BRACE SEMICOLON */
{  yy_destructor(yypParser,11,&yymsp[-6].minor);
#line 288 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{
}
#line 2590 "./mate_grammar.c"
  yy_destructor(yypParser,4,&yymsp[-5].minor);
  yy_destructor(yypParser,5,&yymsp[-1].minor);
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 136: /* gop_defaults ::= GOP_KW OPEN_BRACE gop_expiration_default gop_idle_timeout_default gop_lifetime_default gop_drop_unassigned_default gop_tree_mode_default gop_show_times_default CLOSE_BRACE SEMICOLON */
{  yy_destructor(yypParser,12,&yymsp[-9].minor);
#line 300 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{
}
#line 2601 "./mate_grammar.c"
  yy_destructor(yypParser,4,&yymsp[-8].minor);
  yy_destructor(yypParser,5,&yymsp[-1].minor);
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      case 144: /* gog_defaults ::= GOG_KW OPEN_BRACE gog_expiration_default gop_tree_mode_default gog_goptree_default gog_show_times_default CLOSE_BRACE SEMICOLON */
{  yy_destructor(yypParser,13,&yymsp[-7].minor);
#line 321 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"
{
}
#line 2612 "./mate_grammar.c"
  yy_destructor(yypParser,4,&yymsp[-6].minor);
  yy_destructor(yypParser,5,&yymsp[-1].minor);
  yy_destructor(yypParser,2,&yymsp[0].minor);
}
        break;
      default:
      /* (114) mate_config ::= decls */ yytestcase(yyruleno==114);
      /* (115) decls ::= decls decl */ yytestcase(yyruleno==115);
      /* (116) decls ::= */ yytestcase(yyruleno==116);
      /* (117) decl ::= pdu_decl (OPTIMIZED OUT) */ assert(yyruleno!=117);
      /* (118) decl ::= gop_decl (OPTIMIZED OUT) */ assert(yyruleno!=118);
      /* (119) decl ::= gog_decl (OPTIMIZED OUT) */ assert(yyruleno!=119);
      /* (120) decl ::= transform_decl (OPTIMIZED OUT) */ assert(yyruleno!=120);
      /* (121) decl ::= defaults_decl (OPTIMIZED OUT) */ assert(yyruleno!=121);
      /* (122) decl ::= debug_decl (OPTIMIZED OUT) */ assert(yyruleno!=122);
      /* (125) dbgfile_default ::= */ yytestcase(yyruleno==125);
      /* (126) dbglevel_default ::= */ yytestcase(yyruleno==126);
      /* (127) pdu_dbglevel_default ::= */ yytestcase(yyruleno==127);
      /* (128) gop_dbglevel_default ::= */ yytestcase(yyruleno==128);
      /* (129) gog_dbglevel_default ::= */ yytestcase(yyruleno==129);
      /* (132) pdu_defaults ::= */ yytestcase(yyruleno==132);
      /* (133) pdu_last_extracted_default ::= */ yytestcase(yyruleno==133);
      /* (134) pdu_drop_unassigned_default ::= */ yytestcase(yyruleno==134);
      /* (135) pdu_discard_default ::= */ yytestcase(yyruleno==135);
      /* (137) gop_defaults ::= */ yytestcase(yyruleno==137);
      /* (138) gop_expiration_default ::= */ yytestcase(yyruleno==138);
      /* (139) gop_idle_timeout_default ::= */ yytestcase(yyruleno==139);
      /* (140) gop_lifetime_default ::= */ yytestcase(yyruleno==140);
      /* (141) gop_drop_unassigned_default ::= */ yytestcase(yyruleno==141);
      /* (142) gop_tree_mode_default ::= */ yytestcase(yyruleno==142);
      /* (143) gop_show_times_default ::= */ yytestcase(yyruleno==143);
      /* (145) gog_defaults ::= */ yytestcase(yyruleno==145);
      /* (146) gog_expiration_default ::= */ yytestcase(yyruleno==146);
      /* (147) gog_goptree_default ::= */ yytestcase(yyruleno==147);
      /* (148) gog_show_times_default ::= */ yytestcase(yyruleno==148);
        break;
/********** End reduce actions ************************************************/
  };
  assert( yyruleno<sizeof(yyRuleInfo)/sizeof(yyRuleInfo[0]) );
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yyact = yy_find_reduce_action(yymsp[yysize].stateno,(YYCODETYPE)yygoto);

  /* There are no SHIFTREDUCE actions on nonterminals because the table
  ** generator has simplified them to pure REDUCE actions. */
  assert( !(yyact>YY_MAX_SHIFT && yyact<=YY_MAX_SHIFTREDUCE) );

  /* It is not possible for a REDUCE to be followed by an error */
  assert( yyact!=YY_ERROR_ACTION );

  yymsp += yysize+1;
  yypParser->yytos = yymsp;
  yymsp->stateno = (YYACTIONTYPE)yyact;
  yymsp->major = (YYCODETYPE)yygoto;
  yyTraceShift(yypParser, yyact, "... then shift");
  return yyact;
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  MateParserARG_FETCH
  MateParserCTX_FETCH
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
/************ Begin %parse_failure code ***************************************/
#line 188 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"

	configuration_error(mc,"Parse Error");
#line 2692 "./mate_grammar.c"
/************ End %parse_failure code *****************************************/
  MateParserARG_STORE /* Suppress warning about unused %extra_argument variable */
  MateParserCTX_STORE
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor _U_,               /* The major type of the error token */
  MateParserTOKENTYPE yyminor         /* The minor type of the error token */
){
  MateParserARG_FETCH
  MateParserCTX_FETCH
#define TOKEN yyminor
/************ Begin %syntax_error code ****************************************/
#line 184 "/root/CLionProjects/tshark/plugins/epan/mate/mate_grammar.lemon"

	configuration_error(mc,"Syntax Error before %s",yyminor);
#line 2714 "./mate_grammar.c"
/************ End %syntax_error code ******************************************/
  MateParserARG_STORE /* Suppress warning about unused %extra_argument variable */
  MateParserCTX_STORE
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  MateParserARG_FETCH
  MateParserCTX_FETCH
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
#ifndef YYNOERRORRECOVERY
  yypParser->yyerrcnt = -1;
#endif
  assert( yypParser->yytos==yypParser->yystack );
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
/*********** Begin %parse_accept code *****************************************/
/*********** End %parse_accept code *******************************************/
  MateParserARG_STORE /* Suppress warning about unused %extra_argument variable */
  MateParserCTX_STORE
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "MateParserAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void MateParser(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  MateParserTOKENTYPE yyminor       /* The value for the token */
  MateParserARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  YYACTIONTYPE yyact;   /* The parser action. */
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  int yyendofinput;     /* True if we are at the end of input */
#endif
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser = (yyParser*)yyp;  /* The parser */
  MateParserCTX_FETCH
  MateParserARG_STORE

  assert( yypParser->yytos!=0 );
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  yyendofinput = (yymajor==0);
#endif

  yyact = yypParser->yytos->stateno;
#ifndef NDEBUG
  if( yyTraceFILE ){
    if( yyact < YY_MIN_REDUCE ){
      fprintf(yyTraceFILE,"%sInput '%s' in state %d\n",
              yyTracePrompt,yyTokenName[yymajor],yyact);
    }else{
      fprintf(yyTraceFILE,"%sInput '%s' with pending reduce %d\n",
              yyTracePrompt,yyTokenName[yymajor],yyact-YY_MIN_REDUCE);
    }
  }
#endif

  do{
    assert( yyact==yypParser->yytos->stateno );
    yyact = yy_find_shift_action((YYCODETYPE)yymajor,yyact);
    if( yyact >= YY_MIN_REDUCE ){
      yyact = yy_reduce(yypParser,yyact-YY_MIN_REDUCE,yymajor,
                        yyminor MateParserCTX_PARAM);
    }else if( yyact <= YY_MAX_SHIFTREDUCE ){
      yy_shift(yypParser,yyact,(YYCODETYPE)yymajor,yyminor);
#ifndef YYNOERRORRECOVERY
      yypParser->yyerrcnt--;
#endif
      break;
    }else if( yyact==YY_ACCEPT_ACTION ){
      yypParser->yytos--;
      yy_accept(yypParser);
      return;
    }else{
      assert( yyact == YY_ERROR_ACTION );
      yyminorunion.yy0 = yyminor;
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminor);
      }
      yymx = yypParser->yytos->major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor, &yyminorunion);
        yymajor = YYNOCODE;
      }else{
        while( yypParser->yytos >= yypParser->yystack
            && yymx != YYERRORSYMBOL
            && (yyact = yy_find_reduce_action(
                        yypParser->yytos->stateno,
                        YYERRORSYMBOL)) >= YY_MIN_REDUCE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yytos < yypParser->yystack || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
          yypParser->yyerrcnt = -1;
#endif
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          yy_shift(yypParser,yyact,YYERRORSYMBOL,yyminor);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
      if( yymajor==YYNOCODE ) break;
      yyact = yypParser->yytos->stateno;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor, yyminor);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      break;
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor, yyminor);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
        yypParser->yyerrcnt = -1;
#endif
      }
      break;
#endif
    }
  }while( yypParser->yytos>yypParser->yystack );
#ifndef NDEBUG
  if( yyTraceFILE ){
    yyStackEntry *i;
    char cDiv = '[';
    fprintf(yyTraceFILE,"%sReturn. Stack=",yyTracePrompt);
    for(i=&yypParser->yystack[1]; i<=yypParser->yytos; i++){
      fprintf(yyTraceFILE,"%c%s", cDiv, yyTokenName[i->major]);
      cDiv = ' ';
    }
    fprintf(yyTraceFILE,"]\n");
  }
#endif
  return;
}

#if 0
/*
** Return the fallback token corresponding to canonical token iToken, or
** 0 if iToken has no fallback.
*/
int MateParserFallback(int iToken){
#ifdef YYFALLBACK
  if( iToken<(int)(sizeof(yyFallback)/sizeof(yyFallback[0])) ){
    return yyFallback[iToken];
  }
#else
  (void)iToken;
#endif
  return 0;
}
#endif
