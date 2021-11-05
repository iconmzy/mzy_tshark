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
#line 2 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"

#include "config.h"

#include <assert.h>

#include "dfilter-int.h"
#include "syntax-tree.h"
#include "sttype-range.h"
#include "sttype-test.h"
#include "sttype-function.h"
#include "sttype-set.h"
#include "drange.h"

#include "grammar.h"

#ifdef _WIN32
#pragma warning(disable:4671)
#endif

/* End of C code */
#line 49 "./grammar.c"
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
**    DfilterTOKENTYPE     is the data type used for minor type for terminal
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
**                       which is DfilterTOKENTYPE.  The entry in the union
**                       for terminal symbols is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    DfilterARG_SDECL     A static variable declaration for the %extra_argument
**    DfilterARG_PDECL     A parameter declaration for the %extra_argument
**    DfilterARG_PARAM     Code to pass %extra_argument as a subroutine parameter
**    DfilterARG_STORE     Code to store %extra_argument into yypParser
**    DfilterARG_FETCH     Code to extract %extra_argument from yypParser
**    DfilterCTX_*         As DfilterARG_ except for %extra_context
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
#define YYNOCODE 43
#define YYACTIONTYPE unsigned char
#define DfilterTOKENTYPE stnode_t*
typedef union {
  int yyinit;
  DfilterTOKENTYPE yy0;
  GSList* yy17;
  test_op_t yy24;
  drange_node* yy85;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define DfilterARG_SDECL dfwork_t *dfw;
#define DfilterARG_PDECL ,dfwork_t *dfw
#define DfilterARG_PARAM ,dfw
#define DfilterARG_FETCH dfwork_t *dfw=yypParser->dfw;
#define DfilterARG_STORE yypParser->dfw=dfw;
#define DfilterCTX_SDECL
#define DfilterCTX_PDECL
#define DfilterCTX_PARAM
#define DfilterCTX_FETCH
#define DfilterCTX_STORE
#define YYNSTATE             34
#define YYNRULE              45
#define YYNTOKEN             31
#define YY_MAX_SHIFT         33
#define YY_MIN_SHIFTREDUCE   64
#define YY_MAX_SHIFTREDUCE   108
#define YY_ERROR_ACTION      109
#define YY_ACCEPT_ACTION     110
#define YY_NO_ACTION         111
#define YY_MIN_REDUCE        112
#define YY_MAX_REDUCE        156
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
#define YY_ACTTAB_COUNT (136)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   129,   21,    7,   90,   91,   94,   95,   92,   93,   97,
 /*    10 */    98,   96,  113,  112,    4,    3,    2,   32,   31,   74,
 /*    20 */    75,  130,   12,   25,    2,   32,   31,   74,   75,    8,
 /*    30 */   154,    6,   23,    1,   30,   20,   26,   18,    5,   29,
 /*    40 */    23,    1,  110,   17,   14,  114,  115,   10,   30,   16,
 /*    50 */    14,  114,  115,   29,   30,   85,   99,   11,   84,   29,
 /*    60 */   118,   14,  114,  115,   83,   30,  117,   14,  114,  115,
 /*    70 */    29,   30,  127,    4,    3,  126,   29,   33,   14,  114,
 /*    80 */   115,  111,   30,   32,   31,   74,   75,   29,   28,   27,
 /*    90 */    32,   31,   74,   75,    3,   22,  125,  150,   23,   30,
 /*   100 */   105,   30,  108,   19,   29,   23,   29,   80,   15,  111,
 /*   110 */   111,   13,  137,  155,  151,   30,  111,   30,   30,  111,
 /*   120 */    29,   24,   29,   29,    9,   30,  111,  111,  111,  111,
 /*   130 */    29,  111,  111,  111,  111,  104,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    38,   39,   36,    3,    4,    5,    6,    7,    8,    9,
 /*    10 */    10,   11,    0,    0,    1,    2,   12,   13,   14,   15,
 /*    20 */    16,   38,   17,   23,   12,   13,   14,   15,   16,   27,
 /*    30 */    33,   24,   28,   29,   37,   20,   21,   40,   29,   42,
 /*    40 */    28,   29,   31,   32,   33,   34,   35,   27,   37,   32,
 /*    50 */    33,   34,   35,   42,   37,   20,   25,   26,   20,   42,
 /*    60 */    32,   33,   34,   35,   20,   37,   32,   33,   34,   35,
 /*    70 */    42,   37,   17,    1,    2,   17,   42,   32,   33,   34,
 /*    80 */    35,   43,   37,   13,   14,   15,   16,   42,   21,   22,
 /*    90 */    13,   14,   15,   16,    2,   33,   17,   33,   28,   37,
 /*   100 */    30,   37,   30,   41,   42,   28,   42,   18,   19,   43,
 /*   110 */    43,   33,   34,   33,   33,   37,   43,   37,   37,   43,
 /*   120 */    42,   33,   42,   42,   19,   37,   43,   43,   43,   43,
 /*   130 */    42,   43,   43,   43,   43,   30,   43,   43,   43,   43,
 /*   140 */    43,   43,   43,   43,   43,   43,   43,   43,   43,   43,
 /*   150 */    43,   43,   43,   43,   43,   43,
};
#define YY_SHIFT_COUNT    (33)
#define YY_SHIFT_MIN      (0)
#define YY_SHIFT_MAX      (105)
static const unsigned char yy_shift_ofst[] = {
 /*     0 */    12,    4,    4,    4,    4,   70,   77,   77,   77,   77,
 /*    10 */    77,   77,   15,    0,    0,   15,   72,   13,  105,   31,
 /*    20 */    67,   89,    2,    9,   20,    7,   35,   38,   44,    5,
 /*    30 */    55,   58,   79,   92,
};
#define YY_REDUCE_COUNT (15)
#define YY_REDUCE_MIN   (-38)
#define YY_REDUCE_MAX   (88)
static const signed char yy_reduce_ofst[] = {
 /*     0 */    11,   17,   28,   34,   45,   -3,   62,   78,   64,   80,
 /*    10 */    81,   88,  -38,  -34,  -34,  -17,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   109,  109,  109,  109,  109,  109,  109,  109,  109,  109,
 /*    10 */   109,  109,  109,  136,  119,  109,  109,  109,  109,  109,
 /*    20 */   135,  109,  148,  109,  149,  109,  109,  109,  134,  109,
 /*    30 */   124,  121,  120,  116,
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
  DfilterARG_SDECL                /* A place to hold %extra_argument */
  DfilterCTX_SDECL                /* A place to hold %extra_context */
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
void DfilterTrace(FILE *TraceFILE, char *zTracePrompt){
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
  /*    1 */ "TEST_AND",
  /*    2 */ "TEST_OR",
  /*    3 */ "TEST_EQ",
  /*    4 */ "TEST_NE",
  /*    5 */ "TEST_LT",
  /*    6 */ "TEST_LE",
  /*    7 */ "TEST_GT",
  /*    8 */ "TEST_GE",
  /*    9 */ "TEST_CONTAINS",
  /*   10 */ "TEST_MATCHES",
  /*   11 */ "TEST_BITWISE_AND",
  /*   12 */ "TEST_NOT",
  /*   13 */ "FIELD",
  /*   14 */ "STRING",
  /*   15 */ "CHARCONST",
  /*   16 */ "UNPARSED",
  /*   17 */ "LBRACKET",
  /*   18 */ "RBRACKET",
  /*   19 */ "COMMA",
  /*   20 */ "INTEGER",
  /*   21 */ "COLON",
  /*   22 */ "HYPHEN",
  /*   23 */ "TEST_IN",
  /*   24 */ "LBRACE",
  /*   25 */ "RBRACE",
  /*   26 */ "WHITESPACE",
  /*   27 */ "DOTDOT",
  /*   28 */ "FUNCTION",
  /*   29 */ "LPAREN",
  /*   30 */ "RPAREN",
  /*   31 */ "sentence",
  /*   32 */ "expr",
  /*   33 */ "entity",
  /*   34 */ "relation_test",
  /*   35 */ "logical_test",
  /*   36 */ "rel_op2",
  /*   37 */ "range",
  /*   38 */ "drnode",
  /*   39 */ "drnode_list",
  /*   40 */ "funcparams",
  /*   41 */ "setnode_list",
  /*   42 */ "range_body",
};
#endif /* defined(YYCOVERAGE) || !defined(NDEBUG) */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "sentence ::= expr",
 /*   1 */ "sentence ::=",
 /*   2 */ "expr ::= relation_test",
 /*   3 */ "expr ::= logical_test",
 /*   4 */ "logical_test ::= expr TEST_AND expr",
 /*   5 */ "logical_test ::= expr TEST_OR expr",
 /*   6 */ "logical_test ::= TEST_NOT expr",
 /*   7 */ "logical_test ::= entity",
 /*   8 */ "entity ::= FIELD",
 /*   9 */ "entity ::= STRING",
 /*  10 */ "entity ::= CHARCONST",
 /*  11 */ "entity ::= UNPARSED",
 /*  12 */ "entity ::= range",
 /*  13 */ "range_body ::= FIELD",
 /*  14 */ "range_body ::= STRING",
 /*  15 */ "range_body ::= range",
 /*  16 */ "range ::= range_body LBRACKET drnode_list RBRACKET",
 /*  17 */ "drnode_list ::= drnode",
 /*  18 */ "drnode_list ::= drnode_list COMMA drnode",
 /*  19 */ "drnode ::= INTEGER COLON INTEGER",
 /*  20 */ "drnode ::= INTEGER HYPHEN INTEGER",
 /*  21 */ "drnode ::= COLON INTEGER",
 /*  22 */ "drnode ::= INTEGER COLON",
 /*  23 */ "drnode ::= INTEGER",
 /*  24 */ "relation_test ::= entity rel_op2 entity",
 /*  25 */ "relation_test ::= entity rel_op2 relation_test",
 /*  26 */ "rel_op2 ::= TEST_EQ",
 /*  27 */ "rel_op2 ::= TEST_NE",
 /*  28 */ "rel_op2 ::= TEST_GT",
 /*  29 */ "rel_op2 ::= TEST_GE",
 /*  30 */ "rel_op2 ::= TEST_LT",
 /*  31 */ "rel_op2 ::= TEST_LE",
 /*  32 */ "rel_op2 ::= TEST_BITWISE_AND",
 /*  33 */ "rel_op2 ::= TEST_CONTAINS",
 /*  34 */ "rel_op2 ::= TEST_MATCHES",
 /*  35 */ "relation_test ::= entity TEST_IN LBRACE setnode_list RBRACE",
 /*  36 */ "setnode_list ::= entity",
 /*  37 */ "setnode_list ::= setnode_list WHITESPACE entity",
 /*  38 */ "setnode_list ::= entity DOTDOT entity",
 /*  39 */ "setnode_list ::= setnode_list WHITESPACE entity DOTDOT entity",
 /*  40 */ "entity ::= FUNCTION LPAREN funcparams RPAREN",
 /*  41 */ "entity ::= FUNCTION LPAREN RPAREN",
 /*  42 */ "funcparams ::= entity",
 /*  43 */ "funcparams ::= funcparams COMMA entity",
 /*  44 */ "expr ::= LPAREN expr RPAREN",
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
** second argument to DfilterAlloc() below.  This can be changed by
** putting an appropriate #define in the %include section of the input
** grammar.
*/
#ifndef YYMALLOCARGTYPE
# define YYMALLOCARGTYPE size_t
#endif

/* Initialize a new parser that has already been allocated.
*/
static void DfilterInit(void *yypRawParser DfilterCTX_PDECL){
  yyParser *yypParser = (yyParser*)yypRawParser;
  DfilterCTX_STORE
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

#ifndef Dfilter_ENGINEALWAYSONSTACK
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
** to Dfilter and DfilterFree.
*/
void *DfilterAlloc(void *(*mallocProc)(YYMALLOCARGTYPE) DfilterCTX_PDECL){
  yyParser *yypParser;
  yypParser = (yyParser*)(*mallocProc)( (YYMALLOCARGTYPE)sizeof(yyParser) );
  if( yypParser ){
    DfilterCTX_STORE
    DfilterInit(yypParser DfilterCTX_PARAM);
  }
  return (void*)yypParser;
}
#endif /* Dfilter_ENGINEALWAYSONSTACK */


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
  DfilterARG_FETCH
  DfilterCTX_FETCH
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
    case 1: /* TEST_AND */
    case 2: /* TEST_OR */
    case 3: /* TEST_EQ */
    case 4: /* TEST_NE */
    case 5: /* TEST_LT */
    case 6: /* TEST_LE */
    case 7: /* TEST_GT */
    case 8: /* TEST_GE */
    case 9: /* TEST_CONTAINS */
    case 10: /* TEST_MATCHES */
    case 11: /* TEST_BITWISE_AND */
    case 12: /* TEST_NOT */
    case 13: /* FIELD */
    case 14: /* STRING */
    case 15: /* CHARCONST */
    case 16: /* UNPARSED */
    case 17: /* LBRACKET */
    case 18: /* RBRACKET */
    case 19: /* COMMA */
    case 20: /* INTEGER */
    case 21: /* COLON */
    case 22: /* HYPHEN */
    case 23: /* TEST_IN */
    case 24: /* LBRACE */
    case 25: /* RBRACE */
    case 26: /* WHITESPACE */
    case 27: /* DOTDOT */
    case 28: /* FUNCTION */
    case 29: /* LPAREN */
    case 30: /* RPAREN */
{
#line 31 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"

	(void) dfw; /* Mark unused, similar to Q_UNUSED */
	stnode_free((yypminor->yy0));

#line 632 "./grammar.c"
}
      break;
    case 32: /* expr */
    case 33: /* entity */
    case 34: /* relation_test */
    case 35: /* logical_test */
    case 37: /* range */
{
#line 40 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
stnode_free((yypminor->yy0));
#line 643 "./grammar.c"
}
      break;
    case 38: /* drnode */
{
#line 57 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
drange_node_free((yypminor->yy85));
#line 650 "./grammar.c"
}
      break;
    case 39: /* drnode_list */
{
#line 60 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
drange_node_free_list((yypminor->yy17));
#line 657 "./grammar.c"
}
      break;
    case 40: /* funcparams */
{
#line 63 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
st_funcparams_free((yypminor->yy17));
#line 664 "./grammar.c"
}
      break;
    case 41: /* setnode_list */
{
#line 66 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
set_nodelist_free((yypminor->yy17));
#line 671 "./grammar.c"
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
static void DfilterFinalize(void *p){
  yyParser *pParser = (yyParser*)p;
  while( pParser->yytos>pParser->yystack ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  if( pParser->yystack!=&pParser->yystk0 ) free(pParser->yystack);
#endif
}

#ifndef Dfilter_ENGINEALWAYSONSTACK
/*
** Deallocate and destroy a parser.  Destructors are called for
** all stack elements before shutting the parser down.
**
** If the YYPARSEFREENEVERNULL macro exists (for example because it
** is defined in a %include section of the input grammar) then it is
** assumed that the input pointer is never NULL.
*/
void DfilterFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
#ifndef YYPARSEFREENEVERNULL
  if( p==0 ) return;
#endif
  DfilterFinalize(p);
  (*freeProc)(p);
}
#endif /* Dfilter_ENGINEALWAYSONSTACK */

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int DfilterStackPeak(void *p){
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
int DfilterCoverage(FILE *out){
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
   DfilterARG_FETCH
   DfilterCTX_FETCH
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
   DfilterARG_STORE /* Suppress warning about unused %extra_argument var */
   DfilterCTX_STORE
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
  DfilterTOKENTYPE yyMinor        /* The minor token to shift in */
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
  {   31,   -1 }, /* (0) sentence ::= expr */
  {   31,    0 }, /* (1) sentence ::= */
  {   32,   -1 }, /* (2) expr ::= relation_test */
  {   32,   -1 }, /* (3) expr ::= logical_test */
  {   35,   -3 }, /* (4) logical_test ::= expr TEST_AND expr */
  {   35,   -3 }, /* (5) logical_test ::= expr TEST_OR expr */
  {   35,   -2 }, /* (6) logical_test ::= TEST_NOT expr */
  {   35,   -1 }, /* (7) logical_test ::= entity */
  {   33,   -1 }, /* (8) entity ::= FIELD */
  {   33,   -1 }, /* (9) entity ::= STRING */
  {   33,   -1 }, /* (10) entity ::= CHARCONST */
  {   33,   -1 }, /* (11) entity ::= UNPARSED */
  {   33,   -1 }, /* (12) entity ::= range */
  {   42,   -1 }, /* (13) range_body ::= FIELD */
  {   42,   -1 }, /* (14) range_body ::= STRING */
  {   42,   -1 }, /* (15) range_body ::= range */
  {   37,   -4 }, /* (16) range ::= range_body LBRACKET drnode_list RBRACKET */
  {   39,   -1 }, /* (17) drnode_list ::= drnode */
  {   39,   -3 }, /* (18) drnode_list ::= drnode_list COMMA drnode */
  {   38,   -3 }, /* (19) drnode ::= INTEGER COLON INTEGER */
  {   38,   -3 }, /* (20) drnode ::= INTEGER HYPHEN INTEGER */
  {   38,   -2 }, /* (21) drnode ::= COLON INTEGER */
  {   38,   -2 }, /* (22) drnode ::= INTEGER COLON */
  {   38,   -1 }, /* (23) drnode ::= INTEGER */
  {   34,   -3 }, /* (24) relation_test ::= entity rel_op2 entity */
  {   34,   -3 }, /* (25) relation_test ::= entity rel_op2 relation_test */
  {   36,   -1 }, /* (26) rel_op2 ::= TEST_EQ */
  {   36,   -1 }, /* (27) rel_op2 ::= TEST_NE */
  {   36,   -1 }, /* (28) rel_op2 ::= TEST_GT */
  {   36,   -1 }, /* (29) rel_op2 ::= TEST_GE */
  {   36,   -1 }, /* (30) rel_op2 ::= TEST_LT */
  {   36,   -1 }, /* (31) rel_op2 ::= TEST_LE */
  {   36,   -1 }, /* (32) rel_op2 ::= TEST_BITWISE_AND */
  {   36,   -1 }, /* (33) rel_op2 ::= TEST_CONTAINS */
  {   36,   -1 }, /* (34) rel_op2 ::= TEST_MATCHES */
  {   34,   -5 }, /* (35) relation_test ::= entity TEST_IN LBRACE setnode_list RBRACE */
  {   41,   -1 }, /* (36) setnode_list ::= entity */
  {   41,   -3 }, /* (37) setnode_list ::= setnode_list WHITESPACE entity */
  {   41,   -3 }, /* (38) setnode_list ::= entity DOTDOT entity */
  {   41,   -5 }, /* (39) setnode_list ::= setnode_list WHITESPACE entity DOTDOT entity */
  {   33,   -4 }, /* (40) entity ::= FUNCTION LPAREN funcparams RPAREN */
  {   33,   -3 }, /* (41) entity ::= FUNCTION LPAREN RPAREN */
  {   40,   -1 }, /* (42) funcparams ::= entity */
  {   40,   -3 }, /* (43) funcparams ::= funcparams COMMA entity */
  {   32,   -3 }, /* (44) expr ::= LPAREN expr RPAREN */
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
  DfilterTOKENTYPE yyLookaheadToken  /* Value of the lookahead token */
  DfilterCTX_PDECL                   /* %extra_context */
){
  int yygoto;                     /* The next state */
  YYACTIONTYPE yyact;             /* The next action */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  DfilterARG_FETCH
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
      case 0: /* sentence ::= expr */
#line 144 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{ dfw->st_root = yymsp[0].minor.yy0; }
#line 1102 "./grammar.c"
        break;
      case 1: /* sentence ::= */
#line 145 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{ dfw->st_root = NULL; }
#line 1107 "./grammar.c"
        break;
      case 2: /* expr ::= relation_test */
      case 3: /* expr ::= logical_test */ yytestcase(yyruleno==3);
      case 8: /* entity ::= FIELD */ yytestcase(yyruleno==8);
      case 9: /* entity ::= STRING */ yytestcase(yyruleno==9);
      case 10: /* entity ::= CHARCONST */ yytestcase(yyruleno==10);
      case 11: /* entity ::= UNPARSED */ yytestcase(yyruleno==11);
      case 12: /* entity ::= range */ yytestcase(yyruleno==12);
      case 13: /* range_body ::= FIELD */ yytestcase(yyruleno==13);
      case 14: /* range_body ::= STRING */ yytestcase(yyruleno==14);
      case 15: /* range_body ::= range */ yytestcase(yyruleno==15);
#line 147 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{ yylhsminor.yy0 = yymsp[0].minor.yy0; }
#line 1121 "./grammar.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 4: /* logical_test ::= expr TEST_AND expr */
#line 153 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{
	yylhsminor.yy0 = stnode_new(STTYPE_TEST, NULL);
	sttype_test_set2(yylhsminor.yy0, TEST_OP_AND, yymsp[-2].minor.yy0, yymsp[0].minor.yy0);
}
#line 1130 "./grammar.c"
  yy_destructor(yypParser,1,&yymsp[-1].minor);
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 5: /* logical_test ::= expr TEST_OR expr */
#line 159 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{
	yylhsminor.yy0 = stnode_new(STTYPE_TEST, NULL);
	sttype_test_set2(yylhsminor.yy0, TEST_OP_OR, yymsp[-2].minor.yy0, yymsp[0].minor.yy0);
}
#line 1140 "./grammar.c"
  yy_destructor(yypParser,2,&yymsp[-1].minor);
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 6: /* logical_test ::= TEST_NOT expr */
{  yy_destructor(yypParser,12,&yymsp[-1].minor);
#line 165 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{
	yymsp[-1].minor.yy0 = stnode_new(STTYPE_TEST, NULL);
	sttype_test_set1(yymsp[-1].minor.yy0, TEST_OP_NOT, yymsp[0].minor.yy0);
}
#line 1151 "./grammar.c"
}
        break;
      case 7: /* logical_test ::= entity */
#line 171 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{
	yylhsminor.yy0 = stnode_new(STTYPE_TEST, NULL);
	sttype_test_set1(yylhsminor.yy0, TEST_OP_EXISTS, yymsp[0].minor.yy0);
}
#line 1160 "./grammar.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 16: /* range ::= range_body LBRACKET drnode_list RBRACKET */
#line 191 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{
	yylhsminor.yy0 = stnode_new(STTYPE_RANGE, NULL);
	sttype_range_set(yylhsminor.yy0, yymsp[-3].minor.yy0, yymsp[-1].minor.yy17);

	/* Delete the list, but not the drange_nodes that
	 * the list contains. */
	g_slist_free(yymsp[-1].minor.yy17);
}
#line 1173 "./grammar.c"
  yy_destructor(yypParser,17,&yymsp[-2].minor);
  yy_destructor(yypParser,18,&yymsp[0].minor);
  yymsp[-3].minor.yy0 = yylhsminor.yy0;
        break;
      case 17: /* drnode_list ::= drnode */
#line 201 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{
	yylhsminor.yy17 = g_slist_append(NULL, yymsp[0].minor.yy85);
}
#line 1183 "./grammar.c"
  yymsp[0].minor.yy17 = yylhsminor.yy17;
        break;
      case 18: /* drnode_list ::= drnode_list COMMA drnode */
#line 206 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{
	yylhsminor.yy17 = g_slist_append(yymsp[-2].minor.yy17, yymsp[0].minor.yy85);
}
#line 1191 "./grammar.c"
  yy_destructor(yypParser,19,&yymsp[-1].minor);
  yymsp[-2].minor.yy17 = yylhsminor.yy17;
        break;
      case 19: /* drnode ::= INTEGER COLON INTEGER */
#line 212 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{
	yylhsminor.yy85 = drange_node_new();
	drange_node_set_start_offset(yylhsminor.yy85, stnode_value(yymsp[-2].minor.yy0));
	drange_node_set_length(yylhsminor.yy85, stnode_value(yymsp[0].minor.yy0));

	stnode_free(yymsp[-2].minor.yy0);
	stnode_free(yymsp[0].minor.yy0);
}
#line 1205 "./grammar.c"
  yy_destructor(yypParser,21,&yymsp[-1].minor);
  yymsp[-2].minor.yy85 = yylhsminor.yy85;
        break;
      case 20: /* drnode ::= INTEGER HYPHEN INTEGER */
#line 223 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{
	yylhsminor.yy85 = drange_node_new();
	drange_node_set_start_offset(yylhsminor.yy85, stnode_value(yymsp[-2].minor.yy0));
	drange_node_set_end_offset(yylhsminor.yy85, stnode_value(yymsp[0].minor.yy0));

	stnode_free(yymsp[-2].minor.yy0);
	stnode_free(yymsp[0].minor.yy0);
}
#line 1219 "./grammar.c"
  yy_destructor(yypParser,22,&yymsp[-1].minor);
  yymsp[-2].minor.yy85 = yylhsminor.yy85;
        break;
      case 21: /* drnode ::= COLON INTEGER */
{  yy_destructor(yypParser,21,&yymsp[-1].minor);
#line 235 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{
	yymsp[-1].minor.yy85 = drange_node_new();
	drange_node_set_start_offset(yymsp[-1].minor.yy85, 0);
	drange_node_set_length(yymsp[-1].minor.yy85, stnode_value(yymsp[0].minor.yy0));

	stnode_free(yymsp[0].minor.yy0);
}
#line 1233 "./grammar.c"
}
        break;
      case 22: /* drnode ::= INTEGER COLON */
#line 245 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{
	yylhsminor.yy85 = drange_node_new();
	drange_node_set_start_offset(yylhsminor.yy85, stnode_value(yymsp[-1].minor.yy0));
	drange_node_set_to_the_end(yylhsminor.yy85);

	stnode_free(yymsp[-1].minor.yy0);
}
#line 1245 "./grammar.c"
  yy_destructor(yypParser,21,&yymsp[0].minor);
  yymsp[-1].minor.yy85 = yylhsminor.yy85;
        break;
      case 23: /* drnode ::= INTEGER */
#line 255 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{
	yylhsminor.yy85 = drange_node_new();
	drange_node_set_start_offset(yylhsminor.yy85, stnode_value(yymsp[0].minor.yy0));
	drange_node_set_length(yylhsminor.yy85, 1);

	stnode_free(yymsp[0].minor.yy0);
}
#line 1258 "./grammar.c"
  yymsp[0].minor.yy85 = yylhsminor.yy85;
        break;
      case 24: /* relation_test ::= entity rel_op2 entity */
#line 267 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{
	yylhsminor.yy0 = stnode_new(STTYPE_TEST, NULL);
	sttype_test_set2(yylhsminor.yy0, yymsp[-1].minor.yy24, yymsp[-2].minor.yy0, yymsp[0].minor.yy0);
}
#line 1267 "./grammar.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 25: /* relation_test ::= entity rel_op2 relation_test */
#line 274 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{
	stnode_t *L, *F;
	/* for now generate it like yymsp[-2].minor.yy0 yymsp[-1].minor.yy24 F  TEST_OP_AND  F P G, later it could be optimized
	   or semantically checked (to make a <= b >= c or a == b != c invalid)?
	 */

	F = yymsp[0].minor.yy0;
	do {
		g_assert(F != NULL && stnode_type_id(F) == STTYPE_TEST);
		sttype_test_get(F, NULL, &F, NULL);
	} while (stnode_type_id(F) == STTYPE_TEST);

	L = stnode_new(STTYPE_TEST, NULL);
	sttype_test_set2(L, yymsp[-1].minor.yy24, yymsp[-2].minor.yy0, stnode_dup(F));

	yylhsminor.yy0 = stnode_new(STTYPE_TEST, NULL);
	sttype_test_set2(yylhsminor.yy0, TEST_OP_AND, L, yymsp[0].minor.yy0);
}
#line 1290 "./grammar.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 26: /* rel_op2 ::= TEST_EQ */
{  yy_destructor(yypParser,3,&yymsp[0].minor);
#line 293 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{ yymsp[0].minor.yy24 = TEST_OP_EQ; }
#line 1297 "./grammar.c"
}
        break;
      case 27: /* rel_op2 ::= TEST_NE */
{  yy_destructor(yypParser,4,&yymsp[0].minor);
#line 294 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{ yymsp[0].minor.yy24 = TEST_OP_NE; }
#line 1304 "./grammar.c"
}
        break;
      case 28: /* rel_op2 ::= TEST_GT */
{  yy_destructor(yypParser,7,&yymsp[0].minor);
#line 295 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{ yymsp[0].minor.yy24 = TEST_OP_GT; }
#line 1311 "./grammar.c"
}
        break;
      case 29: /* rel_op2 ::= TEST_GE */
{  yy_destructor(yypParser,8,&yymsp[0].minor);
#line 296 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{ yymsp[0].minor.yy24 = TEST_OP_GE; }
#line 1318 "./grammar.c"
}
        break;
      case 30: /* rel_op2 ::= TEST_LT */
{  yy_destructor(yypParser,5,&yymsp[0].minor);
#line 297 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{ yymsp[0].minor.yy24 = TEST_OP_LT; }
#line 1325 "./grammar.c"
}
        break;
      case 31: /* rel_op2 ::= TEST_LE */
{  yy_destructor(yypParser,6,&yymsp[0].minor);
#line 298 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{ yymsp[0].minor.yy24 = TEST_OP_LE; }
#line 1332 "./grammar.c"
}
        break;
      case 32: /* rel_op2 ::= TEST_BITWISE_AND */
{  yy_destructor(yypParser,11,&yymsp[0].minor);
#line 299 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{ yymsp[0].minor.yy24 = TEST_OP_BITWISE_AND; }
#line 1339 "./grammar.c"
}
        break;
      case 33: /* rel_op2 ::= TEST_CONTAINS */
{  yy_destructor(yypParser,9,&yymsp[0].minor);
#line 300 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{ yymsp[0].minor.yy24 = TEST_OP_CONTAINS; }
#line 1346 "./grammar.c"
}
        break;
      case 34: /* rel_op2 ::= TEST_MATCHES */
{  yy_destructor(yypParser,10,&yymsp[0].minor);
#line 301 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{ yymsp[0].minor.yy24 = TEST_OP_MATCHES; }
#line 1353 "./grammar.c"
}
        break;
      case 35: /* relation_test ::= entity TEST_IN LBRACE setnode_list RBRACE */
#line 304 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{
	stnode_t *S;
	yylhsminor.yy0 = stnode_new(STTYPE_TEST, NULL);
	S = stnode_new(STTYPE_SET, yymsp[-1].minor.yy17);
	sttype_test_set2(yylhsminor.yy0, TEST_OP_IN, yymsp[-4].minor.yy0, S);
}
#line 1364 "./grammar.c"
  yy_destructor(yypParser,23,&yymsp[-3].minor);
  yy_destructor(yypParser,24,&yymsp[-2].minor);
  yy_destructor(yypParser,25,&yymsp[0].minor);
  yymsp[-4].minor.yy0 = yylhsminor.yy0;
        break;
      case 36: /* setnode_list ::= entity */
#line 312 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{
	yylhsminor.yy17 = g_slist_append(NULL, yymsp[0].minor.yy0);
	yylhsminor.yy17 = g_slist_append(yylhsminor.yy17, NULL);
}
#line 1376 "./grammar.c"
  yymsp[0].minor.yy17 = yylhsminor.yy17;
        break;
      case 37: /* setnode_list ::= setnode_list WHITESPACE entity */
#line 318 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{
	yylhsminor.yy17 = g_slist_append(yymsp[-2].minor.yy17, yymsp[0].minor.yy0);
	yylhsminor.yy17 = g_slist_append(yylhsminor.yy17, NULL);
}
#line 1385 "./grammar.c"
  yy_destructor(yypParser,26,&yymsp[-1].minor);
  yymsp[-2].minor.yy17 = yylhsminor.yy17;
        break;
      case 38: /* setnode_list ::= entity DOTDOT entity */
#line 325 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{
	yylhsminor.yy17 = g_slist_append(NULL, yymsp[-2].minor.yy0);
	yylhsminor.yy17 = g_slist_append(yylhsminor.yy17, yymsp[0].minor.yy0);
}
#line 1395 "./grammar.c"
  yy_destructor(yypParser,27,&yymsp[-1].minor);
  yymsp[-2].minor.yy17 = yylhsminor.yy17;
        break;
      case 39: /* setnode_list ::= setnode_list WHITESPACE entity DOTDOT entity */
#line 331 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{
	yylhsminor.yy17 = g_slist_append(yymsp[-4].minor.yy17, yymsp[-2].minor.yy0);
	yylhsminor.yy17 = g_slist_append(yylhsminor.yy17, yymsp[0].minor.yy0);
}
#line 1405 "./grammar.c"
  yy_destructor(yypParser,26,&yymsp[-3].minor);
  yy_destructor(yypParser,27,&yymsp[-1].minor);
  yymsp[-4].minor.yy17 = yylhsminor.yy17;
        break;
      case 40: /* entity ::= FUNCTION LPAREN funcparams RPAREN */
#line 340 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{
	yylhsminor.yy0 = yymsp[-3].minor.yy0;
	sttype_function_set_params(yylhsminor.yy0, yymsp[-1].minor.yy17);
}
#line 1416 "./grammar.c"
  yy_destructor(yypParser,29,&yymsp[-2].minor);
  yy_destructor(yypParser,30,&yymsp[0].minor);
  yymsp[-3].minor.yy0 = yylhsminor.yy0;
        break;
      case 41: /* entity ::= FUNCTION LPAREN RPAREN */
#line 347 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{
	yylhsminor.yy0 = yymsp[-2].minor.yy0;
}
#line 1426 "./grammar.c"
  yy_destructor(yypParser,29,&yymsp[-1].minor);
  yy_destructor(yypParser,30,&yymsp[0].minor);
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 42: /* funcparams ::= entity */
#line 352 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{
	yylhsminor.yy17 = g_slist_append(NULL, yymsp[0].minor.yy0);
}
#line 1436 "./grammar.c"
  yymsp[0].minor.yy17 = yylhsminor.yy17;
        break;
      case 43: /* funcparams ::= funcparams COMMA entity */
#line 357 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{
	yylhsminor.yy17 = g_slist_append(yymsp[-2].minor.yy17, yymsp[0].minor.yy0);
}
#line 1444 "./grammar.c"
  yy_destructor(yypParser,19,&yymsp[-1].minor);
  yymsp[-2].minor.yy17 = yylhsminor.yy17;
        break;
      case 44: /* expr ::= LPAREN expr RPAREN */
{  yy_destructor(yypParser,29,&yymsp[-2].minor);
#line 364 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"
{
	yymsp[-2].minor.yy0 = yymsp[-1].minor.yy0;
	stnode_set_bracket(yymsp[-2].minor.yy0, TRUE);
}
#line 1455 "./grammar.c"
  yy_destructor(yypParser,30,&yymsp[0].minor);
}
        break;
      default:
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
  DfilterARG_FETCH
  DfilterCTX_FETCH
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
/************ Begin %parse_failure code ***************************************/
#line 131 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"

	dfw->syntax_error = TRUE;
#line 1504 "./grammar.c"
/************ End %parse_failure code *****************************************/
  DfilterARG_STORE /* Suppress warning about unused %extra_argument variable */
  DfilterCTX_STORE
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor _U_,               /* The major type of the error token */
  DfilterTOKENTYPE yyminor         /* The minor type of the error token */
){
  DfilterARG_FETCH
  DfilterCTX_FETCH
#define TOKEN yyminor
/************ Begin %syntax_error code ****************************************/
#line 70 "/root/CLionProjects/tshark/epan/dfilter/grammar.lemon"


	header_field_info	*hfinfo;

	if (!TOKEN) {
		dfilter_fail(dfw, "Unexpected end of filter string.");
		dfw->syntax_error = TRUE;
		return;
	}

	switch(stnode_type_id(TOKEN)) {
		case STTYPE_UNINITIALIZED:
			dfilter_fail(dfw, "Syntax error.");
			break;
		case STTYPE_TEST:
			dfilter_fail(dfw, "Syntax error, TEST.");
			break;
		case STTYPE_STRING:
			dfilter_fail(dfw, "The string \"%s\" was unexpected in this context.",
				(char *)stnode_data(TOKEN));
			break;
		case STTYPE_CHARCONST:
			dfilter_fail(dfw, "The character constant \"%s\" was unexpected in this context.",
				(char *)stnode_data(TOKEN));
			break;
		case STTYPE_UNPARSED:
			dfilter_fail(dfw, "\"%s\" was unexpected in this context.",
				(char *)stnode_data(TOKEN));
			break;
		case STTYPE_INTEGER:
			dfilter_fail(dfw, "The integer %d was unexpected in this context.",
				stnode_value(TOKEN));
			break;
		case STTYPE_FIELD:
			hfinfo = (header_field_info *)stnode_data(TOKEN);
			dfilter_fail(dfw, "Syntax error near \"%s\".", hfinfo->abbrev);
			break;
		case STTYPE_FUNCTION:
			dfilter_fail(dfw, "The function \"%s\" was unexpected in this context.",
				sttype_function_funcdef(TOKEN)->name);
			break;
		case STTYPE_SET:
			dfilter_fail(dfw, "Syntax error, SET.");
			break;

		/* These aren't handed to use as terminal tokens from
		   the scanner, so was can assert that we'll never
		   see them here. */
		case STTYPE_NUM_TYPES:
		case STTYPE_RANGE:
		case STTYPE_FVALUE:
			g_assert_not_reached();
			break;
	}
	dfw->syntax_error = TRUE;
#line 1579 "./grammar.c"
/************ End %syntax_error code ******************************************/
  DfilterARG_STORE /* Suppress warning about unused %extra_argument variable */
  DfilterCTX_STORE
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  DfilterARG_FETCH
  DfilterCTX_FETCH
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
  DfilterARG_STORE /* Suppress warning about unused %extra_argument variable */
  DfilterCTX_STORE
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "DfilterAlloc" which describes the current state of the parser.
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
void Dfilter(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  DfilterTOKENTYPE yyminor       /* The value for the token */
  DfilterARG_PDECL               /* Optional %extra_argument parameter */
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
  DfilterCTX_FETCH
  DfilterARG_STORE

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
                        yyminor DfilterCTX_PARAM);
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
int DfilterFallback(int iToken){
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
