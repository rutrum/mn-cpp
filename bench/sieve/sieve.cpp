#include <iostream>
#include <boost/dynamic_bitset.hpp>

#include "../../util/soe.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) return 1;

    uint64_t size = strtol(argv[1], NULL, 10);

    Sieve s = Sieve(size);
    cout << s.count() << endl;
}
