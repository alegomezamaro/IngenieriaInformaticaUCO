#ifndef FUNCIONES_H
#define FUNCIONES_H

struct nodo
{
	int dato;				//el int puede variar dependiendo del dato q te den
	struct nodo * sig;
};

void insertarDelante(struct nodo ** cabeza,int dato);

struct nodo * nuevoElemento();

void insertarDetras(struct nodo ** cabeza,int dato);

void mostrarLista(struct nodo * cabeza);

int contarElementos(struct nodo * cabeza);

void calcularMedia(struct nodo * cabeza, float * mediaRef);

void borrarLista(struct nodo ** cabeza);

#endif