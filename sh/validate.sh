#!/bin/bash
. sh/allTests.sh
set -e

name=$1

compile $name

nums=( 256 512 1024 2048 4096 8192 16384 32768 65536 131072 262144 )
# nums=( 256 512 1024 2048 4096 8192 16384 )

echo "Running test for.."
for i in ${nums[@]}; do
    printf "  n=$i..."
    c=$(bin/$name $i)
    echo "done!"
    validate $i $c
done

echo ""