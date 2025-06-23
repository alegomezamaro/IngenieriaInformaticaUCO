#include "funciones.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void mostrarVector(struct dato * v, int tam);
int comprobarListas(struct lista * lista,struct dato * v);

int main()
{
    struct dato v[] = {
        {1111,1.5},
        {2222,5.3},
        {3333,0.5},
        {4444,4.9},
        {5555,2.9}
    };

    struct lista * cabeza = NULL;
    struct dato datosCorrectos[] = {
        {3333,0.5},
        {1111,1.5}
    };


    printf("\nLOS ELEMENTOS DEL VECTOR SON LOS SIGUIENTES:\n");
    mostrarVector(v,5);

    int cantidad = ejercicio(v,5,&cabeza,2.0);
    if(cantidad==2 && comprobarListas(cabeza,datosCorrectos))
        printf("\nEJERCICIO CORRECTO\n\n");
    else
        printf("\nEJERCICIO INCORRECTO\n\n");

    return 0;
}

void mostrarVector(struct dato * v, int tam)
{
    for (size_t i = 0; i < tam; i++)
    {
        printf("Codigo: %d Peso: %.2f\n",v[i].codigo,v[i].peso);
    }
}

int comprobarListas(struct lista * lista,struct dato * v)
{
    int i=0;
    struct lista * aux = lista;
    while(aux!=NULL)
    {
        if((aux->elemento).codigo != v[i].codigo || (aux->elemento).peso != v[i].peso)
            return 0;
        i++;
        aux=aux->siguiente;
    }
    return 1;
}