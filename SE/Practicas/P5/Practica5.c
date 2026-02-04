/******************************************************************************/
/* Practica 5: Timers sofrware con VIC                          							*/
/******************************************************************************/
/* Aquí se debe hacer una pequeña descripción de los objetivos de la práctica */
/* Apellidos y nombre del alumno/s:																						*/
/* Alba Rueda, Lucía                                                          */
/* Gomez Amaro, Alejandro                                                     */
/******************************************************************************/
/* Sistemas Empotrados. 3º de Graduado en Ingenieria Informática						  */
/* Universidad de Córdoba									      															*/
/******************************************************************************/
#include <stdio.h>
#include <LPC23xx.H>		 /* LPC23xx definitions */
#include "Practica5.h"
#include "misTipos.h"

/* Variables globales */
UINT32 timersw0;
UINT32 timersw1;
BOOL signal0High;
BOOL signal1High;

extern void hardwareInit(void);

/******************************************************************************/
/* delayT0Unlocked                                                            */
/******************************************************************************/
/* Esta funcion arranca el timer 0 y programa el registro match0              */ 
/******************************************************************************/
void delayT0Unlocked(unsigned int delayInDecimaMiliseg){
 	T0TCR = 0x02;		/* reset timer */
	T0MR0 = delayInDecimaMiliseg * (12000000 / 10000-1);
	T0MCR = 0x07;		/* timer on match */
	T0TCR = 0x01;		/* inicia timer y para cuando se llegue al final de cuenta*/
}


int main (void) {
	/*Inicializaciones de variables globales*/
	signal0High = TRUE;
	signal1High = TRUE;
	timersw0=SIGNAL0_HIGHTIME;
	timersw1=SIGNAL1_HIGHTIME;
	// Inicizalización hardware
	hardwareInit();
	delayT0Unlocked(1);
	
	while(1){}
}
