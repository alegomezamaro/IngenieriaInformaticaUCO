#include "funciones.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void existeFichero(char *nombreFichero){
    FILE * fich=fopen(nombreFichero,"r");
    if (fich==NULL){
        printf("No existe fichero.\n");
        exit(-1);
    }
    fclose(fich);
}

void mostrarFichero(char *nombreFichero){
    FILE * fich=fopen(nombreFichero,"r");
    if (fich==NULL){
        printf("No existe fichero.\n");
        exit(-1);
    }
    struct alumnos a;
    while (fscanf(fich, "%s %s %s %d %d",a.nombre,a.apellido1,a.apellido2,&a.edad,&a.bilingue)==5){
        printf("nombre: %s Apellidos %s %s Edad: %d Bilingue: %d\n",a.nombre,a.apellido1,a.apellido2,a.edad,a.bilingue);
    }
    fclose(fich);
}

void contarFichero(char *nombreFichero,int *tam){
    FILE * fich=fopen(nombreFichero,"r");
    if (fich==NULL){
        printf("No existe fichero.\n");
        exit(-1);
    }

    int contador=0;
    struct alumnos a;
    while (fscanf(fich, "%s %s %s %d %d",a.nombre,a.apellido1,a.apellido2,&a.edad,&a.bilingue)==5){
        contador++;
    }

    fclose(fich);
    (*tam)=contador;
}

void añadirAlumno(char *nombreFichero,struct alumnos nuevo){
     FILE * fich=fopen(nombreFichero,"a");
    if (fich==NULL){
        printf("No existe fichero.\n");
        exit(-1);
    }

    
    fprintf(fich,"%s %s %s %d %d\n",nuevo.nombre,nuevo.apellido1,nuevo.apellido2,nuevo.edad,nuevo.bilingue);
    fclose(fich);
}

void modificarAlumno(char *nombreFichero,char *nombre,int bilingue){
    FILE * fich=fopen(nombreFichero,"r");
    if (fich==NULL){
        printf("No existe fichero.\n");
        exit(-1);
    }

    FILE * fich2=fopen("auxiliar.txt","w");
    if (fich2 == NULL){
        printf("Error al abrir el fichero...\n");
        exit(-1);
    }

    struct alumnos a;
    while (fscanf(fich, "%s %s %s %d %d",a.nombre,a.apellido1,a.apellido2,&a.edad,&a.bilingue)==5){
        if (strcmp(a.nombre,nombre)==0){
            a.bilingue=bilingue;
        }
        fprintf(fich2,"%s %s %s %d %d\n",a.nombre,a.apellido1,a.apellido2,a.edad,a.bilingue);
    }

    fclose(fich);
    fclose(fich2);

    remove(nombreFichero);
    rename("auxiliar.txt",nombreFichero);
}

void borrarNombre(char *nombreFichero,char *nombre){
    FILE * fich=fopen(nombreFichero,"r");
    if (fich==NULL){
        printf("No existe fichero.\n");
        exit(-1);
    }

    FILE * fich2=fopen("auxiliar.txt","w");
    if (fich2 == NULL){
        printf("Error al abrir el fichero...\n");
        exit(-1);
    }

    struct alumnos a;
    int borrador=0;
    while (fscanf(fich, "%s %s %s %d %d",a.nombre,a.apellido1,a.apellido2,&a.edad,&a.bilingue)==5){
        if (strcmp(a.nombre,nombre)!=0){
            fprintf(fich2,"%s %s %s %d %d\n",a.nombre,a.apellido1,a.apellido2,a.edad,a.bilingue);    
        }
        else{
            borrador=1;
        }
    }

    fclose(fich);
    fclose(fich2);

    remove(nombreFichero);
    rename("auxiliar.txt",nombreFichero);
}

struct alumnos *reservarMemoria(int tam){
    struct alumnos *v=NULL;
    v=(struct alumnos*)malloc(sizeof(struct alumnos)*tam);
    if (v==NULL){
        printf("Error al reservar memoria,\n");
        exit(-1);
    }

    return v;
    
}

void fichero_vector(char *nombreFichero,struct alumnos *v){
    FILE * fich=fopen(nombreFichero,"r");
    if (fich==NULL){
        printf("Error al abrir el fichero.\n");
        exit(-1);
    }
    
    struct alumnos a;
    int i=0;
    while (fscanf(fich,"%s %s %s %d %d",a.nombre,a.apellido1,a.apellido2,&a.edad,&a.bilingue)==5){
        strcpy(v[i].nombre,a.nombre);
        strcpy(v[i].apellido1,a.apellido1);
        strcpy(v[i].apellido2,a.apellido2);
        v[i].edad=a.edad;
        v[i].bilingue=a.bilingue;
        i++;
    }
    

    fclose(fich);
}

void vector_Fichero(char *nuevoFichero,struct alumnos *v,int tam){
    FILE * fich=fopen(nuevoFichero,"w");
    if (fich==NULL){
        printf("Error al abrir el fichero.\n");
        exit(-1);
    }

    for (int i = 0; i < tam; i++){
        fprintf(fich,"%s %s %s %d %d\n",v[i].nombre,v[i].apellido1,v[i].apellido2,v[i].edad,v[i].bilingue);
    }
    
    fclose(fich);
}

void vector_Ficherob(char *binarioFichero,struct alumnos *v,int tam){
    FILE * fich=fopen(binarioFichero,"wb");
    if (fich==NULL){
        printf("Error al abrir el fichero.\n");
        exit(-1);
    }

    for (int i = 0; i < tam; i++){
        fwrite(&v[i],sizeof(struct alumnos),1,fich);
    }
    

    fclose(fich);
}

void liberarMemoria(struct alumnos **v){
    free(*v);
    (*v)=NULL;
}
