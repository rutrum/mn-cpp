int go4Free(Factorization& d) {

    // Initialize variables

    // Define Gi[j] to be the greatest integer in row j+1
    int Gi[12] = {};
    greatestIntegerInRow(d, Gi, 12);

    // Define Li[j] to be the lower bound for array of integers j mod 12
    int Li[12] = {};
    Li[0] = max(max(max(max(max(Gi[0], Gi[1]), Gi[2]), Gi[3]), Gi[5]), Gi[11]);
    Li[1] = Gi[0];
    Li[2] = max(Gi[0], Gi[1]);
    Li[3] = max(Gi[0], Gi[2]);
    Li[4] = max(max(Gi[0], Gi[1]), Gi[3]);
    Li[5] = Gi[0];
    Li[6] = max(max(max(Gi[0], Gi[1]), Gi[2]), Gi[5]);
    Li[7] = Gi[0];
    Li[8] = max(max(Gi[0], Gi[1]), Gi[3]);
    Li[9] = max(Gi[0], Gi[2]);
    Li[10] = max(Gi[0], Gi[1]);
    Li[11] = Gi[0];

    // Define U to be the upper bound of integers in lattice
    int U = (d.pairs.back().x - 1) * (d.pairs.back().y - 1);

    // Define Ai to be the vectorbool of integers i mod 12
    // Note that the +1 is for safety
    boost::dynamic_bitset<> Ai[12];
    for (int i = 0; i < 12; i++) {
        Ai[i].resize((U-Li[i]) / 12 + 1);
    }

    // Initialize the number of free numbers
    int countUnique = 0;
    for (int i = 0; i < 12; i++) {
        countUnique += (Li[i] + i) / 12;
    }
    
    // Initialize lookup table for the number of row/column steps
    int columnStep[12][12] = {
        {1, 12, 6, 4, 3, 12, 2, 12, 3, 4, 6, 12},
        {0, 12, 0, 0, 0, 12, 0, 12, 0, 0, 0, 12},
        {0, 12, 6, 0, 0, 12, 0, 12, 0, 0, 6, 12},
        {0, 12, 0, 4, 0, 12, 0, 12, 0, 4, 0, 12},
        {0, 12, 6, 0, 3, 12, 0, 12, 3, 0, 6, 12},
        {0, 12, 0, 0, 0, 12, 0, 12, 0, 0, 0, 12},
        {0, 12, 6, 4, 0, 12, 2, 12, 0, 4, 6, 12},
        {0, 12, 0, 0, 0, 12, 0, 12, 0, 0, 0, 12},
        {0, 12, 6, 0, 3, 12, 0, 12, 3, 0, 6, 12},
        {0, 12, 0, 4, 0, 12, 0, 12, 0, 4, 0, 12},
        {0, 12, 6, 0, 0, 12, 0, 12, 0, 0, 6, 12},
        {0, 12, 0, 0, 0, 12, 0, 12, 0, 0, 0, 12},
    };

    int rowStep[12][12] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 4, 0, 0, 0, 2, 0, 4, 0, 0, 0, 2},
        {0, 1, 3, 0, 0, 2, 0, 3, 0, 0, 1, 2},
        {0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2},
        {0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2},
        {0, 4, 0, 0, 0, 2, 0, 4, 0, 0, 0, 2},
        {0, 1, 1, 2, 0, 1, 1, 2, 0, 1, 1, 2},
        {0, 4, 0, 0, 0, 2, 0, 4, 0, 0, 0, 2},
        {0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2},
        {0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2},
        {0, 1, 3, 0, 0, 2, 0, 3, 0, 0, 1, 2},
        {0, 4, 0, 0, 0, 2, 0, 4, 0, 0, 0, 2},
    };

    int startRow[12] = {
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5
    };

    // Algorithm

    int totalRows = d.pairs.back().x - 1;

    for (int i = 0; i < 12; i++) {

        for (int row = startRow[i], t = 1; row <= totalRows; 0) {

            while (d.pairs[t].x <= row) {
                t++;
            }

            int start = findStartColumn(Li[i], row, i, 12);

            int cStep = columnStep[i][row % 12];

            int offset = (start * row - Li[i]) % 12;
            for (
                int p = (start * row - Li[i]) / 12;
                p < (d.pairs[t].y * row - Li[i] - offset + 11) / 12;
                p += (row * cStep) / 12
            ) {
                Ai[i][p] = true;
            }

            row += rowStep[i][row % 12];

        }

    }

    for (int i = 0; i < 12; i++) {
        countUnique += Ai[i].count();
    }

    return countUnique;
    
}