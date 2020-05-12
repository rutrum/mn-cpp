using namespace std;

class WheelSieve2 {

    boost::dynamic_bitset<> primes;

public:

    WheelSieve2(uint64_t n) {
        primes.resize((n + 1) / 2);
        init_sieve();
    }

    uint64_t count() {
        return primes.size() - primes.count();
    }

    void print() {
        for (uint64_t i = 0; i < primes.size(); i++) {
            cout << 2*i + 1 << " " << (primes[i] == 0) << endl;
        }
    }

    bool is_prime(uint64_t n) {
        if (n % 2 == 0) {
            return false;
        }
        return primes[n / 2] == 0;
    }

    // Returns the next prime greater than n
    // returns 0 if next prime isn't within sieve.
    int next_prime(uint64_t n) {
        if (n < 2) return 2;
        for (uint64_t i = (n + 1) / 2; i < primes.size(); i++) {
            if (primes[i] == 0) { return i * 2 + 1; }
        }
        return 0;
    }

private:

    void init_sieve() {
        for (int i = 3; i < 2 * primes.size(); i += 2) {
            if (primes[i / 2] == 0) {
                for (int j = i * i; j < 2 * primes.size(); j += i * 2) {
                    primes[(j - 1) / 2] = 1;
                }
            }
        }
    }
};
