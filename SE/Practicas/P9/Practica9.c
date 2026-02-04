/******************************************************************************/
/* Practica 9: Aplicación utilizando el sistema operativo Instan-up           */
/******************************************************************************/
/* Aquí se debe hacer una pequeña descripción de los objetivos de la práctica */
/* Apellidos y nombre del alumno/s:																						*/
/* Alba Rueda, Lucía                                                          */
/* Gomez Amaro, Alejandro                                                     */
/******************************************************************************/
/* Sistemas Empotrados. 3º de Graduado en Ingenieria Informática						  */
/* Universidad de Córdoba									      															*/
/******************************************************************************/
#include <stdio.h>
#include <LPC23xx.H>		 /* LPC23xx definitions */
#include "Practica9.h"
#include "misTipos.h"
UINT32 image_pin24;

extern void hardwareInit(void);
extern void SO_Inicio_TCB_Var(void);
extern void startT1(void);
extern void ActVIC_T1(void);
extern void SOStart(void);
extern void SODespachador_Tareas(void);
extern unsigned int SOAgrego_Tarea(int (*)(void),const unsigned int, const unsigned int);

int MyTask(void){
	if(image_pin24==0){
		PIN_P4_24_HIGH;
		image_pin24=1;
	}
	else{
		PIN_P4_24_LOW;
		image_pin24=0;
	}
	return 0;
}

int main(void){
	PIN_P4_24_LOW;
	image_pin24=0;												/* Inicializo la variable 																*/
	hardwareInit();												/* Inicializo recursos Hardware														*/
	SO_Inicio_TCB_Var();									/* Llamo a la función que inicializa las variables del SO */
	startT1();														/* Inicializo el timer asociado al sistema operativo, T1  */
	ActVIC_T1();													/* Coloca los valores en el VIC para el T1                */
	SOStart();														/* Arranca el sistema operativo 													*/
	SOAgrego_Tarea(MyTask,100,100);				/* Se definen las tareas al sistema operativo 						*/
	while(1){															/* Llamada continua al planificador / despachador 				*/
		SODespachador_Tareas();
	}
	
}
