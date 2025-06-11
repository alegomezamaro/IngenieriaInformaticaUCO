#include "funciones.h"
#include "examen.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    struct lista * ls = NULL;
    int tam=-1;
    struct estudiante v[] = {
        {"Andrea Sanchez",7.8,50},
        {"Luis Mengual Santos", 5.9, 80},
        {"Pedro Romario",8.0,45},
        {"Mariana de la Luz",3.9,20}
    };

    //fichero a lista
    apartado1("estudiantes.txt",&ls,&tam);
    if(tam!=4 || !comprobar1(ls,v,4))
    {
        printf("\nAPARTADO 1 --> MAL\n");
    }
    else
    {
        printf("\nAPARTADO 1 --> BIEN\n");
    }

    printf("\n");

    //borrar último elemento de la lista
    apartado2(&ls); 
    if(!comprobar1(ls,v,3))
    {
        printf("\nAPARTADO 2 --> MAL\n");
    }
    else
    {
        printf("\nAPARTADO 2 --> BIEN\n");
    }

    delete(&ls);

    printf("\n");
    return 0;
}