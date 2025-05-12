 #include "ej2f.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define tam_vector 10

void rellenarVectorAleatorio(int v[]){
	srand(time(NULL));
	printf("\nLos valores del vector son: ");
	for(int i=0; i < tam_vector; i++){
		v[i]=rand() % 50;
		printf("%i ", v[i]);
	}
}

void valorMayor(int v[], int mayor[], int valor){
	printf("\nLos valores mayores a %i son: ", valor);
	for(int i=0, j=0; i<tam_vector; i++){
		if(v[i]>valor){
			mayor[j]=v[i];
			printf("%i ", mayor[j]);
			j++;
		}
	}
}
		
void valorMenor(int v[], int menor[], int valor){
	printf("\nLos valores menores a %i son: ", valor);
	for(int i=0, j=0; i<tam_vector; i++){	
		if(v[i]<valor){
			menor[j]=v[i];
			printf("%i ", menor[j]);
			j++;
		}
	}
}
