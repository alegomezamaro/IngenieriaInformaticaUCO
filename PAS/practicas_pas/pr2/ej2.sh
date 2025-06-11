#!/bin/bash

#eliminar lineas vacias, subrayados
#formato
# Titulo: XXX
# | -> Autor: XXX
# | -> Año: XXX
# | -> Precio: XXX
# | -> Género: XXX

# Verificar que se pase un argumento
if [ "$#" -ne 1 ]; then
    echo "Argumentos erróneos. Uso: $0 <fichero_libros.txt>"
    exit 1
fi

fichero="$1"

# Verificar que el archivo existe
if [ ! -f "$fichero" ]; then
    echo "Error: El archivo '$fichero' no existe."
    exit 1
fi

# Procesar el archivo con sed
sed -E '
    /^$/d;                                             # Elimina líneas vacías
    s/^Título: (.*)/Título: \1/;                       # Formatea "Título"
    s/^Autor: (.*)/| -> Autor: \1/;                    # Formatea "Autor"
    s/^Año: (.*)/| -> Año: \1/;                        # Formatea "Año"
    s/^Precio: (.*)/| -> Precio: \1/;                  # Formatea "Precio"
    s/\[Género: (.*)\]/| -> Género: \1/                # Formatea "Género" eliminando corchetes
' "$fichero"

# --- EXPLICACIÓN DEL BLOQUE SED ---
#
# sed -E '\n#    /^$/d;                                             # /^$/d elimina las líneas vacías del archivo.
#    s/^Título: (.*)/Título: \1/;                       # Busca líneas que empiecen con "Título: " y captura todo lo que sigue con (.*),
#                                                        # \1 se usa para volver a insertar el contenido capturado en la línea sin cambios.
#    s/^Autor: (.*)/| -> Autor: \1/;                    # Lo mismo con "Autor:", pero reemplaza el prefijo con "| -> Autor: "
#    s/^Año: (.*)/| -> Año: \1/;                        # Igual para "Año", cambiando el formato para la salida.
#    s/^Precio: (.*)/| -> Precio: \1/;                  # Lo mismo para "Precio", asegurando que la salida sea consistente.
#    s/\[Género: (.*)\]/| -> Género: \1/                # Captura el género dentro de corchetes y los elimina, manteniendo solo el contenido interno.
#
# Notas adicionales:
# - La opción -E (Extended Regular Expressions) es necesaria porque estamos usando paréntesis () para capturar grupos.
# - (.*) significa "cualquier cosa después del prefijo", y \1 reutiliza ese contenido en la sustitución.
# - \1 evita que el contenido capturado se pierda durante la sustitución.