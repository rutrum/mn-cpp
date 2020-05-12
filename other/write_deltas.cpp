#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <fstream>

#include "../util/factors.h"
#include "../util/soe.h"
#include "../delta/moduloN.h"

using namespace std;

int main() {
    int sum = 0;
    int N = 60;
    auto classes = classify_coords(N);

    ofstream out;
    out.open("delta_100000.txt");
    for (int i = 1; i <= 100000; i++) {
        Factors f = Factors(i);
        int delta = delta_moduloN(f, N, classes);
        sum += i - delta;
        out << delta << endl;
    }
    out.close();
    cout << sum << endl;
}
