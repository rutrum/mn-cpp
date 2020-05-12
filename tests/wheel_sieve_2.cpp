#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>

#include "../util/sieve/wheel_mod_2.h"

using namespace std;

int main() {
    WheelSieve2 s = WheelSieve2(53);
    int p = 1;
    while (p != 0) {
        p = s.next_prime(p);
        cout << p << endl;
    }
    cout << s.count() << endl;
}
