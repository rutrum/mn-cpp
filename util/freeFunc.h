// Given lower bound l, row r, remainder a, and modulus n,
// this will return the first column c that meets the following criteria:
//      - c * r > l
//      - c > r
//      - c * r = a (mod n)
int findStartColumn(int l, int r, int a, int n) {
    // First calculute start column without modulus condition
    int calc = l / r + 1;
    int bMod = max(r, calc);
    // manually check the next n column values to see if they are a good start
    int aMod = -1;
    for (int i = 0; i < n; i++) {
        if ((bMod + i) * r % n == a) {
            aMod = bMod + i;
            break;
        }
    }
    return aMod;
}

void greatestIntegerInRow(Factorization& d, int Gi[], int l) {
    int i = 0; // Current Gi

    // Calculate greatest integer by looping up through pairs.x
    for (int t = 0; t < d.pairs.size() && i < l; t++) {
        if (d.pairs[t].x > i + 1) {
            Gi[i] = (d.pairs[t].y - 1) * (i + 1);
            i++;
            t--;
        }
    }

    // Calculate greatest integer by looping down through pairs.y
    for (int t = d.pairs.size() - 1; t >= 0 && i < l; t--) {
        if (d.pairs[t].y > i + 1) {
            Gi[i] = (d.pairs[t].x - 1) * (i + 1);
            i++;
            t++;
        }
    }

    // Fill rows that don't exist with zeros
    while (i < l) {
        Gi[i] = 0;
        i++;
    }
}