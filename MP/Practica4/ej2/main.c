#include"funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Dada la siguiente estructura:
	struct alumno {
		char nombre[50];
		int DNI;
		float nota;
	};
Escribe un programa que rellene un vector dinámico de tipo struct alumno y lo ordene
mediante el método de ordenación básico que prefieras (selección, inserción o burbuja).
El vector dinámico se rellenará a partir de los datos de un fichero binario. En Moodle
tienes disponibles los fuentes para generar el fichero binario.
La ordenación se hará usando como campo clave el DNI y podrá ser ascendente o
descendente.
Para realizar la ordenación en uno u otro sentido, se implementará una única función de
ordenación que, además del vector y el número de elementos, recibirá como parámetro
un puntero a una función de comparación.
El programa recibirá dos argumentos en la línea de órdenes:
	- Un entero con el sentido de la ordenación (1=ascendente o 2=descendente).
	- El nombre del fichero con los datos para rellenar el vector.
Al terminar el programa, deberá liberar la memoria usada.
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
	
	imprimeVector(vector,tam);
	
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

