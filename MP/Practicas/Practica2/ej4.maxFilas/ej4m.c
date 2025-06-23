#include "ej4f.h"

int main(){
	int filas, columnas;
	printf("\nIntroduce el tamaño de la matriz: ");
	printf("\nFilas: "); 
	scanf("%i", &filas);
	printf("\nColumnas: "); 
	scanf("%i", &columnas);
	float **matriz=reservarMemoria(filas, columnas);
	rellenaMatriz(matriz, filas, columnas);
	imprimeMatriz(matriz, filas, columnas);
	float *maxVector = (float *)malloc(filas * sizeof(float));
    if (maxVector == NULL) {
        printf("\nError, no se pudo asignar memoria para el vector");
    }
	maxVector=maxFil(matriz, filas, columnas);
	for (int i=0; i < filas; ++i){
		printf("\nEn la fila %i: %.3f", i, maxVector[i]);
	}
	liberarMemoria(matriz);
}