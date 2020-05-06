#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <fstream>

#include "../util/factors.h"
#include "../util/soe.h"
#include "../delta/segmented_modulo_1.h"
#include "./help.h"

using namespace std;

int main() {
    ifstream in;
    in.open("results/delta_100000.txt");
    for (int n = 1; n <= 100000; n++) {
        Factors f = Factors(n);
        int calculated = delta_segmented_modulo_1(f, 1000);

        int expected;
        in >> expected;

        assert_delta_n(expected, calculated, n);
    }
    in.close();
}
