#include "pilas.h"
#include <stdio.h>
#include <stdlib.h>

/*
Pilas de contenedores
- Descripción
	- Para mover los contenedores de mercancía de un importante puerto comercial, se
	utiliza un método de almacenamiento basado en el concepto de pila.
		- De este modo, el contenedor situado más abajo en la pila fue el primero que se
		apiló, y, para moverlo, es necesario mover a otra pila todos los contenedores que
		hay encima de él.
	- Cada contenedor de mercancía está identificado por un código entero, X.
	- Por motivos de seguridad, como mucho se pueden apilar N contenedores en una
	misma pila.
		- De este modo, si la pila no está llena, entonces se puede apilar un nuevo
		contenedor.
	- Si se desea sacar un contenedor de código X entonces:
		- Se deben desapilar previamente los contenedores encima de él colocándolos en
		una nueva pila auxiliar.
		- Se extrae el contenedor X y se vuelven a introducir los contenedores extraídos
		previamente.
Objetivo
	- Codifica un programa que, utilizando las funciones push (apilar), pop (desapilar), y
	vacia que están implementadas en la biblioteca pilas.a, permita gestionar una pila de
	contenedores con la siguiente funcionalidad:
		- Crear una pila de N contenedores.
		- Listar los contenedores que hay en pila.
			- Se muestra por pantalla un listado de los contenedores contenidos en la pila.
		- Conocer si un contenedor de código X está en la pila.
		- Sacar el contenedor de código X que puede estar en cualquier posición de la pila.
NOTA: no se podrá recorrer en ningún caso la pila secuencialmente como si fuera una
lista, sino que solo se hará uso de una pila auxiliar y de las funciones vacia, push y pop.
*/

int main(int argc,char **argv)
{
	if(argc!=2)
	{
		printf("No se han introducido los argumentos correctamente debe ser <n prog> <N cont>");
		exit(1);
	}
	int i;
	int N=atoi(argv[1]);
	struct nodo *cima;
	int valor;
	struct nodo *aux;
	
	for(i=0;i<N;i++)
	{
		printf("Introduzca el número del nuevo contenedor\n");
		scanf("%i",&valor);
		
		push(&cima,valor);
	}
	
	aux=cima;
	while(aux!=NULL)
	{
		printf("Numero de contenedor: %i\n",aux->numero);
		aux=aux->sig;
	}
	
	printf("Introduzca el numero del contenedor a buscar\n");
	scanf("%i",&valor);
	
	aux=cima;
	while(aux!=NULL)
	{
		if(valor==aux->numero)
		{
			printf("Tenemos el contenedor numero %i\n",valor);
		}
		aux=aux->sig;
	}
	
	printf("Introduzca el numero del contenedor a sacar\n");
	scanf("%i",&valor);
	
	aux=cima;
	struct nodo *aux2;
	while(aux!=NULL)
	{	
		
		if(valor==aux->numero)
		{
			aux=aux->sig;
			printf("Valor encontrado y borrado\n");
			N--;
		}
		else
		{	
			push(&aux2,pop(&aux));
			aux2=aux;
			aux=aux->sig;
		}
	}
	cima=aux2;
	aux=cima;

	while(aux!=NULL)
	{
		printf("Numero de contenedor: %i\n",aux->numero);
		aux=aux->sig;
	}
	
	
	return 0;
}
