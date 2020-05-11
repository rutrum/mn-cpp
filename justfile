alias t := test
test TEST:
    g++ tests/{{ TEST }}.cpp -o bin/test -O3
    bin/test
    @echo "Success!"
    
alias b := bench
bench BENCH START END:
    g++ bench/{{ BENCH }}.cpp -o bin/bench -O3
    /bin/time -p bin/bench {{ START }} {{ END }}
    @play ~/Downloads/alert.mp3 -q 2> /dev/null

alias bs := bench-sieve
bench-sieve SIEVE SIZE:
    g++ bench/sieve/{{ SIEVE }}.cpp -o bin/bench-sieve -O3
    /bin/time -p bin/bench-sieve {{ SIZE }}

alias bss := bench-segmented-sieve
bench-segmented-sieve SIZE SEGMENT:
    g++ bench/sieve/segmented_sieve.cpp -o bin/bench-sieve -O3
    # /bin/time -p bin/bench-sieve {{ SIZE }} {{ SEGMENT }}
    sudo perf stat -d bin/bench-sieve {{ SIZE }} {{ SEGMENT }}

alias m := gen-multiplier
gen-multiplier ALG MULTIPLIER:
    g++ multipliers/{{ ALG }}.cpp -o bin/multiplier -O3
    /bin/time -p bin/multiplier {{ MULTIPLIER }}
    wc -l results/multipliers/deltas_max4294967296_m{{ MULTIPLIER }}.txt
    @play ~/Downloads/alert.mp3 -q 2> /dev/null

alias pm := par-multiplier
par-multiplier NP:
    mpicxx multipliers/pshift.cpp -o bin/pmultiplier -O3
    mpirun -q -np {{ NP }} bin/pmultiplier

clean:
    trash bin/*
