/*
PRACTICA 3 EJERCICIO 3
En concurrencia, el problema del productor-consumidor es un problema típico, y su enunciado
general es el siguiente:
Hay un proceso generando algún tipo de datos (registros, caracteres, aumento de variables,
modificaciones en arrays, modificación de ficheros, etc) y poniéndolos en un buffer. Hay un
consumidor que está extrayendo datos de dicho buffer de uno en uno.
El sistema está obligado a impedir la superposición de las operaciones sobre los datos, es decir, sólo
un agente (productor o consumidor) puede acceder al buffer en un momento dado (así el productor
no sobrescribe un elemento que esté leyendo el consumidor, y viceversa). Estaríamos hablando de
la sección crítica.
Si suponemos que el buffer es limitado y está completo, el productor debe esperar hasta que el
consumidor saque al menos un elemento para así poder seguir almacenando datos. En el caso de
que el buffer esté vacío el consumidor debe esperar a que se escriba información nueva por parte del
productor. 
Una vez haya estudiado detenidamente el problema del productor-consumidor:
    a) Implemente el problema para hilos, teniendo en cuenta que la sección crítica va a ser un
    array de enteros con una capacidad de 5 elementos y donde habrá un productor y un
    consumidor. Cada uno podrá producir-consumir 10 elementos.
    b) Haga lo mismo pero con una sección crítica de 3 elementos, y habrá 3 productores y 3
    consumidores, que podrán producir-consumir 1 elemento cada uno.
*/

#include <stdio.h>  //Funciones de entrada/salida, como printf o perror
#include <stdlib.h> //exit, malloc o atoi
#include <string.h> //strerror
#include <errno.h> //Errores en la variable errno
#include <pthread.h> //Hilos y mutex
#include <semaphore.h> //Semaforos generales

#define TAM 5 //Tamaño del buffer

//Definimos las variables globales
int buffer[TAM];
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
sem_t lleno;
sem_t vacio;
int posP=0;
int posC=0;

//Funcion productor
void* productor(void* arg){

    //Rellenamos X numeros
    for (int i = 0; i < 10; i++) {
        int num = rand() % 101;

        //Bloqueamos semaforos
        sem_wait(&lleno);
        pthread_mutex_lock(&mutex);

        //Insertamos datos
        buffer[posP] = num;
        printf("Productor %d en la posición %d\n", num, posP);
        posP = (posP + 1) % 5;

        //Liberamos semaforos
        pthread_mutex_unlock(&mutex);
        sem_post(&vacio);
    }
    pthread_exit(NULL);
}

//Funcion consumidor
void* consumidor(void* arg){

    //Recogemos X numeros
    for(int i = 0; i < 10; i++){
        
        //Bloqueamos semaforos
        sem_wait(&vacio);
        pthread_mutex_lock(&mutex);

        //Recogemos datos
        printf("Consumidor consumiendo un %d de la posición %d\n", buffer[posC], posC);
        posC = (posC + 1) % 5;

        //Liberamos semaforos
        pthread_mutex_unlock(&mutex);
        sem_post(&lleno);
    }
    pthread_exit(NULL);
}

int main() {
    //Inicializar semaforos y numeros aleatorios
    sem_init(&lleno, 0, TAM);
    sem_init(&vacio, 0, 0);
    srand(time(NULL));
    pthread_t prod;
    pthread_t cons;
    
    //Creamos los hilos
    if(pthread_create(&prod, NULL, productor, NULL) != 0){
        fprintf(stderr, "\nError al crear el hilo (pthread_create)\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_create(&cons, NULL, consumidor, NULL) != 0){
        fprintf(stderr, "\nError al crear el hilo (pthread_create)\n");
        exit(EXIT_FAILURE);
    }
    
    //Liberamos los hilos
    if(pthread_join(prod, NULL) != 0){
        fprintf(stderr, "\nError al recoger el hilo %d (pthread_join)\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_join(cons, NULL) != 0){
        fprintf(stderr, "\nError al recoger el hilo %d (pthread_join)\n");
        exit(EXIT_FAILURE);
    };
    
    //Liberamos los semaforos
    pthread_mutex_destroy(&mutex);
    sem_destroy(&lleno);
    sem_destroy(&vacio);
    return 0;
}