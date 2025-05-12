#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct producto{

	char nombre[50];
	int cod;
	float precio;
	int unidades;
};

void funcion(char* fb, char* ftmin, char* ftmax);

#endif