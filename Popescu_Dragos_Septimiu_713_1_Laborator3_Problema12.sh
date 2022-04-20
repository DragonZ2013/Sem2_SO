#!/bin/sh
if [ $1 -gt $2 ] && [ $1 -gt $3 ] #case: a is the largest of the numbers
then
    b=$(($2*$2))
    #b=b*b
    c=$(($3*$3))
    #c=c*c
    a=$(($1*$1))
    #a=a*a
    p=$(($c+$b))
    #p=c*c+b*b
    sol=$(($a-$p))#sol=a*a-c*c-b*b
elif [ $2 -gt $1 ] && [ $2 -gt $3 ] #case: b is the largest of the numbers
then
    b=$(($2*$2))
    #b=b*b
    c=$(($3*$3))
    #c=c*c
    a=$(($1*$1))
    #a=a*a
    p=$(($a+$c))
    #p=a*a+c*c
    sol=$(($b-$p))
    #sol=b*b-a*a-c*c

else #case: c is the largest of the numbers
    b=$(($2*$2))
    #b=b*b
    c=$(($3*$3))
    #c=c*c
    a=$(($1*$1))
    #a=a*a
    p=$(($a+$b))
    #p=(a*a+b*b)
    sol=$(($c-$p))
    #sol=c*c-a*a-b*b
fi

#echo $sol
if [[ $sol -eq 0 ]] #sol=0 > numbers are pythagoric
then
    echo 'ja'
else
    echo 'nein'
fi