class FastRules {

    map<pair<int, int>, pair<int, int>> fast_hash;
    vector<int> input_periods;

public:

    FastRules() {

        // Open the hashmap file
        ifstream file;
        file.open("constants/raw_hash.txt");
        while (!file.eof()) {
            int a, b, c, d;
            file >> a >> b >> c >> d;
            pair<int, int> key = make_pair(a, b);
            pair<int, int> value = make_pair(c, d);
            fast_hash[key] = value;
        }
        file.close();

        // Open the input period file
        ifstream file2;
        file2.open("constants/input_periods.txt");
        while (!file2.eof()) {
            int a;
            file2 >> a;
            input_periods.push_back(a);
        }
        file2.close();
    }

    int eval(Factors f) {
        int hp = f.highest_prime();
        int c = f.n/hp;

        if (c >= input_periods.size() - 1) {
            // c is too big.  No rule here!
            return -1;

        } else {
            // Given c, we can find the period of that evaluation rule
            int period = input_periods[c];

            // Using c and where hp sits in the period, we can uniquely
            // determine all variables to perform fast evaluation
            pair<int, int> key = make_pair(c, hp % period);
            pair<int, int> result = fast_hash[key];

            return hp / period * result.first + result.second;
        }
    }

private:

};
