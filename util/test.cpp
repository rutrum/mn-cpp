#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>

#include "factors.h"
#include "soe.h"
#include "start_column.h"
#include "../delta/naive.h"
#include "../delta/modulo1.h"
#include "../delta/modulo2.h"
#include "../delta/moduloN.h"

using namespace std;

int main() {

    /*
    vector<vector<pair<int,int>>> classes = classify_coords(6);
    for (int i = 0; i < classes.size(); i++) {
        cout << "Class " << i << ": ";
        for (int j = 0; j < classes[i].size(); j++) {
            pair<int,int> p = classes[i][j];
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << endl;
    }

    Factors f = Factors(48);
    auto lbs = f.mod_class_lower_bounds(6);
    for (int i = 0; i < lbs.size(); i++) {
        cout << i << ": " << lbs[i] << endl;
    }
    */

    int sum = 0;
    int N = 60;
    auto classes = classify_coords(N);
    for (int i = 1; i <= 100000; i++) {
        Factors f = Factors(i);
        int modn = delta_moduloN(f, N, classes);
        /*if (modn != delta_modulo2(f)) {
            cout << "UNEQUAL" << endl;
            cout << "N: " << modn << endl;
            cout << "0: " << delta_naive(f) << endl;
            //f.print();
            return 0;
        }*/
        //cout << i << endl;
        //sum += i - delta_moduloN(f, 2);
        sum += i - modn;
    }
    cout << sum << endl;
}
