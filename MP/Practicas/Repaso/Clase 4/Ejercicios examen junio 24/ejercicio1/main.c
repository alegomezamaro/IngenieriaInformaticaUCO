#include "funciones.h"
#include "examen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    
    printf("\nEste main intentará evaluarte los 3 apartados por separado, aunque el código debería ser revisado:\n");

    int status1 = 0, status2 = 0, status3 = 0;
    struct equipo * v = NULL;
    int tam = -1;
    v = apartado1(&tam,"equipos.txt");
    if(tam!=3 || v==NULL)
    {
        printf("\nApartado 1 incorrecto.\n");
        status1 = 1;
    }
    else
        printf("\nApartado 1 CORRECTO.\n");
    
    if(status1!=1)
        printf("\nApartado 2 requiere del apartado 1\n");
    else
    {
        apartado2(tam,v,"equipos.txt");
        struct equipo e1 = {"Universidad de Granada",11,326,198};
        struct equipo e2 = {"Escuela de Agronomos",15,435,310};
        struct equipo e3 = {"Real Betis",14,580,247};
        struct equipo result[3];
        result[0]=e1;
        result[1]=e2;
        result[2]=e3;
        status2 = comprobar2(result,v,3);
        if(status2==1)
            printf("\nApartado 2 incorrecto.\n");
        else
            printf("\nApartado 2 CORRECTO.\n");


    }

    printf("\n");
    return 0;   
}