 #include "ej8f.h"

void multiplicarMatrices(int **matriz1, int **matriz2, int nFil, int nCol){
/*Multiplica una matriz1 con otra matriz2 y lo guarda en la matriz1 */
	int *v=matriz1[0];
	int *w=matriz2[0];
	for(int i=0; i<nFil*nCol; i++){
			v[i]=v[i]*w[i];
	}
}