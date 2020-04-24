#include <stdlib.h>
#include <iostream>
#include <boost/dynamic_bitset.hpp>

#include "../util/Sieve.h"
Sieve sieve;
#include "../util/Factorization.h"

#include "../util/freeFunc.h"
#include "../alg/aFast.h"
#include "../alg/a5Free.h"

using namespace std;

int main(int argc, char * argv[]) {

    int start = 1, end = 1000;
    long Mn = 0;

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
    
    sieve.init(end);

    Factorization freeFact(60);
    boundPool.resize(60);
    for (int j = 0; j < freeFact.pairs.size(); j++) {
        boundPool[0].push_back(freeFact.pairs[j].x - 1);
        boundPool[0].push_back(freeFact.pairs[j].y - 1);
    }
    
    for (int i = 1; i < 60; i++) {
        // First look at x values
        for (int j = 0; j < freeFact.pairs.size(); j++) {
            if (i % freeFact.pairs[j].x == 0) {
                boundPool[i].push_back(freeFact.pairs[j].x - 1);
            }
            if (i % freeFact.pairs[j].y == 0) {
                boundPool[i].push_back(freeFact.pairs[j].y - 1);
            }
        }
    }

    for (int i = start; i <= end; i++) {
        Factorization d(i);
        int delta;
        if (canFast(d)) {
            delta = goFast(d);
        } else {
            delta = go5Free(d);
        }
        Mn += i - delta;
    }
    
    cout << Mn << endl;
}