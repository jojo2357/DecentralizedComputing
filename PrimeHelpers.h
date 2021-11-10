#ifndef DECENTRALIZEDCOMPUTING_PRIMEHELPERS_H
#define DECENTRALIZEDCOMPUTING_PRIMEHELPERS_H

#include "stdafx.h"

class PrimesWaitingForPrime {
public :
    PrimesWaitingForPrime() = default;
    PrimesWaitingForPrime(BigInt num) { value = num; }

    BigInt value; //pendingPrime
    SortedDoublyLinkedList<BigInt> primesWaiting;

    bool operator==(const PrimesWaitingForPrime &other) const {
        return value == other.value;
    }

    bool operator>(const PrimesWaitingForPrime &other) const {
        return value > other.value;
    }

    friend std::ostream &operator<<(std::ostream &os, const PrimesWaitingForPrime &x) {
        os << "#" << x.value.toString() << " {" << x.primesWaiting << "}";
        return os;
    }

    bool operator==(const int &other) const {
        return false;
    }
};

class PendingPrimeAndCalculations {
public:
    PendingPrimeAndCalculations() = default;
    PendingPrimeAndCalculations(BigInt num) { value = num; }

    BigInt value; //primeCandidate
    SortedDoublyLinkedList<BigInt> primesWaiting;

    bool operator==(const PendingPrimeAndCalculations &other) const {
        return value == other.value;
    }

    bool operator>(const PendingPrimeAndCalculations &other) const {
        return value > other.value;
    }

    friend std::ostream &operator<<(std::ostream &os, const PendingPrimeAndCalculations &x) {
        os << "#" << x.value.toString() << " {" << x.primesWaiting << "}";
        return os;
    }

    bool operator==(const int &other) const {
        return false;
    }
};

#endif //DECENTRALIZEDCOMPUTING_PRIMEHELPERS_H
