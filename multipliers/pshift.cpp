#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <fstream>
#include <string>
#include "mpi.h"

#include "../util/factors.h"
#include "../util/sieve/sieve.h"
#include "../delta/segmented_naive.h"
#include "../deltas/dynamic_shift.h"

using namespace std;

uint32_t* run_on_m(int, uint32_t, uint64_t, Sieve);
uint32_t* read_multipliers(uint32_t);
void write_multipliers(uint64_t, uint32_t, uint32_t*);

// New compile and run commands for MPI!
// mpicxx -o blah file.cpp
// mpirun -q -np 32 blah

int main (int argc, char * argv[]) {

    int my_rank;                    // my CPU number for this process
    int p;                          // number of CPUs that we have
    MPI_Status status;              // return status for receive

    // MPI Initialization
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    // THE REAL PROGRAM IS HERE
    
    uint64_t max = 4294967296;

    if (my_rank == 0) {
        // MASTER

        // Read multipliers from file
        uint32_t total_ms = 10;
        uint32_t* ms = read_multipliers(total_ms);

        uint32_t current = 0;
        int less = 0; // Says if we need to expect some number less final responses

        // Distribute initial multiplier 
        for (int i = 1; i < p; i++) {
            if (current < total_ms) {
                uint32_t m = ms[current];
                while (m < 17) {
                    current++;
                    if (current >= total_ms) {
                        cout << "[M] No more!  Final send to " << status.MPI_SOURCE << endl;
                        less++;
                        uint32_t m = 0;
                        MPI_Send(&m, 1, MPI_UNSIGNED_LONG, status.MPI_SOURCE, 0, MPI_COMM_WORLD);
                        break;
                    }
                    m = ms[current];
                }
                cout << "[M] Sending " << m << " to " << i << endl;
                MPI_Send(&m, 1, MPI_UNSIGNED_LONG, i, 0, MPI_COMM_WORLD);
            } else {
                // None left, send 0
                less++;
                uint32_t m = 0;
                MPI_Send(&m, 1, MPI_UNSIGNED_LONG, i, 0, MPI_COMM_WORLD);
            }
            current++;
        }

        cout << "[M] Done sending initial" << endl;

        // Give processors the next multiplier
        while (current < total_ms) {
            cout << "[M] Ready to recieve" << endl;

            uint32_t ready;
            MPI_Recv(&ready, 1, MPI_UNSIGNED_LONG, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            cout << "[M] Recieved from " << status.MPI_SOURCE << endl;

            uint32_t send_m = ms[current];
            MPI_Send(&send_m, 1, MPI_UNSIGNED_LONG, status.MPI_SOURCE, 0, MPI_COMM_WORLD);

            current++;
        }

        cout << "[M] Final communication" << endl;

        // Tell the remaining processors there aren't any left
        for (int i = 1; i < p - less; i++) {
            uint32_t ready = 0;
            MPI_Recv(&ready, 1, MPI_UNSIGNED_LONG, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            cout << "[M] Final recieve from " << status.MPI_SOURCE << endl;
            uint32_t m = 0;
            MPI_Send(&m, 1, MPI_UNSIGNED_LONG, status.MPI_SOURCE, 0, MPI_COMM_WORLD);
            cout << "[M] Final send " << status.MPI_SOURCE << endl;
        }

        delete ms;
        cout << "[M] Done!" << endl;

    } else {
        // SLAVE
        cout << "[" << my_rank << "] Initializing sieve" << endl;

        // Ask for first interval
        uint32_t m;
        MPI_Recv(&m, 1, MPI_UNSIGNED_LONG, 0, 0, MPI_COMM_WORLD, &status);

        // Keep looping through each interval
        while (m != 0) {

            cout << "[" << my_rank << "] Computing m = " << m << endl;

            Sieve s = Sieve(max / m + 1);
            uint32_t* deltas = run_on_m(my_rank, m, max, s);
            write_multipliers(max, m, deltas);
            delete[] deltas;

            cout << "[" << my_rank << "] Done! Asking for another." << endl;
            // Tell master I want another!
            MPI_Send(&m, 1, MPI_UNSIGNED_LONG, 0, 0, MPI_COMM_WORLD);


            // Recieve next multiplier
            MPI_Recv(&m, 1, MPI_UNSIGNED_LONG, 0, 0, MPI_COMM_WORLD, &status);

            cout << "[" << my_rank << "] Recieved m = " << m << endl;
        }
    }

    // Shut down MPI
    MPI_Finalize();

    return 0;
}

uint32_t* read_multipliers(uint32_t total_ms) {
    ifstream in;
    in.open("multipliers/m2pow32.txt");
    uint32_t* ms = new uint32_t[total_ms];
    for (int i = 0; i < total_ms; i++) {
        in >> ms[i];
    }
    in.close();
    return ms;
}

void write_multipliers(uint64_t max, uint32_t m, uint32_t* deltas) {
    ofstream out;
    out.open("multipliers/data/deltas_max" + to_string(max) + "_m" + to_string(m) + ".txt");
    for (uint64_t n = 1; n <= max / m; n++) {
        if (deltas[n] != -1) {
            out << n * m << " " << deltas[n] << endl;
        }
    }
    out.close();
}


uint32_t* run_on_m(int my_rank, uint32_t m, uint64_t max, Sieve s) {
    uint32_t* deltas = new uint32_t[max / m + 1];
    for (uint64_t i = 0; i <= max / m; i++) {
        deltas[i] = -1;
    }

    deltas_dynamic_shift(m, 1, max, s, deltas);
    return deltas;
}
