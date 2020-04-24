#include <stdlib.h>
#include <iostream>
#include <boost/dynamic_bitset.hpp>
#include <boost/math/common_factor_rt.hpp>

#include "../../util/Sieve.h"
Sieve sieve;
#include "../../util/Factorization.h"

#include "../../alg/AlgNFree.h"

vector<vector<int>> AlgNFree::columnStep;
vector<vector<int>> AlgNFree::rowStep;
vector<int> AlgNFree::rowStart;
vector<vector<int>> AlgNFree::boundPool;
int AlgNFree::f;

using namespace std;

int main(int argc, char * argv[]) {

    int m = 29 * 224737;
    sieve.init(m);

    AlgNFree::init(4);

    for (int i = 2, j = 0; i <= m, j < 20000; i++) {
        if (sieve.sieve[i] == 0) {
            AlgNFree::go(29*i);
            j++;
        }
    }

}