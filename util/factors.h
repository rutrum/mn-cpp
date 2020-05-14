using namespace std;

class Factors {

    // Stores all divisors pairs where the
    // first element is greater. (row, column)
    vector<pair<uint32_t, uint32_t>> pairs;

public:

    uint32_t n;

    Factors(uint32_t n) {
        this->n = n;
        pairs.push_back(pair<uint32_t, uint32_t>(1, n));
        for (uint32_t i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                pairs.push_back(pair<uint32_t, uint32_t>(i, n / i));
            }
        }
    }

    Factors(uint32_t n, vector<pair<uint32_t,uint32_t>> pairs) {
        this->n = n;
        this->pairs = pairs;
    }

    static Factors all_pairs(uint32_t n) {
        auto pairs = vector<pair<uint32_t, uint32_t>>();
        pairs.push_back(pair<uint32_t, uint32_t>(1, n));
        for (uint32_t i = 2; i <= n; i++) {
            if (n % i == 0) {
                pairs.push_back(pair<uint32_t, uint32_t>(i, n / i));
            }
        }
        return Factors(n, pairs);
    }

    void print() const {
        for (uint32_t i = 0; i < pairs.size(); i++) {
            pair<uint32_t, uint32_t> p = pairs[i];
            cout << p.first << ", " << p.second << endl;
        }
    }

    // Returns factors(n*p) for prime p exploiting the pairs already found for n
    Factors scale(uint32_t p) const {
        auto merged = vector<pair<uint32_t, uint32_t>>();
        merged.reserve(this->num_pairs());
        if (p <= n) {

            auto to_add = pair<uint32_t,uint32_t>(1, p);
            uint32_t l = 0, r = 1;

            // If first == second, then its the last pair, so we have to break
            while (to_add.first < to_add.second) { 

                merged.push_back(to_add);

                if (this->pairs[l].first * p < this->pairs[r].first) {
                    auto pr = this->pairs[l];
                    to_add = pair<uint32_t,uint32_t>(pr.first * p, pr.second);
                    l++;
                } else if (this->pairs[l].first * p > this->pairs[r].first) {
                    auto pr = this->pairs[r];
                    to_add = pair<uint32_t,uint32_t>(pr.first, pr.second * p);
                    r++;
                } else {
                    auto pr = this->pairs[l];
                    to_add = pair<uint32_t,uint32_t>(pr.first * p, pr.second);
                    l++;
                    r++;
                }
            }
            if (to_add.first == to_add.second) { // Handles when m*p = a^2
                merged.push_back(to_add);
            }
        } else {
            for (uint32_t i = 0; i < this->pairs.size(); i++) {
                auto cur = this->pairs[i];
                auto pr = pair<uint32_t, uint32_t>(cur.first, cur.second * p);
                merged.push_back(pr);
            }
        }

        return Factors(n*p, move(merged));
    }

    Factors stretch_lattice(uint32_t p) const {
        auto new_pairs = vector<pair<uint32_t, uint32_t>>();
        for (uint32_t i = 0; i < this->pairs.size(); i++) {
            auto new_pair = pair<uint32_t,uint32_t>(this->pairs[i].first, this->pairs[i].second * p);
            new_pairs.push_back(new_pair);
        }
        return Factors(n*p, new_pairs);
    }

    bool is_prime() const {
        return pairs.size() == 1;
    }

    uint32_t row_bound_on_pair(uint32_t t) const {
        return pairs[t].first;
    }

    uint32_t col_bound_on_pair(uint32_t t) const {
        return pairs[t].second;
    }

    // Maybe there's a better way, maybe there isn't
    uint32_t highest_prime() const {
        for (uint32_t t = pairs.size() - 1; t >= 0; t--) {
            uint32_t p = pairs[t].second;
            bool is_prime = true;
            for (uint32_t i = 2; i * i <= p; i++) {
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
    uint32_t product_bound() const {
        pair<uint32_t, uint32_t> p = pairs.back();
        return (p.first - 1) * (p.second - 1) + 1;
    }

    // The bound on the number of rows in the shape
    uint32_t row_bound() const {
        return pairs.back().first;
    }
    
    // Returns the number of divisor pairs
    uint32_t num_pairs() const {
        return pairs.size();
    }

    // Populates an array with the max of each row within
    // the shape formed by the factorization.
    // Stops after `total` rows.
    // Will calculate maxes for the "full" shape, not just the bottom half.
    uint32_t* row_maxes(uint32_t total) const {
        uint32_t* maxes = new uint32_t[total + 1];
        uint32_t r = 1; // Current row
        
        for (uint32_t t = 0; t < pairs.size() && r <= total; t++) {
            // If r hasn't reached the row bound on the tth pair
            if (r < pairs[t].first) {
                maxes[r] = (pairs[t].second - 1) * r;
                r++;
                t--; // Stay on the same pair
            }
        }

        // Now loop backwards in case the rest of the shape is needed,
        // when the row < col
        for (uint32_t t = pairs.size() - 1; t >= 0 && r <= total; t--) {
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
    // modulus.  That is, the last uint32_teger in each modulo class
    // that is "free".
    vector<uint32_t> mod_class_lower_bounds(uint32_t N) const {
        auto maxes = this->row_maxes(N);

        vector<uint32_t> lower_bounds(N);
    
        // For modulus = 0, check divisibilty of N
        for (uint32_t d = 1; d <= N; d++) {
            if (N % d == 0) {
                lower_bounds[0] = max(lower_bounds[0], maxes[d]);
            }
        }

        // Check divisibility of remainders 1..(N-1)
        for (uint32_t i = 1; i < N; i++) {
            for (uint32_t d = 1; d <= i; d++) {
                if (N % d == 0 && i % d == 0) {
                    lower_bounds[i] = max(lower_bounds[i], maxes[d]);
                }
            }
        }

        return lower_bounds;
    }

private:

};
