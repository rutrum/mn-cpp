uint32_t delta_segmented_modulo_2(Factors f, uint32_t segment_size) {
    uint32_t total_visited = 0;
    uint32_t* row_maxes = f.row_maxes(2);

    // EVENS

    // Lower bound for evens can come from either the first row,
    // or the second row.  Pick the better one.
    uint32_t evens_lb = max(row_maxes[1], row_maxes[2]);
    uint32_t evens_range = f.product_bound() - evens_lb;
    uint32_t evens_size = evens_range / 2 + 1; // Store half the range (no odds)
    boost::dynamic_bitset<> evens_visited(evens_size);

    total_visited += evens_lb / 2; // Free visits!

    // Start from the third row, everything is known about first two
    for (uint32_t r = 3, t = 1; r < f.row_bound(); r++) {

        // If row has maxed out pair's shape, go to next pair
        while (r >= f.row_bound_on_pair(t)) {
            t++;
        }

        // From /util/start_column.h
        uint32_t start = start_column(evens_lb, r, 0, 2);

        // Can we skip columns?
        uint32_t step = 1;
        if (r % 2 == 1) {
            step = 2;  // Odds in this row, we skip those
        }

        // The slow intuitive way:
        /*
            for (int c = start; c < f.col_bound_on_pair(t); c += step) {
                int p = c * r;                  // product
                int i = (p - evens_lb) / 2;     // index after translation and scaling
                evens_visited[i] = true;
            }
        */
        // The quicker way:
        for (int i = (start * r - evens_lb) / 2;
            i < (f.col_bound_on_pair(t) * r - evens_lb) / 2;
            i += (step * r) / 2
        ) {
            evens_visited[i] = true;
        }
    }

    total_visited += evens_visited.count();
    // evens_visited.reset();

    // ODDS

    // Lower bound for odds is the max value of the first row.
    int odds_lb = row_maxes[1];
    int odds_range = f.product_bound() - odds_lb;
    int odds_size = odds_range / 2 + 1; // Store half the range (no evens)
    boost::dynamic_bitset<> odds_visited(odds_size);

    total_visited += (odds_lb + 1) / 2; // Free visits!

    // Start from the third row, everything is known about first two
    // Skip every other row, those are all evens
    for (int r = 3, t = 1; r < f.row_bound(); r += 2) {

        // If row has maxed out pair's shape, go to next pair
        while (r >= f.row_bound_on_pair(t)) {
            t++;
        }

        // From /util/start_column.h
        int start = start_column(odds_lb, r, 1, 2);

        // The slow intuitive way:
        /*
            for (int c = start; c < f.col_bound_on_pair(t); c++) {
                int p = c * r;                 // product
                int i = (p - odds_lb) / 2;     // index after translation and scaling
                odds_visited[i] = true;
            }
        */
        // The quicker way:
        for (int i = (start * r - odds_lb) / 2;
            i < (f.col_bound_on_pair(t) * r - odds_lb) / 2;
            i += r
        ) {
            odds_visited[i] = true;
        }
    }

    total_visited += odds_visited.count();
    //odds_visited.reset();

    delete[] row_maxes;
    return total_visited;
}
