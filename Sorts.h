#ifndef SORTS_H
#define SORTS_H

#include "DList.h"
#include "Expediente.h"

/**
 * @class Sorts
 * @brief Implementacion de los algoritmos de ordenamiento del proyecto sobre la lista doblemente ligada
 */


class Sorts{
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
