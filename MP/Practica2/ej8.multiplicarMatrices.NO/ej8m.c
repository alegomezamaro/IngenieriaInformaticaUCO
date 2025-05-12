#include "ej8f.h"

int main(){
	int filas, columnas;
	printf("\nIntroduce el tamaño de la matriz: ");
	printf("\nFilas: "); 
	scanf("%i", &filas);
	printf("\nColumnas: "); 
	scanf("%i", &columnas);
	int **matriz1=reservarMemoria(filas, columnas);
	int **matriz2=reservarMemoria(filas, columnas);
	rellenaMatriz(matriz1, filas, columnas);
	rellenaMatriz(matriz2, filas, columnas);
	imprimeMatriz(matriz1, filas, columnas);
	imprimeMatriz(matriz2, filas, columnas);
	multiplicarMatrices(matriz1, matriz2, filas, columnas);
	imprimeMatriz(matriz1, filas, columnas);
	liberarMemoria(matriz1);
	liberarMemoria(matriz2);
	return 0;
}