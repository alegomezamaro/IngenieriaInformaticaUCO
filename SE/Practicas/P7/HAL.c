/******************************************************************************/
/* HAL.C: funciones generales que acceden al hardware.                   	    */
/* Capa de abstraccción del hardware (Hardware Abstract Layer)                */
/* Sistemas Empotrados Universidad de Cordoba                                 */
/******************************************************************************/

 #include <LPC23xx.H>                    /* LPC23xx definitions               */
 #include "Practica7.h"
 /* Import external IRQ handlers from IRQ.c file                              */
 extern __irq void T0_IRQHandler (void);
 extern void init_serial (void);
/******************************************************************************/
/* pinesSignalInit                                                            */
/******************************************************************************/
/* Esta funcion configura el pin P4.24 y P4.25 como salida 		                */ 
/******************************************************************************/
void pinesSignalInit(void)
{
  PINSEL9 = 0x00000000; 
  PINMODE9 = 0x000000000;
  FIO4DIR3  = 0x03; //00000001b
}
/******************************************************************************/
/* timer0Init                                                                 */
/******************************************************************************/
/* Esta funcion configura el timer 0 con los parámetros que no cambian 				*/ 
/* durante la aplicacion                                                      */
/******************************************************************************/
void timer0Init(void)
{
	T0PR  = 0x00;															 /* activa el preescalador a cero */
	// cntrolador de interrupciones vectorizadas
	VICVectAddr4 = (unsigned long) T0_IRQHandler;     /* Set Interrupt Vector   */
	VICVectCntl4 = 15;                      /* use it for Timer0 Interrupt      */
	VICIntEnable = (1 << 4);                  /* Enable Timer 0 Interrupt       */
}

/******************************************************************************/
/* hardwareInit                                                               */
/******************************************************************************/
/* Esta funcion se llama al comienzo del programa para inicializar el Hardware*/ 
/******************************************************************************/
void hardwareInit(void)
{
	pinesSignalInit(); 	// Configura los pines del circuito
	timer0Init();				// Inicializa el timer 0
	init_serial();
	
}
