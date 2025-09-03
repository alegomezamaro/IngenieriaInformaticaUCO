/*
PRACTICA 1 EJERCICIO 6
Use el ejercicio 1 y cree una variable global de tipo entero inicializada a 0. Haga que cada hijo
aumente en uno el valor de esa variable global y que el padre imprima el resultado final. ¿Qué
ocurre? Correcto, su valor no se modifica porque los hijos son procesos nuevos que no comparten
memoria. Para ello, y concretamente en sistemas basados en POSIX, se utilizan métodos de
intercomunicación de procesos como son memoria compartida y semáforos, los cuales se estudiarán
en otra práctica de la asignatura.
*/

#include <stdio.h>  //Funciones de entrada/salida, como printf o perror
#include <stdlib.h> //exit, malloc o atoi
#include <string.h> //strerror
#include <errno.h> //Errores en la variable errno
#include <unistd.h> //fork, getpid, getppid, sleep, execl, execv...
#include <sys/types.h> //Todas las funciones pid_t
#include <sys/wait.h> //wait, waitpid y sus macros (WIFEXITED, WIFSIGNALED...)

int main(int argc, char *argv[]){

    //Llamada incorrecta
    if(argc != 2){
        fprintf(stderr, "\nNumero de argumentos invalido ./ej6 <numero de procesos hijo>\n");
        exit(EXIT_FAILURE);
    }

    //Declaración de variables
    int n=atoi(argv[1]);
    pid_t pid, childPid;
    int status;
    int valor=0;

    //Declaración del proceso padre
    printf("\nPADRE - Mi id es %d\n", getpid());

    //Creamos los hijos
    for(int i=0; i < n; i++){
        pid=fork();

        //Error al crear los hijos
        if(pid == -1){
            printf("\nError al crear los hijos (fork). Errno %d: %s\n", errno, strerror(errno));
            exit(EXIT_FAILURE);
        }

        //Hijos creados correctamente
        else if(pid == 0){
            printf("\nHIJO %d - Mi id es %d y el de mi padre %d\n", (i+1), getpid(), getppid());

            //Sumamos 1 a valor
            valor++;
            printf("\nHIJO %d - Mi id es %d y sumo 1 a mi padre %d. VALOR = %d\n", (i+1), getpid(), getppid(), valor);
            exit(EXIT_SUCCESS);
        }
    }

    //Recogemos los hijos
    while((childPid=waitpid(-1, &status, WUNTRACED | WCONTINUED)) > 0){
        if(WIFEXITED(status)){
            printf("\nPADRE - Tengo id %d y he recogido a mi hijo de id %d. Status %d\n", getpid(), childPid, WEXITSTATUS(status));
        }
        else if(WIFSIGNALED(status)){
            printf("\nPADRE - Tengo id %d y he recogido a mi hijo de id %d forzosamente. Status %d\n", getpid(), childPid, WTERMSIG(status));
        }
        else if(WIFSTOPPED(status)){
            printf("\nPADRE - Tengo id %d y mi hijo de id %d se ha parado. Status %d\n", getpid(), childPid, WSTOPSIG(status));
        }
    }

    //Hijos recogidos correctamente
    if(childPid == -1){
        printf("\nPADRE - Tengo id %d y he recogido a tomos mis hijos\n", getpid());
        printf("\nPADRE - Tengo id %d y finalmente VALOR = %d\n", getpid(), valor);
        exit(EXIT_SUCCESS);
    }

    //Error al recoger los hijos
    else{
        printf("\nError al recoger los hijos (waitpid). Errno %d: %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
}