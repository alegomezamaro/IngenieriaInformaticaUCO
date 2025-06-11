#!/bin/bash

# Verificar si se proporciona un argumento (el directorio)
# El script espera recibir exactamente un argumento: el directorio que se quiere procesar.
# Si no se proporciona el argumento o hay más de uno, se muestra un mensaje de error y el script termina.
if [ $# -ne 1 ]; then
    echo "Uso: $0 <directorio>"
    exit 1
fi

# Asignar el argumento proporcionado al script a la variable 'directorio'
directorio=$1

# Verificar si el directorio especificado existe
# Si el directorio no existe (es decir, si no es un directorio válido), se muestra un mensaje de error y el script termina.
if [ ! -d "$directorio" ]; then
    echo "Error: El directorio '$directorio' no existe."
    exit 1
fi

# Listar los archivos del directorio recursivamente sin incluir directorios
# 'find' busca todos los archivos (no directorios) dentro del directorio especificado y sus subdirectorios.
# Luego, por cada archivo encontrado, se ejecuta el bloque de código dentro del bucle 'while'.
find "$directorio" -type f | while read -r archivo; do
    # 'basename' obtiene solo el nombre del archivo, sin su ruta
    nombre=$(basename "$archivo")
    
    # 'realpath' obtiene la ruta absoluta del archivo, sin importar la ruta relativa
    ruta=$(realpath "$archivo")
    
    # 'stat -c %Y' obtiene la fecha de la última modificación del archivo en formato de timestamp (segundos desde la época Unix)
    fecha_modificacion=$(stat -c %Y "$archivo")
    
    # 'stat -c %s' obtiene el tamaño del archivo en bytes
    tamano=$(stat -c %s "$archivo")
    
    # 'stat -c %A' obtiene los permisos del archivo en formato legible para el ser humano
    permisos=$(stat -c %A "$archivo")
    
    # Imprime el nombre, ruta, fecha de modificación, tamaño en bytes y permisos del archivo
    # Los valores se separan por tabuladores (\t) para una presentación más ordenada
    echo -e "$nombre\t$ruta\t$fecha_modificacion\t$tamano bytes\t$permisos"
done | sort -k 3 -n  # Ordenar la salida por la fecha de modificación (columna 3) en orden numérico (n)