#!/bin/bash

# mem_leak.sh -
#
# Checks for memory leaks in a C++ program using GNU leaks 
# If there are no memory leaks, the output should be 0 leaks
# You can pipe mem_leak into grep to check for leaks
# $ ./mem_leaks.sh | grep leaks

assignment_cpp="$1"

if [ -z "$assignment_cpp" ]; then
   assignment_cpp=$(ls | grep '.cpp' | sort -r | head -1)
fi

assignment="${assignment_cpp%.*}"

>&2 echo "[INFO/DEBUG] Checking for memory leaks in $assignment_cpp"

g++ -std=c++11 "$assignment_cpp" -o "$assignment"
leaks --atExit -- "./$assignment"