int goFast(Factorization& d) {
    int hp = d.getHighestPrime();
    int c = d.n/hp;
    int countUnique;
    switch(c) {
        case 1:
            //a(p) = 0
            countUnique = 0;
            break;
        case 2:
            //a(2p) = p - 1
            countUnique = hp - 1;
            break;
        #include "three_up_fast_rules.h"
    }
    return countUnique;
}

bool canFast(Factorization d) {
    int hp = d.getHighestPrime();
    int c = d.n/hp;
    if (c > 16) {
        return false;
    }
    return true;
}
