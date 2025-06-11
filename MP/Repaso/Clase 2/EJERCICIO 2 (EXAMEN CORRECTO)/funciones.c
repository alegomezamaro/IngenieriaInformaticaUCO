#include "funciones.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
    La función de abajo recibe un vector como primer argumento, el número de elementos del 
    vector como segundo argumento, una lista como tercer argumento y una variable real llamada
    límite como cuarto argumento.

    La función deberá volcar los datos del vector a la lista siguiente respetando las siguientes
    normas:
        1) Solo se volcarán a la lista los elementos del vector cuyo peso sea inferior al 
            limite que se recibe como cuarto argumento.
        2) Los elementos deben quedar en la lista en orden inverso a como se encuentran en el vector.
    
    Además la función debe retornar el número de elementos que se han volcado a la lista.
*/

int ejercicio(struct dato * VECTOR, int NUMELEMENTOS, struct lista ** LISTA, float limite){
    
    //COMPLETAR AQUÍ

    int cont = 0;

    *LISTA = NULL;

    for (int i = 0; i < NUMELEMENTOS; i++){
        
        if(VECTOR[i].peso < limite){

            insertarDelante(LISTA, VECTOR[i]);
            cont++;
        }
    }

    print_lista(*LISTA);

    return cont;
}

void insertarDelante(struct lista ** LISTA, struct dato elemento){

    struct lista * nuevo = nuevoElemento();
    nuevo -> elemento = elemento;
    nuevo -> siguiente = (*LISTA);
    (*LISTA) = nuevo;
}

struct lista * nuevoElemento(){

    struct lista * nuevo = NULL;

    nuevo = (struct lista *)malloc(sizeof(struct lista));

    if(nuevo == NULL){

        printf("Error al insertar un nuevo elemento. \n");
        exit(-1);
    }

    return nuevo;
}

void print_lista(struct lista * LISTA){

    struct lista* current = LISTA;

    while (current != NULL) {

        printf("Codigo: %d, Peso: %.2f\n", current->elemento.codigo, current->elemento.peso);
        current = current -> siguiente;
    }
}
