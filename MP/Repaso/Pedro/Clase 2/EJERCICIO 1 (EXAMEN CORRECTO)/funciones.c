#include "funciones.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
    La función debe volcar los datos del vector V1 y V2 en una cola (LS)
    teniendo en cuenta que no haya elementos repetidos (considerar repetidos
    si tienen la misma matricula).

    Deberás primero volcar los datos de V1 y luego V2. El tamaño de cada vector
    será tam1 y tam2 respectivamente.

    La función debe retornar el nº de elementos que se han insertado en la cola.
*/

int ejercicio(struct coche * V1, struct coche * V2, int tam1, int tam2, struct lista ** LS)
{
    //COMPLETA

    int cont = 0; 

    for (int i = 0; i < tam1; i++){
        
        if(buscarCoche(*LS, V1[i].matricula) == 0){

            insertarDetras(LS, V1[i]);
            cont++;
        }
    }

    for (int i = 0; i < tam2; i++){
        
        if(buscarCoche(*LS, V2[i].matricula) == 0){

            insertarDetras(LS, V2[i]);
            cont++;
        }
    }

    return cont;
}

//COMPLETA AQUÍ CON LAS FUNCIONES QUE HAYAS UTILIZADO

int buscarCoche(struct lista * LS, int dato){

    struct lista * aux = LS;

    while(aux != NULL){

        if(dato == aux -> matricula){

            return 1;
        }

        aux = aux -> siguiente;
    }

    return 0;
}

void insertarDetras(struct lista ** LS, struct coche dato){

    struct lista * nuevo = nuevoElemento();

    nuevo -> matricula = dato.matricula;
    strcpy(nuevo -> marca, dato.marca);
    nuevo -> anio_matriculacion = dato.anio_matriculacion;
    nuevo -> siguiente = NULL;

    if((*LS) == NULL){

        (*LS) = nuevo;
    }

    else{

        struct lista * aux = (*LS);

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

        printf("Error al reservar espacio para el nuevo elemento. \n");
        exit(-1);
    }

    return nuevo;
}