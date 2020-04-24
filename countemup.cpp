#include <stdlib.h>
#include <iostream>
#include <boost/dynamic_bitset.hpp>
#include <boost/math/common_factor_rt.hpp>

#include "util/Sieve.h"
Sieve sieve;
#include "util/Factorization.h"

#include "util/freeFunc.h"
#include "alg/aModN.h"

using namespace std;

int main(int argc, char * argv[]) {

    int start = 1, end = 1000;
    long Mn = 0;
    const int N = 120;

    cout << "MODULO " << N << endl;

    switch (argc) {
        case 4:
            Mn = strtol(argv[3], NULL, 10);
        case 3:
            start = strtol(argv[1], NULL, 10);
            end = strtol(argv[2], NULL, 10);
            break;
        case 2:
            end = strtol(argv[1], NULL, 10);
    }

    sieve.init(max(end, N));

    initModN(N);

    // Here I should initialize boundPool

    // LOWER BOUND POOL

    // There is a vector corresponding to a remainder mod f, called i
    // that contains all the factors of f that divide i.  These indices
    // are the rows that calculate the lowerbound Li

    // Factorization freeFact(60);
    // boundPool.resize(60);
    // for (int j = 0; j < freeFact.pairs.size(); j++) {
    //     boundPool[0].push_back(freeFact.pairs[j].x - 1);
    //     boundPool[0].push_back(freeFact.pairs[j].y - 1);
    // }
        
    // for (int i = 1; i < 60; i++) {
    //     // First look at x values
    //     for (int j = 0; j < freeFact.pairs.size(); j++) {
    //         if (i % freeFact.pairs[j].x == 0) {
    //             boundPool[i].push_back(freeFact.pairs[j].x - 1);
    //         }
    //         if (i % freeFact.pairs[j].y == 0) {
    //             boundPool[i].push_back(freeFact.pairs[j].y - 1);
    //         }
    //     }
    // }

    unsigned long long totalProducts = 0;
    int power = 1;
    for (int i = start; i <= end; i++) {
        Factorization d(i);

        totalProducts += goModN(d);
        if (i == power) {
            cout << "products for " << i << ": " << totalProducts << endl;
            power *= 2;
        }

        // unsigned long long delta = go5Free(d);
        // Mn += i - delta;
    }
    
    //cout << Mn << endl;
}