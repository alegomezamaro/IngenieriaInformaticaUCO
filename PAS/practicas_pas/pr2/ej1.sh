#!/bin/bash  # Indica que el script debe ejecutarse con el intérprete de bash.

# Comprobación del número de argumentos. Si no es 1, muestra un mensaje de uso y termina el script.
if [ $# -ne 1 ]  # '$#' es el número de argumentos pasados al script. Si no es igual a 1, se ejecuta el bloque.
then 
    echo "Uso: ./$0 <fichero_libros>"  # '$0' es el nombre del script, lo muestra en el mensaje.
    exit 1  # Termina el script con código de error (1) si no se cumple la condición.
fi

# Asigna el primer argumento pasado al script a la variable 'fichero'.
fichero=$1  # '$1' es el primer argumento, es el nombre del archivo de libros.

# Comprobación de que el archivo especificado existe. Si no, muestra un mensaje de error.
if [ ! -e $fichero ]  # '! -e' comprueba si el archivo no existe. '$fichero' es el nombre del archivo.
then   
    echo "Se esperaba un fichero de tipo libros.txt"  # Mensaje si el archivo no existe.
    exit 1  # Termina el script con error si el archivo no existe.
fi

# Ejercicio 1: Buscar los años de los libros publicados entre 1950 y 2020
echo "1) Años de los libros publicados entre 1950 y 2020:"

# 'grep "Año: [1-2][0-9][0-9][0-9]" "$fichero"' busca las líneas que contienen "Año: XXXX" (años entre 1000 y 2999).
# '[1-2][0-9][0-9][0-9]' especifica que el año debe comenzar con 1 o 2 seguido de tres dígitos numéricos.
# 'sed 's/Año: //'' elimina la palabra "Año: " al principio de cada línea.
# 'awk '$0 >= 1950 && $0 <= 2020'' filtra solo los años entre 1950 y 2020.
grep "Año: [1-2][0-9][0-9][0-9]" "$fichero" | sed 's/Año: //' | awk '$0 >= 1950 && $0 <= 2020'

# Ejercicio 2: Mostrar los libros cuyo precio es superior a 20 euros
echo -e "\n2) Precios superiores a 20 euros:"

# 'grep "Precio: [0-9]*,[0-9][0-9]€" "$fichero"' busca líneas con el formato "Precio: X,Y€" (ej. "Precio: 19,99€").
# '[0-9]*,[0-9][0-9]€' busca números con una coma como separador decimal, seguidos de '€'.
# 'sed 's/Precio: //' elimina la palabra "Precio: ".
# 'awk '$0 > 20'' filtra los precios mayores a 20.
grep "Precio: [0-9]*,[0-9][0-9]€" "$fichero" | sed 's/Precio: //' | awk '$0 > 20'

# Ejercicio 3: Contar el número de libros por género
echo -e "\n3) Numero de libros por genero:"

# 'grep -o "\[.*\]" "$fichero"' busca todas las partes del texto que están entre corchetes (por ejemplo, "[Género: ...]").
# '-o' hace que solo se muestren las coincidencias encontradas, en lugar de la línea completa.
# 'sed 's/\[Género: //; s/\]//'' elimina las palabras "Género: " y los corchetes.
# 'sort' ordena los géneros.
# 'uniq -c' cuenta las ocurrencias de cada género.
# 'while read count genre; do' recorre cada línea de salida, desglosando el número y el género.
# 'echo "$genre aparece $count veces"' imprime el género y su frecuencia.
grep -o "\[.*\]" "$fichero" | sed 's/\[Género: //; s/\]//' | sort | uniq -c | while read count genre; do
    echo "$genre aparece $count veces"  # Imprime el género y su cantidad de veces.
done

# Ejercicio 4: Buscar palabras de al menos 8 caracteres que empiezan por consonante y terminan por vocal
echo -e "\n4) Palabras de al menos 8 caracteres que empiezan por consonante y terminan por vocal:"

# 'grep -Eo "\b[^aeiouAEIOU][áéíóúa-z]{6,}[áéíóúaeiou]\b" "$fichero"' busca palabras que:
# - '\b' indica un límite de palabra (inicio o final).
# - '[^aeiouAEIOU]' significa que la palabra debe comenzar con una consonante (carácter no vocal).
# - '[áéíóúa-z]{6,}' significa que la palabra debe tener al menos 6 caracteres intermedios.
# - '[áéíóúaeiou]' indica que debe terminar en una vocal.
# '-E' permite usar expresiones regulares extendidas, y '-o' muestra solo las coincidencias.
# 'sed 's/ //' elimina los espacios, si es necesario.
grep -Eo "\b[^aeiouAEIOU][áéíóúa-z]{6,}[áéíóúaeiou]\b" "$fichero" | sed 's/ //'

# Ejercicio 5: Buscar líneas de autor cuyo nombre o apellido contiene una doble "l"
echo -e "\n5) Líneas de autor cuyo nombre o apellido contiene una doble \"l\":"

# 'grep "Autor: .*ll.*" "$fichero"' busca líneas que contienen "Autor: " seguido de cualquier texto que contenga "ll".
# '.*' es un comodín que permite cualquier número de caracteres entre "Autor: " y "ll".
grep "Autor: .*ll.*" "$fichero"

# Ejercicio 6: Buscar títulos de libros con más de tres palabras
echo -e "\n6) Títulos de libros con más de tres palabras:"

# 'grep -Eo "Título: .*" "$fichero"' busca las líneas que contienen "Título: ", mostrando toda la línea después de eso.
# 'awk 'NF>4'' filtra las líneas que contienen más de 4 campos (palabras), pues 'NF' es el número de campos (palabras) en la línea.
grep -Eo "Título: .*" "$fichero" | awk 'NF>4'

# Ejercicio 7: Buscar títulos de libros cuyo precio termina en ",99€"
echo -e "\n7) Títulos de libros con precio terminando en ',99€':"

# 'grep -B3 ",99€" "$fichero"' busca las líneas que contienen ",99€" y muestra las 3 líneas previas a cada coincidencia.
# '-B3' muestra 3 líneas antes de la coincidencia.
# 'grep "Título:"' filtra las líneas que contienen la palabra "Título:" para mostrar solo los títulos de esos libros.
grep -B3 ",99€" "$fichero" | grep "Título:"

# Ejercicio 8: Contar el número de libros con año de publicación anterior a 2000
echo -e "\n8)  Número de libros con año de publicación anterior a 2000:"

# 'grep -Eo "Año: [0-9]{4,4}" "$fichero"' busca años de 4 dígitos después de "Año: ".
# 'sed 's/Año: //' elimina la palabra "Año:".
# 'awk '$0 < 2000'' filtra los años menores a 2000.
# 'wc -l' cuenta el número de líneas que coinciden con la condición, es decir, cuántos libros fueron publicados antes de 2000.
grep -Eo "Año: [0-9]{4,4}" "$fichero" | sed 's/Año: //' | awk '$0 < 2000' | wc -l

# Ejercicio 9: Buscar líneas con dos o más palabras con mayúscula consecutivas
echo -e "\n9)  Líneas con dos o más palabras con mayúscula consecutivas:"

# 'grep -E "[A-Z][a-z]+ [A-Z][a-z]+" "$fichero"' busca líneas que contienen dos palabras consecutivas, cada una comenzando con mayúscula.
# '[A-Z]' indica que la palabra debe empezar con una letra mayúscula, seguida de una o más letras minúsculas '[a-z]'.
# ' ' (espacio) separa las dos palabras.
grep -E "[A-Z][a-z]+ [A-Z][a-z]+" "$fichero"

# Ejercicio 10: Buscar géneros con una palabra compuesta (que contiene un guion)
echo -e "\n10)  Géneros con una palabra compuesta:"

# 'grep -o "\[.*-.*\]" "$fichero"' busca géneros que contienen un guion (ej. "Fantasía-Ciencia").
# '-o' muestra solo las coincidencias que están entre corchetes.
# 'sort' ordena alfabéticamente los géneros encontrados.
# 'uniq' elimina las repeticiones y muestra solo géneros únicos.
grep -o "\[.*-.*\]" "$fichero" | sort | uniq
