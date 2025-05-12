/*
PRACTICA 1 EJERCICIO 9
Realizar un programa que este permanentemente a la espera de capturar una señal SIGUSR1 (en un
bucle while(1) infinito por ejemplo), de forma que cuando la capture imprima su ID. Compílelo y
láncelo por consola.
Creo otro programa aparte que reciba por línea de argumentos un ID de un proceso, y su cometido
sea enviar una señal SIGUSR1 al proceso cuyo ID ha recibido por dicha línea de argumentos. Una
vez enviada la señal SIGUSR1 esperará durante 1 segundo y enviará al mismo proceso al que envió
la señal SIGUSR1 la señal de KILL. Compruebe por consola si el proceso al que ha enviado ambas
señales existe ya en el sistema.
RECUERDE, LOS SLEEPS() SON A MODO DIVULGATIVO. NO USAR SLEEPS() PARA
SINCRONIZAR SUS PROCESOS A NO SER QUE SE LE PIDA EXPRESAMENTE, ESO
ES CUESTIÓN DEL NÚCLEO DEL SISTEMA OPERATIVO.
*/

#include <stdio.h>  //Funciones de entrada/salida, como printf o perror
#include <stdlib.h> //exit, malloc o atoi
#include <string.h> //strerror
#include <errno.h> //Errores en la variable errno
#include <unistd.h> //fork, getpid, getppid, sleep, execl, execv...
#include <sys/types.h> //Todas las funciones pid_t
#include <sys/wait.h> //wait, waitpid y sus macros (WIFEXITED, WIFSIGNALED...)
#include <signal.h> //Señales

/*
Ejecutar './ej9recibir' en una terminal
Ver el <PID> de dicho proceso
Ejecutar './ej9enviare <PID>' en otro terminal con el pid dado en './ej9recibir'
*/

//Mensaje imprimido al recibir la señal
void senial(int senial){
    printf("\nSe ha recibido la señal SIGUSR1: %d\n", senial);
}

int main(){

    //Espera a recibir una señal
    signal(SIGUSR1, senial);
    printf("\nProceso a la espera de señales, mi PID es %d\n", getpid());

    //Bucle infinito
    while (1){
        pause();
    }
    exit(EXIT_SUCCESS);  
}