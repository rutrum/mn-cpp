#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>

#include "../util/partial_soe.h"

using namespace std;

int main() {
    PartialSieve s = PartialSieve(0, 10000);
    
    int total = 0;
    for (int i = 0; i < 100000; i += 10000) {
        PartialSieve s = PartialSieve(i, 10000 + i);
        total += s.count();
    }

    if (total != 9593) {
        cout << "Expected 9592, got " << total << endl;
        return 1;
    }
}
