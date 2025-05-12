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

int main(int argc, char *argv[]){

    //Llamada incorrecta
    if(argc != 2){
        fprintf(stderr, "\nNumero de argumentos invalido ./ej9 <pid a recibir la señal>\n");
        exit(EXIT_FAILURE);
    }

    //Declaración de variables
    pid_t pid=atoi(argv[1]);

    //Envio de señal
    if(kill(pid, SIGUSR1) == -1){

        //Error al envial la señal
        printf("\nError al enviar SIGUSR1 (kill). Errno %d: %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE); 
    }

    printf("\nSeñal SIGUSR1 enviada al proceso con PID %d\n", pid);
    sleep(1); //Esperar 1 segundo para seguir

    //Matamos el proceso
    if(kill(pid, SIGKILL) == -1){

        //Error al envial la señal
        printf("\nError al enviar SIGKILL (kill). Errno %d: %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    printf("\nSeñal SIGKILL enviada al proceso con PID %d\n", pid);
    exit(EXIT_SUCCESS);
}