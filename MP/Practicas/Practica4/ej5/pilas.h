#ifndef _PILAS_H_
#define _PILAS_H_

/*! 
    \file pilas.h
    \brief Fichero de cabecera de la biblioteca pilas.a
    \note Metodología de la Programación
    \note Práctica 4
    \note Curso académico 2014-2015
*/

/*! Definición de la estructura nodo */
struct nodo {
   int numero;           /*!< Campo que almacena un numero */
   struct nodo * sig;	 /*!< Dirección del siguiente elemento */
};

/*!
    \fn void push (struct nodo ** cima, int num);
    \brief Introduce un elemento en la cima de la pila
    \param cima Puntero pasado por referencia a la cima de la pila
    \param num  Número entero que se va a insertar en la pila
    \sa    nuevoElemento()
 */
void push (struct nodo ** cima, int num);


/*!
 \fn  int pop(struct nodo ** cima);
 \brief Extrae el elemento situado en la cima de la pila
 \param cima Puntero pasado por referencia a la cima de la pila
 \pre   La pila no debe estar vacía, es decir, debe contener al menos un elemento.
 \post  La cima de la pila ha sido extraída
 \return Número entero situado en la cima de la pila
 */
int pop(struct nodo ** cima);

/*!
 \fn  int pilaVacia(struct nodo * cima);
 \brief Comprueba si la pula está vacía
 \param cima Puntero a la cima de la pila
 \return 1, si la pila está vacía; 0, en caso contrario.
 */
int pilaVacia(struct nodo * cima);



/*!
 \fn struct nodo * nuevoElementoPila();
 \brief   Reserva memoria para un nuevo elemento de tipo nodo
 \return  Dirección de inicio de la memoria reservada
 */
struct nodo * nuevoElementoPila();


#endif

