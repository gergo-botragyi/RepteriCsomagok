#ifndef DINARRAY_CPP
#define DINARRAY_CPP

#include "list.h"
#include "bfsData.h"
#include "junction.h"

template <>
listItem<bfsData>* List<bfsData>::findDataByChar(char name)const{
    listItem<bfsData>* ret = arr;
    while(ret != nullptr && ret->item.getJunction() != name){
        ret = ret->next;
    }
    return ret;
}

template <>
listItem<Junction>* List<Junction>::findJunctionByChar(char name)const{
    listItem<Junction>* ret = arr;
    while(ret != nullptr && ret->item.getName() != name){
        ret = ret->next;
    }
    return ret;
}

#endif