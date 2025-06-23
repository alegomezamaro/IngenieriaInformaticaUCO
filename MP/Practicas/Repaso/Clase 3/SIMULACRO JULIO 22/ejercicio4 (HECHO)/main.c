/*
    www.academiamain.es
    605 45 70 99 (Ángel)
*/
#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comprobar(struct lista * aprobados,struct alumno * vaprobados, struct lista * suspensos, struct alumno * vsuspensos);
int comparar(struct alumno a, struct alumno b);
void borrarLista(struct lista ** ls);

int main()
{
    struct lista * aprobados = NULL, * suspensos = NULL;
    struct alumno vaprobados [] = {
            {"Mariano Lopez Lopez", 2,8.7},
            {"Maria Garcia Brey", 1,5.9},
            {"Luis Enrique Palos", 3, 6.3}
            };
    struct alumno vsuspensos [] = {
            {"Luisa Federia de la Serna", 2, 3.9},
            {"Pedro Luis Diaz", 2, 2.3}
            };

    int tam = ejercicio("alumnos.txt",&aprobados,&suspensos);

    if(tam == 5 && comprobar(aprobados,vaprobados,suspensos,vsuspensos))
    {
        printf("\n\nEJERCICIO CORRECTO!\n\n");
    }
    else
    {
        printf("\n\nEJERCICIO INCORRECTO!\n\n");
    }

    borrarLista(&aprobados);
    borrarLista(&suspensos);
    return 0;
}

int comprobar(struct lista * aprobados,struct alumno * vaprobados, struct lista * suspensos, struct alumno * vsuspensos)
{
    struct lista * aux = aprobados;
    int i=0;
    while(aux!=NULL)
    {
        if(!comparar(aux->dato,vaprobados[i]))
            return 0;
        aux = aux->siguiente;
        i++;
    }

    i=0;
    aux = suspensos;
    while(aux!=NULL)
    {
        if(!comparar(aux->dato,vsuspensos[i]))
            return 0;
        aux = aux->siguiente;
        i++;
    }

    return 1;
}

int comparar(struct alumno a, struct alumno b)
{
    return strcmp(a.nombre,b.nombre)==0 && a.curso==b.curso;// && a.nota==b.nota;
}

void borrarLista(struct lista ** ls)
{
    while((*ls)!=NULL)
    {
        struct lista * aux = (*ls);
        (*ls) = (*ls)->siguiente;
        free(aux);
    }
}
