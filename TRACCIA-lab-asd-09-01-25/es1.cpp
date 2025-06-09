#include "set-dll.h"
/*************************************************/
/* Funzione da implementare                      */
/*************************************************/

//Es 1
//Ritorna il numero di coppie nell'insieme
unsigned int nbPairs(const set_list& li){
  set_list curr = li;
  unsigned int ris = 0;
  while(curr){
    pair_list curr1 = curr->pairs;
    while(curr1){
      ris++;
      curr1 = curr1->next_pair;
    }
    curr = curr->next;
  }
  return ris;
}