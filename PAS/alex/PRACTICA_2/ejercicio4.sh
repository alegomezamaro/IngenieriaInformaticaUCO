#Desarrolla un script que consulte el archivo /etc/passwd y realice las siguientes tareas:

#1. Mostrar todos los usuarios cuyo nombre empieza con la letra “l”.

#2. Mostrar los usuarios cuyo shell es válido (es decir, diferente de /bin/false o /usr/bin/nologin).

#3. Mostrar el UID de los usuarios cuyo directorio home no está en /home.

#4. Mostrar los usuarios que tienen asignado un GID mayor que 1000.

#5. Mostrar los usuarios y su UID con una “,” en su gecos.

#getent passwd para ver el contenido sobre lo que vamos a trabajar

#proxy(usuario):x:13(UID):13(GID):proxy:/bin:/usr/sbin/nologin (shell diferente de /bin/false o /usr/bin/nologin)

#!/bin/bash


echo "1. Mostrar todos los usuarios cuyo nombre empieza con la letra “l”"

cat /etc/passwd | sed -rne "s/(^l.*):x:.+:.+:.*:.+:.+/\1/p"

echo -e "\n2. Mostrar los usuarios cuyo shell es válido (es decir, diferente de /bin/false o /usr/bin/nologin)."

cat /etc/passwd | grep -vE "/bin/false$|/usr/sbin/nologin$" | sed -rne "s/(.*):x:.+:.+:.*:.+:.+/\1/p"

echo -e "\n3. Mostrar el UID de los usuarios cuyo directorio home no está en /home."

cat /etc/passwd | grep -vE "home" | sed -rne "s/.*:x:(.*):.*:.*:.*:.*/\1/p"

echo -e "\n4. Mostrar los usuarios que tienen asignado un GID mayor que 1000."

cat /etc/passwd | sed -rne "s/(.*):x:.*:([1-9][0-9]{3,}):.*:.*:.*/\1/p"

echo -e "\n 5.Mostrar los usuarios y su UID con una “,” en su gecos."

cat /etc/passwd | sed -rne "s/(.*):x:(.*):.*:.*:.*:.*/\1, \2/p"