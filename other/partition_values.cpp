#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <fstream>

#include "../util/factors.h"
#include "../util/sieve/sieve.h"

using namespace std;

int main() {
    uint64_t max = 4294967296;
    auto visited = boost::dynamic_bitset<>(max + 1);

    fstream m_file;
    m_file.open("results/m_values.txt");
    fstream alg2_file;
    alg2_file.open("results/alg2_values.txt");

    Sieve s = Sieve(max);
    
    for (uint64_t k = 1; k < max; k++) {

        if (visited[k] == 1) continue;

        // Find largest divisible prime
        uint64_t m = 1;
        for (uint64_t p = s.prev_prime(k + 1); p > 0; p = s.prev_prime(p)) {
            if (k % p == 0) {
                m = k / p;
                break;
            }
        }

        // Starting at hp*hp, find number of multipliers found
        uint64_t total = 0;
        for (uint64_t p = 1; p * m <= max && total < 15; p = s.next_prime(p)) {
            if (visited[p] == 0)
                total += 1;
        }

        if (total < 15) {
            // Not enough values to be worth of being a multiplier
            // Add these values to a list of values to be computed
            // using algorithm 2
            alg2_file << k << endl;
            visited[k] = 1;

        } else {
            // Good multiplier!  Let's write k to file and
            // cross off the values in visited

            m_file << k << endl;
            for (uint64_t p = hp; p * hp <= max; p = s.next_prime(p)) {
                visited[hp * p] = true;
            }

        }
    }

    m_file.close();
    alg2_file.close();
}
