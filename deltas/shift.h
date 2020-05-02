int* deltas_shift(int m, int max) {

    int* deltas = new int[max + 1];
    for (int i = 0; i < max + 1; i++) {
        deltas[i] = -1;
    }
    boost::dynamic_bitset<> visited(max + 1);
    
    // Find the shape of m and its initial delta(m) value
    Factors mf = Factors::all_pairs(m);
    deltas[m] = delta_naive(mf);
    
    Factors last = mf;
    Factors next = mf.stretch_lattice(5);

    last.print();
    next.print();


    cout << "next: " << next.n << endl;
    cout << "5*m: " << 5*m << endl;
    cout << "delta10: " << delta_naive(next) << endl;
    deltas[5*m] = delta_naive(next);

    // Translate the shape so its the shape as m * p
    // Loop through each m*p shape and run algorithm 3
    // to find the differences between shapes.
    // Add differences to last value of delta and save

    return deltas;
}
