#ifndef LINKED_LIST
#define LINKED_LIST

#include "stdafx.h"

template<class T>
class SortedDoublyLinkedList {
public:
    int size = 0;

    SortedDoublyLinkedList() { headEntry = new entry<T>(); finalEntry = new entry<T>(); }

    SortedDoublyLinkedList(entry<T>* root) { headEntry = root; }

    Iterator<entry<T>> begin() { return Iterator<entry<T>>(headEntry); }

    Iterator<entry<T>> end() { return Iterator<entry<T>>(nullptr); }

    std::vector<T> toVector() {
        std::vector<T> out;
        for (entry<T> entry : this)
            out.push_back(*entry.value);
        return out;
    }

    static SortedDoublyLinkedList<T> fromVector(std::vector<T> datain) {
        SortedDoublyLinkedList<T> out;
        for (T val : datain) {
            out.insert(new entry<T>(val));
        }
        return out;
    }

    int insert(entry<T> *value) {
        size++;
        if (!headEntry->isInstantiated()) {
            headEntry = value;
            finalEntry = value;
        }else {
            if (*value->value > *finalEntry->value){
                finalEntry->next = value;
                value->previous = finalEntry;
                finalEntry = value;
                return size;
            }
            entry<T> *currentEntry = headEntry;
            if (*headEntry->value > *value->value){
                headEntry->previous = value;
                value->next = headEntry;
                headEntry = value;
                return 0;
            }
            int i;
            for (i = 1; currentEntry->next != nullptr; i++) {
                if (*currentEntry->next->value > *value->value) {
                    value->previous = currentEntry;
                    value->next = currentEntry->next;
                    currentEntry->next = currentEntry->next->previous = value;
                    return i;
                } else {
                    currentEntry = currentEntry->next;
                }
            }
            currentEntry->next = value;
            value->previous = currentEntry;
            finalEntry = value;
            return i;
        }
        return 0;
    }

    SortedDoublyLinkedList<T> copy() {
        SortedDoublyLinkedList<T> out;
        entry<T>* currentEntry = headEntry;
        while (currentEntry != nullptr && currentEntry->isInstantiated()){
            out.insert(new entry<T>(currentEntry->value));
            currentEntry = currentEntry->next;
        }
        return out;
    }

    T getObject(T obj) {
        if (!couldHaveObject(obj))
            return T();
        entry<T>* currentEntry = headEntry;
        while (currentEntry != nullptr){
            if (*currentEntry->value == obj)
                return *currentEntry->value;
            currentEntry = currentEntry->next;
        }
        return T();
    }

    T* getReference(T obj) {
        if (!couldHaveObject(obj))
            return new T();
        entry<T>* currentEntry = headEntry;
        while (currentEntry != nullptr && currentEntry->isInstantiated()){
            if (*currentEntry->value == obj)
                return currentEntry->value;
            currentEntry = currentEntry->next;
        }
        return new T();
    }

    bool couldHaveObject(T obj) {
        if (!headEntry->isInstantiated())
            return false;
        if (finalEntry->isInstantiated() && obj > *finalEntry->value)
            return false;
        if (*headEntry->value > obj)
            return false;
        return true;
    }

    bool hasObject(T obj) {
        if (!couldHaveObject(obj))
            return false;
        else {
            entry<T> *currentEntry = headEntry;
            do {
                if (obj == *currentEntry->value) {
                    return true;
                }
            } while ((currentEntry = currentEntry->next) != nullptr);
            return false;
        }
    }

    T remove(T value) {
        if (!couldHaveObject(value))
            return T();
        if (*headEntry->value == value) {
            if (headEntry->next != nullptr) {
                headEntry = headEntry->next;
                headEntry->previous = nullptr;
            } else
                headEntry = finalEntry = new entry<T>();
            size--;
            return value;
        } else {
            entry<T> *currentEntry = headEntry;
            do {
                if (value == *currentEntry->value) {
                    removeEntry(currentEntry);
                    size--;
                    return *currentEntry->value;
                }
            } while ((currentEntry = currentEntry->next) != nullptr);
            return T();
        }
    }

    SortedDoublyLinkedList<T> subset(T max) {
        if (!couldHaveObject(max))
            return SortedDoublyLinkedList<T>();
        SortedDoublyLinkedList<T> out;
        entry<T> *currentEntry = headEntry;
        while (currentEntry != nullptr && currentEntry->isInstantiated() && *currentEntry->value <= max) {
            std::string s = max.toString();
            std::string sa = currentEntry->value->toString();
            out.insert(new entry<T>(currentEntry->value));
            currentEntry = currentEntry->next;
        }
        return out;
    }

    entry<T>* operator[](int windex) {
        if (windex >= 0 && windex < size) {
            if (windex == 0)
                return headEntry;
            entry<T> *currentEntry = headEntry;
            for (int i = 1; i <= windex; i++) {
                currentEntry = currentEntry->next;
            }
            return currentEntry;
        }
        return new entry<T>();
    }

    friend std::ostream &operator<<(std::ostream &out, const SortedDoublyLinkedList<T> &other) {
        entry<T> *currentEntry = other.headEntry;
        if (!currentEntry->isInstantiated() || currentEntry->value == nullptr)
#ifdef DEBUG_PRINTS
            out << "NO ENTRIES" << std::endl;
#else
            ;
#endif
        else {
            out << "0: " << *currentEntry->value;
            currentEntry = currentEntry->next;
            for (int i = 1; currentEntry != nullptr; i++) {
                out << '\n' << i << ": " << *currentEntry->value;
                currentEntry = currentEntry->next;
            }
        }
        return out;
    }

    void removeEntry(entry<T> *entry) {
        if (entry->previous != nullptr)
            entry->previous->next = entry->next;
        if (entry->next != nullptr)
            entry->next->previous = entry->previous;
        else
            finalEntry = entry->previous;
    }

    void join(SortedDoublyLinkedList<T> list) {
        for (entry<T> val : list)
            if (val.isInstantiated())
                insert(new entry<T>(val.value));
    }

    entry<T> *getHeadReference() {
        return headEntry;
    }

private:
    entry<T>* headEntry;
    entry<T>* finalEntry;
};

#endif
