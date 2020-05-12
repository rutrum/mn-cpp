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

    Factors(int n, vector<pair<int,int>> pairs) {
        this->n = n;
        this->pairs = pairs;
    }

    static Factors all_pairs(int n) {
        auto pairs = vector<pair<int, int>>();
        pairs.push_back(pair<int, int>(1, n));
        for (int i = 2; i <= n; i++) {
            if (n % i == 0) {
                pairs.push_back(pair<int, int>(i, n / i));
            }
        }
        return Factors(n, pairs);
    }

    void print() {
        for (int i = 0; i < pairs.size(); i++) {
            pair<int, int> p = pairs[i];
            cout << p.first << ", " << p.second << endl;
        }
    }

    // Returns factors(n*p) for prime p exploiting the pairs already found for n
    Factors scale(int p) {
        /*
        
        auto merged = vector<pair<int, int>>();

        if (p < n) {
            auto to_add = pair<int,int>(1, n * p);
            int l = 0, r = 0;

            while (to_add.first <= to_add.second) {
                merged.push_back(to_add);

                if (this->pairs[l].first < this->pairs[r].first * p) {
                    auto pr = this->pairs[l];
                    to_add = pair<int,int>(pr.first, pr.second * p);
                    l++;

                } else if (this->pairs[l].first > this->pairs[r].first * p) {
                    auto pr = this->pairs[r];
                    to_add = pair<int,int>(pr.first * p, pr.second);
                    r++;

                } else { // equality
                    auto pr = this->pairs[l];
                    to_add = pair<int,int>(pr.first * p, pr.second);
                    l++;
                    r++;
                }
            }
            cout << "didn't add " << to_add.first << " " << to_add.second << endl;
        } else {
            for (int i = 0; i < this->pairs.size(); i++) {
                auto cur = this->pairs[i];
                auto pr = pair<int, int>(cur.first, cur.second * p);
                merged.push_back(pr);
            }
        }

        return Factors(n*p, merged);
        */
        auto merged = vector<pair<int, int>>();
        merged.reserve(this->num_pairs() * 2);
        if (p <= n) {

            auto to_add = pair<int,int>(1, p);
            int l = 0, r = 1;

            // If first == second, then its the last pair, so we have to break
            while (to_add.first < to_add.second) { 

                merged.push_back(to_add);

                if (this->pairs[l].first * p < this->pairs[r].first) {
                    auto pr = this->pairs[l];
                    to_add = pair<int,int>(pr.first * p, pr.second);
                    l++;
                } else if (this->pairs[l].first * p > this->pairs[r].first) {
                    auto pr = this->pairs[r];
                    to_add = pair<int,int>(pr.first, pr.second * p);
                    r++;
                } else {
                    auto pr = this->pairs[l];
                    to_add = pair<int,int>(pr.first * p, pr.second);
                    l++;
                    r++;
                }
            }
            if (to_add.first == to_add.second) { // Handles when m*p = a^2
                merged.push_back(to_add);
            }
        } else {
            for (int i = 0; i < this->pairs.size(); i++) {
                auto cur = this->pairs[i];
                auto pr = pair<int, int>(cur.first, cur.second * p);
                merged.push_back(pr);
            }
        }

        //merged.pop_back();
        return Factors(n*p, merged);
    }

    Factors stretch_lattice(int p) {
        auto new_pairs = vector<pair<int, int>>();
        for (int i = 0; i < this->pairs.size(); i++) {
            auto new_pair = pair<int,int>(this->pairs[i].first, this->pairs[i].second * p);
            new_pairs.push_back(new_pair);
        }
        return Factors(n*p, new_pairs);
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

    // Maybe there's a better way, maybe there isn't
    int highest_prime() {
        for (int t = pairs.size() - 1; t >= 0; t--) {
            int p = pairs[t].second;
            bool is_prime = true;
            for (int i = 2; i * i <= p; i++) {
                if (p % i == 0) {
                    is_prime = false;
                    break;
                }
            }
            if (is_prime) {
                return p;
            }
        }
        // unreachable
        return 1;
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
    
    // Returns the number of divisor pairs
    int num_pairs() {
        return pairs.size();
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
