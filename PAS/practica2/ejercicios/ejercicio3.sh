#!/bin/bash

if [ $# -lt 2 ]; then

    echo "Uso: $0 archivo_de_acceso.log [repite-si|repite-no]"
    exit 1
fi

archivo="$1" #Argumento 1
modo="$2" #Argumento 2

if [[ ! -f "$archivo" ]]; then #Si archivo no existe

    echo "Archivo no encontrado: $archivo"
    exit 1
fi

if [[ "$modo" != "repite-si" && "$modo" != "repite-no" ]]; then #Si repite-si/no no se ha introducido correctamente

    echo "Modo inválido. Usa \"repite-si\" o \"repite-no\"."
    exit 1
fi

datos=$(grep ' 200 ' "$archivo" | sed -E 's/^([0-9\.]+).*\"[A-Z]+ ([^ ]+).*\" 200.*/\1 \2/')
#grep ' 200 ' "$archivo"    Filtra las lineas HTTP 200
#^([0-9\.]+)                Captura la IP (principio de la línea)
#.*\"[A-Z]+ ([^ ]+)         Dentro del "GET /algo HTTP...", captura la direccioón (/algo)
#.*\" 200                   Verifica que es HTTP 200
#.*/\1 \2/'                 Reemplaza toda la linea por la IP y dirección

if [[ "$modo" == "repite-si" ]]; then #Si repite-si

    echo "$datos" | sort #Imprime datos

else #Si repite-no

    echo "$datos" | sort | uniq -c | sed -E "s/([0-9]+) (.+) (.+)$/\2 \3 --> \1 veces/"
    #$datos" | sort     Muestra los datos ordenados alfabéticamente 
    #uniq -c    Elimina las lineas duplicadas y cuenta cuantas veces aparece cada linea
    #sed -E "s/([0-9]+) (.+) (.+)$/\2 \3 --> \1 veces/"     Imprime el numero de veces
fi

exit 0