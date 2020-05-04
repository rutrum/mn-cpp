#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <fstream>
#include <string>
#include "mpi.h"

#include "../util/factors.h"
#include "../util/soe.h"
#include "../delta/naive.h"
#include "../deltas/shift.h"

using namespace std;

void run_on_m(int, uint32_t);

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

    if (my_rank == 0) {
        // MASTER

        // Read multipliers from file
        int total_ms = 20; // 3400619;
        ifstream in;
        in.open("multipliers/m2pow32.txt");
        uint32_t* ms = new uint32_t[total_ms];
        for (int i = 0; i < total_ms; i++) {
            in >> ms[i];
        }
        in.close();

        uint32_t current = 0;
        int less = 0; // Says if we need to expect some number less final responses

        // Distribute initial multiplier 
        for (int i = 1; i < p; i++) {
            if (current < total_ms) {
                uint32_t m = ms[current];
                while (m < 17 || m > 4294967296 / 30) {
                    current++;
                    if (current >= total_ms) {
                        cout << "No more!  Final send to " << status.MPI_SOURCE << endl;
                        less++;
                        uint32_t m = 0;
                        MPI_Send(&m, 1, MPI_UNSIGNED_LONG, status.MPI_SOURCE, 0, MPI_COMM_WORLD);
                        break;
                    }
                    m = ms[current];
                }
                cout << "Master sending " << m << " to " << i << endl;
                MPI_Send(&m, 1, MPI_UNSIGNED_LONG, i, 0, MPI_COMM_WORLD);
            } else {
                // None left, send 0
                less++;
                uint32_t m = 0;
                MPI_Send(&m, 1, MPI_UNSIGNED_LONG, i, 0, MPI_COMM_WORLD);
            }
            current++;
        }

        cout << "Master done sending initial" << endl;

        // Give processors the next multiplier
        while (current < total_ms) {

            uint32_t ready = 0;
            cout << "Ready to recieve" << endl;
            MPI_Recv(&ready, 1, MPI_UNSIGNED_LONG, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);

            cout << "Recieved m=" << ready << " from " << status.MPI_SOURCE << endl;

            uint32_t m = ms[current];
            current++;
            
            // Skip m value if its too small (too much memory)
            // or if its too big (too much time)
            while (m < 17 || m > 4294967296 / 30) {
                current++;
                if (current >= total_ms) {
                    cout << "No more!  Final send to " << status.MPI_SOURCE << endl;
                    less++;
                    uint32_t m = 0;
                    MPI_Send(&m, 1, MPI_UNSIGNED_LONG, status.MPI_SOURCE, 0, MPI_COMM_WORLD);
                    break;
                }
                m = ms[current];
            }
            
            // Make sure still some left
            if (current >= total_ms) {
                cout << "No more!  Final send to " << status.MPI_SOURCE << endl;
                less++;
                uint32_t m = 0;
                MPI_Send(&m, 1, MPI_UNSIGNED_LONG, status.MPI_SOURCE, 0, MPI_COMM_WORLD);
                break;
            } else {
                cout << "Sending m=" << m << " to " << status.MPI_SOURCE << endl;
                MPI_Send(&m, 1, MPI_UNSIGNED_LONG, status.MPI_SOURCE, 0, MPI_COMM_WORLD);
            }
            current++;
        }

        cout << "Final communication" << endl;

        // Tell the remaining processors there aren't any left
        for (int i = 1; i < p - less; i++) {
            uint32_t ready = 0;
            MPI_Recv(&ready, 1, MPI_UNSIGNED_LONG, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            cout << "Final recieve from " << status.MPI_SOURCE << endl;
            uint32_t m = 0;
            MPI_Send(&m, 1, MPI_UNSIGNED_LONG, status.MPI_SOURCE, 0, MPI_COMM_WORLD);
            cout << "Final send " << status.MPI_SOURCE << endl;
        }

        delete ms;
        cout << "Master cpu done!" << endl;

    } else {
        // SLAVE

        // Ask for first interval
        uint32_t m;
        MPI_Recv(&m, 1, MPI_UNSIGNED_LONG, 0, 0, MPI_COMM_WORLD, &status);

        // Keep looping through each interval
        while (m != 0) {

            cout << "[" << my_rank << "] Computing m=" << m << endl;
            run_on_m(my_rank, m);


            cout << "[" << my_rank << "] Done! Sending m=" << m << " to master" << endl;
            // Tell master I want another!
            MPI_Send(&m, 1, MPI_UNSIGNED_LONG, 0, 0, MPI_COMM_WORLD);

            cout << "[" << my_rank << "] Sent! Recieving from master" << endl;
            // Recieve next multiplier
            MPI_Recv(&m, 1, MPI_UNSIGNED_LONG, 0, 0, MPI_COMM_WORLD, &status);

            cout << "[" << my_rank << "] got m=" << m << endl;
        }
    }

    // Shut down MPI
    MPI_Finalize();

    return 0;
}


void run_on_m(int my_rank, uint32_t m) {
    uint64_t max = 4294967296;

    Sieve s = Sieve(max / m + 1);

    uint32_t* deltas = new uint32_t[max / m + 1];
    for (uint64_t i = 0; i <= max / m; i++) {
        deltas[i] = -1;
    }

    cout << "[" << my_rank << "] done assigning -1" << endl;

    deltas_shift(m, max, s, deltas);
    cout << "[" << my_rank << "] Done! Writing to file" << endl;

    ofstream out;
    out.open("multipliers/data/deltas_max" + to_string(max) + "_m" + to_string(m) + ".txt");
    for (uint64_t n = 1; n <= max / m; n++) {
        if (deltas[n] != -1) {
            out << n * m << " " << deltas[n] << endl;
        }
    }
    cout << "[" << my_rank << "] Done! Closing file" << endl;
    out.close();
    cout << "[" << my_rank << "] Deleting deltas" << endl;
    delete[] deltas;
}
