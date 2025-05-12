#include "examen.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
    Apartado 1
*/
void apartado1(struct alumno *Vector, int nElementos, int criterio)
{
    if(criterio == 1){

        ordena(Vector, nElementos, &nombreAlfa);
    }

    if(criterio == 2){

        ordena(Vector, nElementos, &dniDescendente);
    }
}

/*
    Apartado 2
*/
void apartado2(struct alumno *Vector, int nElementos)
{
    qsort(Vector, sizeof(struct alumno), nElementos, &mediaAsc);
}

/*
    Apartado 3
*/
void apartado3(int dividendo, int divisor, int *resultado)
{
    
}

/*
    Apartado 4
*/
int apartado4(char *cadena, char caracter)
{
    return -1;
}

// COMPLETE AQUÍ CON LAS FUNCIONES AUXILIARES QUE NECESITE

void ordena(struct alumno * Vector, int nElementos, int (*metodo)(struct alumno a, struct alumno b)){

    for (int i = 0; i < nElementos; i++){
        
        for (int j = i + 1; j < nElementos; j++){
            
            if((*metodo)(Vector[i], Vector[j]) == 1){

                struct alumno aux = Vector[i];

                Vector[i] = Vector[j];

                Vector[j] = aux;
            }
        }
    }
}

int nombreAlfa(struct alumno a, struct alumno b){

    if(strcmp(a.nombre, b.nombre) > 0){

        return 1;
    }

    return 0;
}

int dniDescendente(struct alumno a, struct alumno b){

    if(a.dni < b.dni){

        return 1;
    }

    return 0;
}

int mediaAsc(const void * a, const void * b){

    struct alumno *alumnoA = (struct alumno *)a;
    struct alumno *alumnoB = (struct alumno *)b;

    float mediaA = (alumnoA->nota1 + alumnoA->nota2 + alumnoA->nota3) / 3.0;
    float mediaB = (alumnoB->nota1 + alumnoB->nota2 + alumnoB->nota3) / 3.0;

    if (mediaA > mediaB){

        return 1;
    } 

    return 0;
    

}