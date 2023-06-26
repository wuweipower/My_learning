/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7"

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
#line 1 "lab2.y"

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define BOOL int
#define true 1
#define false 2

#define MAXSTR 20
#define MAXMEMBER 100

#define INTTYPE  0
#define CHARTYPE 1

extern int yylex();
extern FILE* yyin;
extern char str[20];
int VarCount=0;
FILE* fp;
int NXQ=0; 

int Entry(char *name);                       
int AddType(int first,int type);             
int NewTemp();                                
int Merge(int p,int q);                      
void BackPatch(int p,int t);          
int GEN(char* op,int a1,int a2,int re);               
void OutQuadruple();                      
void OutList();     
int yyparse();
int yyerror(char *errstr);

struct QUATERLIST{
	char op[6];
	int arg1;
	int arg2;
	int result;
} QuaterList[MAXMEMBER];
struct VARLIST{
	char name[20];
	int type;
	int addr;
} VarList[MAXMEMBER];


/* Line 371 of yacc.c  */
#line 117 "lab2.tab.c"

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
     Int = 100,
     Char = 101,
     Void = 102,
     Main = 103,
     If = 104,
     Else = 105,
     While = 106,
     Const = 107,
     And = 108,
     Equal = 109,
     Or = 110,
     Ident = 111,
     Num = 112,
     String = 113
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 51 "lab2.y"

    int  Iv;
    int CH;
    int NO;
    struct { int TC,FC;} _BExp;
    struct { int QUAD,CH;} _WBD;
    struct { int type,place;} _Exp;
    char   _Rop[5];
    int First;
    char   str[20];


/* Line 387 of yacc.c  */
#line 186 "lab2.tab.c"
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



/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 214 "lab2.tab.c"

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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   107

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  30
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  46
/* YYNRULES -- Number of states.  */
#define YYNSTATES  88

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   257

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      26,    27,    22,    20,    25,    21,     2,    23,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    24,
      17,    19,    18,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    28,     2,    29,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    13,    17,    20,    24,
      27,    33,    38,    44,    46,    48,    52,    54,    58,    62,
      66,    70,    74,    76,    78,    80,    82,    85,    88,    91,
      94,    97,   101,   106,   111,   113,   117,   121,   122,   127,
     128,   133,   137,   139,   141,   143,   145
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      31,     0,    -1,    32,    -1,    33,    41,    -1,    33,    34,
      -1,    34,    -1,    34,    35,    24,    -1,    35,    24,    -1,
      35,    25,    40,    -1,    36,    40,    -1,    35,    25,    38,
      19,    39,    -1,    36,    38,    19,    39,    -1,    10,    36,
      38,    19,    39,    -1,     3,    -1,     4,    -1,    38,    19,
      39,    -1,    40,    -1,    39,    20,    39,    -1,    39,    21,
      39,    -1,    39,    22,    39,    -1,    39,    23,    39,    -1,
      26,    39,    27,    -1,    40,    -1,    51,    -1,    14,    -1,
      42,    -1,    42,    41,    -1,    37,    24,    -1,    43,    47,
      -1,    44,    47,    -1,    45,    47,    -1,    44,    47,     8,
      -1,     7,    26,    48,    27,    -1,    46,    26,    48,    27,
      -1,     9,    -1,    28,    41,    29,    -1,    39,    52,    39,
      -1,    -1,    48,    11,    49,    48,    -1,    -1,    48,    13,
      50,    48,    -1,    26,    48,    27,    -1,    15,    -1,    16,
      -1,    17,    -1,    18,    -1,    12,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   105,   105,   108,   109,   110,   112,   113,   115,   116,
     117,   134,   153,   174,   175,   177,   184,   187,   201,   217,
     232,   247,   248,   253,   256,   261,   262,   264,   265,   266,
     267,   274,   277,   280,   283,   286,   289,   295,   295,   296,
     296,   297,   300,   306,   314,   315,   316
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "Int", "Char", "Void", "Main", "If",
  "Else", "While", "Const", "And", "Equal", "Or", "Ident", "Num", "String",
  "'<'", "'>'", "'='", "'+'", "'-'", "'*'", "'/'", "';'", "','", "'('",
  "')'", "'{'", "'}'", "$accept", "CompUnit", "SubComp", "VarDef",
  "VarDefList", "VarList", "Type", "AsignState", "AVariable", "Exp",
  "Variable", "StateList", "Statement", "IfElse", "IfNoElse", "Wd", "W",
  "ComplexState", "BoolExp", "$@1", "$@2", "Data", "RelationOp", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,    60,    62,    61,
      43,    45,    42,    47,    59,    44,    40,    41,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    30,    31,    32,    33,    33,    34,    34,    35,    35,
      35,    35,    35,    36,    36,    37,    38,    39,    39,    39,
      39,    39,    39,    39,    40,    41,    41,    42,    42,    42,
      42,    43,    44,    45,    46,    47,    48,    49,    48,    50,
      48,    48,    51,    51,    52,    52,    52
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     3,     2,     3,     2,
       5,     4,     5,     1,     1,     3,     1,     3,     3,     3,
       3,     3,     1,     1,     1,     1,     2,     2,     2,     2,
       2,     3,     4,     4,     1,     3,     3,     0,     4,     0,
       4,     3,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    13,    14,     0,     0,     2,     0,     5,     0,     0,
       0,     1,     0,    34,    24,     4,     0,     0,    16,     3,
      25,     0,     0,     0,     0,     0,     7,     0,     0,     9,
       0,     0,    27,     0,    26,     0,    28,    29,    30,     0,
       6,     0,     8,     0,     0,    42,    43,     0,     0,    22,
       0,    23,     0,    15,     0,    31,     0,     0,    11,    12,
       0,     0,    46,    44,    45,     0,     0,     0,     0,     0,
      37,    39,    32,     0,    35,    33,    10,    21,    41,    17,
      18,    19,    20,    36,     0,     0,    38,    40
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,     9,    16,    17,    48,
      49,    19,    20,    21,    22,    23,    24,    36,    50,    84,
      85,    51,    69
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -40
static const yytype_int8 yypact[] =
{
      72,   -40,   -40,    44,    13,   -40,    70,    72,    66,     5,
       5,   -40,     4,   -40,   -40,    72,    36,    46,   -40,   -40,
       0,    35,    35,    35,    52,    74,   -40,     5,    62,    64,
      85,    25,   -40,    42,   -40,     0,   -40,    81,   -40,    25,
     -40,    86,    64,    42,    42,   -40,   -40,    25,    49,   -40,
      11,   -40,    42,    73,    68,   -40,    15,    42,    73,    73,
      32,    16,   -40,   -40,   -40,    42,    42,    42,    42,    42,
     -40,   -40,   -40,    65,   -40,   -40,    73,   -40,   -40,    78,
      78,   -40,   -40,    73,    25,    25,    51,    51
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -40,   -40,   -40,   -40,   100,     3,   104,   -40,    -6,   -32,
      -4,    -3,   -40,   -40,   -40,   -40,   -40,    80,   -39,   -40,
     -40,   -40,   -40
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -17
static const yytype_int8 yytable[] =
{
      56,    53,    18,    28,    30,    29,    18,    12,    61,    13,
      25,    58,    59,    11,    14,    60,    18,    34,    25,    14,
      73,    41,    70,    42,    71,    76,    70,    70,    71,    71,
      31,    18,    54,    79,    80,    81,    82,    83,    72,    14,
      45,    46,    75,    78,    62,    86,    87,     1,     2,    63,
      64,    47,    65,    66,    67,    68,    14,    45,    46,    77,
      32,    62,    70,    35,    71,    33,    63,    64,    52,    65,
      66,    67,    68,     1,     2,     1,     2,    12,    39,    13,
       3,    43,     3,   -16,    14,    65,    66,    67,    68,    55,
      26,    27,    77,    65,    66,    67,    68,    74,    40,    27,
      67,    68,    37,    38,    44,    57,    15,    10
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-40)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_uint8 yycheck[] =
{
      39,    33,     6,     9,    10,     9,    10,     7,    47,     9,
       7,    43,    44,     0,    14,    47,    20,    20,    15,    14,
      52,    27,    11,    27,    13,    57,    11,    11,    13,    13,
      26,    35,    35,    65,    66,    67,    68,    69,    27,    14,
      15,    16,    27,    27,    12,    84,    85,     3,     4,    17,
      18,    26,    20,    21,    22,    23,    14,    15,    16,    27,
      24,    12,    11,    28,    13,    19,    17,    18,    26,    20,
      21,    22,    23,     3,     4,     3,     4,     7,    26,     9,
      10,    19,    10,    19,    14,    20,    21,    22,    23,     8,
      24,    25,    27,    20,    21,    22,    23,    29,    24,    25,
      22,    23,    22,    23,    19,    19,     6,     3
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,    10,    31,    32,    33,    34,    35,    36,
      36,     0,     7,     9,    14,    34,    37,    38,    40,    41,
      42,    43,    44,    45,    46,    35,    24,    25,    38,    40,
      38,    26,    24,    19,    41,    28,    47,    47,    47,    26,
      24,    38,    40,    19,    19,    15,    16,    26,    39,    40,
      48,    51,    26,    39,    41,     8,    48,    19,    39,    39,
      39,    48,    12,    17,    18,    20,    21,    22,    23,    52,
      11,    13,    27,    39,    29,    27,    39,    27,    27,    39,
      39,    39,    39,    39,    49,    50,    48,    48
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

  switch (yytype)
    {

      default:
        break;
    }
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
/* Line 1792 of yacc.c  */
#line 105 "lab2.y"
    {(yyval.CH)=0;}
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 108 "lab2.y"
    {GEN("Stop",0,0,0);}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 109 "lab2.y"
    {(yyval.CH)=0;}
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 110 "lab2.y"
    {(yyval.CH)=0;}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 112 "lab2.y"
    {(yyval.CH)=0;}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 113 "lab2.y"
    {(yyval.CH)=0;}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 115 "lab2.y"
    {AddType((yyvsp[(3) - (3)].NO),(yyvsp[(1) - (3)].First));}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 116 "lab2.y"
    {(yyval.First)=(yyvsp[(1) - (2)].Iv);AddType((yyvsp[(2) - (2)].NO),(yyval.First));}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 117 "lab2.y"
    {
		AddType((yyvsp[(3) - (5)].NO),(yyvsp[(1) - (5)].First));
		if(VarList[(yyvsp[(3) - (5)].NO)].type==(yyvsp[(5) - (5)]._Exp).type)
			   GEN("=",(yyvsp[(5) - (5)]._Exp).place,0,(yyvsp[(3) - (5)].NO));
		else if((yyvsp[(5) - (5)]._Exp).type==INTTYPE && VarList[(yyvsp[(3) - (5)].NO)].type==CHARTYPE)
		{
			   int T=NewTemp();
			   GEN("INT->CHAR",(yyvsp[(5) - (5)]._Exp).place,0,T);
			   GEN("=",T,0,(yyvsp[(3) - (5)].NO));
		}
		else if((yyvsp[(5) - (5)]._Exp).type==CHARTYPE && VarList[(yyvsp[(3) - (5)].NO)].type==INTTYPE)
		{
			 int T=NewTemp();
			 GEN("CHAR->INT",(yyvsp[(5) - (5)]._Exp).place,0,T);
			 GEN("=",T,0,(yyvsp[(3) - (5)].NO));
		}
	}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 135 "lab2.y"
    {
			(yyval.First)=(yyvsp[(1) - (4)].Iv);
			AddType((yyvsp[(2) - (4)].NO),(yyval.First));
			if(VarList[(yyvsp[(2) - (4)].NO)].type==(yyvsp[(4) - (4)]._Exp).type)
				GEN("=",(yyvsp[(4) - (4)]._Exp).place,0,(yyvsp[(2) - (4)].NO));
			else if((yyvsp[(4) - (4)]._Exp).type==INTTYPE && VarList[(yyvsp[(2) - (4)].NO)].type==CHARTYPE)
			{
			   	int T=NewTemp();
			   	GEN("INT->CHAR",(yyvsp[(4) - (4)]._Exp).place,0,T);
			   	GEN("=",T,0,(yyvsp[(2) - (4)].NO));
			}
			else if((yyvsp[(4) - (4)]._Exp).type==CHARTYPE && VarList[(yyvsp[(2) - (4)].NO)].type==INTTYPE)
			{
				int T=NewTemp();
				GEN("CHAR->I",(yyvsp[(4) - (4)]._Exp).place,0,T);
				GEN("=",T,0,(yyvsp[(2) - (4)].NO));
			}
		}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 154 "lab2.y"
    {
			(yyval.First)=(yyvsp[(2) - (5)].Iv);
			AddType((yyvsp[(3) - (5)].NO),(yyval.First));
			if(VarList[(yyvsp[(3) - (5)].NO)].type==(yyvsp[(5) - (5)]._Exp).type)
				GEN("=",(yyvsp[(5) - (5)]._Exp).place,0,(yyvsp[(3) - (5)].NO));
			else if((yyvsp[(5) - (5)]._Exp).type==INTTYPE && VarList[(yyvsp[(3) - (5)].NO)].type==CHARTYPE)
			{
			   	int T=NewTemp();
			   	GEN("INT->CHAR",(yyvsp[(5) - (5)]._Exp).place,0,T);
			   	GEN("=",T,0,(yyvsp[(3) - (5)].NO));
			}
			else if((yyvsp[(5) - (5)]._Exp).type==CHARTYPE && VarList[(yyvsp[(3) - (5)].NO)].type==INTTYPE)
			{
				int T=NewTemp();
				GEN("CHAR->I",(yyvsp[(5) - (5)]._Exp).place,0,T);
				GEN("=",T,0,(yyvsp[(3) - (5)].NO));
			}
		}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 174 "lab2.y"
    {(yyval.Iv)=INTTYPE;}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 175 "lab2.y"
    {(yyval.Iv)=CHARTYPE;}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 177 "lab2.y"
    {
	(yyval._WBD).QUAD=(yyvsp[(1) - (3)].NO);
	(yyval._WBD).CH=NXQ-1;
	if(VarList[(yyvsp[(1) - (3)].NO)].type==(yyvsp[(3) - (3)]._Exp).type)  GEN("=",(yyvsp[(3) - (3)]._Exp).place,0,(yyvsp[(1) - (3)].NO));
}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 184 "lab2.y"
    {(yyval.NO)=(yyvsp[(1) - (1)].NO);}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 188 "lab2.y"
    {
		int T=NewTemp();
		if((yyvsp[(1) - (3)]._Exp).type== INTTYPE && (yyvsp[(3) - (3)]._Exp).type==INTTYPE)  
		{
			GEN("INT+",(yyvsp[(1) - (3)]._Exp).place,(yyvsp[(3) - (3)]._Exp).place,T);
		  	VarList[T].type=(yyval._Exp).type=INTTYPE;
		}
		else if((yyvsp[(1) - (3)]._Exp).type== CHARTYPE && (yyvsp[(3) - (3)]._Exp).type==CHARTYPE)  
		{
		  	GEN("CHAR+",(yyvsp[(1) - (3)]._Exp).place,(yyvsp[(3) - (3)]._Exp).place,T);
		  	VarList[T].type=(yyval._Exp).type=CHARTYPE;
		}
		}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 202 "lab2.y"
    {
		int T=NewTemp();
		if((yyvsp[(1) - (3)]._Exp).type== INTTYPE && (yyvsp[(3) - (3)]._Exp).type==INTTYPE)
		{
			GEN("INT-",(yyvsp[(1) - (3)]._Exp).place,(yyvsp[(3) - (3)]._Exp).place,T);
			VarList[T].type=(yyval._Exp).type=INTTYPE;
		}
		else if((yyvsp[(1) - (3)]._Exp).type== CHARTYPE && (yyvsp[(3) - (3)]._Exp).type==CHARTYPE)	
		{
			GEN("CHAR-",(yyvsp[(1) - (3)]._Exp).place,(yyvsp[(3) - (3)]._Exp).place,T);
			VarList[T].type=(yyval._Exp).type=CHARTYPE;
		}
		(yyval._Exp).place=T;
	}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 218 "lab2.y"
    {
		int T=NewTemp();
		if((yyvsp[(1) - (3)]._Exp).type== INTTYPE && (yyvsp[(3) - (3)]._Exp).type==INTTYPE)
		{
		  	GEN("INT*",(yyvsp[(1) - (3)]._Exp).place,(yyvsp[(3) - (3)]._Exp).place,T);
		  	VarList[T].type=(yyval._Exp).type=INTTYPE;
		}
		else if((yyvsp[(1) - (3)]._Exp).type== CHARTYPE && (yyvsp[(3) - (3)]._Exp).type==CHARTYPE)	
		{
			GEN("CHAR*",(yyvsp[(1) - (3)]._Exp).place,(yyvsp[(3) - (3)]._Exp).place,T);
		  	VarList[T].type=(yyval._Exp).type=CHARTYPE;
		}
		(yyval._Exp).place=T;
		}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 233 "lab2.y"
    {
		int T=NewTemp();
		if((yyvsp[(1) - (3)]._Exp).type== INTTYPE && (yyvsp[(3) - (3)]._Exp).type==INTTYPE)
		{
		  	GEN("INT/",(yyvsp[(1) - (3)]._Exp).place,(yyvsp[(3) - (3)]._Exp).place,T);
		  	VarList[T].type=(yyval._Exp).type=INTTYPE;
		}
		else if((yyvsp[(1) - (3)]._Exp).type== CHARTYPE && (yyvsp[(3) - (3)]._Exp).type==CHARTYPE)
		{
		  	GEN("CHAR/",(yyvsp[(1) - (3)]._Exp).place,(yyvsp[(3) - (3)]._Exp).place,T);
		  	VarList[T].type=(yyval._Exp).type=CHARTYPE;
		}
		(yyval._Exp).place=T;
	}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 247 "lab2.y"
    {(yyval._Exp)=(yyvsp[(2) - (3)]._Exp);}
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 249 "lab2.y"
    {
		 (yyval._Exp).place=(yyvsp[(1) - (1)].NO);
		 (yyval._Exp).type=VarList[(yyvsp[(1) - (1)].NO)].type;
	}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 253 "lab2.y"
    {(yyval._Exp)=(yyvsp[(1) - (1)]._Exp);}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 256 "lab2.y"
    { (yyval.NO)=Entry(str); }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 261 "lab2.y"
    {(yyval.CH)=(yyvsp[(1) - (1)].CH);BackPatch((yyvsp[(1) - (1)].CH),NXQ);}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 262 "lab2.y"
    {(yyval.CH)=(yyvsp[(1) - (2)].CH);BackPatch((yyvsp[(1) - (2)].CH),NXQ);}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 264 "lab2.y"
    {(yyval.CH)=0;}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 265 "lab2.y"
    {(yyval.CH)=Merge((yyvsp[(1) - (2)].CH),(yyvsp[(2) - (2)].CH));}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 266 "lab2.y"
    {(yyval.CH)=Merge((yyvsp[(1) - (2)].CH),(yyvsp[(2) - (2)].CH));}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 267 "lab2.y"
    { 
			GEN("j",0,0,(yyvsp[(1) - (2)]._WBD).QUAD);
			BackPatch((yyvsp[(2) - (2)].CH),(yyvsp[(1) - (2)]._WBD).QUAD);
			(yyval.CH)=(yyvsp[(1) - (2)]._WBD).CH;
		}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 274 "lab2.y"
    {int q=NXQ;GEN("j",0,0,0);BackPatch((yyvsp[(1) - (3)].CH),NXQ);(yyval.CH)=Merge((yyvsp[(2) - (3)].CH),q);}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 277 "lab2.y"
    {BackPatch((yyvsp[(3) - (4)]._BExp).TC,NXQ);(yyval.CH)=(yyvsp[(3) - (4)]._BExp).FC;}
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 280 "lab2.y"
    {BackPatch((yyvsp[(3) - (4)]._BExp).TC,NXQ);(yyval._WBD).QUAD=(yyvsp[(1) - (4)].CH);(yyval._WBD).CH=(yyvsp[(3) - (4)]._BExp).FC;}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 283 "lab2.y"
    {(yyval.CH)=NXQ;}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 286 "lab2.y"
    {	(yyval.CH)=(yyvsp[(2) - (3)].CH);	}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 290 "lab2.y"
    {
		(yyval._BExp).TC=NXQ;(yyval._BExp).FC=NXQ+1;
		GEN((yyvsp[(2) - (3)]._Rop),(yyvsp[(1) - (3)]._Exp).place,(yyvsp[(3) - (3)]._Exp).place,0);
		GEN("j",0,0,0);                      
	}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 295 "lab2.y"
    {BackPatch((yyvsp[(1) - (2)]._BExp).TC,NXQ);}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 295 "lab2.y"
    {(yyval._BExp).TC=(yyvsp[(4) - (4)]._BExp).TC;(yyval._BExp).FC=Merge((yyvsp[(1) - (4)]._BExp).FC,(yyvsp[(4) - (4)]._BExp).FC);}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 296 "lab2.y"
    {BackPatch((yyvsp[(1) - (2)]._BExp).FC,NXQ);}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 296 "lab2.y"
    {(yyval._BExp).FC=(yyvsp[(4) - (4)]._BExp).FC;(yyval._BExp).TC=Merge((yyvsp[(1) - (4)]._BExp).TC,(yyvsp[(4) - (4)]._BExp).TC);}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 297 "lab2.y"
    {(yyval._BExp)=(yyvsp[(2) - (3)]._BExp);}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 301 "lab2.y"
    { 
		int i=Entry(str);
		(yyval._Exp).type=VarList[i].type=INTTYPE;
	  	(yyval._Exp).place=i;
	}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 307 "lab2.y"
    {
		int i=Entry(str);
		(yyval._Exp).type=VarList[i].type=CHARTYPE;
		(yyval._Exp).place=i;
	}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 314 "lab2.y"
    {strcpy((yyval._Rop),"j<");}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 315 "lab2.y"
    {strcpy((yyval._Rop),"j>");}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 316 "lab2.y"
    {strcpy((yyval._Rop),"j=");}
    break;


/* Line 1792 of yacc.c  */
#line 1868 "lab2.tab.c"
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


/* Line 2055 of yacc.c  */
#line 318 "lab2.y"



void OutQuadruple(void)
{
    int i;
	printf("------------------------------------------------------\n");
    printf("\nQuarters :\n");
    for(i=0;i<NXQ;i++)
    {
        printf("NO.%4d ( %8s, ",i,QuaterList[i].op);
        if(QuaterList[i].arg1)
	        printf("%6s, ",VarList[QuaterList[i].arg1].name);
   		else printf("      , ");
        if(QuaterList[i].arg2)
	        printf("%6s, ",VarList[QuaterList[i].arg2].name);
		else printf("      , ");
        if((QuaterList[i].op[0]=='j')||(QuaterList[i].op[0]=='S')) 
			printf("%6d )\n",QuaterList[i].result);
        else if(QuaterList[i].result)
	        printf("%6s )\n",VarList[QuaterList[i].result].name);
		else printf("-\t )\n");
    }
    return;
}

int yyerror(char *errstr)
{
    printf(" %s\n",errstr);
    return 0;
}

int Entry(char *name)
{
    int i;
    for(i=1;i<=VarCount;i++) 
        if(!strcmp(name,VarList[i].name)) 
            return i;
    if(++VarCount>MAXMEMBER) 
    {
        printf("Too many Variables!\n");exit(-1);
    }
    strcpy(VarList[VarCount].name,name);
    return VarCount;
}

int AddType(int first,int type)
{ 
    int i;
    for(i=first;i<=VarCount;i++) VarList[i].type=type;
    return i-1;
}

int Merge(int p,int q)
{
   int r;
   if(!q) return p;
   else
   {
       r=q;
       while(QuaterList[r].result)
        r=QuaterList[r].result;
       QuaterList[r].result=p;
   }
   return q;
}

void BackPatch(int p,int t)
{
    int q=p;
    while(q)
    { 
        int q1=QuaterList[q].result;
        QuaterList[q].result=t;
        q=q1;
    } 
    return;
}

int GEN(char* op,int a1,int a2,int re)
{
    strcpy(QuaterList[NXQ].op,op);
    QuaterList[NXQ].arg1=a1;
    QuaterList[NXQ].arg2=a2;
    QuaterList[NXQ].result=re;
    NXQ++;
    return NXQ;
}

int NewTemp()
{
    static int no=0;
    char Tempname[10];
    sprintf(Tempname,"T%o",no++);
    return Entry(Tempname);
}

void OutList(void)
{
    int i;
	printf("\n------------------------------------------------------\n");
	printf("\nAddress allocation : \n");
    printf(" Address\tName\tType\n");
    for(i=1;i<VarCount;i++)
    {
        printf("%4d\t%6s\t\t",i,VarList[i].name);
        if(VarList[i].type) 	
			printf(" CHAR   \n");
        else printf(" INT \n"); 
    }
	printf("------------------------------------------------------\n");
    return;
}

int main(int argc, char *argv[])
{
    yyin=NULL;
    if(argc>1)
    {
        if((yyin=fopen(argv[1],"r"))==NULL)
        {
            printf("Can't open file %s\n",argv[1]);exit(0);
        }
    } 
    yyin=fopen("test.txt","r");
    if(yyin==NULL)
    {
        printf("Can't open file test.txt\n");
        return -1;
    }	
	printf("\n Ai Lejun with 202030430011   ");
	printf("\n Huangxin with 202065073276   \n");
    yyparse();
    printf("\n");
    OutQuadruple();
    OutList();
    getchar();
    return;
}