TEST_CASE( "shift", "[deltas]" ) {
    auto expected = delta_100000();

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
}

TEST_CASE( "shift-big", "[deltas][big]" ) {
    auto expected = delta_u32();

    uint64_t max = 4294967296; 
    uint32_t m = 100000000;

    Sieve s = Sieve(max / m);

    uint32_t* deltas = new uint32_t[max / m + 1];
    for (uint64_t i = 0; i <= max / m; i++) {
        deltas[i] = -1;
    }
    deltas_shift(m, max, s, deltas);

    for (auto p = 1; p != 0; p = s.next_prime(p)) {
        CHECK(expected[p] == deltas[p]);
    }

    delete[] deltas;
}

TEST_CASE( "dynamic_shift", "[deltas]" ) {
    auto expected = delta_100000();

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
        deltas_dynamic_shift(m, 1, max, s, m_deltas);
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
}

TEST_CASE( "dynamic_shift-big", "[deltas][big]" ) {
    auto expected = delta_u32();

    uint64_t max = 4294967296; 
    uint32_t m = 100000000;

    Sieve s = Sieve(max / m);

    uint32_t* deltas = new uint32_t[max / m + 1];
    for (uint64_t i = 0; i <= max / m; i++) {
        deltas[i] = -1;
    }
    deltas_dynamic_shift(m, 1, max, s, deltas);

    for (auto p = 1; p != 0; p = s.next_prime(p)) {
        CHECK(expected[p] == deltas[p]);
    }

    delete[] deltas;
}

TEST_CASE( "dynamic_shift-runtime", "[deltas][big][runtime]" ) {
    uint64_t max = 4294967296; 
    uint32_t ms[5] = {6999, 33444, 101, 2000000, 100000000};
    
    int w = 120;
    auto classes = classify_coords(w);

    for (int j = 0; j < 5; j++) {
        uint32_t m = ms[j];

        Sieve s = Sieve(max / m);

        uint32_t* deltas = new uint32_t[max / m + 1];
        for (uint64_t i = 0; i <= max / m; i++) {
            deltas[i] = -1;
        }
        deltas_dynamic_shift(m, 1, max, s, deltas);
        

        for (auto p = 1; p != 0; p = s.next_prime(p)) {
            Factors f = Factors(m * p);
            uint64_t calculated = delta_modulo_w(f, w, classes);

            CHECK(calculated == deltas[p]);
        }

        delete[] deltas;
    }
}
