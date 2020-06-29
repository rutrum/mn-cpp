TEST_CASE( "fast", "[delta]" ) {

    // Initialize fast evaluation hashmap
    FastRules fast = FastRules(); 

    ifstream in;
    in.open("results/delta_100000.txt");
    for (int n = 1; n <= 100000; n++) {
        Factors f = Factors(n);
        
        int expected;
        in >> expected;

        int calculated = fast.eval(f);
        if (calculated != -1) {
            CHECK( calculated == expected );
        }
    }
    in.close();
}

TEST_CASE( "naive", "[delta][naive]" ) {
    auto expected = delta_100000();

    for (int n = 1; n <= 100000; n++) {
        Factors f = Factors(n);
        int calculated = delta_naive(f);

        REQUIRE( calculated == expected[n] );
    }
}

TEST_CASE( "naive_save", "[delta][naive]" ) {
    auto expected = delta_100000();

    for (int n = 1; n <= 100000; n++) {
        Factors f = Factors(n);

        auto visited = boost::dynamic_bitset<>(f.product_bound());
        delta_naive_save(f, visited);
        int calculated = visited.count();

        REQUIRE( calculated == expected[n] );
    }
}

TEST_CASE( "segmented_naive", "[delta][naive][segmented]" ) {
    auto expected = delta_100000();

    for (int n = 1; n <= 100000; n++) {
        Factors f = Factors(n);
        int calculated = delta_segmented_naive(f, 1000);

        REQUIRE( calculated == expected[n] );
    }
}

TEST_CASE( "segmented_naive-big", "[delta][naive][segmented][big]") {
    auto expected = delta_u32();

    for (uint64_t n = 38; n <= 42; n += 2) {
        Factors f = Factors(n * 100000000);
        uint64_t calculated = delta_segmented_naive(f, 2000000);

        REQUIRE( calculated == expected[n] );
    }
}

TEST_CASE( "segmented_naive_save", "[delta][naive][segmented]" ) {
    auto expected = delta_100000();

    for (int n = 1; n <= 100000; n++) {
        Factors f = Factors(n);

        auto visited = boost::dynamic_bitset<>(f.product_bound());
        delta_segmented_naive_save(f, 1000, visited);
        int calculated = visited.count();

        REQUIRE( calculated == expected[n] );
    }
}

TEST_CASE( "modulo_1", "[delta][modulo]" ) {
    auto expected = delta_100000();

    for (int n = 1; n <= 100000; n++) {
        Factors f = Factors(n);
        int calculated = delta_modulo_1(f);

        REQUIRE( calculated == expected[n] );
    }
}

TEST_CASE( "modulo_1-big", "[delta][modulo][big]") {
    auto expected = delta_u32();

    for (uint64_t n = 38; n <= 42; n += 2) {
        Factors f = Factors(n * 100000000);
        uint64_t calculated = delta_modulo_1(f);

        REQUIRE( calculated == expected[n] );
    }
}

TEST_CASE( "segmented_modulo_1", "[delta][modulo][segmented]" ) {
    auto expected = delta_100000();

    for (int n = 1; n <= 100000; n++) {
        Factors f = Factors(n);
        int calculated = delta_segmented_modulo_1(f, 1000);

        REQUIRE( calculated == expected[n] );
    }
}

TEST_CASE( "segmented_modulo_1-big", "[delta][modulo][segmented][big]" ) {
    auto expected = delta_u32();

    for (uint64_t n = 1; n <= 42; n++) {
        Factors f = Factors(n * 100000000);
        uint64_t calculated = delta_segmented_modulo_1(f, 2000000);

        REQUIRE( calculated == expected[n] );
    }
}

TEST_CASE( "modulo_w", "[delta][modulo]" ) {
    auto expected = delta_100000();

    int w = GENERATE(2, 6, 12, 60, 120, 240);
    auto classes = classify_coords(w);

    for (int n = 1; n <= 100000; n++) {
        Factors f = Factors(n);
        int calculated = delta_modulo_w(f, w, classes);

        REQUIRE( calculated == expected[n] );
    }
}

TEST_CASE( "modulo_w-big", "[delta][modulo][big]" ) {
    auto expected = delta_u32();

    int w = 120;
    auto classes = classify_coords(w);

    for (uint64_t n = 2; n <= 42; n += 4) {
        Factors f = Factors(n * 100000000);
        uint64_t calculated = delta_modulo_w(f, w, classes);

        REQUIRE( calculated == expected[n] );
    }
}
