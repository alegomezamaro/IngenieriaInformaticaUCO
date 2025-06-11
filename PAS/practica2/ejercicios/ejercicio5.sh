#!/bin/bash

# Utilizar el comando ifconfig para mostrar las interfaces de red disponibles. En base a su resultado, para cada interfaz, queremos extraer:

# 1. La direccion IP que tiene asignada.
# 2. La direccion de broadcast y la mascara de red. Para la mascara de red, queremos obtener el numero de unos a la izquierda de la IP que estamos utilizando (tıpicamente, 8, 16 o 24, pero debes hacerlo convirtiendo la mascara de red
# 3. Comprobar si tiene el cable conectado. Para ello, utilizar la herramienta ethtool y comprobar si la opcion “Link detected = yes” aparece como afirmativa.
# 4. De nuevo, utilizando ethtool, enumerar las velocidades a las que puede trabajar la interfaz y cuales de ellas est ´ an anunciadas como disponibles. ´
# A continuacion, se muestra un ejemplo de la salida de este ´ script :

# Comprobamos que tenemos la herramienta 'ip' instalada
if ! command -v ip &> /dev/null; then
    echo "El comando 'ip' no está instalado. Instálalo y vuelve a intentarlo."
    exit 1
fi

# Comprobamos que tenemos la herramienta 'ethtool' instalada
if ! command -v ethtool &> /dev/null; then
    echo "El comando 'ethtool' no está instalado. Instálalo y vuelve a intentarlo."
    exit 1
fi

# Obtenemos la lista de interfaces de red disponibles
interfaces=$(ip -o link show | grep -oP '^\d+: \K[^:]+')

# Si no se encuentran interfaces, mostramos un mensaje
if [ -z "$interfaces" ]; then
    #-z     Longitud cero 
    echo "No se han encontrado interfaces de red."
    exit 1
fi

#Para cada interfaz
for iface in $interfaces; do

    # Verificamos si la interfaz tiene una dirección IP asignada
    ip=$(ip addr show $iface | grep -oP 'inet \K[^/]+')
    #ip addr show $iface    Muestra la interfaz
    #grep -oP 'inet \K[^/]+'    Almacena la IP sin máscara

    #Si no tiene 
    if [ -n "$ip" ]; then

        #1. Mostramos el nombre de la interfaz
        echo "Interfaz: $iface"

        #2. Extraemos la dirección IP
        echo " -> Dirección IP: $ip"
        
        #3. Extraemos la dirección de broadcast y la máscara de red utilizando IP
        broadcast=$(ip addr show $iface | grep -oP 'broadcast \K[^ ]+')
            #Busca el broadcast asociado a la IP
        echo " -> Broadcast: $broadcast"
        
        #4. Calculamos el número de unos en la máscara de red OPCION DIRECTA
        #mask=$(ip addr show $iface | grep -oP 'inet [^/]+/\K[0-9]+')
            #Obtenemos la mascara de red desde la IP
        #echo " -> Máscara de red: $mask bits"

        #4. Calculamos el número de unos en la máscara de red
        #Obtenemos el CIDR de la interfaz
        cidr=$(ip addr show $iface | grep -oP 'inet \K[^ ]+' | cut -d/ -f2) 
        #Construimos la mascara binaria
        binary_mask=$(printf "%*s" "$cidr" "" | tr ' ' '1')
        #Contamos los unos
        ones=$(echo "$binary_mask" | tr -cd '1' | wc -c) 
        echo " -> Máscara de red: $ones bits"
        
        #5. Comprobamos si el cable está conectado con ethtool
        cable_connected=$(ethtool $iface | grep -i 'Link detected' | grep -oP '\w+$')
        if [ "$cable_connected" == "yes" ]; then
            echo " -> Cable conectado: Sí"
        else
            echo " -> Cable conectado: No"
        fi
        
        #6. Obtenemos las velocidades soportadas y anunciadas con ethtool
        supported_speeds=$(ethtool $iface | grep -i 'Supported ports' | sed 's/^.*Supported ports: //')
        advertised_speeds=$(ethtool $iface | grep -i 'Advertised speeds' | sed 's/^.*Advertised speeds: //')
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