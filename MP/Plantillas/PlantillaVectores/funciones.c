#include "funciones.h"

#include <stdlib.h>
#include <stdio.h>

int *reservarMemoria(int tam){
    int *v=NULL;
    v=(int *)malloc(sizeof(int)*tam);
    if (v==NULL){
        printf("Error al reservar memoria.\n");
        exit(-1);
    }
    return v;
}

void rellenarMemoria(int *v,int tam){
    printf("Rellena los datos:\n");
    for (int i = 0; i < tam; i++){
        scanf("%d",&v[i]);
    }
}

void imprimirVector(int *v,int tam){
    for (int i = 0; i < tam; i++){
        printf("El vector es: %d \n",v[i]);
    }
}

void liberarMemoria(int **v){
    free(*v);
    (*v)=NULL;
}