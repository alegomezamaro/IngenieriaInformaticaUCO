/*
PRACTICA 2 EJERCICIO 3
Implemente un programa que cree un vector de 10 elementos relleno con números aleatorios
entre 1 y 9. No cree el vector de manera global, declárelo en el main(). Reparta ese vector entre 2
hebras o 5 hebras a partes iguales, según se indique por linea de argumentos un 2 o un 5, de forma
que cada hebra sume la parte del vector que le corresponda y se lo devuelva al hilo principal, el cual
mostrará la suma de los resultados devuelto por las hebras creadas.
Ejemplo de invocación del programa para crear 5 hebras que se repartan el vector: ./a.out 5
*/

#include <stdio.h>  //Funciones de entrada/salida, como printf o perror
#include <stdlib.h> //exit, malloc o atoi
#include <string.h> //strerror
#include <errno.h> //Errores en la variable errno
#include <pthread.h> //Hilos y mutex
#include <time.h> //Numeros aleatorios
#include <unistd.h> 
#define TAM 10 //Tamaño del vector

struct hilo{
    int *vector;
    int inic;
    int fin;
    int suma;
};

//Estructura hilo que suma los valores de una fracción del vector
void *funcHilos(void *arg){

    //Hacemos casting
    struct hilo *argumento= (struct hilo*) arg;

    //Sumamos los valores que corresponden al hilo
    argumento->suma=0;
    printf("\nSUMA HILO:\n");
    for(int i=argumento->inic; i < argumento->fin; i++){
        argumento->suma += argumento->vector[i];
        printf("\n%d +=%d\n", argumento->vector[i], argumento->suma);
    }

    //Retornamos el hilo
    pthread_exit((void*)argumento);
}

int main(int argc, char *argv[]){

    //Llamada incorrecta
    if(argc != 2){
        fprintf(stderr, "\nNumero de argumentos invalido ./ej3 <2 o 5>\n");
        exit(EXIT_FAILURE);
    }

    //Definimos las variables
    int n=atoi(argv[1]);
    pthread_t hilos[n];
    struct hilo *pthread[n];
    srand(time(NULL));
    int v[TAM];
    int elem=(TAM/n);
    int total=0;

    if(n != 2 && n != 5){
        fprintf(stderr, "\nArgumento invalido ./ej3 <2 o 5>\n");
        exit(EXIT_FAILURE);
    }

    //Rellenamos el vector con numeros aleatorios
    printf("\nVECTOR:\n");
    for(int i=0; i < TAM; i++){
        v[i]=((int)rand()%9)+1;
        printf("\nv[%d]= %d\n", i, v[i]);
    }

    //Creamos los hilos
    for(int i=0; i < n; i++){

        //Reservamos memoria
        pthread[i]=malloc(sizeof(struct hilo));

        //Error al reservar memoria
        if(pthread==NULL){
            fprintf(stderr, "\nError reservar memoria (malloc)\n");
            exit(EXIT_FAILURE);
        }

        //Guardamos los valores en el struct
        pthread[i]->vector=v;
        pthread[i]->inic=elem*i;
        pthread[i]->fin=((elem*(i+1))-1);

        if(pthread_create(&hilos[i], NULL, funcHilos, (void*)pthread[i]) != 0){
            fprintf(stderr, "\nError al crear el hilo %d (pthread_create)\n", (i+1));
            free(pthread[i]);
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
        total += devuelto->suma;
        printf("\nSUMA TOTAL + %d = %d\n", devuelto->suma, total);
        free(devuelto);
    }

    printf("\nSe han recogido todos los hilos\n");
    exit(EXIT_SUCCESS);
}