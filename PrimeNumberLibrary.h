#ifndef PNL
#define PNL

#include "stdafx.h"

class PrimeNumberLibrary {
public:
    PrimeNumberLibrary(BigInt limit) {
        primes.insert(new entry<BigInt>(&BigInt::TWO));
        primes.insert(new entry<BigInt>(&BigInt::THREE));
        for (BigInt i = BigInt::SIX; i < limit; i = i + BigInt::SIX) {
            candidatePrimes.insert(new entry<BigInt>(new BigInt(i - 1)));
            candidatePrimes.insert(new entry<BigInt>(new BigInt(i + 1)));
        }
    }

    void addPrime(BigInt prime) {
        if (prime == BigInt(901)) {
            std::cout << "";
        }
        if (primes.hasObject(prime))
            return;
        candidatePrimes.remove(prime);
        primes.insert(new entry<BigInt>(new BigInt(prime)));
        newlyPrimed.insert(new entry<BigInt>(new BigInt(prime)));
    }

    void calculatePrime(BigInt numIn);
    void calculatePrime(BigInt numIn, SortedDoublyLinkedList<BigInt> calcsToDo);
    SortedDoublyLinkedList<BigInt> candidatePrimes;
    SortedDoublyLinkedList<BigInt> primes;
    SortedDoublyLinkedList<BigInt> newlyPrimed;
    SortedDoublyLinkedList<PrimesWaitingForPrime> primesWaitingForPrimes;
    SortedDoublyLinkedList<PendingPrimeAndCalculations> pendingPrimesAndCalcs;
    void doStuffWithNewlyPrimed();
private:
    void reportFinishingCalc(BigInt pendingPrimeNumber, BigInt completedCalulation);
};

#endif
