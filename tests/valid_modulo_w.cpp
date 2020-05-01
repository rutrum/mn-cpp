#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <fstream>

#include "../util/factors.h"
#include "../util/soe.h"
#include "../delta/modulo_w.h"
#include "./help.h"

using namespace std;

int main() {
    ifstream in;
    in.open("results/delta_100000.txt");

    int w = 30;
    auto classes = classify_coords(w);

    for (int n = 1; n <= 30000; n++) {
        Factors f = Factors(n);
        int calculated = delta_modulo_w(f, w, classes);

        int expected;
        in >> expected;

        assert_delta_n(expected, calculated, n);
    }
    in.close();
}
