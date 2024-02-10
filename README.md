# Progetto Compilatore Kaleidoscope - Readme

## Descrizione del Progetto

Questo progetto si propone di implementare un compilatore per il linguaggio Kaleidoscope. Il linguaggio è descritto da una grammatica su 4 livelli.

## Grammatica di Primo Livello

La grammatica di primo livello del linguaggio Kaleidoscope è definita come segue:

```bnf
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

```
