#!/bin/bash

if [ $# -ne 4 ]; then

    echo "Uso: $0 <directorio_origen> <directorio_destino> <compresion> <sobrescribir>"
    exit 1
fi

origen=$1 #Argumento 1
destino=$2 #Argumento 2
comprimir=$3 #Argumento 3
sobrescribir=$4 #Argumento 4

if [ ! -d "$origen" ]; then

    echo "El directorio origen no existe"
    exit 1
fi

if [ "$comprimir" != "0" ] && [ "$comprimir" != "1" ]; then #Comprueba si comprimir es 0 o 1

    echo "El valor de compresion debe ser 0 o 1"
    exit 1
fi

if [ "$sobrescribir" != "0" ] && [ "$sobrescribir" != "1" ]; then #Comprueba si sobrescribir es 0 o 1

    echo "El valor de sobrescribir debe ser 0 o 1"
    exit 1
fi

mkdir -p "$destino" #Crea el directorio destino con la ruta dada
usuario=$(whoami) #Almacena el nombre del usuario
fecha=$(date +%Y%m%d) #Almacena la fecha en la que estamos
nombrecopia=$(basename "$origen")"_"$usuario"_"$fecha #Formato "nombreOrigen_usuario_fecha" para la copia

if [ "$comprimir" -eq 1 ]; then #Si comprimir=1

    nombrecopia="$nombrecopia.tar.gz" #Nombre de la copia comprimida

else #Sino

    nombrecopia="$nombrecopia.tar" #Nombre de la copia
fi

rutacopia="$destino/$nombrecopia" #Asignamos una ruta a la copia

if [ -f "$rutacopia" ] && [ "$sobrescribir" -eq 0 ]; then #Si existe un archivo con esa ruta y sobrescribir=0

    echo "No se sobrescribirá la copia."
    exit 0
fi

if [ "$comprimir" -eq 1 ]; then #Si comprimir=1

    tar -czf "$rutacopia" -P "$origen" #Comprime el archivo

else #Sino

    tar -cf "$rutacopia" -P "$origen" #No comprime el archivo
fi

echo "Copia realizada en $rutacopia"

exit 0