#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <omp.h>
#define LENGTH 100000000

int t; //Número de threads
int *array, count;
pthread_mutex_t m;

void* count3s_thread(void* arg){
    int id=*(int*)arg;
    int i;
    int length_per_thread=LENGTH/t;
    int start=id*length_per_thread;
    
    for(i=start; i<start+length_per_thread; i++){
        if(array[i] == 3){
            pthread_mutex_lock(&m);
            count++;
            pthread_mutex_unlock(&m); 
        }
    }
    return NULL;
}

int main(int argc, char *argv[]){

    if(argc>1)
        t=atoi(argv[1]);
    else
        t=4;

    array=(int*)malloc(LENGTH*sizeof(int));
    for(int i=0; i<LENGTH; i++)
        array[i]=rand()%101;

    pthread_t threads[t];
    int thread_ids[t];
    pthread_mutex_init(&m, NULL);
    double start_time = omp_get_wtime();
    for(int i=0; i<t; i++){
        thread_ids[i]=i;
        pthread_create(&threads[i], NULL, count3s_thread, &thread_ids[i]);
    }

    for(int i=0; i<t; i++){
        pthread_join(threads[i], NULL);
    }

    double end_time=omp_get_wtime();
    printf("Pthreads (Mutex) - Hilos: %d, Treses: %d\n", t, count);
    printf("Tiempo: %f milisegundos\n", (end_time - start_time)*1000);
    pthread_mutex_destroy(&m);
    free(array);
    return 0;
}