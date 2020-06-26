#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <fstream>

#include "../util/factors.h"
#include "../util/sieve/sieve.h"
#include "../delta/modulo_w.h"

using namespace std;

int main() {
    int sum = 0;
    int N = 60;
    auto classes = classify_coords(N);

    ofstream out;
    out.open("delta_u32.txt");
    for (uint64_t i = 3221225472; i <= 3221225482; i++) { // broken for these values
        cout << "i: " << i << endl;
        Factors f = Factors(i);
        uint64_t delta = delta_modulo_w(f, N, classes);
        sum += i - delta;
        out << delta << endl;
    }
    out.close();
    cout << sum << endl;
}
