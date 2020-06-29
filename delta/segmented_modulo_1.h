uint32_t delta_segmented_modulo_1(Factors f, uint64_t segment_size) {

    // prime check...may remove, but will segfault on primes
    if (f.is_prime()) {
        return 0;
    }

    uint32_t first_row_max = f.col_bound_on_pair(1) - 1;

    // The number of free integers from first row
    uint64_t total_free = first_row_max;

    // Now position 0 refers to first row max + 1, the smallest 
    // product we will calculate
    boost::dynamic_bitset<> visited(f.product_bound() - first_row_max);

    for (uint64_t start = first_row_max; start < f.product_bound(); start += segment_size) {
        uint64_t end = start + segment_size;
        if (end >= f.product_bound()) end = f.product_bound();

        // r iterates over rows
        // t iterates over pairs
        for (uint32_t r = 2, t = 1; r < f.row_bound(); r++) {

            // If row has maxed out pair's shape, go to next pair
            if (r == f.row_bound_on_pair(t)) {
                t++;
            }

            // Initialize product start and end based on shape bounds
            // and bounds from the segment size.  Note that
            // (r - (start % r)) % r is the modular additive inverse of start
            uint64_t lower_segment_bound = start + (r - start % r) % r;
            uint64_t row_squared_bound = r * r;
            uint64_t free_bound = first_row_max + (r - first_row_max % r);

            uint64_t p_start = lower_segment_bound;
            if (p_start < free_bound) p_start = free_bound;
            if (p_start < row_squared_bound) p_start = row_squared_bound;

            uint64_t upper_segment_bound = end;
            uint64_t shape_bound = f.col_bound_on_pair(t) * r;

            uint64_t p_end = upper_segment_bound;
            if (p_end > shape_bound) p_end = shape_bound; 

            // Slow intuitive way
            /*
                for (uint64_t p = p_start; p < p_end; p += r) {
                    uint64_t i = p - first_row_max;
                    visited[i] = true;
                }
            */
            // Faster way
            // i is signed (as well as p_end and first_row_max) because of the substraction
            // p_end - first_row_max overflows positive when you shouldnt
            if (p_end > first_row_max && p_start > first_row_max) {
                for (uint64_t i = p_start - first_row_max; i < p_end - first_row_max; i += r) {
                    visited[i] = true;
                }
            }

        }
        //sum += visited.count();
    }

    //return sum + total_free;
    return total_free + visited.count();
}
