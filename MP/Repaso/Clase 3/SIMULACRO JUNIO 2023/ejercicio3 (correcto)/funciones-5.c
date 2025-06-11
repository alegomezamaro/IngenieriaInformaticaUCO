/*------------------------------------------------------------------*/
/* NOMBRE Y APELLIDOS:                                              */
/* DNI:                                                             */
/*------------------------------------------------------------------*/
#include "funciones.h"

//HAZ AQUI LOS INCLUDE QUE SEAN NECESARIOS

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*------------------------------------------------------------------*/
/*Ejercicio 3: Listas
  -nEle1, nEle2: El número de elementos de los vectores C1 y C2 respectivamente
  -C1 y C2: Vectores con los alumnos presentados en primera y segunda convocatoria. Ya se han reservado y rellenado en el main.
  -LP: Lista de alumnos presentados a alguna de las convocatorias.
  -VALOR DEVUELTO: La función devolverá el número de alumnos de la lista LP.

/*------------------------------------------------------------------*/

int ejercicio3(int nEle1, int nEle2, struct datos* C1, struct datos* C2, struct lista ** LP)
{
  //INCLUYE AQUI EL CODIGO NECESARIO PARA RESOLVER EL EJERCICIO
  
  int cont = 0;

  for (int i = 0; i < nEle1; i++){
  
    insertarDetras(LP, C1[i]);
    cont++;
  }

  for(int j = 0; j < nEle2; j++){

    if(encontrado(*LP, C2[j]) == 0){

      insertarDetras(LP, C2[j]);
      cont++;
    }
  }

  return cont;
}

//ESCRIBE AQUÍ TU FUNCION RECURSIVA Y TODAS LAS FUNCIONES QUE CONSIDERES NECESARIAS

int encontrado(struct lista * LS, struct datos dato){

  struct lista * aux = LS;

  int found = 0;

  while(aux != NULL){

    if(dato.codigo == aux -> codigo){

      found = 1;
      return found;
    }

    aux = aux -> sig;
  }

  return 0;
}

void insertarDetras(struct lista ** LS, struct datos dato){

  struct lista * nuevo = nuevoElemento();

  nuevo -> codigo = dato.codigo;
  
  strcpy(dato.nombre, nuevo -> nombre);

  if((*LS) == NULL){

    (*LS) = nuevo;
  }else{

    struct lista * aux = (*LS);

    while(aux -> sig != NULL){

      aux = aux -> sig;
    }

    aux -> sig = nuevo;
  }
}

struct lista * nuevoElemento(){

  struct lista * nuevo = NULL;

  nuevo = (struct lista *)malloc(sizeof(struct lista));

  if(nuevo == NULL){

    printf("Error al añadir un nuevo elemento. \n");
    exit(-1);
  }

  return nuevo;
}