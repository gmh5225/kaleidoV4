# Progetto Compilatore Kaleidoscope - Readme

## Descrizione del Progetto

Questo progetto si propone di implementare un compilatore per il linguaggio Kaleidoscope. Il linguaggio è descritto da una grammatica su 4 livelli.

## Grammatica di Primo Livello

La grammatica di primo livello del linguaggio Kaleidoscope è definita come segue:

```grammatica livello 1
% start startsymb ;

startsymb :
    program

program :
    % empty
    | top ";" program

top : 
  %empty 
| definition
| external stmts :
| globalvar

definition :
    "def" proto block

external:
    "extern" proto

proto:
    "id" "(" idseq ")"

globalvar :
    "global" "id"

idseq :
    %empty
|   "id" idseq

% left ":";
% left " <" "==";
% left "+" " -";
% left "*" "/";

stmts :
    stmt
|   stmt ";" stmts

stmt :
    assignment
|   block
|   exp

assignment:
    "id" "=" exp

block : 
    "{" stmts "}"
|   "{" vardefs ";" stmts "}"

vardefs:
    binding
|   vardefs ";" binding

initexp:
    %empty
|   "=" exp

condexp:
    binding : exp " <" exp
|   exp "==" exp

exp:
    exp "+" exp 
|   exp " -" exp
|   exp "*" exp
|   exp "/" exp
|   idexp
|   "(" exp ")"
|   "number"
|   expif

idexp:
    "id"
|   "id" "(" optexp ")"

explist:
    exp
|   exp " ," explist

optexp:
    %empty
|   explist

```

## Implementazione Primo Livello

Per implementarla ho aggiunto le varie produzioni richieste al file Bison parser.yy e i simboli necessari per riconoscerle nel file Flex scanner.ll.
Ad esempio:

```bison
block:
  "{" stmts "}"             { $$ = new BlockAST($2); } 
| "{" vardefs ";" stmts "}" { $$ = new BlockAST($2,$4); }
;
```

Per il quale è necessario il riconoscimento delle parentesi graffe.

```lex
"{"      return yy::parser::make_LBRACE    (loc);
"}"      return yy::parser::make_RBRACE    (loc);
```
