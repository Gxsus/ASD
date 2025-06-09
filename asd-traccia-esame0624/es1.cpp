#include "trinary-tree.h"

struct cell{
  triTree el;
  cell *next;
};

typedef cell* stack;
stack emptyStack = nullptr;

stack createEmptyStack();
bool isEmptyStack(stack s);
void addElemStack(stack &s, triTree e);
bool popElemStack(stack &s, triTree &e);

unsigned int nbOccurrence(Elem el,const triTree& tr){
  if(tr == nullptr) return 0;
  stack s = createEmptyStack();
  triTree curr;
  unsigned int ris = 0;
  addElemStack(s, tr);

  while(popElemStack(s, curr)){
    if(curr -> el == el) ris++;
    if(curr -> child1 != nullptr) addElemStack(s, curr -> child1);
    if(curr -> child2 != nullptr) addElemStack(s, curr -> child2);
    if(curr -> child3 != nullptr) addElemStack(s, curr -> child3);
  }

  return ris;
}

stack createEmptyStack(){ return emptyStack; }

bool isEmptyStack(stack s){ return s == emptyStack; }

void addElemStack(stack &s, triTree e){
  stack tmp = new cell;
  tmp -> el = e;
  tmp -> next = s;
  s = tmp;
}

bool popElemStack(stack &s, triTree &e){
  if(isEmptyStack(s)) return false;
  stack tmp = s -> next;
  e = s -> el;
  delete s;
  s = tmp;
  return true;
}