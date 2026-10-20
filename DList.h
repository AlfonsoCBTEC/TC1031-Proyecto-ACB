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

    ~DList(){
        clear();
    }

    bool empty() const { return (head == nullptr); }
    int length() const { return size;}
    DLink<T>* getHead() const { return head; }
    DLink<T>* getTail() const { return tail; }

    /**
     * @brief Inserta elemento al final de la lista en O(1)
     */
    void addLast(T val){
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

    /**
     * @brief Busca algun expediente por matricula en O(n).
     * @return Si es que existe, un puntero al nodo, sino nullptr
     */
    DLink<T>* findByMatricula(const std::string& mat) const{
        DLink<T>* curr = head;
        while (curr != nullptr){
            if (curr->value.getMatricula() == mat){
                return curr;
            }
            curr = curr -> next;
        }
        return nullptr;
    }

    /**
     * @brief Elimina algun nodo especifico por matricula en O(n)
     */
    bool removeByMatricula(const std::string& mat){
        DLink<T>* target = findByMatricula(mat);
        if(target == nullptr) return false;

        if(target == head) head = target->next;
        if(target == tail) tail = target->previous;
        if(target->previous != nullptr) target->previous->next = target->next;
        if(target->next != nullptr) target->next->previous = target->previous;

        delete target;
        size--;
        return true;
    }

    /**
     * @brief Libera toda la memoria de la dlist en O(n).
     */
    void clear(){
        DLink<T>* curr = head;
        while (curr!=nullptr){
            DLink<T>* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
        head = tail = nullptr;
        size = 0;
    }

};

#endif
