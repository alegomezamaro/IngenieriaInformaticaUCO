#ifndef EXAMEN
#define EXAMEN

#define MAXLINEA 100

struct equipo
{
    int codigo; //identificador univoco del equipo
    char nombre[MAXLINEA]; //nombre del equipo
    float porcentaje; //porcentaje de triples acertados
};

struct equipo * apartado1(int * nEle, char * nombreFichero);
void apartado2(int nEle, struct equipo * Vector, char * nombreFichero);
void apartado3(int nEle, struct equipo * Vector, char * nombreFichero);

//Completa aquí con las funciones que hayas implementado

#endif