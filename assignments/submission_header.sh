#!/bin/bash

# submission_header.sh - 

# EXAMPLE: 
#          $ ./submission_header.sh -f file.cpp -n 1
#                                        ^^        ^ 
#         File that is going to be submitted       ^
#                                                  ^ 
#                                               HW Number
# Only submit a .txt file.
# The file name is required to be: HW1_FirstName_LastName_SUNetID.txt
# The first line of your code should be //HW1 by FirstName LastName
# The second line of your code should be //SU Net ID: XXXXXXX SUID: 12345678
# Do not implement the functions in the class declaration. But outside the class, like void className::func().
# Do not declare extra class variables, global variables, or extra functions.
# Be sure your code can be compiled and run-on Visual Studio 2022 (Visual Studio Code is different from Visual Studio 2022).
# Our standard compiler will be Visual Studio 2022 for Windows. (All editions are fine. Remember that the community edition is free.)
# If you have any further questions on the assignments or grading, please come to the office hour or send an email.

while getopts "n:o:f:" flag; do
    case "${flag}" in
        n) 
            hw=${OPTARG} # specify which homework number
            ;; 
        o) 
            output=${OPTARG}
            ;;   
        f)
            file=${OPTARG}
            ;;     
    esac
done

if [ -z "$file" ]; then
    "f) argument is empty. Please specify file."
fi 

if [ -z "$output" ]; then
   output='submissions'
fi

if [ -z "$hw" ]; then
    >&2 echo "[WARNING] No homework number specified with option n). Defaulting to HW#."
    hw='#'
fi

out_file="HW${hw}_firstname_lastname_suid.txt"

if [ ! -d  "$output" ]; then
    mkdir -p "$output" 
fi  

sed '1i\
// HW# by FirstName LastName \
// SU Net ID: SU_NET_ID SUID: SUID' $file > "$output/$out_file.temp"

sed -e "s/HW#/HW${hw}/g" "$output/$out_file.temp" > "$output/$out_file"
rm "$output/$out_file.temp"


