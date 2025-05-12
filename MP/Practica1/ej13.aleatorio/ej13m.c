#include "ej13f.h"

int main(){
	int vector[TAM_vector], *impares[TAM_vector], *divisores[TAM_vector];
	rellenarVectorAleatorio(vector);
	imprimirVector(vector);
	int tam_impares = crearIndiceImpares(vector, impares);
	int tam_divisibles = crearIndiceDivisible(vector, divisores);
	imprimeIndice(impares, divisores, tam_impares, tam_divisibles);
	return 0;
}
