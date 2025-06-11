#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comprobar2(struct equipo * result,struct equipo * v,int tam)
{
    for (size_t i = 0; i < tam; i++)
    {
        if(strcmp(result[i].nombre,v[i].nombre)!=0 || result[i].codigo!=v[i].codigo 
            || result[i].porcentaje!=v[i].porcentaje)
            return 0;
    }
    return 1;
}
