#include <stdlib.h>
#include <iostream>
#include <boost/dynamic_bitset.hpp>
#include <boost/math/common_factor_rt.hpp>

#include "../util/Sieve.h"
Sieve sieve;
#include "../util/Factorization.h"

#include "../util/freeFunc.h"
#include "../alg/aModN.h"

using namespace std;

int main(int argc, char * argv[]) {

    int start = 0, end = 1000;
    long Mn = 0;
    const int N = 12;

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
    
    sieve.init(end);

    initModN(N);

    for (int i = start; i <= end; i++) {
        Factorization d(i);
        int delta = goModN(d);
        Mn += i - delta;
    }
    
    cout << Mn << endl;
}
