#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include "mpi.h" // message passing interface

// More includes for M(n) algorithm
#include <math.h>
#include <boost/dynamic_bitset.hpp>
#include <boost/math/common_factor_rt.hpp>

using namespace std;

#include "../util/Sieve.h"
Sieve sieve;
#include "../util/fastFact.h"
#include "../util/Factorization.h"

#include "../util/freeFunc.h"
#include "../alg/a5Free.h"

// add threshhold and resend wanted intervals
// throw away intervals that I've already printed (decrement loop)
// open/close file reader for every loop

struct intMvals {
    int interval;
    long long M;
    intMvals(int a, long long b) {
        interval = a;
        M = b;
    }
    bool operator< (intMvals g) {
        return (this->interval < g.interval);
    }
    bool operator> (intMvals g) {
        return (this->interval > g.interval);
    }
};

// New compile and run commands for MPI!
// mpicxx -o blah file.cpp
// mpirun -q -np 32 blah

int main (int argc, char * argv[]) {

    string filename = "./sumDelta.txt";
    if (argc > 1) {
        filename = argv[1];
    }

    int my_rank;                    // my CPU number for this process
    int p;                                  // number of CPUs that we have
    MPI_Status status;              // return status for receive

    // General note:
    // Tag 0 sends back interval
    // Tag 1 sends back sum(i-delta(n)) for n in interval

    // MPI Initialization
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    // THE REAL PROGRAM IS HERE

    int start = 0 + 1;
    int int_len = 1024;
    int end = int_len * 1024;
    int num_intervals = (end - start + 1) / int_len;

    sieve.init(60);

    if (my_rank == 0) {
        // MASTER

        vector< intMvals > big_list;
        int next_to_print = 1;
        int dist_int = 0;
        long long sum = 0;
        int threshhold = p * 1.5;

        // Distribute initial interval
        for (int i = 1; i < p; i++) {
            if (dist_int < num_intervals) {
                // Still intervals to send
                dist_int++;
                MPI_Send(&dist_int, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            } else {
                // No more to send; send 0
                int val = 0;
                MPI_Send(&val, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
        }

        for (int i = 0; i < num_intervals; i++) {

            int recv_int = 0;
            long long recv_sum = 0;

            // Get any finished interval value
            MPI_Recv(&recv_int, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            // Then fetch sum of delta value
            MPI_Recv(&recv_sum, 1, MPI_LONG_LONG, status.MPI_SOURCE, 1, MPI_COMM_WORLD, &status);

            int end_int = recv_int * int_len + start - 1;
            int start_int = end_int - int_len + 1;

            ofstream output;
            output.open("./sumDelta.txt", fstream::app);

            output << start_int << " " << end_int << " " << recv_sum << endl;

            // Don't do any logic if I've already seen interval before
            // if (recv_int >= next_to_print) {
            //      ofstream output;
            //      output.open("Mvalues.txt", fstream::app);

            //      // Do logic
            //      intMvals x(recv_int, recv_sum);
            //      big_list.push_back(x);
            //      sort(big_list.rbegin(), big_list.rend());

            //      // Print all values that are 
            //      while (big_list.size() > 0 && big_list.back().interval == next_to_print) {
            //              int n = big_list.back().interval * int_len + start - 1;
            //              sum += big_list.back().M;
            //              output << n << " " << big_list.back().M << endl;
            //              next_to_print++;
            //              big_list.pop_back();
            //      }_int >= next_to_print) {
            //      ofstream output;
            //      output.open("Mvalues.txt", fstream::app);

            //      // Do logic
            //      intMvals x(recv_int, recv_sum);
            //      big_list.push_back(x);
            //      sort(big_list.rbegin(), big_list.rend());

            //      // Print all values that are 
            //      while (big_list.size() > 0 && big_list.back().interval == next_to_print) {
            //              int n = big_list.back().interval * int_len + start - 1;
            //              sum += big_list.back().M;
            //              output << n << " " << big_list.back().M << endl;
            //              next_to_print++;
            //              big_list.pop_back();
            //      }

            //      output.close();
            // } else {
            //      i--;
            // }

            if (big_list.size() > threshhold) {
                MPI_Send(&next_to_print, 1, MPI_INT, status.MPI_SOURCE, 0, MPI_COMM_WORLD);
                threshhold += 2 * p;
                continue;
            } else if (big_list.size() < threshhold / 2) {
                threshhold = max(p * 2, (threshhold * 3) / 4);
            }

            // Send back response
            if (dist_int < num_intervals) {
                // Still more intervals to send
                dist_int++;
                MPI_Send(&dist_int, 1, MPI_INT, status.MPI_SOURCE, 0, MPI_COMM_WORLD);
            } else {
                // No more to send; send 0
                int val = 0;
                MPI_Send(&val, 1, MPI_INT, status.MPI_SOURCE, 0, MPI_COMM_WORLD);
            }

        }

        cout << "Master cpu done!" << endl;

        } else {
            // SLAVE

            // Initialize stuff for algorithm
            Factorization freeFact(60);
            boundPool.resize(60);
            for (int j = 0; j < freeFact.pairs.size(); j++) {
                boundPool[0].push_back(freeFact.pairs[j].x - 1);
                boundPool[0].push_back(freeFact.pairs[j].y - 1);
            }
            for (int i = 1; i < 60; i++) {
                // First look at x values
                for (int j = 0; j < freeFact.pairs.size(); j++) {
                    if (i % freeFact.pairs[j].x == 0) {
                        boundPool[i].push_back(freeFact.pairs[j].x - 1);
                    }
                    if (i % freeFact.pairs[j].y == 0) {
                        boundPool[i].push_back(freeFact.pairs[j].y - 1);
                    }
                }
            }

            // Ask for first interval
            int my_int;
            MPI_Recv(&my_int, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

            // Keep looping through each interval
            while (my_int != 0) {

                // ****************
                // M(n) CALCULATION
                // ****************

                long long sum = 0;
                int my_start = (my_int - 1) * int_len + start;
                int my_end = my_start + int_len - 1;

                vector<vector<int> > segment;
                findSegmentPairs(segment, my_start, my_end + 1);

                for (long i = my_start; i <= my_end; i++) {
                    int index = i % my_start;
                    if (my_start == 1) {
                        index = i - 1;
                    }
                    Factorization d(i, segment[index]);
                    int delta = go5Free(d);
                    sum += i - delta;
                }

                // cout << "segment size: " << sizeof(segment) << endl;

                // ***************
                // END CALCULATION
                // ***************

                // Send interval and result
                // if (my_rank == 1) {
                //      cout << "Starting useless calc" << endl;
                //      int sum = 0;
                //      for (int i = 0; i < 1000000000; i++) {
                //              sum += i;
                //      }
                //      cout << "Done with calc" << endl;
                // }
                MPI_Send(&my_int, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
                MPI_Send(&sum, 1, MPI_LONG_LONG, 0, 1, MPI_COMM_WORLD);

                // Recieve next interval
                MPI_Recv(&my_int, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
            }
        }

        // cout << my_rank << " is done!" << endl;

        // Shut down MPI
        MPI_Finalize();

        return 0;
    }
