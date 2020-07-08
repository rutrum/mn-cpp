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
    if (argc < 3) {
        return 1;
    }

    uint32_t n = strtol(argv[2], NULL, 10);
    Factors f = Factors(n);

    string alg = string(argv[1]);
    uint32_t calculated;

    if (alg == "naive") {
        calculated = delta_naive(f);

    } else if (alg == "segmented_naive") {
        calculated = delta_segmented_naive(f, 200000);

    } else if (alg == "modulo_1") {
        calculated = delta_modulo_1(f);

    } else if (alg == "segmented_modulo_1") {
        calculated = delta_segmented_modulo_1(f, 2000000);

    } else if (alg == "modulo_w") {
        int w = 120;
        auto classes = classify_coords(w);
        calculated = delta_modulo_w(f, w, classes);

    } else if (alg == "fast") {
        FastRules fast = FastRules(); 
        calculated = fast.eval(f);
        if (calculated == -1) {
            cout << "No fast rule to calculate " << n << endl;
            return 1;
        }

    } else {
        cout << "No such algorithm \"" << alg << "\"" << endl;
        return 1;
    }

    cout << calculated << endl;
}
