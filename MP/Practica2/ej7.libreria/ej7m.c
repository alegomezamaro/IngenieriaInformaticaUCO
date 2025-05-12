#include "ej7f.h"

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

	int *minVector=(int*)malloc(columnas*sizeof(int));
	if(minVector == NULL){
		printf("\nError, la matriz no se ha generado correctamente");
	}
	for (int i = 0; i < columnas; i++){
		minVector[i]=matriz[0][i];
	}
	for(int i=0; i<columnas; i++){
		for(int j=1; j<filas; j++){
			if(minVector[i] > matriz[j][i]){
				minVector[i] = matriz[j][i];
			}
		}
	}

	liberarMemoria(matriz);
	for (int i=0; i < columnas; ++i){
		printf("\nEn la columna %i: %d", i, minVector[i]);
	}
	return 0;
}