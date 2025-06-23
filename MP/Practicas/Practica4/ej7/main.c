/*! 
    \file main.c
    \brief  Programa principal que permite resolver un crucigrama
    \note Metodología de la Programación
    \note Práctica 4
    \note Curso académico 2014-2015
*/

#include <stdio.h>
#include "ficheros.h"
#include "memoria.h"
#include "crucigrama.h"

/*
Pilas de contenedores
- Descripción
  - Para mover los contenedores de mercancía de un importante puerto comercial, se
  utiliza un método de almacenamiento basado en el concepto de pila.
    - De este modo, el contenedor situado más abajo en la pila fue el primero que se
    apiló, y, para moverlo, es necesario mover a otra pila todos los contenedores que
    hay encima de él.
  - Cada contenedor de mercancía está identificado por un código entero, X.
  - Por motivos de seguridad, como mucho se pueden apilar N contenedores en una
  misma pila.
    - De este modo, si la pila no está llena, entonces se puede apilar un nuevo
    contenedor.
  - Si se desea sacar un contenedor de código X entonces:
    - Se deben desapilar previamente los contenedores encima de él colocándolos en
    una nueva pila auxiliar.
    - Se extrae el contenedor X y se vuelven a introducir los contenedores extraídos
    previamente.
Objetivo
  - Codifica un programa que, utilizando las funciones push (apilar), pop (desapilar), y
  vacia que están implementadas en la biblioteca pilas.a, permita gestionar una pila de
  contenedores con la siguiente funcionalidad:
    - Crear una pila de N contenedores.
    - Listar los contenedores que hay en pila.
      - Se muestra por pantalla un listado de los contenedores contenidos en la pila.
    - Conocer si un contenedor de código X está en la pila.
    - Sacar el contenedor de código X que puede estar en cualquier posición de la pila.
NOTA: no se podrá recorrer en ningún caso la pila secuencialmente como si fuera una
lista, sino que solo se hará uso de una pila auxiliar y de las funciones vacia, push y pop.
*/


/*!
 \fn int main()
 \brief Programa principal
 */
int main(){

  /* Comprueba si existe el fichero */
   existeFichero();

   /* Carga el fichero */
   cargaFicheroBinario();

   /* Reserva memoria para el crucigrama */
   reservaCrucigrama();

   /* Crea el crucigrama */
   creaCrucigrama();

   /* Imprime el crucigrama */
   imprimeCrucigrama(); 

   /* Se librera la memoria */
   liberaCrucigrama();  
      
   return 0;
}   

