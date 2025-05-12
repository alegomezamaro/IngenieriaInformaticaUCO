/*
PRACTICA 1 EJERCICIO 3
Modifique levemente el ejercicio 1. Implemente un programa que cree N (pedido desde línea de
argumentos) procesos utilizando fork():
- Cada proceso hijo mostrará por salida estándar un mensaje incluyendo su ID
- A continuación cada hijo esperará 10*n segundos, donde “n” va de 1 a N, de acuerdo al
orden de proceso creado, y finalizará su ejecución con código de salida 0. Recuerde que esto
es simplemente hacer un exit(0), return(0) o EXIT_SUCCESS).
- El proceso padre mostrará por salida estándar un mensaje cada vez que cree exitosamente un
hijo indicando el número de proceso creado (1..n), esperará por la finalización de todos
ellos, e imprimirá un mensaje indicando la finalización de cada hijo y su status. Terminará
con código 0.
- Verifique en otra consola los procesos creados utilizando los comandos “ps -u”, “pstree”,
“ps -a”. Deberá visualizar algo similar a la siguiente captura de pantalla. No olvide esperar a
los hijos creados fuera del bucle for principal.
¿Quién piensa que es el padre de su programa, es decir, el padre de su main() o proceso principal
que ha creado el abanico de hijos?
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
    if(argc != 2){
        fprintf(stderr, "\nNumero de argumentos invalido ./ej3 <numero de procesos hijo>\n");
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
            sleep(10*(i+1));
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
        printf("\nPADRE - Tengo id %d y he recogido a todos mis hijos\n", getpid());
        exit(EXIT_SUCCESS);
    }

    //Error al recoger los hijos
    else{
        printf("\nError al recoger los hijos (waitpid). Errno %d: %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
}