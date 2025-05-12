#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct alumnos{
    char nombre[50];
    char apellido1[50];
    char apellido2[50];
    int edad;
    int bilingue;
};

struct producto{
    char nombre[50];
    int cod;
    float precio;
    int unidades;
};

struct nodo{
    int dato; //Con  char dato[TAM], no se podria (cadena), usar strcpy
    struct nodo * sig;
};



#endif