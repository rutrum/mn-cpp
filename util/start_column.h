int start_column(int lb, int r, int a, int n) {
    
    // First calculate the start column without checking
    // the modulus condition.
    int start = max(r, lb / r + 1);

    // This column may not be congruent to a mod n, so 
    // iterate across the row until a suitable column is found.
    // A column will be found with n steps.
    for (int step = 0; step < n; step++) {
        if ((start + step) * r % n == a) {
            return start + step;
        }
    }

    // Unreachable
    cout << "UNREACHABLE" << endl;
    return -1;
}
