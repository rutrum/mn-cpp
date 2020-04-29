// Some function that creates the classes of coordinates
vector<vector<pair<int, int>>> classify_coords(int N) {
    vector<vector<pair<int,int>>> classes;
    classes.resize(N);

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            classes[r * c % N].push_back(pair<int,int>(r,c));
        }
    }

    return classes;
}

int delta_moduloN(Factors f, int N, vector<vector<pair<int,int>>> classes) {
    int total_visited = 0;

    // Determine coordinates based on the modulus and then
    // determine the lower bounds of each vector
    // auto classes = classify_coords(N);
    auto lower_bounds = f.mod_class_lower_bounds(N);

    // m is the modulus
    for (int m = 0; m < classes.size(); m++) {

        int visited_range = f.product_bound() - lower_bounds[m];
        int visited_size = visited_range / N + 1;
        boost::dynamic_bitset<> visited(visited_size);

        // Free stuff!
        // Each modulus only gets 1/Nth the lower_bound, because each
        // vector stores only 1/Nth the products
        total_visited += (lower_bounds[m] + m) / N;  

        // p is the index of the coordinate
        for (int p = 0; p < classes[m].size(); p++) {
            pair<int,int> coords = classes[m][p];

            // The starting row.  We could skip the first few here.
            int row_start = coords.second == 0 ? N : coords.second;

            for (int r = row_start, t = 1; r < f.row_bound(); r += N) {
                
                while (r >= f.row_bound_on_pair(t)) {
                    t++;
                }

                // Start on the coordinate point, and increment by N
                // until passed the row number (we only scan the lower half)
                // and passed the lower bound, we get those for free already
                int start = coords.first;
                while (start < r || start <= lower_bounds[m] / r) start += N;

                // The slow intuitive way:
                /*
                    for (int c = start; c < f.col_bound_on_pair(t); c += N) {
                        int p = c * r;                      // product
                        int i = (p - lower_bounds[m]) / N;  // index after translation and scaling
                        visited[i] = true;
                    }
                    for (int p = start * r; p < f.col_bound_on_pair(t) * r; p += N * r) {
                        int i = (p - lower_bounds[m]) / N;  // index after translation and scaling
                        visited[i] = true;
                    }
                    for (int p = start * r - lower_bounds[m]; 
                        p < f.col_bound_on_pair(t) * r - lower_bounds[m]; 
                        p += N * r
                    ) {
                        int i = p / N;  // index after translation and scaling
                        visited[i] = true;
                    }
                */
                // The quicker way:
                
                // Need to figure out why this works
                int offset = (start * r - lower_bounds[m]) % N;

                for (int i = (start * r - lower_bounds[m]) / N; 
                    i < (f.col_bound_on_pair(t) * r - lower_bounds[m] - offset + N - 1) / N; 
                    i += r 
                ) {
                    visited[i] = true;
                }
            }
        }

        total_visited += visited.count();
    }

    return total_visited;
}
