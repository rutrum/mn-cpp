#include <stdlib.h>
#include <iostream>
#include <boost/dynamic_bitset.hpp>

#include "../util/Sieve.h"
Sieve sieve;
#include "../util/Factorization.h"

#include "../alg/a1Free.h"

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
        int delta = go1Free(d);
        Mn += i - delta;
    }
    
    cout << Mn << endl;
}
