// 2. Nos piden crear dos hebras, una “escritor” y otra “lector”, en el que ambos pueden acceder a la variable compartida llamada “variable” inicializada inicialmente a -1.
//    Ambas no pueden ni escribir y leer a la vez, pudiéndose la intercalación entre uno y otro. Cada hebra se ejecutará un numero de iteraciones pasados por línea de argumentos
//    Ejemplo de invocación: ./ej2 3

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

//Inicializamos las variables globales
int variable = -1;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//Escritor
void *Escritor(void *num){
    int *aux;
    aux = (int *) num; //Casting void* a int*
    
    //Accedemos num veces
    for (int i = 0; i < (*aux); i++) {

        //Bloqueamos el mutex
        pthread_mutex_lock(&mutex);

        //Escribimos el número
        int cantidad = rand() % 10 + 1;
        variable = cantidad; 
        printf("Escritor %ld, escribo el número %d\n", pthread_self(), variable);

        //Desbloqueamos el mutex
        pthread_mutex_unlock(&mutex);
    }

    //Cerramos el hilo
    pthread_exit(NULL);
}

//Lector
void *Lector(void *num){
    int *aux;
    aux = (int *) num; // Casting void* a int*
    
    //Accedemos num veces
    for (int i = 0; i < (*aux); i++) {

        //Bloqueamos el mutex
        pthread_mutex_lock(&mutex);

        //Leemos el numero
        printf("Lector %ld, lee el número %d\n", pthread_self(), variable);

        //Desbloqueamos el mutex
        pthread_mutex_unlock(&mutex);
    }

    //Cerramos el hilo
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "\nFormato incorrecto, ./ej2 <Número de accesos a la variable global>\n");
        exit(EXIT_FAILURE);
    }

    //Creamos las variables
    int num = atoi(argv[1]);
    pthread_t hilo[2]; 

    //Creamos los hilos
    if(pthread_create(&hilo[0], NULL, (void*)Escritor, (void*)&num)){
        fprintf(stderr, "\nError al crear un escritor. Errno= %d (%s)\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
    if(pthread_create(&hilo[1], NULL, (void*)Lector, (void*)&num)){
        fprintf(stderr, "\nError al crear un lector (pthread_create). Errno= %d (%s)\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    //Esperamos a que ambos hilos terminen
    for(int i = 0; i < 2; ++i){
        if(pthread_join(hilo[i], NULL)){
            printf("\nError en la espera de la hebra (pthread_join). Errno= %d (%s)\n", errno, strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
}