/******************************************************************************/
/* Practica 3: Manejo de GPIO y Timers II.																		*/
/******************************************************************************/
/* Aquí se debe hacer una pequeña descripción de los objetivos de la práctica */
/* Apellidos y nombre del alumno/s: Gómez Amaro Alejandro 										*/
/******************************************************************************/
/* Sistemas Empotrados. 3º de Graduado en Ingenieria Informática						  */
/* Universidad de Córdoba									      															*/
/******************************************************************************/
#include <stdio.h>
#include <LPC23xx.H>		 /* LPC23xx definitions */
#include "Practica3.h"
#include "misTipos.h"

extern void hardwareInit(void);

int main (void){
		
	unsigned int signal0High = FALSE;
	unsigned int signal1High = FALSE;
	hardwareInit();
	delayT0Unlocked(PULSO0_LOW);
	delayT1Unlocked(PULSO1_LOW);

	while(1){
		
		if((T0IR&0x01) == (unsigned int)0x01){
		
			T0IR=0x1;
			if (signal0High==TRUE){
				
				signal0High=FALSE;
				SIGNAL0_PIN_LOW;
				delayT0Unlocked(PULSO0_LOW);
			}
			else{
				
				signal0High=TRUE;
				SIGNAL0_PIN_HIGH;
				delayT0Unlocked(PULSO0_HIGH);
			}
		}

		if((T1IR&0x01) == (unsigned int)0x01){
			
			T1IR=0x1;
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
		}
	}
}
