/******************************************************************************/
/* HAL.C: Capa de abstraccción del hardware     									            */
/* Sistemas Empotrados Universidad de Cordoba                                 */
/******************************************************************************/

 #include <LPC23xx.H>                    /* LPC23xx definitions               */
 /* Import external IRQ handlers from IRQ.c file                              */
 extern __irq void T0_IRQHandler (void);
/******************************************************************************/
/* ADC_Init                                                            */
/******************************************************************************/
/* Esta funcion configura el conversor analógico/digital 0 del LCP2378        */ 
/******************************************************************************/
void ADC_Init(void)
{
  PCONP |= (1 << 12);
	PINSEL1 |= (1 << 14);
	AD0INTEN = (1 << 0);
	AD0CR = (1 << 0)
					| (3 << 8)
					| (1 << 21);
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
/* delayT0Unlocked                                                            */
/******************************************************************************/
/* Esta funcion arranca el timer 0 y programa el registro match0							*/ 
/******************************************************************************/
void delayT0Unlocked(unsigned int delayInDecimaMiliseg)
{
	T0TCR = 0x02;
	T0MR0 = delayInDecimaMiliseg * 12000000 / 10000;
	T0MCR = 0x07;
	T0TCR = 0x01;
}
/******************************************************************************/
/* hardwareInit                                                               */
/******************************************************************************/
/* Esta funcion se llama al comienzo del programa para inicializar el Hardware*/ 
/******************************************************************************/
void hardwareInit(void)
{
	ADC_Init(); 	// Configura los pines del circuito
	timer0Init();				// Inicializa el timer 0
	
}
