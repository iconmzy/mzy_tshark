/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_PROTOBUF_LANG_HOME_YMQ_TSHARK_CMAKE_BUILD_DEBUG_EPAN_PROTOBUF_LANG_H_INCLUDED
# define YY_PROTOBUF_LANG_HOME_YMQ_TSHARK_CMAKE_BUILD_DEBUG_EPAN_PROTOBUF_LANG_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int protobuf_langdebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    PT_QUOTE = 258,
    PT_LPAREN = 259,
    PT_RPAREN = 260,
    PT_LBRACKET = 261,
    PT_RBRACKET = 262,
    PT_LCURLY = 263,
    PT_RCURLY = 264,
    PT_EQUAL = 265,
    PT_NOTEQUAL = 266,
    PT_NOTEQUAL2 = 267,
    PT_GEQUAL = 268,
    PT_LEQUAL = 269,
    PT_ASSIGN_PLUS = 270,
    PT_ASSIGN = 271,
    PT_PLUS = 272,
    PT_MINUS = 273,
    PT_MULTIPLY = 274,
    PT_DIV = 275,
    PT_LOGIC_OR = 276,
    PT_OR = 277,
    PT_LOGIC_AND = 278,
    PT_AND = 279,
    PT_NOT = 280,
    PT_NEG = 281,
    PT_XOR = 282,
    PT_SHL = 283,
    PT_SHR = 284,
    PT_PERCENT = 285,
    PT_DOLLAR = 286,
    PT_COND = 287,
    PT_SEMICOLON = 288,
    PT_DOT = 289,
    PT_COMMA = 290,
    PT_COLON = 291,
    PT_LESS = 292,
    PT_GREATER = 293,
    PT_SYNTAX = 294,
    PT_IMPORT = 295,
    PT_WEAK = 296,
    PT_PUBLIC = 297,
    PT_PACKAGE = 298,
    PT_OPTION = 299,
    PT_REQUIRED = 300,
    PT_OPTIONAL = 301,
    PT_REPEATED = 302,
    PT_ONEOF = 303,
    PT_MAP = 304,
    PT_RESERVED = 305,
    PT_ENUM = 306,
    PT_GROUP = 307,
    PT_EXTEND = 308,
    PT_EXTENSIONS = 309,
    PT_MESSAGE = 310,
    PT_SERVICE = 311,
    PT_RPC = 312,
    PT_STREAM = 313,
    PT_RETURNS = 314,
    PT_TO = 315,
    PT_PROTO2 = 316,
    PT_PROTO3 = 317,
    PT_IDENT = 318,
    PT_STRLIT = 319,
    PT_DECIMALLIT = 320,
    PT_OCTALLIT = 321,
    PT_HEXLIT = 322
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 91 "/home/ymq/tshark/cmake-build-debug/epan/protobuf_lang.y" /* yacc.c:1909  */

    char* sval;
    pbl_node_t* node;
    int ival;
    guint64 u64val;

#line 129 "/home/ymq/tshark/cmake-build-debug/epan/protobuf_lang.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int protobuf_langparse (void *yyscanner, protobuf_lang_state_t *state);

#endif /* !YY_PROTOBUF_LANG_HOME_YMQ_TSHARK_CMAKE_BUILD_DEBUG_EPAN_PROTOBUF_LANG_H_INCLUDED  */
