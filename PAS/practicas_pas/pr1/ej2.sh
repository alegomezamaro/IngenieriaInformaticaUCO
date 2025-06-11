#!/bin/bash

# Verifica que se pasen exactamente 4 argumentos al script.
if [ $# -ne 4 ]; then     
    echo "Argumentos incorrectos. Uso: $0 <directorio_origen> <directorio_destino> <comprimir 0/1> <sobreescribir 0/1>"
    exit 1  # Si no hay 4 argumentos, muestra el mensaje de error y finaliza la ejecución.
fi

# Asigna los argumentos a variables para mayor claridad.
directorio_origen=$1   # Primer argumento: directorio a copiar.
directorio_destino=$2  # Segundo argumento: directorio donde se almacenará la copia.
compresion=$3          # Tercer argumento: 0 = solo archivar, 1 = archivar y comprimir.
sobreescribir=$4       # Cuarto argumento: 0 = no sobrescribir, 1 = sobrescribir si ya existe.

# Comprueba si el directorio de origen existe.
if [ ! -d "$directorio_origen" ]; then   
    echo "Error: El directorio de origen '$directorio_origen' no existe."
    exit 1  # Si el directorio no existe, muestra un error y termina el script.
fi

# Comprueba si el directorio de destino existe, si no, lo crea.
if [ ! -d "$directorio_destino" ]; then   
    mkdir -p "$directorio_destino"  # -p permite crear subdirectorios si es necesario.
fi

# Obtiene el nombre del usuario actual.
usuario=$(whoami)   

# Obtiene la fecha en formato AñoMesDía (YYYYMMDD).
# date +%Y%m%d: Formato de fecha que devuelve el año, mes y día sin separadores.
# + : Indica que se va a especificar un formato de salida.
fecha=$(date +%Y%m%d) 

# Genera el nombre del archivo de copia con el formato requerido.
nombre_archivo="$(basename "$directorio_origen")${usuario}${fecha}"
# basename: Devuelve el nombre del archivo o directorio sin la ruta completa.
# ${usuario}${fecha}: Añade el nombre de usuario y la fecha al nombre del archivo.
# basename "$directorio_origen": Extrae solo el nombre del directorio de origen, sin la ruta completa.
# Por ejemplo, si el directorio de origen es "/home/usuario/documentos", basename devolverá "documentos".

# Determina si la copia debe ser comprimida o no.
if [ "$compresion" -eq 1 ]; then
    archivo_destino="$directorio_destino/${nombre_archivo}.tar.gz"  # Si se comprime, el archivo termina en .tar.gz.
    # Se añade .tar.gz al nombre del archivo para indicar que está comprimido.
    # archivo_destino: Es la ruta completa del archivo de destino, incluyendo el nombre y la extensión.
    tar_opciones="-czf"  # Opciones de tar: -c (crear), -z (comprimir con gzip), -f (especificar archivo).
else
    archivo_destino="$directorio_destino/${nombre_archivo}.tar"  # Si no se comprime, termina en .tar.
    tar_opciones="-cf"  # Opciones de tar: -c (crear), -f (especificar archivo).
fi

# Verifica si el archivo de copia ya existe.
if [ -f "$archivo_destino" ]; then
    echo "Ya se ha realizado esta copia hoy ($archivo_destino)."
    # La fecha se incluye en el nombre del archivo, por lo que si ya existe, significa que se ha hecho hoy.
    if [ "$sobreescribir" -eq 0 ]; then
        echo "No se sobreescribirá la copia."
        exit 0  # Si no se permite sobrescribir, finaliza el script sin hacer nada.
    fi
fi

# Crea el archivo de respaldo con tar usando las opciones seleccionadas.
if tar $tar_opciones "$archivo_destino" "$directorio_origen"; then
    # tar $tar_opciones "$archivo_destino" "$directorio_origen": Crea el archivo de respaldo.
    # argumentos:
    # - $tar_opciones: Las opciones de tar que se definieron anteriormente.
    # - "$archivo_destino": El archivo de destino donde se guardará la copia.
    # - "$directorio_origen": El directorio que se va a copiar.
    echo "Copia realizada en $archivo_destino."  # Si la copia fue exitosa, muestra un mensaje de éxito.
else
    echo "Error al crear la copia de seguridad."  # Si hubo un error con tar, muestra un mensaje de error.
    exit 1  # Finaliza el script con código de error.
fi