#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *generar_numeros_aleatorios(int num_elementos, int minimo, int maximo);
void guardar_numeros_en_fichero(FILE *fichero, int *numeros, int num_elementos);

#endif
