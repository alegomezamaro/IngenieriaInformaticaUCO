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
grep -vE '^([^:]*:){5}/home' /etc/passwd | cut -d: -f3
    #([^:]*:){5}: Salta los 5 primeros campos (usuario:contraseña:uid:gid:gecos:).
    #/home: Detecta si el campo home empieza por /home.
    #-v: Inversa, para quedarte con los que no están en /home.
    #cut -d: -f3: Extrae el UID de esas líneas.

echo -e "\n4. Usuarios con GID mayor que 1000:"
while IFS=: read -r user _ _ gid _; do
     #read -r user _ _ gid _      Guarda el primer y cuarto campo

    if [ "$gid" -gt 1000 ]; then
        echo "$user"
    fi
    #Si gid es mayor de 1000 imprime el usuario
done < /etc/passwd

echo -e "\n5. Usuarios y su UID con una ',' en su gecos:"
while IFS=: read -r user _ uid _ gecos _; do
    #read -r user _ uid _ gecos _   Guarda el primer, tercer y quinto campo
    if [[ "$gecos" == *,* ]]; then
        echo "$user, $uid"
    fi
    #Si el gecos tiene una coma imprime usuario, uid
done < /etc/passwd