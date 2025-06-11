#!/bin/bash

temp=$(mktemp) #Creamos un fichero temporal
tail -n 20 ~/.bash_history > "$temp" #Almacenamos en mkdir los 20 ultimos comandos generados

declare -A cuenta #Array asociativo "diccionario" cuenta
declare -A max_args #Array asociativo "diccionario" maximo argumentos

while read -r linea; do #Lee linea por linea hasta el final

    comando=$(echo "$linea" | cut -d '' -f 1) #Almacena el nombre del comando
    num_args=$(echo "$linea" | wc -w) #Cuenta el numero de palabras de la linea
    cuenta["$comando"]=$((cuenta["$comando"] + 1)) #Incrementa 1 las veces que se ha usado el comando

    if [ -z "${max_args["$comando"]}" ] || [ "$num_args" -gt "${max_args["$comando"]}" ]; then
    #Si nunca habia aparecido o tiene mas argumentos que el anterior maximo

        max_args["$comando"]=$num_args #Se actualiza el numero de argumentos
    fi
done < "$temp" #El fichero del que se leen las lineas es temp

for cmd in "${!cuenta[@]}"; do #Recorre el array cuenta

    echo "Comando: $cmd" #Imprime el nombre del comando
    echo " -> Veces ejecutado: ${cuenta[$cmd]}" #Imprime cuantas veces se ha ejecutado
    echo " -> Máximo número de argumentos: $((max_args[$cmd] - 1))" #Imprime el maximo numero de argumentos
    echo ""
done

rm "$temp" #Eliminamos el fichero temporal

exit 0