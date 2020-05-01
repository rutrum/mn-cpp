void assert_delta_n(int expected, int calculated, int n) {
    if (calculated != expected) {
        cout << "Calculated\t" << calculated << endl;
        cout << "Expected\t" << expected << endl;
        cout << "n = " << n << endl;
        exit(1);
    }
}
