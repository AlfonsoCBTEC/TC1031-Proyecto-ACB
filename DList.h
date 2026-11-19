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

    DLink(T val);
};

template<class T>
DLink<T>::DLink(T val) : value(val), previous(nullptr), next(nullptr) {}

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
    DList();
    ~DList();

    bool empty() const;
    int length() const;
    DLink<T>* getHead() const;
    DLink<T>* getTail() const;

    /**
     * @brief Inserta elemento al final de la lista en O(1)
     */
    void addLast(T val);

    /**
     * @brief Busca algun expediente por matricula en O(n).
     * @return Si es que existe, un puntero al nodo, sino nullptr
     */
    DLink<T>* findByStudentId(const std::string& id) const;

    /**
     * @brief Elimina algun nodo especifico por matricula en O(n)
     */
    bool removeByStudentId(const std::string& id);

    /**
     * @brief Libera toda la memoria de la dlist en O(n).
     */
    void clear();
};

template <class T>
DList<T>::DList() : head(nullptr), tail(nullptr), size(0) {}

template <class T>
DList<T>::~DList(){
    clear();
}

template <class T>
bool DList<T>::empty() const { 
    return (head == nullptr); 
}

template <class T>
int DList<T>::length() const { 
    return size;
}

template <class T>
DLink<T>* DList<T>::getHead() const { 
    return head; 
}

template <class T>
DLink<T>* DList<T>::getTail() const { 
    return tail; 
}

template <class T>
void DList<T>::addLast(T val){
    DLink<T>* newLink = new DLink<T>(val);
    if(empty()){
        head = tail = newLink;
    } else {
        tail->next = newLink;
        newLink->previous = tail;
        tail = newLink;
    }
    size++;
}

template <class T>
DLink<T>* DList<T>::findByStudentId(const std::string& id) const{
    DLink<T>* curr = head;
    while (curr != nullptr){
        if (curr->value.getId() == id){
            return curr;
        }
        curr = curr -> next;
    }
    return nullptr;
}

template <class T>
bool DList<T>::removeByStudentId(const std::string& id){
    DLink<T>* target = findByStudentId(id);
    if(target == nullptr) return false;

    if(target == head) head = target->next;
    if(target == tail) tail = target->previous;
    if(target->previous != nullptr) target->previous->next = target->next;
    if(target->next != nullptr) target->next->previous = target->previous;

    delete target;
    size--;
    return true;
}

template <class T>
void DList<T>::clear(){
    DLink<T>* curr = head;
    while (curr!=nullptr){
        DLink<T>* nextNode = curr->next;
        delete curr;
        curr = nextNode;
    }
    head = tail = nullptr;
    size = 0;
}

#endif
