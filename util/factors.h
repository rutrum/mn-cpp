using namespace std;

class Factors {

    // Stores all divisors pairs where the
    // first element is greater. (row, column)
    vector<pair<int, int>> pairs;

public:

    int n;

    Factors(int n) {
        this->n = n;
        pairs.push_back(pair<int, int>(1, n));
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                pairs.push_back(pair<int, int>(i, n / i));
            }
        }
    }

    void print() {
        for (int i = 0; i < pairs.size(); i++) {
            pair<int, int> p = pairs[i];
            cout << p.first << ", " << p.second << endl;
        }
    }

    bool is_prime() {
        return pairs.size() == 1;
    }

    int row_bound_on_pair(int t) {
        return pairs[t].first;
    }

    int col_bound_on_pair(int t) {
        return pairs[t].second;
    }

    // One more than the highest product within the shape
    int product_bound() {
        pair<int, int> p = pairs.back();
        return (p.first - 1) * (p.second - 1) + 1;
    }

    // The bound on the number of rows in the shape
    int row_bound() {
        return pairs.back().first;
    }

    // Populates an array with the max of each row within
    // the shape formed by the factorization.
    // Stops after `total` rows.
    // Will calculate maxes for the "full" shape, not just the bottom half.
    int* row_maxes(int total) {
        int* maxes = new int[total + 1];
        int r = 1; // Current row
        
        for (int t = 0; t < pairs.size() && r <= total; t++) {
            // If r hasn't reached the row bound on the tth pair
            if (r < pairs[t].first) {
                maxes[r] = (pairs[t].second - 1) * r;
                r++;
                t--; // Stay on the same pair
            }
        }

        // Now loop backwards in case the rest of the shape is needed,
        // when the row < col
        for (int t = pairs.size() - 1; t >= 0 && r <= total; t--) {
            // If r hasn't reached the row bound on the tth pair
            if (r < pairs[t].second) {
                maxes[r] = (pairs[t].first - 1) * r;
                r++;
                t++; // Stay on the same pair
            }
        }

        // Pad unfilled rows with zeros
        while (r <= total) {
            maxes[r] = 0;
            r++;
        }

        return maxes;
    }

    // Given a modulus N, find the lower bound of each
    // modulus.  That is, the last integer in each modulo class
    // that is "free".
    vector<int> mod_class_lower_bounds(int N) {
        auto maxes = this->row_maxes(N);

        vector<int> lower_bounds(N);
    
        // For modulus = 0, check divisibilty of N
        for (int d = 1; d <= N; d++) {
            if (N % d == 0) {
                lower_bounds[0] = max(lower_bounds[0], maxes[d]);
            }
        }

        // Check divisibility of remainders 1..(N-1)
        for (int i = 1; i < N; i++) {
            for (int d = 1; d <= i; d++) {
                if (N % d == 0 && i % d == 0) {
                    lower_bounds[i] = max(lower_bounds[i], maxes[d]);
                }
            }
        }

        return lower_bounds;
    }

private:

};
