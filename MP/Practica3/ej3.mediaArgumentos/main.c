#include "funciones.h"

/*
Codifica un programa en C que, utilizando funciones, calcule la media de los elementos pares
que hay en un fichero de texto generado por el ejercicio anterior. El nombre del fichero se pasará
como argumento en la línea de órdenes.
*/

int main(int argc, char *argv[]) {
    //Verificamos que se han definido dos argumentos
    if (argc != 2) {
        printf("Uso: %s <nombre_del_fichero>\n", argv[0]);
        exit(-1);
    }

    //Definimos las variabes
    char * nombreFichero = argv[1];

    //Llamamos a la función
    double media = calcularMediaPares(nombreFichero);

    //Imprimimos el resultado
    printf("La media de los números pares en el fichero es: %.2f\n", media);

    //Retornamos a 0
    return 0;
}