#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

void mostrarFichero(char * nombreFichero){

	FILE * fich = fopen(nombreFichero, "r");

	if(fich == NULL){

		printf("Error al abrir el fichero. \n");
		exit(-1);
	}

	libro l;

	while(fgets(l.titulo, 100, fich)){

		l.titulo[strlen(l.titulo) -1] = '\0';
		fgets(l.autor, 100, fich);
		l.autor[strlen(l.autor) -1] = '\0';
		fscanf(fich, "%d %f", &l.unidades, &l.precio);

		fgetc(fich);

		printf("TÍTULO: %s\nAutor: %s\nUnidades: %d\nPrecio: %f\n\n", l.titulo, l.autor, l.unidades, l.precio);
	}

	fclose(fich);
}

void borrarLibro(char * nombreFichero, char * tituloElim){

	FILE * fich = fopen(nombreFichero, "r");

	if(fich == NULL){

		printf("Error al abrir el fichero. \n");
		exit(-1);
	}

	FILE * fich2 = fopen("auxiliar.txt", "w");

	if(fich2 == NULL){

		fclose(fich);
		printf("Error al abrir el fichero. \n");
		exit(-1);
	}

	libro l;

	while(fgets(l.titulo, 100, fich)){

		l.titulo[strlen(l.titulo) -1] = '\0';
		fgets(l.autor, 100, fich);
		l.autor[strlen(l.autor) -1] = '\0';
		fscanf(fich, "%d %f", &l.unidades, &l.precio);

		fgetc(fich);

		if(strcmp(l.titulo, tituloElim) != 0){

			fprintf(fich2, "%s\n%s\n%d %f\n", l.titulo, l.autor, l.unidades, l.precio);
		}
	}

	fclose(fich);
	fclose(fich2);

	remove(nombreFichero);
	rename("auxiliar.txt", nombreFichero);

}

void modificarLibro(char * nombreFichero, char * tituloModif, float precioModif){

	FILE * fich = fopen(nombreFichero, "r");

	if(fich == NULL){

		printf("Error al abrir el fichero. \n");
		exit(-1);
	}

	FILE * fich2 = fopen("auxiliar.txt", "w");

	if(fich2 == NULL){

		fclose(fich);
		printf("Error al abrir el fichero. \n");
		exit(-1);
	}

	libro l;

	while(fgets(l.titulo, 100, fich)){

		l.titulo[strlen(l.titulo) -1] = '\0';
		fgets(l.autor, 100, fich);
		l.autor[strlen(l.autor) -1] = '\0';
		fscanf(fich, "%d %f", &l.unidades, &l.precio);

		fgetc(fich);

		if(strcmp(l.titulo, tituloModif) == 0){

			l.precio = precioModif;
		}

		fprintf(fich2, "%s\n%s\n%d %f\n", l.titulo, l.autor, l.unidades, l.precio);
	}

	fclose(fich);
	fclose(fich2);

	remove(nombreFichero);
	rename("auxiliar.txt", nombreFichero);

}

libro * volcarFicheroLista(char * nombreFichero){

	FILE * fich = fopen(nombreFichero, "r");

	if(fich == NULL){

		printf("Error al abrir el fichero. \n");
		exit(-1);
	}

	libro* cabeza = NULL;
    libro* actual = NULL;
    char titulo[100];
    char autor[100];
    int unidades;
    float precio;

	while(fgets(titulo, 100, fich)){

		titulo[strlen(titulo) -1] = '\0';
		fgets(autor, 100, fich);
		autor[strlen(autor) -1] = '\0';
		fscanf(fich, "%d %f", &unidades, &precio);

		fgetc(fich);

		
    }

    fclose(fich);
}