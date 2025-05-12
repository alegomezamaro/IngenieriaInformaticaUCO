#ifndef FUNCIONES_H
#define FUNCIONES_H

struct alumnos
{
    char nombre[1024];
    char apellido1[1024];
    char apellido2[1024];
    int edad;
    int bilingue;
};

void existeFichero(char *nombreFichero);
void mostrarFichero(char *nombreFichero);
void contarFichero(char *nombreFichero,int *tam);

void añadirAlumno(char *nombreFichero,struct alumnos nuevo);
void modificarAlumno(char *nombreFichero,char *nombre,int bilingue);
void borrarNombre(char *nombreFichero,char *nombre);

struct alumnos *reservarMemoria(int tam);
void fichero_vector(char *nombreFichero,struct alumnos *v);
void vector_Fichero(char *nuevoFichero,struct alumnos *v,int tam);
void vector_Ficherob(char *binarioFichero,struct alumnos *v,int tam);
void liberarMemoria(struct alumnos **v);

#endif