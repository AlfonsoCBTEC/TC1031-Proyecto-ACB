#ifndef SORTS_H
#define SORTS_H

#include "DList.h"
#include "Expediente.h"

/**
 * @class Sorts
 * @brief Implementacion de los algoritmos de ordenamiento del proyecto sobre la lista doblemente ligada
 */


class Sorts{
private:
    /**
     * @brief Aqui se divide la dlist en 2 mitades usando punteros slow y fast en O(n), para luego implementar merge sort.
     */
    static DLink<Expediente>* split(DLink<Expediente>* head);

    /**
     * @brief Fusiona 2 sublistas doblemente ligadas en orden alfabetico por Nombre.
     */
    static DLink<Expediente>* mergeByName(DLink<Expediente>* first, DLink<Expediente>* second);

    /**
     * @brief Funcion recursiva de Merge Sort sobre los enlaces de los nodos.
     */
    static DLink<Expediente>* mergeSortRec(DLink<Expediente>* node);

public:
    /**
     * @brief Funcion recursiva de Merge Sort sobre los enlaces de los nodos.
     */
    static void mergeSortByName(DList<Expediente>& list);

    /**
     * @brief Funcion recursiva de Merge Sort sobre los enlaces de los nodos.
     */
    static void insertionSortByAverage(DList<Expediente>& list);
};

DLink<Expediente>* Sorts::split(DLink<Expediente>* head){
    DLink<Expediente>* fast = head;
    DLink<Expediente>* slow = head;
    while(fast->next != nullptr && fast->next->next != nullptr){
        fast = fast->next->next;
        slow = slow->next;
    }
    DLink<Expediente>* temp = slow->next;
    slow->next = nullptr;
    if(temp != nullptr){
        temp->previous = nullptr;
    }
    return temp;
}

DLink<Expediente>* Sorts::mergeByName(DLink<Expediente>* first, DLink<Expediente>* second) {
    if (first == nullptr) return second;
    if (second == nullptr) return first;

    if (first->value.getName() <= second->value.getName()) {
        first->next = mergeByName(first->next, second);
        if (first->next != nullptr) first->next->previous = first;
        first->previous = nullptr;
        return first;
    } else{
        second->next = mergeByName(first, second->next);
        if (second->next != nullptr) second->next->previous = second;
        second->previous = nullptr;
        return second;
    }
}

DLink<Expediente>* Sorts::mergeSortRec(DLink<Expediente>* node){
    if(node == nullptr || node->next == nullptr){
        return node;
    }
    DLink<Expediente>* second = split(node);
    node = mergeSortRec(node);
    second = mergeSortRec(second);

    return mergeByName(node, second);
}

void Sorts::mergeSortByName(DList<Expediente>& list) {
    if(list.head == nullptr || list.head->next == nullptr) return;

    list.head = mergeSortRec(list.head);

    //Aqui finalmente actualice el tail despues de todo el cambio de enlaces
    DLink<Expediente>* curr = list.head;
    while(curr->next != nullptr){
        curr = curr->next;
    }
    list.tail = curr;
}

void Sorts::insertionSortByAverage(DList<Expediente>& list){
    if(list.head == nullptr || list.head->next == nullptr) return;

    DLink<Expediente>* i = list.head->next;
    while (i != nullptr){
        Expediente key = i->value;
        DLink<Expediente>* j = i->previous;

        while (j != nullptr && j->value.getAverage() < key.getAverage()){
            j->next->value = j->value;
            j = j->previous;
        }

        if(j==nullptr){
            list.head->value = key;
        } else {
            j->next->value = key;
        }
        i = i->next;
    }
}

#endif
