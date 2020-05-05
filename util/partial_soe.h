using namespace std;

class PartialSieve {

    boost::dynamic_bitset<> primes;
    uint64_t start;
    uint64_t end;

public:

    // Start is exclusive, end is inclusive
    PartialSieve(uint64_t start, uint64_t end) {
        primes.resize(end - start);
        this->start = start;
        this->end = end;
        init_sieve();
    }

    void print() {
        for (uint64_t i = 0; i < primes.size(); i++) {
            cout << i + 1 + start << " " << (primes[i] == 0) << endl;
        }
    }

    int count() {
        return primes.size() - primes.count();
    }

    bool is_prime(uint64_t n) {
        return primes[n - start] == 0;
    }

    int first_prime() {
        return this->next_prime(start);
    }

    // Returns the next prime greater than n
    // returns 0 if next prime isn't within sieve.
    int next_prime(uint64_t n) {
        for (uint64_t i = n + 1; i <= end; i++) {
            if (primes[i - start - 1] == 0) { return i; }
        }
        return 0;
    }

private:

    void init_sieve() {

        for (uint64_t i = 2; i * i <= end; i++) {
            // could use the other sieve to get first sqrt(end) primes
            uint64_t s = start + i - (start % i);
            if (s < i*i) s = i*i; // Edge case when sieve includes numbers less than sqrt(n)

            for (uint64_t j = s; j <= end; j += i) {
                primes[j - start - 1] = 1;
            }
        }
    }
};
