#include <map>
#include <fstream>

map<pair<int, int>, pair<int, int>> fast_hash;
vector<int> input_periods;

// bool operator<(pair<int, int> const& lhs, pair<int, int> const& rhs) {
//     lhs < rhs;
// }

void populateHash() {
    ifstream file;
    file.open("raw_hash.txt");
    
    while (!file.eof()) {
        int a, b, c, d;
        file >> a >> b >> c >> d;
        pair<int, int> key = make_pair(a, b);
        pair<int, int> value = make_pair(c, d);
        fast_hash[key] = value;
    }

    ifstream file2;
    file2.open("input_periods.txt");
    while (!file2.eof()) {
        int a;
        file2 >> a;
        input_periods.push_back(a);
    }
}

void print_pair(pair<int, int> p) {
    cout << p.first << ", " << p.second << endl;
}

int goHash(Factorization& d) {
    int hp = d.getHighestPrime();
    int c = d.n/hp;
    if (c >= input_periods.size() - 1) {
        return -1;
    } else {
        int input = input_periods[c];
        pair<int, int> key = make_pair(c, hp % input);
        // if (fast_hash.find(key) == fast_hash.end()) { 
        //     print_pair(key);
        //     return -1; 
        // }
        pair<int, int> result = fast_hash[key];
        return hp / input * result.first + result.second;
    }
}

