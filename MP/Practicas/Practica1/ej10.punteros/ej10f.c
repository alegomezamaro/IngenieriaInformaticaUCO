#include "ej10f.h"

void leeVector(double v[], int tam){	//Lee el vector
	double numero;
	printf("\nIntroduce los datos para rellenar el vector: ");
	for(int i=0; i<tam; i++){
		scanf("%lf", &numero);
		v[i]=numero;
	}
}

void escribeVector(double v[], int tam){	//Imprime el vector
	for(int i=0; i<tam; i++){
		printf("\nEl numero en el espacio v[%i] es: %lf", i, v[i]);
	}
}

double sumaPositivos(double v[], int tam){	//Suma los numeros positivos 
	double suma=0;
	for(int i=0; i<tam; i++){
		if(v[i]>0){
			suma += v[i];
		}
	}
	return suma;
}
