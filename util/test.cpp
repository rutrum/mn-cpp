#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>

#include "factors.h"
#include "soe.h"
#include "start_column.h"
#include "../delta/naive.h"

using namespace std;

int main() {
    Sieve s = Sieve(100);
    cout << s.next_prime(40) << endl;
    cout << s.next_prime(1) << endl;
}
