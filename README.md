# Progetto Compilatore Kaleidoscope - Readme

## Note

Il progetto inizia con la modifica dei file contenuti nella directory fornita nel drive del corso "Kaleidoscope1.1-with_expr_if".
 
Non verrà riportato in questo readme il codice scritto per ogni nodo, in quanto ogni modifica ai file originali è stata commentata in questo formato:

```
//K4: Commento inerente alle righe di codice successive
```

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

Infine occorre creare il nodo corrispondente tramite una classe, in questo caso **BlockAST**, prima dichiarandolo nel file driver.hpp. Dopo bisogna implementare i suoi costruttori e il suo metodo codegen (ci potrebbero essere altri metodi da implementare per altri nodi) nel file driver.cpp.

```hpp
class BlockAST : public ExprAST {
  private:
    std::vector<InitAST*> Definitions;
    std::vector<StatementAST*> Statements;
  public:
  BlockAST(std::vector<InitAST*> Definitions,std::vector<StatementAST*> Statements);
  BlockAST(std::vector<StatementAST*> Statements);
  Value *codegen(driver& drv) override;
};
```
Con implementazioni: 

```cpp
//K4: Costruttore con solo statements
BlockAST::BlockAST(std::vector<StatementAST*> Statements):
  Statements(std::move(Statements)) {};
  
//K4: Costruttore con definizioni e statements
BlockAST::BlockAST(std::vector<InitAST*> Definitions,std::vector<StatementAST*> Statements):
  Definitions(std::move(Definitions)), Statements(std::move(Statements)) {};


Value* BlockAST::codegen(driver& drv) {
  //K4: salvo le variabili che andranno nella NamedValues 
  std::vector<AllocaInst*> toSave;
  if (!Definitions.empty())
    for (auto& definition: Definitions) {
      AllocaInst *BoundVal = (AllocaInst*) definition->codegen(drv);
      if (!BoundVal) return nullptr;
      //salvo il vecchio valore della varaiabile oscurata.
      toSave.push_back(drv.NamedValues[definition->getName()]);
      drv.NamedValues[definition->getName()] = BoundVal;
    }
  //K4: Ottengo l'ultimo valore prodotto che sarà quello da restituire
  Value* blockvalue;
  if (!Statements.empty())
    for(auto& statement: Statements) {
      blockvalue = statement->codegen(drv);
      if (!blockvalue) 
        return nullptr;
    }
    
  //K4: Ripristino dei valori fuori dallo scope del blocco
  for (int i = 0; i < Definitions.size(); i++)
    drv.NamedValues[Definitions[i]->getName()] = toSave[i];


  return blockvalue;
};
```

