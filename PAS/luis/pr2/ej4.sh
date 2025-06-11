#!/bin/bash  # Indica que el script debe ejecutarse con el intérprete de bash.

fichero="/etc/passwd"  # El archivo que contiene los detalles de las cuentas de usuario del sistema es /etc/passwd.

# --- Sección 1: Usuarios cuyo nombre empieza con la letra "l" ---
echo -e "Usuarios cuyo nombre empieza con la letra \"l\":"  # Imprime un mensaje indicando que se van a listar los usuarios que comienzan con "l".
grep -o "^l[^:]*" "$fichero"  # Usa 'grep' para buscar líneas que comienzan con "l" (primera letra) y luego imprime solo el nombre de usuario (antes del primer ":").
# - '^l' busca los usuarios cuyo nombre empieza con la letra "l".
# - '[^:]*' asegura que se capture todo el nombre del usuario hasta el primer ':', que es el delimitador en /etc/passwd.

# --- Sección 2: Usuarios con shell válido ---
echo -e "Usuarios con shell válido:"  # Imprime un mensaje indicando que se van a listar los usuarios con shell válido.
grep -Ev "usr/bin/nologin|/bin/false" "$fichero"  # Filtra las líneas que contienen "/usr/bin/nologin" o "/bin/false", que indican que el usuario no tiene shell válido.
# - 'grep -Ev' significa "grep con opción 'E' para expresiones regulares extendidas y 'v' para invertir la coincidencia".
# - La expresión 'usr/bin/nologin|/bin/false' busca estas cadenas en el archivo.
# 'sed 's/:.*//' elimina todo después del primer ':' (que contiene los datos del usuario) dejando solo el nombre de usuario.
sed 's/:.*//'  

# --- Sección 3: UID de los usuarios cuyo directorio home no está en "/home" ---
echo -e "UID de los usuarios cuyo directorio home no está en home:"  # Imprime un mensaje indicando que se van a listar los UIDs de los usuarios que no tienen "/home" en su directorio home.
grep -v "/home" "$fichero"  # Filtra las líneas que no contienen "/home", lo que indica que el directorio home no está en "/home".
# - 'grep -v "/home"' excluye todas las líneas que contienen "/home", dejando solo las líneas donde el directorio home es diferente.
# 'sed -E 's/.*:([0-9]+):.*/\1/' usa una expresión regular para extraer solo el UID (segundo campo) de las líneas restantes.
sed -E 's/.*:([0-9]+):.*/\1/'

# --- Sección 4: Usuarios con GID mayor que 1000 ---
echo -e "Usuarios con GID mayor que 1000:"  # Imprime un mensaje indicando que se van a listar los usuarios cuyo GID (grupo ID) es mayor que 1000.
awk -F: '$4>1000 {print $1}' $fichero  # Usa 'awk' para analizar el archivo usando ':' como delimitador de campos.
# - '-F:' especifica que ':' es el delimitador de campos en el archivo /etc/passwd.
# - '$4>1000' selecciona las líneas donde el cuarto campo (GID) es mayor que 1000.
# - '{print $1}' imprime el primer campo (nombre de usuario) para las líneas que cumplen la condición.

# --- Sección 5: Usuarios y su UID con una ',' en su gecos ---
echo -e "Usuarios y su UID con una ',' en su gecos:"  # Imprime un mensaje indicando que se van a listar los usuarios y sus UID si su campo gecos contiene una coma.
awk -F: '$5 ~ /,/ {print $1 ", " $3}' "$fichero"  # Usa 'awk' para procesar el archivo y buscar líneas donde el campo 5 (gecos) contiene una coma.
# - '$5 ~ /,/' busca en el campo 5 (gecos) si contiene una coma.
# - '{print $1 ", " $3}' imprime el nombre de usuario (campo 1) y el UID (campo 3) para las líneas que cumplen la condición.

