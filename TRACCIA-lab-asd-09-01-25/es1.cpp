#include "set-dll.h"
/*************************************************/
/* Funzione da implementare                      */
/*************************************************/

//Es 1
//Ritorna il numero di coppie nell'insieme
unsigned int nbPairs(const set_list& li){
  unsigned int ris = 0;
  for(set_list tmp = li; tmp != nullptr; tmp = tmp -> next)
    for(pair_list pairs = tmp -> pairs; pairs != nullptr; pairs = pairs -> next_pair) ris++;
  return ris;
}