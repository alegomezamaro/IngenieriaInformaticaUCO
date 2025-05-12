#ifndef _COLAS_H_
#define _COLAS_H_

/*! 
    \file colas.h
    \brief Fichero de cabecera de la biblioteca colas.a
    \note Metodología de la Programación
    \note Práctica 4
    \note Curso académico 2014-2015
*/


/*! Definición de la estructura trabajo */
struct trabajo{
   int login;		/*!< Campo que almacena el login de un usuario */
   char nombre[25]; 	/*!< Campo que almacena el nombre del fichero */
};

/*! Definición de la estructura nodo */
struct nodo {
   struct trabajo elemento;  	/*!< Campo que almacena un elemento */
   struct nodo * sig;		/*!< Dirección del siguiente elemento */
};

/*!
    \fn void insertaCola(struct nodo ** cola, struct trabajo elemento);
    \brief Introduce un elemento al final de la cola
    \param cola Puntero pasado por referencia al principio de la cola 
    \param elemento  Estructura de tipo trabajo que se va a insertar en la cola
 */
void insertaCola(struct nodo ** cola, struct trabajo elemento);

/*!
 \fn  struct trabajo sacaCola(struct nodo ** cola );
 \brief Extrae el elemento situado en al principio de la cola
 \param cola Puntero pasado por referencia al principio de la cola
 \pre   La cola no debe estar vacía, es decir, debe contener al menos un elemento.
 \post  La cabeza de la cola ha sido extraída
 \return Estructura de tipo trabajo que representa la cabeza de la cola
 */
struct trabajo sacaCola(struct nodo ** cola );

/*!
 \fn int colaVacia(struct nodo * cola);
 \brief Comprueba si la cola está vacía
 \param cola Puntero a la cima de la cola
 \return 1, si la cola está vacía; 0, en caso contrario.
 */
int colaVacia(struct nodo * cola);


/*!
 \fn    struct nodo * nuevoElementoCola ();
 \brief   Reserva memoria para un nuevo elemento de tipo nodo
 \return  Dirección de inicio de la memoria reservada
 */
struct nodo * nuevoElementoCola ();

#endif /* _COLAS_H_ */




