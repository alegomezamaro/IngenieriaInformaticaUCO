// 1. Realice un programa que cree dos hijos.  
//  - El primero calculará el factorial del número pasado como argumento. Deberá 
//    de mostrar por pantalla antes de terminar el siguiente mensaje:  
//    "Soy el hijo PID , mi padre PPID el factorial de A es X"  
//  - El segundo abrirá la calculadora y mostrará el mensaje:  
//    "Soy el hijo PID , mi padre PPID y voy a abrir la calculadora."
//  - El padre después de crear los hijos deben de esperar a los hijos y debe 
//    mostrar el estado de finalización de la siguiente manera:  
//    "Padre PID, ha finalizado el hijo PID con el estado ESTADO" 
//    por cada hijo. Mostrando las señales de ERRNO

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){

    if(argc != 2){

        printf("\nNumero de argumentos incorrecto\n");
        exit(EXIT_FAILURE);
    }

    pid_t wpid;
    pid_t fact = fork();
    int status;

    if(fact < 0){

        printf("\nFactorial creado incorrectamente\n");
        exit(EXIT_FAILURE);
    }

    else if(fact == 0){

        printf("\nEntrando en factorial\n");
        
        execl("./factorial", "./factorial", argv[1], NULL);

        printf("\nFactorial abierto incorrectamente\n");
        exit(EXIT_FAILURE);
    }

    pid_t calc = fork();

    if(calc < 0){

        printf("\nCalculadora creado incorrectamente\n");
        exit(EXIT_FAILURE);
    }

    else if(calc == 0){

        printf("\nSoy el hijo %d , mi padre %d y voy a abrir la calculadora.\n", getpid(), getppid());
        
        execlp("gnome-calculator", "gnome-calculator", NULL);

        printf("\nCalculadora abierto incorrectamente\n");
        exit(EXIT_FAILURE);
    }

    while((wpid=waitpid(-1, &status, WUNTRACED | WCONTINUED)) > 0){

        if(WIFEXITED(status)){

            printf("\nPadre %d, ha finalizado el hijo %d con el estado %d", getpid(), wpid, WEXITSTATUS(status));
        }

        if(WIFSIGNALED(status)){
                
            printf("\nPadre %d, ha finalizado el hijo %d con el estado %d", getpid(), wpid, WTERMSIG(status));
        }

        if(WIFSTOPPED(status)){
                
            printf("\nPadre %d, ha finalizado el hijo %d con el estado %d", getpid(), wpid, WSTOPSIG(status));
        }
    }

    exit(EXIT_SUCCESS);
}