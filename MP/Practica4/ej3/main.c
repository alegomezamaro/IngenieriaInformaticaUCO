#include"funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Escribe un programa en C que lea de un fichero binario un vector dinámico de elementos de tipo
struct alumno (definido en el ejercicio 2) y lo ordene ascendentemente y descendentemente
por el campo nombre o por el campo nota utilizando la función qsort de stdlib.h
*/

int main(int argc,char **argv)
{
	if(argc!=3)
	{
		printf("Programa mal inicializado, el formato es <nombre programa> <1(ascendente) o 2(descendente)> <nombre del fichero bin>\n");
		exit(1);
	}
	
	int seleccion=atoi(argv[1]);
	
	alumno *vector=NULL;
	int tam=0;
	
	tamañoStruct(argv[2],&tam);
	
	rellenaVector(&vector,argv[2],&tam);	
	
	if(seleccion==1)
	{
		ordenaAscendente(vector,tam);
	}
	if(seleccion==2)
	{
		ordenaDescendente(vector,tam);
	}
	
	return 0;
}

