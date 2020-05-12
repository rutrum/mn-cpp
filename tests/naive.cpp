#include <iostream>
#include <boost/dynamic_bitset.hpp>
#include <fstream>

#include "../util/factors.h"
#include "../delta/naive.h"
#include "./help.h"

using namespace std;

int main() {
    ifstream in;
    in.open("results/delta_100000.txt");
    for (int n = 1; n <= 100000; n++) {
        Factors f = Factors(n);
        int calculated = delta_naive(f);

        int expected;
        in >> expected;

        assert_delta_n(expected, calculated, n);
    }
    in.close();
}
