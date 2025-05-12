/*
PRACTICA 2 EJERCICIO 1
Implemente un programa que cree un número N de hebras. Cada hebra creará 2 números
aleatorios flotantes (consulte Moodle para la generación de aleatorios) y guardará su suma en una
variable para ello, que será devuelta a la hebra principal o llamadora (la que invocó
pthread_create()).
La hebra principal ira recogiendo los valores devueltos por las N hebras y los ira sumando en
una variable no global cuyo resultado mostrará al final por pantalla. Para ver que los resultados
finales son los que usted espera, muestre los 2 números que va creando cada hebra y su suma, de
forma que pueda comparar esas sumas parciales con la suma final que realizará el main() o hebra
principal. Utilice macros definidas y comprobación de errores en sus programas (errno y
comprobación de valores devueltos en cada llamada, con sus posibles alternativas).
*/

#include <stdio.h>  //Funciones de entrada/salida, como printf o perror
#include <stdlib.h> //exit, malloc o atoi
#include <string.h> //strerror
#include <errno.h> //Errores en la variable errno
#include <pthread.h> //Hilos y mutex
#include <time.h> //Numeros aleatorios

//Estructura hilo con la suma de los valores generados
struct hilo{
    float suma;
};

void *funcHilos(void *arg){

    //Reservamos memoria
    struct hilo *argumento=malloc(sizeof(struct hilo));

    //Error al reservar memoria
    if(argumento==NULL){
        fprintf(stderr, "\nError reservar memoria (malloc)\n");
        pthread_exit(NULL);
    }

    //Generamos los numeros y guardamos la suma
    float num1=(float)rand()/(float)(RAND_MAX/10.0);
    float num2=(float)rand()/(float)(RAND_MAX/10.0);
    argumento->suma=num1+num2;
    printf("\nHILO %ld: %f + %f = %f\n", pthread_self(), num1, num2, argumento->suma);

    //Retornamos el hilo
    pthread_exit((void*)argumento);
}

int main(int argc, char *argv[]){

    //Llamada incorrecta
    if(argc != 2){
        fprintf(stderr, "\nNumero de argumentos invalido ./ej1 <numero de hilos>\n");
        exit(EXIT_FAILURE);
    }

    //Definimos las variables
    int n=atoi(argv[1]);
    pthread_t hilos[n];
    srand(time(NULL));
    float total=0.0;
    

    //Creamos los hilos
    for(int i=0; i < n; i++){
        if(pthread_create(&hilos[i], NULL, funcHilos, NULL) != 0){
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
        total += devuelto->suma;
        printf("\n+ %f = %f\n", devuelto->suma, total);
        free(devuelto);
    }

    printf("\nSe han recogido todos los hilos y la suma es %d\n", total, n);
    exit(EXIT_SUCCESS);
}