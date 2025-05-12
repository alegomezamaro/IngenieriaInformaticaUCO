#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <stdio.h>
#include <stdlib.h>

//Añadimos la estructura dada
struct producto{
	char nombre[50];
	int cod;
	float precio;
	int unidades;
};

//Introducimos los prototipos de las funciones
void comprobarFichero(char* nombreFichero);
void actualizarPrecio(char* nombreFichero, int codigo, float precio);

#endif