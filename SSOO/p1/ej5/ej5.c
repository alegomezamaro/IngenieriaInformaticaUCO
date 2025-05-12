/*
PRACTICA 1 EJERCICIO 5
Cree un programa que reciba por la linea de argumentos un número y calcule el factorial de ese
número. Compílelo y compruebe su funcionamiento.
A partir de ahí cree otro programa aparte que reciba dos números enteros como parámetros en la
linea de argumentos y cree dos procesos hijos, de manera que cada uno calcule el factorial de uno
de los números usando el ejecutable creado anteriormente (“./a.out 3 5”). use para ello la familia de
funciones exec(). En el programa que calcula el factorial ponga un sleep(1) entre los cálculos
parciales para poder observar en consola como se van ejecutando los dos procesos que se lanzarán
en paralelo.
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

int main(int argc, char *argv[]){

    //Llamada incorrecta
    if(argc != 3){
        fprintf(stderr, "\nNumero de argumentos invalido ./ej5 <numero 1> <numero 2>\n");
        exit(EXIT_FAILURE);
    }

    //Declaración de variables
    pid_t pid, childPid;
    int status;

    //Declaración del proceso padre
    printf("\nPADRE - Mi id es %d\n", getpid());

    
    //Creamos los hijos
    for(int i=0; i < 2; i++){
        pid=fork();

        //Error al crear los hijos
        if(pid == -1){
            printf("\nError al crear los hijos (fork). Errno %d: %s\n", errno, strerror(errno));
            exit(EXIT_FAILURE);
        }

        //Hijos creados correctamente
        else if(pid == 0){
            printf("\nHIJO %d - Mi id es %d y el de mi padre %d\n", (i+1), getpid(), getppid());
            execl("./ej5factorial", "./ej5factorial", argv[i+1], NULL);
            printf("\nError al abrir el hijo %d (exec). Errno %d: %s\n", (i+1), errno, strerror(errno));
            exit(EXIT_FAILURE);
        }
        sleep(1);
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
        printf("\nPADRE - Tengo id %d y he recogido a todos mis hijos\n", getpid());
        exit(EXIT_SUCCESS);
    }
    
    //Error al recoger los hijos
    else{
        printf("\nError al recoger los hijos (waitpid). Errno %d: %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
}