#!/bin/bash

#Usuario:Contraseña:UID:GID:GECOS:Home:Shell

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
cat /etc/passwd | grep -vE "home" | sed -rne "s/.*:x:(.*):.*:.*:.*:.*/\1/p"

echo -e "\n4. Usuarios con GID mayor que 1000:"
grep -E '^([^:]*:){3}([1-9][0-9]{3,}|[1-9][0-9]{4,})' /etc/passwd | sed -rne "s/(.*):x:.*:.*:.*:.*:.*/\1/p"
#grep -E '^([^:]*:){3}([1-9][0-9]{3,}|[1-9][0-9]{4,})' /etc/passwd      GID entre 1000-99999
#sed -rne "s/(.*):x:.*:.*:.*:.*:.*/\1/p"    Imprime el nombre de usuario

echo -e "\n5. Usuarios y su UID con una ',' en su gecos:"
grep -E '^([^:]*:){4}[^:]*,.*' /etc/passwd | sed -rne "s/(.*):x:(.*):.*:.*:.*:.*/\1, \2/p"
#^([^:]*:){4}   Avanza hasta despues del cuarto : (GECOS)
#[^:]*,.*   El quinto campo contiene una coma
#sed -rne "s/(.*):x:(.*):.*:.*:.*:.*/\1, \2/p"  Imprime Usuario, UID