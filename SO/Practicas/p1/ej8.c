/*
PRACTICA 1 EJERCICIO 8
Realizar un programa padre que expanda un hijo y al cual le envíe cada 1 segundo una señal
personalizada de usuario SIGUSR1. El hijo debe imprimir un mensaje en pantalla cada vez que
recibe la señal del padre, tratándola en una función aparte llamada tratarSennal(). Enviados 5
mensajes los procesos deben salir. Utiliza las funciones signal() y kill().
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

int enviados=0;

//Función que se hace al mandar señal
void tratarSennal(int senial){
    enviados++;
    printf("\nHIJO - Señal %d recibida\n", enviados);

    //Maximo de señales recibidas
    if(enviados == 5){
        printf("\nSe ha llegado al maximo de llamadas (5)\n");
        kill(getpid(), SIGKILL);
    }
}

int main(){
    //Declaración de variables
    pid_t pid;
    int status;

    //Declaración del proceso padre
    printf("\nPADRE - Mi id es %d\n", getpid());

    
    //Creamos el hijo
    pid=fork();

    //Error al crear el hijo
    if(pid == -1){
        printf("\nError al crear el hijo (fork). Errno %d: %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    //Hijo creado correctamente
    if(pid == 0){
        printf("\nHIJO - Mi id es %d y el de mi padre %d\n", getpid(), getppid());

        //Creamos la señal
        signal(SIGUSR1, tratarSennal);

        //Bucle infinito
        while(1){
            pause();
        }
    }

    //Enviador de señales cada segundo
    else{
        printf("\nPADRE - Mi id es %d y voy a enviar señales a mi hijo\n", getpid());

        //Bucle de llamadas cada 1 segundo
        for(int i=0; i < 10; i++){

            //Sleep antes del kill
            sleep(1);

            kill(pid, SIGUSR1);
            printf("\nPADRE - Señal %d de tipo SIGUSR1 enviada\n", (i+1));
        }

        //Recogemos el hijo
        wait(NULL);
    }
    
    //Hijo recogido correctamente
    printf("\nPADRE - Tengo id %d y he recogido a mi hijos\n", getpid());
    exit(EXIT_SUCCESS);
}