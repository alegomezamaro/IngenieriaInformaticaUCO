 #include "ej4f.h"

float **reservarMemoria(int nFil, int nCol){
//Reserva memoria para una matriz de nFil filas y nCol columnas. La reserva de memoria se realizará por filas
	float **matriz=(float**)malloc(nFil*sizeof(float*));
	matriz[0]=(float*)malloc(nFil*nCol*sizeof(float));
	for(int i=1; i<nFil; i++){
		matriz[i]=matriz[i-1]+nCol; 
	}
	return matriz;
}

void rellenaMatriz(float **matriz, int nFil, int nCol){
/*Rellena una matriz con valores aleatorios en el intervalo [0, 1]. Usa la notación de
aritmética de punteros para recorrer la matriz */
	srand(time(NULL));
	float *v=matriz[0];
	for(int i=0; i<nFil*nCol; i++){
			v[i]=(float)(rand()%999)/1000;
	}
}

void imprimeMatriz(float **matriz, int nFil, int nCol){
//Imprime una matriz por pantalla. Usa la notación de artitmética de punteros para recorrer la matriz
	printf("\nLos valores de la matriz son: \n");
	for(int i=0; i<nFil; i++){
		for(int j=0; j<nCol; j++){
			printf("%4.3f   ", matriz[i][j]);
		}
	printf("\n");
	}
}

float *maxFil(float **matriz, int nFil, int nCol) {
// Devuelve un vector dinámico con los máximos de cada fila
    if (matriz == NULL) {
        printf("\nError, la matriz no se ha generado correctamente");
        return NULL;
    }

    float *maximos = (float *)malloc(nFil * sizeof(float));
    if (maximos == NULL) {
        printf("\nError, no se pudo asignar memoria para el vector");
        return NULL;
  	}
    for (int i = 0; i < nFil; i++) {
        maximos[i] = matriz[i][0];
        for (int j = 1; j < nCol; j++) {
            if (maximos[i] < matriz[i][j]) {
                maximos[i] = matriz[i][j];
            }
        }
    }

    return maximos;
}

void liberarMemoria(float **matriz){
//Libera la memoria de una matriz reservada dinámicamente
	free(matriz[0]);
	free(matriz);
}