/*
    Autor: Academia Main()
    Web: www.academiamain.es
    Contacto:  605 45 70 99 
*/
#ifndef FUNCIONES_H
#define FUNCIONES_H

struct dato
{
    char nombre[100];
    float peso;
    int codigo;
};

void ejercicio(struct dato * V, int nElementos, int criterio);

//COMPLETA AQUÍ CON EL PROTOTIPO DE LAS FUNCIONES QUE HAYAS NECESITADO

void ordena(struct dato * V, int nElementos, int (*metodo)(struct dato a, struct dato b));

int nombreAlfabetico(struct dato a, struct dato b);

int pesoDescendente(struct dato a, struct dato b);

int codigoAscendente(struct dato a, struct dato b);

#endif