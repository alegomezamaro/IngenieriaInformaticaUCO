#!/bin/bash  

# Comprobamos si el número de argumentos pasados al script es diferente de 1.
if [ $# -ne 1 ]; then
    # $#: Es una variable especial en Bash que *contiene el número de argumentos* pasados al script.
    # Si no se pasa exactamente un argumento (el directorio), mostramos un mensaje de uso y terminamos el script.
    # -ne: Es un operador que significa *"no es igual"* (not equal). Se usa para comparar si dos valores no son iguales.
    echo "Uso: $0 <directorio>"  # $0 es el nombre del script, y lo usamos para indicar al usuario cómo ejecutarlo correctamente.
    exit  # Terminamos el script porque el número de argumentos no es el esperado.
fi

# Asignamos el primer argumento a la variable 'directorio', que será la ruta del directorio que el usuario desea procesar.
directorio=$1  # $1 es el primer argumento pasado al script (en este caso, la ruta del directorio).

# Comprobamos si la ruta especificada NO es un directorio válido.
if [ ! -d "$directorio" ]; then
    # Si no es un directorio válido (la opción -d verifica que el camino sea un directorio),
    # mostramos un mensaje de error y salimos del script.
    echo "El directorio '$directorio' no existe."
    exit  # Terminamos el script si el directorio no existe.
fi

# Usamos 'find' para obtener todos los archivos en el directorio (sin especificar un patrón de archivo específico).
ficheros=$(find "$directorio" -type f -name "*")  # find busca archivos (-type f) en la ruta proporcionada.
# Explicación de las opciones de 'find':
# - "$directorio" es la ruta donde 'find' comenzará a buscar.
# - '-type f' especifica que buscamos solo archivos, no directorios u otros tipos de objetos.
# - '-name ""': El '' significa que buscamos todos los archivos, sin ningún patrón específico (se podrían usar patrones, como "*.txt" para solo archivos de texto).

# Verificamos si la variable 'ficheros' está vacía (es decir, si no se encontraron archivos en el directorio).
if [ -z "$ficheros" ]; then
    # El operador '-z' comprueba si la cadena está vacía. En este caso, si no hay archivos,
    # el comando 'find' no devuelve nada, y 'ficheros' quedaría vacío.
    # Si no se encontraron archivos, mostramos un mensaje y salimos del script.
    echo "No se encontraron ficheros de texto en el directorio '$directorio'."
    exit  # Terminamos el script si no hay archivos.
fi

# 'wc -l' cuenta el número de líneas de un archivo. Utilizamos 'head' para obtener el primer archivo en la lista de 'ficheros'.
# 'head -n 1' obtiene solo el primer archivo de la lista que devuelve 'find'.
num_lineas=$(wc -l < "$(echo "$ficheros" | head -n 1)")  # El < redirige la entrada de 'wc -l' para contar las líneas del primer archivo.

# 'wc -l' es el comando que cuenta las líneas de un archivo. El '<' es una forma de redirigir la entrada estándar a un archivo sin necesidad de usar 'cat'.
# Explicación:
# - 'head -n 1' selecciona el primer archivo de la lista de 'ficheros'.
# - 'wc -l' cuenta el número de líneas del primer archivo, lo que nos da la cantidad de líneas que iteraremos en el bucle.
# El resultado se almacena en 'num_lineas', la variable que indica cuántas líneas tiene el primer archivo.

# Iniciamos un bucle 'for' para recorrer cada línea de los archivos.
# El número de iteraciones es igual al número de líneas del archivo (en este caso, del primer archivo).
for ((i = 1; i <= num_lineas; i++)); do
    suma=0  # Inicializamos la variable 'suma' que acumulará el total de las líneas procesadas en esta iteración.

    # Usamos un bucle 'while' para leer cada archivo de la lista 'ficheros'.
    # 'IFS=' asegura que la línea completa se lea sin dividirla en campos.
    while IFS= read fichero; do
        # Usamos 'head' para obtener las primeras 'i' líneas del archivo y 'tail' para obtener solo la línea 'i'.
        # 'head -n "$i" "$fichero"' obtiene las primeras 'i' líneas del archivo.
        # 'tail -n 1' toma la última de esas líneas, que será la número 'i'.
        valor=$(head -n "$i" "$fichero" | tail -n 1)

        # Sumamos el valor obtenido en esa línea al acumulado en la variable 'suma'.
        suma=$((suma + valor))  # Realizamos la operación aritmética de sumar el valor al total de 'suma'.
    done <<< "$ficheros"  # <<< redirige la lista de archivos a 'read', uno por uno.
    # '<<<' es un operador que redirige una cadena a la entrada estándar del comando.
    # En este caso, la lista de ficheros se pasa a 'read', que la procesará línea por línea.
    
    # Después de procesar todos los archivos, mostramos el total acumulado de personas por sesión.
    echo "Asistieron $suma personas a la sesion $i"
done