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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    
    if(argc!=2){
        fprintf(stderr, "\nNumero de argumentos incorrecto: ./ej1 <Numero a calcular el factorial>\n");
        exit(EXIT_FAILURE);
    }

    //Definimos variables
    pid_t pidFact=fork();
    int status;

    //Error al crear el proceso factorial
    if(pidFact==-1){
        fprintf(stderr, "\nError al crear el proceso factorial (fork)\n");
        exit(EXIT_FAILURE);
    }

    //Proceso factorial creado correctamente
    else if(pidFact==0){
        execl("./factorial", "./factorial", argv[1], NULL);
        fprintf(stderr, "\nError al abrir el proceso factorial (execl)\n");
        exit(EXIT_FAILURE);
    }

    //Recogemos factorial
    while((pidFact=waitpid(-1, &status, WUNTRACED | WCONTINUED))>0){
        if(pidFact>0){
            if(WIFEXITED(status)){
                printf("\nPadre %d, ha finalizado el hijo %d con el estado %d", getpid(), getppid(), WEXITSTATUS(status));
            }
            else if(WIFEXITED(status)){
                printf("\nPadre %d, ha finalizado el hijo %d con el estado %d", getpid(), getppid(), WTERMSIG(status));
            }
            else if(WIFSTOPPED(status)){
                printf("\nPadre %d, ha finalizado el hijo %d con el estado %d", getpid(), getppid(), WSTOPSIG(status));
            }
            else if(WIFCONTINUED(status)){
                printf("\nPadre %d, el hijo %d ha continuado su ejecución", getpid(), getppid());
            }
        }
    }

    pid_t pidCalc=fork();

    //Error al crear el proceso calculadora
    if(pidCalc==-1){
        fprintf(stderr, "\nError al crear el proceso calculadora (fork)\n");
        exit(EXIT_FAILURE);
    }

    //Proceso calculadora creado correctamente
    else if(pidCalc==0){
        printf("\nSoy el hijo %d , mi padre %d y voy a abrir la calculadora.\n", getpid(), getppid());
        execlp("gnome-calculator", "gnome-calculator", NULL);
        fprintf(stderr, "\nError al abrir el proceso calculadora (execlp)\n");
        exit(EXIT_FAILURE);
    }

    //Recogemos calculadora
    while((pidCalc=waitpid(-1, &status, WUNTRACED | WCONTINUED))>0){
        if(pidFact>0){
            if(WIFEXITED(status)){
                printf("\nPadre %d, ha finalizado el hijo %d con el estado %d", getpid(), getppid(), WEXITSTATUS(status));
            }
            else if(WIFEXITED(status)){
                printf("\nPadre %d, ha finalizado el hijo %d con el estado %d", getpid(), getppid(), WTERMSIG(status));
            }
            else if(WIFSTOPPED(status)){
                printf("\nPadre %d, ha finalizado el hijo %d con el estado %d", getpid(), getppid(), WSTOPSIG(status));
            }
            else if(WIFCONTINUED(status)){
                printf("\nPadre %d, el hijo %d ha continuado su ejecución", getpid(), getppid());
            }
        }
    }

    exit(EXIT_SUCCESS);
}