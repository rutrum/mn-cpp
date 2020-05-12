#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <fstream>

#include "../util/factors.h"
#include "../util/soe.h"
#include "../delta/segmented_naive.h"
#include "../deltas/dynamic_shift.h"
#include "./help.h"

using namespace std;

int main() {

    uint64_t max = 4294967296; 

    Sieve s = Sieve(max);

    cout << s.count() << endl;
    boost::dynamic_bitset<> visited(max+1);

    for (int m = 1; m < 30000000; m++) {
        for (auto i = 1; m*i < max; i = s.next_prime(i)) {
            visited[m * i] = true;
        }
    }
    uint64_t total = visited.count();
    cout << "Deltas computed: " << total << endl;
    cout << "Percentage: " << total * 1.0 / max << endl;
}
