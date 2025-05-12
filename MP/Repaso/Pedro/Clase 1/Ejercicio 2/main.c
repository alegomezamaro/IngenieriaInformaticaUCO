#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

int main(int argc, char ** argv){

	if(argc != 2){

		printf("Error, debes introducir el nombre del fichero. \n");
		exit(-1);
	}

	char * nombreFichero = argv[1];

	mostrarFichero(nombreFichero);

	char tituloElim[100];

	//printf("Introduzca el título que quiere eliminar: ");
	//scanf("%s", tituloElim);

	//borrarLibro(nombreFichero, tituloElim);

	char tituloModif[100];
	float precioModif;

	//printf("Introduzca el título que quiere modificar: ");
	//fgets(tituloModif, 100, stdin);
	//tituloModif[strlen(tituloModif) -1] = '\0';

	//printf("Introduzca el nuevo precio: ");
	//getchar();
	//scanf("%f", &precioModif);

	//modificarLibro(nombreFichero, tituloModif, precioModif);

	libro* listaLibros = volcarFicheroLista(nombreFichero);


	return 0;
}