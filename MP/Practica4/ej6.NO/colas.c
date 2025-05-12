/*! 
    \file colas.c
    \brief Fichero de código de las funciones de manejo de colas
    \note Metodología de la Programación
    \note Práctica 4
    \note Curso académico 2014-2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "colas.h"


void insertaCola(struct nodo ** cola, struct trabajo elemento){
   struct nodo * nuevo;
   struct nodo * aux;

   /* Se reserva memoria para un nuevo elemento para la cola */
   nuevo=nuevoElementoCola();

   /* Se actualizan los datos del nodo */
   nuevo -> elemento=elemento;
   nuevo->sig=NULL;

   /* Se comrpueba si la cola está vacía */
/*   if (*cola==NULL){ */
   if (colaVacia(*cola) == 1){
      *cola=nuevo;
   }
   /* En caso contrario */
   else {
      aux=*cola;
      while (aux->sig!=NULL){
         aux=aux->sig;
      }
      aux->sig=nuevo;
   }
}


struct trabajo sacaCola(struct nodo ** cola ){
   struct nodo * aux;
   struct trabajo n;

   /* Se accede a la cabeza de la cola */
   aux=*cola;

   /* La cabeza de la cola pasa al siguiente elemento */
   *cola=aux->sig;
 
  /* Se copia la información del nodo que estaba en la cabeza de la cola */
   n=aux->elemento;
  
   /* Se libera la memoria del nodo */
   free(aux);

   /* Se devuelve la información del nodo que estaba en la cabeza de la cola */
   return n;     
}


int colaVacia(struct nodo * cola){

   /* Si la cola está vacía */
   if (cola==NULL){
      return 1;
   }
   /* En caso contrario */
   else {
      return 0;
   }
}


struct nodo * nuevoElementoCola()
{
   struct nodo *nuevo;

   /* Se reserva la memoria para un nuevo nodo */
   nuevo = (struct nodo *) malloc(sizeof(struct nodo));

   if (nuevo == NULL) {
      printf("Error al reservar memoria para el nodo\n");
      exit(-1);
   }

   /* Se devuelve el nodo reservado */
   return nuevo;
}

