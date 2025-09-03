/*
PRACTICA 3 EJERCICIO 4
Cree dos hilos de manera que uno ejecute escribirA() y el otro escribirB(). Implemente un programa
que introduzca los semáforos oportunos para que la salida sea BABABABABA. No olvide indicar
los valores iniciales de los semáforos que utilice.
void escribirA (void p){
    int i;
    for (i= 0; i< 5; i++){
        printf ("A");
        fflush(NULL);
    }
    pthread exit(NULL);
}
void escribirB (void p){
    int i;
    for (i= 0;i< 5; i++){
        printf ("B");
        fflush(NULL);
    }
    pthread exit(NULL);
}
*/

#include <stdio.h>  //Funciones de entrada/salida, como printf o perror
#include <stdlib.h> //exit, malloc o atoi
#include <string.h> //strerror
#include <errno.h> //Errores en la variable errno
#include <pthread.h> //Hilos y mutex
#include <semaphore.h> //Semaforos generales

///Definimos los semaforos generales
sem_t escA;
sem_t escB;

//Imprime A
void* escribirA(void* p) {
    for (int i = 0; i < 5; i++) {

        //Espera B
        sem_wait(&escB);
        printf("A");

        //Desbloquea B
        sem_post(&escA);
    }
    pthread_exit(NULL);
}

//Imprime B
void* escribirB(void* p) {
    for (int i = 0; i < 5; i++) {
        
        //Espera A
        sem_wait(&escA);
        printf("B");

        //Desbloquea A
        sem_post(&escB);
    }
    pthread_exit(NULL);
}

int main() {

    //Definimos los hilos
    pthread_t hiloA;
    pthread_t hiloB;

    //Inicializamos los semáforos
    sem_init(&escB, 0, 0);
    sem_init(&escA, 0, 1); //A 1 para escribir primero

    //Creamos los hilos
    if(pthread_create(&hiloA, NULL, escribirA, NULL) != 0){
        fprintf(stderr, "\nError al crear el hilo (pthread_create)\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_create(&hiloB, NULL, escribirB, NULL) != 0){
        fprintf(stderr, "\nError al crear el hilo (pthread_create)\n");
        exit(EXIT_FAILURE);
    }

    //Recogemos los hilos
    if(pthread_join(hiloA, NULL) != 0){
        fprintf(stderr, "\nError al recoger el hilo %d (pthread_join)\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_join(hiloB, NULL) != 0){
        fprintf(stderr, "\nError al recoger el hilo %d (pthread_join)\n");
        exit(EXIT_FAILURE);
    }

    //Destruimos los semaforos
    sem_destroy(&escB);
    sem_destroy(&escA);
    printf("\nFIN\n");
    return 0;
}