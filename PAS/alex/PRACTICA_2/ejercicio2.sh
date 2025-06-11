#!/bin/bash

if [ $# -ne 1 ] && [ ! -f "$1" ]; then

    echo "Uso $0 <libros.txt>"

    exit 1

fi

fichero=$1

cat $fichero | sed -E "

    /^$/d

    s/_//g

    s/Autor:/| -> Autor:/
    s/Año:/| -> Año:/
    s/Precio:/| -> Precio:/
    s/\[Género:/| -> Género:/; s/\]$//

"
exit 0

#/^$/d: borra las lineas vacias

#s/_//g: elimina las lineas subrayadas

#s/^Autor:/| -> Autor:/ : sustituye al comienzo de una linea Autor: por | -> Autor: y asi con todos  

#s/^\[Género:/| -> Género:/; s/\]$//: sustituye al comienzo de una linea [Género: por | -> Género:  ; como carácter separador de dos comandos sed s/\]$// Reemplaza el patrón encontrado (el corchete de cierre al final de la línea) por nada (lo elimina).

cat $fichero | sed -re "s/Autor: (.+)/\| -> Autor: \1/" | sed -re "s/Año: (.+)/\| -> Año: \1/" | sed -re "s/Precio: (.+)/\| -> Precio: \1/" | sed -re "s/\[Género: (.+)\]/\| -> Género \1/"