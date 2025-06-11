#!/bin/bash

# Verificar si se proporciona al menos un argumento
# El número de argumentos que debe recibir el script es 1 o 2.
# Si no se proporcionan los argumentos correctamente, se muestra el mensaje de uso y se termina el script.
if [ $# -lt 1 ] || [ $# -gt 2 ]; then
    echo "Uso: $0 <longitud de la cadena> [tipo de cadena]"
    exit 1
fi

# Asignamos el primer argumento a la variable 'longitud'
# Este valor indica cuántos caracteres debe tener la cadena aleatoria.
longitud=$1

# Asignamos el segundo argumento a la variable 'tipo'
# Este valor es opcional y especifica el tipo de caracteres que debe tener la cadena (alfanum, alfa, num).
tipo=$2

# Validar que la longitud sea un número entero positivo
# Aquí usamos una expresión regular para asegurarnos de que 'longitud' sea solo un número entero positivo.
# Además, verificamos que la longitud no sea menor o igual a cero.
# Expresion regular: ^[0-9]+$ significa que solo se permiten dígitos del 0 al 9.
# ^: Indica el inicio de la cadena.
# [0-9]+: Indica que debe haber al menos un dígito (uno o más).
# $: Indica el final de la cadena.
if ! [[ "$longitud" =~ ^[0-9]+$ ]] || [ "$longitud" -le 0 ]; then
    echo "Error: La longitud debe ser un número entero positivo."
    exit 1
fi

# Si no se proporciona el tipo de cadena (es decir, 'tipo' está vacío),
# o si el tipo es incorrecto, se entra en el bucle 'while' para pedir al usuario que lo ingrese.
# Los tipos válidos son: alfanum, alfa o num.
while [[ -z "$tipo" || ! "$tipo" =~ ^(alfanum|alfa|num)$ ]]; do
    # Mostramos un mensaje al usuario indicando los tipos válidos.
    # El uso de 'read -p' permite leer la entrada del usuario y asignarla a la variable 'tipo'.
    # -p: Permite mostrar un mensaje antes de la entrada del usuario.
    # Leer la entrada del usuario para 'tipo', obligando a introducir uno de los valores válidos.
    read -p "Introduce el tipo de cadena (alfanum, alfa o num): " tipo
done

# Según el tipo de cadena seleccionado, definimos el conjunto de caracteres que se pueden usar en la cadena aleatoria.
# Usamos una estructura 'case' para asignar los caracteres válidos a la variable 'caracteres'.

case "$tipo" in
    (alfa)
        # Solo se permitirán letras mayúsculas y minúsculas.
        caracteres='A-Za-z'
        ;;
    (num)
        # Solo se permitirán dígitos numéricos.
        caracteres='0-9'
        ;;
    (alfanum)
        # Se permitirán tanto letras (mayúsculas y minúsculas) como números.
        caracteres='A-Za-z0-9'
        ;;
esac

# Generamos la cadena aleatoria usando una serie de comandos:
# - cat /dev/urandom: Genera datos aleatorios.
# - tr -dc "$caracteres": Elimina todos los caracteres que no están en el conjunto '$caracteres'.
# - head -c "$longitud": Limita la salida a la longitud especificada por el usuario.
# El resultado final se almacena en la variable 'cadena'.

cadena=$(cat /dev/urandom | tr -dc "$caracteres" | head -c "$longitud")

# Imprimimos la cadena aleatoria generada.
echo "$cadena"