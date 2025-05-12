#include "ej3f.h"

int main(){
	int filas, columnas;
	printf("\nIntroduce el tamaño de la matriz: ");
	printf("\nFilas: "); 
	scanf("%i", &filas);
	printf("\nColumnas: "); 
	scanf("%i", &columnas);
	int **matriz=reservarMemoria(filas, columnas);
	rellenaMatriz(matriz, filas, columnas);
	imprimeMatriz(matriz, filas, columnas);
	int *minVector=minCol(matriz, filas, columnas);
	liberarMemoria(&matriz, columnas);
	for (int i=0; i < columnas; ++i){
		printf("\nEn la columna %i: %d", i, minVector[i]);
	}
}