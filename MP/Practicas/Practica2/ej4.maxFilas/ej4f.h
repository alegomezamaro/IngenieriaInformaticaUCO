#ifndef EJ4F_H
#define EJ4F_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float **reservarMemoria(int nFil, int nCol);
void rellenaMatriz(float **matriz, int nFil, int nCol);
void imprimeMatriz(float **matriz, int nFil, int nCol);
float *maxFil(float **matriz, int nFil, int nCol);
void liberarMemoria(float **matriz);

#endif