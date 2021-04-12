#!/bin/sh

for i in $*; do
    awk 'length($0)>10 {print substr($0,11)} length($0)>10 {c++} END{print FILENAME,c}' $i
    #$0= modifies entire line, C counts lines that match condition, END = prints after the analysis of one file
done
