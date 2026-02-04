/******************************************************************************/
/* Practica5.h: definiciones para las practicas y algunas funciones 	        */
/* Sistemas Empotrados Universidad de Cordoba                                 */
/******************************************************************************/

#define SIGNAL0_LOWTIME	  2 											// duracion del pulso 0 a nivel bajo en décimas de segundo
#define SIGNAL0_HIGHTIME	3												// duracion del pulso 0 a nivel alto en décimas de segundo
#define SIGNAL1_LOWTIME	  5  											// duracion del pulso 1 a nivel bajo en décimas de segundo
#define SIGNAL1_HIGHTIME	7												// duracion del pulso 1 a nivel alto en décimas de segundo

#define	SIGNAL0_PIN_HIGH 	FIO4SET3 = 0x01;	// Pin señal 0 a alto 	P4.24
#define	SIGNAL0_PIN_LOW   FIO4CLR3 = 0x01;	// Pin señal 0 a bajo		P4.24	 
#define	SIGNAL1_PIN_HIGH 	FIO4SET3 = 0x02;	// Pin señal 0 a alto 	P4.25
#define	SIGNAL1_PIN_LOW   FIO4CLR3 = 0x02;	// Pin señal 0 a bajo		P4.25	 
#include <LPC23xx.H>



