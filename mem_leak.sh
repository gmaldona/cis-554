#!/bin/bash
assignment_cpp="$1"

if [ -z "$assignment_cpp" ]; then
   assignment_cpp=$(ls | grep '.cpp' | sort -r | head -1)
fi

assignment="${assignment_cpp%.*}"

>&2 echo "[INFO/DEBUG] Checking for memory leaks in $assignment_cpp"

g++ -std=c++11 "$assignment_cpp" -o "$assignment"
leaks --atExit -- "./$assignment"