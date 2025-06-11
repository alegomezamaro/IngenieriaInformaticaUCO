#include "examen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Añade aquí las librerías que necesites

/*
    Esta función recibe como parámetros:
        1º Un vector de elementos de tipo struct dato
        2º El número de elementos del vector
        3º Una cola

    La función debe volcar en la cola todos los elementos del vector.
*/
void ejercicio1(struct dato * V, int numeroElementos, struct lista ** cola)
{
   for(int i = 0; i < numeroElementos; i++){

    insertarDetras(cola, V[i]);

   }
}

/*
    Esta función debe volcar los elementos de la cola cuyo ratio_ganancia sea positivo a un vector.
    El primer argumento es la cola con todos los elementos.
        (ojo, el vector 2 es de tipo struct dato 2 no de tipo struct dato, es decir, igual que la cola recibida)
    En el segundo argumento se debe almacenar el número de elementos insertados en el vector.

    La función debe retornar el vector generado.
*/
struct dato2 *ejercicio2(struct lista * cola, int * tam)
{
 
    (* tam) = 0;

    struct lista * aux = cola;

    while(aux != NULL){

        if(aux -> ratio_ganancia > 1){

            (*tam)++;
        }

        aux = aux -> siguiente;
    }

    struct dato2 * VECTOR = NULL;

    VECTOR = reservarMemoria(tam);

    int index = 0;

    aux = cola;

    while(aux != NULL){

        if(aux -> ratio_ganancia > 1){

            strcpy(VECTOR[index].codigo, aux -> codigo);
            VECTOR[index].unidades = aux -> unidades;
            VECTOR[index].ratio_ganancia = aux -> ratio_ganancia;
            index++;
        }

        aux = aux -> siguiente;
    }

    return VECTOR;
}

// COMPLETAR CON LAS FUNCIONES IMPLEMENTADAS PARA LA REALIZACIÓN DE LOS EJERCICIOS

void insertarDetras(struct lista ** COLA, struct dato d){

    struct lista * nuevo = nuevoElemento();

    strcpy(nuevo -> codigo, d.codigo);

    nuevo -> unidades = d.unidades;

    nuevo -> ratio_ganancia = (d.precio_venta / d.precio_compra);

    nuevo -> siguiente = NULL;

    if((* COLA) == NULL){

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

struct dato2 * reservarMemoria(int * tam){

    struct dato2 * v = NULL;

    v = (struct dato2 *)malloc(sizeof(struct dato2) * (*tam));

    if(v == NULL){

        exit(-1);
    }

    return v;
}
