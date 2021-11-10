#include "stdafx.h"

/*template<class T>
int SortedDoublyLinkedList<T>::insert(T value) {
    if (headEntry == NULL)
        headEntry = entry<T>(value);
    else {
        entry<T>* currentEntry = headEntry;
        int i;
        for (i = 1; currentEntry->next != NULL; i++) {
            if (currentEntry->next->value > value) {
                currentEntry->next = currentEntry->next->previous = &entry<T>(value, currentEntry->next, currentEntry);
                return i;
            } else {
                currentEntry = currentEntry->next;
            }
        }
        currentEntry->next = &entry<T>(value, currentEntry);
        return i;
    }
    return 0;
}*/

/*template<class T>
void SortedDoublyLinkedList<T>::display() {
    entry<T>* currentEntry = headEntry;
    if (currentEntry == nullptr)
#ifdef DEBUG_PRINTS
        std:cout << "NO ENTRIES" << endl;
#else
        ;
#endif
    else {
        for (int i = 0; currentEntry != NULL; i++) {
            cout << i << ": " << currentEntry->value << "\n";
            currentEntry = currentEntry->next;
        }
    }
}*/

/*template<class T>
std::ostream &operator<<(std::ostream &out, const SortedDoublyLinkedList<T> &other) {
    entry<T>* currentEntry = other.headEntry;
    if (currentEntry == nullptr)
#ifdef DEBUG_PRINTS
        out << "NO ENTRIES" << endl;
#else
    ;
#endif
    else {
        for (int i = 0; currentEntry != NULL; i++) {
            out << i << ": " << currentEntry->value << "\n";
            currentEntry = currentEntry->next;
        }
    }
    return out;
}*/
