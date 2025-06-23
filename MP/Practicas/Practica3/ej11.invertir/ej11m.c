#include "ej11f.h"
/*
Construye una función recursiva que permita invertir los elementos de un vector. Por ejemplo, si
el vector original es V=(3,7,2,6,7,8), el resultado de la llamada será V=(8,7,6,2,3,7). Puedes pasar
como parámetros el vector y dos posiciones a intercambiar.
*/

int main(){
	//Definimos las variables
	int *vector;
	int n;

	//Introducimos el tamaño del vector dinamico
	printf("\nIndica el tamaño del vector (mayor que 0): ");
	scanf("%i", &n);

	//Comprobamos que n > 0
	if(n>0){
		vector = (int*)malloc(n*sizeof(int));
	
		//Rellenamos el vector aleatorio
		rellenarVectorAleatorio(vector, n);

		//Imprimimos el vector
		printf("\nElementos del vector dinamico y aleatorio\n");
		imprimirVector(vector, n);

		//Invertimos el vector
		invertir(vector, 0, n-1);

		//Imprimimos el vector invertido
		printf("\nElementos del vector dinamico invertido\n");
		imprimirVector(vector, n);
	}
	else{
		printf("El numero debe de ser mayor a 0");
	}

	//Finalizamos
	return 0;
}