#!/bin/bash
echo -n "Introduzca un numero: "
read n
let sum=0; let i=0
while [ $i -le $n ];
do
	let sum="$sum + $i"
	let i="$i+1"
	echo $sum
done
