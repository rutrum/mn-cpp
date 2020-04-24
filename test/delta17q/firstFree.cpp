#include <stdlib.h>
#include <iostream>
#include <boost/dynamic_bitset.hpp>

#include "../../util/Sieve.h"
Sieve sieve;
#include "../../util/Factorization.h"

#include "../../alg/AlgFirstFree.h"

using namespace std;

int main(int argc, char * argv[]) {

    int m = 29 * 224737;
    sieve.init(m);

    for (int i = 2, j = 0; i <= m, j < 20000; i++) {
        if (sieve.sieve[i] == 0) {
            AlgFirstFree::go(29*i);
            j++;
        }
    }

}