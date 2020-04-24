#!/bin/bash

testsPath="test/*.cpp"
for path in $testsPath; do
    sh/validate.sh $path
done