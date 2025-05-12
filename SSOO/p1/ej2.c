/*
PRACTICA 1 EJERCICIO 2
Realice el mismo ejercicio que en el apartado anterior, pero esta vez atendiendo al esquema que
muestra la siguiente figura. Los hijos deben mostrar también su ID y el de su padre, al igual que en
el ejercicio 1:
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

        fprintf(stderr, "\nNumero de argumentos invalido ./ej2 <numero de procesos hijo>\n");
        exit(EXIT_FAILURE);
    }

    //Declaración de variables
    int n=atoi(argv[1]);
    pid_t pid, childPid;
    int status;

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
        }

        //Recogemos los hijos
        else{
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

            //Hijo recogido correctamente
            exit(EXIT_SUCCESS);
        }
    }

    //Todos los hijos recogidos correctamente
    printf("\nPADRE - Tengo id %d y he recogido a todos mis hijos\n", getpid());
    exit(EXIT_SUCCESS);
}