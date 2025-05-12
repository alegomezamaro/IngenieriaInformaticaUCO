/*! 
    \file pilas.c
    \brief Fichero de código de las funciones de manejo de pilas
    \note Metodología de la Programación
    \note Práctica 4
    \note Curso académico 2014-2015
*/
#include <stdio.h>
#include <stdlib.h>
#include "pilas.h"

void push (struct nodo ** cima, int num) {

   struct nodo * nuevo;
    
   /* Se reserva memoria para el nuevo nodo */
   nuevo=nuevoElementoPila();
    
   /* Se actualizan los campos del nodo */
   nuevo->numero=num;
   nuevo->sig=*cima;
    
   /* Se indica que el nodo es la nueva cima de la pila */
   *cima=nuevo;
}


int pop(struct nodo ** cima){
   int numero;
   struct nodo * aux;
    
   /* Se accede al nodo situado en la cima de la pila */
   aux=(*cima);
    
   /* Se copia el valor del campo numero del nodo de la cima de la pila */
   numero=(*cima)->numero;
    
   /* Se desapila la cima de la pila */
   *cima=(*cima)->sig;
    
   /* Se libera la memoria del nodo que estaba en la cima de la pila */
   free(aux);
    
   /* Se devuelve el número que estaba en la cima de la pila */
   return numero;
}



int pilaVacia(struct nodo * cima){
    
   /* Se comprueba si la pila está vacía */
   if (cima==NULL)
      return 1;
   /* En caso contrario */
   else
      return 0;
}

struct nodo * nuevoElementoPila()
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



