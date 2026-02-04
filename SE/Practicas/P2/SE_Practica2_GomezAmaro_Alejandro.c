/******************************************************************************/
/* Practica 2: Manejo de puertos básicos de E/S y Timers (I).									*/
/******************************************************************************/
/* Aquí se debe hacer una pequeña descripción de los objetivos de la práctica */
/* Apellidos y nombre del alumno/s: Gómez Amaro Alejandro 										*/
/******************************************************************************/
/* Sistemas Empotrados. 3º de Graduado en Ingenieria Informática						  */
/* Universidad de Córdoba									      															*/
/******************************************************************************/
#include <stdio.h>
#include <LPC23xx.H>		 /* LPC23xx definitions */
#include "Practica2.h"
#include "misTipos.h"

extern void hardwareInit(void);

int main (void) 
{
	hardwareInit();
	while(1){
		
		SIGNAL0_PIN_LOW;
		delayT0Unlocked(PULSO0_LOW); //Espera
		while(!(T0IR & 0X00000001));
		T0IR = 1;
		SIGNAL0_PIN_HIGH;
		delayT0Unlocked(PULSO0_HIGH);
		while(!(T0IR & 0X00000001));
		T0IR = 1;
	}
}
