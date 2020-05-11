#include <stdlib.h>
#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>

#include "../util/factors.h"
#include "../delta/modulo_w.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;

    long sum = 0;
    int start = strtol(argv[1], NULL, 10);
    int end = strtol(argv[2], NULL, 10);

    int w = 120;
    auto classes = classify_coords(w);

    for (int n = start; n <= end; n++) {
        Factors f = Factors(n);
        int delta = delta_modulo_w(f, w, classes);
        sum += n - delta;
    }

    cout << sum << endl;
}
