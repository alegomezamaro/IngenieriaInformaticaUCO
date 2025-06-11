/*------------------------------------------------------------------*/
/* NOMBRE Y APELLIDOS:                                              */
/* DNI:                                                             */
/*------------------------------------------------------------------*/
#include "funciones.h"

//HAZ AQUI LOS INCLUDE QUE SEAN NECESARIOS


/*------------------------------------------------------------------*/
/*Ejercicio 2: Recursividad
    -nEle: número de elementos de V1 y V2.
    -V1, V2, VR: Los dos vectores a mezclar y el vector resultado, 
         respectivamente. Estos vectores ya están reservados en el main.

/*------------------------------------------------------------------*/

void ejercicio2(int nEle, int* V1, int* V2, int* VR)
{
   //INCLUYE AQUI LA LLAMADA A TU FUNCIÓN RECURSIVA 
  for(int i = 0; i < nEle; i++){

    VR[i] = frecursiva(V1, V2, VR);
  }
}

//ESCRIBE AQUÍ TU FUNCION RECURSIVA Y TODAS LAS FUNCIONES QUE CONSIDERES NECESARIAS


