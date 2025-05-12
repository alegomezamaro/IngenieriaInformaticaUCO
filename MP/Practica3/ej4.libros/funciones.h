#ifndef _FUNCIONES_H_
#define _FUNCIONES_H_
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

struct libro{
char titulo[100];
char autor[50];
float precio;
int unidades;
};

int menu();
void comprobarLibro(char* nombreFichero);
void añadirLibro(char* nombreFichero);
int contarLibros(char* nombreFichero);
struct libro* reservarMemoria(int tamaño);
void liberarMemoria(struct libro** vector);
void listarLibrosStock(char *nombreFichero);
void venderNunidades(char* nombreFichero);
void borrar0unidades(char* nombreFichero);

#endif
