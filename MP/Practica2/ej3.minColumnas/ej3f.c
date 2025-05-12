 #include "ej3f.h"

int **reservarMemoria(int nFil, int nCol){	//Reserva memoria para una matriz de nFil filas y nCol columnas. La reserva de memoria se realizará por filas
	int** matriz;
	int i; 
	matriz=(int**)malloc(nFil*sizeof(int*));
	if(matriz == NULL){
		printf("\nError, la matriz no se ha generado correctamente");
	}
	for(i=0; i<nFil;i++){ 
		matriz[i]=(int*)malloc(nCol*sizeof(int));
		if(matriz == NULL){
		printf("\nError, la matriz no se ha generado correctamente");
		}
	}
	return matriz;
}

void rellenaMatriz(int **matriz, int nFil, int nCol){	//Rellena una matriz con valores aleatorios en el intervalo [1, 20]. Usa la notación de aritmética de punteros para recorrer la matriz
	srand(time(NULL));
	for(int i=0; i<nFil; i++){
		for(int j=0; j<nCol; j++){
			matriz[i][j]=rand()%21;
		}
	}
}

void imprimeMatriz(int **matriz, int nFil, int nCol){	//Imprime una matriz por pantalla. Usa la notación de artitmética de punteros para recorrer la matriz
	printf("\nLos valores de la matriz son: ");
	for(int i=0; i<nFil; i++){
		for(int j=0; j<nCol; j++){
			printf("\nEl valor en matriz[%i][%i] es %i", i, j, matriz[i][j]);
		}
	}
}

int *minCol(int **matriz, int nFil, int nCol){	//Devuelve un vector dinámico con los mínimos de cada columna
	int *minimos=(int*)malloc(nCol*sizeof(int));
	if(minimos == NULL){
		printf("\nError, la matriz no se ha generado correctamente");
	}
	for (int i = 0; i < nCol; i++){
		minimos[i]=matriz[0][i];
	}
	for(int i=0; i<nCol; i++){
		for(int j=1; j<nFil; j++){
			if(minimos[i] > matriz[j][i]){
				minimos[i] = matriz[j][i];
			}

		}
	}
	return minimos;
}

void liberarMemoria(int ***matriz, int nFil){	//Libera la memoria de una matriz reservada dinámicamente. La función pondrá el puntero matriz a NULL antes de terminar
	for (int i = 0; i < nFil; i++){
		free((*matriz)[i]);
	}
	free(*matriz);
	(*matriz)=NULL;
}