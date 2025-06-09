#include "set-dll.h"
/*************************************************/
/* Funzione da implementare                      */
/*************************************************/

// Es 2
// Aggiunge una coppia (v1,v2) all'insieme
// Se la coppia e' gia' presente, non fa nulla
void addPair(set_list &li, int v1, int v2) {
  set_list curr = li;
  int somma = v1 + v2;
  while (curr != empty_set_list) {
    if (curr->sum == somma) {
      pair_list curr1 = curr->pairs;
      while (curr1) {
        if (curr1->v1 == v1 && curr1->v2 == v2) {
          return;
        }
        curr1 = curr1->next_pair;
      }
      pair_list aux = new pair_node;
      aux->v1 = v1;
      aux->v2 = v2;
      aux->prev_pair = nullptr;
      aux->next_pair = curr->pairs;
      if (curr->pairs)
        curr->pairs->prev_pair = aux;

      curr->pairs = aux;
      return;
    }
    curr = curr->next;
  }
  pair_list aux = new pair_node;
  aux->v1 = v1;
  aux->v2 = v2;
  aux->prev_pair = nullptr;
  aux->next_pair = nullptr;
  set_list l = new set_node;
  l->next = li;
  l->prev = nullptr;
  if(li)
    li->prev = l;
  l->pairs = aux;
  li = l;
}