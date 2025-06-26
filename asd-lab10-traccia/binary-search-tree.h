#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include "list-array.h"

using namespace list;

namespace bst{
    struct AdjListBI;
    struct AdjListIt;
    typedef AdjListBI* ListBI;
    typedef AdjListIt* ListIt;

    struct BIt{
        Elem key;
        int quantity;
    };

    struct It{
        Elem key;
        ListBI basicComponents; // i basic items che lo compongono
        ListIt components; // gli items normali che lo compongono
    };
    
    typedef BIt* BasicItem;
    typedef It* Item;

    struct AdjListBI{
        BasicItem item;
        ListBI next;
    };

    struct AdjListIt{
        Item item;
        ListIt next;
    };

    struct nodeBI{
        nodeBI *bst_left;
        nodeBI *bst_right;
        BasicItem item;
    }; // struttura per l'albero di ricerca dei basic items

    struct nodeIt{
        nodeIt *bst_left;
        nodeIt *bst_right;
        Item item;
    }; // struttura per l'albero di ricerca degli items

    typedef nodeBI* bstBI;
    typedef nodeIt* bstIt;

    bstBI getEmptyBstBI();
    bstIt getEmptyBstIt();
    BasicItem getEmptyBI();
    Item getEmptyIt();

    /*
        +-----------------------------------+
        |           bstBI FUNZIONI          |
        +-----------------------------------+

        Nota: Per leggere le funzioni del bstIt andare a riga 71
    */ 

    // Crea un albero bstBI vuoto per i basic item.
    bstBI createEmptyBstBI();

    // Returna true se il bstBI è vuoto, altrimenti false.
    bool isEmptyBstBI(const bstBI&);
    
    // Aggiunge un basic item al bstBI se non lo trova, e returna true.
    // Nel caso in cui il basic item è già presente in uno degli alberi returna false.
    bool addItemBstBI(Elem, bstBI&, const bstIt &bstI);

    // Rimuove un basic item al bstBI se lo trova, e returna true.
    // Nel caso in cui il basic item non è presente nella lista returna false.
    bool removeItemBstBI(Elem, bstBI&, bstIt&);

    // Returna il basic item con valore passato come parametro se lo trova,
    // altrimenti returna emptyBstBI.
    BasicItem getItemBstBI(Elem, const bstBI&);

    // Returna true se trova il basic item con valore passato come parametro,
    // altrimenti returna false.
    bool isPresentItemBstBI(Elem, const bstBI&);

    // Rimuove tutti gli elementi dal bstBI.
    void clearBstBI(bstBI&);

    /*
        +-----------------------------------+
        |           bstIt FUNZIONI          |
        +-----------------------------------+
        
        Nota: Per leggere le funzioni del bstBI andare a riga 38
    */ 

    // Crea un albero bstIt vuoto per i basic item.
    bstIt createEmptyBstIt();

    // Returna true se il bstIt è vuoto, altrimenti false.
    bool isEmptyBstIt(const bstIt&);
    
    // Aggiunge un basic item al bstIt se non lo trova, e returna true.
    // Nel caso in cui il basic item è già presente nella lista returna false.
    bool addItemBstIt(Elem, Elem*, size_t, bstIt&, const bstBI&);

    // Rimuove un basic item al bstIt se lo trova, e returna true.
    // Nel caso in cui il basic item non è presente nella lista returna false.
    bool removeItemBstIt(Elem, bstIt&);

    // Returna il basic item con valore passato come parametro se lo trova,
    // altrimenti returna emptyBstIt.
    Item getItemBstIt(Elem, const bstIt&);

    // Returna true se trova l'item con valore passato come parametro,
    // altrimenti returna false.
    bool isPresentItemBstIt(Elem, const bstIt&);

    // Rimuove tutti gli elementi dal bstIt.
    void clearBstIt(bstIt&);

}

#endif