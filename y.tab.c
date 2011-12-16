/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "yacc.y"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "calc3.h"
#define YYDEBUG 1
#define YYERROR_VERBOSE 1
/* prototypes */
nodeType *opr(int oper, int nops, ...);
nodeType *id(int i);
nodeType *proc(int i);
nodeType *iCon(int value);
nodeType *fCon(float value);
nodeType *defVar(int type, int var);
nodeType *defProcParam(int type, int var, nodeType* params);
void freeNode(nodeType *p);
int ex(nodeType *p);
int yylex(void);
void print_all();

void yyerror(const char *s);

variable *sym[99];                    /* symbol table */
variable *proc_sym[99];
nodeType * top;
int proc_var_count;
int inside_procedure;


/* Line 268 of yacc.c  */
#line 101 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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
     FUNC_STMT = 280,
     FUNC_ARG_STMT = 281,
     NE = 282,
     EQ = 283,
     LE = 284,
     GE = 285,
     ModE = 286,
     DivE = 287,
     MulE = 288,
     MinE = 289,
     PluE = 290,
     RETURN = 291,
     UMINUS = 292
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
#define FUNC_STMT 280
#define FUNC_ARG_STMT 281
#define NE 282
#define EQ 283
#define LE 284
#define GE 285
#define ModE 286
#define DivE 287
#define MulE 288
#define MinE 289
#define PluE 290
#define RETURN 291
#define UMINUS 292




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 30 "yacc.y"

    int iValue;                 /* integer value */
	float fValue;				/* float value */
    char sIndex;                /* symbol table index */
	int iType;					/* Type enum */
    nodeType *nPtr;             /* node pointer */



/* Line 293 of yacc.c  */
#line 221 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 233 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  44
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   534

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  9
/* YYNRULES -- Number of rules.  */
#define YYNRULES  52
/* YYNRULES -- Number of states.  */
#define YYNSTATES  147

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    37,     2,     2,
      45,    46,    35,    33,    49,    34,     2,    36,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    50,
      28,    51,    27,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    47,     2,    48,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    29,    30,    31,    32,    38,    39,    40,    41,
      42,    43,    44
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    17,    27,    37,    48,    49,
      52,    57,    60,    62,    64,    67,    70,    74,    79,    84,
      89,    94,    99,   104,   110,   117,   124,   136,   142,   150,
     154,   158,   160,   164,   166,   169,   171,   173,   175,   178,
     182,   186,   190,   194,   198,   202,   206,   210,   214,   218,
     222,   226,   230
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      53,     0,    -1,    54,    -1,    57,    54,    -1,    17,     5,
      45,    46,    47,    57,    48,    54,    -1,    17,     5,    45,
      55,    46,    47,    57,    48,    54,    -1,    18,     6,     5,
      45,    46,    47,    57,    48,    54,    -1,    18,     6,     5,
      45,    55,    46,    47,    57,    48,    54,    -1,    -1,     6,
       5,    -1,     6,     5,    49,    55,    -1,     6,     5,    -1,
      50,    -1,    15,    -1,    60,    50,    -1,    56,    50,    -1,
      11,    60,    50,    -1,     5,    51,    60,    50,    -1,     5,
      42,    60,    50,    -1,     5,    41,    60,    50,    -1,     5,
      40,    60,    50,    -1,     5,    39,    60,    50,    -1,     5,
      38,    60,    50,    -1,     9,    45,    60,    46,    57,    -1,
       7,    57,     9,    45,    60,    46,    -1,     7,    57,     8,
      45,    60,    46,    -1,    12,    45,     5,    51,    60,    13,
      60,    14,    60,    46,    57,    -1,    10,    45,    60,    46,
      57,    -1,    10,    45,    60,    46,    57,    22,    57,    -1,
      47,    59,    48,    -1,    43,    60,    50,    -1,    60,    -1,
      60,    49,    58,    -1,    57,    -1,    59,    57,    -1,     3,
      -1,     4,    -1,     5,    -1,    34,    60,    -1,    60,    33,
      60,    -1,    60,    34,    60,    -1,    60,    35,    60,    -1,
      60,    36,    60,    -1,    60,    28,    60,    -1,    60,    27,
      60,    -1,    60,    37,    60,    -1,    60,    32,    60,    -1,
      60,    31,    60,    -1,    60,    29,    60,    -1,    60,    30,
      60,    -1,    45,    60,    46,    -1,     5,    45,    46,    -1,
       5,    45,    58,    46,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    62,    62,    66,    67,    71,    75,    79,    83,    86,
      87,    90,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   114,   115,   118,   119,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "FLOAT", "VARIABLE", "TYPE",
  "DO", "UNTIL", "WHILE", "IF", "PRINT", "FOR", "STEP", "TO", "COMMENT",
  "PROG", "PROC", "FUNC", "CALL", "ARGS", "IFX", "ELSE", "PROC_STMT",
  "PROC_ARG_STMT", "FUNC_STMT", "FUNC_ARG_STMT", "'>'", "'<'", "NE", "EQ",
  "LE", "GE", "'+'", "'-'", "'*'", "'/'", "'%'", "ModE", "DivE", "MulE",
  "MinE", "PluE", "RETURN", "UMINUS", "'('", "')'", "'{'", "'}'", "','",
  "';'", "'='", "$accept", "program", "function", "param_list", "def_var",
  "stmt", "arg_list", "stmt_list", "expr", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,    62,    60,   282,
     283,   284,   285,    43,    45,    42,    47,    37,   286,   287,
     288,   289,   290,   291,   292,    40,    41,   123,   125,    44,
      59,    61
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    52,    53,    54,    54,    54,    54,    54,    54,    55,
      55,    56,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    58,    58,    59,    59,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     8,     9,     9,    10,     0,     2,
       4,     2,     1,     1,     2,     2,     3,     4,     4,     4,
       4,     4,     4,     5,     6,     6,    11,     5,     7,     3,
       3,     1,     3,     1,     2,     1,     1,     1,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     4
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       8,    35,    36,    37,     0,     0,     0,     0,     0,     0,
      13,     0,     0,     0,     0,     0,     0,    12,     0,     2,
       0,     8,     0,     0,     0,     0,     0,     0,     0,     0,
      11,     0,     0,     0,    37,     0,     0,     0,     0,    38,
       0,     0,    33,     0,     1,    15,     3,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    14,     0,
       0,     0,     0,     0,    51,     0,    31,     0,     0,     0,
       0,     0,    16,     0,     0,     0,    30,    50,    29,    34,
      44,    43,    48,    49,    47,    46,    39,    40,    41,    42,
      45,    22,    21,    20,    19,    18,    52,     0,    17,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    32,     0,
       0,    23,    27,     0,     9,     0,     0,     0,     0,    25,
      24,     0,     0,     0,     0,     0,     0,     0,    28,     0,
      10,     8,     0,     0,     0,     0,     4,     8,     8,     0,
       0,     5,     6,     8,     0,     7,    26
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    18,    19,   106,    20,    21,    65,    43,    22
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -107
static const yytype_int16 yypact[] =
{
     137,  -107,  -107,    22,     3,   202,   -35,   -22,    36,   -14,
    -107,    27,    39,    36,    36,    36,   202,  -107,    42,  -107,
      -4,   137,   191,    36,    36,    36,    36,    36,    32,    36,
    -107,     4,    36,    36,     2,   226,    54,    20,    64,  -107,
     237,   388,  -107,   154,  -107,  -107,  -107,    36,    36,    36,
      36,    36,    36,    36,    36,    36,    36,    36,  -107,   261,
     272,   296,   307,   331,  -107,    25,   377,   342,    29,    30,
     408,   428,  -107,    21,    -3,    31,  -107,  -107,  -107,  -107,
     -15,   -15,   -15,   -15,   -15,   -15,   -30,   -30,  -107,  -107,
    -107,  -107,  -107,  -107,  -107,  -107,  -107,    36,  -107,    36,
      36,   202,   202,    36,    74,    33,    47,    -2,  -107,   448,
     468,  -107,    72,    55,    46,   202,    52,    56,    59,  -107,
    -107,   202,    36,    96,    58,   202,   202,    60,  -107,   366,
    -107,   137,    61,    63,   202,    36,  -107,   137,   137,    65,
     488,  -107,  -107,   137,   202,  -107,  -107
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -107,  -107,   -19,  -106,  -107,    -5,    11,  -107,     1
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      31,   118,    46,   104,   104,    55,    56,    57,    30,    35,
      32,    42,    68,    69,    39,    40,    41,   130,    53,    54,
      55,    56,    57,    33,    59,    60,    61,    62,    63,    66,
      67,    36,    37,    70,    71,     1,     2,    34,    79,     1,
       2,    34,    44,   105,   117,    38,    45,    28,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    73,
      23,    24,    25,    26,    27,    74,    13,    28,   122,    75,
      13,    96,   103,    29,    99,   100,   107,    15,    64,   114,
     115,    15,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,   116,   121,   123,   111,   112,    66,   125,
     109,   110,   104,   126,   113,   127,   131,   134,   108,   137,
     124,   138,   136,   143,     0,     0,   128,     0,   141,   142,
     132,   133,     0,   129,   145,     0,     0,     0,     0,   139,
       0,     0,     0,     0,     0,     0,   140,     0,     0,   146,
       1,     2,     3,     4,     5,     0,     6,     7,     8,     9,
       0,     0,    10,     0,    11,    12,     0,     1,     2,     3,
       4,     5,     0,     6,     7,     8,     9,     0,     0,    10,
       0,    13,     0,     0,     0,     0,     0,     0,     0,     0,
      14,     0,    15,     0,    16,     0,     0,    17,    13,     0,
       0,     0,     0,     0,     0,     0,     0,    14,     0,    15,
       0,    16,    78,     0,    17,     1,     2,     3,     4,     5,
       0,     6,     7,     8,     9,     0,     0,    10,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,     0,
       0,     0,     0,     0,     0,     0,    13,     0,     0,     0,
       0,    58,     0,     0,     0,    14,     0,    15,     0,    16,
       0,     0,    17,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,     0,    72,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    76,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
       0,    91,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    92,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,     0,    93,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    94,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
     135,    95,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    98,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    97,     0,     0,     0,
       0,     0,     0,     0,    77,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,     0,     0,     0,     0,
       0,     0,     0,     0,   101,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,     0,     0,     0,     0,
       0,     0,     0,     0,   102,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,     0,     0,     0,     0,
       0,     0,     0,     0,   119,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,     0,     0,     0,     0,
       0,     0,     0,     0,   120,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,     0,     0,     0,     0,
       0,     0,     0,     0,   144
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-107))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       5,   107,    21,     6,     6,    35,    36,    37,     5,     8,
      45,    16,     8,     9,    13,    14,    15,   123,    33,    34,
      35,    36,    37,    45,    23,    24,    25,    26,    27,    28,
      29,    45,     5,    32,    33,     3,     4,     5,    43,     3,
       4,     5,     0,    46,    46,     6,    50,    45,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,     5,
      38,    39,    40,    41,    42,    45,    34,    45,    13,     5,
      34,    46,    51,    51,    45,    45,    45,    45,    46,     5,
      47,    45,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    46,    22,    49,   101,   102,    97,    47,
      99,   100,     6,    47,   103,    46,    48,    47,    97,    48,
     115,    48,   131,    48,    -1,    -1,   121,    -1,   137,   138,
     125,   126,    -1,   122,   143,    -1,    -1,    -1,    -1,   134,
      -1,    -1,    -1,    -1,    -1,    -1,   135,    -1,    -1,   144,
       3,     4,     5,     6,     7,    -1,     9,    10,    11,    12,
      -1,    -1,    15,    -1,    17,    18,    -1,     3,     4,     5,
       6,     7,    -1,     9,    10,    11,    12,    -1,    -1,    15,
      -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    -1,    45,    -1,    47,    -1,    -1,    50,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,    45,
      -1,    47,    48,    -1,    50,     3,     4,     5,     6,     7,
      -1,     9,    10,    11,    12,    -1,    -1,    15,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    -1,
      -1,    50,    -1,    -1,    -1,    43,    -1,    45,    -1,    47,
      -1,    -1,    50,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      14,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    46
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     9,    10,    11,    12,
      15,    17,    18,    34,    43,    45,    47,    50,    53,    54,
      56,    57,    60,    38,    39,    40,    41,    42,    45,    51,
       5,    57,    45,    45,     5,    60,    45,     5,     6,    60,
      60,    60,    57,    59,     0,    50,    54,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    50,    60,
      60,    60,    60,    60,    46,    58,    60,    60,     8,     9,
      60,    60,    50,     5,    45,     5,    50,    46,    48,    57,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    50,    50,    50,    50,    50,    46,    49,    50,    45,
      45,    46,    46,    51,     6,    46,    55,    45,    58,    60,
      60,    57,    57,    60,     5,    47,    46,    46,    55,    46,
      46,    22,    13,    49,    57,    47,    47,    46,    57,    60,
      55,    48,    57,    57,    47,    14,    54,    48,    48,    57,
      60,    54,    54,    48,    46,    54,    57
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 62 "yacc.y"
    { top = opr(PROG,1,(yyvsp[(1) - (1)].nPtr)); ex(top); freeNode(top); print_all(); exit(0); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 66 "yacc.y"
    { (yyval.nPtr) = opr(';', 2, (yyvsp[(1) - (2)].nPtr), (yyvsp[(2) - (2)].nPtr)); }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 67 "yacc.y"
    { 
																			(yyval.nPtr) = opr(PROC, 3, proc((yyvsp[(2) - (8)].sIndex)), (yyvsp[(6) - (8)].nPtr), (yyvsp[(8) - (8)].nPtr)); 
																			inside_procedure = 0;
																		}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 71 "yacc.y"
    { 
																							(yyval.nPtr) = opr(PROC, 4, proc((yyvsp[(2) - (9)].sIndex)), (yyvsp[(7) - (9)].nPtr), (yyvsp[(9) - (9)].nPtr), (yyvsp[(4) - (9)].nPtr)); 
																							inside_procedure = 0; 
																						}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 75 "yacc.y"
    {
																				(yyval.nPtr) = opr(FUNC, 4, iCon((yyvsp[(2) - (9)].iType)), proc((yyvsp[(3) - (9)].sIndex)), (yyvsp[(7) - (9)].nPtr), (yyvsp[(9) - (9)].nPtr)); 
																				inside_procedure = 0;
																			}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 79 "yacc.y"
    {
																								(yyval.nPtr) = opr(FUNC, 5, iCon((yyvsp[(2) - (10)].iType)), proc((yyvsp[(3) - (10)].sIndex)), (yyvsp[(8) - (10)].nPtr), (yyvsp[(10) - (10)].nPtr), (yyvsp[(5) - (10)].nPtr));
																								inside_procedure = 0;
																							}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 83 "yacc.y"
    { (yyval.nPtr) = opr(';', 2, NULL, NULL); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 86 "yacc.y"
    { (yyval.nPtr) = defProcParam((yyvsp[(1) - (2)].iType),(yyvsp[(2) - (2)].sIndex),NULL); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 87 "yacc.y"
    { (yyval.nPtr) = defProcParam((yyvsp[(1) - (4)].iType),(yyvsp[(2) - (4)].sIndex),(yyvsp[(4) - (4)].nPtr)); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 90 "yacc.y"
    { (yyval.nPtr) = defVar((yyvsp[(1) - (2)].iType),(yyvsp[(2) - (2)].sIndex)); }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 93 "yacc.y"
    { (yyval.nPtr) = opr(';', 2, NULL, NULL); }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 94 "yacc.y"
    { (yyval.nPtr) = opr('c', 0); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 95 "yacc.y"
    { (yyval.nPtr) = (yyvsp[(1) - (2)].nPtr); }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 96 "yacc.y"
    { (yyval.nPtr) = (yyvsp[(1) - (2)].nPtr); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 97 "yacc.y"
    { (yyval.nPtr) = opr(PRINT, 1, (yyvsp[(2) - (3)].nPtr)); }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 98 "yacc.y"
    { (yyval.nPtr) = opr('=', 2, id((yyvsp[(1) - (4)].sIndex)), (yyvsp[(3) - (4)].nPtr)); }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 99 "yacc.y"
    { (yyval.nPtr) = opr(PluE, 2, id((yyvsp[(1) - (4)].sIndex)), (yyvsp[(3) - (4)].nPtr)); }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 100 "yacc.y"
    { (yyval.nPtr) = opr(MinE, 2, id((yyvsp[(1) - (4)].sIndex)), (yyvsp[(3) - (4)].nPtr)); }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 101 "yacc.y"
    { (yyval.nPtr) = opr(MulE, 2, id((yyvsp[(1) - (4)].sIndex)), (yyvsp[(3) - (4)].nPtr)); }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 102 "yacc.y"
    { (yyval.nPtr) = opr(DivE, 2, id((yyvsp[(1) - (4)].sIndex)), (yyvsp[(3) - (4)].nPtr)); }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 103 "yacc.y"
    { (yyval.nPtr) = opr(ModE, 2, id((yyvsp[(1) - (4)].sIndex)), (yyvsp[(3) - (4)].nPtr)); }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 104 "yacc.y"
    { (yyval.nPtr) = opr(WHILE, 2, (yyvsp[(3) - (5)].nPtr), (yyvsp[(5) - (5)].nPtr)); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 105 "yacc.y"
    { (yyval.nPtr) = opr(DO, 2, (yyvsp[(2) - (6)].nPtr), (yyvsp[(5) - (6)].nPtr)); }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 106 "yacc.y"
    { (yyval.nPtr) = opr(UNTIL, 2, (yyvsp[(2) - (6)].nPtr), (yyvsp[(5) - (6)].nPtr)); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 107 "yacc.y"
    { (yyval.nPtr) = opr(FOR, 5, id((yyvsp[(3) - (11)].sIndex)),(yyvsp[(5) - (11)].nPtr),(yyvsp[(7) - (11)].nPtr),(yyvsp[(9) - (11)].nPtr),(yyvsp[(11) - (11)].nPtr)); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 108 "yacc.y"
    { (yyval.nPtr) = opr(IF, 2, (yyvsp[(3) - (5)].nPtr), (yyvsp[(5) - (5)].nPtr)); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 109 "yacc.y"
    { (yyval.nPtr) = opr(IF, 3, (yyvsp[(3) - (7)].nPtr), (yyvsp[(5) - (7)].nPtr), (yyvsp[(7) - (7)].nPtr)); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 110 "yacc.y"
    { (yyval.nPtr) = (yyvsp[(2) - (3)].nPtr); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 111 "yacc.y"
    { (yyval.nPtr) = opr(RETURN, 1, (yyvsp[(2) - (3)].nPtr)); }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 114 "yacc.y"
    { (yyval.nPtr) = opr(ARGS,2,(yyvsp[(1) - (1)].nPtr),NULL); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 115 "yacc.y"
    { (yyval.nPtr) = opr(ARGS,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr)); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 118 "yacc.y"
    { (yyval.nPtr) = (yyvsp[(1) - (1)].nPtr); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 119 "yacc.y"
    { (yyval.nPtr) = opr(';', 2, (yyvsp[(1) - (2)].nPtr), (yyvsp[(2) - (2)].nPtr)); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 123 "yacc.y"
    { (yyval.nPtr) = iCon((yyvsp[(1) - (1)].iValue)); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 124 "yacc.y"
    { (yyval.nPtr) = fCon((yyvsp[(1) - (1)].fValue)); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 125 "yacc.y"
    { (yyval.nPtr) = id((yyvsp[(1) - (1)].sIndex)); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 126 "yacc.y"
    { (yyval.nPtr) = opr(UMINUS, 1, (yyvsp[(2) - (2)].nPtr)); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 127 "yacc.y"
    { (yyval.nPtr) = opr('+', 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr)); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 128 "yacc.y"
    { (yyval.nPtr) = opr('-', 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr)); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 129 "yacc.y"
    { (yyval.nPtr) = opr('*', 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr)); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 130 "yacc.y"
    { (yyval.nPtr) = opr('/', 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr)); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 131 "yacc.y"
    { (yyval.nPtr) = opr('<', 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr)); }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 132 "yacc.y"
    { (yyval.nPtr) = opr('>', 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr)); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 133 "yacc.y"
    { (yyval.nPtr) = opr('%', 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr)); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 134 "yacc.y"
    { (yyval.nPtr) = opr(GE, 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr)); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 135 "yacc.y"
    { (yyval.nPtr) = opr(LE, 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr)); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 136 "yacc.y"
    { (yyval.nPtr) = opr(NE, 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr)); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 137 "yacc.y"
    { (yyval.nPtr) = opr(EQ, 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr)); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 138 "yacc.y"
    { (yyval.nPtr) = (yyvsp[(2) - (3)].nPtr); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 139 "yacc.y"
    { (yyval.nPtr) = opr(CALL, 2, proc((yyvsp[(1) - (3)].sIndex)), NULL); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 140 "yacc.y"
    { (yyval.nPtr) = opr(CALL, 2, proc((yyvsp[(1) - (4)].sIndex)), (yyvsp[(3) - (4)].nPtr)); }
    break;



/* Line 1806 of yacc.c  */
#line 2017 "y.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 143 "yacc.y"


#define SIZEOF_NODETYPE ((char *)&p->iCon - (char *)p)



nodeType *iCon(int value) {
    nodeType *p;
    size_t nodeSize;

    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(integerConNodeType);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeIntCon;
    p->iCon.value = value;

    return p;
}

nodeType *fCon(float value) {
    nodeType *p;
    size_t nodeSize;

    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(floatConNodeType);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeFloatCon;
    p->fCon.value = value;

    return p;
}

nodeType *id(int id) {
    nodeType *p;
    size_t nodeSize;

	if( inside_procedure == 0 ){
		if( sym[id] == NULL ){
			yyerror("variable used before definition");
		}

		// allocate node 
		//fprintf(stderr,"id: %d",id);
		//fprintf(stderr,"sym[id]->type: %d",sym[id]->type);
		//fprintf(stderr,"typeIntId: %d",typeIntId);
		if( sym[id]->type == typeIntId ){ 
			nodeSize = SIZEOF_NODETYPE + sizeof(intIdNodeType);
		}else{
			nodeSize = SIZEOF_NODETYPE + sizeof(floatIdNodeType);
		}
		if ((p = malloc(nodeSize)) == NULL)
			yyerror("out of memory");

		/* copy information */
		//fprintf(stderr,"VAR %d has type %d",i,sym[i]->type);
		p->type = sym[id]->type;
		
		if( p->type == typeIntId ){
			p->iId.i = id;
		}else if( p->type == typeFloatId ){
			p->fId.i = id;
			//fprintf(stderr,"Setting fId = %d\n",p->fId.i);
		}else{
			printf("Unkown error");
			exit(1);
		}
	}else{
		int i;
		for(i = 0; i < proc_var_count; i++){
			if(proc_sym != NULL ){
				if(proc_sym[i]->original == id){
					yyerror("param defined twice");
					exit(1);
				}
			}else{
				break;
			}
		}
		if( proc_sym[i] == NULL ){
			yyerror("variable used before definition");
		}

		// allocate node 
		//fprintf(stderr,"i: %d",i);
		//fprintf(stderr,"proc_sym[i]->type: %d",proc_sym[i]->type);
		//fprintf(stderr,"typeIntId: %d",typeIntId);
		if( proc_sym[i]->type == typeIntId ){ 
			nodeSize = SIZEOF_NODETYPE + sizeof(intIdNodeType);
		}else{
			nodeSize = SIZEOF_NODETYPE + sizeof(floatIdNodeType);
		}
		if ((p = malloc(nodeSize)) == NULL)
			yyerror("out of memory");

		/* copy information */
		//fprintf(stderr,"VAR %d has type %d",i,proc_sym[i]->type);
		p->type = proc_sym[i]->type;
		
		if( p->type == typeIntId ){
			p->iId.i = i;
		}else if( p->type == typeFloatId ){
			p->fId.i = i;
			//fprintf(stderr,"Setting fId = %d\n",p->fId.i);
		}else{
			printf("Unkown error");
			exit(1);
		}
	}

    return p;
}

nodeType *proc(int i){
    nodeType *p;
    size_t nodeSize;

	if( sym[i] == NULL ){
		sym[i] = (variable *)malloc(sizeof(variable *));
		sym[i]->type = typeProc;
	}

    // allocate node 
    nodeSize = SIZEOF_NODETYPE + sizeof(intIdNodeType);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeProc;
	
	p->iId.i = i;

	inside_procedure = 1;
	proc_var_count = 0;

    return p;
}

nodeType *defVar(int type, int var){
	if(inside_procedure == 0){
		//fprintf(stderr,"defining variable %d as type %d\n", var, type);
		if( sym[var] == NULL ){
			sym[var] = (variable *)malloc(sizeof(variable *));

			//fprintf(stderr,"Defining %d var as type %d\n",var,type);
			sym[var]->type = type;
		
			return opr('D', 0);
		}else{
			yyerror("variable defined twice.");
			exit(1);
		}
	}else{
		int i;
		for(i = 0; i < proc_var_count; i++){
			if(proc_sym != NULL ){
				if(proc_sym[i]->original == var){
					yyerror("param defined twice");
					exit(1);
				}
			}else{
				break;
			}
		}
		
		proc_sym[proc_var_count] = (variable *)malloc(sizeof(variable));
		proc_sym[proc_var_count]->type = type;
		proc_sym[proc_var_count]->original = var;

		return opr('D',0);
	}
}

nodeType *defProcParam(int type, int var, nodeType* params){
	inside_procedure = 1;
	int i;
	for(i = 0; i < proc_var_count; i++){
		if(proc_sym != NULL ){
			if(proc_sym[i]->original == var){
				yyerror("param defined twice");
				exit(1);
			}
		}else{
			break;
		}
	}
	proc_sym[proc_var_count] = (variable *)malloc(sizeof(variable));
	proc_sym[proc_var_count]->type = type;
	proc_sym[proc_var_count]->original = var;

	return opr('P',3,iCon(var),iCon(type),params);
}

nodeType *opr(int oper, int nops, ...) {
    va_list ap;
    nodeType *p;
    size_t nodeSize;
    int i;

    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(oprNodeType) +
        (nops - 1) * sizeof(nodeType*);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeOpr;
    p->opr.oper = oper;
    p->opr.nops = nops;
    va_start(ap, nops);
    for (i = 0; i < nops; i++)
        p->opr.op[i] = va_arg(ap, nodeType*);
    va_end(ap);
    return p;
}

void freeNode(nodeType *p) {
    int i;

    if (!p) return;
    if (p->type == typeOpr) {
        for (i = 0; i < p->opr.nops; i++)
            freeNode(p->opr.op[i]);
    }
    free (p);
}

void yyerror(const char *s) {
    fprintf(stdout, "%s\n", s);
}

int main(int argc, char **argv){
	if(argc > 1){
		stdin = fopen(argv[1],"r"); 
	}
    yyparse();

	if(argc > 1){
		fclose(stdin);
	}
    return 0;
}

