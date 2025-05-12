#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <signal.h>

int par=0;
int impar=0;

pthread_mutex_t semaforo_par;
pthread_mutex_t semaforo_impar;

void * Suma(int *n){

    int suma =0;

    if( ((*n)%2) == 0){

        for (int i = 0; i < 5; i++)
        {
            int num = (rand()%10) +1;
            suma = suma + num;

            if(pthread_mutex_lock(&semaforo_par) != 0){

                perror("ERROR en pthread_mutex_lock\n");
                printf("errno value = %d\n",errno);
                exit(EXIT_FAILURE);

            }

            par=par+num;

            if(pthread_mutex_unlock(&semaforo_par) != 0){

                perror("ERROR en pthread_mutex_unlock\n");
                printf("errno value = %d\n",errno);
                exit(EXIT_FAILURE);

            }
        }
        
    }else{

        for (int i = 0; i < 5; i++)
        {
            int num = (rand()%10) +1;
            suma = suma + num;

            if(pthread_mutex_lock(&semaforo_impar) != 0){

                perror("ERROR en pthread_mutex_lock\n");
                printf("errno value = %d\n",errno);
                exit(EXIT_FAILURE);

            }

            impar=impar+num;

            if(pthread_mutex_unlock(&semaforo_impar) != 0){

                perror("ERROR en pthread_mutex_unlock\n");
                printf("errno value = %d\n",errno);
                exit(EXIT_FAILURE);

            }
        }

    }

    printf("[HILO %d] -- Soy la hilo %lu y la suma que he realizado es %d\n",(*n),pthread_self(), suma);
    printf("\n");

    int *envio=(int *)malloc(sizeof(int));
    *envio = suma;
    pthread_exit((void *) envio);


}

int main(int argc, char **argv){


    if(argc != 2){
        perror("ERROR; Debe de seguir la siguiente estructura ./ejecutable.out n_hilos\n");
        printf("errno value = %d\n",errno);
        exit(EXIT_FAILURE);
    }

    int n_hilos = atoi(argv[1]);

    srand(time(NULL));

    pthread_t idhilos[n_hilos];

    if(pthread_mutex_init(&semaforo_par,NULL)!=0){
        perror("ERROR al iniciar el semaforo\n");
        printf("errno value = %d\n",errno);
        exit(EXIT_FAILURE);
    }

    if(pthread_mutex_init(&semaforo_impar,NULL)!=0){
        perror("ERROR al iniciar el semaforo\n");
        printf("errno value = %d\n",errno);
        exit(EXIT_FAILURE);
    }

    int indice[n_hilos];

    for (int i = 0; i < n_hilos; i++)
    {
        indice[i]=i+1;
        if(pthread_create(&idhilos[i],NULL,(void *) Suma, &indice[i]) != 0){
            
            perror("ERROR pthread_create\n");
            printf("errno value = %d\n",errno);
            exit(EXIT_FAILURE);

        }
    }
    
    int *recogida;

    for (int i = 0; i < n_hilos; i++)
    {

        if(pthread_join(idhilos[i],(void **)&recogida) != 0){
            
            perror("ERROR pthread_create\n");
            printf("errno value = %d\n",errno);
            exit(EXIT_FAILURE);

        }

        printf("[MAIN] -- El hilo %lu devolvio el valor de la suma %d\n", idhilos[i],(*recogida));

    }

    printf("\n");
    printf("[MAIN] -- Valor de la variable compartida par es: %d\n",par);
    printf("[MAIN] -- Valor de la variable compartida impar es: %d\n",impar);

    free(recogida);


    if(pthread_mutex_destroy(&semaforo_par)!=0){
        perror("ERROR al iniciar el pthread_mutex_destroy\n");
        printf("errno value = %d\n",errno);
        exit(EXIT_FAILURE);
    }

        if(pthread_mutex_destroy(&semaforo_impar)!=0){
        perror("ERROR al iniciar el pthread_mutex_destroy\n");
        printf("errno value = %d\n",errno);
        exit(EXIT_FAILURE);
    }




    exit(EXIT_SUCCESS);
}