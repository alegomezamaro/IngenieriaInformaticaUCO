/*------------------------------------------------------------------*/
/* NOMBRE Y APELLIDOS:                                              */
/* DNI:                                                             */
/*------------------------------------------------------------------*/

#include "funciones.h"

//HAZ AQUI LOS INCLUDE QUE SEAN NECESARIOS

#include <string.h>

/*------------------------------------------------------------------*/
/*Ejercicio 1: Ordenacion y punteros a funciones
               nEle: número de elementos del vector
               Vector: el vector a ordenar
               criterio: 0-->ascendente por indice de masa corporal
                         1-->descendente por nombre 
/*------------------------------------------------------------------*/
void ejercicio1(int nEle, struct datos* Vector, int criterio)
{

     if(criterio==0) 
     {
         //INCLUYE AQUI LA LLAMADA A TU FUNCIÓN DE ORDENACIÓN PARA ORDEN ASCENDENTE
        
        ordena(Vector, nEle, &IMCAscendente);
                       
     }
     else 
     {
         //INCLUYE AQUI LA LLAMADA A TU FUNCIÓN DE ORDENACIÓN PARA ORDEN DESCENDENTE
        
        ordena(Vector, nEle, &nombreDescendente);
     }
}

//ESCRIBE AQUÍ TU FUNCION DE Y TODAS LAS FUNCIONES QUE CONSIDERES NECESARIAS

void ordena(struct datos * v, int tam, int (*metodo)(struct datos a, struct datos b)){

    for (int i = 0; i < tam; i++){
        
        for (int j = i + 1; j < tam; j++){
            
            if((*metodo)(v[i], v[j]) == 1){

                struct datos aux = v[i];

                v[i] = v[j];

                v[j] = aux; 
            }
        }
    }
}

int IMCAscendente(struct datos a, struct datos b){

    float imca = a.pesoKg / (a.alturaM * a.alturaM);
    float imcb = b.pesoKg / (b.alturaM * b.alturaM);

    if(imca > imcb){

        return 1;
    }

    return 0;
}

int nombreDescendente(struct datos a, struct datos b){

    if(strcmp(a.nombre, b.nombre) < 0){

        return 1;
    }

    return 0;
}