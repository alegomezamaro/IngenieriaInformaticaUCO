#!/bin/bash

if [ $# -ne 1 ]; then

    echo "Uso: $0 <directorio/home>"
    exit 1
fi

ruta=$1 #Argumento 1
usuarios=$(find $ruta -maxdepth 1 -mindepth 1) #Busca los usuarios en una profundidad de uno (es decir en la carpeta dada "ruta")
echo $usuarios #Imprime los usuarios encontrados

for usuario in $usuarios; do #Recorre todos los usuarios

    permhome=$(stat -c %a $usuario) #Permisos en la carpeta usuario

    if [ -e "$usuario/.ssh" ]; then

        permisosdir=$(stat -c %a $usuario/.ssh) #Permisos en la carpeta ssh del usuario
    else

        permisosdir=0
    fi

    if [ -e "$usuario/.ssh/id_rsa" ]; then

        permisosfich=$(stat -c %a $usuario/.ssh/id_rsa) #Permisos en el fichero id_rsa del usuario
        #stat       Obtiene informacion sobre un archivo o directorio
        #-c %a      Devuelve los permisos del archivo o directorio en formato octal
    else
    
        permisosfich=0
    fi    

    if [ $permhome -gt 700 ] || [ $permisosdir -gt 700 ] || [ $permisosfich -gt 600 ]; then #Si los permisos no son los correctos

        nombreusuario=$(echo $usuario | cut -d "/" -f 3) #Extrae el nombre de usuario
        #Divide FicheroEjercicio3/home/ale por / y coge el tercero "ale"

        echo "El usuario $nombreusuario tiene una clave privada de ssh en $usuario/ ssh/id_rsa que no está protegida. La clave debe ser accesible unicamente por el propietario."
        echo "El usuario $nombreusuario tiene una clave privada de ssh en $usuario/ ssh/id_rsa que no está protegida. La clave debe ser accesible unicamente por el propietario." > "$usuario/Desktop/AVISO"
        #Almacena el echo en Desktop/AVISO

    fi
done

exit 0 