// 1. Nos piden crear dos procesos hijos en paralelo, uno que abra la calculadora y otro el reloj. Los nombres de los ejecutables son pasados por línea de comandos.
//    Ejemplo de ejecución: ./ej1 gnome-calculator xclock

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv []){

    if(argc != 3){

        fprintf(stderr, "\nNumero de argumentos incorrecto\n");
        exit(EXIT_FAILURE);
    }

    char *calc = argv[1];
    char *reloj = argv[2];
    pid_t pcalc, preloj;
    int status;

    pcalc = fork();

    if(pcalc == -1){

        fprintf(stderr, "\nProceso calculadora generado incorrectamente\n");
        exit(EXIT_FAILURE);
    }

    else if(pcalc == 0){

        printf("\nCALCULADORA -> Soy PID %d con PPID %d\n", getpid(), getppid());
        execlp(calc, calc, NULL);
        fprintf(stderr, "\nCalculadora abierta incorrectamente\n");
        exit(EXIT_FAILURE);
    }

    while((pcalc = waitpid(-1, &status, WUNTRACED | WCONTINUED)) > 0){

        if(WIFEXITED(status)){

            printf("\nPADRE -> Soy PID %d y he recogido la calculadora con PID %d correctamente. Status: %d\n", getpid(), pcalc, WEXITSTATUS(status));
        }

        if(WIFSIGNALED(status)){

            printf("\nPADRE -> Soy PID %d y he finalizado la calculadora con PID %d correctamente. Status: %d\n", getpid(), pcalc, WTERMSIG(status));
        }

        if(WIFSTOPPED(status)){

            printf("\nPADRE -> Soy PID %d y he parado la calculadora con PID %d correctamente. Status: %d\n", getpid(), pcalc, WSTOPSIG(status));
        }
    }

    preloj = fork();

    if(preloj == -1){

        fprintf(stderr, "\nProceso reloj generado incorrectamente\n");
        exit(EXIT_FAILURE);
    }

    else if(preloj == 0){

        printf("\nRELOJ -> Soy PID %d con PPID %d\n", getpid(), getppid());
        execlp(reloj, reloj, NULL);
        fprintf(stderr, "\nReloj abierta incorrectamente\n");
        exit(EXIT_FAILURE);
    }

    while((preloj = waitpid(-1, &status, WUNTRACED | WCONTINUED)) > 0){

        if(WIFEXITED(status)){

            printf("\nPADRE -> Soy PID %d y he recogido el reloj con PID %d correctamente. Status: %d\n", getpid(), preloj, WEXITSTATUS(status));
        }

        if(WIFSIGNALED(status)){

            printf("\nPADRE -> Soy PID %d y he finalizado el reloj con PID %d correctamente. Status: %d\n", getpid(), preloj, WTERMSIG(status));
        }

        if(WIFSTOPPED(status)){

            printf("\nPADRE -> Soy PID %d y he parado el reloj con PID %d correctamente. Status: %d\n", getpid(), preloj, WSTOPSIG(status));
        }
    }

    if(pcalc != -1 || preloj != -1){

        fprintf(stderr, "\nPADRE -> No se han recogido ambos hijos correctamente\n");
        exit(EXIT_FAILURE);
    }

    fprintf(stderr, "\nPADRE -> Se han recogido ambos hijos correctamente\n");
    exit(EXIT_SUCCESS);
}