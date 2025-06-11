#!/bin/bash

# Utilizar el comando ifconfig para mostrar las interfaces de red disponibles. En base a su resultado, para cada interfaz, queremos extraer:

# 1. La direccion IP que tiene asignada.
# 2. La direccion de broadcast y la mascara de red. Para la máscara de red, queremos obtener el número de unos a la izquierda de la IP que estamos utilizando (típicamente, 8, 16 o 24, pero debes hacerlo convirtiendo la máscara de red).
# 3. Comprobar si tiene el cable conectado. Para ello, utilizar la herramienta ethtool y comprobar si la opción “Link detected = yes” aparece como afirmativa.
# 4. De nuevo, utilizando ethtool, enumerar las velocidades a las que puede trabajar la interfaz y cuales de ellas están anunciadas como disponibles.
# A continuación, se muestra un ejemplo de la salida de este script:

function show(){
  # Muestra la información de la interfaz
  echo "Interfaz: $intfz"
  echo "-> Dirección IP: $ip"  # Dirección IP de la interfaz
  echo "-> Broadcast: ${bc:-0.0.0.0}"  # Dirección de broadcast, por defecto 0.0.0.0 si no está disponible
  # Convertimos la máscara de red a bits y mostramos la cantidad de unos (máscara en formato de bits)
  echo "-> Máscara de red: $(count_ones_ip "$netmask") bits"
  echo "-> Cable conectado: $link"  # Si el cable está conectado o no
  echo "-> Velocidades soportadas: ${vs:-No disponible}"  # Velocidades soportadas por la interfaz
  echo "-> Velocidades anunciadas como disponibles: ${vd:-No disponible}"  # Velocidades anunciadas por la interfaz
  echo " "
}

function count_ones_ip() {
    # Función para contar los unos en la máscara de red (la cantidad de bits activos)
    bin_ip=$(convert_ip_to_bin $1)  # Convertimos la máscara a binario
    # Quitamos los caracteres que no son '1' y contamos cuántos '1's hay
    echo -n "$bin_ip" | sed 's/[^1]//g' | wc -c  # wc -c cuenta el número de caracteres
}

function convert_to_bin() {
    # Función para convertir un número decimal a binario de 8 bits
    echo "obase=2; $1" | bc | awk '{printf "%08d", $1}'  # 'obase=2' convierte a binario y 'awk' lo formatea a 8 bits
}

function convert_ip_to_bin() {
    # Función para convertir una IP (formato 'x.x.x.x') a binario
    ip=$1
    IFS='.' read -r octet1 octet2 octet3 octet4 <<< "$ip"  # Divide la IP en 4 octetos

    # Convertimos cada octeto a binario
    bin_octet1=$(convert_to_bin $octet1)
    bin_octet2=$(convert_to_bin $octet2)
    bin_octet3=$(convert_to_bin $octet3)
    bin_octet4=$(convert_to_bin $octet4)

    # Regresamos la IP en formato binario
    echo "$bin_octet1.$bin_octet2.$bin_octet3.$bin_octet4"
}

# Creamos un archivo con las líneas relevantes de la salida de ifconfig
file="ifconfig.txt"
ifconfig | grep -E 'flags|inet ' > "$file"  # Filtramos solo las líneas que contienen 'flags' o 'inet' (información de la interfaz)

# Iteramos por cada línea del archivo $file
while read -r line; do
  # Caso en que la línea contenga 'flags' (esto indica una nueva interfaz)
  if [[ $line == *flags* ]]; then
    # Extraemos el nombre de la interfaz y lo guardamos en la variable $intfz
    intfz=$(echo "$line" | awk '{
      gsub(":","",$1);  # Eliminamos los dos puntos de la interfaz
      print $1  # Imprimimos solo el nombre de la interfaz
    }')
  # Caso en que la línea contenga 'inet' (dirección IP)
  else
    # Extraemos la dirección IP, la máscara de red (netmask) y la dirección de broadcast
    ip=$(echo "$line" | awk '{print $2}')  # Dirección IP
    netmask=$(echo "$line" | awk '{print $4}')  # Máscara de red
    bc=$(echo "$line" | awk '{print $6}')  # Dirección de broadcast

    # Obtener información sobre el estado de la interfaz y las velocidades utilizando ethtool
    eth_file="eth.txt"
    ethtool $intfz > $eth_file  # Guardamos la salida de ethtool en un archivo temporal

    # Extraemos el estado del cable (si está conectado o no)
    link=$(awk -F': ' '/Link detected/{
      if ($2 == "yes")
        print "Si"  # Si el cable está conectado
      else
        print "No"  # Si el cable no está conectado
    }' $eth_file)

    # Extraemos las velocidades soportadas por la interfaz (Supported link modes)
    vs=$(awk -F': ' '/Supported link modes/{
      gsub("^[[:space:]]+","",$2)  # Quitamos los espacios en blanco
      list = $2
      while(getline && $2 == ""){  # Continuamos leyendo hasta encontrar una línea con datos
        gsub("^[[:space:]]+","",$1)  # Quitamos más espacios en blanco
        list = list " " $1
      }
      print list  # Imprimimos la lista de velocidades soportadas
    }' $eth_file)

    # Extraemos las velocidades anunciadas como disponibles (Advertised link modes)
    vd=$(awk -F': ' '/Advertised link modes/{
      gsub("^[[:space:]]+","",$2)  # Quitamos los espacios en blanco
      list = $2
      while(getline && $2 == ""){  # Continuamos leyendo hasta encontrar una línea con datos
        gsub("^[[:space:]]+","",$1)  # Quitamos más espacios en blanco
        list = list " " $1
      }
      print list  # Imprimimos la lista de velocidades anunciadas
    }' $eth_file)

    # Imprimimos toda la información recopilada de la interfaz
    show
  fi
done < $file  # Leemos el archivo línea por línea

# Limpiamos los archivos temporales generados
rm "$file"
rm "$eth_file"
