#!/bin/bash

if [ $# -ne 4 ]; then

    echo "Error el formato de entrada tiene que ser <directorio_origen> <directorio_destino> <comprimir> <sobreescribir>"

    exit 1

fi

#Almacenamos argumentos en variables 

dir_origen=$1

dir_destino=$2

comprimir=$3

sobreescribir=$4

#Comprobamos si el directorio origen existe

if [ ! -d "$dir_origen" ];then

    echo "El directorio $dir_origen no existe"

    exit 1

fi

#Comprobamos que los valores de comprimir y sobreescribir sean 0 ó 1

if [ "$comprimir" -ne 0 ] && [ "$comprimir" -ne 1 ]; then

    echo "Error, el valor de comprimir debe ser 0 ó 1"

    exit 1

fi

if [ "$sobreescribir" -ne 0 ] && [ "$sobreescribir" -ne 1 ]; then

    echo "Error, el valor de comprimir debe ser 0 ó 1"

    exit 1

fi

mkdir -p "$dir_destino" #Crea directorio destino siguiendo la ruta en la que nos encontramos

usuario=$(whoami) #Almacena el nombre de usuario

fecha=$(date +%Y%m%d) #Almacena la fecha a la que estamos

nombre=$(basename "$dir_origen")"_"$usuario"_"$fecha #Nombre que va a tener nuestro archivo 

if [ "$comprimir" -eq 1 ]; then

    nombre="$nombre.tar.gz"

else

    nombre="$nombre.tar"

fi

ruta_copia="$dir_destino/$nombre" #Ruta de la copia en el directorio destino

if [ -f "$ruta_copia" ] && [ "$sobreescribir" -eq 0 ]; then #Si existe un archivo con esa ruta y sobrescribir=0

    echo "No se sobreescribirá en el archivo"

    exit 0

fi


if [ "$comprimir" -eq 1 ]; then #Si comprimir=1

    tar -czf "$ruta_copia" -P "$dir_origen" #Comprime el archivo con el comando -czf y con -P para que no se pierdan los permisos

else #Sino

    tar -cf "$ruta_copia" -P "$dir_origen" #No comprime el archivo con el comando -cf y con -P para que no se pierdan los permisos
fi

echo "Copia realizada en $ruta_copia"

exit 0

