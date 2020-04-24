#include <stdlib.h>
#include <iostream>
#include <boost/dynamic_bitset.hpp>

#include "../util/Sieve.h"
Sieve sieve;
#include "../util/Factorization.h"

#include "../util/freeFunc.h"
#include "../alg/a1Free.h"
#include "../alg/a2Free.h"
#include "../alg/aFast.h"

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

    for (int i = start; i <= end; i++) {
        Factorization d(i);
        int delta;
        if (canFast(d)) {
            delta = goFast(d);
        } else if (i % 6 == 2 || i % 6 == 4) {
            delta = go1Free(d);
        } else {
            delta = go2Free(d);
        }
        Mn += i - delta;
    }
    
    cout << Mn << endl;
}