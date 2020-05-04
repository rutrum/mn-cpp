#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <fstream>

#include "../util/factors.h"
#include "../util/soe.h"
#include "../delta/naive.h"
#include "../delta/modulo_1.h"
#include "../delta/modulo_w.h"
#include "../deltas/shift.h"
#include "./help.h"

using namespace std;

int main() {

    // Load in correct results
    ifstream in;
    in.open("./results/delta_100000.txt");
    int expected[100001];
    for (int i = 1; i <= 100000; i++) {
        in >> expected[i];
    }

    int max = 100000; 
    //int max = 524288; 

    Sieve s = Sieve(max);

    cout << s.count() << endl;

    int deltas[max + 1];
    for (auto i = 0; i <= max; i++) {
        deltas[i] = -1;
    }

    cout << "Multipliers" << endl;
    // Use multipliers to find classes of delta values
    for (int m = 2; m <= 1000; m++) {
        uint32_t m_deltas[max / m + 1];
        for (auto i = 0; i <= max / m; i++) {
            m_deltas[i] = -1;
        }
        deltas_shift(m, max, s, m_deltas);
        for (auto i = 0; i <= max / m; i++) {
            if (m_deltas[i] != -1) {
                deltas[m * i] = m_deltas[i];
            }
        }
    }

    /*
    int w = 60;
    auto classes = classify_coords(w);

    for (int n = 1; n <= max; n++) {
        if (deltas[n] != -1) {
            Factors f = Factors(n);
            int modw = delta_modulo_w(f, w, classes);
            assert_delta_n(modw, deltas[n], n);
        }
    }
    */

    cout << "Check" << endl;
    for (auto n = 1; n <= max; n++) {
        if (deltas[n] != -1) {
            assert_delta_n(expected[n], deltas[n], n);
        }
    }

    in.close();
}
