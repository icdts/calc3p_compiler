/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INTEGER = 258,
     FLOAT = 259,
     VARIABLE = 260,
     TYPE = 261,
     DO = 262,
     UNTIL = 263,
     WHILE = 264,
     IF = 265,
     PRINT = 266,
     FOR = 267,
     STEP = 268,
     TO = 269,
     COMMENT = 270,
     PROG = 271,
     PROC = 272,
     FUNC = 273,
     CALL = 274,
     ARGS = 275,
     IFX = 276,
     ELSE = 277,
     PROC_STMT = 278,
     PROC_ARG_STMT = 279,
     NE = 280,
     EQ = 281,
     LE = 282,
     GE = 283,
     ModE = 284,
     DivE = 285,
     MulE = 286,
     MinE = 287,
     PluE = 288,
     UMINUS = 289
   };
#endif
/* Tokens.  */
#define INTEGER 258
#define FLOAT 259
#define VARIABLE 260
#define TYPE 261
#define DO 262
#define UNTIL 263
#define WHILE 264
#define IF 265
#define PRINT 266
#define FOR 267
#define STEP 268
#define TO 269
#define COMMENT 270
#define PROG 271
#define PROC 272
#define FUNC 273
#define CALL 274
#define ARGS 275
#define IFX 276
#define ELSE 277
#define PROC_STMT 278
#define PROC_ARG_STMT 279
#define NE 280
#define EQ 281
#define LE 282
#define GE 283
#define ModE 284
#define DivE 285
#define MulE 286
#define MinE 287
#define PluE 288
#define UMINUS 289




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 30 "yacc.y"

    int iValue;                 /* integer value */
	float fValue;				/* float value */
    char sIndex;                /* symbol table index */
	int iType;					/* Type enum */
    nodeType *nPtr;             /* node pointer */



/* Line 2068 of yacc.c  */
#line 128 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


