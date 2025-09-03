// 2. Nos piden crear dos hebras, una “escritor” y otra “lector”, en el que ambos pueden acceder a la variable compartida llamada “variable” inicializada inicialmente a -1.
//    Ambas no pueden ni escribir y leer a la vez, pudiéndose la intercalación entre uno y otro. Cada hebra se ejecutará un numero de iteraciones pasados por línea de argumentos
//    Ejemplo de invocación: ./ej2 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>

int val = -1;
pthread_mutex_t sem = PTHREAD_MUTEX_INITIALIZER;

void* lector(void *arg){

    int *numero = (int*) arg;

    for(size_t i=0; i < *numero; i++){

        pthread_mutex_lock(&sem);
        printf("\nLECTOR %ld -> Leo %d\n", pthread_self(), val);
        pthread_mutex_unlock(&sem);
    }

    pthread_exit(NULL);
}

void* escritor(void *arg){

    int *numero = (int*) arg;

    for(size_t i=0; i < *numero; i++){

        pthread_mutex_lock(&sem);
        int aux = rand() % 10;
        val = aux;
        printf("\nESCRITOR %ld -> Escribo %d\n", pthread_self(), val);
        pthread_mutex_unlock(&sem);
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]){

    if(argc != 2){

        fprintf(stderr, "\nNumero de argumentos incorrecto\n");
        exit(EXIT_FAILURE);
    }

    int num = atoi(argv[1]);
    pthread_t hlect, hescr;

    if(pthread_create(&hlect, NULL, lector, &num)){

        fprintf(stderr, "\nError al crear un lector. Errno= %d (%s)\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    if(pthread_create(&hescr, NULL, escritor, &num)){

        fprintf(stderr, "\nError al crear un escritor. Errno= %d (%s)\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    if(pthread_join(hlect, NULL)){

        printf("\nError en la espera de la hebra lector. Errno= %d (%s)\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    if(pthread_join(hescr, NULL)){

        printf("\nError en la espera de la hebra escritor. Errno= %d (%s)\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    pthread_mutex_destroy(&sem);
    exit(EXIT_SUCCESS);
}