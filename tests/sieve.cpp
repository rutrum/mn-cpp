#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>

#include "../util/soe.h"
#include "../util/segmented_soe.h"
#include "../util/wheel_sieve_mod_2.h"

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
