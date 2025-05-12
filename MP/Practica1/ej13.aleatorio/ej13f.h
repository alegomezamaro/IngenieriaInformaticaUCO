#ifndef EJ13F_H
#define EJ13F_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAM_vector 20

void rellenarVectorAleatorio(int v[]);
void imprimirVector(int v[]);
int crearIndiceImpares(int v[], int *impares[]);
int crearIndiceDivisible(int v[], int *divisible[]);
void imprimeIndice(int *impares[], int *divisible[], int tam_impares, int tam_divisible);

#endif