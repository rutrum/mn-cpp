#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <fstream>
#include <string>

#include "../util/factors.h"
#include "../util/soe.h"
#include "../delta/segmented_naive.h"
#include "../deltas/dynamic_shift.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) { return 1; }

    uint64_t max = 4294967296;
    int m = strtol(argv[1], NULL, 10);

    //cout << "Init sieve" << endl;
    Sieve s = Sieve(max / m + 1);
    //cout << "sieve done" << endl;

    //cout << "Attempting to allocate " << max / m + 1 << endl;
    uint32_t* deltas = new uint32_t[max / m + 1];
    //cout << "Deltas allocated" << endl;
    for (uint64_t i = 0; i <= max / m; i++) {
        deltas[i] = -1;
    }
    //cout << "-1 assigned allocated" << endl;


    // Use multipliers to find classes of delta values
    deltas_dynamic_shift(m, max, s, deltas);

    // Write the multipliers to file
    ofstream out;
    out.open("results/multipliers/deltas_max" + to_string(max) + "_m" + to_string(m) + ".txt");
    for (uint64_t n = 1; n <= max / m; n++) {
        if (deltas[n] != -1) {
            out << n * m << " " << deltas[n] << endl;
        }
    }
    out.close();
    delete[] deltas;

    cout << "m = " << m << endl;

}
