#include <iostream>
#include <vector>

#include "../util/factors.h"
#include "../util/sieve/highest_prime.h"

using namespace std;

int main() {
    HighestPrimeSieve s = HighestPrimeSieve(100000);
    if (s.count() != 9593) {
        cout << "Expected 9593, got " << s.count() << endl;
        return 1;
    }

    for (int p = 1; p < 100; p = s.next_prime(p)) {
        cout << p << endl;
    }
}
