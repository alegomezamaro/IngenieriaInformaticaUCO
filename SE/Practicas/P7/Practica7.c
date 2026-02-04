/******************************************************************************/
/* Practica 7: Utilizando el puerto serie como interfaz de usuario            */
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
#include "Practica7.h"
#include "misTipos.h"
#define SEMIPERIODO_INICIAL 5

/* Variables globales */
UINT32 timersw0, timersw0InitialCount;
UINT32 timersw1, timersw1InitialCount;

BOOL signal0High;
BOOL signal1High;

// extern unsigned int key
extern void hardwareInit(void);
extern int getkey(void);

/******************************************************************************/
/* continousTimerT0                                                           */
/******************************************************************************/
/* Esta funcion arranca el timer 0 y programa el registro match0              */ 
/* El timer se programa para que no se detenga                                */
/* Esta función genera una temporización continua                             */
/******************************************************************************/
void continousTimerT0(unsigned int timerInDecimaMiliseg){	
 	T0TCR = 0x02;		/* reset timer */
	T0MR0 = timerInDecimaMiliseg * (12000000 / 10000-1);
	T0MCR = 0x03;		/* timer on match */
	T0TCR = 0x01;		/* inicia timer y para cuando se llegue al final de cuenta*/
}


UINT32 menuTimer(UINT32* timer, UINT32* semiperiodo){
	UINT32 charTmp;
	printf("Señal-Timer 0 o 1: \n");
	do{
		charTmp=getkey();
		if(charTmp == ESC) return charTmp;
		if((charTmp<0x32) && (charTmp>=0x30)) printf("%c\n", (char) charTmp); //Eco		
	}while (!((charTmp<0x32) & (charTmp>=0x30)));
	* timer = (charTmp-0x30); //ya tengo el timer
	printf("Indique el semiperiodo utilizando dos digitos 01 a 99: \n");
	do{
		charTmp=getkey();
		if(charTmp == ESC) return charTmp;
		if((charTmp<0x3A) && (charTmp>=0x30)) printf("%c\n", (char) charTmp); //Eco		
	}while (!((charTmp<0x3A) & (charTmp>=0x30)));
	* semiperiodo = (charTmp-0x30)*10; //hemos obtenido la decena del periodo
	do{
		charTmp=getkey();
		if(charTmp == ESC) return charTmp;
		if((charTmp<0x3A) && (charTmp>=0x30)) printf("%c\n", (char) charTmp); //Eco		
	}while (!((charTmp<0x3A) & (charTmp>=0x30))); //obtengo la unidad
	*semiperiodo = *semiperiodo+(charTmp-0x30); //obtengo el semiperiodo
	return OK;
}


int main(void){
	UINT32 timer, semiperiodo;
	// inicialización variables globales
	signal0High=TRUE;
	signal1High=TRUE;
	// inicialización hardware
	hardwareInit();
	SIGNAL0_PIN_HIGH;
	SIGNAL1_PIN_HIGH;
	//inicialización timers
	
	timersw0InitialCount=SEMIPERIODO_INICIAL;
	timersw0=SEMIPERIODO_INICIAL;
	printf("Señal 0 Timer 0 periodo= %d milisegundos \n", semiperiodo*2);
	
	timersw1InitialCount=SEMIPERIODO_INICIAL;
	timersw1=SEMIPERIODO_INICIAL;
	printf("Señal 1 Timer 1 periodo= %d milisegundos \n", semiperiodo*2);
	
	continousTimerT0(10); //Temporizo una décima de milisegundo
	
	while(1){
		printf("Pulse una tEcla para cambiar el semiperiodo de las señales\n");
		(void)getkey();
		if(OK==menuTimer(&timer,&semiperiodo)){
			switch(timer){
				case 0:
						timersw0InitialCount=semiperiodo;
					  printf("Señal 0 Timer 0 periodo= %d milisegundos \n", semiperiodo*2);
						break;
				case 1:	
					  timersw1InitialCount=semiperiodo;
					  printf("Señal 1 Timer 1 periodo= %d milisegundos \n", semiperiodo*2);
			}
		}		
	}
}
