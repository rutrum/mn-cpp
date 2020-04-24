# Calculating M(n)

## utils

### Sieve.h
Implementation of the sieve of Eratosthenes.

### Factorization.h
Determines prime factorization, divisor pairs, and other properties of a given number.

## algs

### AlgDelta.h
Calculates delta(n) without taking any shortcuts.  It checks _every_ number underneath the lattice formed by divisor pairs.

### AlgFirstFree.h
Calculates delta(n) without checking the first row of the lattice.

### AlgSecondFree.h
Calculates delta(n) without checking the first two rows of the lattice.  This stores unique values in an even integer bit vector and an odd integer bit vector.

### AlgFast.h
Calculates delta(n) if it has a explicit rule such that n=m*p for prime p and m < 7.

### AlgShiftShape.h
Calculates delta(n) for a family of multiples of a value by iterating lattice points across the multiplication table.  This calculates delta(n) for values such that the shape is consistent.

### AlgShiftShapeFill.h
Calculates delta(n) in the same way as AlgShiftShape but will sometimes correct the shape when it is not consistent.

## test

### testAlgDelta.cpp
Calculates M(n) using AlgDelta.

### testAlgFirstFree.cpp
Calculates M(n) using AlgFirstFree.

### testAlgSecondFree.cpp
Calculates M(n) using testAlgSecondFree.

### testAlgFast_AlgFirstFree.cpp
Calculates M(n) using AlgFast when applicable, and AlgFirstFree otherwise.

### testCombo.cpp
Calculates M(n) using AlgFast when applicable, and uses either AlgFirstFree or AlgSecondFree otherwise.

### testAlgShiftShape_AlgFirstFree.cpp
Calculates M(n) by finding all delta(n) using AlgShiftShape and then AlgFirstFree to fill the gaps.

### testComboNoFill.cpp
Calculates M(n) by finding all delta(n) using AlgShiftShape and then testCombo to fill the gaps.

### testAlgShiftShapeFill_AlgFirstFree.cpp
Calculates M(n) by finding all delta(n) using AlgShiftShapeFill and then AlgFirstFree to fill the gaps.

### testComboFill.cpp
Calculates M(n) by finding all delta(n) using AlgShiftShapeFill and then testCombo to fill the gaps.

## sh

### validateTest.sh
Takes a test name as input, then compiles the test, and tests it for small known values of M(n).

### validateAllTests.sh
Runs validateTest for all tests in test directory.

### timeTest.sh
Takes a test name and any number of values for m.  Compiles the test and times it for all m values.  Output is stored into the data directory as a text file named today's date concatenated with the test name.

## data
Stores text files with output from shell scripts.

## bin
Stores all executables.