#!/bin/bash

if [ $# -lt 1 ] || [ $# -gt 2 ]; then #Comprueba si el número de argumentos es menos de 1 o mas de 2

    echo "Uso: $0 <longitud de la cadena> [tipo de cadena]"
    exit 1
fi

longitud=$1 #Argumento 1
tipo=$2 #Argumento 2

while [[ -z "$tipo" || ( "$tipo" != "alfa" && "$tipo" != "num" && "$tipo" != "alfanum" ) ]]; do
#Mientras tipo este vacio o no se introduzca una cadena válida

    read -p "Introduce el tipo de cadena (alfanum, alfa o num): " tipo #Almacena la respuesta en $tipo
done

case "$tipo" in #Según el tipo de cadena

    alfa) #Alfabético
        tr -dc 'a-zA-Z' < /dev/urandom | head -c "$longitud";;

    num) #Numérico
        tr -dc '0-9' < /dev/urandom | head -c "$longitud";;

    alfanum) #Alfanumérico
        tr -dc 'a-zA-Z0-9' < /dev/urandom | head -c "$longitud";;

esac
    #tr -dc 'a-zA-Z0-9'     Elimina todos los caracteres de que esten en el dominio dado
    #< /dev/urandom         Secuencia aleatoria de bytes
    #head -c "$longitud"    Coge los $longitud primeros bytes

echo #Salto de línea

exit 0