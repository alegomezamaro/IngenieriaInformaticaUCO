#!/bin/bash

# Utilizar el comando ifconfig para mostrar las interfaces de red disponibles. En base a su resultado, para cada interfaz, queremos extraer:

# 1. La direccion IP que tiene asignada.
# 2. La direccion de broadcast y la mascara de red. Para la mascara de red, queremos obtener el numero de unos a la izquierda de la IP que estamos utilizando (tıpicamente, 8, 16 o 24, pero debes hacerlo convirtiendo la mascara de red
# 3. Comprobar si tiene el cable conectado. Para ello, utilizar la herramienta ethtool y comprobar si la opcion “Link detected = yes” aparece como afirmativa.
# 4. De nuevo, utilizando ethtool, enumerar las velocidades a las que puede trabajar la interfaz y cuales de ellas est ´ an anunciadas como disponibles. ´
# A continuacion, se muestra un ejemplo de la salida de este ´ script :

# Obtenemos la lista de interfaces de red disponibles
interfaces=$(ifconfig | grep -oE '^[a-zA-Z0-9]+')

# Si no se encuentran interfaces, mostramos un mensaje
if [ -z "$interfaces" ]; then
    #-z     Longitud cero 
    echo "No se han encontrado interfaces de red."
    exit 1
fi

#Para cada interfaz
for iface in $interfaces; do

    # Verificamos si la interfaz tiene una dirección IP asignada
    ip=$(ifconfig "$iface" | grep 'inet addr' | sed -E 's/.*inet addr:([0-9.]+).*/\1/')

    #Si no tiene 
    if [ -n "$ip" ]; then

        #1. Mostramos el nombre de la interfaz
        echo "Interfaz: $iface"

        #2. Extraemos la dirección IP
        echo " -> Dirección IP: $ip"
        
        #3. Extraemos la dirección de broadcast y la máscara de red utilizando IP
        broadcast=$(ifconfig "$iface" | grep 'Bcast' | sed -E 's/.*Bcast:([0-9.]+).*/\1/')
            #Busca el broadcast asociado a la IP
        echo " -> Broadcast: $broadcast"
        
        #4. Calculamos el número de unos en la máscara de red OPCION DIRECTA
        # Máscara decimal
        mask=$(ifconfig "$iface" | grep 'Mask' | sed -E 's/.*Mask:([0-9.]+).*/\1/')
        # Convertimos a binario y contamos los 1
        binary_mask=$(echo $mask | tr '.' ' ' | while read a b c d; do
          printf "%08d%08d%08d%08d\n" \
            "$(echo "obase=2; $a" | bc)" \
            "$(echo "obase=2; $b" | bc)" \
            "$(echo "obase=2; $c" | bc)" \
            "$(echo "obase=2; $d" | bc)"
        done)
        ones=$(echo "$binary_mask" | tr -cd '1' | wc -c)
        echo " -> Máscara de red: $ones bits"
        
        #5. Comprobamos si el cable está conectado con ethtool
        cable_connected=$(ethtool "$iface" 2>/dev/null | grep -i 'Link detected' | grep -o 'yes')
        if [ "$cable_connected" == "yes" ]; then
            echo " -> Cable conectado: Sí"
        else
            echo " -> Cable conectado: No"
        fi
        
        #6. Obtenemos las velocidades soportadas y anunciadas con ethtool
        supported_speeds=$(ethtool "$iface" 2>/dev/null | sed -n '/Supported link modes:/,/^[A-Za-z]/p' | grep -oE '[0-9]+baseT/[A-Za-z]+' | sort -u | tr '\n' ' ')
        advertised_speeds=$(ethtool "$iface" 2>/dev/null | sed -n '/Advertised link modes:/,/^[A-Za-z]/p' | grep -oE '[0-9]+baseT/[A-Za-z]+' | sort -u | tr '\n' ' ')
            #ethtool "$iface"   Muestra la interfaz
            #sed -n '/Supported link modes:/,/^[A-Za-z]/p'  Coge solo cuando empieza por..
            #grep -oE '[0-9]+baseT/[A-Za-z]+'   Extrae solo velocidades
            #sort -u    Elimina duplicados
            #tr '\n' ' '     Pone todo en la misma línea.

        #Si no hay velocidades soportadas o anunciadas, mostramos "No disponible"
        if [ -z "$supported_speeds" ]; then
            supported_speeds="No disponible"
        fi
        if [ -z "$advertised_speeds" ]; then
            advertised_speeds="No disponible"
        fi 
        echo " -> Velocidades soportadas: $supported_speeds"
        echo " -> Velocidades anunciadas como disponibles: $advertised_speeds"

    else
        echo "Interfaz $iface no tiene dirección IP asignada."
    fi
done