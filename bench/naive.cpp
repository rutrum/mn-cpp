#include <stdlib.h>
#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>

#include "../util/factors.h"
#include "../delta/naive.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;

    long sum = 0;
    int start = strtol(argv[1], NULL, 10);
    int end = strtol(argv[2], NULL, 10);

    for (int n = start; n <= end; n++) {
        Factors f = Factors(n);
        int delta = delta_naive(f);
        sum += n - delta;
    }

    cout << sum << endl;
}
