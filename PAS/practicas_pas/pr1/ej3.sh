#!/bin/bash

# Comprobamos si se ha pasado la ruta del directorio de usuarios como argumento al script.
# Si no se pasa un argumento, mostramos un mensaje de error y terminamos la ejecución.
if [ -z "$1" ]; then
  echo "Por favor, proporciona la ruta al directorio de usuarios."  # Mensaje de error
  exit 1  # Finaliza el script con código de error 1
fi

# Asignamos el primer argumento ($1) a la variable base_dir, que será la ruta al directorio donde están los usuarios.
base_dir=$1

# Empezamos un bucle para recorrer todos los directorios de usuarios dentro de base_dir.
# base_dir/*: Esto selecciona todos los elementos dentro del directorio base.
# salida de base dir/*:
# /usuario1
# /usuario2
# /usuario3
# ...
for usuario_dir in $base_dir/*; do
    # Comprobamos si usuario_dir es realmente un directorio (lo que indica que es un directorio de usuario).
    if [ -d "$usuario_dir" ]; then
        # Extraemos el nombre del usuario del directorio (sin la ruta completa).
        username=$(basename "$usuario_dir")

        # Definimos las rutas a los directorios y archivos relevantes para SSH.
        ssh_dir="$usuario_dir/.ssh"  # Directorio .ssh del usuario (donde se encuentran las claves SSH).
        private_key="$ssh_dir/id_rsa"  # Ruta al archivo de clave privada id_rsa.
        desktop_dir="$usuario_dir/Desktop"  # Directorio Desktop del usuario (para guardar el archivo de advertencia).

        # Verificamos si el archivo de clave privada id_rsa existe en el directorio .ssh del usuario.
        if [ -f "$private_key" ]; then
            # Usamos stat para obtener los permisos de los directorios y archivos en formato numérico.
            # -c %a: Muestra los permisos en formato octal (numérico).
            home_perms=$(stat -c %a "$usuario_dir")  # Permisos del directorio home del usuario.
            ssh_perms=$(stat -c %a "$ssh_dir")  # Permisos del directorio .ssh.
            key_perms=$(stat -c %a "$private_key")  # Permisos del archivo de clave privada id_rsa.

            # Comprobamos si los permisos son incorrectos según las recomendaciones de seguridad.
            # Si los permisos son mayores que los permitidos, entonces la clave no está protegida correctamente.
            if [ "$home_perms" -gt 750 ] || [ "$ssh_perms" -gt 700 ] || [ "$key_perms" -gt 600 ]; then
                # Si los permisos son incorrectos, mostramos un mensaje de advertencia en la consola.
                echo "El usuario $username tiene una clave privada de SSH en $private_key que no está protegida."
                echo "La clave debe ser accesible únicamente por el propietario."

                # Si existe el directorio Desktop, creamos un archivo advertencia_ssh.txt para advertir al usuario.
                # Esto es útil para que el usuario vea la advertencia directamente en su escritorio.
                if [ -d "$desktop_dir" ]; then
                    # Creamos el archivo de advertencia con el mensaje explicativo.
                    echo "Advertencia: La clave SSH no está correctamente protegida." > "$desktop_dir/advertencia_ssh.txt"
                fi
            fi
        fi
    fi
done

# Los permisos de un directorio en Linux se definen en tres categorías:
# 1. Propietario: El usuario dueño del directorio.
# 2. Grupo: Los usuarios que pertenecen al mismo grupo que el propietario.
# 3. Otros: Cualquier usuario que no sea el propietario ni pertenezca al grupo.
#
# Los permisos se muestran en formato octal (numérico), donde cada dígito representa:
# - r (lectura): 4
# - w (escritura): 2
# - x (ejecución): 1
#
# Los directorios tienen permisos especiales:
# - Lectura (r): Permite ver el contenido del directorio (ver los archivos dentro de él).
# - Escritura (w): Permite agregar, eliminar o renombrar archivos dentro del directorio.
# - Ejecución (x): Permite acceder a los archivos y subdirectorios dentro del directorio (por ejemplo, navegar a él).
#
# Los permisos correctos para un directorio son:
# - El directorio home del usuario generalmente debe tener permisos 750 o menos. Esto significa que:
#     - El propietario tiene todos los permisos (lectura, escritura y ejecución).
#     - El grupo solo tiene permisos de lectura y ejecución.
#     - Otros no tienen acceso.
# - El directorio .ssh debe ser más restrictivo, con permisos 700 o menos, de modo que:
#     - Solo el propietario puede leer, escribir y ejecutar dentro de este directorio (nadie más debe poder acceder a él).
# - El archivo de clave privada (id_rsa) debe tener permisos 600 o menos, de modo que:
#     - Solo el propietario puede leer y escribir el archivo. Nadie más debe tener acceso (ni lectura, ni escritura, ni ejecución).
#
# Si los permisos son demasiado permisivos (por ejemplo, si un directorio tiene permisos 755 o el archivo id_rsa tiene permisos 644),
# significa que otros usuarios podrían tener acceso a tus archivos privados, lo cual representa un riesgo de seguridad.
#
# Por eso, el script verifica estos permisos para asegurarse de que las claves privadas están protegidas adecuadamente,
# lo que es esencial para la seguridad del sistema y la privacidad de los usuarios.