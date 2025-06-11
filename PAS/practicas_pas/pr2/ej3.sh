#!/bin/bash  # Indica que el script debe ejecutarse con el intérprete de bash.

# Descripción del propósito del script:
# El objetivo del script es procesar un archivo de registros de acceso HTTP (por ejemplo, archivos de log),
# filtrar las solicitudes HTTP con código de estado 200 (éxito), extraer solo la dirección IP y la URL,
# ordenar las solicitudes por dirección IP, y opcionalmente contar las solicitudes repetidas o no repetidas
# dependiendo de un argumento opcional.

# Se espera que el script reciba dos parámetros:
# - El nombre del archivo de log a procesar.
# - Un parámetro opcional que puede ser "repite-si" o "repite-no".
# - "repite-si" imprime todas las solicitudes (incluso las repetidas).
# - "repite-no" elimina las solicitudes repetidas y muestra cuántas veces se repitió cada IP.

file=$1  # El primer argumento es el archivo de log que se va a procesar.
mode=$2  # El segundo argumento es el modo de repetición (opcional).

# Crear una variable 'list' que usaremos para almacenar resultados intermedios.
list="tmp.txt"  # El archivo temporal donde guardaremos las solicitudes filtradas.

# Filtrar las solicitudes HTTP 200 (exitosas) y extraer la IP y URL.
# 'grep' busca las líneas que contienen '200', lo que indica que la solicitud fue exitosa.
# 'sed -E' se usa para aplicar una expresión regular extendida que extrae la dirección IP y la URL.
# Explicación de la expresión regular de 'sed':
# s/([0-9\.]+) ... "/[A-Z]+ ([^ ]+) .*/\1 \2/:
#  - '([0-9\.]+)': Captura la dirección IP (compuesta por números y puntos).
#  - '([^ ]+)': Captura la URL después del método HTTP (la URL está entre comillas y es el segundo campo).
#  - El patrón '.*' se refiere a cualquier cosa después de la URL, que no nos interesa.
grep '200' $file | sed -E '
s/([0-9\.]+).*"[A-Z]+ ([^ ]+) .*/\1 \2/
' | sort > $list  # El resultado se ordena por IP y se guarda en el archivo temporal 'tmp.txt'.

# Si el modo es "repite-si", simplemente muestra todas las líneas del archivo temporal.
if [ $mode == "repite-si" ];  # Comprueba si el modo de repetición es "repite-si".
then
  cat $list  # Muestra todas las solicitudes sin eliminar repeticiones.
else
  # Si el modo es "repite-no", eliminamos las líneas duplicadas y mostramos el número de repeticiones por IP.
  uniq -c $list | sed -E 's/^[[:space:]]*([0-9]) (.*)/\2 --> \1 veces/'  # 
  # 'uniq -c' cuenta las repeticiones de las líneas en el archivo temporal 'tmp.txt'.
  # 'sed -E' es utilizado para cambiar el formato de salida, de modo que muestra algo como:
  # "URL --> X veces", donde X es el número de veces que la IP solicitó esa URL.
  # Explicación de la expresión regular en sed:
  # 's/^[[:space:]]*([0-9]) (.*)/\2 --> \1 veces/':
  #  - '^[[:space:]]*': Coincide con cualquier cantidad de espacios en blanco al principio de la línea.
  #  - '([0-9])': Captura el número de repeticiones.
  #  - '(.*)': Captura la URL.
  #  - '\2 --> \1 veces': Reemplaza la línea con el formato "URL --> número de repeticiones veces".
fi

# Elimina el archivo temporal 'tmp.txt' para limpiar los archivos generados.
rm $list  # Elimina el archivo temporal para no dejar archivos innecesarios.
