#Este ejercicio consiste en utilizar sed y grep para analizar un archivo de acceso web de un
#servidor Apache, como viene en el fichero access.log.
#El archivo de acceso contiene registros de solicitudes HTTP a un servidor Apache, y cada línea
#sigue el formato estándar de acceso de Apache, que incluye la dirección IP, fecha y hora, tipo de
#solicitud, URL solicitada, código de respuesta HTTP, y tamaño de la respuesta en bytes.
#El objetivo de este ejercicio es crear un script en bash utilizando sed y grep que realice lo siguiente:
#Filtrar las líneas que contienen solicitudes exitosas (código de respuesta HTTP 200).
#Extraer solo la dirección IP y la URL solicitada de esas líneas.
#Ordenar las solicitudes por dirección IP y mostrar el resultado, repitiendo las líneas cuando
#una misma IP pide el mismo recurso en distintas fechas.
#Opcionalmente (estableciendo repite-no en lugar de repite-si), eliminar las líneas
#que contienen solicitudes de un mismo cliente repetidas, dejando solo la primera aparici´on.
#El script debe ejecutarse de la siguiente manera:
#./ejercicio3.sh archivo_de_acceso.log [repite-si,repite-no]
#donde archivo de acceso.log es el archivo que contiene los registros de acceso del servidor
#Apache. Si el script se invoca con repite-si entonces se repetirán los accesos de la misma IP, si
#se invoca con repite-no entonces no se repetirán y se incluirá el número total de accesos.
#A continuación, se muestra un ejemplo de la salida de este script :

#!/bin/bash


# Comprobación de argumentos
if [ $# -lt 2 ]; then

    echo "Uso $0 <archivo_acceso.log> [repite-si|repite-no]"

    exit 1

fi

archivo=$1

cadena=$2


#Comprobamos si archivo es un fichero normal
if [ ! -f $archivo ]; then

    echo "Error el archivo $archivo no se encuentra"

    exit 1

fi

#Comprobamos que modo sea repite-si o repite-no

if [ $cadena != "repite-si" ] && [ $cadena != "repite-no" ]; then

    echo "Error, tienes que poner repite-si ó repite-no"

    exit 1

fi

# Extraer IP y URL solo de líneas con código 200

datos=$(cat $archivo | grep -E "200" | sed -E "s/([0-9\.]+).*\"[A-Z]+ ([^ ]+).*\" 200.*/\1 \2/")

if [ $cadena == "repite-si" ]; then

    echo "$datos" | sort #Muestra los datos y los ordena alfabéticamente las líneas de entrada (se ordenan primero por IP y luego por URL)

else

    echo "$datos" | sort | uniq -c | sed -E "s/([0-9]+) (.+) (.+)$/\2 \3 --> \1 veces/"

    #Muestra los datos y los ordena alfabéticamente las líneas de entrada (se ordenan primero por IP y luego por URL)
    #uniq -c: elimina las lineas duplicadas y cuenta cuantas veces aparece cada linea

fi

exit 0