// Algorithm 3
// But improved!
void visit_between_distinct_shapes(uint32_t &hamming, boost::dynamic_bitset<> &visited, Factors last, Factors next) {
    // t walks through last
    // s walks through next
    for (uint32_t r = 1, t = 0, s = 0; r < next.row_bound(); r++) {
        
        if (t < last.num_pairs() && r >= last.row_bound_on_pair(t)) {
            t++;
        }

        while (r >= next.row_bound_on_pair(s)) {
            s++;
        }

        uint32_t p_end = r * next.col_bound_on_pair(s);

        uint32_t row_squared_bound = r * r;
        uint32_t inner_shape_bound = 1;
        if (t < last.num_pairs()) {
            inner_shape_bound = r * last.col_bound_on_pair(t);
        }

        uint32_t p_start = inner_shape_bound;
        if (p_start < row_squared_bound && row_squared_bound < p_end) p_start = row_squared_bound;

        // Slower, intuitive way:
        /*
            for (uint32_t c = last.col_bound_on_pair(t); c < next.col_bound_on_pair(t); c++) {
                uint32_t p = c * r;
                if (!visited[p]) {
                    visited[p] = true;
                    hamming++;
                }
            }
        */
        // Faster way:
        for (uint32_t p = p_start; p < p_end; p += r) {
            if (!visited[p]) {
                visited[p] = true;
                hamming++;
            }
        }
    }
}

// Fails when m = 0 because of the way primes are fetched
void deltas_early_shift(uint32_t m, uint64_t max, Sieve sieve, uint32_t deltas[]) {

    boost::dynamic_bitset<> visited(max + 1);
    
    // Find the shape of m and its initial delta(m) value
    Factors mf = Factors(m);
    uint32_t hamming = delta_naive_save(mf, visited);
    deltas[1] = hamming;
    
    // Set default values for first iteration of loop
    uint32_t last_prime = 1;
    uint32_t next_prime = 2;

    Factors next = mf;
    Factors last = mf;

    // Continue until we max out
    while (next_prime > 0 && next_prime * m <= max) {

        last = next;
        next = Factors(m * next_prime);

        visit_between_distinct_shapes(hamming, visited, last, next);

        deltas[next_prime] = hamming;

        last_prime = next_prime;
        next_prime = sieve.next_prime(last_prime);
    }
}
