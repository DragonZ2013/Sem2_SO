#!/bin/sh
mv $1 $2 #moves the first folder in the second
cd $2/$1 #moves the current location for the find command(unsure if i can use relative path)
find -type f -name "*" | while read line; #finds all type=file elements recursively
#also processes the output with read
do
	mv $line $line.einz #adds the .einz extension to each file returned
done
