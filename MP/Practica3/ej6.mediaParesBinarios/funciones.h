#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <stdio.h>
#include <stdlib.h>

int leer_numeros_desde_fichero(FILE *fichero, int **numeros);
float calcular_media_pares(int *numeros, int num_elementos);

#endif