/**********************************************************************/
/* Practica 1: Hola mundo																							*/
/**********************************************************************/
/* Apellidos y nombre del alumno: Alejandro Gómez Amaro								*/
/**********************************************************************/
/* Sistemas Empotrados. 3º de Graduado en Ingeniería Informática			*/
/* Universidad de Cordoba																							*/
/**********************************************************************/
#include <stdio.h>
#include <LPC23xx.h>
extern void init_serial (void);

int main (void){
		init_serial ();
		printf("Hola mundo");
		while (1);
}
