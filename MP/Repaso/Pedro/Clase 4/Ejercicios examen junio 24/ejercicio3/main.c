/*
    www.academiamain.es
    605 45 70 99 (Ángel)
*/
#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comprobar(struct dato * v1, struct dato * v2, int tam);
int compararDato(struct dato a, struct dato b);
void liberar(struct dato ** v);

int main()
{
    struct dato v1[] = {{"nombre 1", 1, 10.4},{"nombre 3", 2, 27.8}, {"nombre 7", 9, 12.5}};
    struct dato v2[] = {{"nombre 4", 5, 41.7},{"nombre 2", 3, 77.1}, {"nombre 9", 13, 42.1},{"nombre 6",14,65.3}};
    struct dato * v3 = NULL;
    struct dato vresult [] = {{"nombre 1", 1, 10.4},{"nombre 2", 3, 77.1},{"nombre 3", 2, 27.8},{"nombre 4", 5, 41.7},{"nombre 6",14,65.3},{"nombre 7", 9, 12.5},{"nombre 9", 13, 42.1}};
    int tam = 0;

    v3 = ejercicio(v1,v2,3,4,&tam);

    if(tam!=7)
    {
        printf("\n\nTAMAÑO DEL VECTOR RESULTADO INCORRECTO\n\n");
    }
    else
    {
        if(comprobar(v3,vresult,7))
        {
            printf("\n\nEJERCICIO CORRECTO!\n\n");
        }
        else
        {
            printf("\n\nEJERCICIO INCORRECTO!\n\n");
        }
    }

    liberar(&v3);

    return 0;
}

int comprobar(struct dato * v1, struct dato * v2, int tam)
{
    for (size_t i = 0; i < tam; i++)
    {
        if(!compararDato(v1[i],v2[i]))
        {
            return 0;
        }
    }
    return 1;
}

int compararDato(struct dato a, struct dato b)
{
    return strcmp(a.nombre,b.nombre)==0 && a.codigo==b.codigo && a.longitud==b.longitud;
}

void liberar(struct dato ** v)
{
    free(*v);
    (*v)=NULL;
}