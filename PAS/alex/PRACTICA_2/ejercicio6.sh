#Este ejercicio consiste en analizar los últimos 20 comandos ejecutados por el usuario en la terminal utilizando el historial de comandos (.bash history). 
#A partir de estos comandos, el script debe proporcionar la siguiente información:

#1. Contar cuántas veces ha sido ejecutado cada comando.

#2. Determinar cuál ha sido el número máximo de argumentos con los que se ha invocado cada comando.

#NOTA1: para los efectos del ejercicio, no se van a considerar tuberías o el separador “;”. Es decir, el comando de cada línea siempre será la primera palabra y, si hay tuberías, se considera
#que son argumentos al comando detectado al principio de la línea. P.ej.: echo 2 | tail -c 4 contabiliza como un comando echo con 5 argumentos.

#NOTA2: El propio nombre del comando no se contabiliza como argumento.


#!/bin/bash

#Creamos un fichero temporal, donde se almacenará los resultados

temp=$(mktemp)

#Últimos 20 comandos del historial del bash y los mete en el fichero temporal "temp"

tail -n 20 ~/.bash_history > "$temp"

#Procesamos cada línea (declara arrays asociativos)

declare -A cuenta

declare -A max_args

while read -r linea; do #Lee el archivo temporal línea por línea y almacena cada línea en la variable linea.
    
    comando=$(echo "$linea" | cut -d '' -f 1) #Muestra la primera palabra de la linea (corresponde al comando ejecutado)  awk '{print $1}'
    
    num_args=$(echo "$linea" | wc -w) #Cuenta el número de palabras en la línea (incluyendo el comando y sus argumentos).
    
    cuenta["$comando"]=$((cuenta["$comando"] + 1)) #Incrementa el contador del comando en el array cuenta.
    
    if [ -z "${max_args["$comando"]}" ] || [ "$num_args" -gt "${max_args["$comando"]}" ]; then #Si el comando no tiene un valor registrado en max_args ó el número actual de argumentos es mayor que el máximo registrado.
    
        max_args["$comando"]=$num_args #Actualiza el valor de max_args para el comando.
    
    fi

done < "$temp" #Indica que el bucle debe leer las líneas del archivo temporal.

# Mostrar resultados

for cmd in "${!cuenta[@]}"; do #Itera sobre todos los comandos almacenados en el array cuenta.

    echo "Comando: $cmd" #Nombre del comando.

    echo " -> Veces ejecutado: ${cuenta[$cmd]}" #Número de veces que se ejecutó el comando.

    echo " -> Máximo número de argumentos: $((max_args[$cmd] - 1))" #Calcula el número máximo de argumentos, restando 1 para excluir el propio nombre del comando.

    echo ""

done

rm "$temp" #Elimina el archivo temporal creado al inicio del script.

exit 0