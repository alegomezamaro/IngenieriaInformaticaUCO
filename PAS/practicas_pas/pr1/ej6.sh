#!/bin/bash

# Función que genera un índice HTML para un directorio
generar_indice_html() {
  # Directorio que recibe como parámetro
  local dir=$1
  
  # Comprobar si el directorio existe
  if [ ! -d "$dir" ]; then
    echo "Error: El directorio $dir no existe."
    return 1
  fi

  # Nombre del archivo de índice
  local index_file="$dir/index.html"
  
  # Empezar a escribir el archivo HTML
  echo "<ul>" > "$index_file"

  # Recorrer los elementos en el directorio
  for item in "$dir"/*; do
    if [ -d "$item" ]; then
      # Si es un directorio, añadir enlace
      local subdir_name=$(basename "$item")
      echo "<li><a href=\"$subdir_name/index.html\">$subdir_name</a></li>" >> "$index_file"
    elif [ -f "$item" ]; then
      # Si es un archivo, añadir como elemento de lista
      local file_name=$(basename "$item")
      echo "<li>$file_name</li>" >> "$index_file"
    fi
  done

  # Cerrar la lista HTML
  echo "</ul>" >> "$index_file"

  # Informar de que se ha creado el índice
  echo "Se ha creado el fichero $index_file con el contenido del directorio $dir."
}

# Función recursiva que recorre directorios y genera índices
generar_indices_recursivos() {
  local dir=$1

  # Llamar a la función para generar el índice del directorio actual
  generar_indice_html "$dir"

  # Recorrer todos los subdirectorios y generar índices para ellos
  for subdir in "$dir"/*; do
    if [ -d "$subdir" ]; then
      # Llamar a la función recursiva para cada subdirectorio
      generar_indices_recursivos "$subdir"
    fi
  done
}

# Comprobar si el parámetro (directorio) ha sido pasado
if [ -z "$1" ]; then
  echo "Uso: ./ejercicio6.sh <directorio>"
  exit 1
fi

# Directorio de entrada
base_dir="$1"

# Comprobar si el directorio existe
if [ ! -d "$base_dir" ]; then
  echo "Error: El directorio $base_dir no existe."
  exit 1
fi

# Llamar a la función recursiva para generar índices en el directorio base
generar_indices_recursivos "$base_dir"

# PARA COMPILAR:
# chmod +x ejercicio6.sh

# PARA EJECUTAR:
# ./ejercicio6.sh FicherosEjercicio3/

# SALIDA POR PANTALLA:
# nombre del archivo,ruta completa,fecha de modificion, tamaño en bytes y permisos