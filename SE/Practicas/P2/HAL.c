/******************************************************************************/
/* HAL.C: funciones generales que acceden al hardware.                   	    */
/* Capa de abstraccción del hardware (Hardware Abstract Layer)                */
/* Sistemas Empotrados Universidad de Cordoba                                 */
/******************************************************************************/
 #include <LPC23xx.H>                    /* LPC23xx definitions               */
/******************************************************************************/
/* pinesSignalInit                                                            */
/******************************************************************************/
/* Esta funcion configura el pin P4.24 como salida						                */ 
/******************************************************************************/
void pinesSignalInit(void)
{
  PINSEL9 = 0x00000000;
  PINMODE9 = 0x000000000;
  FIO4DIR3  = 0x01;
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
}
