#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <fstream>

#include "../util/factors.h"
#include "../util/sieve/sieve.h"
#include "../util/sieve/highest_prime.h"

using namespace std;

int main() {
    uint64_t max = 4294967296; //2^32
    //uint64_t max = 2147483648; //2^31
    //uint64_t max = 1073741824; //2^30
    //uint64_t max = 268435456; //2^28
    //uint64_t max = 33554432; //2^25
    //uint64_t max = 1048576; //2^20
    auto visited = boost::dynamic_bitset<>(max + 1);

    uint64_t thresh = 10;

    // Wipe the files
    ofstream alg2_file;
    alg2_file.open("results/alg2_values.txt");
    alg2_file.close();
    ofstream m_file;
    m_file.open("results/m_values.txt");
    m_file.close();

    HighestPrimeSieve s = HighestPrimeSieve(max);

    uint64_t p_thresh = 1;
    for (uint64_t i = 0; i < thresh; i++) {
        p_thresh = s.next_prime(p_thresh);
    }
    cout << p_thresh << endl;
    
    uint64_t k;
    for (k = 1; k * p_thresh < max; k++) {

        if (visited[k] == 1) continue;

        // Find multipliers
        uint64_t m = k / s.highest_prime(k);

        uint64_t total = 0;
        for (uint64_t p = 1; p * m <= max && total < thresh; p = s.next_prime(p)) {
            if (visited[p * m] == 0)
                total += 1;
        }

        if (total < thresh) {
            // Not enough values to be worth of being a multiplier
            // Add these values to a list of values to be computed
            // using algorithm 2
            
            ofstream alg2_file;
            alg2_file.open("results/alg2_values.txt", fstream::app);
            for (uint64_t p = s.highest_prime(k); p != 0 && p * m <= max; p = s.next_prime(p)) {
                if (visited[m * p] == 0) {
                    alg2_file << m * p << endl;
                    visited[m * p] = 1;
                }
            }
            alg2_file.close();

        } else {
            // Good multiplier!  Let's write k to file and
            // cross off the values in visited

            ofstream m_file;
            m_file.open("results/m_values.txt", fstream::app);
            m_file << m << " " << s.highest_prime(k) << endl;
            m_file.close();

            for (uint64_t p = s.highest_prime(k); p != 0 && p * m <= max; p = s.next_prime(p)) {
                visited[m * p] = 1;
            }
        }
    }

    alg2_file;
    alg2_file.open("results/alg2_values.txt", fstream::app);
    for (; k < max; k++) {
        if (visited[k] == 0)
            alg2_file << k << endl;
    }
    alg2_file.close();

}
