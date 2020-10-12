#include <iostream>
#include <stdlib.h>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <fstream>
#include <string>
#include <map>

#include "../util/factors.h"
#include "../delta/fast.h"
#include "../delta/naive.h"
#include "../delta/segmented_naive.h"
#include "../delta/modulo_1.h"
#include "../delta/segmented_modulo_1.h"
#include "../delta/modulo_w.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 4) {
        return 1;
    }

    uint32_t start = strtol(argv[2], NULL, 10);
    uint32_t end = strtol(argv[3], NULL, 10);

    uint64_t sum = 0;

    string alg = string(argv[1]);
    uint32_t calculated;

    if (alg == "naive") {
        for (int n = start + 1; n <= end; n++) {
            Factors f = Factors(n);
            sum += n - delta_naive(f);
        }

    } else if (alg == "segmented_naive") {
        for (int n = start + 1; n <= end; n++) {
            Factors f = Factors(n);
            sum += n - delta_segmented_naive(f, 2000000);
        }

    } else if (alg == "modulo_1") {
        for (int n = start + 1; n <= end; n++) {
            Factors f = Factors(n);
            sum += n - delta_modulo_1(f);
        }

    } else if (alg == "segmented_modulo_1") {
        for (int n = start + 1; n <= end; n++) {
            Factors f = Factors(n);
            sum += n - delta_segmented_modulo_1(f, 2000000);
        }

    } else if (alg == "modulo_w") {
        int w = 120;
        auto classes = classify_coords(w);
        for (int n = start + 1; n <= end; n++) {
            Factors f = Factors(n);
            sum += n - delta_modulo_w(f, w, classes);
        }

    } else if (alg == "fast-modulo_1") {
        FastRules fast = FastRules(); 
        for (int n = start + 1; n <= end; n++) {
            calculated = fast.eval(n);
            if (calculated == -1) {
                Factors f = Factors(n);
                sum += n - delta_modulo_1(f);
            } else {
                sum += n - calculated;
            }
        }

    } else {
        cout << "No such algorithm \"" << alg << "\"" << endl;
        return 1;
    }

    cout << "sum(n-delta(n)): " << sum << endl;
}
