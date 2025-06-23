#include "ej10f.h"

int main(){
	int tam;
	printf("\nIntroduce el tamaño del vector: ");
	scanf("%i", &tam);
	double v[tam];
	leeVector(v,tam);
	escribeVector(v,tam);
	double suma=sumaPositivos(v,tam);
	printf("\nLa suma de positivos es %lf",suma );
	return 0;
}
