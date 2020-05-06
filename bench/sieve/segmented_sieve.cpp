#include <iostream>
#include <math.h>
#include <boost/dynamic_bitset.hpp>

#include "../../util/soe.h"
#include "../../util/segmented_sieve.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;

    uint64_t size = strtol(argv[1], NULL, 10);
    uint64_t segment = strtol(argv[2], NULL, 10);

    SegmentedSieve s = SegmentedSieve(size, segment);
    cout << s.count() << endl;
}
