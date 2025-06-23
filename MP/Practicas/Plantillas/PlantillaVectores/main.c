#include "funciones.h"
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char **argv){
    if (argc!=2){
        printf("Error al iniciar el programa.\n");
        exit(-1);
    }
    int tam=atoi(argv[1]);
    int *v=NULL;

    v = reservarMemoria(tam);

    rellenarMemoria(v,tam);

    imprimirVector(v,tam);
    
    liberarMemoria(&v);
    return 0;
}

