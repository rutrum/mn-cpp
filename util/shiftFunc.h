void nextShift(Factorization& dp, Factorization& dq, int& w, vector<bool>& A) {
    // int l = dp.pairs.size();
    // for (int i = 1, k = 0; i < dp.pairs[l - 1].x; i++) {
    for (int i = 1, k = 0; i < dp.last().x; i++) {
        
        // Dont run over the pair
        while (i >= dp.pairs[k].x) {
            k++;
        }

        // Loop between dp and dq and count unique product between shapes
        for (int p = i * dp.pairs[k].y; p < i * dq.pairs[k].y; p += i) {
            if (!A[p]) {
                A[p] = true;
                w++;
            }
        }
    }
}

vector<bool> getUniqueVector(Factorization& d) {

    int isUniqueEnd;
    isUniqueEnd = (d.pairs.back().y - 1) * (d.pairs.back().x - 1);

    vector<bool> isUnique;
    isUnique.resize(isUniqueEnd);

    for (int i = 1, t = 1; i < d.pairs.back().x; i++) {

        int lb = i;

        if (i == d.pairs[t].x) {
            t++;
        }

        int upperBound = d.pairs[t].y * i;
        for (int p = lb * i; p < upperBound; p += i) {
            isUnique[p] = true;
        }   
    }

    return isUnique;

}