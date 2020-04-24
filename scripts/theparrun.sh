#!/bin/bash

mpicxx test/PSegNFree.cpp -o researchThatShouldBeOnBIGDAWG
mpirun -np 25 researchThatShouldBeOnBIGDAWG

# Output should be in Mvalues.txt

uniq sumDelta.txt | sort -n > sortedSumDelta.txt
python3 clean.py sortedSumDelta.txt > Mvalues.txt