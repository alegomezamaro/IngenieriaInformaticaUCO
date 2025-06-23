#include "ej2f.h"
#include <stdio.h>
#include <stdlib.h>
#define tam_vector 10

int main(){
	int valor, v[tam_vector];
	int *mayores = (int*)malloc(tam_vector);
	int *menores = (int*)malloc(tam_vector);
	printf("\nIntroduce el numero a partir del que quieres que dividamos en mayor y menor: ");
	scanf("%i", &valor);
	rellenarVectorAleatorio(v);
	valorMayor(v, mayores, valor);
	valorMenor(v, menores, valor);
	free(mayores);
	free(menores);        
	return 0;
}
