/*------------------------------------------------------------------*/
/* NOMBRE Y APELLIDOS:                                              */
/* DNI:                                                             */
/*------------------------------------------------------------------*/
#ifndef EXAMEN
#define EXAMEN

#include "funciones.h"
/*------------------------------------------------------------------*/
//HAZ AQUI LOS INCLUDE QUE CONSIDERES NECESARIOS
/*------------------------------------------------------------------*/

/*------------------------------------------------------------------*/
//ESCRIBE AQUI LOS PROTOTIPOS DE TUS FUNCIONES
/*------------------------------------------------------------------*/
void apartado1(int nEle, struct nomina* Vector, int criterio);
void apartado2(int nEle, struct nomina* Vector);
   
void ordena(struct nomina * v, int tam, int (*metodo)(struct nomina a, struct nomina b));

int salarioAsc(struct nomina a, struct nomina b);

int nombreDesc(struct nomina a, struct nomina b);

void frecursiva(struct nomina * Vector, int nEle);

#endif