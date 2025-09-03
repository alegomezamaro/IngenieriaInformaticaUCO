/*
PRACTICA 3 EJERCICIO 2
Implemente un programa que cree un número N de hilos, donde N será un argumento al programa.
Tenga en cuenta los siguientes supuestos y condiciones:
- Los N hilos comparten dos variables, una llamada "par" e "impar" inicializadas a 0.
- Los hilos deben recibir un valor entero de 1 a N que indica el orden en el cuál se ha creado
el hilo. Así, el primer hilo creado recibe 1, el segundo 2, etc.
- Cada hilo debe generar 5 números aleatorios entre 0 y 10.
- Los hilos de índice de creación par deben ir sumando a la variable "par" los números que
generan.
- Los hilos de índice de creación impar deben ir sumando a la variable "impar" los números
que generan.
- Una vez finalizado cada hilo, éste debe devolver al programa principal la suma total de los
números que ha generado.
- El programa principal debe mostrar la suma devuelta por cada hebra y el valor final de las
variables “par” e “impar”.
*/

#include <stdio.h>  //Funciones de entrada/salida, como printf o perror
#include <stdlib.h> //exit, malloc o atoi
#include <string.h> //strerror
#include <errno.h> //Errores en la variable errno
#include <pthread.h> //Hilos y mutex
#include <time.h> //Numeros aleatorios

//Definimos las variables globales
pthread_mutex_t mutexP=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexI=PTHREAD_MUTEX_INITIALIZER;
int par=0;
int impar=0;

struct hilo{
    int indice;
    int suma;
};

void *hilo(void *arg){

    //Hacemos casting
    struct hilo *argumento=(struct hilo*) arg;

    //Sumamos los numeros
    for(int i=0; i<5; i++){
        int num=(rand()%11);
        argumento->suma += num;
        printf("\nHILO %ld: + %d = %d\n", argumento->indice, num, argumento->suma);
    }

    //Parte par
    if((argumento->indice % 2) == 0){
        pthread_mutex_lock(&mutexP);
        par += argumento->suma;
        pthread_mutex_unlock(&mutexP);
    }

    //Parte impar
    else if((argumento->indice % 2) == 1){
        pthread_mutex_lock(&mutexI);
        impar += argumento->suma;
        pthread_mutex_unlock(&mutexI);
    }

    pthread_exit(argumento);
}

int main(int argc, char* argv[]){

    //Llamada incorrecta
    if(argc != 2){
        fprintf(stderr, "\nNumero de argumentos invalido ./ej2 <numero de hilos>\n");
        exit(EXIT_FAILURE);
    }

    //Definimos variables
    srand(time(NULL));
    int n=atoi(argv[1]);
    pthread_t hilos[n];
    struct hilo *pthread[n];

    //Creamos los hilos proveedor
    for(int i=0; i < n; i++){

        //Reservamos memoria
        pthread[i]=(struct hilo*) malloc(sizeof(struct hilo));

        //Error al reservar memoria
        if(pthread[i] == NULL){
            fprintf(stderr, "\nError reservar memoria (malloc)\n");
            exit(EXIT_FAILURE);
        }

        //Creamos el hilo pasando el indice
        pthread[i]->indice=(i+1);
        if(pthread_create(&hilos[i], NULL, hilo, (void*)pthread[i]) != 0){
            fprintf(stderr, "\nError al crear el hilo %d (pthread_create)\n", (i+1));
            exit(EXIT_FAILURE);
        }
    }

    //Recogemos los hilos proveedor
    for(int i=0; i < n; i++){
        struct hilo *devuelto;
        if(pthread_join(hilos[i], (void**)&devuelto) != 0){
            fprintf(stderr, "\nError al recoger el hilo %d (pthread_join)\n", (i+1));
            exit(EXIT_FAILURE);
        }

        //Imprimimos el valor del hilo
        printf("\nSUMA HILO %d = %d\n", devuelto->indice, devuelto->suma);
    }

    //Imprimimos los valores
    printf("\nFINAL: PAR = %d\n", par);
    printf("\nFINAL: IMPAR = %d\n", impar);

    //Liberamos memoria
    pthread_mutex_destroy(&mutexP);
    pthread_mutex_destroy(&mutexI);
}