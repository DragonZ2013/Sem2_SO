#!/bin/sh
rep_word=$1 # 1st parameter is the string with which i replace
file=$2 # 2nd parameter is the file name (relative or absolute path)

sed  "s/[a-z]/$1&/g" $2
# replaces lowercase letters with the 1st parameter and the letter itself(&)
