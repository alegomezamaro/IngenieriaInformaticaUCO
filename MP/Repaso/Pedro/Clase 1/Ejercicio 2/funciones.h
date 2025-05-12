#ifndef FUNCIONES_H
#define FUNCIONES_H

typedef struct {

	char titulo[100];
	char autor[100];
	int unidades;
	float precio;
	struct libro * siguiente;
}libro;

struct nodo{

	struct libro dato;
	struct nodo * sig;
};


void mostrarFichero(char * nombreFichero);

void borrarLibro(char * nombreFichero, char * tituloElim);

void modificarLibro(char * nombreFichero, char * tituloModif, float precioModif);

libro * volcarFicheroLista(char * nombreFichero);

#endif