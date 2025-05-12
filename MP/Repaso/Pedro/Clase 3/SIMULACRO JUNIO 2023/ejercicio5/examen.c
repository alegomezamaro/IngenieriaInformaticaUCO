/*------------------------------------------------------------------*/
/* NOMBRE Y APELLIDOS:    se compila gcc main.c examen.c funciones.o                                          */
/* DNI:                                                             */
/*------------------------------------------------------------------*/
#include "funciones.h"
#include "examen.h"

/*------------------------------------------------------------------*/
//HAZ AQUI LOS INCLUDE QUE CONSIDERES NECESARIOS
/*------------------------------------------------------------------*/


/*------------------------------------------------------------------*/
/*Apartado1:
	nEle: número de elementos del vector. Devuelto POR REFERENCIA, hay que calcular su valor.
	nombreFichAlumnos: Nombre del fichero de alumnos.
	nombreFichNotas: Nombre del fichero de notas.
	VALOR DEVUELTO: Vector de struct alumno que debes reservar y rellenar con los datos de los ficheros.
*/
/*------------------------------------------------------------------*/
struct alumno * apartado1(int * nEle, char * nombreFichAlumnos, char * nombreFichNotas)
{

	FILE * fich = fopen(nombreFichAlumnos, "r");

	if(fich == NULL){

		printf("Error al abrir el fichero. \n");
		exit(-1);
	}

	FILE * fich2 = fopen(nombreFichNotas, "r");

	if(fich2 == NULL){

		printf("Error al abrir el fichero. \n");
		exit(-1);
	}

	struct alumno a;

	while()
  
  //NI DE DEVOLVER POR REFERENCIA EL NUMERO DE ELEMENTOS DEL VECTOR
  return NULL;
}

/*------------------------------------------------------------------*/
/*Apartado2:
	nEle: número de elementos del vector.
	Vector: Vector ya creado y relleno con los datos de alumnos.
	nombreFichResultado: Nombre del fichero resultado.

*/
/*------------------------------------------------------------------*/
void apartado2(int nEle, struct alumno* Vector, char* nombreFichResultado)
{
     //INCLUYE AQUI EL CODIGO NECESARIO PARA RESOLVER EL EJERCICIO

}

/*------------------------------------------------------------------*/
//ESCRIBE AQUI TODAS LAS FUNCIONES QUE CONSIDERES NECESARIAS
/*------------------------------------------------------------------*/
