#!/bin/bash
if [ -d $1 ];
then
	echo "Existe el directorio $1"
else
	echo "No existe el directorio $1"
	exit 1
fi

dir=$1
for fichero in $(ls $dir)
do
	echo $fichero
done
