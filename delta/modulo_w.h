// Some function that creates the classes of coordinates
vector<vector<pair<int, int>>> classify_coords(int w) {
    vector<vector<pair<int,int>>> classes;
    classes.resize(w);

    for (int r = 0; r < w; r++) {
        for (int c = 0; c < w; c++) {
            classes[r * c % w].push_back(pair<int,int>(r,c));
        }
    }

    return classes;
}

int delta_modulo_w(Factors f, int w, vector<vector<pair<int,int>>> classes) {
    uint64_t total_visited = 0;

    // Determine coordinates based on the modulus and then
    // determine the lower bounds of each vector
    // auto classes = classify_coords(w);
    auto lower_bounds = f.mod_class_lower_bounds(w);

    // m is the modulus
    for (int m = 0; m < classes.size(); m++) {

        uint64_t visited_range = f.product_bound() - lower_bounds[m];
        uint64_t visited_size = visited_range / w + 1;
        boost::dynamic_bitset<> visited(visited_size);

        // Free stuff!
        // Each modulus only gets 1/wth the lower_bound, because each
        // vector stores only 1/wth the products;  Add m for mod 0 case.
        total_visited += (lower_bounds[m] + m) / w;  

        // p is the index of the coordinate
        for (int p = 0; p < classes[m].size(); p++) {
            pair<int,int> coords = classes[m][p];

            // The starting row.  We could skip the first few here.
            uint64_t row_start = coords.second == 0 ? w : coords.second;

            for (uint64_t r = row_start, t = 1; r < f.row_bound(); r += w) {
                
                while (r >= f.row_bound_on_pair(t)) {
                    t++;
                }

                // Start on the coordinate point, and increment by w
                // until passed the row number (we only scan the lower half)
                // and passed the lower bound, we get those for free already
                uint64_t start = coords.first;
                while (start < r || start <= lower_bounds[m] / r) start += w;

                // The slow intuitive way:
                    for (uint64_t c = start; c < f.col_bound_on_pair(t); c += w) {
                        int p = c * r;                      // product
                        int i = (p - lower_bounds[m]) / w;  // index after translation and scaling
                        visited[i] = true;
                    }
                /*
                    for (int p = start * r; p < f.col_bound_on_pair(t) * r; p += w * r) {
                        int i = (p - lower_bounds[m]) / w;  // index after translation and scaling
                        visited[i] = true;
                    }
                */
                /*
                    for (int p = start * r - lower_bounds[m]; 
                        p < f.col_bound_on_pair(t) * r - lower_bounds[m]; 
                        p += w * r
                    ) {
                        int i = p / w;  // index after scaling
                        visited[i] = true;
                    }
                */
                // The quicker way:
                
                // Need to figure out why this works
                /*
                uint64_t offset = (start * r - lower_bounds[m]) % w;

                for (uint64_t i = (start * r - lower_bounds[m]) / w; 
                    i < ((uint64_t)f.col_bound_on_pair(t) * r - lower_bounds[m] - offset + w - 1) / w; 
                    i += r 
                ) {
                    visited[i] = true;
                }
                */
            }
        }

        total_visited += visited.count();
    }

    return total_visited;
}
