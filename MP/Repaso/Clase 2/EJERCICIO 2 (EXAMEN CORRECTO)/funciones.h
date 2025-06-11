#ifndef FUNCIONES_H
#define FUNCIONES_H

struct dato
{
    int codigo;
    float peso;
};

struct lista
{
    struct dato elemento;
    struct lista * siguiente;
};

int ejercicio(struct dato * VECTOR, int NUMELEMENTOS, struct lista ** LISTA, float limite);

//COMPLETA AQUÍ CON EL PROTOTIPO DE LAS FUNCIONES QUE HAYAS CREADO

void insertarDelante(struct lista ** LISTA, struct dato elemento);

struct lista * nuevoElemento();

void print_lista(struct lista* LISTA);

#endif