/******************************************************************************/
/* HAL.C: funciones generales que acceden al hardware.                   	    */
/* Capa de abstraccción del hardware (Hardware Abstract Layer)                */
/* Sistemas Empotrados Universidad de Cordoba                                 */
/******************************************************************************/
extern __irq void T0_IRQHandler (void);
extern __irq void T1_IRQHandler (void);

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
	VICVectAddr4 = (unsigned long) T0_IRQHandler;     /* Set Interrupt Vector  */
	VICVectCntl4 = 15;                      /* use it for Timer0 Interrupt     */
	VICIntEnable = (1 << 4);                  /* Enable Timer 0 Interrupt       */
}

/******************************************************************************/
/* timer1Init                                                                 */
/******************************************************************************/
/* Esta funcion configura el timer 1 con los parámetros que no cambian 				*/ 
/* durante la aplicacion                                                      */
/******************************************************************************/
void timer1Init(void)
{
	PCONP |= (0<<2);									 /* Habilito Time 1, power y reloj */
	T1PR = 0x00; 												 /* activa el preescalador a cero */
	VICVectAddr5 = (unsigned long) T1_IRQHandler;     /* Set Interrupt Vector  */
	VICVectCntl5 = 15;                      /* use it for Timer0 Interrupt     */
	VICIntEnable = (1 << 5);                  /* Enable Timer 0 Interrupt       */
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
	timer1Init();				// Inicializa el timer 1
	
}
