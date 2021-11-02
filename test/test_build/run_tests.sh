#!/bin/sh
cd /mnt/c/Users/filip/Documents/Programming_projects/C_lang__/TSP_backtracking/test/test_build
echo "Running tests..."
cmake ..
make
./backtracking_tests
cd --
