#include <iostream>
#include <stdlib.h>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <fstream>
#include <string>
#include <map>

#include "../util/factors.h"
#include "../util/sieve/sieve.h"
#include "../delta/naive.h"
#include "../delta/segmented_naive.h"
#include "../deltas/shift.h"
#include "../deltas/dynamic_shift.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        return 1;
    }

    string alg = string(argv[1]);
    uint32_t m = strtol(argv[2], NULL, 10);
    uint32_t start;
    uint32_t end = strtol(argv[3], NULL, 10);

    Sieve s = Sieve(end / m + 1);

    uint32_t* deltas = new uint32_t[end / m + 1];
    for (uint64_t i = 0; i <= end / m; i++) {
        deltas[i] = -1;
    }

    if (alg == "shift") {
        deltas_shift(m, end, s, deltas);

    } else if (alg == "dynamic_shift") {
        deltas_dynamic_shift(m, 1, end, s, deltas);

    } else {
        cout << "No such algorithm \"" << alg << "\"" << endl;
        return 1;
    }

    uint32_t total = 0;
    for (uint64_t i = 0; i <= end / m; i++) {
        if (deltas[i] != -1) {
            total += 1;
        }
    }

    cout << total << endl;

    delete[] deltas;
}
