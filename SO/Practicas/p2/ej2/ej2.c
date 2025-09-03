/*
PRACTICA 2 EJERCICIO 2
Implemente un programa que cuente las líneas de los ficheros de texto que se le pasen como
parámetros y al final muestre el número de líneas totales (contando las de todos los ficheros juntos).
Ejemplo de llamada: ./a.out fichero1 fichero2 fichero3
Debe crear un hilo por cada fichero indicado por linea de argumentos, de forma que todos los
ficheros se procesen de manera paralela, uno por cada hilo.
*/

#include <stdio.h>  //Funciones de entrada/salida, como printf o perror
#include <stdlib.h> //exit, malloc o atoi
#include <string.h> //strerror
#include <errno.h> //Errores en la variable errno
#include <pthread.h> //Hilos y mutex

//Estructura hilo que cuenta las lineas de un fichero
void *funcHilos(void *arg){

    //Hacemos casting a la estructura
    struct hilo *argumento=(struct hilo*) arg;
    argumento->lineas=0;

    //Abrimos el fichero
    FILE *f=fopen(argumento->fichero, "r");

    //Error al reservar memoria
    if(f==NULL){
        fprintf(stderr, "\nError al abrir el fichero (fopen)\n");
        pthread_exit((void*) argumento);
    }

    //Contamos las lineas del fichero
    char linea[MAX];
    while(fgets(linea, sizeof(linea), f) != NULL){
        argumento->lineas++;
    }

    //Retornamos el hilo
    fclose(f);
    printf("\nHILO %ld: %d líneas en %s\n", pthread_self(), argumento->lineas, argumento->fichero);
    pthread_exit((void*)argumento);
}

int main(int argc, char *argv[]){

    //Definimos las variables
    int n=(argc-1);
    pthread_t hilos[n];
    struct hilo *pthread[n];
    int total=0;

    //Creamos los hilos
    for(int i=0; i < n; i++){
        //Reservamos memoria
        pthread[i]=(struct hilo*) malloc(sizeof(struct hilo));

        //Error al reservar memoria
        if(pthread[i]==NULL){
            fprintf(stderr, "\nError reservar memoria (malloc)\n");
            pthread_exit(NULL);
        }

        //Metemos el nombre del fichero en el hilo y cremaos los hilos
        pthread[i]->fichero=(argv[i+1]);
        if(pthread_create(&hilos[i], NULL, funcHilos, (void*)pthread[i]) != 0){
            fprintf(stderr, "\nError al crear el hilo %d (pthread_create)\n", (i+1));
            exit(EXIT_FAILURE);
        }
    }

    //Recogemos los hilos
    for(int i=0; i < n; i++){
        struct hilo *devuelto;
        if(pthread_join(hilos[i], (void**)&devuelto) != 0){
            fprintf(stderr, "\nError al recoger el hilo %d (pthread_join)\n", (i+1));
            exit(EXIT_FAILURE);
        }

        //Sumamos los valores
        total += devuelto->lineas;
        printf("\n+ %d = %d\n", devuelto->lineas, total);
        free(pthread[i]);
    }

    printf("\nSe han recogido todos los hilos y hay %d lineas entre %d ficheros\n", total, n);
    exit(EXIT_SUCCESS);
}