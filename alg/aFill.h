// Algorithm 4
static int fillDiff(Factorization& Dw, Factorization& Dc, vector<bool>& A) {
    int dw = 0, dc = 0;
    int lw = Dw.pairs.size(), lc = Dc.pairs.size();
    set<int> S;
    while (dc < lc) {
        if (dw < lw && Dw.pairs[dw].x == Dc.pairs[dc].x) {
            dw++;
            dc++;
        } else {
            for (int i = Dc.pairs[dc - 1].x; i < Dc.pairs[dc].x; i++) {
                int js;
                if (dw == lw) {
                    js = i;
                } else {
                    js = Dw.pairs[dw].y;
                }
                for (int j = js; j < Dc.pairs[dc].y; j++) {
                    if (A[i * j] == 0) {
                        S.insert(i * j);
                    }
                }
            }
            dc++;
        }
    }
    return S.size();
}

void goFill(int m, int max, vector<int>& weights, int b) {
    
    vector<bool> A; // bit vector to store unique integers
    A.resize(max + 1);
    int w = 0; // hamming weight of A

    Factorization base(m);
    int x = base.numberOfFactors();

    // This next part is a mess I know; trying to fix dumb stuff
    int p = b;
    Factorization initial(1);
    while (true) {
        p++;
        if (m * p > max) {
            // cout << p << endl;
            return;
        }
        initial = Factorization(m * p);
        if ((initial.numberOfFactors() + 1) / 2 == x) {
            break;
        }
    }
    
    w = go1Free(initial);

    // Move values from initial bit vector to A (dumb error 1)
    vector<bool> S;
    S = getUniqueVector(initial);
    for (int i = 0; i <= S.size(); i++) {
        A[i] = S[i];
    }

    weights[m * p] = w;
    
    Factorization dp(m * p);
    for (int q = p + 1; m * q <= max; q++) {

        // used for comparing difference between dp
        // and the possibly incomplete next shape m*(p+1)
        Factorization shifted = dp;
        shifted.shiftLatticePoints();
        
        nextShift(dp, shifted, w, A);

        // dp.printPairs();
        // shifted.printPairs();
        // cout << endl << endl;

        // generated just to test if m*(p+1) shape is correct
        Factorization dq(m * q);

        // Is the algorithm correct?
        if (x == dq.pairs.size()) {
            weights[m * q] = w;
        } else {
            // If it's not, ask if we use algorithm 4?
            if (weights[m * q] == 0 && m * m > max / 2) {
                if (q == dq.bestTauPlusVal(max)) {
                    weights[m * q] = w + fillDiff(shifted, dq, A);
                }
            }
        }
        dp = shifted;
    }
}