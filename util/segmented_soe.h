using namespace std;

class SegmentedSieve {

    boost::dynamic_bitset<> primes;
    uint64_t start;
    uint64_t end;

public:

    SegmentedSieve(uint64_t start, uint64_t end) {
        primes.resize(end - start + 1);
        cout << primes.size() << endl;
        this->start = start;
        this->end = end;
        init_sieve();
    }

    void print() {
        for (uint64_t i = 0; i < primes.size(); i++) {
            cout << i + start << " " << (primes[i] == 0) << endl;
        }
    }

    bool is_prime(uint64_t n) {
        return primes[n - start] == 0;
    }

    int first_prime() {
        return this->next_prime(start - 1);
    }

    // Returns the next prime greater than n
    // returns 0 if next prime isn't within sieve.
    int next_prime(uint64_t n) {
        for (uint64_t i = n + 1; i <= end; i++) {
            if (primes[i - start] == 0) { return i; }
        }
        return 0;
    }

private:

    void init_sieve() {

        for (uint64_t i = 2; i * i <= end; i++) {
            // could use the other sieve to get first sqrt(end) primes
            int s = ((start - 1) / i + 1) * i;
            cout << "s: " << s << endl;
            for (uint64_t j = s; j <= end; j += i) {
                primes[j - start] = 1;
            }
        }
    }
};
