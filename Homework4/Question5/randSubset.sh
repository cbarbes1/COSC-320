#!/bin/bash
#

randend=$((1+$RANDOM % $1))

while [ $randend -lt $2 ];
do 
	newrand=$((1 + $RANDOM % $1))
	randend=`expr $newrand + $randend`
done  

head -n $randend $3 | tail -n $2 > "new.txt"

exit 0

