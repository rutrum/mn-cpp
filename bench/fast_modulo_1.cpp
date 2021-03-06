#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <boost/dynamic_bitset.hpp>

#include "../util/factors.h"
#include "../delta/modulo_1.h"
#include "../delta/fast.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;

    long sum = 0;
    int start = strtol(argv[1], NULL, 10);
    int end = strtol(argv[2], NULL, 10);

    FastRules fast = FastRules(); 

    for (int n = start; n <= end; n++) {
        Factors f = Factors(n);
        int delta = fast.eval(f);
        if (delta == -1) {
            delta = delta_modulo_1(f);
        }
        sum += n - delta;
    }

    cout << sum << endl;
}
