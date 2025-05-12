#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv)
{
    if (argc!=3)
    {
        printf("Error al iniciar el progama.\n");
        exit(-1);
    }
    
    char * nombreFichero=argv[1];
    char *nuevoFichero=argv[2];

    existeFichero(nombreFichero);

    /*mostrarFichero(nombreFichero);

    struct producto nuevo;

    printf("Introdice el nuevo nombre:\n");
    fgets(nuevo.nombre, 50, stdin);
    nuevo.nombre[strlen(nuevo.nombre) - 1] = '\0';
    printf("Introdice el nuevo cod:\n");
    scanf("%d",&nuevo.cod);
    printf("Introdice el nuevo precio:\n");
    scanf("%f",&nuevo.precio);
    printf("Introdice las unidades:\n");
    scanf("%d",&nuevo.unidades);

    añadirProducto(nombreFichero,nuevo);

    char nombre[50];
    printf("Introduce el nombre de la persona que deseas eliminar.\n");
    getchar();
    fgets(nombre,50,stdin);
    nombre[strlen(nombre)-1]='\0';
    borrarProducto(nombreFichero,nombre);
    

    int cod;

    printf("Introduce el cod de la persona.\n");
    scanf("%d",&cod);
    printf("Introduce el nombre de la persona que deseas modificar.\n");
    getchar();
    fgets(nombre,50,stdin);
    nombre[strlen(nombre)-1]='\0';
    modificarFichero(nombreFichero,nombre,cod);*/

    struct producto *v=NULL;

    int tam;
    contarFichero(nombreFichero,&tam);
    printf("En el fichero hay %d personas.\n",tam);
    printf("\n");

/*
    v=reservarMemoria(cont);

    FicherobinVector(nombreFichero,v);
    for (int i = 0; i < cont; i++)
    {
        printf("nombre: %s cod: %d precio: %f unidades: %d\n",v[i].nombre,v[i].cod,v[i].precio,v[i].unidades);
    }

    VectorFichero(nuevoFichero,v,cont);
    

    librerarMemoria(&v);*/

    

    return 0;
}
