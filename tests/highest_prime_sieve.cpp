#include <iostream>
#include <vector>

#include "../util/factors.h"
#include "../util/sieve/highest_prime.h"

using namespace std;

int main() {
    HighestPrimeSieve s = HighestPrimeSieve(4294967296);
    if (s.count() != 9593) {
        cout << "Expected 9593, got " << s.count() << endl;
        return 1;
    }
}
