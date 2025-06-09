#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector> 
#include <fstream> 
#include <string>  
#include <chrono>        
#include "string-utility.h"
#include "list-array.h"

using namespace std::chrono; 
using namespace std; 

namespace tree{

  enum Error {OK, FAIL};

  typedef string Label;      

  const Label emptyLabel = "$#$#$";

  struct treeNode; // definita nel file tree-chsib.cpp

  typedef treeNode* Tree; // un albero è identificato dal puntatore alla sua radice; useremo indistintamente "albero" e "puntatore a nodo"

  const Tree emptyTree = NULL; 

  // isEmpty restituisce true se l'albero t e' vuoto, false altrimenti
  bool isEmpty(const Tree&);

  // addElem aggiunge un nodo etichettato con la prima label 
  // come figlio del nodo etichettato la seconda label
  Error addElem(const Label, const Label, Tree&);

  // deleteElem (versione iterativa) rimuove dall'albero il nodo etichettato con la Label l
  // e collega al padre di tale nodo tutti i suoi figli
  // Restituisce FAIL se si tenta di cancellare la radice e questa ha 
  // dei figli (non si saprebbe a che padre attaccarli) oppure se non esiste 
  // un nodo nell'albero etichettato con la Label; cancella e restituisce OK altrimenti
  Error deleteElemI(const Label, Tree&);

  // deleteElem (come sopra ma versione ricorsiva) 
  Error deleteElemR(const Label, Tree&);
  
  // father restituisce l'etichetta del padre del nodo con etichetta l
// se il nodo esiste nell'albero (o sottoalbero) t e se il padre esiste. 
// Restituisce la costante emptyLabel altrimenti
  Label father(const Label, const Tree&);

  // children restituisce una lista di Label, contenente le etichette 
  // di tutti i figli nell'albero t del nodo etichettato con l
  list::List children(const Label, const Tree&);

  // degree restituisce il numero di archi uscenti dal nodo etichettato con l; 
  // restituisce -1 se non esiste nessuna etichetta l nell'albero
  int degree(const Label, const Tree&);

  // ancestors (versione ricorsiva) restituisce una lista di Label, contenente le etichette 
  // di tutti gli antenati del nodo l ESCLUSA l'etichetta del nodo stesso
  list::List ancestorsR(const Label, const Tree&);

  // ancestors (come sopra ma versione iterativa) 
  list::List ancestorsI(const Label, const Tree&);

  // leastCommonAncestor restituisce l'etichetta del minimo antenato comune 
 // ai nodi etichettati con label1 e label2
  Label leastCommonAncestor(const Label, const Label, const Tree&);

  // member restituisce 
  // true se il nodo etichettato con la label l appartiene all'albero t e false altrimenti
  bool member(const Label, const Tree&);

  // numNodes restituisce il numero di nodi nell'albero t 
  // mediante una visita ricorsiva in depthfirst
  int numNodes(const Tree&);
  
  // createEmptyTree restituisce l'albero vuoto
  Tree createEmpty();
}


/* Funzioni che non caratterizzano il TDD Tree, ma che servono per input/output */
tree::Tree readFromFile(string);
void printTree(const tree::Tree&);
