/******************************************************************************/
/* Practica5.h: definiciones para las practicas y algunas funciones 	        */
/* Sistemas Empotrados Universidad de Cordoba                                 */
/******************************************************************************/
#include <LPC23xx.H>		 /* LPC23xx definitions */
#include "Practica7.h"
#include "misTipos.h"
 
extern UINT32 timersw0, timersw0InitialCount;
extern UINT32 timersw1, timersw1InitialCount;
extern BOOL signal0High;
extern BOOL signal1High;
/******************************************************************************/
/* Timer 0 IRQ                                                                */
/******************************************************************************/
 __irq void T0_IRQHandler (void){
	 timersw0--;
	 timersw1--;
	 if(timersw0==0){ 
		 timersw0=timersw0InitialCount;
			if(signal0High==TRUE){
				SIGNAL0_PIN_LOW;
				signal0High=FALSE;
			}
			else{				
				SIGNAL0_PIN_HIGH;
				signal0High=TRUE;
			}
	}
	 if(timersw1==0){
		 timersw1=timersw1InitialCount;
		 if(signal1High==TRUE){
			 SIGNAL1_PIN_LOW;
			 signal1High=FALSE;
		 }
		 else{
			 SIGNAL1_PIN_HIGH;
			 signal1High=TRUE;
		 }
		}
	  T0IR 	= 1;
		VICVectAddr = 0;
		
	}
