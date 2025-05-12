#include "ej11f.h"

void invertir(int *vector, int p1, int p2){
	int auxiliar;

	//Comprobamos que p1 < p2
	if(p1 < p2){
		auxiliar = vector[p1];
		vector[p1]=vector[p2];
		vector[p2]=auxiliar;

		//Actualizamos posiciones
		p1++;
		p2--;

		//Llamamos a a funcion recursiva
		invertir(vector, p1, p2);
	}
	return;
}

void rellenarVectorAleatorio(int *v, int n){
	srand(time(NULL));
	int i;
	for(i=0; i<n; i++){
		v[i]=rand()%51;
	}
	printf("\n");
}

void imprimirVector(int *v, int n){
	int i;
	for(i=0; i<n; i++){
		printf("\nv[i] = %i", v[i]);
	}
	printf("\n");
	return;
}