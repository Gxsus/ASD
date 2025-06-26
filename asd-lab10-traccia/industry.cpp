// TO DO, vedi indicazioni in industry.h
#include "industry.h"
#include "binary-search-tree.h"
#include <iostream>

using namespace industry;
using namespace bst;

struct industry::st_Industry{
    bstBI basicItems;
    bstIt items;
};

struct BasicItemsNeeded{
    BasicItem item;
    int quantity;
    BasicItemsNeeded *next;
};

typedef BasicItemsNeeded* ListNeededBI;

Industry industry::createEmptyIndustry(){ 
    Industry ret = new st_Industry;
    ret -> basicItems = nullptr;
    ret -> items = nullptr;
    return ret; 
}

bool industry::insertBasicItem(Industry& indus, std::string name){ 
    return addItemBstBI(name, indus -> basicItems, indus -> items); 
}

bool industry::insertItem(Industry& indus, std::string name, std::string* components, size_t s){ 
    return addItemBstIt(name, components, s, indus -> items, indus -> basicItems); 
}

bool industry::isPresentItem(const Industry& indus, std::string name){ 
    return isPresentItemBstBI(name, indus -> basicItems)? true: isPresentItemBstIt(name, indus -> items); 
}

bool industry::removeItem(Industry& indus, std::string name){
    return removeItemBstBI(name, indus -> basicItems, indus -> items)? true: removeItemBstIt(name, indus -> items);
}

bool industry::addBasicItem(Industry& indus, std::string name, int v){
    BasicItem basicItem = getItemBstBI(name, indus -> basicItems);
    if(basicItem == getEmptyBI()) return false;
    
    basicItem -> quantity += v;
    if(basicItem -> quantity < 0) basicItem -> quantity = 0;
    return true;
}

bool industry::listNeed(const Industry& indus, std::string name, list::List& lres){
    Item item = getItemBstIt(name, indus -> items);
    if(item != getEmptyIt()){
        ListBI basicItems = item -> basicComponents;
        ListIt items = item -> components;
        while(basicItems != nullptr || items != nullptr){
            if(items == nullptr){
                addBack(basicItems -> item -> key, lres);
                basicItems = basicItems -> next;
            }else if(basicItems == nullptr){
                addBack(items -> item -> key, lres);
                items = items -> next;
            }else if(basicItems -> item -> key >= items -> item -> key){
                addBack(items -> item -> key, lres);
                items = items -> next;
            }else{
                addBack(basicItems -> item -> key, lres);
                basicItems = basicItems -> next;
            }    
        }
        return true;
    }
    return isPresentItemBstBI(name, indus -> basicItems);
}

void auxListNeededByComponent(const bstIt &bst, Item it, list::List& lres){
    if(isEmptyBstIt(bst)) return;
    auxListNeededByComponent(bst -> bst_left, it, lres);
    ListIt items = bst -> item -> components;

    while(items != nullptr){
        if(items -> item == it){ 
            addBack(bst -> item -> key, lres);
            break;
        }
        items = items -> next;
    }

    auxListNeededByComponent(bst -> bst_right, it, lres);
}

void auxListNeededByBasicComponent(const bstIt &bst, BasicItem it, list::List& lres){
    if(isEmptyBstIt(bst)) return;
    auxListNeededByBasicComponent(bst -> bst_left, it, lres);
    ListBI items = bst -> item -> basicComponents;

    while(items != nullptr){
        if(items -> item == it){ 
            addBack(bst -> item -> key, lres);
            break;
        }
        items = items -> next;
    }

    auxListNeededByBasicComponent(bst -> bst_right, it, lres);
}

bool industry::listNeededBy(const Industry& indus, std::string name, list::List& lres){
    Item it = getItemBstIt(name, indus -> items);

    if(it != getEmptyIt()){
        auxListNeededByComponent(indus -> items, it, lres);
        return true;
    }else{
        std::cout << "Here" << endl;
        BasicItem basicIt = getItemBstBI(name, indus -> basicItems);
        if(basicIt == getEmptyBI()) return false; 
        auxListNeededByBasicComponent(indus -> items, basicIt, lres);
        return true;
    }
}

void addInOrderList(List &lst, std::string name){
    std::string tmp;
    for(int i = 0; i < list::size(lst); i ++){
        tmp = list::get(i, lst);
        if(tmp > name){
            list::add(i, name, lst);
            return;
        }else if(tmp == name) return;
    }
    list::addBack(name, lst);
}

void auxlistNeededByChainBstIt(const bstIt& bst, const bstIt& root, Item it, list::List& lres){
    if(isEmptyBstIt(bst)) return;
    auxlistNeededByChainBstIt(bst -> bst_right, root, it, lres);
    
    ListIt list = bst -> item -> components;
    while(list != nullptr){
        if(list -> item == it){
            addInOrderList(lres, bst -> item -> key);
            auxlistNeededByChainBstIt(root, root, bst -> item, lres);
            break;
        }    
        list = list -> next;
    }

    auxlistNeededByChainBstIt(bst -> bst_left, root, it, lres);
}

void auxlistNeededByChainBstBI(const bstIt& bst, const bstIt& root, BasicItem it, list::List& lres){
    if(isEmptyBstIt(bst)) return;
    auxlistNeededByChainBstBI(bst -> bst_right, root, it, lres);
    
    ListBI list = bst -> item -> basicComponents;
    while(list != nullptr){
        if(list -> item == it){
            addInOrderList(lres, bst -> item -> key);
            auxlistNeededByChainBstIt(root, root, bst -> item, lres);
            break;
        }    
        list = list -> next;
    }

    auxlistNeededByChainBstBI(bst -> bst_left, root, it, lres);
}

bool industry::listNeededByChain(const Industry& indus, std::string name, list::List& lres){
    Item it = getItemBstIt(name, indus -> items);
    
    if(it != getEmptyIt()){
        auxlistNeededByChainBstIt(indus -> items, indus -> items, it, lres);
        return true;
    }else{
        BasicItem basicIt = getItemBstBI(name, indus -> basicItems);
        if(basicIt == getEmptyBI()) return false; 
        auxlistNeededByChainBstBI(indus -> items, indus -> items, basicIt, lres);
        return true;
    }
}

ListNeededBI getItemInListNeededBI(BasicItem it, const ListNeededBI &list){
    ListNeededBI tmp = list;

    while(tmp != nullptr){
        if(tmp -> item == it) return tmp;
        tmp = tmp -> next;
    }

    return nullptr;
}

void auxHowManyItem(Item it, ListNeededBI &list){
    ListIt components = it -> components;
    while(components != nullptr){
        auxHowManyItem(components -> item, list);
        components = components -> next;
    }

    ListNeededBI tmpList;
    ListBI basicComponents = it -> basicComponents;

    
    while(basicComponents != nullptr){
        tmpList = getItemInListNeededBI(basicComponents -> item, list);
        if(tmpList == nullptr){
            tmpList = new BasicItemsNeeded;
            tmpList -> item = basicComponents -> item;
            tmpList -> quantity = 1;
            tmpList -> next = list;
            list = tmpList;
        }else{
            tmpList -> quantity++;
        }
        basicComponents = basicComponents -> next;
    }

}

bool industry::howManyItem(const Industry& indus, std::string name, unsigned& res){
    Item it = getItemBstIt(name, indus -> items);
    int ris;

    if(it != getEmptyIt()){
        ListNeededBI list = nullptr, tmp;
        auxHowManyItem(it, list);

        if(list != nullptr){
            if(list -> quantity > list -> item -> quantity){
                res = 0;
                while(list != nullptr){
                    tmp = list;
                    list = list -> next;
                    delete tmp;
                }
                return true;
            }else ris = list -> item -> quantity / list -> quantity;
            list = list -> next;
        }

        while(list != nullptr){
            if(list -> quantity > list -> item -> quantity){
                res = 0;
                while(list != nullptr){
                    tmp = list;
                    list = list -> next;
                    delete tmp;
                }
                return true;
            }else if(list -> item -> quantity / list -> quantity < ris) ris = list -> quantity; 
            tmp = list;
            list = list -> next;
            delete tmp;
        }
        res = ris;
        return true;
    }else{
        BasicItem basicIt = getItemBstBI(name, indus -> basicItems);
        if(basicIt == getEmptyBI()){
            res = 0;
            return false; 
        }
        res = basicIt -> quantity;
        return true;
    }
}
