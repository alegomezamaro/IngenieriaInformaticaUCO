#Escribe una funci´on en bash que permita generar un fichero de índice para un directorio que
#reciba como parámetro. Dicho índice, deberá contener en, formato HTML, un listado con los
#ficheros y directorios que contenga. En HTML, una lista se puede especificar mediante las etiquetas
#<ul> (apertura) y </ul> (cierre). Los elementos de la lista se indican entre la etiqueta
#de apertura y la de cierre utilizando una etiqueta <li></li> por cada elemento. Además, los
#elementos asociados con directorios deberán tener un enlace que permita navegar hacia el índice
#de dicho directorio. Para ello, se puede utilizar la etiqueta <a></a>, como se muestra en el siguiente ejemplo:

#Una vez implementada dicha función, crea un script que reciba como único argumento la ruta
#de un directorio existente y genere, utilizando la función implementada, los índices de dicho
#directorio y de todos los subdirectorios que contenga, de forma recursiva. Recuerda realizar los controles de errores que estimes oportunos.
#A continuación se muestra un ejemplo de ejecuci ´on del script:

#!/bin/bash

if [ $# -ne 1 ]; then #Comprueba si el número de argumentos es 1

    echo "Uso: $0 <directorio>"
    
    exit 1

fi

directorio=$1 #Argumento 1

if [ ! -d "$1" ]; then #Comprueba si el directorio existe

    echo "Error: El directorio no existe"

    exit 1

fi

lista=("$directorio:$directorio")  #Guardamos todos los directorios

while [ ${#lista[@]} -gt 0 ]; do #Mientras haya directorios

    
    entrada="${lista[0]}" #Obtenemos el primer directorio
    
    lista=("${lista[@]:1}") #Eliminamos el primer directorio
    
    dir="${entrada%%:*}" #Obtenemos el directorio
    
    ruta_relativa="${entrada#*:}" #Obtenemos la ruta relativa
    
    echo "<!DOCTYPE html>" > "$dir/index.html" #Crear el fichero index.html
    
    echo "<html><body>" >> "$dir/index.html" #Añadir el cuerpo del fichero
    
    echo "<h1>Contenido de $ruta_relativa</h1>" >> "$dir/index.html" #Añadir el título
    
    echo "<ul>" >> "$dir/index.html" #Añadir la lista

    for elemento in "$dir"/*; do #Recorremos los elementos del directorio

        nombre=$(basename "$elemento") #Obtenemos el nombre del elemento

        if [ "$nombre" = "index.html" ]; then #Si el nombre es index.html, se salta

            continue
        fi

        if [ -d "$elemento" ]; then #Si es un directorio

            echo "<li><a href=\"$nombre/index.html\">$nombre</a></li>" >> "$dir/index.html" #Añadir el enlace al index.html
    
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