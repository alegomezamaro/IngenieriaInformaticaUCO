#ifndef EJ9F_H
#define EJ9F_H

#include <stdio.h>
#include <math.h>

#define TAM 3

struct Monomio{

    int coeficiente;
    int grado;
};

void leerMonomio(struct Monomio *m);
void imprimirMonomio(struct Monomio m);
void leerPolinomio(struct Monomio p[]);
void imprimirPolinomio(struct Monomio p[]);
void mayorMenor(struct Monomio p[], struct Monomio *menor, struct Monomio *mayor);
void evaluarPolinomio(struct Monomio p[]);

#endif