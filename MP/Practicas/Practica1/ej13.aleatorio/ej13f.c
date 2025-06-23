#include "ej13f.h"

void rellenarVectorAleatorio(int v[]){	//Rellena un vector con numeros aleatorios
	srand(time(NULL));
	for(int i=0; i < TAM_vector; i++){
		v[i]=rand() % 50;
	}
}

void imprimirVector(int v[]){	//Imprime el vector
	for(int i=0; i < TAM_vector; i++){
		printf("\nLa posicion del vector[%i] es %i", i, v[i]);
	}
}

int crearIndiceImpares(int v[], int *impares[]){	//Crea un indice con los impares del vector dado
	int j=0;
	for(int i=0; i < TAM_vector; i++){
		if(v[i] % 2 != 0){
			impares[j]=&v[i];
			j++;
		}
	}
return j;
}

int crearIndiceDivisible(int v[], int *divisible[]){	//Crea un indice con los numeros divisibles entre 3 del vector dado
	int j=0;
	for(int i=0; i < TAM_vector; i++){
		if(v[i] % 3 == 0){
			divisible[j]=&v[i];
			j++;
		}
	}
return j;
}

void imprimeIndice(int *impares[], int *divisible[], int tam_impares, int tam_divisible){	//Imprime los indices impares y divisibles entre 3
	printf("\n\nLos numeros impares dentro del vector son: ");
	for(int i=0; i < tam_impares; i++){
		printf("\nv[%i]: %i", i, *impares[i]);
	}
	printf("\n\nLos numeros divisibles entre tres dentro del vector son: ");
	for(int i=0; i < tam_divisible; i++){
		printf("\nv[%i]: %i", i, *divisible[i]);
	}
}
