#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>

#include "../util/sieve/sieve.h"

using namespace std;

int main() {
    Sieve s = Sieve(100000);
    if (s.count() != 9593) {
        cout << "Expected 9593, got " << s.count() << endl;
        return 1;
    }
}
