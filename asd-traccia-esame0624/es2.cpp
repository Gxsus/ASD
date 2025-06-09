#include "trinary-tree.h"

// DECLARATION OF STACK
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

void deleteTree(triTree& tr){
  if(tr == nullptr) return;
  deleteTree(tr -> child1);
  deleteTree(tr -> child2);
  deleteTree(tr -> child3);
  delete tr;
}

// FUNCTION TO WRITE
void deleteAll(Elem el, triTree& tr){
  stack s = createEmptyStack();
  triTree tmp, del;
  bool wasFound;

  while(tr != nullptr && tr -> el == el){
    tmp = tr;
    tr = tr -> child2;
    delete tmp;
  }

  if(tr == nullptr) return;

  addElemStack(s, tr);
  while(popElemStack(s, tmp)){
    wasFound = false;
    
    if(tmp -> child1 != nullptr && tmp -> child1 -> el == el){
      wasFound = true;
      deleteTree(tmp -> child1 -> child2);
      deleteTree(tmp -> child1 -> child3);
      del = tmp -> child1;
      tmp -> child1 = tmp -> child1 -> child1;
      delete del;
    }

    if(tmp -> child2 != nullptr && tmp -> child2 -> el == el){
      wasFound = true;
      deleteTree(tmp -> child2 -> child1);
      deleteTree(tmp -> child2 -> child3);
      del = tmp -> child2;
      tmp -> child2 = tmp -> child2 -> child2;
      delete del;
    }

    if(tmp -> child3 != nullptr && tmp -> child3 -> el == el){
      wasFound = true;
      deleteTree(tmp -> child3 -> child1);
      deleteTree(tmp -> child3 -> child2);
      del = tmp -> child3;
      tmp -> child3 = tmp -> child3 -> child3;
      delete del;
    }

    if(wasFound) addElemStack(s, tmp);
    else{
      if(tmp -> child1 != nullptr) addElemStack(s, tmp -> child1);
      if(tmp -> child2 != nullptr) addElemStack(s, tmp -> child2);
      if(tmp -> child3 != nullptr) addElemStack(s, tmp -> child3);
    }
  }
  
}

//DEFINITION OF THE STACK
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