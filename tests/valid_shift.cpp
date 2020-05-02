#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <fstream>

#include "../util/factors.h"
#include "../util/soe.h"
#include "../delta/naive.h"
#include "../deltas/shift.h"
#include "./help.h"

using namespace std;

int main() {
    ifstream in;
    in.open("results/delta_100000.txt");

    int expected[100001];
    for (int i = 1; i <= 100000; i++) {
        in >> expected[i];
    }

    int max = 65536; // 2^16

    for (int m = 2; m <= 2; m++) {
        int* calculated = deltas_shift(m, max);
        for (int n = 1; n <= max; n++) {
            if (calculated[n] != -1) {
                cout << n << endl;
                assert_delta_n(expected[n], calculated[n], n);
            }
        }
        delete calculated;
    }

    in.close();
}
