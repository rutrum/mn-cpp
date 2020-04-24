#include <stdlib.h>
#include <iostream>
#include <boost/dynamic_bitset.hpp>

#include "../util/Sieve.h"
Sieve sieve;
#include "../util/Factorization.h"

#include "../util/shiftFunc.h"

#include "../alg/a1Free.h"
#include "../alg/aShift.h"

using namespace std;

int main(int argc, char * argv[]) {

    int m = strtol(argv[1], NULL, 10);
    
    sieve.init(m);

    vector<int> A;
    A.resize(m + 2);

    for (int i = 2; i * i < m; i++) {
        goShift(i, m, A);
    }

    // Fill gaps with AlgFirstFree
    for (int i = 1; i <= m; i++) {
        if (A[i] == 0) {
            Factorization d(i);
            A[i] = go1Free(d);
        }
    }

    // Calc M(n)
    long v = 0;
    for (int i = 1; i < m + 1; i++) {
        v += i - A[i];
    }

    cout << v << endl;
}