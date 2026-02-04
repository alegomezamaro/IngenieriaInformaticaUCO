/******************************************************************************/
/* Practica 8: Conversor Analógico-Digital                       							*/
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
#include "Practica8.h"
#include "misTipos.h"

extern void hardwareInit(void);
extern void init_serial(void);
extern void delayT0Unlocked(unsigned int);

int main (void) {
	UINT32 AD_Value;
	AD_Value=0;
	hardwareInit();
	init_serial();
	
	while(1){
		AD0CR |=(1 << 24);
		AD_Value=AD0DR0;
		delayT0Unlocked(10000);
		while(!(T0IR & 0x00000001));
		T0IR=1;
		while((AD_Value& 0x80000000)!=0x80000000)(AD_Value=AD0DR0);
		AD_Value=(AD0DR0 >> 6) & 0x3FF;
		printf("Valor de la conversion = 0x%03x\n\r", AD_Value);
	}
}
