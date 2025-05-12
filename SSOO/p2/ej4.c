/*
PRACTICA 2 EJERCICIO 4
Implemente un programa que cree dos hebras y cada una incremente 1.000.000 veces en un
bucle una variable global (recuerde que la variable global, al estar en el mismo espacio de memoria
para las dos hebras, es compartida, y que su uso es “peligroso”). Imprima al final del programa
principal el valor de la variable (en cada ejecución posiblemente obtenga un valor diferente a
2.000.000 – problema de concurrencia –). Intente razonar el resultado, el cual le servirá como
concepto introductorio de la siguiente práctica de la asignatura. 
*/

#include <stdio.h>  //Funciones de entrada/salida, como printf o perror
#include <stdlib.h> //exit, malloc o atoi
#include <string.h> //strerror
#include <errno.h> //Errores en la variable errno
#include <pthread.h> //Hilos y mutex

//Variable global
int global=0;

//Estructura hilo que incrementa 1.000.000 de veces la variable global
void *funcHilos(void *arg){

    //Incrementamos la memoria un millon de veces
    for(int i=0; i < 1000000; i++){
        global++;
    }

    //Retornamos el hilo
    pthread_exit(NULL);
}

int main(){
    //Definimos las variables
    pthread_t hilos[2];

    //Creamos los hilos
    for(int i=0; i < 2; i++){
        if(pthread_create(&hilos[i], NULL, funcHilos, NULL) != 0){
            fprintf(stderr, "\nError al crear el hilo %d (pthread_create)\n", (i+1));
            exit(EXIT_FAILURE);
        }
    }

    //Recogemos los hilos
    for(int i=0; i < 2; i++){
        struct hilo *devuelto;
        if(pthread_join(hilos[i], (void**)&devuelto) != 0){
            fprintf(stderr, "\nError al recoger el hilo %d (pthread_join)\n", (i+1));
            exit(EXIT_FAILURE);
        }

        //Liberamos la memoria
        free(devuelto);
    }

    printf("\nSe han recogido todos los hilos y el valor global es %d\n", global);
    exit(EXIT_SUCCESS);
}