/******************************************************************************/
/* Practica2.h: definiciones para las practicas y algunas funciones 	*/
/* Sistemas Empotrados Universidad de Cordoba                                 */
/******************************************************************************/

#define PULSO0_LOW	5  											// duracion del pulso a nivel bajo
#define PULSO0_HIGH	7												// duracion del pulso a nivel alto
#define	SIGNAL0_PIN_HIGH 	FIO4SET3 = 0x01;	// Pin señal 0 a alto 	P4.24
#define	SIGNAL0_PIN_LOW   FIO4CLR3 = 0x01;	// Pin señal 0 a bajo		P4.24	 
#include <LPC23xx.H>
/******************************************************************************/
/* delayT0Unlocked                                                            */
/******************************************************************************/
/* Esta funcion arranca el timer 0 y programa el registro match0              */ 
/******************************************************************************/
void delayT0Unlocked(unsigned int delayInDecimaMiliseg)
{
 	T0TCR = 0x02;		/* reset timer */
	T0MR0 = delayInDecimaMiliseg * 12000000 / 10000;
	T0MCR = 0x07;		/* timer on match */
	T0TCR = 0x01;		/* inicia timer y para cuando se llegue al final de cuenta*/
}
