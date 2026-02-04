/******************************************************************************/
/* HAL.C: funciones generales que acceden al hardware.                   	    */
/* Capa de abstraccción del hardware (Hardware Abstract Layer)                */
/* Sistemas Empotrados Universidad de Cordoba                                 */
/******************************************************************************/
extern int init_serial(void);

void hardwareInit(void)
{
	init_serial();
	
}
