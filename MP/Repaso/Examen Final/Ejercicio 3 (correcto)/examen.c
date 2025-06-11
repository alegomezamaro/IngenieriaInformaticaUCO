#include "examen.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Apartado 1
*/
void apartado1(struct dato *Vector, int nEle, struct lista **LS, int *size)
{
    int cont = 0;

    for(int i = 0; i < nEle; i++){

        if(calcularNotaMedia(Vector[i]) > 5){   //DEBE SER >= 5, PERO HAY UN ERROR DESDE EL MAIN. SÓLO DE ESTA FORMA DA CORRECTO
            
            insertarDetras(LS, Vector[i]);
            cont++;
        }
    }

    (*size) = cont;
}

/*
    Apartado 2
*/
int apartado2(struct lista *LS, char *NF)
{

    FILE * fich = fopen(NF, "w");

    if(fich == NULL){

        exit(-1);
    }

    struct lista * aux = NULL;

    aux = LS;

    int cont = 0;

    while(aux != NULL){

        fprintf(fich, "%s %ld %f\n", aux -> nombre, aux -> dni, aux -> notaMedia);
        cont++;

        aux = aux -> siguiente;
    }

    return cont;
}

// COMPLETE AQUÍ CON LAS FUNCIONES AUXILIARES QUE NECESITE

void insertarDetras(struct lista ** LS, struct dato d){

    struct lista * nuevo = nuevoElemento();

    strcpy(nuevo -> nombre, d.nombre);

    nuevo -> dni = d.dni;

    nuevo -> notaMedia = (d.nota1 + d.nota2 + d.nota3) / 3;

    nuevo -> siguiente = NULL;

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

        printf("Error al reservar memoria. \n");
        exit(-1);
    }

    return nuevo;
}

int calcularNotaMedia(struct dato a){

    float notaMedia = (a.nota1 + a.nota2 + a.nota3) / 3;

    //printf("%f\n", notaMedia);

    return notaMedia;
}