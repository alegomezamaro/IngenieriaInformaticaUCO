#Utilizar el comando ifconfig para mostrar las interfaces de red disponibles. En base a su resultado, para cada interfaz, queremos extraer:

#1. La dirección IP que tiene asignada.

#2. La dirección de broadcast y la máscara de red. Para la máscara de red, queremos obtener el número de unos a la izquierda de la IP que estamos utilizando (típicamente, 8, 16 o 24, pero
#debes hacerlo convirtiendo la máscara de red2).

#3. Comprobar si tiene el cable conectado. Para ello, utilizar la herramienta ethtool y comprobar si la opción “Link detected” aparece como afirmativa.

#4. De nuevo, utilizando ethtool, enumerar las velocidades a las que puede trabajar la interfaz y cuáles de ellas están anunciadas como disponibles.

#!/bin/bash

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
echo "Obteniendo interfaces de red..."
interfaces=$(ip -o link show | grep -oP '^\d+: \K[^:]+')

# Si no se encuentran interfaces, mostramos un mensaje
if [ -z "$interfaces" ]; then
    echo "No se han encontrado interfaces de red."
    exit 1
fi

# Procesamos cada interfaz
for iface in $interfaces; do
    echo "Procesando la interfaz: $iface"
    
    # Verificamos si la interfaz tiene una dirección IP asignada
    ip=$(ip addr show $iface | grep -oP 'inet \K[^/]+')
    
    if [ -n "$ip" ]; then
        # 1. Mostramos el nombre de la interfaz
        echo "Interfaz: $iface"
        
        # 2. Extraemos la dirección IP
        echo " -> Dirección IP: $ip"
        
        # 3. Extraemos la dirección de broadcast y la máscara de red utilizando ip
        broadcast=$(ip addr show $iface | grep -oP 'broadcast \K[^ ]+')
        netmask=$(ip addr show $iface | grep -oP 'inet \K[^/]+$' | sed 's/.*\///')
        echo " -> Broadcast: $broadcast"
        
        # 4. Calculamos el número de unos en la máscara de red
        # Convertimos la máscara de red de decimal a binario
        mask_dec=$netmask
        binary_mask=$(echo "obase=2; $mask_dec" | bc)
        ones=$(echo $binary_mask | tr -cd '1' | wc -c)
        echo " -> Máscara de red: $ones bits"
        
        # 5. Comprobamos si el cable está conectado con ethtool
        cable_connected=$(ethtool $iface | grep -i 'Link detected' | grep -oP '\w+$')
        if [ "$cable_connected" == "yes" ]; then
            echo " -> Cable conectado: Sí"
        else
            echo " -> Cable conectado: No"
        fi
        
        # 6. Obtenemos las velocidades soportadas y anunciadas con ethtool
        supported_speeds=$(ethtool $iface | grep -i 'Supported ports' | sed 's/^.*Supported ports: //')
        advertised_speeds=$(ethtool $iface | grep -i 'Advertised speeds' | sed 's/^.*Advertised speeds: //')
        
        # Si no hay velocidades soportadas o anunciadas, mostramos "No disponible"
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

#SE EJECUTA CON  sudo ./ejercicio5.sh

