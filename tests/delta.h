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
    ifstream in;
    in.open("results/delta_100000.txt");
    for (int n = 1; n <= 100000; n++) {
        Factors f = Factors(n);
        int calculated = delta_naive(f);

        int expected;
        in >> expected;

        REQUIRE( calculated == expected );
    }
    in.close();
}

TEST_CASE( "naive_save", "[delta][naive]" ) {
    ifstream in;
    in.open("results/delta_100000.txt");
    for (int n = 1; n <= 100000; n++) {
        Factors f = Factors(n);

        auto visited = boost::dynamic_bitset<>(f.product_bound());
        delta_naive_save(f, visited);
        int calculated = visited.count();

        int expected;
        in >> expected;

        REQUIRE( calculated == expected );
    }
    in.close();
}

TEST_CASE( "segmented_naive", "[delta][naive][segmented]" ) {
    ifstream in;
    in.open("results/delta_100000.txt");
    for (int n = 1; n <= 100000; n++) {
        Factors f = Factors(n);
        int calculated = delta_segmented_naive(f, 1000);

        int expected;
        in >> expected;

        REQUIRE( calculated == expected );
    }
    in.close();
}

TEST_CASE( "segmented_naive_save", "[delta][naive][segmented]" ) {
    ifstream in;
    in.open("results/delta_100000.txt");
    for (int n = 1; n <= 100000; n++) {
        Factors f = Factors(n);

        auto visited = boost::dynamic_bitset<>(f.product_bound());
        delta_segmented_naive_save(f, 1000, visited);
        int calculated = visited.count();

        int expected;
        in >> expected;

        REQUIRE( calculated == expected );
    }
    in.close();
}

TEST_CASE( "modulo_1", "[delta][modulo]" ) {
    ifstream in;
    in.open("results/delta_100000.txt");
    for (int n = 1; n <= 100000; n++) {
        Factors f = Factors(n);
        int calculated = delta_modulo_1(f);

        int expected;
        in >> expected;

        REQUIRE( calculated == expected );
    }
    in.close();
}

TEST_CASE( "segmented_modulo_1", "[delta][modulo][segmented]" ) {
    ifstream in;
    in.open("results/delta_100000.txt");
    for (int n = 1; n <= 100000; n++) {
        Factors f = Factors(n);
        int calculated = delta_segmented_modulo_1(f, 1000);

        int expected;
        in >> expected;

        REQUIRE( calculated == expected );
    }
    in.close();
}

/*
TEST_CASE( "modulo_2", "[delta][modulo]" ) {
    ifstream in;
    in.open("results/delta_100000.txt");
    for (int n = 1; n <= 100000; n++) {
        Factors f = Factors(n);
        int calculated = delta_modulo_2(f);

        int expected;
        in >> expected;

        REQUIRE( calculated == expected );
    }
    in.close();
}
*/

TEST_CASE( "modulo_w", "[delta][modulo]" ) {
    ifstream in;
    in.open("results/delta_100000.txt");

    int w = 120;
    auto classes = classify_coords(w);

    for (int n = 1; n <= 100000; n++) {
        Factors f = Factors(n);
        int calculated = delta_modulo_w(f, w, classes);

        int expected;
        in >> expected;

        REQUIRE( calculated == expected );
    }
    in.close();
}

