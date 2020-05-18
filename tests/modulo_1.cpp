#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <fstream>

#include "../util/factors.h"
#include "../delta/modulo_1.h"
#include "./help.h"

using namespace std;

int main() {
    ifstream in;
    in.open("results/delta_100000.txt");
    for (int n = 1; n <= 100000; n++) {
        cout << n << endl;
        Factors f = Factors(n);
        f.print();
        int calculated = delta_modulo_1(f);
        cout << n << endl;

        int expected;
        in >> expected;

        assert_delta_n(expected, calculated, n);
    }
    in.close();
}
