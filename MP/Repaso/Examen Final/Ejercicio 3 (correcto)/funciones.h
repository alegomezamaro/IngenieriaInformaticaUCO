#ifndef FUNCIONES_H
#define FUNCIONES_H

#define SIZE 250

struct dato
{
    char nombre[SIZE];
    long dni;
    float nota1, nota2, nota3;
};

struct lista
{
    char nombre[SIZE];
    long dni;
    float notaMedia;
    struct lista * siguiente;
};

#endif