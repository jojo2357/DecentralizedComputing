#include "stdafx.h"


void PrimeNumberLibrary::calculatePrime(BigInt numIn) {
#ifdef DEBUG_PRINTS
    if (numIn == BigInt(11)){
        std::cout << "";
    }
    if (primes.hasObject(numIn)) {
        std::cout << "Thats a duplicate\n";
        return;
    } else if (!candidatePrimes.hasObject(numIn)) {
        std::cout << "Thats not a candidate\n";
        return;
    }
#else
        if (primes.hasObject(numIn) || !candidatePrimes.hasObject(numIn))
            return;
#endif
    else {
        SortedDoublyLinkedList<BigInt> out;
        BigInt sqrt = numIn.sqrt();
#ifdef DEBUG_PRINTS
        std::cout << "Testing " << numIn << " (" << sqrt << "): ";
#endif
        if (pendingPrimesAndCalcs.hasObject(PendingPrimeAndCalculations(numIn))) {
            out = pendingPrimesAndCalcs.getReference(PendingPrimeAndCalculations(numIn))->primesWaiting;
            for (entry<BigInt> entry : pendingPrimesAndCalcs.getReference(
                    PendingPrimeAndCalculations(numIn))->primesWaiting) {
                if (primes.hasObject(*entry.value))
                    out.remove(*entry.value);
            }
        } else {
            out = primes.subset(sqrt);
        }
        return calculatePrime(numIn, out);
        SortedDoublyLinkedList<BigInt> uncheckedPossiblePrimes = candidatePrimes.subset(sqrt);

        for (entry<BigInt> num : primes.subset(sqrt)) {
            if (!num.isInstantiated())
                continue;
            if (numIn % *num.value == BigInt::ZERO) {
                candidatePrimes.remove(numIn);
                std::cout << "composite to " << *num.value << "\n";
                if (numIn == BigInt(25)) {
                    std::cout << "";
                }
                return;
            } else {
                out.remove(*num.value);
                uncheckedPossiblePrimes.remove(*num.value);
            }
        }
        if (uncheckedPossiblePrimes.size > 0)
            out.join(uncheckedPossiblePrimes);
        else {
            candidatePrimes.remove(numIn);
            primes.insert(new entry<BigInt>(&numIn));
            std::cout << "prime!\n";
            return;
        }
        std::cout << "pending " << out << "\n";
        return;
    }
}

void
PrimeNumberLibrary::calculatePrime(BigInt numIn, SortedDoublyLinkedList<BigInt> calcsToDo) {
    BigInt sqrt = numIn.sqrt();
    SortedDoublyLinkedList<BigInt> uncheckedPossiblePrimes = candidatePrimes.subset(sqrt);

    for (entry<BigInt> num : calcsToDo.copy()) {
        if (!num.isInstantiated())
            continue;
        bool composite = numIn % *num.value == BigInt::ZERO;
#ifdef DEBUG_PRINTS
        if (numIn == BigInt(901) && composite){
            auto holder = pendingPrimesAndCalcs.getReference(PendingPrimeAndCalculations(numIn));
            std::cout << "";
        }
        if (numIn == BigInt(25) && composite){
            auto holder = pendingPrimesAndCalcs.getReference(PendingPrimeAndCalculations(numIn));
            std::cout << "";
        }
#endif
        if (primesWaitingForPrimes.hasObject(PrimesWaitingForPrime(numIn)))
            primesWaitingForPrimes.getReference(PrimesWaitingForPrime(numIn))->primesWaiting.remove(*num.value);
        if (pendingPrimesAndCalcs.hasObject(PendingPrimeAndCalculations(*num.value)))
            pendingPrimesAndCalcs.getReference(PendingPrimeAndCalculations(*num.value))->primesWaiting.remove(numIn);
        if (composite) {
            candidatePrimes.remove(numIn);
#ifdef DEBUG_PRINTS
            std::cout << "composite to " << num.value << "\n";
#endif
            {
                entry<PrimesWaitingForPrime> *anEntry = primesWaitingForPrimes.getHeadReference();
                for (int i = 0; anEntry != nullptr && anEntry->isInstantiated() && i < primesWaitingForPrimes.size; i++) {
                    /*PrimesWaitingForPrime pp = primesWaitingForPrimes.remove(*anEntry->value);
                    pp.primesWaiting.remove(numIn);
                    primesWaitingForPrimes.insert(new entry<PrimesWaitingForPrime>(pp));*/
                    anEntry->value->primesWaiting.remove(numIn);
                    anEntry = anEntry->next;
                }
            }
            /*for (entry<PrimesWaitingForPrime> entry : primesWaitingForPrimes) {
                entry.value.primesWaiting.remove(numIn);
            }*/
            //doesnt run
            if (primesWaitingForPrimes.getReference(PrimesWaitingForPrime(numIn))->primesWaiting.size > 0)
                for (entry<BigInt> entry : primesWaitingForPrimes.getReference(PrimesWaitingForPrime(numIn))->primesWaiting) {
                    if (!pendingPrimesAndCalcs.hasObject(*entry.value))
                        continue;
#ifdef DEBUG_PRINTS
                    auto thing = pendingPrimesAndCalcs.getReference(*entry.value);
                    if (numIn == BigInt(901)){
                        std::cout << "";
                    }
#endif
                    pendingPrimesAndCalcs.getReference(*entry.value)->primesWaiting.remove(numIn);
                    if (pendingPrimesAndCalcs.getReference(*entry.value)->primesWaiting.size == 0)
                        addPrime(*entry.value);
                }
            primesWaitingForPrimes.remove(PrimesWaitingForPrime(numIn));
            pendingPrimesAndCalcs.remove(PendingPrimeAndCalculations(numIn));
            /*if (numIn == BigInt(901)){
                auto holder = pendingPrimesAndCalcs.getReference(PendingPrimeAndCalculations(numIn));
                auto other = primesWaitingForPrimes.getReference(PrimesWaitingForPrime(numIn));
                std::cout << "";
            }
            reportFinishingCalc(numIn, num.value);
            pendingPrimesAndCalcs.remove(numIn);
            if (primesWaitingForPrimes.getReference(PrimesWaitingForPrime(numIn))->primesWaiting.size > 0)
                for (entry<BigInt> entry : primesWaitingForPrimes.getReference(PrimesWaitingForPrime(numIn))->primesWaiting) {
                    auto thing = pendingPrimesAndCalcs.getReference(entry.value);
                    if (numIn == BigInt(901)){
                        std::cout << "";
                    }
                    pendingPrimesAndCalcs.getReference(entry.value)->primesWaiting.remove(numIn);
                    if (pendingPrimesAndCalcs.getReference(entry.value)->primesWaiting.size == 0)
                        addPrime(entry.value);
                }*/

#ifdef DEBUG_PRINTS
            if (numIn == BigInt(901) && composite){
                auto holder = pendingPrimesAndCalcs.hasObject(PendingPrimeAndCalculations(numIn));
                auto other = false;
                for (entry<PrimesWaitingForPrime> pfp : primesWaitingForPrimes) {
                    if (pfp.value->primesWaiting.hasObject(numIn))
                        std::cout << "";
                }
                std::cout << "";
            }
#endif
            return;
        } else {
            calcsToDo.remove(*num.value);
            reportFinishingCalc(numIn, *num.value);
            //uncheckedPossiblePrimes.remove(*num.value);
        }
    }
    if (uncheckedPossiblePrimes.size > 0) {
        calcsToDo.join(uncheckedPossiblePrimes);
        PendingPrimeAndCalculations* pending = new PendingPrimeAndCalculations(numIn);
        if (!pendingPrimesAndCalcs.hasObject(*pending)) {
#ifdef DEBUG_PRINTS
            if (numIn == BigInt(901)){
                std::cout << "";
            }
#endif
            pending->primesWaiting = calcsToDo;
            pendingPrimesAndCalcs.insert(new entry<PendingPrimeAndCalculations>(pending));
        }
        for (entry<BigInt> num : calcsToDo) {
            if (!primesWaitingForPrimes.hasObject(PrimesWaitingForPrime(*num.value)))
                primesWaitingForPrimes.insert(new entry<PrimesWaitingForPrime>(new PrimesWaitingForPrime(*num.value)));
            if (!primesWaitingForPrimes.getReference(PrimesWaitingForPrime(*num.value))->primesWaiting.hasObject(numIn))
                primesWaitingForPrimes.getReference(PrimesWaitingForPrime(*num.value))->primesWaiting.insert(
                        new entry<BigInt>(new BigInt(numIn)));
        }
#ifdef DEBUG_PRINTS
        std::cout << "pending " << calcsToDo << "\n";
#endif
        return;
    } else {
        addPrime(numIn);
#ifdef DEBUG_PRINTS
        std::cout << "prime!\n";
#endif
        return;
    }
}

void PrimeNumberLibrary::reportFinishingCalc(BigInt pendingPrimeNumber, BigInt completedCalulation) {
#ifdef DEBUG_PRINTS
    if (pendingPrimeNumber == BigInt(901)){
        auto holder = pendingPrimesAndCalcs.getReference(PendingPrimeAndCalculations(pendingPrimeNumber));
        std::cout << "";
    }
#endif
    if (primesWaitingForPrimes.hasObject(PrimesWaitingForPrime(completedCalulation))) {
        primesWaitingForPrimes.getReference(PrimesWaitingForPrime(completedCalulation))->primesWaiting.remove(
                pendingPrimeNumber);
        if (primesWaitingForPrimes.getReference(PrimesWaitingForPrime(completedCalulation))->primesWaiting.size == 0)
            primesWaitingForPrimes.remove(PrimesWaitingForPrime(completedCalulation));
    }
    if (pendingPrimesAndCalcs.hasObject(PendingPrimeAndCalculations(pendingPrimeNumber))) {
        pendingPrimesAndCalcs.getReference(PendingPrimeAndCalculations(pendingPrimeNumber))->primesWaiting.remove(
                completedCalulation);
        if (pendingPrimesAndCalcs.getReference(PendingPrimeAndCalculations(pendingPrimeNumber))->primesWaiting.size ==
            0)
            pendingPrimesAndCalcs.remove(PendingPrimeAndCalculations(pendingPrimeNumber));
    }
}

void PrimeNumberLibrary::doStuffWithNewlyPrimed() {
    if (newlyPrimed.size > 0) {
        BigInt newlyPrimedNumber = *newlyPrimed[0]->value;
#ifdef DEBUG_PRINTS
        if (newlyPrimedNumber == BigInt(17)){
            auto arrr = primesWaitingForPrimes.getReference(
                    PrimesWaitingForPrime(newlyPrimedNumber));
            auto arrr1 = primesWaitingForPrimes.getReference(
                    PrimesWaitingForPrime(newlyPrimedNumber))->primesWaiting.hasObject(BigInt(901));
            std::cout << "";
        }
#endif
        if (primesWaitingForPrimes.getReference(
                PrimesWaitingForPrime(newlyPrimedNumber))->primesWaiting.size > 0) {
            for (entry<BigInt> testNum : primesWaitingForPrimes.getReference(
                    PrimesWaitingForPrime(newlyPrimedNumber))->primesWaiting.copy()) {
#ifdef DEBUG_PRINTS
                std::cout << "Restest " << *testNum.value;
#endif
                bool knowinglyComposite = *testNum.value % newlyPrimedNumber == BigInt::ZERO;
#ifdef DEBUG_PRINTS
                if (*testNum.value == BigInt(901)){
                    std::cout << "";
                }
#endif
                if (knowinglyComposite) {
#ifdef DEBUG_PRINTS
                    std::cout << " composite to " << newlyPrimedNumber;
#endif
                    //reportFinishingCalc(testNum.value, newlyPrimedNumber);
                    candidatePrimes.remove(*testNum.value);
                    pendingPrimesAndCalcs.remove(PendingPrimeAndCalculations(*testNum.value));
                    {
                        entry<PrimesWaitingForPrime> *entry = primesWaitingForPrimes.getHeadReference();
                        for (int i = 0; entry != nullptr && entry->isInstantiated() && i < primesWaitingForPrimes.size; i++) {
                            entry->value->primesWaiting.remove(*testNum.value);
                            entry = entry->next;
                        }
                    }
#ifdef DEBUG_PRINTS
                    if (*testNum.value == BigInt(25)) {
                        std::cout << "";
                    }
#endif
                    if (primesWaitingForPrimes.getReference(PrimesWaitingForPrime(*testNum.value))->primesWaiting.size > 0) {
                        for (entry <BigInt> entry : primesWaitingForPrimes.getReference(
                                PrimesWaitingForPrime(*testNum.value))->primesWaiting) {
                            if (!pendingPrimesAndCalcs.hasObject(*entry.value))
                                continue;
#ifdef DEBUG_PRINTS
                            auto thing = pendingPrimesAndCalcs.getReference(*entry.value);
                            if (*testNum.value == BigInt(901)) {
                                std::cout << "";
                            }
#endif
                            pendingPrimesAndCalcs.getReference(*entry.value)->primesWaiting.remove(*testNum.value);
                            if (pendingPrimesAndCalcs.getReference(*entry.value)->primesWaiting.size == 0)
                                addPrime(*entry.value);
                        }
                    }
                    pendingPrimesAndCalcs.remove(PendingPrimeAndCalculations(*testNum.value));
                    primesWaitingForPrimes.remove(PrimesWaitingForPrime(*testNum.value));
                } else {
#ifdef DEBUG_PRINTS
                    auto thing = pendingPrimesAndCalcs.getReference(*testNum.value);
                    if (*testNum.value == BigInt(901)) {
                        std::cout << "";
                    }
#endif
                    if (pendingPrimesAndCalcs.getReference(
                            PendingPrimeAndCalculations(*testNum.value))->primesWaiting.size <= 1) {
#ifdef DEBUG_PRINTS
                        std::cout << " is prime!";
#endif
                        addPrime(*testNum.value);
                        pendingPrimesAndCalcs.remove(PendingPrimeAndCalculations(*testNum.value));
                    } else {
                        pendingPrimesAndCalcs.getReference(
                                PendingPrimeAndCalculations(*testNum.value))->primesWaiting.remove(newlyPrimedNumber);
#ifdef DEBUG_PRINTS
                        std::cout << " still needs " << pendingPrimesAndCalcs.getReference(
                                PendingPrimeAndCalculations(*testNum.value))->primesWaiting << " to resolve";
#endif
                    }
                }
#ifdef DEBUG_PRINTS
                std::cout << "\n";
#endif
            }
            primesWaitingForPrimes.remove(PrimesWaitingForPrime(newlyPrimedNumber));
        }
        newlyPrimed.remove(newlyPrimedNumber);
    }
}
