# Progetto Compilatore Kaleidoscope - Readme

## Descrizione del Progetto

Questo progetto si propone di implementare un compilatore per il linguaggio Kaleidoscope. Il linguaggio è descritto da una grammatica di primo livello, e successive versioni del progetto si concentrano su miglioramenti e estensioni della grammatica.

## Grammatica di Primo Livello

La grammatica di primo livello del linguaggio Kaleidoscope è definita nel file `grammatica.kl` come segue:

```bnf
% start startsymb ; globalvar :
" global " "id"

startsymb :
program idseq :
% empty
program : | "id" idseq
% empty
| top ";" program % left ":";
% left " <" "==";
top : % left "+" " -";
% empty % left "*" "/";
| definition
| external stmts :
| globalvar stmt

| stmt ";" stmts

definition :
" def " proto block stmt :
assignment
external : | block
" extern " proto | exp
proto : assignment
"id" "(" idseq ")" "id" "=" exp
