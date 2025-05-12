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

ficheros=$(find $directorio -type f)

for fichero in $ficheros; do

    nombre=$(basename $fichero) #Nombre del fichero
    ruta=$fichero #Ruta del fichero
    tam=$(stat -c %s $fichero) #Tamaño del fichero
    #%s     Tamaño en bytes del fichero

    permisos=$(stat -c %A $fichero) #Permisos del fichero
    #%A     Permisos (-rwxr-xr--)
    
    fecha_mod=$(stat -c %Y $fichero) #Fecha de modificación
    #%Y     Timestamp unix (cuando fue modificado en segundos desde 1970)

    echo -e "$nombre\t$ruta\t$tam bytes\t$permisos\t$fecha_mod" #Imprime dividiento en tabuladores (\t)
done | sort -k5 -n  #Ordena por fecha de modificación
#sort -k5 -n    Ordena por el quinto campo (fecha_mod) en por formato numérico

exit 0