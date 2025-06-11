#!/bin/bash

if [ $# -ne 1 ] || [ $1 -lt 0 ]; then

    echo "Error debe de haber dos argumentos, uno mayor que 0 y otro que se opcional alfa, num o alfanum"
    
    exit 1

fi

longitud=$1

cadena=$2

while [ "$cadena" != "alfa" ] || [ "$cadena" != "num" ] || [ "$cadena" != "alfanum" ]; do #OJO CUIDADO CON "$cadena" aqui pongo entre "" ya que al principio se desconoce el valor ya que no le damos ninguno 
    
    echo "Introduce por teclado la cadena correcta: alfa, num o alfanum"

    read cadena

    if [ $cadena == "alfa" ] || [ $cadena == "num" ] || [ $cadena == "alfanum" ]; then

        break

    fi

done

variable1=$(tr -dc A-Za-z < /dev/urandom | head -c $longitud) #tr: elimina caracteres no deseados, -dc: elimina los caracteres que no estén en el rango A-Za-z, < /dev/urandom: genera caracteres aleatorios, head -c $longitud: muestra los primeros $longitud caracteres

variable2=$(tr -dc 0-9 < /dev/urandom | head -c $longitud)  #tr: elimina caracteres no deseados, -dc: elimina los caracteres que no estén en el rango A-Za-z, < /dev/urandom: genera caracteres aleatorios, head -c $longitud: muestra los primeros $longitud caracteres

variable3=$(tr -dc A-Za-z0-9 < /dev/urandom | head -c $longitud) #tr: elimina caracteres no deseados, -dc: elimina los caracteres que no estén en el rango A-Za-z, < /dev/urandom: genera caracteres aleatorios, head -c $longitud: muestra los primeros $longitud caracteres

if [ $cadena == "alfa" ]; then

    echo "La cadena alfa es: $variable1"

fi

if [ $cadena == "num" ]; then

    echo "La cadena num es: $variable2"

fi

if [ $cadena == "alfanum" ]; then

    echo "La cadena alfanum es: $variable3"

fi

exit 0

