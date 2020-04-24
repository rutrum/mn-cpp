int go2Free(Factorization& d) {

    // Initialize variables

    // Determine start
    int Gi[2] = {};
    greatestIntegerInRow(d, Gi, 2);

    int Li[2] = {};
    Li[0] = max(Gi[0], Gi[1]); // Evens
    Li[1] = Gi[0]; // Odds

    // Determine end
    int U = (d.pairs.back().x - 1) * (d.pairs.back().y - 1);

    boost::dynamic_bitset<> uniqueEvens((U - Li[0]) / 2 + 1);
    boost::dynamic_bitset<> uniqueOdds((U - Li[1]) / 2 + 1);

    // Initialize countUnique
    int countUnique 
            = (Li[1] + 1) / 2 // Really ceil(Li[1] / 2) but not really
            + Li[0] / 2;

    // Algorithm

    int totalRows = d.pairs.back().x - 1;

    // Determine values in the evens array
    for (int row = 3, t = 1; row <= totalRows; row++) {

        while (d.pairs[t].x <= row) {
            t++;
        }

        int start = findStartColumn(Li[0], row, 0, 2);

        int step = 1;
        int mod = row % 2;
        if (mod == 1) {
            step = 2; // We can skip odds
        }

        for (
            int p = (start * row - Li[0]) / 2; 
            p < (d.pairs[t].y * row - Li[0]) / 2; 
            p += (row * step) / 2
        ) {
            uniqueEvens[p] = true;
        }
    }

    // Determine values in the odds array
    for (int row = 3, t = 1; row <= totalRows; row += 2) {

        while (d.pairs[t].x <= row) {
            t++;
        }

        int start = findStartColumn(Li[1], row, 1, 2);

        for (
            int p = (start * row - Li[1]) / 2; 
            p < (d.pairs[t].y * row - Li[1]) / 2; 
            p += row
        ) {
            uniqueOdds[p] = true;
        }

    }

    countUnique += uniqueEvens.count() + uniqueOdds.count();

    return countUnique;

}