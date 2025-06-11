#!/bin/bash


if [ $# -ne 1 ]; then #Comprueba que hay un argumento en la llamada

    echo "Error, uso $0 <directorio>"

    exit 1

fi

if [ ! -d $1 ]; then #Comprueba que existe el directorio

    echo "Error, no existe directorio"

    exit 1

fi

directorio=$1 #Almacena el directorio

busca=$(find $directorio -type f) #Busca en el directorio los ficheros de tipo f(que sea fichero)

primerFichero=$(find $directorio -type f | head -n 1) #Cuenta las lineas del primer fichero

n=$(cat $primerFichero | wc -l) #Cuenta las lineas del primer fichero


total=0;

for ((i=1;i<=$n;i=$i+1)); do #Recorre las lineas de los ficheros

    suma=0;

    for fichero in $busca; do

        linea=$(cat $fichero | head -n $i | tail -n 1) #Con head coge las primeras 'i' lineas y con tail de esas n lineas del head coge la ultima

        let suma=$suma+$linea; #Suma las lineas de los ficheros

    done

    echo "Asistieron $suma personas a la sesión $i"

    let total=$total+$suma

done

media=0

let media=($total/$n)

echo "La media de asistencia es: $media"



exit 0
