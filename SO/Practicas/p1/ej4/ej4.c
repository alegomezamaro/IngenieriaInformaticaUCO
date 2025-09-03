/*
PRACTICA 1 EJERCICIO 4
Implemente un programa donde se creen dos hijos. Uno de ellos que abra la calculadora de su
distribución de Linux (busque como se llama ese ejecutable) y el otro que abra un editor de textos
con N ficheros pasados como argumentos (recuerde hacer que el padre espere a los hijos). Use para
ello la familia de funciones exec().
Un ejemplo de invocación sería:
./miPrograma gnome-calculator gedit fichero1.txt fichero2.txt ficheroN.txt
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
    if(argc < 3){
        fprintf(stderr, "\nNumero de argumentos invalido ./ej4 <calculadora> <editor> <fichero 1> ... <fichero N>\n");
        exit(EXIT_FAILURE);
    }

    //Declaración de variables
    char *calc=argv[1];
    char *edit=argv[2];
    pid_t pidCalc, pidEdit;
    int status, pidTemp;

    //Declaración del proceso padre
    printf("\nPADRE - Mi id es %d\n", getpid());

    //Creamos la calculadora
    pidCalc=fork();

    //Error al crear el proceso calculadora
    if(pidCalc == -1){
        printf("\nError al crear el proceso calculadora (fork). Errno %d: %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    //Calculadora creada correctamente
    else if(pidCalc == 0){
        printf("\nCALCULADORA - Mi id es %d y el de mi padre %d\n", getpid(), getppid());
        pidTemp = getpid();
        execlp(calc, calc, NULL);
        printf("\nError al abrir la calculadora (execvp). Errno %d: %s", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }


    //Recogemos la calculadora
    while((pidCalc=waitpid(pidTemp, &status, WUNTRACED | WCONTINUED)) > 0){
        if(WIFEXITED(status)){
            printf("\nPADRE - Tengo id %d y he recogido a la calculadora de id %d. Status %d\n", getpid(), pidCalc, WEXITSTATUS(status));
        }
        else if(WIFSIGNALED(status)){
            printf("\nPADRE - Tengo id %d y he recogido a la calculadora de id %d forzosamente. Status %d\n", getpid(), pidCalc, WTERMSIG(status));
        }
        else if(WIFSTOPPED(status)){
            printf("\nPADRE - Tengo id %d y la calculadora de id %d se ha parado. Status %d\n", getpid(), pidCalc, WSTOPSIG(status));
        }
    }

    //Hijos recogidos correctamente
    if(pidCalc == -1){
        printf("\nPADRE - Tengo id %d y he recogido la calculadora\n", getpid());
    }

    //Error al recoger los hijos
    else{
        printf("\nError al recoger la calculadora (waitpid). Errno %d: %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    //Creamos el editor
    pidEdit=fork();

    //Error al crear el proceso calculadora
    if(pidEdit == -1){
        printf("\nError al crear el proceso editor (fork). Errno %d: %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    //Calculadora creada correctamente
    else if(pidEdit == 0){
        printf("\nEDITOR - Mi id es %d y el de mi padre %d\n", getpid(), getppid());
        pidTemp = getpid();
        execvp(edit, &argv[2]);
        printf("\nError al abrir el editor (execvp). Errno %d: %s", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }


    //Recogemos la calculadora
    while((pidEdit=waitpid(pidTemp, &status, WUNTRACED | WCONTINUED)) > 0){
        if(WIFEXITED(status)){
            printf("\nPADRE - Tengo id %d y he recogido el editor de id %d. Status %d\n", getpid(), pidEdit, WEXITSTATUS(status));
        }
        else if(WIFSIGNALED(status)){
            printf("\nPADRE - Tengo id %d y he recogido el editor de id %d forzosamente. Status %d\n", getpid(), pidEdit, WTERMSIG(status));
        }
        else if(WIFSTOPPED(status)){
            printf("\nPADRE - Tengo id %d y el editor de id %d se ha parado. Status %d\n", getpid(), pidEdit, WSTOPSIG(status));
        }
    }

    //Hijos recogidos correctamente
    if(pidEdit == -1){
        printf("\nPADRE - Tengo id %d y he recogido el editor\n", getpid());
    }

    //Error al recoger los hijos
    else{
        printf("\nError al recoger el editor (waitpid). Errno %d: %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    //Todos los hijos recogidos correctamente
    printf("\nPADRE - Tengo id %d y he recogido a todos mis hijos\n", getpid());
    exit(EXIT_SUCCESS);
}