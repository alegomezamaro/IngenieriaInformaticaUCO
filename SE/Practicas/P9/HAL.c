/******************************************************************************/
/* HAL.C: funciones generales que acceden al hardware.                   	    */
/* Capa de abstraccción del hardware (Hardware Abstract Layer)                */
/* Sistemas Empotrados Universidad de Cordoba                                 */
/******************************************************************************/

 #include <LPC23xx.H>                    /* LPC23xx definitions               */
 #include "Practica9.h"

/******************************************************************************/
/* pinesSignalInit                                                            */
/******************************************************************************/
/* Esta funcion configura el pin P4.24 										 		                */ 
/******************************************************************************/
void pinesSignalInit(void)
{
  PINSEL9 = 0x00000000; 
  PINMODE9 = 0x000000000;
  FIO4DIR3  = 0x03;
}
/******************************************************************************/
/* hardwareInit                                                               */
/******************************************************************************/
/* Esta funcion se llama al comienzo del programa para inicializar el Hardware*/ 
/******************************************************************************/
void hardwareInit(void)
{
	pinesSignalInit(); 	// Configura los pines del circuito
}
