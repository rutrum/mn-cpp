#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <math.h>

#include "../util/sieve/segmented.h"

using namespace std;

int main() {
    SegmentedSieve s = SegmentedSieve(100000, 2000);
    if (s.count() != 9593) {
        cout << "Expected 9593, got " << s.count() << endl;
        return 1;
    }
}
