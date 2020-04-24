int go0Free(Factorization& d) {

    int isUniqueEnd;
    int countUnique = 0;

    isUniqueEnd = (d.pairs.back().y - 1) * (d.pairs.back().x - 1);
    boost::dynamic_bitset<> isUnique(isUniqueEnd + 1);

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

    countUnique += isUnique.count();

    return countUnique;

}
