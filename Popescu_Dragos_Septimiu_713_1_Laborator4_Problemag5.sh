#!/bin/sh
abs_path=$1 #absolute path given as parameter
for i in $abs_path/*.c # i is the name of each file in the absolute path
do #of format *.c
    #head -n 3 $i | grep -c "^#include *" head gets the top 3 rows from file   
    var=` head -n 3 $i | egrep -c "^#include *"`
    #grep count for include at start of row
    if [ $var -eq 3 ] #checks if all 3 checked rows have the "#include "
    then
        echo $i #prints the absolute path to the file
    fi
done

