#include "funciones.h"
#include <stdlib.h>
#include <stdio.h>

int main(){

	struct nodo * cabeza = NULL;

	insertarDelante(&cabeza,1);
	insertarDelante(&cabeza,2);
	insertarDelante(&cabeza,3);

	insertarDetras(&cabeza,4);
	insertarDetras(&cabeza,5);

	mostrarLista(cabeza);

	printf("\n");

	int tam = contarElementos(cabeza);

	printf("En la lista hay %d elementos. \n\n", tam);

	//Media por referencia

	float mediaRef = 0;

	calcularMedia(cabeza, &mediaRef);

	printf("La media de los elementos es: %f\n", mediaRef);

	borrarLista(&cabeza);
	
	return 0;
}