#ifndef DECENTRALIZEDCOMPUTING_PENDINGPRIMECALCULATION_H
#define DECENTRALIZEDCOMPUTING_PENDINGPRIMECALCULATION_H

#include "stdafx.h"

class PendingPrimeCalculation {
public:
    BigInt candidateValue;
    SortedDoublyLinkedList<BigInt> checksPendingResults;

    bool operator<(const PendingPrimeCalculation& other) const { return candidateValue < other.candidateValue; }
    bool operator>(const PendingPrimeCalculation& other) const { return candidateValue > other.candidateValue; }
};

#endif //DECENTRALIZEDCOMPUTING_PENDINGPRIMECALCULATION_H
