int delta_modulo_2(Factors f) {
    int total_visited = 0;
    int* row_maxes = f.row_maxes(2);

    // EVENS

    // Lower bound for evens can come from either the first row,
    // or the second row.  Pick the better one.
    int evens_max = max(row_maxes[1], row_maxes[2]);
    int evens_range = f.product_bound() - evens_max;
    int evens_size = evens_range / 2 + 1; // Store half the range (no odds)
    boost::dynamic_bitset<> evens_visited(evens_size);

    total_visited += evens_max / 2; // Free visits!

    // Start from the third row, everything is known about first two
    for (int r = 3, t = 1; r < f.row_bound(); r++) {

        // If row has maxed out pair's shape, go to next pair
        while (r >= f.row_bound_on_pair(t)) {
            t++;
        }

        // From /util/start_column.h
        int start = start_column(evens_max, r, 0, 2);

        // Initialize bounds
        uint64_t row_squared_bound = r * r + (2 * r - r * r % (r * 2)); // Might be broken
        uint64_t free_bound = evens_max + (2 * r - evens_max % (r * 2)); // Might be broken

        uint64_t p_start = row_squared_bound;
        if (p_start < free_bound) p_start = free_bound;

        uint64_t p_end = f.col_bound_on_pair(t) * r;

        cout << "evens_max " << evens_max << endl;
        cout << "r^2 " << row_squared_bound << endl;
        cout << "free " << free_bound << endl;
        cout << "pstart " << p_start << endl;

        // Can we skip columns?
        //int step = r % 2 + 1;
        int step = 1;
        if (r % 2 == 1) {
            step = 2;  // Odds in this row, we skip those
        }

        // The slow intuitive way:
            for (int p = p_start; p < p_end; p += step * r) {
                cout << p << endl;
                int i = (p - evens_max) / 2;     // index after translation and scaling
                evens_visited[i] = true;
            }
        /*
        // The quicker way:
        for (int i = (p_start - evens_max) / 2;
            i < (p_end - evens_max) / 2;
            i += (step * r) / 2
        ) {
            cout << i << endl;
            evens_visited[i] = true;
        }
        */
    }

    total_visited += evens_visited.count();
    // evens_visited.reset();

    // ODDS

    // Lower bound for odds is the max value of the first row.
    int odds_max = row_maxes[1];
    int odds_range = f.product_bound() - odds_max;
    int odds_size = odds_range / 2 + 1; // Store half the range (no evens)
    boost::dynamic_bitset<> odds_visited(odds_size);

    total_visited += (odds_max + 1) / 2; // Free visits!

    // Start from the third row, everything is known about first two
    // Skip every other row, those are all evens
    for (int r = 3, t = 1; r < f.row_bound(); r += 2) {

        // If row has maxed out pair's shape, go to next pair
        while (r >= f.row_bound_on_pair(t)) {
            t++;
        }

        // From /util/start_column.h
        int start = start_column(odds_max, r, 1, 2);

        // Initialize bounds
        uint64_t row_squared_bound = r * r;
        uint64_t free_bound = odds_max + 1 + (r - (odds_max + 1) % r); // This is broken

        uint64_t p_start = row_squared_bound;
        if (p_start < free_bound) p_start = free_bound;

        uint64_t p_end = f.col_bound_on_pair(t) * r;

        cout << "odds_max " << odds_max << endl;
        cout << "r^2 " << row_squared_bound << endl;
        cout << "free " << free_bound << endl;
        cout << "pstart " << p_start << endl;
        cout << "pend " << p_end << endl;

        // The slow intuitive way:
            for (int p = p_start; p < p_end; p += 2 * r) {
                cout << p << endl;
                int i = (p - odds_max) / 2;     // index after translation and scaling
                odds_visited[i] = true;
            }
        /*
        // The quicker way:
        for (int i = (p_start - odds_max) / 2;
            i < (p_end - odds_max) / 2;
            i += r
        ) {
            cout << i << endl;
            odds_visited[i] = true;
        }
        */
        cout << endl;
    }

    total_visited += odds_visited.count();
    //odds_visited.reset();

    delete[] row_maxes;
    return total_visited;
}
