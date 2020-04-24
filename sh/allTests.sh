#!/bin/bash

validate () {
    n=$1 # n value
    c=$2 # Calculated M(n)
    a=$(getMn $n)
    if [ $a = 0 ]; then
        echo "Calculated $c"
        return 0
    elif [ $a = $c ]; then
        return 0
    else
        echo "Expected $a"
        echo "Calculated $c"
        return 1
    fi 
}

getMn () {
    n=$1 # n value
    case $n in 
        256) echo 17668 ;;
        512) echo 67765 ;;
        1024) echo 260095 ;;
        2048) echo 1004977 ;;
        4096) echo 3903563 ;;
        8192) echo 15204380 ;;
        16384) echo 59415059 ;;
        32768) echo 232492567 ;;
        65536) echo 911705949 ;;
        131072) echo 3581081997 ;;
        262144) echo 14081153467 ;;

        100) echo 2906 ;;
        1000) echo 248083 ;;
        10000) echo 22504348 ;;
        100000) echo 2099198630 ;;

        *) echo 0 ;;
    esac
}

compile () {
    path=$1
    name=$(basename $path .cpp)
    printf "Compiling $name..."
    g++ -O3 -I./ -o "bin/$name" $path
    if [[ $? -ne 0 ]]; then
        return $?
    fi
    echo "done!"
}

printNow () {
    echo "$(date +%Y.%m.%d) $(date +%H:%M)"
}