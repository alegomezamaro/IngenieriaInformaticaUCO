#ifndef FUNCIONES_H
#define FUNCIONES_H

struct coche
{
    int matricula;
    char marca[100];
    int anio_matriculacion;
};

struct lista
{
    int matricula;
    char marca[100];
    int anio_matriculacion;
    struct lista * siguiente;
};

int ejercicio(struct coche * V1, struct coche * V2, int tam1, int tam2, struct lista ** LS);

//COMPLETA AQUÍ CON LOS PROTOTIPOS QUE HAYAS UTILIZADO

int buscarCoche(struct lista * LS, int dato);

void insertarDetras(struct lista ** LS, struct coche dato);

struct lista * nuevoElemento();

#endif