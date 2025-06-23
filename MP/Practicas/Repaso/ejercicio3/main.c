
#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mostrarVector(struct dato * v, int tam);

int main()
{
    struct dato v [] = {
        {"NOMBRE1",1.5,5},
        {"NOMBRE2",4.1,1},
        {"NOMBRE3",8.3,2},
        {"NOMBRE4",0.1,3},
        {"NOMBRE5",9.23,5}
    };

    printf("\n");
    printf("Vector antes de ser ordenado:\n");
    mostrarVector(v,5);

    printf("\n");
    printf("\n");
    printf("Vector después de ser ordenado por nombre alfabeticamente:\n");
    ejercicio(v,5,1);
    mostrarVector(v,5);


    printf("\n");
    printf("\n");
    printf("Vector después de ser ordenado por peso descendentemenete:\n");
    ejercicio(v,5,2);
    mostrarVector(v,5);


    printf("\n");
    printf("\n");
    printf("Vector después de ser ordenado por codigo ascendentemente:\n");
    ejercicio(v,5,3);
    mostrarVector(v,5);


}

void mostrarVector(struct dato * v, int tam)
{
    for (size_t i = 0; i < tam; i++)
    {
        printf("Nombre: %s Peso: %.2f Código: %d\n",v[i].nombre, v[i].peso, v[i].codigo);
    }
    
}