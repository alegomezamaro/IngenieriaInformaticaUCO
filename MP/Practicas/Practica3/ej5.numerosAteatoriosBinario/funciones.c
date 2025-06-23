#include "funciones.h"

int *generar_numeros_aleatorios(int num_elementos, int minimo, int maximo) { //Genera una cantidad n de numeros aleatorios en el intervalo min-max
    //Definimos las variables
    if (num_elementos <= 0) {
        return NULL;
    }

    //Generamos memoria dinamica, si no se guarda bien return NULL
    int *numeros = (int *)malloc(num_elementos * sizeof(int));
    if (!numeros) {
        return NULL;
    }

    //Generamos los numeros aleatorios y los retornamos
    srand(time(NULL));
    for (int i = 0; i < num_elementos; i++) {
        numeros[i] = rand() % (maximo - minimo + 1) + minimo;
    }

    return numeros;
}

void guardar_numeros_en_fichero(FILE *fichero, int *numeros, int num_elementos) { //Guarda los numeros en el fichero deseado
    fwrite(numeros, sizeof(int), num_elementos, fichero);
}