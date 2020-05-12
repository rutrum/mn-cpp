uint32_t delta_segmented_naive(Factors f, uint64_t segment_size) {

    boost::dynamic_bitset<> visited(f.product_bound());

    // Start and end define the bounds of the segment; end is exclusive
    for (uint64_t start = 0; start < f.product_bound(); start += segment_size) {
        uint64_t end = start + segment_size;
        if (end >= f.product_bound()) end = f.product_bound();

        // r iterates over rows
        // t iterates over pairs
        // Opportunity to improve: skip rows that only have products less than start
        for (uint64_t r = 1, t = 1; r < f.row_bound(); r++) {

            // If row has maxed out pair's shape, go to next pair
            if (r == f.row_bound_on_pair(t)) {
                t++;
            }

            // Initialize product start and end based on shape bounds
            // and bounds from the segment size.  Note that
            // (r - (start % r)) % r is the modular additive inverse of start
            uint64_t p_start = start + (r - start % r) % r;
            // Check if smaller than diagonal
            if (p_start < r * r) p_start = r * r;

            uint64_t p_end = end;
            // Check if end surpasses shape bound
            if (p_end > f.col_bound_on_pair(t) * r) p_end = f.col_bound_on_pair(t) * r; 

            // Scan through entries in the rth row of the table
            // Only catch products between start and end
            for (uint64_t p = p_start; p < p_end; p += r) {
                visited[p] = true;
            }
        }
    }

    return visited.count();
}

uint32_t delta_segmented_naive_save(Factors f, uint64_t segment_size, boost::dynamic_bitset<> &visited) {

    // Start and end define the bounds of the segment; end is exclusive
    for (uint64_t start = 0; start < f.product_bound(); start += segment_size) {
        uint64_t end = start + segment_size;
        if (end >= f.product_bound()) end = f.product_bound();

        // r iterates over rows
        // t iterates over pairs
        // Opportunity to improve: skip rows that only have products less than start
        for (uint64_t r = 1, t = 1; r < f.row_bound(); r++) {

            // If row has maxed out pair's shape, go to next pair
            if (r == f.row_bound_on_pair(t)) {
                t++;
            }

            // Initialize product start and end based on shape bounds
            // and bounds from the segment size.  Note that
            // (r - (start % r)) % r is the modular additive inverse of start
            uint64_t p_start = start + (r - start % r) % r;
            // Check if smaller than diagonal
            if (p_start < r * r) p_start = r * r;

            uint64_t p_end = end;
            // Check if end surpasses shape bound
            if (p_end > f.col_bound_on_pair(t) * r) p_end = f.col_bound_on_pair(t) * r; 

            // Scan through entries in the rth row of the table
            // Only catch products between start and end
            for (uint64_t p = p_start; p < p_end; p += r) {
                visited[p] = true;
            }
        }
    }

    return visited.count();
}
