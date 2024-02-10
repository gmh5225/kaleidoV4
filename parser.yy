%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.2"
%defines

%define api.token.constructor
%define api.location.file none
%define api.value.type variant
%define parse.assert

%code requires {
  # include <string>
  #include <exception>
  class driver;
  class RootAST;
  class ExprAST;
  class NumberExprAST;
  class VariableExprAST;
  class CallExprAST;
  class FunctionAST;
  class SeqAST;
  class PrototypeAST;
  class BlockAST;
  class VarBindingsAST;
  class GlobalVariableAST;
  class AssignmentExprAST;
  class StatementAST; 
  class IfStatementAST;
  class InitAST;
  class ForStatementAST;
}

// The parsing context.
%param { driver& drv }

%locations

%define parse.trace
%define parse.error verbose

%code {
# include "driver.hpp"
}

%define api.token.prefix {TOK_}
%token
  END  0  "end of file"
  SEMICOLON  ";"
  COMMA      ","
  DMINUS     "--"
  MINUS      "-"
  DPLUS      "++"
  PLUS       "+"
  STAR       "*"
  SLASH      "/"
  LPAREN     "("
  RPAREN     ")"
  QMARK      "?"
  COLON      ":"
  LT         "<"
  GT         ">"
  EQ         "=="
  ASSIGN     "="
  LSQRBRACE  "["
  RSQRBRACE  "]"
  LBRACE     "{"
  RBRACE     "}"
  AND        "and"
  OR         "or"
  NOT        "not"
  EXTERN     "extern"
  DEF        "def"
  GLOBAL     "global"
  VAR        "var"
  IF         "if"
  ELSE       "else"
  FOR        "for"
;

%token <std::string> IDENTIFIER "id"
%token <double> NUMBER "number"
%type <ExprAST*> exp
%type <ExprAST*> idexp
%type <ExprAST*> expif 
%type <ExprAST*> condexp
%type <ExprAST*> relexp
%type <ExprAST*> initexp
%type <std::vector<ExprAST*>> optexp
%type <std::vector<ExprAST*>> exparr
%type <RootAST*> program
%type <RootAST*> top
%type <FunctionAST*> definition
%type <PrototypeAST*> external
%type <GlobalVariableAST*> globalvar;
%type <PrototypeAST*> proto
%type <std::vector<std::string>> idseq
%type <BlockAST*> block
%type <InitAST*> init;
%type <InitAST*> binding;
%type <std::vector<InitAST*>> vardefs;
%type <AssignmentExprAST*> assignment;
%type <StatementAST*> stmt;
%type <std::vector<StatementAST*>> stmts;
%type <IfStatementAST*> ifstmt;
%type <ForStatementAST*> forstmt;
%%
%start startsymb;

startsymb:
program                 { drv.root = $1; }
;

program:
  %empty                { $$ = new SeqAST(nullptr,nullptr); }
|  top ";" program      { $$ = new SeqAST($1,$3); }
;

top:
%empty                  { $$ = nullptr; }
| definition            { $$ = $1; }
| globalvar             { $$ = $1; }
| external              { $$ = $1; }
;

definition:
  "def" proto block       { $$ = new FunctionAST($2,$3); $2->noemit(); }
;

globalvar:
  "global" "id"                   { $$ = new GlobalVariableAST($2); }
| "global" "id" "[" "number" "]"  { $$ = new GlobalVariableAST($2,$4,true); }
;

external:
  "extern" proto        { $$ = $2; }
;

proto:
  "id" "(" idseq ")"    { $$ = new PrototypeAST($1,$3);  }
;

idseq:
  %empty                { std::vector<std::string> args;
                          $$ = args; }
| "id" idseq            { $2.insert($2.begin(),$1);
                          $$ = $2; }
;

assignment:
  "id" "=" exp              {$$ = new AssignmentExprAST($1,$3);}
| "id" "[" exp "]" "=" exp  {$$ = new AssignmentExprAST($1,$6,$3); }
| "++" "id"                 {$$ = new AssignmentExprAST($2, new BinaryExprAST('+', new VariableExprAST($2), new NumberExprAST(1))); }
| "--" "id"                 {$$ = new AssignmentExprAST($2, new BinaryExprAST('-', new VariableExprAST($2), new NumberExprAST(1))); }
| "id" "++"                 {$$ = new AssignmentExprAST($1, new BinaryExprAST('+', new VariableExprAST($1), new NumberExprAST(1))); }
| "id" "--"                 {$$ = new AssignmentExprAST($1, new BinaryExprAST('-', new VariableExprAST($1), new NumberExprAST(1))); }
;


block:
  "{" stmts "}"             { $$ = new BlockAST($2); } 
| "{" vardefs ";" stmts "}" { $$ = new BlockAST($2,$4); }
;

vardefs:
  binding               { std::vector<InitAST*> definitions;
                          definitions.push_back($1);
                          $$ = definitions; }
| vardefs ";" binding   { $1.push_back($3); $$ = $1; }
;

initexp:
  %empty  {$$ = nullptr;}
| "=" exp {$$ = $2;}
;

binding:
  "var" "id" initexp                                { $$ = new VarBindingsAST($2,$3); };
| "var" "id" "[" "number" "]"                       { $$ = new ArrayBindingAST($2,$4);}
| "var" "id" "[" "number" "]" "=" "{" exparr "}"   { $$ = new ArrayBindingAST($2,$4,$8);}
;

%left ":" "?";
%left "==" ">" "<";
%left "+" "-";
%left "not";
%left "and" "or";
%left "*" "/";

exp:
  "-" exp               { $$ = new BinaryExprAST('-',new NumberExprAST(0),$2);}
| exp "+" exp           { $$ = new BinaryExprAST('+',$1,$3); }
| exp "-" exp           { $$ = new BinaryExprAST('-',$1,$3); }
| exp "*" exp           { $$ = new BinaryExprAST('*',$1,$3); }
| exp "/" exp           { $$ = new BinaryExprAST('/',$1,$3); }
| idexp                 { $$ = $1; }
| "(" exp ")"           { $$ = $2; }
| expif                 { $$ = $1; }
| "number"              { $$ = new NumberExprAST($1); }
;

idexp:
  "id"                  { $$ = new VariableExprAST($1); }
| "id" "(" optexp ")"   { $$ = new CallExprAST($1,$3); };
| "id" "[" exp "]"      { $$ = new VariableExprAST($1,$3,true);}
;

condexp:
  relexp                 {$$ = $1;}
| relexp "and" condexp   {$$ = new BinaryExprAST('&',$1,$3);}
| relexp "or" condexp    {$$ = new BinaryExprAST('|',$1,$3);}
| "not" condexp          {$$ = new BinaryExprAST('^',$2,nullptr);}
| "(" condexp ")"        {$$ = $2;}
;

relexp:
  exp "<" exp            { $$ = new BinaryExprAST('<',$1,$3); }
|  exp ">" exp           { $$ = new BinaryExprAST('>',$1,$3); }
| exp "==" exp           { $$ = new BinaryExprAST('=',$1,$3); }
;

optexp:
  %empty                { std::vector<ExprAST*> args;
			                    $$ = args; }
| exparr                { $$ = $1; }
;

exparr:
  exp                   { std::vector<ExprAST*> args;
                          args.push_back($1);
			                    $$ = args;
                        }
| exp "," exparr       { $3.insert($3.begin(), $1);
                          $$ = $3; }
;

expif:
  condexp "?" exp ":" exp { $$ = new IfExprAST($1,$3,$5);}
;

stmts:
  stmt                  {std::vector<StatementAST*> statements;
                         statements.insert(statements.begin(), $1);
                         $$ = statements; }
| stmt ";" stmts        {$3.insert($3.begin(), $1);
                         $$ = $3;}
;

stmt:
  block                 {$$ = $1;}
| assignment            {$$ = $1;}
| ifstmt                {$$ = $1;}
| forstmt               {$$ = $1;}
| exp                   {$$ = $1;}
;

//K4 sceglie la precedenza tra if else ed if: 
%right "noelse" "else" ;

ifstmt :
  "if" "(" condexp ")" stmt                   {$$ = new IfStatementAST($3,$5); } %prec "noelse"
| "if" "(" condexp ")" stmt "else" stmt       {$$ = new IfStatementAST($3,$5,$7); }
; 

forstmt :
"for" "(" init ";" condexp ";" assignment ")" stmt {$$ = new ForStatementAST($3,$5,$7,$9);}
;

init :
  binding {$$ = $1;}
| assignment {$$ = $1;}
;

 
%%

void
yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}