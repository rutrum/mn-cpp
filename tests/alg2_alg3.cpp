#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <fstream>

#include "../util/factors.h"
#include "../util/sieve/sieve.h"
#include "../delta/segmented_naive.h"
#include "../delta/naive.h"
#include "../deltas/dynamic_shift.h"
#include "../deltas/shift.h"
#include "../delta/segmented_modulo_1.h"
#include "./help.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) { return 1; }
    uint32_t m = strtol(argv[1], NULL, 10);

    uint64_t max = 4294967296; 
    cout << "Sieving..." << endl;
    Sieve s = Sieve(max / m + 1);
    cout << "done!" << endl;

    cout << "Allocating..." << endl;
    uint32_t* dyn_deltas = new uint32_t[max / m + 1];
    for (uint64_t i = 0; i <= max / m; i++) {
        dyn_deltas[i] = -1;
    }
    uint32_t* trial_deltas = new uint32_t[max / m + 1];
    for (uint64_t i = 0; i <= max / m; i++) {
        trial_deltas[i] = -1;
    }
    cout << "done!" << endl;

    cout << "Dynamic shifting with scaling..." << endl;
    deltas_dynamic_shift(m, max, s, dyn_deltas);
    cout << "done!" << endl;

    cout << "Dynamic shifting with trial division..." << endl;
    deltas_dynamic_shift_trial(m, max, s, trial_deltas);
    cout << "done!" << endl;

    cout << "Checking..." << endl;
    for (int i = 0; i < max / m + 1; i++) {
        if (dyn_deltas[i] != -1) {
            
            Factors f = Factors(i * m);
            uint32_t mod_delta = delta_segmented_modulo_1(f, 2000000);

            if (mod_delta < 0 || mod_delta != dyn_deltas[i] || mod_delta != trial_deltas[i]) {
                cout << endl << "Mismatch: n = " << i * m << endl;
                cout << "alg2:\t" << mod_delta << endl;
                cout << "trial:\t" << trial_deltas[i] << endl;
                cout << "dyn:\t" << dyn_deltas[i] << endl;
            } else {
                cout << "Good: n = " << i * m << endl;
            }
        }
    }
    cout << endl << "...done!" << endl;

}
