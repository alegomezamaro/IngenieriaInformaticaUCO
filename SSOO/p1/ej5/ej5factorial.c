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

//Calcula el factorial de n
int calcFactorial(int n){

    //Numero base
    int factorial = 1;

    //Calculamos el factorial
    for(int i=1; i <= n; i++){
        factorial *= i;
    }

    //Retornamos el valor
    return factorial;
}

int main(int argc, char * argv[]){

    //Llamada incorrecta
    if(argc != 2){
        fprintf(stderr, "\nNumero de argumentos invalido ./ej5factorial <numero positivo>\n");
        exit(EXIT_FAILURE);
    }

    //Declaración de variables
    int n = atoi(argv[1]); //Numero al que calcular el factorial
    int factorial = calcFactorial(n);

    //Imprimimos el resultado
    printf("\nFACTORIAL DE %d = %d\n", n, factorial);
    exit(EXIT_SUCCESS);
}