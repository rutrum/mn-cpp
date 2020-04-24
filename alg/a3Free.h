int go3Free(Factorization& d) {

    // Initialize variables

    // Define Gi[j] to be the greatest integer in row j+1
    int Gi[6] = {};
    greatestIntegerInRow(d, Gi, 6);

    // Define Li[j] to be the lower bound for array of integers j mod 6
    int Li[6] = {};
    Li[0] = max(max(max(Gi[0], Gi[1]), Gi[2]), Gi[5]);
    Li[1] = Gi[0];
    Li[2] = max(Gi[0], Gi[1]);
    Li[3] = max(Gi[0], Gi[2]);
    Li[4] = max(Gi[0], Gi[1]);
    Li[5] = Gi[0];

    // Define U to be the upper bound of integers in lattice
    int U = (d.pairs.back().x - 1) * (d.pairs.back().y - 1);

    // Define Ai to be the vectorbool of integers i mod 6
    // Note that the +1 is for safety
    boost::dynamic_bitset<> Ai[6];
    for (int i = 0; i < 6; i++) {
        Ai[i].resize((U-Li[i]) / 6 + 1);
    }

    // Initialize the number of free numbers
    int countUnique = 0;
    for (int i = 0; i < 6; i++) {
        countUnique += (Li[i] + i) / 6;
    }
    
    // Initialize lookup table for the number of row/column steps
    int columnStep[6][6] = {
        {1, 6, 3, 2, 3, 6},
        {0, 6, 0, 0, 0, 6},
        {0, 6, 3, 0, 3, 6},
        {0, 6, 0, 2, 0, 6},
        {0, 6, 3, 0, 3, 6},
        {0, 6, 0, 0, 0, 6}
    };

    int rowStep[6][6] = {
        {1, 1, 1, 1, 1, 1},
        {0, 4, 0, 0, 0, 2},
        {0, 1, 2, 0, 1, 2},
        {0, 2, 0, 2, 0, 2},
        {0, 1, 2, 0, 1, 2},
        {0, 4, 0, 0, 0, 2}
    };

    int startRow[6] = {
        4, 5, 4, 5, 4, 5
    };

    // Algorithm

    int totalRows = d.pairs.back().x - 1;

    for (int i = 0; i < 6; i++) {

        for (int row = startRow[i], t = 1; row <= totalRows; 0) {

            while (d.pairs[t].x <= row) {
                t++;
            }

            const int start = findStartColumn(Li[i], row, i, 6);

            const int cStep = columnStep[i][row % 6];

            const int offset = (start * row - Li[i]) % 6;
            
            for (
                int p = (start * row - Li[i]) / 6;
                p < (d.pairs[t].y * row - Li[i] - offset + 5) / 6;
                p += (row * cStep) / 6
            ) {
                Ai[i][p] = true;
            }

            row += rowStep[i][row % 6];

        }

    }

    for (int i = 0; i < 6; i++) {
        countUnique += Ai[i].count();
    }

    return countUnique;
    
}