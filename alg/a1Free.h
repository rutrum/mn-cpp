int go1Free(Factorization& d) {

    int isUniqueStart, isUniqueEnd;
    int countUnique = 0;

    if (d.pairs.size() < 2) {
        isUniqueStart = 0;
    } else {
        isUniqueStart = d.pairs[1].y - 1;
    }
    isUniqueEnd = (d.pairs.back().y - 1) * (d.pairs.back().x - 1);
    countUnique = isUniqueStart;

    boost::dynamic_bitset<> isUnique(isUniqueEnd - isUniqueStart + 1);

    for (int i = 2, t = 1; i < d.pairs.back().x; i++) {

        int lb = i;
        if (lb < isUniqueStart / i + 1) {
            lb = isUniqueStart / i + 1;
        }

        if (i == d.pairs[t].x) {
            t++;
        }

        int upperBound = d.pairs[t].y * i - isUniqueStart;
        for (int p = lb * i - isUniqueStart; p < upperBound; p += i) {
            isUnique[p] = true;
        }   
    }

    countUnique += isUnique.count();

    return countUnique;

}