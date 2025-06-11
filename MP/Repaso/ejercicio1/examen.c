#include "examen.h"

//COMPLETAR CON LAS LIBRERÍAS NECESARIAS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// APARTADO 1 VOLCAR TODOS LOS ELEMENTOS DEL FICHERO EN LA LISTA ENCOLANDO,
//LA FUNCION DEBE DE GUARDAR EN LA VARIABLE ELEMENTOS EL NUMERO DE ELEMENTOS QUE HA VOLCADO.
void apartado1(char * nF, struct lista ** COLA, int * elementos){
    //COMPLETAR
    FILE *f = fopen(nF, "r");
    if (f == NULL) {
        perror("Error1");
        exit(-1);
    }

    struct lista *a;
    *elementos = 0;

    while (fscanf(f, "%s %f %d", a.nombre, &a.nota_media, &a.porcentaje_superado) == 3) {
        struct lista *nuevo = (struct lista *)malloc(sizeof(struct lista));
        if (nuevo == NULL) {
            printf("Error2");
            fclose(f);
            exit(-1);
        }

        strcpy(nuevo->nombre, nombre);
        nuevo->nota_media = nota_media;
        nuevo->porcentaje_superado = porcentaje_superado;
        nuevo->siguiente = NULL;

        if (*COLA == NULL) {
            *COLA = nuevo;
        } else {
            ultimo->siguiente = nuevo;
        }
        ultimo = nuevo;
        (*elementos)++;
    }

    fclose(f);
}

// APARTADO 2 BORRAR EL NUMERO DE ELEMENTOS DE COLA.
void apartado2(struct lista ** COLA)
{
    //COMPLETAR
    struct lista *actual = *COLA;
    struct lista *siguiente;

    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }

    *COLA = NULL;
}

//COMPLETAR CON LAS FUNCIONES QUE HAYAS IMPLEMENTADO