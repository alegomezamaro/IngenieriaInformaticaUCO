#ifndef FUNCIONES_H
#define FUNCIONES_H

#define LENGTH 100

struct dato
{
    char nombre[LENGTH];
    int codigo;
    double longitud;
};

struct dato * ejercicio(struct dato * v1,struct dato * v2,int tam1, int tam2, int * tam);

//COMPLETA AQUÍ CON LOS PROTOTIPOS


#endif