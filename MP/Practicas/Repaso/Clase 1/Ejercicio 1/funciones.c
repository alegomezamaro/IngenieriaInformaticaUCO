#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertarDelante(struct nodo ** cabeza,int dato){

	struct nodo * nuevo = nuevoElemento();
	nuevo -> dato = dato;        // equivale a: (*nuevo).dato=dato
	nuevo -> sig = (*cabeza);
	(*cabeza) = nuevo;
}

struct nodo * nuevoElemento(){

	struct nodo * nuevo = NULL;
	nuevo = (struct nodo *)malloc(sizeof(struct nodo));
	if(nuevo == NULL){

		printf("Error al reservar espacio para el nodo.\n");
		exit(-1);
	}

	return nuevo;
}

void insertarDetras(struct nodo ** cabeza,int dato){

	struct nodo * nuevo = nuevoElemento();
	nuevo -> dato = dato;        // equivale a: (*nuevo).dato=dato
	nuevo -> sig = NULL;

	if((*cabeza) == NULL){

		(*cabeza) = nuevo;
	}

	else{

		struct nodo * aux = (*cabeza);
		while(aux -> sig!=NULL){

			aux = aux -> sig;
		}

		aux -> sig = nuevo;
	}
}

void mostrarLista(struct nodo * cabeza){

	struct nodo * aux = cabeza;   //Recorrer la lista

	while(aux != NULL){

		printf("%d\n", aux -> dato);
		aux = aux -> sig;
	}
}

int contarElementos(struct nodo * cabeza){

	struct nodo * aux = cabeza;   //Recorrer la lista
	int cont = 0;

	while(aux != NULL){

		cont++;
		aux = aux -> sig;
	}

	return cont;
}

void calcularMedia(struct nodo * cabeza, float * mediaRef){

	struct nodo * aux = cabeza;   //Recorrer la lista
	float suma = 0;
	int cont = 0;

	while(aux != NULL){

		suma += aux -> dato;
		cont++;
		aux = aux -> sig;
	}

	(*mediaRef) = suma / cont;

}

void borrarLista(struct nodo ** cabeza){

	struct nodo * aux = (*cabeza);
	struct nodo * ant;

	while(aux != NULL){

		ant = aux;
		aux = aux -> sig;
		free(ant);
	}

	(*cabeza) = NULL;
}
