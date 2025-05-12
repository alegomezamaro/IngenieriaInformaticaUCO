#!/bin/bash

if [ $# -ne 1 ] || [ ! -f "$1" ] || [[ $1 != *.txt ]]; then #1 argumento, tipo fichero que acabe en .txt
    echo "Argumentos erróneos. Uso: $0 <fichero.txt>"
    exit 1
fi

archivo=$1

sed '/^$/d' "$archivo" |    #Elimina líneas vacías
sed 's/^Autor:/| -> Autor:/' |      #"Autor:" a "-> Autor:"
sed 's/^Año:/| -> Año:/' |      #"Año:" a "-> Año:"
sed 's/^Precio:/| -> Precio:/' |    #"Precio:" a "-> Precio:"
sed 's/^\[Género:/| -> Género:/' | sed 's/\]//' |    #"[Genero: ...]" a "-> Genero: ..."
tee libros_formateados.txt  #Muestra por pantalla y guarda en fichero

exit 0