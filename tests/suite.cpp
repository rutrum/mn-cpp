#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <fstream>
#include <map>

#include "catch.hpp"

#include "../util/factors.h"
#include "../util/sieve/sieve.h"
#include "../util/sieve/segmented.h"
#include "../util/sieve/wheel_mod_2.h"
#include "../util/sieve/highest_prime.h"
#include "../util/sieve/partial.h"

#include "../delta/fast.h"
#include "../delta/naive.h"
#include "../delta/segmented_naive.h"
#include "../delta/modulo_1.h"
#include "../delta/segmented_modulo_1.h"
#include "../delta/modulo_w.h"

#include "../deltas/shift.h"
#include "../deltas/dynamic_shift.h"

#include "sieve.h"
#include "delta.h"
#include "deltas.h"

using namespace std;

void check_factor(Factors f) {
    CHECK( f.n > 0 );
    for (int i = 0; i < f.num_pairs(); i++) {
        CHECK( f.n == f.row_bound_on_pair(i) * f.col_bound_on_pair(i));
    }
}

TEST_CASE( "factor" ) {
    SECTION( "n < 2^31" ) {
        Factors f = Factors(12);
        CHECK( f.num_pairs() == 3 );
        check_factor(f);

        f = Factors(100000000);
        CHECK( f.num_pairs() == 41 );
        check_factor(f);
    }
    SECTION (" 2^31 < n < 2^32 ") {
        Factors f = Factors(3221225472);
        CHECK( f.num_pairs() == 31 );
        check_factor(f);

        f = Factors(4294967296 - 4); // 2^32 - 4
        CHECK( f.num_pairs() == 144 );
        check_factor(f);
    }
}

