#include "dict-tree.h"
#include <iostream>

/*************************************************/
/* Funzione da implementare                      */
/*************************************************/

//Es 1
//Ritorna il numero di parole nell' albero
unsigned int nbWords(const dictTree& dt){
  if(dt == nullptr) return 0;
  if(dt -> val == '8') return 1 + nbWords(dt -> brother);
  return nbWords(dt -> son) + nbWords(dt -> brother);
}

