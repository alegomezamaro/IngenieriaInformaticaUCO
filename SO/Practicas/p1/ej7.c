/*
PRACTICA 1 EJERCICIO 7
Realizar un programa que capture la señal de alarma, de manera que imprima la cadena “RING”
pasados 5 segundos, después pasados otros 3 segundos y por último cada segundo. Implementar
esto último, utilizando un bucle infinito que vaya imprimiendo el número de timbrazos. Pasados 4
timbrazos, el proceso se debe parar utilizando para ello la función kill().
*/

#include <stdio.h>  //Funciones de entrada/salida, como printf o perror
#include <stdlib.h> //exit, malloc o atoi
#include <unistd.h> //fork, getpid, getppid, sleep, execl, execv...
#include <signal.h> //Señales

int cont=0;

void campanada(int signal){
    //Sumamos la campanada dada
    cont++;
    printf("\nRING %d\n", cont);
    
    //Segunda campanada a 3 segundos
    if(cont == 1){
        alarm(3);
    }

    //A partir de la tercera campanada 1 segundo
    else if(cont > 1 && cont < 4){
        alarm(1);
    }

    //Fin del bucle
    else if(cont == 4){
        printf("\nSe ha llegado al maximo de campanadas (4)\n");
        kill(getpid(), SIGKILL);
    }
}

int main(){
    //Llamamos a la función campanada cuando suene alarm
    signal(SIGALRM, campanada);

    //Activamos a alarma a 5 segundos
    alarm(5);

    //Bucle infinito
    while(1){
        pause();
    }
}