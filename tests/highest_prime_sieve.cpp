#include <iostream>
#include <vector>

#include "../util/factors.h"
#include "../util/highest_prime_sieve.h"

using namespace std;

int main() {
    HighestPrimeSieve s = HighestPrimeSieve(100000);
    if (s.count() != 9593) {
        cout << "Expected 9593, got " << s.count() << endl;
        return 1;
    }
}
