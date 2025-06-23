/*------------------------------------------------------------------*/
/* NOMBRE Y APELLIDOS:                                              */
/* DNI:                                                             */
/*------------------------------------------------------------------*/
#include "funciones.h"
#include "examen.h"

/*------------------------------------------------------------------*/
//HAZ AQUI LOS INCLUDE QUE CONSIDERES NECESARIOS
/*------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*------------------------------------------------------------------*/
/*Apartado1: Ordenacion y punteros a funciones
               nEle: número de elementos del vector
               Vector: el vector a ordenar. Ya ha sido reservado 
                       y rellenado en el main
               criterio: 0-->ascendente por salario NETO
                         1-->descendente por nombre
*/                          
/*------------------------------------------------------------------*/
void apartado1(int nEle, struct nomina* Vector, int criterio)
{

     if(criterio==0) 
     {
         //INCLUYE AQUI LA LLAMADA A TU FUNCIÓN DE ORDENACIÓN PARA ORDEN ASCENDENTE

        ordena(Vector, nEle, &salarioAsc);       
     }
     else 
     {
         //INCLUYE AQUI LA LLAMADA A TU FUNCIÓN DE ORDENACIÓN PARA ORDEN DESCENDENTE
        
        ordena(Vector, nEle, &nombreDesc);
     }
}

/*------------------------------------------------------------------*/
/*Apartado2: Recursividad
             nEle: número de elementos del vector
             Vector: el vector a imprimir de forma RECURSIVA. 
                       y en orden directo (desde la posicion 0 hasta el final).
                       Ya ha sido reservado y rellenado con valores en el main.
*/                       
/*------------------------------------------------------------------*/
void apartado2(int nEle, struct nomina* Vector)
{
    //INCLUYE AQUI LA LLAMADA A TU FUNCIÓN RECURSIVA        
           
}

/*------------------------------------------------------------------*/
//ESCRIBE AQUI TODAS LAS FUNCIONES QUE CONSIDERES NECESARIAS
/*------------------------------------------------------------------*/

void ordena(struct nomina * v, int tam, int (*metodo)(struct nomina a, struct nomina b)){

    for (int i = 0; i < tam; i++){
        
        for (int j = i + 1; j < tam; j++){
            
            if((*metodo)(v[i], v[j]) == 1){

                struct nomina aux = v[i];

                v[i] = v[j];

                v[j] = aux;
            }
        }
    }
}

int salarioAsc(struct nomina a, struct nomina b){

    float snA = a.salarioBruto - a.salarioBruto * (a.retenciones / 100);
    float snB = b.salarioBruto - b.salarioBruto * (b.retenciones / 100);

    if(snA > snB){

        return 1;
    }

    return 0;
}

int nombreDesc(struct nomina a, struct nomina b){

    if(strcmp(a.nombre, b.nombre) < 0){

        return 1;
    }

    return 0;
}
