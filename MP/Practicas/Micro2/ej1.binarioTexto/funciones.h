#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definimos la estructura
struct producto{

	char nombre[50];
	int cod;
	float precio;
	int unidades;	
};

//Definimos los prototipos de funciones 
void comprobarExistenciaFichBin(char *nombreFicheroBinario);
void comprobarExistenciaFichTexto(char *nombreFicheroTexto);
void GeneraFicheroTexto(char *nombreFicheroBinario, char *nombreFicheroTexto);

#endif