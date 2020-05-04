using namespace std;

class Sieve {

    boost::dynamic_bitset<> primes;

public:

    Sieve(uint64_t n) {
        primes.resize(n + 1);
        init_sieve();
    }

    uint64_t count() {
        return primes.size() - primes.count() - 2;
    }

    void print() {
        for (uint64_t i = 0; i < primes.size(); i++) {
            cout << i << " " << (primes[i] == 0) << endl;
        }
    }

    bool is_prime(uint64_t n) {
        return primes[n] == 0;
    }

    // Returns the next prime greater than n
    // returns 0 if next prime isn't within sieve.
    int next_prime(uint64_t n) {
        for (uint64_t i = n + 1; i < primes.size(); i++) {
            if (primes[i] == 0) { return i; }
        }
        return 0;
    }

private:

    void init_sieve() {
        // multiples of 2
        for (uint64_t j = 4; j < primes.size(); j += 2) {
            primes[j] = 1;
        }
        
        // multiples of 3 and not 2
        for (uint64_t j = 9; j < primes.size(); j += 6) {
            primes[j] = 1;
        }

        // integers 5 mod 6
        for (uint64_t i = 5; i * i < primes.size(); i += 6) {
            if (primes[i] == 0) {
                for (uint64_t j = i * i; j < primes.size(); j += 4 * i) {
                    primes[j] = 1;
                    j += 2 * i;
                    if (j < primes.size()) {
                        primes[j] = 1;
                    }
                }
            }
        }

        // integers 1 mod 6
        for (uint64_t i = 7; i * i < primes.size(); i += 6) {
            if (primes[i] == 0) {
                for (uint64_t j = i * i; j < primes.size(); j += 2 * i) {
                    primes[j] = 1;
                    j += 4 * i;
                    if (j < primes.size()) {
                        primes[j] = 1;
                    }
                }
            }
        }
    }
};
