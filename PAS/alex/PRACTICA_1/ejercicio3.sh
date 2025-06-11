#!/bin/bash

#Comprobamos el nº de argumentos

if [ $# -ne 1 ]; then

    echo "Uso: $0 <ruta_usuarios>"

    exit 1

fi

ruta_usuarios="$1" #argv[1]

salidaFind=$(find $ruta_usuarios -maxdepth 1 -mindepth 1) #maxdepth 1: profundidad máxima 1 de la ruta que puede buscar, mindepth 1: profundidad mínima 1 de la ruta que puede buscar

echo $salidaFind #Muestra la busqueda de los "alumnos" tal que asi: FicherosEjercicio3/home/nombre_alumno

for usuario in $salidaFind; do #Recorre cada uno de los usuarios

    perhome=$(stat -c %a $usuario) #Con stat obtiene info. detallada sobre un archivo o directorio. -c %a: devuelve los permisos del archivo o directorio en formato octal, $usuario: ruta del usuario

    permisosDir=$(stat -c %a $usuario/.ssh) #Muestra los permisos de la ruta del usuario, dentro del /.shh
    
    permisosFich=$(stat -c %a $usuario/.ssh/id_rsa) #Muestra los permisos de la ruta del usuario, dentro del /.shh/id_rsa

    if [ $perhome -gt 700 ] || [ $permisosDir -gt 700 ] || [ $permisosFich -gt 600 ]; then #Si los permisos del home son > 700, los de directorio >700 y los de fichero > 600

        nombreUsuario=$(echo $usuario | cut -d '/' -f 3) #De la ruta FicheroEjercicio3/home/pepe lo divide en 3 y coge el 3º en este caso pepe

        echo "El usuario $nombreUsuario tiene una clave privada de ssh en $usuario/ ssh/id_rsa que no está protegida. La clave debe ser accesible unicamente por el propietario." > "$usuario/Desktop/AVISO" #Almacena el error en Desktop/AVISO
        
        echo "El usuario $nombreUsuario tiene una clave privada de ssh en $usuario/ ssh/id_rsa que no está protegida. La clave debe ser accesible unicamente por el propietario."
    
    fi

done

