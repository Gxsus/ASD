#include "tree-chsib.h"

using namespace tree;

/* Nota: nei commenti usiamo "albero" e "puntatore a un nodo" come sinonimi, scegliendo di volta in volta
la formulazione più adatta a dare la specifica di una funzione. 
Dal punto di vista tecnico, usiamo sempre il tipo Tree sia quando operiamo su un albero, sia quando operiamo, 
a livello concettuale, su un puntatore a un nodo dell'albero. 
Questo approccio e' corretto in quanto un albero (o sottoalbero) è un puntatore a una struct di tipo treeNode:
un albero è identificato univocamente dal puntatore alla sua radice */ 



/*******************************************************************************************************/
// il nodo di un albero è caratterizzato dall'etichetta, il puntatore al primo figlio e il puntatore al prossimo fratello
// NON manteniamo il puntatore al padre, anche se sarebbe comodo per alcune funzioni (ma del tutto inutile per altre)
struct tree::treeNode {
    Label label;    
    treeNode *firstChild;
    treeNode *nextSibling;
};

struct cell {
    Tree label;    
    cell *next;
};

typedef cell* stack;

stack emptyStack = nullptr;

stack createEmptyStack(){ return emptyStack; }

bool isEmptyStack(stack s){ return s == emptyStack; }

void addElemStack(stack &s, Tree t){
   if(isEmptyStack(s)){
      s = new cell;
      s -> label = t;
      s -> next = emptyStack;
      return;
   }
   stack tmp = new cell;
   tmp -> next = s;
   tmp -> label = t;
   s = tmp;
}

Tree getElemStack(stack s){
   return s -> label;
}

Tree popElemStack(stack &s){
   if(isEmptyStack(s)) return emptyTree;
   Tree ret = s -> label;
   stack tmp = s -> next;
   delete s;
   s = tmp;
   return ret;
}

Tree getNode(Label l, Tree t){
   if(isEmpty(t)) return emptyTree;
   else if(t -> label == l) return t;
   Tree tmp = getNode(l, t -> firstChild);
   return isEmpty(tmp)?getNode(l, t -> nextSibling): tmp;
}




/*******************************************************************************************************/
// isEmpty restituisce true se l'albero t e' vuoto, false altrimenti
bool tree::isEmpty(const Tree& t)
{ 
   return t == emptyTree;
}



/*******************************************************************************************************/
// addElem aggiunge il nodo etichettato con labelOfNodeToAdd come
// figlio del nodo etichettato con labelOfNodeInTree.
// Caso particolare: aggiunta della radice, che si ottiene
// con labelOfNodeInTree uguale a emptyLabel (= nessun padre), e ha successo
// solo se l'albero e' vuoto (in caso contrario restituisce FAIL 
// e non aggiunge nulla).
// Restituisce FAIL se non esiste un nodo nell'albero etichettato 
// con labelOfNodeInTree oppure se nell'albero esiste gia' un nodo 
// etichettato con labelOfNodeToAdd; aggiunge e restituisce OK altrimenti  
Error tree::addElem(const Label labelOfNodeInTree, const Label labelOfNodeToAdd, Tree& t)
{
   if(member(labelOfNodeToAdd, t)) return FAIL;
   else if(labelOfNodeInTree == emptyLabel){
      if(!isEmpty(t)) return FAIL;
      t = new treeNode;
      t -> firstChild = emptyTree;
      t -> nextSibling = emptyTree;
      t -> label = labelOfNodeToAdd;
      return OK;
   }
   Tree node = getNode(labelOfNodeInTree, t), tmp;
   if(isEmpty(node)) return FAIL;
   tmp = node -> firstChild;
   node -> firstChild = new treeNode;
   node -> firstChild -> firstChild = emptyTree;
   node -> firstChild -> nextSibling = tmp;
   node -> firstChild -> label = labelOfNodeToAdd;
   return OK;
}     



/*******************************************************************************************************/
// deleteElem (versione iterativa) rimuove dall'albero il nodo etichettato con la Label l
// e collega al padre di tale nodo tutti i suoi figli
// Restituisce FAIL se si tenta di cancellare la radice e questa ha 
// dei figli (non si saprebbe a che padre attaccarli) oppure se non esiste 
// un nodo nell'albero etichettato con la Label; cancella e restituisce OK altrimenti
Error tree::deleteElemI(const Label l, Tree& t)
{
   stack s = createEmptyStack();
   Tree tree, tmp, aux, d;
   addElemStack(s, t);

   while(!isEmptyStack(s)){
      // tolgo il ramo dallo stack e controllo i figli
      tree = popElemStack(s);
      tmp = tree -> firstChild;
      if(!isEmpty(tmp)){
         if(tmp -> label == l){
            if(isEmpty(tmp -> firstChild)) tree -> firstChild = tmp -> nextSibling;
            else{
               aux = tmp -> firstChild;
               tree -> firstChild = aux;
               while(!isEmpty(aux -> nextSibling)) aux = aux -> nextSibling;
               aux -> nextSibling = tmp -> nextSibling;
            }
            delete tmp;
            return OK;
         }

         while(!isEmpty(tmp -> nextSibling)){ 
            if(tmp -> nextSibling -> label == l){
               if(isEmpty(tmp -> nextSibling -> firstChild)){ aux = tmp -> nextSibling; tmp -> nextSibling = aux -> nextSibling; delete aux;}
               else{
                  aux = tmp -> nextSibling -> firstChild;
                  d = tmp -> nextSibling;
                  tmp -> nextSibling = aux;
                  while(!isEmpty(aux -> nextSibling)) aux = aux -> nextSibling;
                  aux -> nextSibling = d -> nextSibling;
                  delete d;
               }
               return OK;
            }
            tmp = tmp -> nextSibling;
         }

         addElemStack(s, tree -> firstChild);
      }
      if(!isEmpty(tree -> nextSibling)) addElemStack(s, tree -> nextSibling);
   }

   return FAIL;
}




/*******************************************************************************************************/
// deleteElem (versione ricorsiva): stesso comportamento della versione iterativa, ma implementata ricorsivamente
// (può anche non essere ricorsiva la deleteElemR, ma deve fare uso di funzioni ausiliarie ricorsive)
Error tree::deleteElemR(const Label l, Tree& t)
{
   if(isEmpty(t)) return FAIL;

   Tree tmp = t -> firstChild, aux, d;

   if(isEmpty(tmp)) return deleteElemR(l, t -> nextSibling);
   else if(tmp -> label == l){
      if(tmp -> label == l){
         if(isEmpty(tmp -> firstChild)) t -> firstChild = tmp -> nextSibling;
         else{
            aux = tmp -> firstChild;
            t -> firstChild = aux;
            while(!isEmpty(aux -> nextSibling)) aux = aux -> nextSibling;
            aux -> nextSibling = tmp -> nextSibling;
         }
         delete tmp;
         return OK;
      }
   }

   while(!isEmpty(tmp -> nextSibling)){ 
      if(tmp -> nextSibling -> label == l){
         if(isEmpty(tmp -> nextSibling -> firstChild)){ aux = tmp -> nextSibling; tmp -> nextSibling = aux -> nextSibling; delete aux;}
         else{
            aux = tmp -> nextSibling -> firstChild;
            d = tmp -> nextSibling;
            tmp -> nextSibling = aux;
            while(!isEmpty(aux -> nextSibling)) aux = aux -> nextSibling;
            aux -> nextSibling = d -> nextSibling;
            delete d;
         }
         return OK;
      }
      tmp = tmp -> nextSibling;
   }

   return deleteElemR(l, t -> firstChild) == OK? OK: deleteElemR(l, t -> nextSibling);
}



/*******************************************************************************************************/
// father restituisce l'etichetta del padre del nodo con etichetta l se il nodo esiste nell'albero 
// (o sottoalbero) t e se il padre esiste. 
// Restituisce la costante emptyLabel altrimenti
Label tree::father(const Label l, const Tree& t)
{ 
   if(isEmpty(t)) return emptyLabel;

   Tree tmp = t -> firstChild;
   while(!isEmpty(tmp)){ 
      if(tmp -> label == l) return t -> label;
      tmp = tmp -> nextSibling;
   }

   Label ret = father(l, t -> firstChild);
   return ret == emptyLabel? father(l, t -> nextSibling): ret;
}



/*******************************************************************************************************/
// children restituisce una lista di Label, contenente le etichette 
// di tutti i figli nell'albero t del nodo etichettato con l
// La lista può essere implementata usando una qualunque delle strutture dati viste a lezione
// (non un Vector!!!): si riusi una implementazione del TDD list, adattandola 
// a elementi di tipo string (nelle precedenti esercitazioni gli elementi erano int)
list::List tree::children(const Label l, const Tree& t)
{
   list::List lst = list::createEmpty();
   stack s = createEmptyStack();
   Tree node = getNode(l, t) -> firstChild;
   if(isEmpty(node)) return lst;
   addElemStack(s, node);

   while(!isEmptyStack(s)){
      node = popElemStack(s);
      if(!isEmpty(node->firstChild)) addElemStack(s, node->firstChild);
      if(!isEmpty(node->nextSibling)) addElemStack(s, node->nextSibling);
      list::addFront(node -> label, lst);
   }

   return lst;
}



/*******************************************************************************************************/
// degree restituisce il numero di archi uscenti dal nodo etichettato con l; restituisce -1 se non esiste 
// nessuna etichetta l nell'albero
int tree::degree(const Label l, const Tree& t)
{
   if(isEmpty(t)) return -1;
   else if(t -> label == l) return 0;
   
   int tmp = degree(l, t -> firstChild);
   return tmp >= 0? tmp + 1: degree(l, t -> nextSibling); // ci sommo 1 solo se viene dal figlio
}



/*******************************************************************************************************/
// ancestors (versione ricorsiva) restituisce una lista di Label, contenente le etichette 
// di tutti gli antenati del nodo l ESCLUSA l'etichetta del nodo stesso
// La lista può essere implementata usando una delle strutture dati viste a lezione
// (non un Vector)
// (può anche non essere ricorsiva la ancestorsR, ma deve fare uso di funzioni ausiliarie ricorsive)
stack ancestorsRic(const Label l, const Tree& t)
{
   if(isEmpty(t)) return emptyStack;

   stack s;
   if(t -> label == l){
      s = createEmptyStack();
      addElemStack(s, t);
      return s;
   }
   s = ancestorsRic(l, t->firstChild);
   if(!isEmptyStack(s)){ addElemStack(s, t); cout << t -> label << endl; return s;}
   return ancestorsRic(l, t->nextSibling);
}

list::List tree::ancestorsR(const Label l, const Tree& t)
{
   list::List lst = list::createEmpty();
   if(isEmpty(t)) return lst;
   stack s = ancestorsRic(l, t);
   
   if(isEmptyStack(s)) return lst;
   Tree node = popElemStack(s);

   while(node -> label != l){ 
      list::addBack(node -> label, lst);
      node = popElemStack(s);
   }

   return lst;
}



/*******************************************************************************************************/
// ancestors (versione iterativa) restituisce una lista di Label, contenente le etichette 
// di tutti gli antenati del nodo l ESCLUSA l'etichetta del nodo stesso
// La lista può essere implementata usando una delle strutture dati viste a lezione
// (non un Vector)
list::List tree::ancestorsI(const Label l, const Tree& t)
{
   list::List lst = list::createEmpty();
   Label ft = father(l, t);
   if(ft == emptyLabel) return lst;
   list::addFront(ft, lst);

   while(ft != t -> label){
      ft = father(ft, t);
      list::addFront(ft, lst);
   }

   return lst;
}



/*******************************************************************************************************/
// leastCommonAncestor restituisce l'etichetta del minimo antenato comune 
// ai nodi etichettati con label1 e label2
Label tree::leastCommonAncestor(const Label label1, const Label label2, const Tree& t)
{
   list::List lst1 = ancestorsI(label1, t), lst2 = ancestorsI(label2, t);
   int size1 = list::size(lst1), size2 = list::size(lst2);
   for(int i = size1 - 1; i >= 0; i--)
      for(int j = size2 - 1; j >= 0; j--)
         if(list::get(i, lst1) == list::get(j, lst2)) return get(i, lst1);
   return emptyLabel;
}



/*******************************************************************************************************/
// member restituisce true se il nodo etichettato con la label l appartiene all'albero t e false altrimenti
bool tree::member(const Label l, const Tree& t)
{ 
   if(isEmpty(t)) return false;
   if(t -> label == l) return true;
   if(member(l, t -> firstChild)) return true;
   return member(l, t -> nextSibling);
}



/*******************************************************************************************************/
// numNodes restituisce il numero di nodi nell'albero t mediante una visita ricorsiva in depthfirst
int tree::numNodes(const Tree& t)
{
   if(isEmpty(t)) return 0;
   
   return numNodes(t -> firstChild) + 1 + numNodes(t -> nextSibling);
}



/*******************************************************************************************************/
// createEmptyTree restituisce l'albero vuoto
Tree tree::createEmpty()
{
   return emptyTree;
}



/*******************************************************************************************************/
// Visualizzazione possibilmente strutturata come visto a lezione
void printTreeRic(const Tree& t, int grade) {
   if(isEmpty(t)) return;

   cout << grade << "-";
   for(int i = 0; i < grade; i++) cout << "--";
   cout << t -> label<< endl;
   printTreeRic(t -> firstChild, grade + 1);
   printTreeRic(t -> nextSibling, grade);
}

void printTree(const Tree& t) {
   printTreeRic(t, 0);
}



/****************************************************************/
// Questa funzione NON richiede di conoscere come e' fatta la struttura dati che implementa l'albero: usa solo addElem e quindi e' ad 
// un alto livello di astrazione
// Vantaggi: codice compatto, leggibile, riutilizzabile per qualunque implementazione del TDD Tree
// Svantaggi: inefficiente: la addElem cerca ogni volta il nodo con etichetta fatherLabel, mentre basterebbe una chiamata sola per 
// trovarlo e poi si potrebbero attaccare tutti i figli a esso, senza ripetere la dispendiosa ricerca nell'albero; per renderla 
// efficiente dovrei pero' accedere direttamente alla struttura dati chiamando qualche funzione ausiliaria che operi 
// sui nodi dell'albero, rinunciando a scrivere codice modulare, chiaro e ad un ragionevole livello di astrazione... 
// Non esiste un'opzione migliore tra le due: se il codice deve essere efficiente, è opportuno scrivere una funzione ad hoc per 
// una determinata implementazione; se il codice deve essere riutilizzabile, bisogna limitarsi a usare le funzioni offerte dall'
// interfaccia del TDD in modo che la funzione continui ad andare bene anche se cambia l'implementazione
Tree readFromStream(istream& str)
{
    Tree t = createEmpty(); 
    string line;
    Label rootLabel, fatherLabel, childLabel;
    getline(str, line);  
    istringstream instream;            // uso una variabile di tipo istringstream per poter scandire i pezzi di ogni riga usando >>
    instream.clear();
    instream.str(line);
    instream >> rootLabel;             // il primo elemento che si incontra nel file e' l'etichetta della radice, per convenzione su come deve essere fatto il file
    addElem(emptyLabel, rootLabel, t); // la si inserisce nell'albero vuoto, indicando che il padre non c'e' (primo argomento emptyLabel)
    getline(str, line);                // poi si iniziano a scansionare le righe seguenti
    instream.clear();
    instream.str(line);
    while (!str.eof())  
        {        
	instream >> fatherLabel; // in ogni riga del file, il primo elemento e' l'etichetta del nodo padre e gli altri sono le etichette dei figli
        removeBlanksAndLower(fatherLabel); // normalizzo l'etichetta del padre
        while (!instream.eof())            // finche' la riga corrente non e' terminata
            { 
            instream >> childLabel;              // leggo la prossima etichetta
            removeBlanksAndLower(childLabel);    // la normalizzo
            addElem(fatherLabel, childLabel, t); // e la attacco al padre
            }
        getline(str, line);  
        instream.clear();
        instream.str(line);
        }
    str.clear();
    return t;
}



/****************************************************************/
Tree readFromFile(string nome_file)
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    if (!ifs) {cout << "\nErrore apertura file, verificare di avere inserito un nome corretto\n"; return createEmpty();}  
    return readFromStream(ifs);
}

