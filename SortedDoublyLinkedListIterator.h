#ifndef DECENTRALIZEDCOMPUTING_SortedDoublyLinkedListIteratorITERATOR_H
#define DECENTRALIZEDCOMPUTING_SortedDoublyLinkedListIteratorITERATOR_H

#include "stdafx.h"

template<class T>
struct Iterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T *;  // or also value_type*
    using reference = T &;  // or also value_type&

    Iterator(pointer ptr) : m_ptr(ptr) {}

    reference operator*() const { return *m_ptr; }

    pointer operator->() { return m_ptr; }

    // Prefix increment
    Iterator &operator++() {
        m_ptr = m_ptr->next;
        return *this;
    }

    // Postfix increment
    Iterator operator++(int) {
        Iterator tmp = *this;
        ++(*this);
        return tmp;
    }

    friend bool operator==(const Iterator &a, const Iterator &b) { return a.m_ptr == b.m_ptr; };

    friend bool operator!=(const Iterator &a, const Iterator &b) { return a.m_ptr != b.m_ptr; };

private:

    pointer m_ptr;
};

#endif //DECENTRALIZEDCOMPUTING_SortedDoublyLinkedListIteratorITERATOR_H
