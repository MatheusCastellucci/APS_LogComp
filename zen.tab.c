/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "zen.y"

    /* C Declarations */
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <llvm-c/Core.h>
    #include <llvm-c/ExecutionEngine.h>
    #include <llvm-c/Target.h>
    #include <llvm-c/Analysis.h>
    #include "symbol_table.h"
    #include "codegen.h"

    /* External declarations */
    extern int yylex();
    void yyerror(const char *s);

    /* Global LLVM variables */
    LLVMModuleRef module;
    LLVMBuilderRef builder;
    LLVMValueRef current_function;

    /* Integer type */
    LLVMTypeRef int_type;

    /* Initialize LLVM */
    void init_llvm() {
        module = LLVMModuleCreateWithName("zen_module");
        builder = LLVMCreateBuilder();
        int_type = LLVMInt32Type();
    }

    /* Finalize LLVM */
    void finalize_llvm() {
        LLVMDumpModule(module);
        LLVMDisposeBuilder(builder);
        LLVMDisposeModule(module);
    }

#line 110 "zen.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "zen.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUMBER = 3,                     /* NUMBER  */
  YYSYMBOL_STRING = 4,                     /* STRING  */
  YYSYMBOL_IDENTIFIER = 5,                 /* IDENTIFIER  */
  YYSYMBOL_LET = 6,                        /* LET  */
  YYSYMBOL_IS = 7,                         /* IS  */
  YYSYMBOL_IF = 8,                         /* IF  */
  YYSYMBOL_ELSE = 9,                       /* ELSE  */
  YYSYMBOL_WHILE = 10,                     /* WHILE  */
  YYSYMBOL_FOR = 11,                       /* FOR  */
  YYSYMBOL_IN = 12,                        /* IN  */
  YYSYMBOL_FUNCTION = 13,                  /* FUNCTION  */
  YYSYMBOL_END = 14,                       /* END  */
  YYSYMBOL_RETURN = 15,                    /* RETURN  */
  YYSYMBOL_PRINT = 16,                     /* PRINT  */
  YYSYMBOL_INPUT = 17,                     /* INPUT  */
  YYSYMBOL_PLUS = 18,                      /* PLUS  */
  YYSYMBOL_MINUS = 19,                     /* MINUS  */
  YYSYMBOL_TIMES = 20,                     /* TIMES  */
  YYSYMBOL_DIVIDED_BY = 21,                /* DIVIDED_BY  */
  YYSYMBOL_EQUALS = 22,                    /* EQUALS  */
  YYSYMBOL_NOT_EQUALS = 23,                /* NOT_EQUALS  */
  YYSYMBOL_GREATER_THAN = 24,              /* GREATER_THAN  */
  YYSYMBOL_LESS_THAN = 25,                 /* LESS_THAN  */
  YYSYMBOL_GREATER_OR_EQUAL = 26,          /* GREATER_OR_EQUAL  */
  YYSYMBOL_LESS_OR_EQUAL = 27,             /* LESS_OR_EQUAL  */
  YYSYMBOL_AND = 28,                       /* AND  */
  YYSYMBOL_OR = 29,                        /* OR  */
  YYSYMBOL_NOT = 30,                       /* NOT  */
  YYSYMBOL_SEMICOLON = 31,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 32,                     /* COMMA  */
  YYSYMBOL_LPAREN = 33,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 34,                    /* RPAREN  */
  YYSYMBOL_UMINUS = 35,                    /* UMINUS  */
  YYSYMBOL_LOWEST = 36,                    /* LOWEST  */
  YYSYMBOL_YYACCEPT = 37,                  /* $accept  */
  YYSYMBOL_program = 38,                   /* program  */
  YYSYMBOL_statements = 39,                /* statements  */
  YYSYMBOL_non_empty_statements = 40,      /* non_empty_statements  */
  YYSYMBOL_statement = 41,                 /* statement  */
  YYSYMBOL_variable_declaration = 42,      /* variable_declaration  */
  YYSYMBOL_assignment = 43,                /* assignment  */
  YYSYMBOL_function_declaration = 44,      /* function_declaration  */
  YYSYMBOL_parameter_list_opt = 45,        /* parameter_list_opt  */
  YYSYMBOL_parameter_list = 46,            /* parameter_list  */
  YYSYMBOL_control_structure = 47,         /* control_structure  */
  YYSYMBOL_if_statement = 48,              /* if_statement  */
  YYSYMBOL_while_loop = 49,                /* while_loop  */
  YYSYMBOL_for_loop = 50,                  /* for_loop  */
  YYSYMBOL_expression_statement = 51,      /* expression_statement  */
  YYSYMBOL_print_statement = 52,           /* print_statement  */
  YYSYMBOL_return_statement = 53,          /* return_statement  */
  YYSYMBOL_expression = 54,                /* expression  */
  YYSYMBOL_logical_or_expression = 55,     /* logical_or_expression  */
  YYSYMBOL_logical_and_expression = 56,    /* logical_and_expression  */
  YYSYMBOL_equality_expression = 57,       /* equality_expression  */
  YYSYMBOL_relational_expression = 58,     /* relational_expression  */
  YYSYMBOL_additive_expression = 59,       /* additive_expression  */
  YYSYMBOL_multiplicative_expression = 60, /* multiplicative_expression  */
  YYSYMBOL_unary_expression = 61,          /* unary_expression  */
  YYSYMBOL_primary_expression = 62,        /* primary_expression  */
  YYSYMBOL_argument_list_opt = 63,         /* argument_list_opt  */
  YYSYMBOL_argument_list = 64              /* argument_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  50
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   91

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  62
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  112

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   291


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      35,    36
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    90,    90,   107,   112,   118,   125,   135,   139,   143,
     147,   151,   155,   159,   163,   172,   180,   191,   202,   215,
     218,   225,   233,   243,   247,   251,   258,   267,   281,   292,
     304,   314,   324,   334,   341,   345,   352,   356,   363,   367,
     371,   378,   382,   386,   390,   394,   401,   405,   409,   416,
     420,   424,   431,   435,   439,   446,   470,   481,   485,   493,
     498,   505,   512
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUMBER", "STRING",
  "IDENTIFIER", "LET", "IS", "IF", "ELSE", "WHILE", "FOR", "IN",
  "FUNCTION", "END", "RETURN", "PRINT", "INPUT", "PLUS", "MINUS", "TIMES",
  "DIVIDED_BY", "EQUALS", "NOT_EQUALS", "GREATER_THAN", "LESS_THAN",
  "GREATER_OR_EQUAL", "LESS_OR_EQUAL", "AND", "OR", "NOT", "SEMICOLON",
  "COMMA", "LPAREN", "RPAREN", "UMINUS", "LOWEST", "$accept", "program",
  "statements", "non_empty_statements", "statement",
  "variable_declaration", "assignment", "function_declaration",
  "parameter_list_opt", "parameter_list", "control_structure",
  "if_statement", "while_loop", "for_loop", "expression_statement",
  "print_statement", "return_statement", "expression",
  "logical_or_expression", "logical_and_expression", "equality_expression",
  "relational_expression", "additive_expression",
  "multiplicative_expression", "unary_expression", "primary_expression",
  "argument_list_opt", "argument_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-40)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       7,   -40,    -1,    16,    11,    11,    20,    26,    11,    11,
      11,    11,   -40,    11,    29,   -40,   -40,     7,   -40,   -40,
     -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,     8,    30,
      34,     5,    21,    24,    33,   -40,   -40,    11,    11,     4,
       3,     7,     7,    54,    35,    39,    40,   -40,   -40,    38,
     -40,   -40,   -40,    11,    11,    11,    11,    11,    11,    11,
      11,    11,    11,    11,    11,    42,    43,    44,   -40,    11,
     -40,    10,    60,    11,    71,   -40,   -40,   -40,    34,     5,
      21,    21,    24,    24,    24,    24,    33,    33,   -40,   -40,
     -40,    11,   -40,    46,     7,   -40,   -40,     7,    47,    48,
     -40,   -40,   -40,    66,    67,    71,     7,   -40,   -40,   -40,
      69,   -40
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,    57,    56,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    14,     0,     0,     2,     3,     5,     7,     8,
       9,    10,    23,    24,    25,    11,    12,    13,     0,    33,
      35,    37,    40,    45,    48,    51,    54,     0,    59,     0,
      56,     4,     4,     0,     0,     0,     0,    52,    53,     0,
       1,     6,    30,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    61,     0,    60,     0,
      15,     0,     0,     0,    19,    32,    31,    58,    34,    36,
      38,    39,    41,    42,    43,    44,    46,    47,    49,    50,
      17,     0,    55,     0,     4,    26,    28,     4,    21,     0,
      20,    62,    16,     0,     0,     0,     4,    27,    29,    22,
       0,    18
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -40,   -40,   -39,    68,   -40,   -40,   -40,   -40,   -40,   -21,
     -40,   -40,   -40,   -40,   -40,   -40,   -40,    -4,   -40,    36,
      32,     1,    -8,     2,    -3,   -40,   -40,     0
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    14,    15,    16,    17,    18,    19,    20,    99,   100,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    67,    68
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      41,    42,    71,    72,    45,    46,    37,    47,    48,    49,
       1,    69,     2,     3,     1,     4,    40,     5,     6,    94,
       7,    39,     8,     9,    95,    43,    10,    55,    56,    50,
      10,    44,    38,    65,    66,    70,    38,    11,    12,    52,
      13,    11,    61,    62,    13,    57,    58,    59,    60,    82,
      83,    84,    85,    63,    64,   103,    80,    81,   104,    53,
      88,    89,    54,    86,    87,    93,    73,   110,    74,    97,
      75,    76,    77,    90,    96,    91,    98,   102,    92,   105,
     107,   108,   106,   111,   109,    51,    79,    66,     0,    78,
       0,   101
};

static const yytype_int8 yycheck[] =
{
       4,     5,    41,    42,     8,     9,     7,    10,    11,    13,
       3,     7,     5,     6,     3,     8,     5,    10,    11,     9,
      13,     5,    15,    16,    14,     5,    19,    22,    23,     0,
      19,     5,    33,    37,    38,    31,    33,    30,    31,    31,
      33,    30,    18,    19,    33,    24,    25,    26,    27,    57,
      58,    59,    60,    20,    21,    94,    55,    56,    97,    29,
      63,    64,    28,    61,    62,    69,    12,   106,    33,    73,
      31,    31,    34,    31,    14,    32,     5,    31,    34,    32,
      14,    14,    34,    14,   105,    17,    54,    91,    -1,    53,
      -1,    91
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     5,     6,     8,    10,    11,    13,    15,    16,
      19,    30,    31,    33,    38,    39,    40,    41,    42,    43,
      44,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,     7,    33,     5,
       5,    54,    54,     5,     5,    54,    54,    61,    61,    54,
       0,    40,    31,    29,    28,    22,    23,    24,    25,    26,
      27,    18,    19,    20,    21,    54,    54,    63,    64,     7,
      31,    39,    39,    12,    33,    31,    31,    34,    56,    57,
      58,    58,    59,    59,    59,    59,    60,    60,    61,    61,
      31,    32,    34,    54,     9,    14,    14,    54,     5,    45,
      46,    64,    31,    39,    39,    32,    34,    14,    14,    46,
      39,    14
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    37,    38,    39,    39,    40,    40,    41,    41,    41,
      41,    41,    41,    41,    41,    42,    42,    43,    44,    45,
      45,    46,    46,    47,    47,    47,    48,    48,    49,    50,
      51,    52,    53,    54,    55,    55,    56,    56,    57,    57,
      57,    58,    58,    58,    58,    58,    59,    59,    59,    60,
      60,    60,    61,    61,    61,    62,    62,    62,    62,    63,
      63,    64,    64
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     0,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     5,     4,     7,     0,
       1,     1,     3,     1,     1,     1,     4,     6,     4,     6,
       2,     3,     3,     1,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     2,     2,     1,     4,     1,     1,     3,     0,
       1,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: statements  */
#line 91 "zen.y"
    {
        /* Initialize LLVM */
        init_llvm();

        /* Generate code */
        if ((yyvsp[0].statements) != NULL) {
            codegen_statements((yyvsp[0].statements));
        }

        /* Finalize LLVM */
        finalize_llvm();
    }
#line 1248 "zen.tab.c"
    break;

  case 3: /* statements: non_empty_statements  */
#line 108 "zen.y"
    {
        (yyval.statements) = (yyvsp[0].statements);
    }
#line 1256 "zen.tab.c"
    break;

  case 4: /* statements: %empty  */
#line 112 "zen.y"
    {
        (yyval.statements) = NULL;
    }
#line 1264 "zen.tab.c"
    break;

  case 5: /* non_empty_statements: statement  */
#line 119 "zen.y"
    {
        struct Statements* new_node = malloc(sizeof(struct Statements));
        new_node->statement = (yyvsp[0].statement);
        new_node->next = NULL;
        (yyval.statements) = new_node;
    }
#line 1275 "zen.tab.c"
    break;

  case 6: /* non_empty_statements: statement non_empty_statements  */
#line 126 "zen.y"
    {
        struct Statements* new_node = malloc(sizeof(struct Statements));
        new_node->statement = (yyvsp[-1].statement);
        new_node->next = (yyvsp[0].statements);
        (yyval.statements) = new_node;
    }
#line 1286 "zen.tab.c"
    break;

  case 7: /* statement: variable_declaration  */
#line 136 "zen.y"
    {
        (yyval.statement) = (yyvsp[0].statement);
    }
#line 1294 "zen.tab.c"
    break;

  case 8: /* statement: assignment  */
#line 140 "zen.y"
    {
        (yyval.statement) = (yyvsp[0].statement);
    }
#line 1302 "zen.tab.c"
    break;

  case 9: /* statement: function_declaration  */
#line 144 "zen.y"
    {
        (yyval.statement) = (yyvsp[0].statement);
    }
#line 1310 "zen.tab.c"
    break;

  case 10: /* statement: control_structure  */
#line 148 "zen.y"
    {
        (yyval.statement) = (yyvsp[0].statement);
    }
#line 1318 "zen.tab.c"
    break;

  case 11: /* statement: expression_statement  */
#line 152 "zen.y"
    {
        (yyval.statement) = (yyvsp[0].statement);
    }
#line 1326 "zen.tab.c"
    break;

  case 12: /* statement: print_statement  */
#line 156 "zen.y"
    {
        (yyval.statement) = (yyvsp[0].statement);
    }
#line 1334 "zen.tab.c"
    break;

  case 13: /* statement: return_statement  */
#line 160 "zen.y"
    {
        (yyval.statement) = (yyvsp[0].statement);
    }
#line 1342 "zen.tab.c"
    break;

  case 14: /* statement: SEMICOLON  */
#line 164 "zen.y"
    {
        struct Statement* stmt = malloc(sizeof(struct Statement));
        stmt->type = STMT_EMPTY_STATEMENT;
        (yyval.statement) = stmt;
    }
#line 1352 "zen.tab.c"
    break;

  case 15: /* variable_declaration: LET IDENTIFIER SEMICOLON  */
#line 173 "zen.y"
    {
        struct Statement* stmt = malloc(sizeof(struct Statement));
        stmt->type = STMT_VARIABLE_DECLARATION;
        stmt->data.variable_declaration.identifier = strdup((yyvsp[-1].strVal));
        stmt->data.variable_declaration.value = NULL;
        (yyval.statement) = stmt;
    }
#line 1364 "zen.tab.c"
    break;

  case 16: /* variable_declaration: LET IDENTIFIER IS expression SEMICOLON  */
#line 181 "zen.y"
    {
        struct Statement* stmt = malloc(sizeof(struct Statement));
        stmt->type = STMT_VARIABLE_DECLARATION;
        stmt->data.variable_declaration.identifier = strdup((yyvsp[-3].strVal));
        stmt->data.variable_declaration.value = (yyvsp[-1].value);
        (yyval.statement) = stmt;
    }
#line 1376 "zen.tab.c"
    break;

  case 17: /* assignment: IDENTIFIER IS expression SEMICOLON  */
#line 192 "zen.y"
    {
        struct Statement* stmt = malloc(sizeof(struct Statement));
        stmt->type = STMT_ASSIGNMENT;
        stmt->data.assignment.identifier = strdup((yyvsp[-3].strVal));
        stmt->data.assignment.expression = (yyvsp[-1].value);
        (yyval.statement) = stmt;
    }
#line 1388 "zen.tab.c"
    break;

  case 18: /* function_declaration: FUNCTION IDENTIFIER LPAREN parameter_list_opt RPAREN statements END  */
#line 203 "zen.y"
    {
        struct Statement* stmt = malloc(sizeof(struct Statement));
        stmt->type = STMT_FUNCTION_DECLARATION;
        stmt->data.function_declaration.identifier = strdup((yyvsp[-5].strVal));
        stmt->data.function_declaration.params = (yyvsp[-3].paramList);
        stmt->data.function_declaration.body = (yyvsp[-1].statements);
        (yyval.statement) = stmt;
    }
#line 1401 "zen.tab.c"
    break;

  case 19: /* parameter_list_opt: %empty  */
#line 215 "zen.y"
    {
        (yyval.paramList) = NULL;
    }
#line 1409 "zen.tab.c"
    break;

  case 20: /* parameter_list_opt: parameter_list  */
#line 219 "zen.y"
    {
        (yyval.paramList) = (yyvsp[0].paramList);
    }
#line 1417 "zen.tab.c"
    break;

  case 21: /* parameter_list: IDENTIFIER  */
#line 226 "zen.y"
    {
        struct ParamList* params = malloc(sizeof(struct ParamList));
        params->param_count = 1;
        params->param_names = malloc(sizeof(char*));
        params->param_names[0] = strdup((yyvsp[0].strVal));
        (yyval.paramList) = params;
    }
#line 1429 "zen.tab.c"
    break;

  case 22: /* parameter_list: IDENTIFIER COMMA parameter_list  */
#line 234 "zen.y"
    {
        (yyval.paramList) = (yyvsp[0].paramList);
        (yyval.paramList)->param_count += 1;
        (yyval.paramList)->param_names = realloc((yyval.paramList)->param_names, sizeof(char*) * (yyval.paramList)->param_count);
        (yyval.paramList)->param_names[(yyval.paramList)->param_count - 1] = strdup((yyvsp[-2].strVal));
    }
#line 1440 "zen.tab.c"
    break;

  case 23: /* control_structure: if_statement  */
#line 244 "zen.y"
    {
        (yyval.statement) = (yyvsp[0].statement);
    }
#line 1448 "zen.tab.c"
    break;

  case 24: /* control_structure: while_loop  */
#line 248 "zen.y"
    {
        (yyval.statement) = (yyvsp[0].statement);
    }
#line 1456 "zen.tab.c"
    break;

  case 25: /* control_structure: for_loop  */
#line 252 "zen.y"
    {
        (yyval.statement) = (yyvsp[0].statement);
    }
#line 1464 "zen.tab.c"
    break;

  case 26: /* if_statement: IF expression statements END  */
#line 259 "zen.y"
    {
        struct Statement* stmt = malloc(sizeof(struct Statement));
        stmt->type = STMT_IF_STATEMENT;
        stmt->data.if_statement.condition = (yyvsp[-2].value);
        stmt->data.if_statement.then_branch = (yyvsp[-1].statements);
        stmt->data.if_statement.else_clause = NULL;
        (yyval.statement) = stmt;
    }
#line 1477 "zen.tab.c"
    break;

  case 27: /* if_statement: IF expression statements ELSE statements END  */
#line 268 "zen.y"
    {
        struct Statement* stmt = malloc(sizeof(struct Statement));
        stmt->type = STMT_IF_STATEMENT;
        stmt->data.if_statement.condition = (yyvsp[-4].value);
        stmt->data.if_statement.then_branch = (yyvsp[-3].statements);
        struct ElseClause* else_clause = malloc(sizeof(struct ElseClause));
        else_clause->statements = (yyvsp[-1].statements);
        stmt->data.if_statement.else_clause = else_clause;
        (yyval.statement) = stmt;
    }
#line 1492 "zen.tab.c"
    break;

  case 28: /* while_loop: WHILE expression statements END  */
#line 282 "zen.y"
    {
        struct Statement* stmt = malloc(sizeof(struct Statement));
        stmt->type = STMT_WHILE_LOOP;
        stmt->data.while_loop.condition = (yyvsp[-2].value);
        stmt->data.while_loop.body = (yyvsp[-1].statements);
        (yyval.statement) = stmt;
    }
#line 1504 "zen.tab.c"
    break;

  case 29: /* for_loop: FOR IDENTIFIER IN expression statements END  */
#line 293 "zen.y"
    {
        struct Statement* stmt = malloc(sizeof(struct Statement));
        stmt->type = STMT_FOR_LOOP;
        stmt->data.for_loop.iterator = strdup((yyvsp[-4].strVal));
        stmt->data.for_loop.end_expression = (yyvsp[-2].value);
        stmt->data.for_loop.body = (yyvsp[-1].statements);
        (yyval.statement) = stmt;
    }
#line 1517 "zen.tab.c"
    break;

  case 30: /* expression_statement: expression SEMICOLON  */
#line 305 "zen.y"
    {
        struct Statement* stmt = malloc(sizeof(struct Statement));
        stmt->type = STMT_EXPRESSION_STATEMENT;
        stmt->data.expression_statement = (yyvsp[-1].value);
        (yyval.statement) = stmt;
    }
#line 1528 "zen.tab.c"
    break;

  case 31: /* print_statement: PRINT expression SEMICOLON  */
#line 315 "zen.y"
    {
        struct Statement* stmt = malloc(sizeof(struct Statement));
        stmt->type = STMT_PRINT_STATEMENT;
        stmt->data.print_statement.expression = (yyvsp[-1].value);
        (yyval.statement) = stmt;
    }
#line 1539 "zen.tab.c"
    break;

  case 32: /* return_statement: RETURN expression SEMICOLON  */
#line 325 "zen.y"
    {
        struct Statement* stmt = malloc(sizeof(struct Statement));
        stmt->type = STMT_RETURN_STATEMENT;
        stmt->data.return_statement.expression = (yyvsp[-1].value);
        (yyval.statement) = stmt;
    }
#line 1550 "zen.tab.c"
    break;

  case 33: /* expression: logical_or_expression  */
#line 335 "zen.y"
    {
        (yyval.value) = (yyvsp[0].value);
    }
#line 1558 "zen.tab.c"
    break;

  case 34: /* logical_or_expression: logical_or_expression OR logical_and_expression  */
#line 342 "zen.y"
    {
        (yyval.value) = LLVMBuildOr(builder, (yyvsp[-2].value), (yyvsp[0].value), "ortmp");
    }
#line 1566 "zen.tab.c"
    break;

  case 35: /* logical_or_expression: logical_and_expression  */
#line 346 "zen.y"
    {
        (yyval.value) = (yyvsp[0].value);
    }
#line 1574 "zen.tab.c"
    break;

  case 36: /* logical_and_expression: logical_and_expression AND equality_expression  */
#line 353 "zen.y"
    {
        (yyval.value) = LLVMBuildAnd(builder, (yyvsp[-2].value), (yyvsp[0].value), "andtmp");
    }
#line 1582 "zen.tab.c"
    break;

  case 37: /* logical_and_expression: equality_expression  */
#line 357 "zen.y"
    {
        (yyval.value) = (yyvsp[0].value);
    }
#line 1590 "zen.tab.c"
    break;

  case 38: /* equality_expression: equality_expression EQUALS relational_expression  */
#line 364 "zen.y"
    {
        (yyval.value) = LLVMBuildICmp(builder, LLVMIntEQ, (yyvsp[-2].value), (yyvsp[0].value), "eqtmp");
    }
#line 1598 "zen.tab.c"
    break;

  case 39: /* equality_expression: equality_expression NOT_EQUALS relational_expression  */
#line 368 "zen.y"
    {
        (yyval.value) = LLVMBuildICmp(builder, LLVMIntNE, (yyvsp[-2].value), (yyvsp[0].value), "netmp");
    }
#line 1606 "zen.tab.c"
    break;

  case 40: /* equality_expression: relational_expression  */
#line 372 "zen.y"
    {
        (yyval.value) = (yyvsp[0].value);
    }
#line 1614 "zen.tab.c"
    break;

  case 41: /* relational_expression: relational_expression GREATER_THAN additive_expression  */
#line 379 "zen.y"
    {
        (yyval.value) = LLVMBuildICmp(builder, LLVMIntSGT, (yyvsp[-2].value), (yyvsp[0].value), "gttmp");
    }
#line 1622 "zen.tab.c"
    break;

  case 42: /* relational_expression: relational_expression LESS_THAN additive_expression  */
#line 383 "zen.y"
    {
        (yyval.value) = LLVMBuildICmp(builder, LLVMIntSLT, (yyvsp[-2].value), (yyvsp[0].value), "lttmp");
    }
#line 1630 "zen.tab.c"
    break;

  case 43: /* relational_expression: relational_expression GREATER_OR_EQUAL additive_expression  */
#line 387 "zen.y"
    {
        (yyval.value) = LLVMBuildICmp(builder, LLVMIntSGE, (yyvsp[-2].value), (yyvsp[0].value), "getmp");
    }
#line 1638 "zen.tab.c"
    break;

  case 44: /* relational_expression: relational_expression LESS_OR_EQUAL additive_expression  */
#line 391 "zen.y"
    {
        (yyval.value) = LLVMBuildICmp(builder, LLVMIntSLE, (yyvsp[-2].value), (yyvsp[0].value), "letmp");
    }
#line 1646 "zen.tab.c"
    break;

  case 45: /* relational_expression: additive_expression  */
#line 395 "zen.y"
    {
        (yyval.value) = (yyvsp[0].value);
    }
#line 1654 "zen.tab.c"
    break;

  case 46: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 402 "zen.y"
    {
        (yyval.value) = LLVMBuildAdd(builder, (yyvsp[-2].value), (yyvsp[0].value), "addtmp");
    }
#line 1662 "zen.tab.c"
    break;

  case 47: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 406 "zen.y"
    {
        (yyval.value) = LLVMBuildSub(builder, (yyvsp[-2].value), (yyvsp[0].value), "subtmp");
    }
#line 1670 "zen.tab.c"
    break;

  case 48: /* additive_expression: multiplicative_expression  */
#line 410 "zen.y"
    {
        (yyval.value) = (yyvsp[0].value);
    }
#line 1678 "zen.tab.c"
    break;

  case 49: /* multiplicative_expression: multiplicative_expression TIMES unary_expression  */
#line 417 "zen.y"
    {
        (yyval.value) = LLVMBuildMul(builder, (yyvsp[-2].value), (yyvsp[0].value), "multmp");
    }
#line 1686 "zen.tab.c"
    break;

  case 50: /* multiplicative_expression: multiplicative_expression DIVIDED_BY unary_expression  */
#line 421 "zen.y"
    {
        (yyval.value) = LLVMBuildSDiv(builder, (yyvsp[-2].value), (yyvsp[0].value), "divtmp");
    }
#line 1694 "zen.tab.c"
    break;

  case 51: /* multiplicative_expression: unary_expression  */
#line 425 "zen.y"
    {
        (yyval.value) = (yyvsp[0].value);
    }
#line 1702 "zen.tab.c"
    break;

  case 52: /* unary_expression: MINUS unary_expression  */
#line 432 "zen.y"
    {
        (yyval.value) = LLVMBuildNeg(builder, (yyvsp[0].value), "negtmp");
    }
#line 1710 "zen.tab.c"
    break;

  case 53: /* unary_expression: NOT unary_expression  */
#line 436 "zen.y"
    {
        (yyval.value) = LLVMBuildNot(builder, (yyvsp[0].value), "nottmp");
    }
#line 1718 "zen.tab.c"
    break;

  case 54: /* unary_expression: primary_expression  */
#line 440 "zen.y"
    {
        (yyval.value) = (yyvsp[0].value);
    }
#line 1726 "zen.tab.c"
    break;

  case 55: /* primary_expression: IDENTIFIER LPAREN argument_list_opt RPAREN  */
#line 447 "zen.y"
    {
        LLVMValueRef func = LLVMGetNamedFunction(module, (yyvsp[-3].strVal));
        if (!func) {
            fprintf(stderr, "Error: Undefined function '%s'\n", (yyvsp[-3].strVal));
            exit(1);
        }

        LLVMTypeRef funcType = LLVMTypeOf(func);
        if (!funcType) {
            fprintf(stderr, "Error: Unable to determine type of function '%s'\n", (yyvsp[-3].strVal));
            exit(1);
        }

        LLVMValueRef result = LLVMBuildCall2(
            builder,
            LLVMGetElementType(funcType),
            func,
            (yyvsp[-1].argList)->args,
            (yyvsp[-1].argList)->arg_count,
            "calltmp"
        );
        (yyval.value) = result;
    }
#line 1754 "zen.tab.c"
    break;

  case 56: /* primary_expression: IDENTIFIER  */
#line 471 "zen.y"
    {
        LLVMValueRef var = get_variable((yyvsp[0].strVal));
        if (!var) {
            fprintf(stderr, "Error: Undefined variable '%s'\n", (yyvsp[0].strVal));
            exit(1);
        }

        LLVMTypeRef varType = LLVMGetElementType(LLVMTypeOf(var));
        (yyval.value) = LLVMBuildLoad2(builder, varType, var, (yyvsp[0].strVal));
    }
#line 1769 "zen.tab.c"
    break;

  case 57: /* primary_expression: NUMBER  */
#line 482 "zen.y"
    {
        (yyval.value) = LLVMConstInt(int_type, (yyvsp[0].intVal), 0);
    }
#line 1777 "zen.tab.c"
    break;

  case 58: /* primary_expression: LPAREN expression RPAREN  */
#line 486 "zen.y"
    {
        (yyval.value) = (yyvsp[-1].value);
    }
#line 1785 "zen.tab.c"
    break;

  case 59: /* argument_list_opt: %empty  */
#line 493 "zen.y"
    {
        (yyval.argList) = malloc(sizeof(struct ArgList));
        (yyval.argList)->arg_count = 0;
        (yyval.argList)->args = NULL;
    }
#line 1795 "zen.tab.c"
    break;

  case 60: /* argument_list_opt: argument_list  */
#line 499 "zen.y"
    {
        (yyval.argList) = (yyvsp[0].argList);
    }
#line 1803 "zen.tab.c"
    break;

  case 61: /* argument_list: expression  */
#line 506 "zen.y"
    {
        (yyval.argList) = malloc(sizeof(struct ArgList));
        (yyval.argList)->arg_count = 1;
        (yyval.argList)->args = malloc(sizeof(LLVMValueRef));
        (yyval.argList)->args[0] = (yyvsp[0].value);
    }
#line 1814 "zen.tab.c"
    break;

  case 62: /* argument_list: expression COMMA argument_list  */
#line 513 "zen.y"
    {
        (yyval.argList) = (yyvsp[0].argList);
        (yyval.argList)->arg_count += 1;
        (yyval.argList)->args = realloc((yyval.argList)->args, sizeof(LLVMValueRef) * (yyval.argList)->arg_count);
        (yyval.argList)->args[(yyval.argList)->arg_count - 1] = (yyvsp[-2].value);
    }
#line 1825 "zen.tab.c"
    break;


#line 1829 "zen.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 520 "zen.y"


/* Error Handling */
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

/* Main Function */
int main(int argc, char **argv) {
    return yyparse();
}
