using namespace std;

class SegmentedSieve {

    boost::dynamic_bitset<> primes;

public:

    SegmentedSieve(uint64_t n, uint64_t segment_size) {
        primes.resize(n + 1);
        init_sieve(segment_size);
    }

    uint64_t count() {
        return primes.size() - primes.count();
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

    void init_sieve(uint64_t segment_size) {
        primes[1] = 1;
        
        uint64_t sqrtn = sqrt(primes.size() - 1); // Remember the size is one more than max
        //Sieve s = Sieve(sqrtn);

        // Start is exclusive, end is inclusive
        for (uint64_t start = 0; start + 1 < primes.size(); start += segment_size) {
            uint64_t end = start + segment_size;
            if (end >= primes.size()) end = primes.size() - 1;
            //cout << start << " " << end << endl;

            //for (uint64_t p = 2; p != 0 && p * p < end; p = s.next_prime(p)) {
            for (uint64_t p = 2; p * p <= end; p++) {

                uint64_t s = start + p - (start % p);
                if (s < p*p) s = p*p; // Edge case when speve pncludes numbers less than sqrt(n)

                for (uint64_t j = s; j <= end; j += p) {
                    primes[j] = 1;
                }
            }
        }
    }
};

/*
 for( int k= 1; k <= 2^13; k++) {
    \\  we are considering an interval from ((k-1)*2^19, k*2^19]
    for( int i = 2; i <= 2^16; i++) {
        \\ compute start index correctly
        if i^2 < (k-1)*2^19 then {  
            start = (k-1)*2^19 + ( (k-1)*2^19 mod i}
        }
        if i^2 > k*2^19 {
            break; \\ do next i, but can actually move on to next k value b/c all i from here on out will satisfy
        }
        else \\  so (k-1)*2^19 < i^2 <  k*2^19
        {
            start = i*i
        }
        for( int j =start; j <=  k*2^19; j+=i)  { 
            A[j] = true;
        }
    }
}

*/
