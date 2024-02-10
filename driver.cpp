#include "driver.hpp"
#include "parser.hpp"

// Generazione di un'istanza per ciascuna della classi LLVMContext,
// Module e IRBuilder. Nel caso di singolo modulo è sufficiente
LLVMContext *context = new LLVMContext;
Module *module = new Module("Kaleido4.0", *context);
IRBuilder<> *builder = new IRBuilder(*context);

Value *LogErrorV(const std::string Str) {
  std::cerr << Str << std::endl;
  return nullptr;
}

/* Il codice seguente sulle prime non è semplice da comprendere.
   Esso definisce una utility (funzione C++) con due parametri:
   1) la rappresentazione di una funzione llvm IR, e
   2) il nome per un registro SSA
   La chiamata di questa utility restituisce un'istruzione IR che alloca un double
   in memoria e ne memorizza il puntatore in un registro SSA cui viene attribuito
   il nome passato come secondo parametro. L'istruzione verrà scritta all'inizio
   dell'entry block della funzione passata come primo parametro.
   Si ricordi che le istruzioni sono generate da un builder. Per non
   interferire con il builder globale, la generazione viene dunque effettuata
   con un builder temporaneo TmpB
*/
static AllocaInst *CreateEntryBlockAlloca(Function *fun, StringRef VarName, Type* type=Type::getDoubleTy(*context)) {
  IRBuilder<> TmpB(&fun->getEntryBlock(), fun->getEntryBlock().begin());
  return TmpB.CreateAlloca(type, nullptr, VarName);
}

// Implementazione del costruttore della classe driver
driver::driver(): trace_parsing(false), trace_scanning(false) {};

// Implementazione del metodo parse
int driver::parse (const std::string &f) {
  file = f;                    // File con il programma
  location.initialize(&file);  // Inizializzazione dell'oggetto location
  scan_begin();                // Inizio scanning (ovvero apertura del file programma)
  yy::parser parser(*this);    // Istanziazione del parser
  parser.set_debug_level(trace_parsing); // Livello di debug del parsed
  int res = parser.parse();    // Chiamata dell'entry point del parser
  scan_end();                  // Fine scanning (ovvero chiusura del file programma)
  return res;
}

// Implementazione del metodo codegen, che è una "semplice" chiamata del 
// metodo omonimo presente nel nodo root (il puntatore root è stato scritto dal parser)
void driver::codegen() {
  root->codegen(*this);
};

/************************* Sequence tree **************************/
SeqAST::SeqAST(RootAST* first, RootAST* continuation):
  first(first), continuation(continuation) {};

// La generazione del codice per una sequenza è banale:
// mediante chiamate ricorsive viene generato il codice di first e 
// poi quello di continuation (con gli opportuni controlli di "esistenza")
Value *SeqAST::codegen(driver& drv) {
  if (first != nullptr) {
    Value *f = first->codegen(drv);
  } else {
    if (continuation == nullptr) return nullptr;
  }
  Value *c = continuation->codegen(drv);
  return nullptr;
};

/********************* Number Expression Tree *********************/
NumberExprAST::NumberExprAST(double Val): Val(Val) {};

lexval NumberExprAST::getLexVal() const {
  // Non utilizzata, Inserita per continuità con versione precedente
  lexval lval = Val;
  return lval;
};

// Non viene generata un'struzione; soltanto una costante LLVM IR
// corrispondente al valore float memorizzato nel nodo
// La costante verrà utilizzata in altra parte del processo di generazione
// Si noti che l'uso del contesto garantisce l'unicità della costanti 
Value *NumberExprAST::codegen(driver& drv) {  
  return ConstantFP::get(*context, APFloat(Val));
};


/************************* GlobalVariableAST *************************/

GlobalVariableAST::GlobalVariableAST(std::string Name, double Size, bool isArr) : Name(Name), Size(Size), isArr(isArr) {}

const std::string& GlobalVariableAST::getName() { return Name; };

Value* GlobalVariableAST::codegen(driver &drv) {
  GlobalVariable *globalVar;
  if (isArr) {
    if(Size < 1)
      return nullptr;
    ArrayType *arrayType = ArrayType::get(Type::getDoubleTy(*context),Size);
    globalVar = new GlobalVariable(*module, arrayType, false, GlobalValue::ExternalLinkage,  ConstantFP::getNullValue(arrayType), Name);    
  }
  else {
    globalVar = new GlobalVariable(*module, Type::getDoubleTy(*context), false, GlobalValue::ExternalLinkage,  ConstantFP::getNullValue(Type::getDoubleTy(*context)), Name);    
    globalVar->setInitializer(ConstantFP::get(*context, APFloat(0.0)));
  }

  globalVar->print(errs());
  fprintf(stderr, "\n");
  return globalVar;
}


/******************** Variable Expression Tree ********************/
VariableExprAST::VariableExprAST(const std::string &Name, ExprAST* Exp , bool isArr): 
  Name(Name), Exp(Exp), isArr(isArr) {};

lexval VariableExprAST::getLexVal() const {
  lexval lval = Name;
  return lval;
};

Value *VariableExprAST::codegen(driver& drv) {
  AllocaInst *A = drv.NamedValues[Name];
  if (!A) {
    GlobalVariable* globVar = module->getNamedGlobal(Name);
    //K4: Vuol dire che la variabile non è stata trovata nè localmente nè globalmente
    if (!globVar)
      return LogErrorV("Variabile non trovata -> " + Name);

    //K4: Se la variabile è stata trovata ed è un array globale allora:
    if (isArr) {
      //K4: Generazione del codice per ad esempio i in A[i]
      Value* Val = Exp->codegen(drv);
      
      if (!Val) 
        return nullptr;
      //K4: Prendo il valore di Val e lo converto in "signed integer"
      Value* flIndex = builder->CreateFPTrunc(Val, Type::getFloatTy(*context));
      Value* intIndex = builder->CreateFPToSI(flIndex, Type::getInt32Ty(*context));
      //K4: ottengo il puntatore dell'elemento [i]
      Value* cellPTR = builder->CreateInBoundsGEP(globVar->getValueType(),globVar,intIndex);
      return builder->CreateLoad(Type::getDoubleTy(*context), cellPTR, Name.c_str());
    }
    return builder->CreateLoad(globVar->getValueType(), globVar, Name.c_str());
  }

  //K4: Se la variabile è stata trovata localmente, riconsideriamo come per le globali se è un:
  if(isArr) {
  
      Value* Val = Exp->codegen(drv);
      if(!Val) return nullptr;
      //K4: Uguale a prima
      Value* flIndex = builder->CreateFPTrunc(Val, Type::getFloatTy(*context));
      Value* intIndex = builder->CreateFPToSI(flIndex, Type::getInt32Ty(*context));
      Value* cellPTR = builder->CreateInBoundsGEP(A->getAllocatedType(),A,intIndex);
      return builder->CreateLoad(Type::getDoubleTy(*context), cellPTR, Name.c_str());
    }
  return builder->CreateLoad(A->getAllocatedType(), A, Name.c_str());
}

/******************** Binary Expression Tree **********************/
BinaryExprAST::BinaryExprAST(char Op, ExprAST* LHS, ExprAST* RHS):
  Op(Op), LHS(LHS), RHS(RHS) {};

// La generazione del codice in questo caso è di facile comprensione.
// Vengono ricorsivamente generati il codice per il primo e quello per il secondo
// operando. Con i valori memorizzati in altrettanti registri SSA si
// costruisce l'istruzione utilizzando l'opportuno operatore
Value *BinaryExprAST::codegen(driver& drv) {
  Value *L = LHS->codegen(drv);
  
  Value *R;
  //K4: L'unico operatore unario è il NOT.
  if (Op != '^')
    R = RHS->codegen(drv);
  if (!L || !R  ) 
     return nullptr;
  switch (Op) {
  case '+':
    return builder->CreateFAdd(L,R,"addres");
  case '-':
    return builder->CreateFSub(L,R,"subres");
  case '*':
    return builder->CreateFMul(L,R,"mulres");
  case '/':
    return builder->CreateFDiv(L,R,"addres");
  case '<':
    return builder->CreateFCmpULT(L,R,"ltres");
  case '>':
    return builder->CreateFCmpUGT(L,R,"gttest");
  case '=':
    return builder->CreateFCmpUEQ(L,R,"eqres");
  case '&':
    return builder->CreateAnd(L, R, "andres");
  case '|':
    return builder->CreateOr(L, R, "orres");
  case '^':
    return builder->CreateNot(L, "notres");
  default:  
    std::cout << Op << std::endl;
    return LogErrorV("Operatore binario non supportato");
  }
};


/********************* Call Expression Tree ***********************/
/* Call Expression Tree */
CallExprAST::CallExprAST(std::string Callee, std::vector<ExprAST*> Args):
  Callee(Callee),  Args(std::move(Args)) {};

lexval CallExprAST::getLexVal() const {
  lexval lval = Callee;
  return lval;
};

Value* CallExprAST::codegen(driver& drv) {
  // La generazione del codice corrispondente ad una chiamata di funzione
  // inizia cercando nel modulo corrente (l'unico, nel nostro caso) una funzione
  // il cui nome coincide con il nome memorizzato nel nodo dell'AST
  // Se la funzione non viene trovata (e dunque non è stata precedentemente definita)
  // viene generato un errore
  Function *CalleeF = module->getFunction(Callee);
  if (!CalleeF)
     return LogErrorV("Funzione non definita");
  // Il secondo controllo è che la funzione recuperata abbia tanti parametri
  // quanti sono gi argomenti previsti nel nodo AST
  if (CalleeF->arg_size() != Args.size())
     return LogErrorV("Numero di argomenti non corretto");
  // Passato con successo anche il secondo controllo, viene predisposta
  // ricorsivamente la valutazione degli argomenti presenti nella chiamata 
  // (si ricordi che gli argomenti possono essere espressioni arbitarie)
  // I risultati delle valutazioni degli argomenti (registri SSA, come sempre)
  // vengono inseriti in un vettore, dove "se li aspetta" il metodo CreateCall
  // del builder, che viene chiamato subito dopo per la generazione dell'istruzione
  // IR di chiamata
  std::vector<Value *> ArgsV;
  for (auto arg : Args) {
     ArgsV.push_back(arg->codegen(drv));
     if (!ArgsV.back())
        return nullptr;
  }
  return builder->CreateCall(CalleeF, ArgsV, "calltmp");
}

/************************* IF expression *************************/


IfExprAST::IfExprAST(ExprAST* cond, ExprAST* TrueExp, ExprAST* FalseExp) :
  cond(cond), TrueExp(TrueExp), FalseExp(FalseExp) {};

Value* IfExprAST::codegen(driver& drv) {
  Value* CondV = cond->codegen(drv);
  if (!CondV) return nullptr;

  Function *fun = builder->GetInsertBlock()->getParent();
  BasicBlock *TrueBB = BasicBlock::Create(*context, "trueBlock",fun);
    // Il blocco TrueBB viene inserito nella funzione dopo il blocco corrente

  BasicBlock *FalseBB = BasicBlock::Create(*context, "falseBlock");
  BasicBlock *MergeBB = BasicBlock::Create(*context, "mergeblock");
  // Gli altri due blocchi non vengono ancora inseriti perché le istruzioni
  // previste nel "ramo" true del condizionale potrebbe dare luogo alla creazione
  // di altri blocchi, che naturalmente andrebbero inseriti prima di FalseBB
    
  // Ora possiamo crere l'istruzione di salto condizionato
  builder->CreateCondBr(CondV, TrueBB, FalseBB);
  //Ramo true
  builder->SetInsertPoint(TrueBB);
    // "Posizioniamo" il builder all'inizio del blocco true, 
    // generiamo ricorsivamente il codice da eseguire in caso di
    // condizione vera e, in chiusura di blocco, generiamo il saldo 
    // incondizionato al blocco merge
  Value* trueV = TrueExp->codegen(drv);
  if(!trueV) 
    return nullptr;
  TrueBB = builder->GetInsertBlock();

  builder->CreateBr(MergeBB);
  fun->insert(fun->end(), FalseBB);
  // false expr
  builder->SetInsertPoint(FalseBB);
  Value* falseV = FalseExp->codegen(drv);
  if(!falseV) return nullptr;

  FalseBB = builder->GetInsertBlock();
  builder->CreateBr(MergeBB);

  fun->insert(fun->end(),MergeBB);
  builder->SetInsertPoint(MergeBB);

  PHINode *P = builder->CreatePHI(Type::getDoubleTy(*context),2);
  P-> addIncoming(trueV, TrueBB);
  P-> addIncoming(falseV, FalseBB);
  return P;
};


/************************* Block Tree *************************/
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

/************************* InitAST *************************/

const std::string& InitAST::getName() {return Name;};
varHandleType InitAST::getType() {return INIT;};


/************************* VarBindingAST *************************/

VarBindingsAST::VarBindingsAST(std::string Name, ExprAST* Val) : Name(Name), Val(Val) {};

const std::string& VarBindingsAST::getName() { return Name; };

varHandleType VarBindingsAST::getType() {return BIND;};

//K4: Occorre gestire solo variabili locali e non globali (es: var x = 5, all'interno di un blocco).
AllocaInst* VarBindingsAST::codegen(driver& drv) {
  Function *function = builder->GetInsertBlock()->getParent();
  Value* BoundVal;
  if (Val)
    BoundVal = Val->codegen(drv);
  else {
    NumberExprAST* defaultInitValue = new NumberExprAST(0.0);
    BoundVal = defaultInitValue->codegen(drv);
  }

  AllocaInst* Alloca = CreateEntryBlockAlloca(function, Name);
  builder->CreateStore(BoundVal,Alloca);

  return Alloca;
};

/************************* ArrayBindingAST *************************/

ArrayBindingAST::ArrayBindingAST(std::string Name, double Size, std::vector<ExprAST*> Values) :
  Name(Name), Size(Size), Values(std::move(Values)) {};

const std::string& ArrayBindingAST::getName() { return Name; };

varHandleType ArrayBindingAST::getType() { return BIND; };

AllocaInst* ArrayBindingAST::codegen(driver& drv) {
  
  Function *fun = builder->GetInsertBlock()->getParent();
  int intSize = (int)Size;
  ArrayType *arrayType = ArrayType::get(Type::getDoubleTy(*context),intSize);
  AllocaInst *Alloca = CreateEntryBlockAlloca(fun, Name, arrayType);
  //K4: Ogni elemento in Values va generato e memorizzatto nella sua cella
  for(int i = 0; i<Size; i++) {
    //K4: Accedo all'elemento con CreateInBoundsGEP(tipo, nomeArray, i -> signed (true) integer (APINT) 32 bit (32))
    Value* elementPointer = builder->CreateInBoundsGEP(arrayType, Alloca, ConstantInt::get(*context,APInt(32, i, true)));
    Value* elementVal = Values[i]->codegen(drv);
    if(!elementVal) 
      return nullptr;
    builder->CreateStore(elementVal, elementPointer);
  }
  return Alloca;
}


/************************* AssignmentExprAST *************************/

AssignmentExprAST::AssignmentExprAST(std::string Name, ExprAST* Val, ExprAST* Pos) : Name(Name), Val(Val), Pos(Pos) {};

const std::string& AssignmentExprAST::getName() { return Name; };

varHandleType AssignmentExprAST::getType() { return ASSIGN; };

Value* AssignmentExprAST::codegen(driver& drv) {
  //K4: E' necessario prima controllare lo scope locale e se assente controllare tra le variabili globali
  AllocaInst *Variable = drv.NamedValues[Name];
  Value* BoundVal = Val->codegen(drv);
  //K4: E' necessario che esista il valore da assegnare alla variabile
  if(!BoundVal) 
    return nullptr;
  if (!Variable) {
    GlobalVariable* globVar = module->getNamedGlobal(Name);
    if(!globVar) 
      return nullptr;
    //K4: Se esiste Pos vuol dire che è stato usato il parametro nel costruttore e stiamo accedendo quindi a una cella di un array.
    if(Pos) {
      Value* doubleIndex = Pos->codegen(drv);
      if(!doubleIndex) 
        return nullptr;
      //K4: Abbiamo l'index espresso in double e dobbiamo convertirlo in signed int passando da float.
      Value* flIndex = builder->CreateFPTrunc(doubleIndex, Type::getFloatTy(*context));
      Value* intIndex = builder->CreateFPToSI(flIndex, Type::getInt32Ty(*context));
      Value* cellPTR = builder->CreateInBoundsGEP(globVar->getValueType(),globVar,intIndex);
      
      builder->CreateStore(BoundVal,cellPTR);
    }
    else
      builder->CreateStore(BoundVal,globVar);
    return BoundVal;
  }
  if(Pos) {
    Value* doubleIndex = Pos->codegen(drv);
    if(!doubleIndex) return nullptr;
    Value* flIndex = builder->CreateFPTrunc(doubleIndex, Type::getFloatTy(*context));
    Value* intIndex = builder->CreateFPToSI(flIndex, Type::getInt32Ty(*context));    
    Value* cellPTR = builder->CreateInBoundsGEP(Variable->getAllocatedType(),Variable,intIndex);
    
    builder->CreateStore(BoundVal,cellPTR);
  }
  else {
    builder->CreateStore(BoundVal,Variable);
  }
  
  return BoundVal;
};




/************************* IF BLOCK *************************/

//K4: Costruttore per if senza else
IfStatementAST::IfStatementAST(ExprAST* cond, StatementAST* TrueBlock):
  cond(cond), TrueBlock(TrueBlock) {};
//K4: Costruttore if else stmt
IfStatementAST::IfStatementAST(ExprAST* cond, StatementAST* TrueBlock, StatementAST* FalseBlock):
  cond(cond), TrueBlock(TrueBlock), FalseBlock(FalseBlock) {};


Value* IfStatementAST::codegen(driver& drv) {
  Value* CondV = cond->codegen(drv);
  if (!CondV) 
    return nullptr;
  //K4: Stesso concetto di IfExprAST
  Function *fun = builder->GetInsertBlock()->getParent();
  BasicBlock *TrueBB = BasicBlock::Create(*context, "trueBlock",fun);
  BasicBlock *FalseBB = BasicBlock::Create(*context, "falseBlock");
  BasicBlock *MergeBB = BasicBlock::Create(*context, "mergeblock");
  
  
  builder->CreateCondBr(CondV, TrueBB, FalseBB);
  

  builder->SetInsertPoint(TrueBB);
  Value* trueV = TrueBlock->codegen(drv);
  if(!trueV) return nullptr;

  TrueBB = builder->GetInsertBlock();
  builder->CreateBr(MergeBB);

  builder->SetInsertPoint(FalseBB);
  Value* falseV;
  fun->insert(fun->end(), FalseBB);
  builder->SetInsertPoint(FalseBB);
  //K4: Controllo perchè si può trattare anche di if senza else e di conseguenza il blocco False potrebbe non essere presente
  if(FalseBlock) {
    falseV = FalseBlock->codegen(drv);
    
    if(!falseV) 
      return nullptr;

    FalseBB = builder->GetInsertBlock();
  }
  builder->CreateBr(MergeBB);

  fun->insert(fun->end(),MergeBB);
  builder->SetInsertPoint(MergeBB);

  PHINode *P = builder->CreatePHI(Type::getDoubleTy(*context),2);
  P-> addIncoming(ConstantFP::getNullValue(Type::getDoubleTy(*context)), TrueBB);
  P-> addIncoming(ConstantFP::getNullValue(Type::getDoubleTy(*context)), FalseBB);
  return P;
  
  
};



/************************* FOR BLOCK *************************/

ForStatementAST::ForStatementAST(InitAST* Init, ExprAST* Cond, AssignmentExprAST* Inc, StatementAST* Body):
Init(Init), Cond(Cond), Inc(Inc), Body(Body) {};

Value* ForStatementAST::codegen(driver& drv) {
  
  Function *fun = builder->GetInsertBlock()->getParent();
  BasicBlock *InitBB = BasicBlock::Create(*context, "init", fun);
  BasicBlock *CondBB = BasicBlock::Create(*context, "cond", fun);
  BasicBlock *LoopBB = BasicBlock::Create(*context, "loop", fun);
  BasicBlock *AfterLoop = BasicBlock::Create(*context, "afterLoop", fun);
  
  //K4: Eseguo la inizializzazione della variabile del ciclo
  builder->CreateBr(InitBB);
  builder->SetInsertPoint(InitBB);

  std::string varName = Init->getName();
  Value* initVal = Init->codegen(drv);;
  if (!initVal)
    return nullptr;
  /*K4: L'Init può essere un assignment o un binding. 
  Nel caso sia un binding occorre salvare la variabile 
  (nell'eventualità di sovrascrivere una con lo stesso nome fuori dal loop)*/ 
  AllocaInst* oldVar;
  if (Init->getType() == BIND) {
    oldVar = drv.NamedValues[varName];
    drv.NamedValues[varName] = (AllocaInst*) initVal;  
  }

  //K4: Entriamo nel ramo della condizione
  builder->CreateBr(CondBB);
  builder->SetInsertPoint(CondBB);
  Value *CondV = Cond->codegen(drv);
  if(!CondV) 
    return nullptr;

  builder->CreateCondBr(CondV, LoopBB, AfterLoop);

  builder->SetInsertPoint(LoopBB);
  Value *bodyVal = Body->codegen(drv);
  if(!bodyVal) return nullptr;

  Value* incVal = Inc->codegen(drv);
  if(!incVal) 
    return nullptr;

  //K4: Ritorno al ramo BB della condizione dopo l'incremento di variabile di loop.
  builder->CreateBr(CondBB);
  //K4: Quando finisce il loop si va nel BB AfterLoop 
  builder->SetInsertPoint(AfterLoop);
  //K4: P conterrà il valore effettivo della variabile di loop quando la condizione è soddisfatta.
  PHINode *P = builder->CreatePHI(Type::getDoubleTy(*context), 1);
  P->addIncoming(ConstantFP::getNullValue(Type::getDoubleTy(*context)),CondBB);
  //K4: Ripristino in caso di bind perchè la variabile doveva essere modificata solo all'interno del blocco del for
  if(Init->getType() == BIND) {
    drv.NamedValues[varName] = oldVar;
  }
  return P;
};

/************************* Prototype Tree *************************/
PrototypeAST::PrototypeAST(std::string Name, std::vector<std::string> Args):
  Name(Name), Args(std::move(Args)), emitcode(true) {};  //Di regola il codice viene emesso

lexval PrototypeAST::getLexVal() const {
   lexval lval = Name;
   return lval;	
};

const std::vector<std::string>& PrototypeAST::getArgs() const { 
   return Args;
};

// Previene la doppia emissione del codice. Si veda il commento più avanti.
void PrototypeAST::noemit() { 
   emitcode = false; 
};

Function *PrototypeAST::codegen(driver& drv) {
  // Costruisce una struttura, qui chiamata FT, che rappresenta il "tipo" di una
  // funzione. Con ciò si intende a sua volta una coppia composta dal tipo
  // del risultato (valore di ritorno) e da un vettore che contiene il tipo di tutti
  // i parametri. Si ricordi, tuttavia, che nel nostro caso l'unico tipo è double.
  
  // Prima definiamo il vettore (qui chiamato Doubles) con il tipo degli argomenti
  std::vector<Type*> Doubles(Args.size(), Type::getDoubleTy(*context));
  // Quindi definiamo il tipo (FT) della funzione
  FunctionType *FT = FunctionType::get(Type::getDoubleTy(*context), Doubles, false);
  // Infine definiamo una funzione (al momento senza body) del tipo creato e con il nome
  // presente nel nodo AST. ExternalLinkage vuol dire che la funzione può avere
  // visibilità anche al di fuori del modulo
  Function *F = Function::Create(FT, Function::ExternalLinkage, Name, *module);

  // Ad ogni parametro della funzione F (che, è bene ricordare, è la rappresentazione 
  // llvm di una funzione, non è una funzione C++) attribuiamo ora il nome specificato dal
  // programmatore e presente nel nodo AST relativo al prototipo
  unsigned Idx = 0;
  for (auto &Arg : F->args())
    Arg.setName(Args[Idx++]);

  /* Abbiamo completato la creazione del codice del prototipo.
     Il codice può quindi essere emesso, ma solo se esso corrisponde
     ad una dichiarazione extern. Se invece il prototipo fa parte
     della definizione "completa" di una funzione (prototipo+body) allora
     l'emissione viene fatta al momendo dell'emissione della funzione.
     In caso contrario nel codice si avrebbe sia una dichiarazione
     (come nel caso di funzione esterna) sia una definizione della stessa
     funzione.
  */
  if (emitcode) {
    F->print(errs());
    fprintf(stderr, "\n");
  };
  
  return F;
}

/************************* Function Tree **************************/
FunctionAST::FunctionAST(PrototypeAST* Proto, ExprAST* Body): Proto(Proto), Body(Body) {};

Function *FunctionAST::codegen(driver& drv) {
  // Verifica che la funzione non sia già presente nel modulo, cioò che non
  // si tenti una "doppia definizion"
  Function *function = 
      module->getFunction(std::get<std::string>(Proto->getLexVal()));
  // Se la funzione non è già presente, si prova a definirla, innanzitutto
  // generando (ma non emettendo) il codice del prototipo
  if (!function)
    function = Proto->codegen(drv);
  else
    return nullptr;
  // Se, per qualche ragione, la definizione "fallisce" si restituisce nullptr
  if (!function)
    return nullptr;  

  // Altrimenti si crea un blocco di base in cui iniziare a inserire il codice
  BasicBlock *BB = BasicBlock::Create(*context, "entry", function);
  builder->SetInsertPoint(BB);
 
  // Ora viene la parte "più delicata". Per ogni parametro formale della
  // funzione, nella symbol table si registra una coppia in cui la chiave
  // è il nome del parametro mentre il valore è un'istruzione alloca, generata
  // invocando l'utility CreateEntryBlockAlloca già commentata.
  // Vale comunque la pena ricordare: l'istruzione di allocazione riserva 
  // spazio in memoria (nel nostro caso per un double) e scrive l'indirizzo
  // in un registro SSA
  // Il builder crea poi un'istruzione che memorizza il valore del parametro x
  // (al momento contenuto nel registro SSA %x) nell'area di memoria allocata.
  // Si noti che il builder conosce il registro che contiene il puntatore all'area
  // perché esso è parte della rappresentazione C++ dell'istruzione di allocazione
  // (variabile Alloca) 
  
  for (auto &Arg : function->args()) {
    // Genera l'istruzione di allocazione per il parametro corrente
    AllocaInst *Alloca = CreateEntryBlockAlloca(function, Arg.getName());
    // Genera un'istruzione per la memorizzazione del parametro nell'area
    // di memoria allocata
    builder->CreateStore(&Arg, Alloca);
    // Registra gli argomenti nella symbol table per eventuale riferimento futuro
    drv.NamedValues[std::string(Arg.getName())] = Alloca;
  } 
  
  // Ora può essere generato il codice corssipondente al body (che potrà
  // fare riferimento alla symbol table)
  if (Value *RetVal = Body->codegen(drv)) {
    // Se la generazione termina senza errori, ciò che rimane da fare è
    // di generare l'istruzione return, che ("a tempo di esecuzione") prenderà
    // il valore lasciato nel registro RetVal 
    builder->CreateRet(RetVal);

    // Effettua la validazione del codice e un controllo di consistenza
    verifyFunction(*function);
 
    // Emissione del codice su su stderr) 
    function->print(errs());
    fprintf(stderr, "\n");
    return function;
  }

  // Errore nella definizione. La funzione viene rimossa
  function->eraseFromParent();
  return nullptr;
};

