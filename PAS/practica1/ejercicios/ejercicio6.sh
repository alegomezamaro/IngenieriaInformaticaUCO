#!/bin/bash

if [ $# -ne 1 ]; then

    echo "Uso: $0 <directorio>"
    exit 1
fi

directorio=$1 #Argumento 1

if [ ! -d "$directorio" ]; then

    echo "Error: El directorio no existe"
    exit 1
fi

lista=("$directorio:$directorio") #Guardamos dos directorios (directorio:ruta_relativa)

while [ ${#lista[@]} -gt 0 ]; do #Mientras haya elementos en lista 

    entrada="${lista[0]}" #Obtenemos el primer elemento del array
    lista=("${lista[@]:1}") #Eliminamos el primer elemento del array
    dir="${entrada%%:*}" #Elimina de : en adelante ("$directorio:$ruta_relativa" -> "$directorio")
    ruta_relativa="${entrada#*:}" #Elimina del inicio a : ("$directorio:$ruta_relativa" -> "$ruta_relativa")
    
    echo "<!DOCTYPE html>" > "$dir/index.html" #Creamos el fichero index.html
    echo "<html><body>" >> "$dir/index.html" #Añadir el cuerpo del fichero
    echo "<h1>Contenido de $ruta_relativa</h1>" >> "$dir/index.html" #Añadimos el título
    echo "<ul>" >> "$dir/index.html" #Añadimos la lista

    for elemento in "$dir"/*; do #Recorremos los elementos del directorio

        nombre=$(basename "$elemento") #Obtenemos el nombre del elemento

        if [ "$nombre" = "index.html" ]; then #Si el nombre es index.html, se salta

            continue
        fi

        if [ -d "$elemento" ]; then #Si es un directorio

            echo "<li><a href=\"$nombre/index.html\">$nombre</a></li>" >> "$dir/index.html" #Añadir el enlace a index.html
            lista+=("$elemento:$ruta_relativa/$nombre") #Añadir el directorio a la lista

        else #Sino

            echo "<li>$nombre</li>" >> "$dir/index.html" #Añadir el nombre del fichero al index.html
        fi
    done

    echo "</ul>" >> "$dir/index.html" #Cerrar la lista
    echo "</body></html>" >> "$dir/index.html" #Cerrar el fichero
    echo "Se ha creado el fichero $dir/index.html con el contenido del directorio $ruta_relativa" # Muestra un mensaje indicando que se ha creado el archivo index.html con el contenido del directorio correspondiente
done

exit 0