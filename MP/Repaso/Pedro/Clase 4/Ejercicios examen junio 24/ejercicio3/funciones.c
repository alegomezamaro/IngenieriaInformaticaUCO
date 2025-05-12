/*
    www.academiamain.es
    605 45 70 99 (Ángel)
*/
#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    La función ejercicio retorna un puntero a un array de elementos de tipo struct dato, el cual debe contener 
    los elementos de los arrays v1 y v2 pero ordenados por nombre alfabéticamente. 

    Además debe retornar por referencia el tamaño del vector que retorna por valor.

    Es decir, si por ejemplo se recibe un vector v1 de tamaño 5 y un vector v2 de tamaño 3, la función debe guardar 
    en el cuarto argumento (int * tam) un 8, y retornará mediante un return un vector con los 8 elementos ordenados 
    por nombre.
*/

struct dato * ejercicio(struct dato * v1,struct dato * v2,int tam1, int tam2, int * tam)
{
    //COMPLETA CAMBIANDO EL RETURN

    (* tam) = tam1 + tam2;

    struct dato vr = NULL;

    vr = reservarMemoria(tam);

    for (int i = 0; i < tam1; i++) {
        vr[i] = v1[i];
    }

    for (int i = 0; i < tam2; i++) {
        vr[tam1 + i] = v2[i];
    }

    ordena(vr, tam);

    //NO OLVIDES CAMBIAR EL RETURN
    return NULL;
}

//COMPLETA AQUÍ CON LAS FUNCIONES QUE NECESITES
