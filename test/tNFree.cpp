#include <stdlib.h>
#include <iostream>
#include <boost/dynamic_bitset.hpp>
#include <boost/math/common_factor_rt.hpp>

#include "../util/Sieve.h"
Sieve sieve;
#include "../util/Factorization.h"

#include "../util/freeFunc.h"
#include "../alg/aNFree.h"

using namespace std;

int main(int argc, char * argv[]) {

    int start = 100000000, end = start+50;
    long Mn = 0;
    const int N = 5;

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

    int lcm = 1;
    for (int i = 2; i < N + 1; i++) {
        lcm = boost::math::lcm(lcm, i);
    }

    cout << lcm << endl;

    sieve.init(max(end, lcm));
    
    sieve.init(end);

    initNFree(N);

    for (int i = start; i <= end; i++) {
        Factorization d(i);
        int delta = goNFree(d);
        Mn += i - delta;
    }
    
    cout << Mn << endl;
}