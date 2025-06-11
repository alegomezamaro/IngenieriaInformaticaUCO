#!/bin/bash

if [ $# -ne 1 ] && [ ! -f "$1" ]; then

    echo "Uso $0 <libros.txt>"

    exit 1

fi

fichero=$1

echo "1) Años de los libros publicados entre 1950 y 2020:"

#FORMA 1: cat $fichero | sed -rne "s/^Año: (19[5-9][0-9]|20[0-1][0-9]|2020)/\1/p"

cat $fichero | grep -oE "Año: (19[5-9][0-9]|20[0-1][0-9]|2020)" | sed -rne "s/Año: (.+)/\1/p"

#.+ cualquier carácter uno o varias veces lo anterior(1,N)
#.* cualquier carácter ninguno,uno o varias veces lo anterior(0,N)

echo -e "\n2) Precios superiores a 20 euros:" #echo "" es lo mismo que echo -e "\n"

cat $fichero | grep -oE "Precio: ([2-9][0-9],[0-99].+)" | sed -rne "s/Precio: (.+)/\1/p"

echo -e "\n3) Número de libros por género:"

cat $fichero | sed -rne "s/\[Género: (.+)\]/\1/p" | sort | uniq -c | sed -rne "s/ *([0-9]*) (.+)/\2 aparece \1 veces/p"

#sed -rne "s/^\[Género: (.*)\]/\1/p" |sort -n | uniq -c : me muestra cuantas veces aparece ese genero y el género que es
#sed -rne "s/ *([0-9]*) (.*)/\2 aparece \1 veces/p": me muestra el género y luego el nº de veces que aparece dicho género

echo -e "\n4) Palabras de al menos 8 caracteres que empiezan por consonante y terminan por vocal:"

cat $fichero | grep -vE "^[aeiouAEIOU]" | tr ' ' '\n' | tr -d ':' | tr -d '[' | tr -d ']' | grep -E "[aeiou]$" | grep -E ".{8,}"                             

#grep -ioE "\b[^aeiou\s][a-z]{6,}[aeiou]\b" "$fichero"
#.{8,}: con el . coja cualquier caracter y mínimo 8 veces

echo -e "\n5) Líneas de autor cuyo nombre o apellido contiene una doble "l":"

cat $fichero | sed -rne "s/(Autor: .*ll.*)/\1/p"

#.*ll.*: ya que puede haber ninguno,uno o varios caracteres antes y despues de ll

#OTRA FORMA: cat $fichero | grep -iE "^Autor: .*ll.*"
#FORMA DONDE SOLO SALGA EL APELLIDO: cat $fichero | sed -rne "s/^Autor: [A-Za-z]+ (.*ll.*)/\1/p"

echo -e "\n6) Títulos de libros con más de tres palabras:"

cat $fichero | grep -E "Título: [^ ]+ [^ ]+ [^ ]"

#Título: [^ ]+ [^ ]+ [^ ]: empieza por Título seguido de : y un espacio, cada [^ ]+ se refiere a uno o cualquier carácter que no sea espacio (una palabra), asi que contengan 3 palabras

echo -e "\n7) Títulos de libros cuyo precio termina en ,99€"

cat $fichero | grep -EB3 "(.*,[9][9])" | grep -E "Título:"

#grep -EB3 "(.*(IGUAL QUE SI PONGO [0-9][0-9]),[9][9])": muestra las 3 primeras lineas en las que se cumpla que el dinero termine en ,99 

#grep -E "Título:": despues de ese grep, muestra los que tengan Título ó ^T que empiezen por T

echo -e "\n8) Número de libros con año de publicación anterior a 2000:"

cat $fichero | sed -rne "s/^Año: ([0-1][0-9][0-9][0-9]|1[0-9][0-9][0-9])//p" | uniq -c | sed -rne "s/      (.*)/\1/p"

#sed -rne "s/^Año: ([0-1][0-9][0-9][0-9]|1[0-9][0-9][0-9])//p": que empiece por Año:, seguido de un espacio, en un rango desde 0000 hasta el 1999
#OJO no pongo \1 para que el uniq -c me lo cuente
#Con el otro sed lo que hago es que se ponga el 6 en su sitio

echo -e "\n9) Líneas con dos o más palabras con mayúscula consecutivas:"

cat $fichero | grep -E "^[A-Z].+: [A-Z].+ [A-Z].+"

#grep -E "^[A-Z].+: [A-Z].+ [A-Z].+": que empiece por A-Z .+ uno o varios caracteres seguido de : y un espacio 
#[A-Z].+ que tenga A-Z y se repita una o varias veces

echo -e "\n10) Géneros con una palabra compuesta:"

cat $fichero | grep -E "\[Género: .+-.+" | sort | uniq

#grep -E "\[Género: .+-.+": que empiece por [Género: seguido de un espacio, con uno o más caracteres seguido de un - y uno o más caracteres
# sort | uniq: para ordenarlos y quitar los repetidos