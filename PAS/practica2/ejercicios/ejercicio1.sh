#!/bin/bash

if [ $# -ne 1 ] #Se esperaba 1 argumento
then 
    echo "Uso: ./$0 <fichero_libros>"
    exit 1
fi

fichero=$1 #Argumento 1

if [ ! -e $fichero ] #El fichero no existe
then   
    echo "El fichero no existe"
    exit 1
fi

echo -e "\n1) Años de los libros publicados entre 1950 y 2020:"
grep -oE "Año: (19[5-9][0-9]|20[0-1][0-9]|2020)" "$fichero" #1950-1999, 2000-2019, 2020
#-oE    Coincidencias con el patron (E      version extendida)

echo -e "\n2) Precios superiores a 20 euros:" 
grep -oE "[2-9][0-9],[0-9][0-9]€" "$fichero" #Formato “XX,XX€”. 20,00-99,99

echo -e "\n3) Número de libros por género:"
grep -oE "\[.*?\]" "$fichero" | sort -n | uniq -c | sed 's/^ *//;s/\(.*\) \(\[.*\]\)/\2 aparece \1 veces/'
#\[.*?\]
    #\      Interpreta el comando [.?\ literalmente
    #[      Marca inicio de la expresión regular
    #.      Cualquier carácter excepto nueva línea
    #?      Selecciona ninguna o una vez lo anterior
    #\      Hace que interprete ] literalmente
    #]      Marca final de la expresión regular
#sort -n    Ordena de forma numérica segun lo siguiente (uniq -c)
#uniq -c    Cuenta la cantidad de veces que aparece cada línea en la salida
#sed 's/^ *//;s/\(.\) \(\[.*\]\)/\2 aparece \1 veces/'
    #s/^        Sustituye el espacio al principio de la línea por
    #*//        Ninguno o varios espacios en blanco por nada (elimina solo los espacios, no las lineas completas)
    #s/\(.\)    Sustituye lo que interpreta ()

echo -e "\n4) Palabras de al menos 8 caracteres que empiezan por consonante y terminan por vocal:"
grep -ioE "\b[^aeiou ][a-záéíóú]{6,}[aeiou]\b" "$fichero"
#grep -ioE  Igual que -oE pero ignora mayúscula-minúscula
#\b         Marca el inicio de la palabra, asegurando que la coincidencia inicia aquí.
#[^..]      Con esto busca que la primera letra no sea vocal ni un espacio
#[]{6,}     Haya 6 caracteres que contengan ese rango de valores
#[aeiou]    Que sea vocal
#\b         Marca el final de la palabra, asegurando que la coincidencia termina aquí.

echo -e "\n5) Líneas de autor cuyo nombre o apellido contiene una doble "l":"
grep -iE "[A].*[Ll]{2}.*" "$fichero"
#[A]        Imponemos que empieze por A (Autor)
#.*         Coge ninguna, una o varias veces cualquier cosa
#[Ll]{2}    Contiene L o l 2 veces
#.*         Coge ninguna, una o varias veces cualquier cosa

echo -e "\n6) Títulos de libros con más de tres palabras:"
grep -iE "^[T]([^ ]+ ){3,}.*" "$fichero"
#^[T]           Indica que este al principio y que contenga T o t (-i) (Titulo)
#([^ ]+ ){3,}   Uno o más caracteres que no sean un espacio y despues de ellos un espacio al menos 3 veces (3 palabras)
#.*             Cualquier cosa después de las primeras 3 palabras.

echo -e "\n7) Títulos de libros cuyo precio termina en ,99€:"
grep -B3 ",99€" "$fichero" | grep "Título:"
#-B3    Muestra 3 líneas antes de la coincidencia.
#grep "Título:"     Filtra las líneas que contienen la palabra "Título:"

echo -e "\n8) Número de libros con año de publicación anterior a 2000:"
cat $fichero | sed -rne "s/^Año: ([0-1][0-9][0-9][0-9]|1[0-9][0-9][0-9])//p" | uniq -c | sed -rne "s/      (.*)/\1/p"
#sed -rne "s/^Año:  Que empiece por "Año: "
#([0-1][0-9][0-9][0-9]|1[0-9][0-9][0-9])//p"    Rango desde 0000 hasta el 1999
#No pongo \1 para que uniq -c cuente
#sed -rne "s/      (.*)/\1/p"   Coloca el resultado

echo -e "\n9) Líneas con dos o más palabras con mayúscula consecutivas:"
grep -P "([A-ZÁÉÍÓÚÑ][a-záéíóúñ]+ ){2,}" "$fichero"
#grep -P        Permite usar patrones más avanzados que las expresiones regular grep o grep -E
#([A-ZÁÉÍÓÚÑ][a-záéíóúñ]+ )     Busca palabras que empiecen por mayúscula y el resto minuscula (espacio)
#{2,}                           Que el patrón anterior se repita almenos dos veces

echo -e "\n10) Géneros con una palabra compuesta:"
grep -oP '\[.*?-.*?\]' libros.txt | sort | uniq
#\[.*?-.*?\]    Busca texto entre corchetes con un guión (Género es lo único que se muestra entre corchetes)
#sort | uniq    Ordena y evita que se repitan los generos