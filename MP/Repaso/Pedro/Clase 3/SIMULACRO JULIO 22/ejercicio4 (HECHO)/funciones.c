/*
    www.academiamain.es
    605 45 70 99 (Ángel)
*/
#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    La función ejercicio recibe el nombre de un fichero de alumnos como primer argumento,
    como segundo argumento una lista llamada aprobados, y como tercer argumento, una lista llamada
    suspensos. 

    La función debe encolar en la lista aprobados los alumnos del fichero que estén aprobados,
    y en la cola suspensos, aquellos que estén suspensos.

    Además deberá retornar el número de alumnos total procesados en el fichero.
*/

int ejercicio(char * fichero, struct lista ** aprobados, struct lista ** suspensos){
    //COMPLETA AQUÍ

    FILE * fich = fopen(fichero, "r");

    if(fich == NULL){

        printf("Error al abrir el fichero. \n");
        exit(-1);
    }

    struct alumno a;

    int procesados = 0;

    while(fgets(a.nombre, LENGTH, fich)){

        a.nombre[strlen(a.nombre) -1] = '\0';
        fscanf(fich, "%d %f\n", &a.curso, &a.nota);

        if(a.nota < 5){

            insertarDetras(suspensos, a);

        }
        else
        {
            insertarDetras(aprobados, a);
        }
        
        procesados++;
    }

    fclose(fich);

    //NO OLVIDES CAMBIAR EL RETURN
    return procesados;
}

//COMPLETA AQUÍ CON LAS FUNCIONES QUE NECESITES

void insertarDetras(struct lista ** LS, struct alumno a){

    struct lista * nuevo = nuevoElemento();

    strcpy(nuevo -> dato.nombre, a.nombre);

    nuevo -> dato.curso = a.curso;

    nuevo -> dato.nota = a.nota;

    if((*LS) == NULL){

        (*LS) = nuevo;

    }else{

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

        printf("Error al reservar memoria para un nuevo elemento. \n");
        exit(-1);
    }

    return nuevo;
}