#include "examen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    *nEle: número de elementos del vector. Hay que calcular su valor y devolverlo por referencia.
    nombreFichero: Nombre del fichero de datos.
    VALOR DEVUELVO: Vector de struct que debes reservar.
*/
struct equipo * apartado1(int * nEle, char * nombreFichero)
{

    (*nEle) = 0;

    FILE * fich = fopen(nombreFichero, "r");

    if(fich == NULL){

        printf("Error al abrir el fichero. \n");
        exit(-1);
    }

    struct equipo e;

    int tiros_acertados;

    int tiros_lanzados;

    struct equipo * v = NULL;

    v = reservarMemoria(nEle);

    while(fgets(e. nombre, MAXLINEA, fich)){

        e.nombre[strlen(e.nombre) -1] = '\0';
        fscanf(fich, "%d %d %d\n", e.codigo, tiros_lanzados, tiros_acertados);

        e.porcentaje = 
    }
    
    return NULL;
}

/*
    nEle: número de elementos del vector
    Vector: vector que ya ha sido reservador en el main y que debes rellenar con los datos del fichero.
    nombreFichero: Nombre del fichero de datos.
*/
void apartado2(int nEle, struct equipo * Vector, char * nombreFichero)
{

}

/*
    nEle: número de elementos del vector.
    Vector: Vector ya creado y relleno por el main con los datos de equipos.
    nombreFicher: el nombre del fichero resultado.
*/
void apartado3(int nEle, struct equipo * Vector, char * nombreFichero)
{
    
}

//Completa aquí con las funciones que hayas implementado
