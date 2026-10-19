#ifndef DLIST_H
#define DLIST_H

#include <iostream>

template <class T>
class DLink{
public:
  T value;
  DLink<T>* previous;
  DLink<T>* next;

  DLink(T val) : value(val), previous(nullptr), next(nullptr) {}


};



#endif
