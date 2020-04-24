#!/bin/bash
. sh/allTests.sh

name=$1

date=$(date +%Y%m%d)
outFile="./data/run$date$name.txt"
touch $outFile

compile $name

echo "Running test for.."
while [ -n "$2" ]; do
    printf "m=$2..."
    echo "m=$2;" &>> "$outFile"
    ./bin/$name $2 &>> "$outFile"
    echo "done!"
    echo "Finished at $(date +%Y.%m.%d) $(date +%H:%M)"
    echo ""
    echo "" &>> "$outFile"
    shift
done
