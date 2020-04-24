#!/bin/bash
. sh/allTests.sh

if [ -z $2 ]; then
    echo "ERROR: Missing n value."
    exit 1;
fi

path=$1
name=$(basename $path .cpp)

date=$(date +%Y%m%d)
outFile="./data/$name.txt"

compile $path

echo "┌─── "$(printNow)" ───" >> "$outFile"
echo -e "\nStarting at $(printNow)"

echo -e "Running test for.."
while [ -n "$2" ]; do
    echo -ne "\n  n=$2..."
    echo "│" &>> "$outFile"
    echo "│     n  $2" &>> "$outFile"

    allOutput=$( ( /usr/bin/time --format="%e" ./bin/$name $2 ) 2>&1 )
    echo "done!"

    commandOut=$(echo $allOutput | awk '{print $1}')
    commandTime=$(echo $allOutput | awk '{print $2}')

    echo "Finished at $(printNow)"
    echo "│  M(n)  "$commandOut &>> "$outFile"
    echo "│  time  "$commandTime &>> "$outFile"
    shift
done

echo "" &>> "$outFile"