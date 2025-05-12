// 1. Nos piden crear dos procesos hijos en paralelo, uno que abra la calculadora y otro el reloj. Los nombres de los ejecutables son pasados por línea de comandos.
//    Ejemplo de ejecución: ./ej1 gnome-calculator xclock

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){

    if(argc!=3){
        fprintf(stderr, "\nFormato incorrecto, ./ej1 <Calculadora> <Reloj>\n");
        exit(EXIT_FAILURE);
    }

    //Guardamos ejecutables
    char *calc=argv[1];
    char *reloj=argv[2];
    int status;

    //Creamos el proceso calculadora
    pid_t pidCalc=fork();

    //Error al crear el proceso calculadora
    if(pidCalc==-1){
        printf("\nError al crear el proceso calculadora (fork). Errno= %d, %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    //Abrimos calculadora
    else if(pidCalc==0){
        execlp(calc, calc, NULL);
        printf("\nError al abrir la calculadora (execlp). Errno= %d, %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    //Creamos el proceso reloj
    pid_t pidReloj=fork();

    //Error al crear el proceso reloj
    if(pidReloj==-1){
        printf("\nError al crear el proceso reloj (fork). Errno= %d, %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    //Abrimos reloj
    else if(pidReloj==0){
        execlp(reloj, reloj, NULL);
        printf("\nError al abrir el reloj (execlp). Errno= %d, %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    //Recoge el proceso calculadora
    while(pidCalc=waitpid(-1, &status, WUNTRACED | WCONTINUED)>0){
        if(WIFEXITED(status)){
            printf("\nPadre %d, mi hijo con pid %d ha salido correctamente. Status= %d", getppid(), getpid(), WEXITSTATUS(status));
        }

        else if(WIFSIGNALED(status)){
            printf("\nPadre %d, mi hijo con pid %d ha salido forzosamente. Status= %d", getppid(), getpid(), WTERMSIG(status));
        }

        else if(WIFSTOPPED(status)){
            printf("\nPadre %d, mi hijo con pid %d ha parado. Status= %d", getppid(), getpid(), WSTOPSIG(status));
        }

        else if(WIFCONTINUED(status)){
            printf("\nPadre %d, mi hijo con pid %d ha continuado.", getppid(), getpid());
        }
        
    }

    //Recoge los procesos
    while((pidReloj=waitpid(-1, &status, WUNTRACED | WCONTINUED))>0){
        if(WIFEXITED(status)){
            printf("\nPadre %d, mi hijo con pid %d ha salido correctamente. Status= %d", getppid(), getpid(), WEXITSTATUS(status));
        }

        else if(WIFSIGNALED(status)){
            printf("\nPadre %d, mi hijo con pid %d ha salido forzosamente. Status= %d", getppid(), getpid(), WTERMSIG(status));
        }

        else if(WIFSTOPPED(status)){
            printf("\nPadre %d, mi hijo con pid %d ha parado. Status= %d", getppid(), getpid(), WSTOPSIG(status));
        }

        else if(WIFCONTINUED(status)){
            printf("\nPadre %d, mi hijo con pid %d ha continuado.", getppid(), getpid());
        }
        
    }
    
        //Se han recogido correctamente
    if(pidReloj==-1){
        printf("\nEl padre ha recogido ambos procesos correctamente\n");
    }

    //No se han recogido todos
    else{
        perror("\nEl padre no ha recogido ambos procesos correctamente\n");
        exit(EXIT_FAILURE);
    }
    
    //Fin del programa
    exit(EXIT_SUCCESS);
}