#include "funciones.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc!=4){
        printf("Error al iniciar el programa.\n");
        exit(-1);
    }
    
    char * nombreFichero=argv[1];
    char * nuevoFichero=argv[2];
    char * binarioFichero=argv[3];

    existeFichero(nombreFichero);

    mostrarFichero(nombreFichero);

    struct alumnos nuevo;

    printf("Introduzca el nombre del nuevo alumno: ");
    scanf("%s",nuevo.nombre);
    printf("Introduzca el apellido1 del alumno: ");
    scanf("%s",nuevo.apellido1);
    printf("Introduzca el apellido2 del alumno: ");
    scanf("%s",nuevo.apellido2);
    printf("Introduzca la edad del alumno: ");
    scanf("%d",&nuevo.edad);
    printf("Introduzca el bilingue del alumno: ");
    scanf("%d",&nuevo.bilingue);

    añadirAlumno(nombreFichero,nuevo);

    char nombre[1024];
    int bilingue;

    printf("Introduce el nombre del alumno que desea modificar: ");
    scanf("%s",nombre);
    printf("Introduce si es bilingue o no: ");
    scanf("%d",&bilingue);

    modificarAlumno(nombreFichero,nombre,bilingue);

    printf("Introduce el nombre del alumno que desea borrar: ");
    getchar();
    scanf("%s",nombre);
    borrarNombre(nombreFichero,nombre);

    int tam;
    contarFichero(nombreFichero,&tam);
    printf("El tamaño del fichero es %d\n",tam);

    struct alumnos *v=NULL;
    v=reservarMemoria(tam);

    fichero_vector(nombreFichero,v);
    for (int i = 0; i < tam; i++){
        printf("%s %s %s %d %d\n",v[i].nombre,v[i].apellido1,v[i].apellido2,v[i].edad,v[i].bilingue);
    }

    vector_Fichero(nuevoFichero,v,tam);
    vector_Ficherob(binarioFichero,v,tam);
    

    liberarMemoria(&v);

    return 0;
}


