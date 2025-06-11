#include "funciones.h"
#include <string.h>
#include <stdio.h>

int indice(struct alumno* V, int nEle, int codigo)
{
    for (int i = 0; i < nEle; i++)
    {
        if(V[i].dni==codigo)
            return i;
    }
    return -1;
}
int comprobarVector(int nEle, struct alumno* VectorResultado, struct alumno* Correctos)
{
    for (int i = 0; i < nEle; i++)
    {
        if(VectorResultado[i].dni!=Correctos[i].dni)
            return -1;
        if(strcmp(VectorResultado[i].nombre,Correctos[i].nombre)!=0)
            return -2;
        if((int)VectorResultado[i].media!=(int)Correctos[i].media)
            return -3;
    }
    return 1;    
}
void imprimirVector(struct alumno* V, int nEle)
{
    for (int i = 0; i < nEle; i++)
    {
        printf("Nombre: %s DNI: %ld Media: %f\n",V[i].nombre, V[i].dni, V[i].media);
    }
    
}