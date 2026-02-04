/******************************************************************************/
/* Practica4: Controladores de Interrupciones Vectorizadas (VIC).	   					*/
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
#include "Practica4.h"
#include "misTipos.h"

extern void hardwareInit(void);

unsigned int signal0High = FALSE;
unsigned int signal1High = FALSE;

/******************************************************************************/
/* Timer 0 IRQ                                                                */
/******************************************************************************/
 __irq void T0_IRQHandler (void){
	if(signal0High==TRUE){
		signal0High=FALSE;
		SIGNAL0_PIN_LOW;
		delayT0Unlocked(PULSO0_LOW);
	
	 }
	 else{
		 signal0High=TRUE;
		 SIGNAL0_PIN_HIGH;
		 delayT0Unlocked(PULSO0_HIGH);
	 }
	 T0IR = 1;
	 VICVectAddr = 0;
}

/******************************************************************************/
/* Timer 1 IRQ                                                                */
/******************************************************************************/
 __irq void T1_IRQHandler (void) {
	if(signal1High==TRUE){
		signal1High=FALSE;
		SIGNAL1_PIN_LOW;
		delayT1Unlocked(PULSO1_LOW);
	
 }
 else{
	 signal1High=TRUE;
	 SIGNAL1_PIN_HIGH;
	 delayT1Unlocked(PULSO1_HIGH);
 }
 T1IR = 1;
 VICVectAddr = 0;
}




int main (void) {
	
	hardwareInit();
	
	delayT0Unlocked(PULSO0_LOW);
	delayT1Unlocked(PULSO1_LOW);
	
	while(1){}
}
