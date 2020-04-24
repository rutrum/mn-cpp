#include <stdlib.h>
#include <iostream>
#include <boost/dynamic_bitset.hpp>
#include <boost/math/common_factor_rt.hpp>

#include <fstream>

#include "util/Sieve.h"
Sieve sieve;
#include "util/Factorization.h"

#include "util/freeFunc.h"
#include "alg/aNFree.h"

using namespace std;

int main(int argc, char * argv[]) {

    const int N = 5;

    int lcm = 1;
    for (int i = 2; i < N + 1; i++) {
        lcm = boost::math::lcm(lcm, i);
    }
    
    sieve.init(lcm);

    initNFree(N);

    ofstream output;
    output.open ("./step.txt");

    for (int i = 0; i < lcm; i++) {
        output << '{';
        for (int j = 0; j < lcm - 1; j++) {
            output << columnStep[i][j] << ", ";
        }
        output << columnStep[i][lcm - 1] << "},\n";
    }

    output << endl;

    for (int i = 0; i < lcm; i++) {
        output << '{';
        for (int j = 0; j < lcm - 1; j++) {
            output << rowStep[i][j] << ", ";
        }
        output << rowStep[i][lcm - 1] << "},\n";
    }
    
    output << endl;

    for (int j = 0; j < lcm - 1; j++) {
        output << rowStart[j] << ", ";
    }
    output << rowStart[lcm - 1] << endl;


}