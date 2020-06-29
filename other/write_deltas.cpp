#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <fstream>

#include "../util/factors.h"
#include "../util/sieve/sieve.h"
#include "../delta/segmented_modulo_1.h"
#include "../delta/modulo_1.h"

using namespace std;

int main() {

    ofstream out;
    out.open("delta_u32.txt");
    for (uint32_t i = 1; i <= 42; i++) { // broken for these values
        Factors f = Factors(i * 100000000);
        uint64_t delta = delta_segmented_modulo_1(f, 2000000);
        //uint64_t delta = delta_modulo_1(f);
        cout << delta << endl;
        out << delta << endl;
    }
    out.close();
}
