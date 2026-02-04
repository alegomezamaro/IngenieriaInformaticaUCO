/******************************************************************************/
/* Practica5.h: definiciones para las practicas y algunas funciones 	        */
/* Sistemas Empotrados Universidad de Cordoba                                 */
/******************************************************************************/
#include <LPC23xx.H>		 /* LPC23xx definitions */
#include "Practica8h"
#include "misTipos.h"
 
extern UINT32 timersw0;
extern UINT32 timersw1;
extern BOOL signal0High;
extern BOOL signal1High;
extern void delayT0Unlocked(unsigned int delayInDecinalMilideg);
/******************************************************************************/
/* Timer 0 IRQ                                                                */
/******************************************************************************/
 __irq void T0_IRQHandler (void){
	 timersw0--;
	 timersw1--;
	 if(timersw0==0){ 
			if(signal0High==TRUE){
				SIGNAL0_PIN_LOW;
				signal0High=FALSE;
				timersw0=SIGNAL0_LOWTIME;
			}
			else{				
				SIGNAL0_PIN_HIGH;
				signal0High=TRUE;
				timersw0=SIGNAL0_HIGHTIME;
			}
	}
	 if(timersw1==0){
		 if(signal1High==TRUE){
			 SIGNAL1_PIN_LOW;
			 signal1High=FALSE;
			 timersw1=SIGNAL1_LOWTIME;
		 }
		 else{
			 SIGNAL1_PIN_HIGH;
			 signal1High=TRUE;
			 timersw1=SIGNAL1_HIGHTIME;
		 }
		}
	  T0IR 	= 1;
		VICVectAddr = 0;
		delayT0Unlocked(1);
		
	}
