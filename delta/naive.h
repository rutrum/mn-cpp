int delta_naive(Factors f) {
    boost::dynamic_bitset<> visited(f.product_bound());

    // r iterates over rows
    // t iterates over pairs
    for (int r = 1, t = 1; r < f.row_bound(); r++) {

        // If row has maxed out pair's shape, go to next pair
        if (r == f.row_bound_on_pair(t)) {
            t++;
        }

        // Scan through entries in the rth row of the table
        for (int p = r * r; p < f.col_bound_on_pair(t) * r; p += r) {
            visited[p] = true;
        }
    }

    return visited.count();
}
