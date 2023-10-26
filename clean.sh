#!/bin/bash

# clean.sh - delete binaries for homework.

# depreciated
### for cpp in $(ls | grep ".cpp"); do
###    bin=${cpp%%.*}
###
###    if [ -f $bin ]; then
###       rm $bin
###    fi
### done

rm -r build/
