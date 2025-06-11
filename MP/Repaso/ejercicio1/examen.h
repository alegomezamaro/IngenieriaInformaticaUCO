#ifndef EXAMEN
#define EXAMEN

#define SIZE 100

struct estudiante
{
    char nombre[SIZE];
    float nota_media;
    int creditos_superados;
};

struct lista
{
    char nombre[SIZE];
    float nota_media;
    float porcentaje_superado;
    struct lista * siguiente;
};

void apartado1(char * nF, struct lista ** COLA, int * elementos);
void apartado2(struct lista ** COLA);

//COMPLETAR CON LAS FUNCIONES QUE HAYAS IMPLEMENTADO

//
#endif