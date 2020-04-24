vector<vector<int>> columnStep;
vector<vector<int>> rowStep;
vector<int> rowStart;
vector<vector<int>> boundPool;
int f;

void initModN(const int n) {

    f = n;
    
    columnStep.resize(n);
    rowStep.resize(n);
    rowStart.resize(n);
    boundPool.resize(n);


    for (int i = 0; i < n; i++) {
        columnStep[i].resize(n);
        rowStep[i].resize(n);
    }

    // COLUMNS

    // First row is trivial
    columnStep[0][0] = 1;

    for (int i = 1; i < n; i++) {
        int gcd = boost::math::gcd(i, n);
        int value = n / gcd;
        for (int j = 0; j < n; j += gcd) {
            // columnStep[i][j] = value;
            columnStep[j][i] = value;
        }
    }

    // ROWS

    // First column, last row are trivial
    for (int i = 0; i < n; i++) {
        // rowStep[i][0] = 1;
        // rowStep[n-1][i] = 2;
        rowStep[0][i] = 1;
        rowStep[i][n-1] = 2;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 2, p = 1; j < n; j++) {
            // if (columnStep[j][i] != 0) {
            //     rowStep[p][i] = j - p;
            //     p = j;
            // }
            if (columnStep[i][j] != 0) {
                rowStep[i][p] = j - p;
                p = j;
            }
        }
    }

    // START

    // Special case for n = 2
    if (n == 2) {
        rowStart[0] = 3;
        rowStart[1] = 3;
    } else {
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < n; j++) {
                // if (rowStep[j][i] != 0) {
                //     rowStart[i] = j;
                //     break;
                // }
                if (rowStep[i][j] != 0) {
                    rowStart[i] = j;
                    break;
                }
            }
        }
    }

    // LOWER BOUND POOL

    // There is a vector corresponding to a remainder mod f, called i
    // that contains all the factors of f that divide i.  These indices
    // are the rows that calculate the lowerbound Li

    Factorization freeFact(n);
    for (int j = 0; j < freeFact.pairs.size(); j++) {
        boundPool[0].push_back(freeFact.pairs[j].x - 1);
        boundPool[0].push_back(freeFact.pairs[j].y - 1);
    }
    for (int i = 1; i < n; i++) {
        // First look at x values
        for (int j = 0; j < freeFact.pairs.size(); j++) {
            if (i % freeFact.pairs[j].x == 0) {
                boundPool[i].push_back(freeFact.pairs[j].x - 1);
            }
            if (i % freeFact.pairs[j].y == 0) {
                boundPool[i].push_back(freeFact.pairs[j].y - 1);
            }
        }
    }
}

int goModN(Factorization& d) {

    // Initialize variables

    // Define Gi[j] to be the greatest integer in row j+1
    int Gi[f] = {};
    greatestIntegerInRow(d, Gi, f);

    // Define Li[j] to be the lower bound for array of integers j mod f
    int Li[f] = {};
    
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < boundPool[i].size(); j++) {
            Li[i] = max(Li[i], Gi[boundPool[i][j]]);
        }
    }

    // Define U to be the upper bound of integers in lattice
    int U = (d.pairs.back().x - 1) * (d.pairs.back().y - 1);

    // Define Ai to be the vectorbool of integers i mod f
    // Note that the +1 is for safety
    boost::dynamic_bitset<> Ai[f];
    for (int i = 0; i < f; i++) {
        Ai[i].resize((U-Li[i]) / f + 1);
    }

    // Initialize the number of free numbers
    int countUnique = 0;
    for (int i = 0; i < f; i++) {
        countUnique += (Li[i] + i) / f;
    }

    // Algorithm

    int totalRows = d.pairs.back().x - 1;
    long totalProducts = 0;

    for (int i = 0; i < f; i++) {

        for (int row = rowStart[i], t = 1; row <= totalRows; 0) {

            while (d.pairs[t].x <= row) {
                t++;
            }

            int start = findStartColumn(Li[i], row, i, f);

            int cStep = columnStep[i][row % f];

            int offset = (start * row - Li[i]) % f;
            for (
                int p = (start * row - Li[i]) / f;
                p < (d.pairs[t].y * row - Li[i] - offset + f - 1) / f;
                p += (row * cStep) / f
            ) {
                totalProducts += 1;
                // Ai[i][p] = true;
            }

            int rStep = rowStep[i][row % f];
            row += rStep;

        }

    }

    // this breaks it
    return totalProducts;

    for (int i = 0; i < f; i++) {
        countUnique += Ai[i].count();
    }

    return countUnique;
    
}