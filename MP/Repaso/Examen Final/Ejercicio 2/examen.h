#ifndef EXAMEN_H
#define EXAMEN_H

#include "funciones.h"

/*
    Apartado 1
*/
void apartado1(struct alumno * Vector, int nElementos, int criterio);

/*
    Apartado 2
*/
void apartado2(struct alumno * Vector, int nElementos);

/*
    Apartado 3
*/
void apartado3(int dividendo, int divisor, int * resultado);

/*
    Apartado 4
*/
int apartado4(char * cadena, char caracter);

// COMPLETE AQUÍ CON EL PROTOTIPO DE LAS FUNCIONES QUE HAYA IMPLEMENTADO

void ordena(struct alumno * Vector, int nElementos, int (*metodo)(struct alumno a, struct alumno b));

int nombreAlfa(struct alumno a, struct alumno b);

int dniDescendente(struct alumno a, struct alumno b);

int mediaAsc(const void * a, const void * b);
#endif