#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <boost/math/common_factor_rt.hpp>

using namespace std;

#include "../util/Sieve.h"
Sieve sieve;
#include "../util/fastFact.h"
#include "../util/Factorization.h"

#include "../util/freeFunc.h"
#include "../alg/aNFree.h"

int main(int argc, char * argv[]) {

    int m = strtol(argv[1], NULL, 10);

    const int N = 4;
    int lcm = 1;
    for (int i = 2; i <= N; i++) {
        lcm = boost::math::lcm(lcm, i);
    }

    sieve.init(lcm); // Done for initNfree purposes
    initNFree(N);
    // cout << "init done" << endl;
    int segmentSize = sqrt(m) + 1;
    // cout << "segment size: " << segmentSize << endl;

    long last = 0;
    for (int s = 1; s < m + 1; s += segmentSize) {
        vector<vector<int>> segment;
        int e = s + segmentSize;
        if (e > m + 1) {
            e = m + 1;
        }
        
        findSegmentPairs(segment, s, e);

        for (int i = s; i < e; i++) {
            // cout << i % s << endl;
            // cout << segment[i % s].size() << endl;
            int index = i % s;
            if (s == 1) {
                // Don't want to mod by 1
                index = i - 1;
            }
            Factorization d(i, segment[index]);
            // d.printPairs();
            int delta = goNFree(d);
            last += i - delta;
        }
    }
    
    cout << last << endl;
}