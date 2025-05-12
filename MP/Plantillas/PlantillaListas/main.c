#include "funciones.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    
    struct nodo * cabeza =NULL;
    
    inyectarDelante(&cabeza,1);
    inyectarDelante(&cabeza,2);
    inyectarDelante(&cabeza,3);

    inyectarDetras(&cabeza,4);
    inyectarDetras(&cabeza,5);

    mostrarLista(cabeza);

    int tam;
    contarElemento(cabeza,&tam);
    printf("Los elementos son %d \n",tam);

    int elemento;
    printf("introduce el elemento que buscas,\n");
    //scanf(elemento); Mirarlo
    buscaElemento(cabeza,elemento);

    borrarElemento(&cabeza,elemento);

    borrarLista(&cabeza);

    MostrarListaRecursiva(cabeza);

    return 0;
}
