TEST_CASE( "shift", "[deltas]" ) {
    ifstream in;
    in.open("results/delta_100000.txt");

    int expected[100001];
    for (int i = 1; i <= 100000; i++) {
        in >> expected[i];
    }

    int max = 100000; 
    Sieve s = Sieve(max);

    uint32_t deltas[max + 1];
    for (auto i = 0; i <= max; i++) {
        deltas[i] = -1;
    }

    // Use multipliers to find classes of delta values
    for (int m = 2; m <= 1000; m++) {
        uint32_t m_deltas[max / m + 1];
        for (auto i = 0; i <= max / m; i++) {
            m_deltas[i] = -1;
        }
        deltas_shift(m, max, s, m_deltas);
        for (auto i = 0; i <= max / m; i++) {
            if (m_deltas[i] != -1) {
                deltas[m * i] = m_deltas[i];
            }
        }
    }

    for (auto n = 1; n <= max; n++) {
        if (deltas[n] != -1) {
            CHECK(expected[n] == deltas[n]);
        }
    }

    in.close();
}

TEST_CASE( "dynamic_shift", "[deltas]" ) {
    ifstream in;
    in.open("results/delta_100000.txt");

    int expected[100001];
    for (int i = 1; i <= 100000; i++) {
        in >> expected[i];
    }

    int max = 100000; 
    Sieve s = Sieve(max);

    uint32_t deltas[max + 1];
    for (auto i = 0; i <= max; i++) {
        deltas[i] = -1;
    }

    // Use multipliers to find classes of delta values
    for (int m = 2; m <= 1000; m++) {
        uint32_t m_deltas[max / m + 1];
        for (auto i = 0; i <= max / m; i++) {
            m_deltas[i] = -1;
        }
        deltas_dynamic_shift(m, 7, max, s, m_deltas);
        for (auto i = 0; i <= max / m; i++) {
            if (m_deltas[i] != -1) {
                deltas[m * i] = m_deltas[i];
            }
        }
    }

    for (auto n = 1; n <= max; n++) {
        if (deltas[n] != -1) {
            CHECK(expected[n] == deltas[n]);
        }
    }

    in.close();
}
