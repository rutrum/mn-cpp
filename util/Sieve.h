#include <iostream>
#include <vector>

using namespace std;

struct Sieve {

    vector<int> sieve;

    /*
    Initializes the sieve array with values up to n
    */
    void init(int n) {
        sieve.resize(n + 1);
        findSieve();
    }

    /*
    Sieve of Eratosthenes implementation.

    If i is prime, then sieve[i] is 0.  If i is
    composite, then sieve[i] is the smallest prime
    factor of i.
    */
    void findSieve() {
        //finds primes
        for (int i = 2; i * i < sieve.size(); i++) {
            if (sieve[i] == 0) {
                //finds composites
                for (int j = i * i; j < sieve.size(); j += i) {
                    if (sieve[j] == 0) {
                        sieve[j] = i;
                    }
                }
            }
        }
    }

    /*
    Returns the sieve value for number n
    */
    int get(int n) {
        return sieve[n];
    }

    /*
    Prints "i: sieve[i]"
    */
    void print() {
        for (int i = 0; i < sieve.size(); i++) {
            cout << i << ": " << sieve[i] << endl;
        }
    }

};