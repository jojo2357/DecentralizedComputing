#ifndef DECENTRALIZEDCOMPUTING_ENTRY_H
#define DECENTRALIZEDCOMPUTING_ENTRY_H

#include "stdafx.h"

template<class T>
class entry {
public:
    entry() { value = nullptr; instantiated = false; }
    entry(T* val) { value = val; instantiated = true; }
    entry(T* val, entry<T>* last) { value = val; previous = last; instantiated = true; }
    entry(T* val, entry<T>* mp_next, entry<T> *last) { value = val; previous = last; next = mp_next; instantiated = true; }
    T* value;
    entry<T>* previous = nullptr;
    entry<T>* next = nullptr;

    bool isInstantiated() { return instantiated; }

    entry<T> operator++() {
        return *next;
    }
private:
    bool instantiated;
};

#endif //DECENTRALIZEDCOMPUTING_ENTRY_H
