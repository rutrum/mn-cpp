#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <set>
#include <boost/dynamic_bitset.hpp>

#include "../util/Sieve.h"
Sieve sieve;
#include "../util/Factorization.h"

#include "../util/freeFunc.h"
#include "../util/shiftFunc.h"

#include "../alg/a1Free.h"
#include "../alg/a2Free.h"
#include "../alg/aFast.h"
#include "../alg/aFill.h"

using namespace std;

int main(int argc, char * argv[]) {

    int m = strtol(argv[1], NULL, 10);
    
    sieve.init(m);

    vector<int> A;
    A.resize(m + 2);

    for (int i = 2; i * i < m; i++) {
        goFill(i, m, A, sqrt(m));
    }

    // Fill gaps with fast then otherwise
    for (int i = 1; i <= m; i++) {
        if (A[i] == 0) {
            Factorization d(i);
            int delta;
            if (canFast(d)) {
                delta = goFast(d);
            } else if (i % 6 == 2 || i % 6 == 4) {
                delta = go1Free(d);
            } else {
                delta = go2Free(d);
            }
            A[i] = delta;
        }
    }

    // Calc M(n)
    long v = 0;
    for (int i = 1; i < m + 1; i++) {
        v += i - A[i];
    }

    cout << v << endl;
}