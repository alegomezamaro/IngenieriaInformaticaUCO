#include "examen.h"

//COMPLETAR CON LAS LIBRERÍAS NECESARIAS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//

void apartado1(char * nF, struct lista ** COLA, int * elementos)
{
    //COMPLETAR

    FILE * fich = fopen(nF, "r");

    if(fich == NULL){

        printf("Error al abrir el fichero. \n");
        exit(-1);
    }

    struct estudiante e;

    int cont = 0;

    while(fgets(e.nombre, SIZE, fich)){

        e.nombre[strlen(e.nombre) -1] = '\0';
        fscanf(fich, "%f %d\n", &e.nota_media, &e.creditos_superados);

        insertarDetras(COLA, e);

        cont++;
    }

    (*elementos) = cont;
}

void apartado2(struct lista ** COLA)
{
    //COMPLETAR

    struct lista * aux = (*COLA);

    struct lista * previous = NULL;

    while(aux -> siguiente != NULL){

        previous = aux;

        aux = aux -> siguiente;
    }
    
    previous -> siguiente = NULL;

    free(aux);
    
}

//COMPLETAR CON LAS FUNCIONES QUE HAYAS IMPLEMENTADO

void insertarDetras(struct lista ** COLA, struct estudiante dato){

    struct lista * nuevo = nuevoElemento();

    strcpy(nuevo -> nombre, dato.nombre);

    nuevo -> nota_media = dato.nota_media;

    nuevo -> porcentaje_superado = (dato.creditos_superados * 100) / 240.0;

    nuevo -> siguiente = NULL;

    if((*COLA) == NULL){

        (*COLA) = nuevo;

    }else{

        struct lista * aux = (*COLA);

        while(aux -> siguiente != NULL){

            aux = aux -> siguiente;
        } 

        aux -> siguiente = nuevo;
    }
}

struct lista * nuevoElemento(){

    struct lista * nuevo = NULL;

    nuevo = (struct lista *)malloc(sizeof(struct lista));

    if(nuevo == NULL){

        printf("Error al añadir un nuevo elemento. \n");
        exit(-1);
    }

    return nuevo;
}

//
