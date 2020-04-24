#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Factorization {
    
    struct PrimePower {
        int prime;
        int power;

        PrimePower(int a, int b) {
            prime = a;
            power = b;
        }
    };

    struct Pair {
        int x;
        int y;

        Pair(int a, int b) {
            x = a;
            y = b;
        }

        bool operator < (const Pair& p) const {
            return (x < p.x);
        }

    };

    int n;
    vector<PrimePower> pf;
    vector<Pair> pairs;

    Factorization(int num, vector<int>& list) {
        n = num;
        for (int i = 0; i < list.size(); i += 2) {
            // cout << list[i] << " " << list[i+1]<< endl;
            storePair(list[i], list[i + 1]);
        }
    }

    Factorization(int num) {
        n = num;
        factor();
        findFactorPairs(2);
    }

    Pair last() {
        int l = pairs.size();
        return pairs[l - 1];
    }

    // Returns if number is k-smooth
    bool isSmooth(int k) {
        if (pf.back().prime <= k) {
            return true;
        }
        return false;
    }

    // Returns the largest power of p that divides n
    int valuation(int p) {
        for (int i = 0; i < pf.size(); i++) {
            if (pf[i].prime = p) {
                return pf[i].power;
            }
        }
        return 0;
    }

    /*
    The following are tau functions defined in the notes

    maybe to be redone, really quick and dirty way of doing this
    */

    // returns true if any divisor of a lies in the interval (l, u]
    bool tauBool(int l, int u, Factorization a) {
        for (int i = 0; i < a.pairs.size(); i++) {
            if (a.pairs[i].x > l && a.pairs[i].x <= u) {
                return true;
            }
            if (a.pairs[i].y > l && a.pairs[i].y <= u) {
                return true;
            }
        }
        return false;
    }

    int tauPlus(int d) {
        int total = 0;
        Factorization a(d);
        for (int i = 1; i < d; i *= 2) {
            if (tauBool(i, i * 2, a)) {
                total++;
            }
        }
        return total;
    }

    int bestTauPlusVal(int upper) {
        int bestVal = 1;
        int bestTauPlus = 0;
        //upper bound says when to stop checking
        for (int i = 0; i < pairs.size(); i++) {
            if (pairs[i].x >= upper) {
                return bestVal;
            }
            if (tauPlus(pairs[i].x) > bestTauPlus) {
                bestVal = pairs[i].x;
                bestTauPlus = tauPlus(pairs[i].x);
            }
        }
        for (int i = pairs.size() - 1; i >= 0; i--) {
            if (pairs[i].y >= upper) {
                return bestVal;
            }
            if (tauPlus(pairs[i].y) > bestTauPlus) {
                bestVal = pairs[i].y;
                bestTauPlus = tauPlus(pairs[i].y);
            }
        }
    }

    /*
    Moves all divisors pairs left, or
    increase all the y values by specific value.
    Note, this is only useful in very specific cases.
    Used by AlgShiftShapePlus
    */
    void shiftLatticePoints() {
        for (int i = 0; i < pairs.size(); i++) {
            pairs[i].y += pairs.back().x / pairs[i].x;
        }
        n += pairs.back().x;
    }

    /*
    Factors n into primes and stores primes
    and their powers into pf
    */
    void factor() {
        int num = n;
        while (true) {
            int p = sieve.get(num);
            //If p = 0, then a is the next prime
            if (p == 0) {
                storePrime(num);
                break;
            }
            //Otherwise, store p and divide
            storePrime(p);
            num /= p;
        }
    }

    /*
    Adds prime p to pf
    */
    void storePrime(int p) {
        if (pf.size() == 0 || pf.back().prime != p) {
            //prime is new
            PrimePower pp(p, 1);
            pf.push_back(pp);
        } else {
            //prime is duplicate
            pf.back().power++;
        }
    }

    int getHighestPrime() {
        return pf.back().prime;
    }

    /*
    Calculates all factor pairs (f, f/n) and stores them 
    into pairs vector
    
    if howMany is 2, only half the pairs are created
    if howMany is 1, all pairs are created
    */
    void findFactorPairs(int howMany) {

        int howFarBack[pf.size()];
        howFarBack[0] = 1;
        for (int i = 1; i < pf.size(); i++) {
            howFarBack[i] = howFarBack[i - 1] * (pf[i - 1].power + 1);
        }

        //Initial case
        storePair(1, n);

        int justEnough = (numberOfFactors() + 1) / howMany;

        for (int i = 1; i < justEnough; i++) {
            for (int j = pf.size() - 1; j >= 0; j--) {
                if (i % howFarBack[j] == 0) {
                    int f = pairs[i - howFarBack[j]].x * pf[j].prime;
                    storePair(f, n / f);
                    break;
                }
            }
        }

        //order the pairs
        orderPairs();

        //sort the pairs by x element
        std::sort(pairs.begin(), pairs.end());
    }

    /*
    Stores factor pair (a, b) into next open position of pairs
    such that a <= b
    */
    void storePair(int a, int b) {
        Pair fp(a, b);
        pairs.push_back(fp);
    }

    /*
    Swaps pair values if x > y
    */
    void orderPairs() {
        for (int i = 0; i < pairs.size(); i++) {
            if (pairs[i].x > pairs[i].y) {
                int temp = pairs[i].x;
                pairs[i].x = pairs[i].y;
                pairs[i].y = temp;
            }
        }
    }

    /*
    Returns the number of factors of number whose
    prime factorization is pf
    */
    int numberOfFactors() {
        int product = 1;
        for (int i = 0; i < pf.size(); i++) {
            product *= pf[i].power + 1;
        }
        return product;
    }

    /*
    Prints "(pairs[i].a, pairs[i].b)"
    */
    void printPairs() {
        for(int i = 0; i < pairs.size(); i++) {
            cout << i << ": (" << pairs[i].x << ", " << pairs[i].y << ")" << endl;
        }
    }

    /*
    Prints "pf[i].prime^pf[i].power"
    */
    void printFactorization() {
        for(int i = 0; i < pf.size(); i++) {
            cout << pf[i].prime << "^" << pf[i].power << " ";
        }
        cout << endl;
    }

};