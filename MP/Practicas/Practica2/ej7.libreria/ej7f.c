 #include "ej7f.h"

int **reservarMemoria(int nFil, int nCol){
//Reserva memoria para una matriz de nFil filas y nCol columnas. La reserva de memoria se realizará por filas
	int **matriz=(int**)malloc(nFil*sizeof(int*));
	matriz[0]=(int*)malloc(nFil*nCol*sizeof(int));
	for(int i=1; i<nFil; i++){
		matriz[i]=matriz[i-1]+nCol; 
	}
	return matriz;
}

void rellenaMatriz(int **matriz, int nFil, int nCol){
/*Rellena una matriz con valores aleatorios en el intervalo [0, 1]. Usa la notación de
aritmética de punteros para recorrer la matriz */
	srand(time(NULL));
	int *v=matriz[0];
	for(int i=0; i<nFil*nCol; i++){
			v[i]=(int)(rand()%51);
	}
}

void imprimeMatriz(int **matriz, int nFil, int nCol){
//Imprime una matriz por pantalla. Usa la notación de artitmética de punteros para recorrer la matriz
	printf("\nLos valores de la matriz son: \n");
	for(int i=0; i<nFil; i++){
		for(int j=0; j<nCol; j++){
			printf("%i   ", matriz[i][j]);
		}
	printf("\n");
	}
}

void liberarMemoria(int **matriz){
//Libera la memoria de una matriz reservada dinámicamente
	free(matriz[0]);
	free(matriz);
}