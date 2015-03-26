/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7.12-4996"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "parser.ypp"

#include <bits/stdc++.h>
#include "AST.h"
using namespace std;

int yylex();
int yyerror(const char *p) { cerr << "Error!" << endl; }


/* Line 371 of yacc.c  */
#line 78 "parser.tab.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.hpp".  */
#ifndef YY_YY_PARSER_TAB_HPP_INCLUDED
# define YY_YY_PARSER_TAB_HPP_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ASOP = 258,
     EQOP = 259,
     RELOP = 260,
     CONDOP = 261,
     MINUS = 262,
     PLUS = 263,
     MULT_DIV = 264,
     UMINUS = 265,
     NOTOP = 266,
     TYPE = 267,
     VOID = 268,
     ID = 269,
     STRLIT = 270,
     INTLIT = 271,
     HEXLIT = 272,
     CHARLIT = 273,
     BOOLVAL = 274,
     RET = 275,
     BREAK = 276,
     CONT = 277,
     CLASS = 278,
     OPEN = 279,
     CLOSE = 280,
     IF = 281,
     ELSE = 282,
     FOR = 283,
     END = 284,
     PROGRAM = 285,
     COMMENT = 286,
     COMMA = 287,
     SQOPEN = 288,
     SQCLOSE = 289,
     ROPEN = 290,
     RCLOSE = 291,
     CALLOUT = 292
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 11 "parser.ypp"

    vector<ASTDecl*> *decl_list;
    ASTProgram *program;
    ASTDecl *decl;
    vector<ASTVar*> *field_decl;
    vector< pair<string, string> > *arg_decl;
    ASTBlock *block;
    ASTVarDecl *block_field_decl;
    vector<ASTVar1*> *block_field_name;
    vector<ASTStatement*> *statement;
    ASTStatement *statement_decl;
    ASTExpr* expr;
    ASTLiteral* literal;
    vector<ASTExpr*> *method_call;
    ASTMethodCall2 *callout;
    vector<ASTCalloutArgs*> *callout_args;
    ASTCalloutArgs *callout_arg;

    string *str;


/* Line 387 of yacc.c  */
#line 180 "parser.tab.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

#endif /* !YY_YY_PARSER_TAB_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 208 "parser.tab.cpp"

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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
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
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
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
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   195

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNRULES -- Number of states.  */
#define YYNSTATES  136

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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     9,    10,    13,    16,    23,    30,    34,
      41,    44,    50,    51,    54,    59,    64,    65,    69,    72,
      76,    77,    80,    82,    87,    95,    99,   106,   114,   118,
     121,   124,   126,   127,   129,   130,   133,   135,   140,   143,
     145,   149,   153,   157,   161,   165,   169,   172,   175,   179,
     181,   183,   185,   187,   189,   193,   200,   201,   203,   206,
     210,   212,   214,   215,   217,   219
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      39,     0,    -1,    23,    30,    24,    40,    25,    -1,    -1,
      41,    40,    -1,    12,    42,    -1,    12,    14,    35,    43,
      36,    44,    -1,    13,    14,    35,    43,    36,    44,    -1,
      14,    32,    42,    -1,    14,    33,    16,    34,    32,    42,
      -1,    14,    29,    -1,    14,    33,    16,    34,    29,    -1,
      -1,    12,    14,    -1,    43,    32,    12,    14,    -1,    24,
      45,    47,    25,    -1,    -1,    12,    46,    45,    -1,    14,
      29,    -1,    14,    32,    46,    -1,    -1,    47,    48,    -1,
      54,    -1,    14,     3,    51,    29,    -1,    14,    33,    51,
      34,     3,    51,    29,    -1,    14,    53,    29,    -1,    26,
      35,    51,    36,    44,    50,    -1,    28,    14,     3,    51,
      32,    51,    44,    -1,    20,    49,    29,    -1,    21,    29,
      -1,    22,    29,    -1,    44,    -1,    -1,    51,    -1,    -1,
      27,    44,    -1,    14,    -1,    14,    33,    51,    34,    -1,
      14,    53,    -1,    54,    -1,    51,     8,    51,    -1,    51,
       7,    51,    -1,    51,     9,    51,    -1,    51,     6,    51,
      -1,    51,     5,    51,    -1,    51,     4,    51,    -1,    11,
      51,    -1,     7,    51,    -1,    35,    51,    36,    -1,    52,
      -1,    16,    -1,    17,    -1,    18,    -1,    19,    -1,    35,
      58,    36,    -1,    37,    35,    15,    55,    36,    29,    -1,
      -1,    56,    -1,    32,    57,    -1,    32,    57,    56,    -1,
      51,    -1,    15,    -1,    -1,    59,    -1,    51,    -1,    51,
      32,    59,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    68,    68,    75,    76,    83,    95,    99,   105,   111,
     117,   123,   131,   132,   137,   143,   148,   149,   164,   170,
     178,   179,   185,   189,   207,   212,   216,   220,   224,   228,
     232,   236,   241,   242,   244,   245,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   260,   261,
     263,   264,   265,   266,   268,   273,   278,   279,   284,   289,
     295,   296,   298,   299,   304,   309
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ASOP", "EQOP", "RELOP", "CONDOP",
  "MINUS", "PLUS", "MULT_DIV", "UMINUS", "NOTOP", "TYPE", "VOID", "ID",
  "STRLIT", "INTLIT", "HEXLIT", "CHARLIT", "BOOLVAL", "RET", "BREAK",
  "CONT", "CLASS", "OPEN", "CLOSE", "IF", "ELSE", "FOR", "END", "PROGRAM",
  "COMMENT", "COMMA", "SQOPEN", "SQCLOSE", "ROPEN", "RCLOSE", "CALLOUT",
  "$accept", "program", "decl_list", "decl", "field_decl", "arg_decl",
  "block", "block_field_decl", "block_field_name", "statement",
  "statement_decl", "expr_opt", "else_opt", "expr", "literal",
  "method_call", "callout", "callout_opt", "callout_args", "callout_arg",
  "method_opt", "method_arg", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    40,    40,    41,    41,    41,    42,    42,
      42,    42,    43,    43,    43,    44,    45,    45,    46,    46,
      47,    47,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    49,    49,    50,    50,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      52,    52,    52,    52,    53,    54,    55,    55,    56,    56,
      57,    57,    58,    58,    59,    59
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     0,     2,     2,     6,     6,     3,     6,
       2,     5,     0,     2,     4,     4,     0,     3,     2,     3,
       0,     2,     1,     4,     7,     3,     6,     7,     3,     2,
       2,     1,     0,     1,     0,     2,     1,     4,     2,     1,
       3,     3,     3,     3,     3,     3,     2,     2,     3,     1,
       1,     1,     1,     1,     3,     6,     0,     1,     2,     3,
       1,     1,     0,     1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     3,     0,     0,     0,     3,
       0,     5,     0,     2,     4,    10,     0,     0,    12,    12,
       0,     8,     0,     0,     0,     0,     0,    13,     0,     0,
       0,    11,     0,     0,    16,     6,     7,     9,    14,     0,
      20,     0,    16,     0,    18,     0,    17,     0,    32,     0,
       0,    15,     0,     0,     0,    31,    21,    22,    19,     0,
       0,    62,     0,     0,     0,    36,    50,    51,    52,    53,
       0,     0,    33,    49,    39,    29,    30,     0,     0,     0,
       0,     0,    64,     0,    63,    25,    47,    46,     0,    38,
       0,    28,     0,     0,     0,     0,     0,     0,     0,     0,
      56,    23,     0,     0,    54,     0,    48,    45,    44,    43,
      41,    40,    42,     0,     0,     0,     0,    57,     0,    65,
      37,    34,     0,    61,    60,    58,     0,     0,     0,    26,
       0,    59,    55,    24,    35,    27
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     8,     9,    11,    24,    35,    40,    42,    43,
      56,    71,   129,    82,    73,    62,    74,   116,   117,   125,
      83,    84
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -46
static const yytype_int16 yypact[] =
{
     -21,   -19,    34,    33,   -46,     9,    47,    57,    50,     9,
       6,   -46,    39,   -46,   -46,   -46,    62,    63,    68,    68,
      -9,   -46,    65,    67,   -20,     1,    30,   -46,    85,    77,
      77,   -46,    62,    88,    91,   -46,   -46,   -46,   -46,    90,
     -46,    40,    91,   137,   -46,    90,   -46,     7,    71,    76,
      78,   -46,    99,   121,   101,   -46,   -46,   -46,   -46,    71,
      71,    71,   108,    71,    71,    20,   -46,   -46,   -46,   -46,
      71,   109,   177,   -46,   -46,   -46,   -46,    71,   138,   125,
     124,    87,   111,   106,   -46,   -46,   -46,   -46,    71,   -46,
       0,   -46,    71,    71,    71,    71,    71,    71,    22,    71,
     120,   -46,   151,    71,   -46,   105,   -46,    37,    37,    37,
     146,   146,   -46,    77,   118,    49,   128,   -46,    71,   -46,
     -46,   129,    71,   -46,   177,   120,   131,   140,    77,   -46,
     171,   -46,   -46,   -46,   -46,   -46
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -46,   -46,   157,   -46,   -15,   148,   -30,   126,   127,   -46,
     -46,   -46,   -46,   -45,   -46,   122,   130,   -46,    45,   -46,
     -46,    86
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      36,    21,     1,    72,    92,    93,    94,    95,    96,    97,
      59,     3,    28,    55,    80,    81,    29,    37,    86,    87,
      15,     6,     7,    16,    17,    90,    92,    93,    94,    95,
      96,    97,    98,    28,     4,    15,   106,    30,    16,    17,
      60,    18,    61,   105,    95,    96,    97,   107,   108,   109,
     110,   111,   112,    88,   114,    61,    63,     5,   113,    31,
      64,    10,    32,    65,   123,    66,    67,    68,    69,    44,
     124,    12,    45,   127,    19,    13,    20,   130,    63,    22,
      23,    27,    64,   121,    70,    65,    54,    66,    67,    68,
      69,    92,    93,    94,    95,    96,    97,    33,   134,    26,
     135,    34,    38,    39,    41,    75,    70,    76,    54,    92,
      93,    94,    95,    96,    97,    92,    93,    94,    95,    96,
      97,   102,    92,    93,    94,    95,    96,    97,    92,    93,
      94,    95,    96,    97,    77,    78,    79,    85,    91,   120,
     100,    99,   104,   103,    92,    93,    94,    95,    96,    97,
     122,    47,   115,   101,   118,    97,   128,    48,    49,    50,
     132,    34,    51,    52,   126,    53,    14,    25,    46,   133,
     131,     0,    58,    57,    54,    92,    93,    94,    95,    96,
      97,    92,    93,    94,    95,    96,    97,    89,     0,   119,
       0,     0,     0,     0,     0,    34
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-46)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      30,    16,    23,    48,     4,     5,     6,     7,     8,     9,
       3,    30,    32,    43,    59,    60,    36,    32,    63,    64,
      29,    12,    13,    32,    33,    70,     4,     5,     6,     7,
       8,     9,    77,    32,     0,    29,    36,    36,    32,    33,
      33,    35,    35,    88,     7,     8,     9,    92,    93,    94,
      95,    96,    97,    33,    99,    35,     7,    24,    36,    29,
      11,    14,    32,    14,    15,    16,    17,    18,    19,    29,
     115,    14,    32,   118,    35,    25,    14,   122,     7,    16,
      12,    14,    11,   113,    35,    14,    37,    16,    17,    18,
      19,     4,     5,     6,     7,     8,     9,    12,   128,    34,
     130,    24,    14,    12,    14,    29,    35,    29,    37,     4,
       5,     6,     7,     8,     9,     4,     5,     6,     7,     8,
       9,    34,     4,     5,     6,     7,     8,     9,     4,     5,
       6,     7,     8,     9,    35,    14,    35,    29,    29,    34,
      15,     3,    36,    32,     4,     5,     6,     7,     8,     9,
      32,    14,    32,    29,     3,     9,    27,    20,    21,    22,
      29,    24,    25,    26,    36,    28,     9,    19,    42,    29,
     125,    -1,    45,    43,    37,     4,     5,     6,     7,     8,
       9,     4,     5,     6,     7,     8,     9,    65,    -1,   103,
      -1,    -1,    -1,    -1,    -1,    24
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    23,    39,    30,     0,    24,    12,    13,    40,    41,
      14,    42,    14,    25,    40,    29,    32,    33,    35,    35,
      14,    42,    16,    12,    43,    43,    34,    14,    32,    36,
      36,    29,    32,    12,    24,    44,    44,    42,    14,    12,
      45,    14,    46,    47,    29,    32,    45,    14,    20,    21,
      22,    25,    26,    28,    37,    44,    48,    54,    46,     3,
      33,    35,    53,     7,    11,    14,    16,    17,    18,    19,
      35,    49,    51,    52,    54,    29,    29,    35,    14,    35,
      51,    51,    51,    58,    59,    29,    51,    51,    33,    53,
      51,    29,     4,     5,     6,     7,     8,     9,    51,     3,
      15,    29,    34,    32,    36,    51,    36,    51,    51,    51,
      51,    51,    51,    36,    51,    32,    55,    56,     3,    59,
      34,    44,    32,    15,    51,    57,    36,    51,    27,    50,
      51,    56,    29,    29,    44,    44
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

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


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
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
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
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
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

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

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

  YYUSE (yytype);
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

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

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
/* Line 1787 of yacc.c  */
#line 69 "parser.ypp"
    {
    (yyval.program) = new ASTProgram((yyvsp[(4) - (5)].decl_list));
    (yyval.program)->print_ast(0);
}
    break;

  case 3:
/* Line 1787 of yacc.c  */
#line 75 "parser.ypp"
    {(yyval.decl_list) = new vector<ASTDecl*>;}
    break;

  case 4:
/* Line 1787 of yacc.c  */
#line 77 "parser.ypp"
    {
    (yyval.decl_list) = (yyvsp[(2) - (2)].decl_list);
    (yyval.decl_list)->push_back((yyvsp[(1) - (2)].decl));
}
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 84 "parser.ypp"
    {
    vector<ASTVar*> vars = *(yyvsp[(2) - (2)].field_decl);
    vector< pair<string*, ASTVar*> > *var_list = new vector< pair<string*, ASTVar*> >;

    for (int i = 0; i < vars.size(); ++i)
    {
        var_list->push_back(make_pair((yyvsp[(1) - (2)].str), vars[i]));
    }

    (yyval.decl) = new ASTVarDecl(var_list);
}
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 96 "parser.ypp"
    {
    (yyval.decl) = new ASTMethodDecl((yyvsp[(1) - (6)].str), (yyvsp[(2) - (6)].str), (yyvsp[(4) - (6)].arg_decl), (yyvsp[(6) - (6)].block));
}
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 100 "parser.ypp"
    {
    (yyval.decl) = new ASTMethodDecl((yyvsp[(1) - (6)].str), (yyvsp[(2) - (6)].str), (yyvsp[(4) - (6)].arg_decl), (yyvsp[(6) - (6)].block)); 
}
    break;

  case 8:
/* Line 1787 of yacc.c  */
#line 106 "parser.ypp"
    {
    (yyval.field_decl) = (yyvsp[(3) - (3)].field_decl);
    ASTVar *var = new ASTVar1((yyvsp[(1) - (3)].str));
    (yyval.field_decl)->push_back(var);
}
    break;

  case 9:
/* Line 1787 of yacc.c  */
#line 112 "parser.ypp"
    {
    (yyval.field_decl) = (yyvsp[(6) - (6)].field_decl);
    ASTVar *var = new ASTVar2((yyvsp[(1) - (6)].str), (yyvsp[(3) - (6)].str));
    (yyval.field_decl)->push_back(var);
}
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 118 "parser.ypp"
    {
    (yyval.field_decl) = new vector<ASTVar*>;
    ASTVar *var = new ASTVar1((yyvsp[(1) - (2)].str));
    (yyval.field_decl)->push_back(var);
}
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 124 "parser.ypp"
    {
    (yyval.field_decl) = new vector<ASTVar*>;
    ASTVar *var = new ASTVar2((yyvsp[(1) - (5)].str), (yyvsp[(3) - (5)].str));
    (yyval.field_decl)->push_back(var);
}
    break;

  case 12:
/* Line 1787 of yacc.c  */
#line 131 "parser.ypp"
    { (yyval.arg_decl) = new vector< pair<string, string> >; }
    break;

  case 13:
/* Line 1787 of yacc.c  */
#line 133 "parser.ypp"
    { 
    (yyval.arg_decl) = new vector< pair<string, string> >;
    (yyval.arg_decl)->push_back(make_pair(*(yyvsp[(1) - (2)].str), *(yyvsp[(2) - (2)].str)));
}
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 138 "parser.ypp"
    {
    (yyval.arg_decl) = (yyvsp[(1) - (4)].arg_decl);
    (yyval.arg_decl)->push_back(make_pair(*(yyvsp[(3) - (4)].str), *(yyvsp[(4) - (4)].str)));
}
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 144 "parser.ypp"
    {
    (yyval.block) = new ASTBlock((yyvsp[(2) - (4)].block_field_decl), (yyvsp[(3) - (4)].statement)); 
}
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 148 "parser.ypp"
    { (yyval.block_field_decl) = NULL;}
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 150 "parser.ypp"
    {
    (yyval.block_field_decl) = (yyvsp[(3) - (3)].block_field_decl);
    
    if ((yyval.block_field_decl) == NULL)
    {
        (yyval.block_field_decl) = new ASTVarDecl();
    }
    vector<ASTVar1*> vars = *(yyvsp[(2) - (3)].block_field_name);
    for (int i = 0; i < vars.size(); ++i)
    {
        (yyval.block_field_decl)->add_vars(make_pair((yyvsp[(1) - (3)].str), vars[i]));
    }
}
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 165 "parser.ypp"
    { 
    (yyval.block_field_name) = new vector<ASTVar1*>;
    ASTVar1 *var = new ASTVar1((yyvsp[(1) - (2)].str));
    (yyval.block_field_name)->push_back(var);
}
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 171 "parser.ypp"
    {
    (yyval.block_field_name) = (yyvsp[(3) - (3)].block_field_name);
    ASTVar1 *var = new ASTVar1((yyvsp[(1) - (3)].str));
    (yyval.block_field_name)->push_back(var);
}
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 178 "parser.ypp"
    { (yyval.statement) = new vector<ASTStatement*>; }
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 180 "parser.ypp"
    {
    (yyval.statement) = (yyvsp[(1) - (2)].statement);
    (yyval.statement)->push_back((yyvsp[(2) - (2)].statement_decl));
}
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 186 "parser.ypp"
    {
    (yyval.statement_decl) = (yyvsp[(1) - (1)].callout);
}
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 190 "parser.ypp"
    {
    ASTLocation *loc = new ASTLocation1((yyvsp[(1) - (4)].str));
    string op_ = *(yyvsp[(2) - (4)].str);
    if(op_.compare("+=") == 0 || op_.compare("-=") == 0 || op_.compare("*=") == 0 || op_.compare("/=") == 0)
    {
        string *new_op = new string("");
	*new_op += op_[0];
	string other_op = "";
	other_op += op_[1];
	ASTExpr *new_expr =  new ASTBinopExpr(loc,new_op,(yyvsp[(3) - (4)].expr));
    	(yyval.statement_decl) = new ASTAssignment(loc, new_expr);
    }
    else
    {
   	(yyval.statement_decl) = new ASTAssignment(loc, (yyvsp[(3) - (4)].expr));
    }
}
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 208 "parser.ypp"
    {
    ASTLocation *loc = new ASTLocation2((yyvsp[(1) - (7)].str), (yyvsp[(3) - (7)].expr));
    (yyval.statement_decl) = new ASTAssignment(loc, (yyvsp[(6) - (7)].expr));
}
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 213 "parser.ypp"
    {
    (yyval.statement_decl) = new ASTMethodCall1((yyvsp[(1) - (3)].str), (yyvsp[(2) - (3)].method_call));
}
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 217 "parser.ypp"
    {
    (yyval.statement_decl) = new ASTIf((yyvsp[(3) - (6)].expr), (yyvsp[(5) - (6)].block), (yyvsp[(6) - (6)].block));
}
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 221 "parser.ypp"
    {
    (yyval.statement_decl) = new ASTFor((yyvsp[(2) - (7)].str), (yyvsp[(4) - (7)].expr), (yyvsp[(6) - (7)].expr), (yyvsp[(7) - (7)].block));
}
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 225 "parser.ypp"
    {
    (yyval.statement_decl) = new ASTReturn((yyvsp[(2) - (3)].expr));
}
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 229 "parser.ypp"
    {
    (yyval.statement_decl) = new ASTBreak();
}
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 233 "parser.ypp"
    {
    (yyval.statement_decl) = new ASTContinue();
}
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 237 "parser.ypp"
    {
    (yyval.statement_decl) = (yyvsp[(1) - (1)].block);
}
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 241 "parser.ypp"
    { (yyval.expr) = NULL; }
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 242 "parser.ypp"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 244 "parser.ypp"
    { (yyval.block) = NULL; }
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 245 "parser.ypp"
    { (yyval.block) = (yyvsp[(2) - (2)].block); }
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 247 "parser.ypp"
    { (yyval.expr) = new ASTLocation1((yyvsp[(1) - (1)].str)); }
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 248 "parser.ypp"
    { (yyval.expr) = new ASTLocation2((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].expr)); }
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 249 "parser.ypp"
    { (yyval.expr) = new ASTMethodCall1((yyvsp[(1) - (2)].str), (yyvsp[(2) - (2)].method_call)); }
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 250 "parser.ypp"
    { (yyval.expr) = (yyvsp[(1) - (1)].callout); }
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 251 "parser.ypp"
    { (yyval.expr) = new ASTBinopExpr((yyvsp[(1) - (3)].expr), (yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); }
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 252 "parser.ypp"
    { (yyval.expr) = new ASTBinopExpr((yyvsp[(1) - (3)].expr), (yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); }
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 253 "parser.ypp"
    { (yyval.expr) = new ASTBinopExpr((yyvsp[(1) - (3)].expr), (yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); }
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 254 "parser.ypp"
    { (yyval.expr) = new ASTBinopExpr((yyvsp[(1) - (3)].expr), (yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); }
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 255 "parser.ypp"
    { (yyval.expr) = new ASTBinopExpr((yyvsp[(1) - (3)].expr), (yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); }
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 256 "parser.ypp"
    { (yyval.expr) = new ASTBinopExpr((yyvsp[(1) - (3)].expr), (yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].expr)); }
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 257 "parser.ypp"
    { (yyval.expr) = new ASTUnaryExpr((yyvsp[(2) - (2)].expr), (yyvsp[(1) - (2)].str)); }
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 259 "parser.ypp"
    { (yyval.expr) = new ASTUnaryExpr((yyvsp[(2) - (2)].expr), (yyvsp[(1) - (2)].str)); }
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 260 "parser.ypp"
    { (yyval.expr) = (yyvsp[(2) - (3)].expr); }
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 261 "parser.ypp"
    { (yyval.expr) = (yyvsp[(1) - (1)].literal); }
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 263 "parser.ypp"
    { (yyval.literal) = new ASTLiteralInt((yyvsp[(1) - (1)].str)); }
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 264 "parser.ypp"
    { (yyval.literal) = new ASTLiteralInt((yyvsp[(1) - (1)].str)); }
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 265 "parser.ypp"
    { (yyval.literal) = new ASTLiteralChar((yyvsp[(1) - (1)].str)); }
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 266 "parser.ypp"
    { (yyval.literal) = new ASTLiteralBool((yyvsp[(1) - (1)].str)); }
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 269 "parser.ypp"
    {
    (yyval.method_call) = (yyvsp[(2) - (3)].method_call);
}
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 274 "parser.ypp"
    {
    (yyval.callout) = new ASTMethodCall2((yyvsp[(3) - (6)].str), (yyvsp[(4) - (6)].callout_args));
}
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 278 "parser.ypp"
    { (yyval.callout_args) = new vector<ASTCalloutArgs*>; }
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 280 "parser.ypp"
    {
    (yyval.callout_args) = (yyvsp[(1) - (1)].callout_args);
}
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 285 "parser.ypp"
    {
    (yyval.callout_args) = new vector<ASTCalloutArgs*>;
    (yyval.callout_args)->push_back((yyvsp[(2) - (2)].callout_arg));
}
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 290 "parser.ypp"
    {
    (yyval.callout_args) = (yyvsp[(3) - (3)].callout_args);
    (yyval.callout_args)->push_back((yyvsp[(2) - (3)].callout_arg));
}
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 295 "parser.ypp"
    { (yyval.callout_arg) = new ASTCalloutArgs1((yyvsp[(1) - (1)].expr)); }
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 296 "parser.ypp"
    { (yyval.callout_arg) = new ASTCalloutArgs2((yyvsp[(1) - (1)].str)); }
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 298 "parser.ypp"
    { (yyval.method_call) = new vector<ASTExpr*>; }
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 300 "parser.ypp"
    {
    (yyval.method_call) = (yyvsp[(1) - (1)].method_call);
}
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 305 "parser.ypp"
    { 
    (yyval.method_call) = new vector<ASTExpr*>;
    (yyval.method_call)->push_back((yyvsp[(1) - (1)].expr));
}
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 310 "parser.ypp"
    {
    (yyval.method_call) = (yyvsp[(3) - (3)].method_call);
    (yyval.method_call)->push_back((yyvsp[(1) - (3)].expr));
}
    break;


/* Line 1787 of yacc.c  */
#line 2031 "parser.tab.cpp"
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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


/* Line 2050 of yacc.c  */
#line 315 "parser.ypp"

int main()
{
    yyparse();
    
    return 0;
}
