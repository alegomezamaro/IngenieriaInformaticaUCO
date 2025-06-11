#include "funciones.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int comprobar(struct lista * LS, struct coche * V);

int main()
{
    struct coche c1 = {1111,"marca 1",1};
    struct coche c2 = {2222,"marca 2",2};
    struct coche c3 = {3333,"marca 3",3};
    struct coche c4 = {4444,"marca 4",4};
    struct coche c5 = {5555,"marca 5",5};

    struct coche V1[] = {
        {1111,"marca 1",1},
        {2222,"marca 2",2},
        {3333,"marca 3",3}
    };

    struct coche V2[] = {
        {1111,"marca 1",1},
        {4444,"marca 4",4},
        {5555,"marca 5",5},
        {3333,"marca 3",3}
    };

    struct coche RESULTADO[] = {
        {1111,"marca 1",1},
        {2222,"marca 2",2},
        {3333,"marca 3",3},
        {4444,"marca 4",4},
        {5555,"marca 5",5}
    };

    struct lista * LS = NULL;

    int cont = ejercicio(V1,V2,3,4,&LS);

    if(cont==5 && comprobar(LS,RESULTADO))
    {
        printf("\n EJERCICIO CORRECTO\n\n");
    }
    else
    {
        printf("\n EJERCICIO INCORRECTO\n\n");
    }

    return 0;
}

int comprobar(struct lista * LS, struct coche * V)
{
    int i=0;
    struct lista * aux = LS;
    while(aux!=NULL)
    {
        if(aux->matricula != V[i].matricula || strcmp(aux->marca,V[i].marca)!=0 || aux->anio_matriculacion!=V[i].anio_matriculacion )
            return 0;
        aux = aux->siguiente;
        i++;
    }
    return 1;
}