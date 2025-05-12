#!/bin/bash

# Utilizar el comando ifconfig para mostrar las interfaces de red disponibles. En base a su resultado, para cada interfaz, queremos extraer:

# 1. La direccion IP que tiene asignada.
# 2. La direccion de broadcast y la mascara de red. Para la m ´ ascara de red, queremos obtener el numero de unos a la izquierda de la IP que estamos utilizando (tıpicamente, 8, 16 o 24, pero debes hacerlo convirtiendo la mascara de red
# 3. Comprobar si tiene el cable conectado. Para ello, utilizar la herramienta ethtool y comprobar si la opcion “Link detected = yes” aparece como afirmativa.
# 4. De nuevo, utilizando ethtool, enumerar las velocidades a las que puede trabajar la interfaz y cuales de ellas est ´ an anunciadas como disponibles. ´
# A continuacion, se muestra un ejemplo de la salida de este ´ script :

function show(){
  echo "Interfaz: $intfz"
  echo "-> Dirección IP: $ip"
  echo "-> Broadcast: ${bc:-0.0.0.0}"
  # Pasamos la netmask a bytes
  echo "-> Máscara de red: $(count_ones_ip "$netmask") bits"
  echo "-> Cable conectado: $link"
  echo "-> Velocidades soportadas: ${vs:-No disponible}"
  echo "-> Velocidades anunciadas como disponibles: ${vd:-No disponible}"
  echo " "
}

function count_ones_ip() {
    bin_ip=$(convert_ip_to_bin $1)
    #quito el \n de bin_ip para evitar un caracter
    echo -n "$bin_ip" | sed 's/[^1]//g' | wc -c
}

function convert_to_bin() {
    echo "obase=2; $1" | bc | awk '{printf "%08d", $1}'
}

function convert_ip_to_bin() {
    ip=$1
    IFS='.' read -r octet1 octet2 octet3 octet4 <<< "$ip"

    bin_octet1=$(convert_to_bin $octet1)
    bin_octet2=$(convert_to_bin $octet2)
    bin_octet3=$(convert_to_bin $octet3)
    bin_octet4=$(convert_to_bin $octet4)

  echo "$bin_octet1.$bin_octet2.$bin_octet3.$bin_octet4"
}

#metemos en $file solo las lineas que nos interesan de ifconfig
file="ifconfig.txt"
ifconfig | grep -E 'flags|inet ' > "$file"

#iteramos por las lineas de $file
while read -r line; do
  # Caso de que la linea contenga 'flags' -> Interfaz : 
  if [[ $line == *flags* ]]; then
    # Guardamos interfaz en $intfz
    intfz=$(echo "$line" | awk '{
      gsub(":","",$1);
      print $1
    }')
  # Caso de que sea 'inet '
  else
    # Sacamos IP, Netmask y Broadcast
    ip=$(echo "$line" | awk '{print $2}')
    netmask=$(echo "$line" | awk '{print $4}')
    bc=$(echo "$line" | awk '{print $6}')

    # Sacar Link, SV, SC
    eth_file="eth.txt"
    ethtool $intfz > $eth_file
    # Link traducimos ya el si o el no
    link=$(awk -F': ' '/Link detected/{
      if ($2 == "yes")
        print "Si"
      else
        print "No"
    }' $eth_file)
    # Supported Modes : Seguimos cogiendo info hasta llegar
    # a una línea que tenga XXX: XXX
    # A cada info que pillamos le quitamos las tabulaciones
    vs=$(awk -F': ' '/Supported link modes/{
      gsub("^[[:space:]]+","",$2)
      list = $2
      while(getline && $2 == ""){
        gsub("^[[:space:]]+","",$1)
        list = list " " $1
      }
      print list
    }' $eth_file)
    # Avertides Modes : Igual que Supported Modes
    vd=$(awk -F': ' '/Advertised link modes/{
      gsub("^[[:space:]]+","",$2)
      list = $2
      while(getline && $2 == ""){
        gsub("^[[:space:]]+","",$1)
        list = list " " $1
      }
      print list
    }' $eth_file)
    # Comprobamos vs y vd

    # Imprimos info
    show
  fi
done < $file

rm "$file"
rm "$eth_file"

