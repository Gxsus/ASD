#include "dict-tree.h"

using namespace std;

/*************************************************/
/* Funzione da implementare                      */
/*************************************************/
//Es 3
//Ritorna la parola piu' piccola dell'albero
//Se l'albero e' vuoto, ritorna la string vuota ""
dictTree findMinInBrothers(const dictTree &dt) {
  if(!dt)
    return emptyDictTree;
  char min = dt->val;
  dictTree ris = dt;
  dictTree curr = dt;
  while(curr){
    if(curr->val < min){
      min = curr->val;
      ris = curr;
    }
    curr = curr->brother;
  }
  return ris;
}

string minWord(const dictTree& dt){
  if(!dt)
    return "";
  string ris = "";
  dictTree curr = findMinInBrothers(dt);
  ris += curr->val;
  if(curr->son->val == '8')
    return ris;
  while(curr->val != '8'){
    if(curr->son->val == '8')
      return ris;
    curr = findMinInBrothers(curr->son);
    ris += curr->val;
  }
  return ris;
}

