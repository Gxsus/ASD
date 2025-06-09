#include <iostream>

#include "graph.h"

using namespace graph;

struct halfEdgeVertex{ // Lista di adiacenza
  vertexNode *node;
  Weight weight;
  halfEdgeVertex *next;
};

struct graph::vertexNode { // Lista dei vertici
  Label l;
  halfEdgeVertex *adjLst;
  vertexNode *next;
  bool isVisited;
};

Graph getVertex(Label l, Graph g){
  while(!isEmpty(g)){
    if(g -> l == l) return g;
    g = g -> next;
  }

  return emptyGraph;
}

/**********************************************************************/
/*               Funzione da implementare                             */
/**********************************************************************/
// Restituisce il grafo vuoto
Graph graph::createEmptyGraph(){
  return emptyGraph;
}

// Aggiunge nuovo vertice con etichetta la stringa.
// Se non è gia presente, ritorna true, altrimenti fallisce e ritorna false 
bool graph::addVertex(Label l, Graph& g){
  if(!isEmpty(getVertex(l, g))) return false;
  Graph tmp = new vertexNode;
  tmp -> l = l;
  tmp -> next = g;
  tmp -> adjLst = nullptr;
  g = tmp;
  return true;
}

// Aggiunge nuovo arco tra i due vertici con etichette le due stringe e peso
// l'intero. Fallisce se non sono presenti tutti e due i nodi o se l'arco
// tra i due e' gia' presente. Se fallisce ritorna false,
// altrimenti ritorna true
bool graph::addEdge(Label from, Label to, Weight w, Graph& g){
  if(from == to) return false;
  Graph g1 = getVertex(from, g), g2 = getVertex(to, g);
  if(isEmpty(g1) or isEmpty(g2)) return false;
  halfEdgeVertex *adjLst1 = g1 -> adjLst, *adjLst2 = g2 -> adjLst;

  while(adjLst1 != nullptr && adjLst2 != nullptr){
    if(adjLst1 -> node -> l == to or adjLst2 -> node -> l == from){ return false; }
    adjLst1 = adjLst1 -> next;
    adjLst2 = adjLst2 -> next;
  }
  
  adjLst1 = new halfEdgeVertex;
  adjLst2 = new halfEdgeVertex;
  adjLst1 -> node = g2;
  adjLst1 -> next = g1 -> adjLst;
  adjLst1 -> weight = w;
  g1 -> adjLst = adjLst1;
  adjLst2 -> node = g1;
  adjLst2 -> next = g2 -> adjLst;
  adjLst2 -> weight = w;
  g2 -> adjLst = adjLst2;
  return true;
}

// Restituisce true se il grafo e' vuoto, false altrimenti
bool graph::isEmpty(const Graph& g){
  return g == emptyGraph;
}

// Ritorna il numero di vertici del grafo
unsigned int graph::numVertices(const Graph& g){
  Graph cp = g;
  int ret = 0;
  while(!isEmpty(cp)){
    cp = cp -> next;
    ret++;
  }
  return ret;
}

// Ritorna il numero di archi del grafo
unsigned int graph::numEdges(const Graph& g){
  Graph cp = g;
  halfEdgeVertex *adjLst;
  int ret = 0;
  while(!isEmpty(cp)){
    adjLst = cp -> adjLst;
    while(adjLst != nullptr){
      ret++;
      adjLst = adjLst -> next;
    }
    cp = cp -> next;
  } 

  return ret / 2;
}

// Calcola e ritorna (nel secondo parametro) il grado del vertice.
// Restituisce un valore falso se il vertice non esiste,
// altrimenti ritorna true
bool graph::nodeDegree(Label l, unsigned int& degree, const Graph& g) {
  Graph gr = getVertex(l, g);
  if(isEmpty(gr)) return false;
  halfEdgeVertex *adjLst = gr -> adjLst;
  unsigned int ret = 0;
  while(adjLst != nullptr){
    ret++;
    adjLst = adjLst -> next;
  }

  degree = ret;
  return true;
}

// Verifica se due vertici sono adiacenti (ovvero se esiste un arco)
bool graph::areAdjacent(Label v1, Label v2, const Graph& g) {
  if(v1 == v2) return false;
  Graph g1 = getVertex(v1, g), g2 = getVertex(v2, g);
  if(isEmpty(g1) or isEmpty(g2)) return false;
  halfEdgeVertex *adjLst1 = g1 -> adjLst, *adjLst2 = g2 -> adjLst;

  while(adjLst1 != nullptr && adjLst2 != nullptr){
    if(adjLst1 -> node -> l == v2 or adjLst2 -> node -> l == v1){ return true; }
    adjLst1 = adjLst1 -> next;
    adjLst2 = adjLst2 -> next;
  }

  return false;
}

// Ritorna la lista di adiacenza di un vertice
// corrispondente alla lista dei label dei vertici adiacenti
list::List graph::adjacentList(Label v1, const Graph& g) {
  Graph gr = getVertex(v1, g);
  list::List ret = list::createEmpty();
  if(!isEmpty(gr)){
    halfEdgeVertex *adjLst = gr -> adjLst;
    while(adjLst != nullptr){
      list::addFront(adjLst -> node -> l, ret);
      adjLst = adjLst -> next;
    }
  }

  return ret;
}

// Calcola, se esiste, un cammino tra due vertici
// Il primo argomento e il vertice di partenza
// Il secondo argomento e il vertice di arrivo
// Il terzo argomento conterrà la lista delle etichette degli
// vertici visitati sul cammino (senza il vertice di partenza, ne il vertice
// di arrivo)
// Si assume che il chiamante fornisca inizialmente una lista vuota.
// Il quarto argomento è il peso del cammino
// La funziona ritorna false, se il vertice di partenza e uguale al vertice
// di arrivo, o se non c'e un cammino tra i due vertici, altrimenti
// ritorna true
bool findPathRic(Label v, list::List& path, Weight& weight, const Graph& g) {
  if(v == g -> l) return true;

  halfEdgeVertex* tmp = g -> adjLst;  
  while(tmp != nullptr){
    if(!tmp -> node -> isVisited){
      tmp -> node -> isVisited = true;
      if(findPathRic(v, path, weight, tmp -> node)){
        weight += tmp -> weight;
        list::addFront(g -> l, path);
        return true;
      }
    }
    tmp = tmp -> next;
  }

  return false; 
}

bool graph::findPath(Label v1, Label v2, list::List& path, Weight& weight, const Graph& g) {
  list::clear(path);
  path = list::createEmpty();
  weight = 0;

  if(v1 == v2) return true;

  Graph tmp = g;
  while(!isEmpty(tmp)){
    tmp -> isVisited = false;
    tmp = tmp -> next;
  }

  return findPathRic(v2, path, weight, getVertex(v1, g));
}

// Svuota un grafo
void graph::clear(graph::Graph& g){
  halfEdgeVertex *tmp_h;
  Graph tmp_g = g;

  while(!isEmpty(g)){
    tmp_g = g -> next;
    while(g -> adjLst != nullptr){
      tmp_h = g -> adjLst -> next;
      delete g -> adjLst;
      g -> adjLst = tmp_h;
    }
    delete g;
    g = tmp_g;
  }
}

// Stampa il grafo
// Per ogni vertice stampa su una riga l'etichetta del vertice seguito di ':'
// poi le etichette dei vertici adiacenti con fra parentesi il peso associato,
// separate da virgole
void graph::printGraph(const graph::Graph& g) {
  Graph tmp_g = g;
  halfEdgeVertex *tmp_h;
  while(!isEmpty(tmp_g)){
    cout << tmp_g -> l << ": ";
    tmp_h = tmp_g -> adjLst;
    if(tmp_h == nullptr) cout << "EMPTY ADJLIST";
    else while(true){
      cout << tmp_h -> node -> l << " (" << tmp_h -> weight << ")";
      tmp_h = tmp_h -> next;
      if(tmp_h  == nullptr) break;
      cout << ", ";
    }
    cout << ";" << endl;
    tmp_g = tmp_g -> next;
  }
}
