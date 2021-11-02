#!/bin/sh
cd /mnt/c/Users/filip/Documents/Programming_projects/C_lang__/TSP_backtracking/test/test_build
echo "Cleaning tests..."
find ./ -type f -not -name '*.sh' -print0 | xargs -0 -I {} rm -rv {}
cd --