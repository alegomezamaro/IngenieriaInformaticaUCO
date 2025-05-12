#!/bin/bash
read -p "Introduce el numero: " x

if [ $x -ge 1 ] &&  [ $x -lt 10 ];
then
	echo "Rango correcto"
else
	echo "Rango incorrecto"
fi
