#ifndef FUNCIONES_H
#define FUNCIONES_H

struct producto
{
    char nombre[50];
    int cod;
    float precio;
    int unidades;
};

void existeFichero(char *nombreFichero);
void mostrarFichero(char *nombreFichero);

//void añadirProducto(char *nombreFichero,struct producto nuevo);
//void borrarProducto(char *nombreFichero,char *nombre);
void contarFichero(char *nombreFichero,int *tam);
//void modificarFichero(char *nombreFichero,char *nombre,int cod);

/*struct producto * reservarMemoria(int cont);

void FicherobinVector(char *nombreFichero,struct producto *v);
void VectorFichero(char *nuevoFichero,struct producto *v,int cont);

void librerarMemoria(struct producto **v);*/


#endif