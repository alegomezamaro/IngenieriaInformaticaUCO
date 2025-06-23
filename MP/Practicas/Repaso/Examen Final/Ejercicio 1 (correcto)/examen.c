#include "examen.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
    Apartado 1
*/
struct dato *apartado1(char *NF, int *nEle)
{
    FILE * fich = fopen(NF, "r");

    if(fich == NULL){

        printf("Error al abrir el fichero. \n");
        exit(-1);
    }

    fseek(fich, 0, SEEK_END);

    long int bytes = ftell(fich);

    int tam = bytes / sizeof(struct dato);

    struct dato * v = NULL;

    v = reservarMemoria(tam);

    (*nEle) = tam;

    fclose(fich);

    return v;
}

/*
    Apartado 2
*/
int apartado2(char *NF, struct dato *Vector)
{

    FILE * fich = fopen(NF, "r");

    if(fich == NULL){

        printf("Error al abrir el fichero. \n");
        exit(-1);
    }

    struct dato d;

    int i = 0;
    int contEle = 0;

    while(fread(&d, sizeof(struct dato), 1, fich)){

        if(d.unidades > 0){

            Vector[i] = d;
            i++;
            contEle++;
        }
    }

    fclose(fich);

    return contEle;
}

// COMPLETE AQUÍ CON LAS FUNCIONES AUXILIARES QUE NECESITE

struct dato * reservarMemoria(int tam){

    struct dato * v = NULL;

    v = (struct dato *)malloc(sizeof(struct dato) * tam);

    if(v == NULL){

        printf("Error al reservar memoria. \n");
        exit(-1);
    }

    return v;
}