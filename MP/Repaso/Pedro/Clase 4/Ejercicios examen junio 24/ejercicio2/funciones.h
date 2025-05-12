/*------------------------------------------------------------------*/
//                 NO MODIFICAR ESTE FICHERO
/*------------------------------------------------------------------*/
#ifndef FUNCIONES
#define FUNCIONES
#define LENGTH 100

struct nomina
{
   int codigo; //Identificador unico para cada empleado
   char nombre[LENGTH]; //ej. Homer Simpson
   float retenciones; //ej. 15.13    
   float salarioBruto; //ej. 2548.5
};

int imprimirVector(int nEle, struct nomina* Vector);
int imprimirVector2(int nEle, struct nomina* Vector);
void rellenarVector(int nEle, struct nomina * Vector);
int comprobarOrdenacion(int nEle, struct nomina* Vector, int* ordenCodigos, char* ordenNombres[]);


#endif
