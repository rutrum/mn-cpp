// Algorithm 3
// Records in visited the products between last and next lattices
void visit_between_shapes(uint32_t &hamming, boost::dynamic_bitset<> &visited, Factors last, Factors next) {
    for (uint32_t r = 1, t = 0; r < last.row_bound(); r++) {
        
        while (r >= last.row_bound_on_pair(t)) {
            t++;
        }

        // Slower, uint32_tuitive way:
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
        for (uint32_t p = r * last.col_bound_on_pair(t); p < r * next.col_bound_on_pair(t); p += r) {
            if (!visited[p]) {
                visited[p] = true;
                hamming++;
            }
        }
    }
}

// Fails when m = 0 because of the way primes are fetched
void deltas_shift(uint32_t m, uint64_t max, Sieve sieve, uint32_t deltas[]) {

    boost::dynamic_bitset<> visited(max + 1);
    
    // Find the shape of m and its initial delta(m) value
    Factors mf = Factors::all_pairs(m);
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
        next = mf.stretch_lattice(next_prime);

        visit_between_shapes(hamming, visited, last, next);

        deltas[next_prime] = hamming;

        last_prime = next_prime;
        next_prime = sieve.next_prime(last_prime);
    }
}
