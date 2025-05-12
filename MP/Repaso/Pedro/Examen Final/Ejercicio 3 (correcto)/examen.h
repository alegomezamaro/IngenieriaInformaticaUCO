#ifndef EXAMEN_H
#define EXAMEN_H

#include "funciones.h"

/*
    Apartado 1
*/
void apartado1(struct dato * Vector, int nEle, struct lista ** LS, int * size);

/*
    Apartado 2
*/
int apartado2(struct lista * LS, char * NF);

// COMPLETE AQUÍ CON EL PROTOTIPO DE LAS FUNCIONES QUE HAYA IMPLEMENTADO

void insertarDetras(struct lista ** LS, struct dato d);

struct lista * nuevoElemento();

int calcularNotaMedia(struct dato a);

#endif