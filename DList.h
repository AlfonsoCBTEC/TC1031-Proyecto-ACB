#ifndef DLIST_H
#define DLIST_H

#include <iostream>

template <class T> class DList;
class Sorts;

/**
 * @class DLink
 * @brief Nodos doblemente encandenados
 */

template <class T>
class DLink{
public:
    T value;
    DLink<T>* previous;
    DLink<T>* next;

    DLink(T val) : value(val), previous(nullptr), next(nullptr) {}
};

/**
 * class DList
 * @brief Estructura de la lista doblemente ligada
 */
template <class T>
class DList{
private:
    DLink<T>* head;
    DLink<T>* tail;
    int size;

    friend class Sorts;

public:
    DList() : head(nullptr), tail(nullptr), size(0) {}

    bool empty() const { return (head == nullptr); }
    int lenght() const { return size;}
    DLink<T>* getHead() const { return head; }
    DLink<T>* getTail() const { return tail; }
    
};

#endif
