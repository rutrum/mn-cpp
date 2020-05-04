alias t := test
test TEST:
    g++ tests/{{ TEST }}.cpp -o bin/test -O3
    bin/test
    @echo "Success!"
    
alias b := bench
bench BENCH START END:
    g++ bench/{{ BENCH }}.cpp -o bin/bench -O3
    /bin/time -p bin/bench {{ START }} {{ END }}

alias m := gen-multiplier
gen-multiplier MULTIPLIER:
    g++ multipliers/shift.cpp -o bin/multiplier -O3
    /bin/time -p bin/multiplier {{ MULTIPLIER }}

alias pm := par-multiplier
par-multiplier NP:
    mpicxx multipliers/pshift.cpp -o bin/pmultiplier -O3
    mpirun -q -np {{ NP }} bin/pmultiplier

clean:
    trash bin/*
