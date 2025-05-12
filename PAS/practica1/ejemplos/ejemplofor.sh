#!/bin/bash
sum=0
for num in 1 2 3 4 5
do
	echo $num
	let sum="$sum + $num"
done
echo $sum
