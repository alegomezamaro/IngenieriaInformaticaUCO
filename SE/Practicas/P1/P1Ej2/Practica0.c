/************************************************************/
/* MICROCONTROLADORES.																			*/
/* 3º de Graduado en Ingeniería Electrónica Industrial.			*/
/* Universidad de Córdoba.																	*/
/************************************************************/
/* Práctica 0: Introdución a la herramienta Keil uVision 5	*/
/* Nombre y apellidos:																			*/
/* Fecha: 11 de marzo de 2024																*/
/************************************************************/
#include <LPC23xx.H>

#define INT_TMR0	4

void T0ISR() __irq {
	T0IR = 0x01;

	if(FIO2PIN & 0x01){
		FIO2CLR |= 0x1;
	} else
		FIO2SET |= 0x01;

	VICVectAddr = 0;
}

static void InitTimer(void){
	T0TCR = 0x02;
	T0MR0 = 0x1000;
	T0MCR = 0x03;
	
	VICVectAddr4 = (unsigned long)T0ISR;
	VICVectPriority4 = 0;
	VICIntEnable = 1 << INT_TMR0;

	T0TCR = 0x01;
}

int main (){
	FIO2DIR = 0x01;
	InitTimer();
	while(1);
}
