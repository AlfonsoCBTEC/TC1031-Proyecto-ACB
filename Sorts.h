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

     static DLink<Expediente>* split(DLink<Expediente>* head){
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
public: 

    /**
     * @brief Ordena la DList por promedio descendente usando Insertion Sort en O(n^2) / O(n) mejor caso.
     */
    static void insertionSortPorPromedio(DList<Expediente>& lista){
        if(lista.head == nullptr || lista.head->next == nullptr) return;

        DLink<Expediente>* i = lista.head->next;
        while (i != nullptr){
            Expediente key = i->value;
            DLink<Expediente>* j = i->previous;

            while (j != nullptr && j->value.getPromedio() < key.getPromedio()){
                j->next->value = j->value;
                j = j->previous;
            }

            if(j==nullptr){
                lista.head->value = key;
            } else {
                j->next->value = key;
            }
            i = i->next;
        }

    }
};

#endif
