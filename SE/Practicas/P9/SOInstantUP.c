/***************************************************************************************************/
/* Sistema Operativo cíclico Instant-UP                                                            */
/* Sistemas Empotrados. Universidad de Córdoba                                                     */
/***************************************************************************************************/
#include <LPC23xx.H>
#include "misTipos.h"
#include <stdio.h>
/***************************************************************************************************/
/* Definición de timers software asociado a las tareas                                             */
/***************************************************************************************************/
typedef struct
	{
	UINT32 (* pTareas)();  	                        /* Codigo asociado a la tarea                    */
	UINT32 Delay;		                                /* Cuenta actual del temporizador                */
	UINT32 Period;		                              /* Periodo de ejecución de la tarea              */
	UINT32 RunMe;		                                /* Estado de la tarea: lista para ejecutarse     */
	} TAREA;

#define SOMAX_TAREAS 10                           /* Definicion del array de timers/tareas         */

TAREA SOTareas[SOMAX_TAREAS];                     /* definiciontipo                                */

/***************************************************************************************************/
/* Interrupción de tiempo real y actualización de los temporizadores asociados a las tareas        */
/* Se debe asociar un timer hardware al Sistema operativo para que genere la interrupción de       */
/* tiempo real. En este caso el timer 1                                                            */
/***************************************************************************************************/
__irq void T1Manejador_IRQ (void) 
{	 
	UINT32 Indice;	                        /* NOTA: Los cálculos son en *TICKS* (no en milisegundos)*/
	for (Indice = 0; Indice < SOMAX_TAREAS; Indice++)
	{			
		if (SOTareas[Indice].pTareas)	                /* Chequeo si hay tareas en esa posición         */
		{
			if (SOTareas[Indice].Delay == 0)            /* La tarea esta lista para ser ejecutada        */
			{
				SOTareas[Indice].RunMe += 1;              /* Incremento la bandera 'RunMe'                 */
				if (SOTareas[Indice].Period)
				{
          /* Organizo tarea periodica para ser ejecutada nuevamente cuando corresponda             */
					SOTareas[Indice].Delay = SOTareas[Indice].Period;
				}
			}
			else
			{
				/* Tarea aun no lista para ser ejecutada: Solo decremento el Delay                         */
 				SOTareas[Indice].Delay -= 1;
			}
		}
	}
	T1IR        = 1;                                /* Limpio bandera de interrupcion                */              
	VICVectAddr = (unsigned int)0x0;                /* Reconocimiento de interrupcion                */
}	
/***************************************************************************************************/
/* Funciones del Sistema Operativo. Creación de una tarea                                          */
/***************************************************************************************************/
unsigned int SOAgrego_Tarea(unsigned int (* pFuncion)(),const unsigned int DELAY,const unsigned int PERIOD)
{
	UINT32 Indice = 0;
	/* Rastrea si hay tareas en la lista                                                             */
	while ((SOTareas[Indice].pTareas!= 0) && (Indice < SOMAX_TAREAS))
	{									   
		Indice++;						  
	}
	/* ¿Encontró el final de la lista?                                                               */
	if (Indice == SOMAX_TAREAS)
	{
		printf("Error"); 
	}
	SOTareas[Indice].pTareas = pFuncion;
	SOTareas[Indice].Delay   = DELAY;
	SOTareas[Indice].Period  = PERIOD;
	SOTareas[Indice].RunMe   = 0;
	/* Retorna la posicion de la tarea, para permitir luego su ubicacion. Actúa como task ID         */
	return Indice;
}
/***************************************************************************************************/
/* Eliminación de una tarea																											                   */
/***************************************************************************************************/
void SOEliminaTarea (UINT32 i)	
{ 
	SOTareas[i].pTareas= 0;
	SOTareas[i].Delay = 0;
	SOTareas[i].Period =0;
	SOTareas[i].RunMe = 0; 
}
/***************************************************************************************************/
/* Planificador/despachador de tareas																						                   */
/***************************************************************************************************/
void  SODespachador_Tareas(void)
{
	unsigned int Indice;
	/* El despachador ejecuta la proxima tarea si es que hay una                                     */
	for (Indice = 0; Indice < SOMAX_TAREAS; Indice++)
	{
		if (SOTareas[Indice].RunMe > 0)
			{
				(*SOTareas[Indice].pTareas)();            /* Ejecuta la tarea                              */
				SOTareas[Indice].RunMe -= 1;              /* Bajo la bandera RunMe                         */
                  /* Si la tarea no es periodica, se ejecuta solo una vez y se elimina de la lista */
				if (SOTareas[Indice].Period == 0)
					{
	 					SOEliminaTarea(Indice);
					}
			}
	}
}
/*Hay que inializar el SO antes de utilizarlo                                                      */
void SO_Inicio_TCB_Var(void)
{
	unsigned int i;
	for (i = 0; i < SOMAX_TAREAS; i++) SOEliminaTarea(i);
}
/*Hay que inicializar el timer hardware y activar las interrupciones                               */
 void startT1()                   /* Habilita y setea el Temporizador 1 y su Interrupcion asociada */
{
  PCONP |= (0 << 2);											        /* Habilito Timer 1                              */
  T1MR0  = 11999;                                 /* 1 mseg = 12000-1 at 12.0 MHz                  */
  T1MCR  = 3;                                     /* Interrupt and Reset on MR0                    */
  T1TCR  = 1;                                     /* Timer1 Enable                                 */
}
  void ActVIC_T1()
{
  VICVectAddr5  = (unsigned long)T1Manejador_IRQ; /* Coloca al vector interrupcion, para el Timer1 */    
  VICVectCntl5  = 14;                             /* Asigna nivel de prioridad                     */ 
}    
/*Arranca el SO                                                                                    */
void SOStart(void)
{
VICIntEnable  = (1  << 5);                        /* Habilita interrupcion Timer 1                 */
}
