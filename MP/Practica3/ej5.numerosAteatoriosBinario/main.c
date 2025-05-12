#include "funciones.h"

/*
Codifica un programa en C que, utilizando funciones, cree un fichero binario con números
enteros generados aleatoriamente en un intervalo especificado por el usuario. El programa
guardará los números en un vector dinámico antes de volcarlo a disco. El programa recibirá 4
parámetros como argumentos en la línea de órdenes: nombre del fichero a crear, número de
elementos que contendrá el fichero y los extremos superior e inferior del intervalo.
*/

int main(int argc, char *argv[]) {
    //Verificamos que se han definido dos argumentos
    if (argc != 5) {
        printf("Uso: %s <nombre_del_fichero> <numero_de_elementos> <minimo> <maximo>\n", argv[0]);
        return 1;
    }

    //Definir variables
    char *nombre_fichero = argv[1];
    int num_elementos = atoi(argv[2]);
    int minimo = atoi(argv[3]);
    int maximo = atoi(argv[4]);

    if (minimo >= maximo) {
        printf("\nError1, el límite inferior debe ser menor que el límite superior\n");
        return 1;
    }

    //Verificamos que este bien limitado
    FILE *fichero = fopen(nombre_fichero, "wb");
    if (!fichero) {
        printf("\nError2 al abrir el fichero para escritura\n");
        return 1;
    }

    //Llamamos a la función
    int *numeros = generar_numeros_aleatorios(num_elementos, minimo, maximo);

    //Si no se generan los numeros return 0
    if (!numeros) {
        printf("\nError3 al generar los números aleatorios\n");
        fclose(fichero);
        return 1;
    }

    //Guardamos los numeros
    guardar_numeros_en_fichero(fichero, numeros, num_elementos);

    //Cerramos el fichero y liberamos la memoria antes de cerrar
    fclose(fichero);
    free(numeros);
    printf("\nSe han guardado %d números aleatorios en el fichero '%s'\n", num_elementos, nombre_fichero);
    return 0;
}