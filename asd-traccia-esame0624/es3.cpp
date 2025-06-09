#include "trinary-tree.h"

using namespace std;

std::string leavesToString(const triTree& tr){
  if(tr == nullptr) return "";
  else if(tr -> child1 == nullptr && tr -> child2 == nullptr && tr -> child3 == nullptr) 
    return to_string(tr -> el) + " ";
  return leavesToString(tr -> child1) + leavesToString(tr -> child2)+ leavesToString(tr -> child3);
}

