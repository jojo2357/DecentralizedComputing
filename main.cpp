#include "stdafx.h"

int main() {
    struct timeval time_now{};
    gettimeofday(&time_now, nullptr);
    time_t msecs_time = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);

    PrimeNumberLibrary pnl(BigInt(10000));
    //optimal order
    /*for (int i = 0; i < 10000; i++) {
        pnl.doStuffWithNewlyPrimed();
        pnl.calculatePrime(BigInt(i));
    }*/
    //sub-optimal bogorder
    for (int i = 100; i > 0; i--) {
        pnl.doStuffWithNewlyPrimed();
        pnl.calculatePrime(BigInt(i));
    }
    for (int i = 1000; i > 500; i--) {
        pnl.doStuffWithNewlyPrimed();
        pnl.calculatePrime(BigInt(i));
    }
    for (int i = 10000; i > 0; i--) {
        pnl.doStuffWithNewlyPrimed();
        pnl.calculatePrime(BigInt(i));
    }
    while (pnl.newlyPrimed.size > 0)
        pnl.doStuffWithNewlyPrimed();
    if (pnl.primes.size > 100)
        std::cout << "Primes count: " << pnl.primes.size << std::endl;
    else
        std::cout << "Primes: " << pnl.primes << std::endl;
    std::cout << "Candidates: " << pnl.candidatePrimes << std::endl;
    std::cout << "Pending: " << pnl.pendingPrimesAndCalcs << std::endl;
    std::cout << "Calcs: " << pnl.primesWaitingForPrimes << std::endl;

    struct timeval time_end{};
    gettimeofday(&time_end, nullptr);
    time_t msecs_time_end = (time_end.tv_sec * 1000) + (time_end.tv_usec / 1000);

    std::cout << "Time: " << (msecs_time_end - msecs_time) << "\n";
    return 0;
}
