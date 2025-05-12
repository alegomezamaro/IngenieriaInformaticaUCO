#!/bin/bash

echo "1. Usuarios cuyo nombre empieza con la letra 'l':"
cut -d: -f1 /etc/passwd | grep '^l'
#-d: -f1 /etc/passwd    Extrae el nombre de los usuarios
#'^l'                   Selecciona solo los empezados por l

echo -e "\n2. Usuarios con shell válido:"
grep -vE '(/false|/nologin)$' /etc/passwd | cut -d: -f1
#-v                     Muestra lineas que no coincidad
#(/false|/nologin)$     Líneas que terminan en /false o /nologin (shell no valido)
#/etc/passwd            Entrada

echo -e "\n3. UID de los usuarios cuyo directorio home no está en home:"
awk -F: '$6 !~ /^\/home/ { print $3 }' /etc/passwd
#-F:                Delimitar por :
#$6 !~ /^\/home/    Filtra líneas cuyo campo 6 (directorio personal o home) no es /home
#{ print $3 }       Imprime el campo 3 (UID)

echo -e "\n4. Usuarios con GID mayor que 1000:"
awk -F: '$4 > 1000 { print $1 }' /etc/passwd
#$4 > 1000      Usuarios cuyo GID (Grupo ID principal del usuario) es mayor que 1000
#{ print $1 }   Imprime el nombre de usuario

echo -e "\n5. Usuarios y su UID con una ',' en su gecos:"
awk -F: '$5 ~ /,/ { print $1 }' /etc/passwd
#$5             Gecos (comentarios o información del usuario)
#~ /,/          Filtra líneas donde el campo 5 contiene una coma
#{ print $1 }   Imprime el nombre de usuario