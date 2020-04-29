int delta_modulo1(Factors f) {

    // prime check...may remove, but will segfault on primes
    if (f.is_prime()) {
        return 0;
    }

    int first_row_max = f.col_bound_on_pair(1) - 1;

    // The number of free integers from first row
    int total_free = first_row_max;

    // Now position 0 refers to first row max + 1, the smallest 
    // product we will calculate
    boost::dynamic_bitset<> visited(f.product_bound() - first_row_max);

    // r iterates over rows
    // t iterates over pairs
    for (int r = 2, t = 1; r < f.row_bound(); r++) {

        // If row has maxed out pair's shape, go to next pair
        if (r == f.row_bound_on_pair(t)) {
            t++;
        }

        // Row will either start at r (as in naive algorithm)
        // or it go to the column greater whose product is greater
        // than r * r.
        int col_lb = max(r, first_row_max / r + 1);

        // Scan through entries in the rth row of the table,
        // offset by first_row_max for indexing into uniques
        // Alternatively it could be written this way, its just slower:
        /*
            for (int c = col_lb; c < f.col_bound_on_pair(t); c++) {
                int p = c * r;                  // product
                int i = p - first_row_max;      // index into array
                uniques[i] = true;
            }
        */
        for (int i = col_lb * r - first_row_max; 
            i < f.col_bound_on_pair(t) * r - first_row_max; 
            i += r
        ) {
            visited[i] = true;
        }
    }

    return total_free + visited.count();
}
