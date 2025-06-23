#ifndef EJ12F_H
#define EJ12F_H
#include <stdio.h>

struct Fraccion{
	int numerador;
	int denominador;
};
void leerFraccion(struct Fraccion *division);
void imprimirFraccion(struct Fraccion *division);
struct Fraccion multiplicar(struct Fraccion *division1, struct Fraccion *division2);

#endif