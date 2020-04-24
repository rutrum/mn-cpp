// Finds divisor pairs for all integers in [start, end)
// and stores them into segment
void findSegmentPairs(vector<vector<int> >& segment, int start, int end) {
    segment.resize(end - start);

    // First add trivial pair
    for (int i = 0; i < end - start; i++) {
        segment[i].push_back(1);
        segment[i].push_back(i + start);
    }

    for (int i = 2; i * i < end; i++) {
        int j = i - (start % i);
        if (start % i == 0) {
            j = 0;
        }

        for (j; j < end - start; j += i) {
            // if (start + j < 4) continue; //edge case
            if (i * i > j + start) continue; // avoid repeat pairs
            segment[j].push_back(i);
            segment[j].push_back((j + start) / i);
        }
    }
};
