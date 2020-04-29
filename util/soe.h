using namespace std;

class Sieve {

    vector<int> primes;

public:

    Sieve(int n) {
        primes.resize(n + 1);
        init_sieve();
    }

    void print() {
        for (int i = 0; i < primes.size(); i++) {
            cout << primes[i] << " ";
        }
        cout << endl;
    }

    // to return a new factor object
    void factor(int n) {
           
    }

private:

    // Stores the highest prime that divides the index
    void init_sieve() {
        // Finds primes p
        for (int i = 2; i * i < primes.size(); i++) {
            if (primes[i] == 0) {

                // For each multiple of p
                for (int j = i * i; j < primes.size(); j += i) {
                    primes[j] = i;
                }
            }
        }
    }
};
