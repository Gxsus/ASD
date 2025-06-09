#include "dict-tree.h"
#include <iostream>

using namespace std;

/*************************************************/
/* Funzione da implementare                      */
/*************************************************/
// Es 2
// Verifica se una parola è nell'dizionario
// Ritorna true se è presente e false altrimenti

dictTree findCharInBrothers(char c, const dictTree &dt) {
  if (!dt)
    return nullptr;
  if (dt->val == c)
    return dt;
  return findCharInBrothers(c, dt->brother);
}

bool isPresent(string st, const dictTree &dt) {
  dictTree curr = findCharInBrothers(st[0], dt);
  if (!curr)
    return false;
  unsigned int i = 1;
  curr = curr->son;
  while (i < st.length()) {
    if (curr->val == st[i]) {
      i++;
      curr = curr->son;
    } else {
      curr = findCharInBrothers(st[i], curr);
      if (!curr)
        return false;
      i++;
      curr = curr->son;
    }
  }
  return (curr->val == '8');
}