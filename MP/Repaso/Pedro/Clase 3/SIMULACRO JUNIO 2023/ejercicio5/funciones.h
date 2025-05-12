/*------------------------------------------------------------------*/
//                 NO MODIFICAR ESTE FICHERO
/*------------------------------------------------------------------*/
#ifndef FUNCIONES
#define FUNCIONES
#define MAXLINEA 100


struct alumno
{
   long dni; //identificador univoco del alumno
   char nombre[MAXLINEA]; //nombre y apellidos del alumno  
   float media; //nota media   
};

int indice(struct alumno* V, int nEle, int codigo);
int comprobarVector(int nEle, struct alumno* VectorResultado, struct alumno* Correctos);
void imprimirVector(struct alumno* V, int nEle);

#endif
