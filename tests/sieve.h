TEST_CASE( "sieve", "[sieve]" ) {
    Sieve s = Sieve(100000);
    CHECK( s.count() == 9593 );
}

TEST_CASE( "segmented_sieve", "[sieve][segmented]" ) {
    SegmentedSieve s = SegmentedSieve(100000, 2000);
    CHECK( s.count() == 9593 );
}

TEST_CASE( "wheel_sieve_2", "[sieve][wheel]" ) {
    WheelSieve2 s = WheelSieve2(100000);
    CHECK( s.count() == 9593 );
}

TEST_CASE( "highest_prime_sieve", "[sieve]" ) {
    HighestPrimeSieve s = HighestPrimeSieve(100000);
    CHECK( s.count() == 9593 );
}

TEST_CASE( "partial_sieve", "[sieve]" ) {
    PartialSieve s1 = PartialSieve(0, 50000);
    PartialSieve s2 = PartialSieve(50000, 80000);
    PartialSieve s3 = PartialSieve(80000, 100000);
    CHECK( s1.count() + s2.count() + s3.count() == 9593 );
}
