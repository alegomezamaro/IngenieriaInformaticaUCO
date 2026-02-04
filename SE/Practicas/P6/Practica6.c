//
/* Practica 6: Timers sofrware con VIC                          							*/
//
/* Aquí se debe hacer una pequeña descripción de los objetivos de la práctica */
/* Apellidos y nombre del alumno/s:																						*/
/* Alba Rueda, Lucía                                                          */
/* Gomez Amaro, Alejandro                                                     */
//
/* Sistemas Empotrados. 3º de Graduado en Ingenieria Informática						  */
/* Universidad de Córdoba									      															*/
//
#include <stdio.h>
#include <LPC23xx.H>		 /* LPC23xx definitions */
#include "misTipos.h"

extern void hardwareInit(void);
extern int getkey(void);

int main(void){
	UINT32 charTmp;
	UINT32 primerDigito, segundoDigito, resultado;
	//inicializacion hardware
	hardwareInit();
	while(1){
		printf("\n Este programa multiplica dos digitos BCD \n");
		//primer digito. Sólo son validos los caracteres de 0 a 9
		printf("Introduzca el primer digito:");
		do{
			charTmp=getkey();
			if((charTmp<0x3A) & (charTmp>=0x30)) printf("%c", (char) charTmp); //Eco
		} while(!((charTmp<0x3A) & (charTmp>=0x30)));
		primerDigito=(charTmp-0x30);
		//segundo digito. Solo son validos los caracteres de 0 a 9
		printf("\nIntroduzca el segundo digito:");
		do{
			charTmp=getkey();
			if((charTmp<0x3A) & (charTmp>=0x30)) printf("%c", (char) charTmp); //Eco
		} while(!((charTmp<0x3A) & (charTmp>=0x30)));
		segundoDigito=(charTmp-0x30);
		//Resultado
		resultado=primerDigito*segundoDigito;
		printf("\nResultado: %d", resultado);
		printf("\nPulse una tecla para multiplicar de nuevo");
		(void)getkey();
		printf("\n \n");
	}
}
