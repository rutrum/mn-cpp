void goShift(int m, int max, vector<int>& weights) {
    
    // Stores unique integers whose values can't be any larger than max
    vector<bool> A;
    A.resize(max + 1);

    // Hamming weight of A
    int w = 0;

    // Find the number of divisors of the multiplier
    // This is used for checking if a shifted multiplier lattice
    //      accurately represents that of an m*k lattice
    Factorization multiplier(m);
    int numMultiplierDivisors = multiplier.numberOfFactors();

    // Starting with m+1, find the first lattice of that can be
    //      determined using a shifted multiplier lattice.
    Factorization initial(1);
    int p;
    for (p = m; m * p < max; p++) {
        // See if m*p lattice can be respresented by shifted 
        //      multiplier lattice
        initial = Factorization(m * p);
        if ((initial.numberOfFactors() + 1) / 2 == numMultiplierDivisors) {
            break;
        }
    }

    // Use initial lattice this as a starting point for hamming weight.
    w = go1Free(initial);

    // Use initial lattice to find initial unique values.
    vector<bool> S;
    S = getUniqueVector(initial);
    for (int i = 0; i <= S.size(); i++) {
        A[i] = S[i];
    }

    // Store first delta(n) value we found
    weights[m * p] = w;
    
    // Scan through multipliers of initial lattice
    Factorization dp = initial;
    for (int q = p + 1; m * q <= max; q++) {

        // Shift points of lattice of dp
        Factorization shifted = dp;
        shifted.shiftLatticePoints();
        
        // Calculate new unique values between dp and shifted
        nextShift(dp, shifted, w, A);

        // Find actual lattice of m*q
        Factorization dq(m * q);

        // Did shifted accurately calculate delta(m*q)?
        if (numMultiplierDivisors == dq.pairs.size()) {
            weights[m * q] = w;
        }

        dp = shifted;
    }
}