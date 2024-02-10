// A Bison parser, made by GNU Bison 3.5.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.





#include "parser.hpp"


// Unqualified %code blocks.
#line 40 "parser.yy"

# include "driver.hpp"

#line 49 "parser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 140 "parser.cpp"


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
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
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  parser::parser (driver& drv_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      drv (drv_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_number_type
  parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[+state];
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 45: // assignment
        value.YY_MOVE_OR_COPY< AssignmentExprAST* > (YY_MOVE (that.value));
        break;

      case 46: // block
        value.YY_MOVE_OR_COPY< BlockAST* > (YY_MOVE (that.value));
        break;

      case 48: // initexp
      case 50: // exp
      case 51: // idexp
      case 52: // condexp
      case 53: // relexp
      case 56: // expif
        value.YY_MOVE_OR_COPY< ExprAST* > (YY_MOVE (that.value));
        break;

      case 60: // forstmt
        value.YY_MOVE_OR_COPY< ForStatementAST* > (YY_MOVE (that.value));
        break;

      case 40: // definition
        value.YY_MOVE_OR_COPY< FunctionAST* > (YY_MOVE (that.value));
        break;

      case 41: // globalvar
        value.YY_MOVE_OR_COPY< GlobalVariableAST* > (YY_MOVE (that.value));
        break;

      case 59: // ifstmt
        value.YY_MOVE_OR_COPY< IfStatementAST* > (YY_MOVE (that.value));
        break;

      case 49: // binding
      case 61: // init
        value.YY_MOVE_OR_COPY< InitAST* > (YY_MOVE (that.value));
        break;

      case 42: // external
      case 43: // proto
        value.YY_MOVE_OR_COPY< PrototypeAST* > (YY_MOVE (that.value));
        break;

      case 38: // program
      case 39: // top
        value.YY_MOVE_OR_COPY< RootAST* > (YY_MOVE (that.value));
        break;

      case 58: // stmt
        value.YY_MOVE_OR_COPY< StatementAST* > (YY_MOVE (that.value));
        break;

      case 34: // "number"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 33: // "id"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case 54: // optexp
      case 55: // exparr
        value.YY_MOVE_OR_COPY< std::vector<ExprAST*> > (YY_MOVE (that.value));
        break;

      case 47: // vardefs
        value.YY_MOVE_OR_COPY< std::vector<InitAST*> > (YY_MOVE (that.value));
        break;

      case 57: // stmts
        value.YY_MOVE_OR_COPY< std::vector<StatementAST*> > (YY_MOVE (that.value));
        break;

      case 44: // idseq
        value.YY_MOVE_OR_COPY< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 45: // assignment
        value.move< AssignmentExprAST* > (YY_MOVE (that.value));
        break;

      case 46: // block
        value.move< BlockAST* > (YY_MOVE (that.value));
        break;

      case 48: // initexp
      case 50: // exp
      case 51: // idexp
      case 52: // condexp
      case 53: // relexp
      case 56: // expif
        value.move< ExprAST* > (YY_MOVE (that.value));
        break;

      case 60: // forstmt
        value.move< ForStatementAST* > (YY_MOVE (that.value));
        break;

      case 40: // definition
        value.move< FunctionAST* > (YY_MOVE (that.value));
        break;

      case 41: // globalvar
        value.move< GlobalVariableAST* > (YY_MOVE (that.value));
        break;

      case 59: // ifstmt
        value.move< IfStatementAST* > (YY_MOVE (that.value));
        break;

      case 49: // binding
      case 61: // init
        value.move< InitAST* > (YY_MOVE (that.value));
        break;

      case 42: // external
      case 43: // proto
        value.move< PrototypeAST* > (YY_MOVE (that.value));
        break;

      case 38: // program
      case 39: // top
        value.move< RootAST* > (YY_MOVE (that.value));
        break;

      case 58: // stmt
        value.move< StatementAST* > (YY_MOVE (that.value));
        break;

      case 34: // "number"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 33: // "id"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case 54: // optexp
      case 55: // exparr
        value.move< std::vector<ExprAST*> > (YY_MOVE (that.value));
        break;

      case 47: // vardefs
        value.move< std::vector<InitAST*> > (YY_MOVE (that.value));
        break;

      case 57: // stmts
        value.move< std::vector<StatementAST*> > (YY_MOVE (that.value));
        break;

      case 44: // idseq
        value.move< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 45: // assignment
        value.copy< AssignmentExprAST* > (that.value);
        break;

      case 46: // block
        value.copy< BlockAST* > (that.value);
        break;

      case 48: // initexp
      case 50: // exp
      case 51: // idexp
      case 52: // condexp
      case 53: // relexp
      case 56: // expif
        value.copy< ExprAST* > (that.value);
        break;

      case 60: // forstmt
        value.copy< ForStatementAST* > (that.value);
        break;

      case 40: // definition
        value.copy< FunctionAST* > (that.value);
        break;

      case 41: // globalvar
        value.copy< GlobalVariableAST* > (that.value);
        break;

      case 59: // ifstmt
        value.copy< IfStatementAST* > (that.value);
        break;

      case 49: // binding
      case 61: // init
        value.copy< InitAST* > (that.value);
        break;

      case 42: // external
      case 43: // proto
        value.copy< PrototypeAST* > (that.value);
        break;

      case 38: // program
      case 39: // top
        value.copy< RootAST* > (that.value);
        break;

      case 58: // stmt
        value.copy< StatementAST* > (that.value);
        break;

      case 34: // "number"
        value.copy< double > (that.value);
        break;

      case 33: // "id"
        value.copy< std::string > (that.value);
        break;

      case 54: // optexp
      case 55: // exparr
        value.copy< std::vector<ExprAST*> > (that.value);
        break;

      case 47: // vardefs
        value.copy< std::vector<InitAST*> > (that.value);
        break;

      case 57: // stmts
        value.copy< std::vector<StatementAST*> > (that.value);
        break;

      case 44: // idseq
        value.copy< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 45: // assignment
        value.move< AssignmentExprAST* > (that.value);
        break;

      case 46: // block
        value.move< BlockAST* > (that.value);
        break;

      case 48: // initexp
      case 50: // exp
      case 51: // idexp
      case 52: // condexp
      case 53: // relexp
      case 56: // expif
        value.move< ExprAST* > (that.value);
        break;

      case 60: // forstmt
        value.move< ForStatementAST* > (that.value);
        break;

      case 40: // definition
        value.move< FunctionAST* > (that.value);
        break;

      case 41: // globalvar
        value.move< GlobalVariableAST* > (that.value);
        break;

      case 59: // ifstmt
        value.move< IfStatementAST* > (that.value);
        break;

      case 49: // binding
      case 61: // init
        value.move< InitAST* > (that.value);
        break;

      case 42: // external
      case 43: // proto
        value.move< PrototypeAST* > (that.value);
        break;

      case 38: // program
      case 39: // top
        value.move< RootAST* > (that.value);
        break;

      case 58: // stmt
        value.move< StatementAST* > (that.value);
        break;

      case 34: // "number"
        value.move< double > (that.value);
        break;

      case 33: // "id"
        value.move< std::string > (that.value);
        break;

      case 54: // optexp
      case 55: // exparr
        value.move< std::vector<ExprAST*> > (that.value);
        break;

      case 47: // vardefs
        value.move< std::vector<InitAST*> > (that.value);
        break;

      case 57: // stmts
        value.move< std::vector<StatementAST*> > (that.value);
        break;

      case 44: // idseq
        value.move< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (drv));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 45: // assignment
        yylhs.value.emplace< AssignmentExprAST* > ();
        break;

      case 46: // block
        yylhs.value.emplace< BlockAST* > ();
        break;

      case 48: // initexp
      case 50: // exp
      case 51: // idexp
      case 52: // condexp
      case 53: // relexp
      case 56: // expif
        yylhs.value.emplace< ExprAST* > ();
        break;

      case 60: // forstmt
        yylhs.value.emplace< ForStatementAST* > ();
        break;

      case 40: // definition
        yylhs.value.emplace< FunctionAST* > ();
        break;

      case 41: // globalvar
        yylhs.value.emplace< GlobalVariableAST* > ();
        break;

      case 59: // ifstmt
        yylhs.value.emplace< IfStatementAST* > ();
        break;

      case 49: // binding
      case 61: // init
        yylhs.value.emplace< InitAST* > ();
        break;

      case 42: // external
      case 43: // proto
        yylhs.value.emplace< PrototypeAST* > ();
        break;

      case 38: // program
      case 39: // top
        yylhs.value.emplace< RootAST* > ();
        break;

      case 58: // stmt
        yylhs.value.emplace< StatementAST* > ();
        break;

      case 34: // "number"
        yylhs.value.emplace< double > ();
        break;

      case 33: // "id"
        yylhs.value.emplace< std::string > ();
        break;

      case 54: // optexp
      case 55: // exparr
        yylhs.value.emplace< std::vector<ExprAST*> > ();
        break;

      case 47: // vardefs
        yylhs.value.emplace< std::vector<InitAST*> > ();
        break;

      case 57: // stmts
        yylhs.value.emplace< std::vector<StatementAST*> > ();
        break;

      case 44: // idseq
        yylhs.value.emplace< std::vector<std::string> > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 109 "parser.yy"
                        { drv.root = yystack_[0].value.as < RootAST* > (); }
#line 952 "parser.cpp"
    break;

  case 3:
#line 113 "parser.yy"
                        { yylhs.value.as < RootAST* > () = new SeqAST(nullptr,nullptr); }
#line 958 "parser.cpp"
    break;

  case 4:
#line 114 "parser.yy"
                        { yylhs.value.as < RootAST* > () = new SeqAST(yystack_[2].value.as < RootAST* > (),yystack_[0].value.as < RootAST* > ()); }
#line 964 "parser.cpp"
    break;

  case 5:
#line 118 "parser.yy"
                        { yylhs.value.as < RootAST* > () = nullptr; }
#line 970 "parser.cpp"
    break;

  case 6:
#line 119 "parser.yy"
                        { yylhs.value.as < RootAST* > () = yystack_[0].value.as < FunctionAST* > (); }
#line 976 "parser.cpp"
    break;

  case 7:
#line 120 "parser.yy"
                        { yylhs.value.as < RootAST* > () = yystack_[0].value.as < GlobalVariableAST* > (); }
#line 982 "parser.cpp"
    break;

  case 8:
#line 121 "parser.yy"
                        { yylhs.value.as < RootAST* > () = yystack_[0].value.as < PrototypeAST* > (); }
#line 988 "parser.cpp"
    break;

  case 9:
#line 125 "parser.yy"
                          { yylhs.value.as < FunctionAST* > () = new FunctionAST(yystack_[1].value.as < PrototypeAST* > (),yystack_[0].value.as < BlockAST* > ()); yystack_[1].value.as < PrototypeAST* > ()->noemit(); }
#line 994 "parser.cpp"
    break;

  case 10:
#line 129 "parser.yy"
                                  { yylhs.value.as < GlobalVariableAST* > () = new GlobalVariableAST(yystack_[0].value.as < std::string > ()); }
#line 1000 "parser.cpp"
    break;

  case 11:
#line 130 "parser.yy"
                                  { yylhs.value.as < GlobalVariableAST* > () = new GlobalVariableAST(yystack_[3].value.as < std::string > (),yystack_[1].value.as < double > (),true); }
#line 1006 "parser.cpp"
    break;

  case 12:
#line 134 "parser.yy"
                        { yylhs.value.as < PrototypeAST* > () = yystack_[0].value.as < PrototypeAST* > (); }
#line 1012 "parser.cpp"
    break;

  case 13:
#line 138 "parser.yy"
                        { yylhs.value.as < PrototypeAST* > () = new PrototypeAST(yystack_[3].value.as < std::string > (),yystack_[1].value.as < std::vector<std::string> > ());  }
#line 1018 "parser.cpp"
    break;

  case 14:
#line 142 "parser.yy"
                        { std::vector<std::string> args;
                          yylhs.value.as < std::vector<std::string> > () = args; }
#line 1025 "parser.cpp"
    break;

  case 15:
#line 144 "parser.yy"
                        { yystack_[0].value.as < std::vector<std::string> > ().insert(yystack_[0].value.as < std::vector<std::string> > ().begin(),yystack_[1].value.as < std::string > ());
                          yylhs.value.as < std::vector<std::string> > () = yystack_[0].value.as < std::vector<std::string> > (); }
#line 1032 "parser.cpp"
    break;

  case 16:
#line 149 "parser.yy"
                            {yylhs.value.as < AssignmentExprAST* > () = new AssignmentExprAST(yystack_[2].value.as < std::string > (),yystack_[0].value.as < ExprAST* > ());}
#line 1038 "parser.cpp"
    break;

  case 17:
#line 150 "parser.yy"
                            {yylhs.value.as < AssignmentExprAST* > () = new AssignmentExprAST(yystack_[5].value.as < std::string > (),yystack_[0].value.as < ExprAST* > (),yystack_[3].value.as < ExprAST* > ()); }
#line 1044 "parser.cpp"
    break;

  case 18:
#line 151 "parser.yy"
                            {yylhs.value.as < AssignmentExprAST* > () = new AssignmentExprAST(yystack_[0].value.as < std::string > (), new BinaryExprAST('+', new VariableExprAST(yystack_[0].value.as < std::string > ()), new NumberExprAST(1))); }
#line 1050 "parser.cpp"
    break;

  case 19:
#line 152 "parser.yy"
                            {yylhs.value.as < AssignmentExprAST* > () = new AssignmentExprAST(yystack_[0].value.as < std::string > (), new BinaryExprAST('-', new VariableExprAST(yystack_[0].value.as < std::string > ()), new NumberExprAST(1))); }
#line 1056 "parser.cpp"
    break;

  case 20:
#line 153 "parser.yy"
                            {yylhs.value.as < AssignmentExprAST* > () = new AssignmentExprAST(yystack_[1].value.as < std::string > (), new BinaryExprAST('+', new VariableExprAST(yystack_[1].value.as < std::string > ()), new NumberExprAST(1))); }
#line 1062 "parser.cpp"
    break;

  case 21:
#line 154 "parser.yy"
                            {yylhs.value.as < AssignmentExprAST* > () = new AssignmentExprAST(yystack_[1].value.as < std::string > (), new BinaryExprAST('-', new VariableExprAST(yystack_[1].value.as < std::string > ()), new NumberExprAST(1))); }
#line 1068 "parser.cpp"
    break;

  case 22:
#line 159 "parser.yy"
                            { yylhs.value.as < BlockAST* > () = new BlockAST(yystack_[1].value.as < std::vector<StatementAST*> > ()); }
#line 1074 "parser.cpp"
    break;

  case 23:
#line 160 "parser.yy"
                            { yylhs.value.as < BlockAST* > () = new BlockAST(yystack_[3].value.as < std::vector<InitAST*> > (),yystack_[1].value.as < std::vector<StatementAST*> > ()); }
#line 1080 "parser.cpp"
    break;

  case 24:
#line 164 "parser.yy"
                        { std::vector<InitAST*> definitions;
                          definitions.push_back(yystack_[0].value.as < InitAST* > ());
                          yylhs.value.as < std::vector<InitAST*> > () = definitions; }
#line 1088 "parser.cpp"
    break;

  case 25:
#line 167 "parser.yy"
                        { yystack_[2].value.as < std::vector<InitAST*> > ().push_back(yystack_[0].value.as < InitAST* > ()); yylhs.value.as < std::vector<InitAST*> > () = yystack_[2].value.as < std::vector<InitAST*> > (); }
#line 1094 "parser.cpp"
    break;

  case 26:
#line 171 "parser.yy"
          {yylhs.value.as < ExprAST* > () = nullptr;}
#line 1100 "parser.cpp"
    break;

  case 27:
#line 172 "parser.yy"
          {yylhs.value.as < ExprAST* > () = yystack_[0].value.as < ExprAST* > ();}
#line 1106 "parser.cpp"
    break;

  case 28:
#line 176 "parser.yy"
                                                    { yylhs.value.as < InitAST* > () = new VarBindingsAST(yystack_[1].value.as < std::string > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1112 "parser.cpp"
    break;

  case 29:
#line 177 "parser.yy"
                                                    { yylhs.value.as < InitAST* > () = new ArrayBindingAST(yystack_[3].value.as < std::string > (),yystack_[1].value.as < double > ());}
#line 1118 "parser.cpp"
    break;

  case 30:
#line 178 "parser.yy"
                                                   { yylhs.value.as < InitAST* > () = new ArrayBindingAST(yystack_[7].value.as < std::string > (),yystack_[5].value.as < double > (),yystack_[1].value.as < std::vector<ExprAST*> > ());}
#line 1124 "parser.cpp"
    break;

  case 31:
#line 189 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new BinaryExprAST('-',new NumberExprAST(0),yystack_[0].value.as < ExprAST* > ());}
#line 1130 "parser.cpp"
    break;

  case 32:
#line 190 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new BinaryExprAST('+',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1136 "parser.cpp"
    break;

  case 33:
#line 191 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new BinaryExprAST('-',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1142 "parser.cpp"
    break;

  case 34:
#line 192 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new BinaryExprAST('*',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1148 "parser.cpp"
    break;

  case 35:
#line 193 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new BinaryExprAST('/',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1154 "parser.cpp"
    break;

  case 36:
#line 194 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = yystack_[0].value.as < ExprAST* > (); }
#line 1160 "parser.cpp"
    break;

  case 37:
#line 195 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = yystack_[1].value.as < ExprAST* > (); }
#line 1166 "parser.cpp"
    break;

  case 38:
#line 196 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = yystack_[0].value.as < ExprAST* > (); }
#line 1172 "parser.cpp"
    break;

  case 39:
#line 197 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new NumberExprAST(yystack_[0].value.as < double > ()); }
#line 1178 "parser.cpp"
    break;

  case 40:
#line 201 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new VariableExprAST(yystack_[0].value.as < std::string > ()); }
#line 1184 "parser.cpp"
    break;

  case 41:
#line 202 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new CallExprAST(yystack_[3].value.as < std::string > (),yystack_[1].value.as < std::vector<ExprAST*> > ()); }
#line 1190 "parser.cpp"
    break;

  case 42:
#line 203 "parser.yy"
                        { yylhs.value.as < ExprAST* > () = new VariableExprAST(yystack_[3].value.as < std::string > (),yystack_[1].value.as < ExprAST* > (),true);}
#line 1196 "parser.cpp"
    break;

  case 43:
#line 207 "parser.yy"
                         {yylhs.value.as < ExprAST* > () = yystack_[0].value.as < ExprAST* > ();}
#line 1202 "parser.cpp"
    break;

  case 44:
#line 208 "parser.yy"
                         {yylhs.value.as < ExprAST* > () = new BinaryExprAST('&',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ());}
#line 1208 "parser.cpp"
    break;

  case 45:
#line 209 "parser.yy"
                         {yylhs.value.as < ExprAST* > () = new BinaryExprAST('|',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ());}
#line 1214 "parser.cpp"
    break;

  case 46:
#line 210 "parser.yy"
                         {yylhs.value.as < ExprAST* > () = new BinaryExprAST('^',yystack_[0].value.as < ExprAST* > (),nullptr);}
#line 1220 "parser.cpp"
    break;

  case 47:
#line 211 "parser.yy"
                         {yylhs.value.as < ExprAST* > () = yystack_[1].value.as < ExprAST* > ();}
#line 1226 "parser.cpp"
    break;

  case 48:
#line 215 "parser.yy"
                         { yylhs.value.as < ExprAST* > () = new BinaryExprAST('<',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1232 "parser.cpp"
    break;

  case 49:
#line 216 "parser.yy"
                         { yylhs.value.as < ExprAST* > () = new BinaryExprAST('>',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1238 "parser.cpp"
    break;

  case 50:
#line 217 "parser.yy"
                         { yylhs.value.as < ExprAST* > () = new BinaryExprAST('=',yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1244 "parser.cpp"
    break;

  case 51:
#line 221 "parser.yy"
                        { std::vector<ExprAST*> args;
			                    yylhs.value.as < std::vector<ExprAST*> > () = args; }
#line 1251 "parser.cpp"
    break;

  case 52:
#line 223 "parser.yy"
                        { yylhs.value.as < std::vector<ExprAST*> > () = yystack_[0].value.as < std::vector<ExprAST*> > (); }
#line 1257 "parser.cpp"
    break;

  case 53:
#line 227 "parser.yy"
                        { std::vector<ExprAST*> args;
                          args.push_back(yystack_[0].value.as < ExprAST* > ());
			                    yylhs.value.as < std::vector<ExprAST*> > () = args;
                        }
#line 1266 "parser.cpp"
    break;

  case 54:
#line 231 "parser.yy"
                       { yystack_[0].value.as < std::vector<ExprAST*> > ().insert(yystack_[0].value.as < std::vector<ExprAST*> > ().begin(), yystack_[2].value.as < ExprAST* > ());
                          yylhs.value.as < std::vector<ExprAST*> > () = yystack_[0].value.as < std::vector<ExprAST*> > (); }
#line 1273 "parser.cpp"
    break;

  case 55:
#line 236 "parser.yy"
                          { yylhs.value.as < ExprAST* > () = new IfExprAST(yystack_[4].value.as < ExprAST* > (),yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ());}
#line 1279 "parser.cpp"
    break;

  case 56:
#line 240 "parser.yy"
                        {std::vector<StatementAST*> statements;
                         statements.insert(statements.begin(), yystack_[0].value.as < StatementAST* > ());
                         yylhs.value.as < std::vector<StatementAST*> > () = statements; }
#line 1287 "parser.cpp"
    break;

  case 57:
#line 243 "parser.yy"
                        {yystack_[0].value.as < std::vector<StatementAST*> > ().insert(yystack_[0].value.as < std::vector<StatementAST*> > ().begin(), yystack_[2].value.as < StatementAST* > ());
                         yylhs.value.as < std::vector<StatementAST*> > () = yystack_[0].value.as < std::vector<StatementAST*> > ();}
#line 1294 "parser.cpp"
    break;

  case 58:
#line 248 "parser.yy"
                        {yylhs.value.as < StatementAST* > () = yystack_[0].value.as < BlockAST* > ();}
#line 1300 "parser.cpp"
    break;

  case 59:
#line 249 "parser.yy"
                        {yylhs.value.as < StatementAST* > () = yystack_[0].value.as < AssignmentExprAST* > ();}
#line 1306 "parser.cpp"
    break;

  case 60:
#line 250 "parser.yy"
                        {yylhs.value.as < StatementAST* > () = yystack_[0].value.as < IfStatementAST* > ();}
#line 1312 "parser.cpp"
    break;

  case 61:
#line 251 "parser.yy"
                        {yylhs.value.as < StatementAST* > () = yystack_[0].value.as < ForStatementAST* > ();}
#line 1318 "parser.cpp"
    break;

  case 62:
#line 252 "parser.yy"
                        {yylhs.value.as < StatementAST* > () = yystack_[0].value.as < ExprAST* > ();}
#line 1324 "parser.cpp"
    break;

  case 63:
#line 259 "parser.yy"
                                              {yylhs.value.as < IfStatementAST* > () = new IfStatementAST(yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < StatementAST* > ()); }
#line 1330 "parser.cpp"
    break;

  case 64:
#line 260 "parser.yy"
                                              {yylhs.value.as < IfStatementAST* > () = new IfStatementAST(yystack_[4].value.as < ExprAST* > (),yystack_[2].value.as < StatementAST* > (),yystack_[0].value.as < StatementAST* > ()); }
#line 1336 "parser.cpp"
    break;

  case 65:
#line 264 "parser.yy"
                                                   {yylhs.value.as < ForStatementAST* > () = new ForStatementAST(yystack_[6].value.as < InitAST* > (),yystack_[4].value.as < ExprAST* > (),yystack_[2].value.as < AssignmentExprAST* > (),yystack_[0].value.as < StatementAST* > ());}
#line 1342 "parser.cpp"
    break;

  case 66:
#line 268 "parser.yy"
          {yylhs.value.as < InitAST* > () = yystack_[0].value.as < InitAST* > ();}
#line 1348 "parser.cpp"
    break;

  case 67:
#line 269 "parser.yy"
             {yylhs.value.as < InitAST* > () = yystack_[0].value.as < AssignmentExprAST* > ();}
#line 1354 "parser.cpp"
    break;


#line 1358 "parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
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


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    std::ptrdiff_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */
    if (!yyla.empty ())
      {
        symbol_number_type yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];

        int yyn = yypact_[+yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yy_error_token_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -109;

  const signed char parser::yytable_ninf_ = -6;

  const short
  parser::yypact_[] =
  {
      34,   -23,   -23,   -21,    14,  -109,    16,  -109,  -109,  -109,
       6,  -109,     9,    61,  -109,    34,    33,    91,  -109,    53,
    -109,    33,    80,    70,    48,    76,    48,    48,    77,    89,
     100,    88,  -109,  -109,  -109,   114,  -109,   188,  -109,   105,
      47,  -109,   104,   119,  -109,  -109,   107,  -109,  -109,  -109,
      45,    68,  -109,   164,    71,   188,  -109,    67,    48,     2,
    -109,  -109,    48,    48,    48,    91,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,  -109,   108,  -109,    48,
    -109,  -109,    48,    94,  -109,    92,   130,  -109,  -109,   127,
     152,   120,  -109,   188,    12,  -109,   109,    68,    68,  -109,
    -109,   188,   188,   188,   176,  -109,  -109,  -109,    59,   188,
     116,   108,    48,    48,    48,  -109,   121,  -109,    48,  -109,
     126,   103,   137,    13,  -109,    48,   188,   129,   108,   121,
       8,   188,    48,  -109,   139,   133,   108,  -109,  -109
  };

  const signed char
  parser::yydefact_[] =
  {
       3,     0,     0,     0,     0,     2,     0,     6,     7,     8,
       0,    12,     0,    10,     1,     3,    14,     0,     9,     0,
       4,    14,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    40,    39,    59,    58,     0,    24,    62,    36,     0,
      43,    38,     0,    56,    60,    61,     0,    15,    13,    19,
      40,    31,    18,     0,     0,     0,    46,    26,     0,     0,
      21,    20,    51,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    22,     0,    11,     0,
      37,    47,     0,     0,    28,     0,     0,    67,    66,     0,
      53,     0,    52,    16,     0,    25,     0,    33,    32,    34,
      35,    48,    49,    50,     0,    44,    45,    57,     0,    27,
       0,     0,     0,     0,     0,    41,    42,    23,     0,    42,
      29,    63,     0,     0,    54,     0,    55,     0,     0,     0,
       0,    17,     0,    64,     0,     0,     0,    30,    65
  };

  const short
  parser::yypgoto_[] =
  {
    -109,  -109,   144,  -109,  -109,  -109,  -109,   161,   143,   -58,
     153,  -109,  -109,    -2,   -24,  -109,   -22,  -109,  -109,  -108,
    -109,   -54,  -103,  -109,  -109,  -109
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,     4,     5,     6,     7,     8,     9,    11,    22,    33,
      34,    35,    84,    36,    37,    38,    39,    40,    91,    92,
      41,    42,    43,    44,    45,    89
  };

  const short
  parser::yytable_[] =
  {
      51,    87,    53,    55,    54,    56,   124,    23,   121,    25,
      10,    96,    13,    23,    14,    25,   130,    16,    66,    15,
      67,    68,    69,   107,   135,   133,    73,    70,    71,    72,
      17,    28,   116,   138,    55,    86,    85,    -5,    90,    93,
      94,    86,    97,    98,    99,   100,   101,   102,   103,   104,
      55,    55,   105,   106,    24,   108,    62,    88,   109,    26,
       1,     2,     3,    95,    79,    66,    21,    67,    68,    69,
      74,    75,   134,    27,    70,    71,    72,    68,    69,   119,
      19,    50,    32,    81,    73,    82,    83,    46,   122,    55,
      90,   123,    48,    60,   126,    61,    23,    24,    25,    62,
      58,   131,    26,    49,   111,    73,    63,    64,    90,    52,
      57,    59,    17,    23,    24,    25,    27,    65,    73,    26,
      28,    29,    77,    30,    31,    32,    76,    78,   110,    17,
     113,   117,   115,    27,   128,    60,   120,    61,    29,   125,
      30,    31,    32,    66,   127,    67,    68,    69,    63,   112,
     132,   136,    70,    71,    72,   137,   114,   129,    66,    20,
      67,    68,    69,    12,    47,    18,     0,    70,    71,    72,
      66,     0,    67,    68,    69,     0,    80,     0,     0,    70,
      71,    72,    66,     0,    67,    68,    69,     0,     0,     0,
     118,    70,    71,    72,    66,     0,    67,    68,    69,     0,
       0,     0,     0,    70,    71,    72
  };

  const short
  parser::yycheck_[] =
  {
      24,    59,    26,    27,    26,    27,   114,     5,   111,     7,
      33,    65,    33,     5,     0,     7,     3,    11,     6,     3,
       8,     9,    10,    77,   132,   128,    13,    15,    16,    17,
      21,    29,    20,   136,    58,    33,    58,     3,    62,    63,
      64,    33,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    74,    75,     6,    79,    11,    59,    82,    11,
      26,    27,    28,    65,    19,     6,    33,     8,     9,    10,
      23,    24,   130,    25,    15,    16,    17,     9,    10,    20,
      19,    33,    34,    12,    13,    18,    19,    34,   112,   113,
     114,   113,    12,     5,   118,     7,     5,     6,     7,    11,
      11,   125,    11,    33,    12,    13,    18,    19,   132,    33,
      33,    11,    21,     5,     6,     7,    25,     3,    13,    11,
      29,    30,     3,    32,    33,    34,    22,    20,    34,    21,
       3,    22,    12,    25,    31,     5,    20,     7,    30,    18,
      32,    33,    34,     6,    18,     8,     9,    10,    18,    19,
      21,    12,    15,    16,    17,    22,     4,    20,     6,    15,
       8,     9,    10,     2,    21,    12,    -1,    15,    16,    17,
       6,    -1,     8,     9,    10,    -1,    12,    -1,    -1,    15,
      16,    17,     6,    -1,     8,     9,    10,    -1,    -1,    -1,
      14,    15,    16,    17,     6,    -1,     8,     9,    10,    -1,
      -1,    -1,    -1,    15,    16,    17
  };

  const signed char
  parser::yystos_[] =
  {
       0,    26,    27,    28,    37,    38,    39,    40,    41,    42,
      33,    43,    43,    33,     0,     3,    11,    21,    46,    19,
      38,    33,    44,     5,     6,     7,    11,    25,    29,    30,
      32,    33,    34,    45,    46,    47,    49,    50,    51,    52,
      53,    56,    57,    58,    59,    60,    34,    44,    12,    33,
      33,    50,    33,    50,    52,    50,    52,    33,    11,    11,
       5,     7,    11,    18,    19,     3,     6,     8,     9,    10,
      15,    16,    17,    13,    23,    24,    22,     3,    20,    19,
      12,    12,    18,    19,    48,    52,    33,    45,    49,    61,
      50,    54,    55,    50,    50,    49,    57,    50,    50,    50,
      50,    50,    50,    50,    50,    52,    52,    57,    50,    50,
      34,    12,    19,     3,     4,    12,    20,    22,    14,    20,
      20,    58,    50,    52,    55,    18,    50,    18,    31,    20,
       3,    50,    21,    58,    45,    55,    12,    22,    58
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    36,    37,    38,    38,    39,    39,    39,    39,    40,
      41,    41,    42,    43,    44,    44,    45,    45,    45,    45,
      45,    45,    46,    46,    47,    47,    48,    48,    49,    49,
      49,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      51,    51,    51,    52,    52,    52,    52,    52,    53,    53,
      53,    54,    54,    55,    55,    56,    57,    57,    58,    58,
      58,    58,    58,    59,    59,    60,    61,    61
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     3,     0,     1,     1,     1,     3,
       2,     5,     2,     4,     0,     2,     3,     6,     2,     2,
       2,     2,     3,     5,     1,     3,     0,     2,     3,     5,
       9,     2,     3,     3,     3,     3,     1,     3,     1,     1,
       1,     4,     4,     1,     3,     3,     2,     3,     3,     3,
       3,     0,     1,     1,     3,     5,     1,     3,     1,     1,
       1,     1,     1,     5,     7,     9,     1,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\";\"", "\",\"", "\"--\"",
  "\"-\"", "\"++\"", "\"+\"", "\"*\"", "\"/\"", "\"(\"", "\")\"", "\"?\"",
  "\":\"", "\"<\"", "\">\"", "\"==\"", "\"=\"", "\"[\"", "\"]\"", "\"{\"",
  "\"}\"", "\"and\"", "\"or\"", "\"not\"", "\"extern\"", "\"def\"",
  "\"global\"", "\"var\"", "\"if\"", "\"else\"", "\"for\"", "\"id\"",
  "\"number\"", "\"noelse\"", "$accept", "startsymb", "program", "top",
  "definition", "globalvar", "external", "proto", "idseq", "assignment",
  "block", "vardefs", "initexp", "binding", "exp", "idexp", "condexp",
  "relexp", "optexp", "exparr", "expif", "stmts", "stmt", "ifstmt",
  "forstmt", "init", YY_NULLPTR
  };

#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   109,   109,   113,   114,   118,   119,   120,   121,   125,
     129,   130,   134,   138,   142,   144,   149,   150,   151,   152,
     153,   154,   159,   160,   164,   167,   171,   172,   176,   177,
     178,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     201,   202,   203,   207,   208,   209,   210,   211,   215,   216,
     217,   221,   223,   227,   231,   236,   240,   243,   248,   249,
     250,   251,   252,   259,   260,   264,   268,   269
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 1845 "parser.cpp"

#line 273 "parser.yy"


void
yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
