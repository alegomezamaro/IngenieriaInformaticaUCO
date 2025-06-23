#include "funciones.h"

int leer_numeros_desde_fichero(FILE *fichero, int **numeros) {
    fseek(fichero, 0, SEEK_END);
    long file_size = ftell(fichero);
    fseek(fichero, 0, SEEK_SET);
    int num_elementos = file_size / sizeof(int);
    *numeros = (int *)malloc(num_elementos * sizeof(int));
    if (!*numeros) {
        return -1;
    }
    fread(*numeros, sizeof(int), num_elementos, fichero);
    return num_elementos;
}

float calcular_media_pares(int *numeros, int num_elementos) {
    int suma_pares = 0;
    int cantidad_pares = 0;
    for (int i = 0; i < num_elementos; i++) {
        if (numeros[i] % 2 == 0) {
            suma_pares += numeros[i];
            cantidad_pares++;
        }
    }
    if (cantidad_pares == 0) {
        return 0;  // No hay números pares, la media es cero.
    }
    return (float)suma_pares / cantidad_pares;
}