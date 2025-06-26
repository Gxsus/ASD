#include "binary-search-tree.h"
#include <iostream>

using namespace bst;

bstBI emptyBstBI = nullptr;
bstIt emptyBstIt = nullptr;
BasicItem emptyBI = nullptr;
Item emptyIt = nullptr;

bstBI bst::getEmptyBstBI(){ return emptyBstBI; }
bstIt bst::getEmptyBstIt(){ return emptyBstIt; }
BasicItem bst::getEmptyBI(){ return emptyBI; }
Item bst::getEmptyIt(){ return emptyIt; }

//FUNZIONI AUSILIARIE PER removeItemBstBI e removeItemBstIt
void clearComponentList(Item &it){
    ListBI basicItems = it -> basicComponents, prevB;
    ListIt items = it -> components, prevI;

    while(basicItems != nullptr){
        prevB = basicItems;
        basicItems = basicItems -> next;
        delete prevB;
    }

    while(items != nullptr){
        prevI = items;
        items = items -> next;
        delete prevI;
    }
}

BasicItem deleteMinBstBI(bstBI &bst){
    if(isEmptyBstBI(bst)) return emptyBI;

    while(!isEmptyBstBI(bst -> bst_left)) bst = bst -> bst_left; 
    BasicItem ret = bst -> item;
    delete bst;
    bst = bst -> bst_right;
    return ret;
}

Item deleteMinBstIt(bstIt &bst){
    if(isEmptyBstIt(bst)) return emptyIt;

    while(!isEmptyBstIt(bst -> bst_left)) bst = bst -> bst_left; 
    Item ret = bst -> item;
    delete bst;
    bst = bst -> bst_right;
    return ret;
}

void deleteDependentComponentsIt(Item it, bstIt &bst, bstIt &root){
    if(isEmptyBstIt(bst)) return;
    ListIt list = bst -> item -> components;
    while(list != nullptr){
        if(list -> item == it){
            cout << bst -> item -> key << endl;
            deleteDependentComponentsIt(bst -> item, root, root);
            delete bst -> item;
            if(isEmptyBstIt(bst -> bst_right)){
                bstIt tmp = bst -> bst_right;
                delete bst;
                bst = tmp;
            }else bst -> item = deleteMinBstIt(bst -> bst_right);
            return deleteDependentComponentsIt(it, bst, root);
        }
        list = list -> next;
    }
    deleteDependentComponentsIt(it, bst -> bst_left, root); 
    deleteDependentComponentsIt(it, bst -> bst_right, root);
}

void deleteDependentComponentsBI(BasicItem it, bstIt &bst, bstIt &root){
    if(isEmptyBstIt(bst)) return;
    ListBI list = bst -> item -> basicComponents;
    while(list != nullptr){
        if(list -> item == it){
            cout << bst -> item -> key << endl;
            deleteDependentComponentsIt(bst -> item, bst, root);
            delete bst -> item;
            if(isEmptyBstIt(bst -> bst_right)){
                bstIt tmp = bst -> bst_right;
                delete bst;
                bst = tmp;
            }else bst -> item = deleteMinBstIt(bst -> bst_right);
            return deleteDependentComponentsBI(it, bst, root);
        }
        list = list -> next;
    }
    deleteDependentComponentsBI(it, bst -> bst_left, root); 
    deleteDependentComponentsBI(it, bst -> bst_right, root);
}

bool auxRemoveItemBstIt(Elem el, bstIt &bst, bstIt &root){
    if(isEmptyBstIt(bst)) return false;

    if(bst -> item -> key == el){
        Item tmp = bst -> item;
        if(isEmptyBstIt(bst -> bst_right)){
            bstIt tmp = bst -> bst_right;
            delete bst;
            bst = tmp;
        }else bst -> item = deleteMinBstIt(bst -> bst_right);
        deleteDependentComponentsIt(tmp, bst, root);
        clearComponentList(tmp);
        delete tmp;
        return true;
    }else if(bst -> item -> key < el) return auxRemoveItemBstIt(el, bst -> bst_right, root);
    else return auxRemoveItemBstIt(el, bst -> bst_left, root);
}

// FUNZIONE AUSILIARIA PER clearBstIt 
void auxClearBstBI(bstBI &bst){
    if(isEmptyBstBI(bst)) return;

    clearBstBI(bst -> bst_right);
    clearBstBI(bst -> bst_left);
    delete bst;
}

// FUNZIONE AUSILIARIA PER clearBstIt 
void auxClearBstIt(bstIt &bst){
    if(isEmptyBstIt(bst)) return;

    clearBstIt(bst -> bst_right);
    clearBstIt(bst -> bst_left);
    delete bst;
}

// FUNZIONI AUSILIARIE PER addItemBstIt
// Returna true se e solo se tutti i componenti sono stati trovati, false altrimenti.
bool addComponents(Item &it, Elem *components, size_t &len, const bstIt &bst){
    if(isEmptyBstIt(bst)) return false;
    if(addComponents(it, components, len, bst -> bst_right)) return true;
    ListIt tmp;

    for(size_t i = 0; i < len; i++)
        if(bst -> item -> key == components[i]){
            len--;
            components[i] = components[len];
            tmp = it -> components;
            it -> components = new AdjListIt;
            it -> components -> item = bst -> item;
            it -> components -> next = tmp;
            i--;
            break;
        }
    if(len == 0) return true;
    return addComponents(it, components, len, bst -> bst_left);
}

// Returna true se e solo se tutti i componenti sono stati trovati, false altrimenti.
bool addBasicComponents(Item &it, Elem *components, size_t &len, const bstBI &bst){
    if(isEmptyBstBI(bst)) return false;
    if(addBasicComponents(it, components, len, bst -> bst_right)) return true;
    ListBI tmp;
    
    for(size_t i = 0; i < len; i++)
        if(bst -> item -> key == components[i]){
            len--;
            components[i] = components[len];
            tmp = new AdjListBI;
            tmp -> item = bst -> item;
            tmp -> next = it -> basicComponents;
            it -> basicComponents = tmp;
            i--;
            break;
        }
    if(len == 0) return true;
    return addBasicComponents(it, components, len, bst -> bst_left);
}

bool auxAddItemBstIt(Elem el, Elem *components, size_t &len, bstIt &rootBstIt, bstIt &bstIt, const bstBI &bstBI){
    if(isEmptyBstIt(bstIt)){
        bstIt = new nodeIt;
        bstIt -> item = new It;
        bstIt -> item -> key = el;
        bstIt -> item -> basicComponents = nullptr;
        bstIt -> item -> components = nullptr;
        bstIt -> bst_left = emptyBstIt;
        bstIt -> bst_right = emptyBstIt;
        Elem cp[len];
        for(size_t i = 0; i < len; i++) cp[i] = components[i];
        if(addComponents(bstIt -> item, components, len, rootBstIt)){}
        else if(addBasicComponents(bstIt -> item, components, len, bstBI)){}
        else{
            clearComponentList(bstIt -> item);
            delete bstIt -> item;
            delete bstIt;
            bstIt = emptyBstIt;
            return false;
        }
        
        return true;
    }

    if(bstIt -> item -> key < el) return auxAddItemBstIt(el, components, len, rootBstIt, bstIt -> bst_right, bstBI);
    if(bstIt -> item -> key > el) return auxAddItemBstIt(el, components, len, rootBstIt, bstIt -> bst_left, bstBI);
    return false;
}

/*
    +-------------------------------------------+
    |           bstBI IMPLEMENTAZIONE           |
    +-------------------------------------------+

    Nota: Per leggere le funzioni del bstIt andare a riga 106
*/ 

bstBI bst::createEmptyBstBI(){ return emptyBstBI; }

bool bst::isEmptyBstBI(const bstBI &bst){ return bst == emptyBstBI; }

bool auxAddItemBstBI(Elem el, bstBI &bst){
    if(isEmptyBstBI(bst)){
        bst = new nodeBI;
        bst -> item = new BIt;
        bst -> item -> key = el;
        bst -> item -> quantity = 0;
        bst -> bst_left = emptyBstBI;
        bst -> bst_right = emptyBstBI;
        return true;
    }
    
    if(bst -> item -> key < el) return auxAddItemBstBI(el, bst -> bst_right);
    if(bst -> item -> key > el) return auxAddItemBstBI(el, bst -> bst_left);
    return false;
}
    
bool bst::addItemBstBI(Elem el, bstBI &bst, const bstIt &bstI){
    if(isPresentItemBstIt(el, bstI)) return false;    
    return auxAddItemBstBI(el, bst);
}

bool bst::removeItemBstBI(Elem el, bstBI &bstBIt, bstIt &bstIt){
    if(isEmptyBstBI(bstBIt)) return false;

    if(bstBIt -> item -> key == el){
        deleteDependentComponentsBI(bstBIt -> item, bstIt, bstIt);
        if(isEmptyBstBI(bstBIt -> bst_right)){
            bstBI tmp = bstBIt -> bst_right;
            delete bstBIt;
            bstBIt = tmp;
        }else bstBIt -> item = deleteMinBstBI(bstBIt -> bst_right);
        return true;
    }else if(bstBIt -> item -> key < el) return removeItemBstBI(el, bstBIt -> bst_right, bstIt);
    else return removeItemBstBI(el, bstBIt -> bst_left, bstIt);
}

BasicItem bst::getItemBstBI(Elem el, const bstBI &bst){
    if(isEmptyBstBI(bst)) return emptyBI;

    if(bst -> item -> key == el) return bst -> item;
    else if(bst -> item -> key < el) return getItemBstBI(el, bst -> bst_right);
    else return getItemBstBI(el, bst -> bst_left);
}

bool bst::isPresentItemBstBI(Elem el, const bstBI &bst){
    if(isEmptyBstBI(bst)) return false;

    if(bst -> item -> key == el) return true;
    else if(bst -> item -> key < el) return isPresentItemBstBI(el, bst -> bst_right);
    else return isPresentItemBstBI(el, bst -> bst_left);
}

void bst::clearBstBI(bstBI &bst){
    auxClearBstBI(bst);
    bst = nullptr;
}

/*
    +-------------------------------------------+
    |           bstIt IMPLEMENTAZIONE           |
    +-------------------------------------------+

    Nota: Per leggere le funzioni del bstBI andare a riga 45
*/ 

bstIt bst::createEmptyBstIt(){ return emptyBstIt; }

bool bst::isEmptyBstIt(const bstIt &bst){ return bst == emptyBstIt; }

bool bst::addItemBstIt(Elem el, Elem *components, size_t len, bstIt &bstIt, const bstBI &bstBI){
    if(len == 0 || isPresentItemBstBI(el, bstBI)) return false;
    return auxAddItemBstIt(el, components, len, bstIt, bstIt, bstBI);
}

bool bst::removeItemBstIt(Elem el, bstIt &bst){
    return auxRemoveItemBstIt(el, bst, bst);
}

Item bst::getItemBstIt(Elem el, const bstIt &bst){
    if(isEmptyBstIt(bst)) return emptyIt;

    if(bst -> item -> key == el) return bst -> item;
    else if(bst -> item -> key < el) return getItemBstIt(el, bst -> bst_right);
    else return getItemBstIt(el, bst -> bst_left);
}

bool bst::isPresentItemBstIt(Elem el, const bstIt &bst){
    if(isEmptyBstIt(bst)) return false;

    if(bst -> item -> key == el) return true;
    else if(bst -> item -> key < el) return isPresentItemBstIt(el, bst -> bst_right);
    else return isPresentItemBstIt(el, bst -> bst_left);
}

void bst::clearBstIt(bstIt &bst){
    auxClearBstIt(bst);
    bst = nullptr;
}