#include "set-dll.h"
#include <iostream>

/*************************************************/
/* Funzione da implementare                      */
/*************************************************/


// Es 3
// Cancella dell'insieme la coppia (v1,v2)
// Se la coppia non e' presente non fa nulla
void deletePair(set_list &li, int v1, int v2) {
  std::cout << "  ciao " << std::endl;
  int somma = v1 + v2;
  set_list curr = li;
  while (curr) {
    if (curr->sum == somma) {
      pair_list pcurr = curr->pairs;
      while (pcurr) {
        if (pcurr->v1 == v1 && pcurr->v2 == v2) {
          if (pcurr->next_pair)
            pcurr->next_pair->prev_pair = pcurr->prev_pair;
          if (pcurr->prev_pair)
            pcurr->prev_pair->next_pair = pcurr->next_pair;
          if (pcurr == curr->pairs){
            curr->pairs = pcurr->next_pair;
          }
          if (!pcurr->next_pair && !pcurr->prev_pair) {
            delete pcurr;
            if(!curr->next && !curr->prev){
              delete curr;
              li = empty_set_list;
              return;
            }
            if(curr->prev)
              curr->prev->next = curr->next;
            if (curr->next) 
              curr->next->prev = curr->prev;
            if (curr == li){
              li = curr->next;
            }
            delete curr;
            return;
          }
          delete pcurr;
          return;
        }
        pcurr = pcurr->next_pair;
      }
    }
    curr = curr->next;
  }
}
