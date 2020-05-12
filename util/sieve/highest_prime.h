using namespace std;

class HighestPrimeSieve {

    vector<uint64_t> primes;

public:

    HighestPrimeSieve(uint64_t n) {
        primes.resize(n + 1);
        init_sieve();
    }

    uint64_t count() {
        int count = 0;
        for (int i = 1; i < primes.size(); i++) {
            count += primes[i] == 0;
        }
        return count;
    }

    void print() {
        for (uint64_t i = 0; i < primes.size(); i++) {
            cout << i << " " << primes[i] << endl;
        }
    }

    uint64_t highest_prime(uint64_t n) {
        return primes[n];
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
        for (uint64_t i = 2; i < primes.size(); i++) {
            if (primes[i] == 0) {
                for (uint64_t j = 2 * i; j < primes.size(); j += i) {
                    primes[j] = i;
                }
            }
        }
    }
};
