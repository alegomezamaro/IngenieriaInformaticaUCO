#!/bin/bash


#Comprobamos que sólo sea un argumento

if [ $# -ne 1 ]; then

    echo "Error, uso $0 <directorio>"

    exit 1

fi

#Comprobamos que sea un directorio

if [ ! -d $1 ]; then

    echo "$1 no es un directorio"

    exit 1

fi

directorio=$1

#Buscamos lo que haya dentro del directorio

busca=$(find $directorio -type f)

#Recorremos todo elemento del directorio uno a uno

for fichero in $busca; do

    nombre=$(basename $fichero) #1.Nombre del fichero sin la ruta

    ruta=$fichero #2.La ruta absoluta del fichero.

    fecha_mod=$(stat -c %Y $fichero) #3.La fecha de modificación expresada en segundos desde la Época.   
    #%y: muestra la fecha y hora de la ultima modificación del archivo
    #%Y:muestra la fecha

    tam=$(stat -c %s $fichero) #4.Tamaño en bytes

    permisos=$(stat -c %A $fichero) #5.La cadena de permisos del fichero
    #%A: cadena de permisos
    #%a: valor de los permisos (EJ: 777)

    echo -e "$nombre\t$ruta\t$tam bytes\t$fecha_mod\t$permisos" #-e: que lo imprima en una sola linea

done | sort -k4 -n #Ordenacion ascendente(k) en base al 4º elemento del echo y con -n para que sea de tipo numérico


exit 0








