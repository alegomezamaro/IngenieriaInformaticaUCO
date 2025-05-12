// 2. Realice un programa que cree un número N de hilos, donde N será un 
//    argumeto del programa principal.​ Se tendrán dos variables globales "par" 
//    e "impar" . A cada hilo se le pasará su índice (1,...N). 
//  - Cada hilo genera 100 valores aleatorios entre 0 y 10 que se añadirán a la 
//    varable par o impar dependiendo del índice del hilo. (Variable par si el índice 
//    es par . Variable impar si el índice es impar). El hilo devolverá la suma total 
//    de los número generados. Antes de finalizar el hilo duerme durante 10 
//    nanosegundos. 
//  - El padre comprobará que la suma devuelta por los hilos sea igual a la suma 
//    de las variables par e impar.

#include <stdio.h>  //Funciones de entrada/salida, como printf o perror
#include <stdlib.h> //exit, malloc o atoi
#include <string.h> //strerror
#include <errno.h> //Errores en la variable errno
#include <unistd.h> //fork, getpid, getppid, sleep, execl, execv...
#include <pthread.h> //Hilos y mutex
#include <time.h> //srand

//Mutex
int par = 0;
int impar = 0;
pthread_mutex_t mutex_par=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_impar=PTHREAD_MUTEX_INITIALIZER;

//Esctructura hilo
struct Hilo{
    int id;
    int suma;
};

//Generar hilos
void* sumaHilos(void* arg) {

    //Reservar memoria
    struct Hilo* hilo=(struct Hilo*)arg;
    hilo->suma = 0;

    //Generar 100 números aleatorios entre 0 y 10
    for(int i=0; i<100; i++){
        int aux=(int)rand()%11;
        hilo->suma+=aux;
    }

    printf("\nHilo %d= %d", hilo->id, hilo->suma);

    //Devolver el valor del hilo
    pthread_exit((void*)hilo);
}

int main(int argc, char *argv[]){
    if (argc!=2) {
        fprintf(stderr, "\nError al llamar a la función: ./ej2 <Numero de hilos>");
        exit(EXIT_FAILURE);
    }

    int num=atoi(argv[1]);
    pthread_t hebras[num];
    struct Hilo* hilo[num];
    srand(time(NULL));

    //Crear hilos
    for(int i=0; i<num; i++){
        hilo[i] = malloc(sizeof(struct Hilo));

        //Error al reservar la memoria
        if(hilo[i] == NULL){
            fprintf(stderr, "\nError al reservar memoria para el hilo %d\n", i);
            exit(EXIT_FAILURE);
        }

        //Llamamos a la función despues de asignarle un id (indice)
        hilo[i]->id = i+1;
        if (pthread_create(&hebras[i], NULL, sumaHilos, hilo[i]) != 0) {
            perror("\nError al crear el hilo\n");
            exit(EXIT_FAILURE);
        }
    }

    //Recoger los hilos
    for (int i=0; i<num; i++) {
        struct Hilo* hilo;

        //Se ha recogido correctamente?
        if (pthread_join(hebras[i], (void**)&hilo)!=0) {
            perror("\nError al esperar al hilo\n");
            exit(EXIT_FAILURE);
        }

        printf("\nPADRE -> Recogí el hilo %d con suma= %d", hilo->id, hilo->suma);

        //Exclusion mutua de los mutex
        //Par
        if((hilo->suma%2)==0){
            pthread_mutex_lock(&mutex_par);
            par += hilo->suma;
            pthread_mutex_unlock(&mutex_par);
        }
        //Impar
        else{
            pthread_mutex_lock(&mutex_impar);
            impar += hilo->suma;
            pthread_mutex_unlock(&mutex_impar);
        }

        //Liberar memoria del hilo
        free(hilo);
    }

    //Comprobar las sumas totales
    printf("\nResultados finales:");
    printf("\nSuma global PAR= %d", par);
    printf("\nSuma global IMPAR= %d\n", impar);

    //Destruir mutex
    pthread_mutex_destroy(&mutex_par);
    pthread_mutex_destroy(&mutex_impar);
}