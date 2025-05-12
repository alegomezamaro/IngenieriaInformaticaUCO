/*
Este programa muestra la implementación del problema lectores-escritores,
donde hay 2 lectores y 2 escritores (prioridad a los lectores) y un buffer
con un solo dato que se va incrementando.

Este programa no posee el adecuado control de errores a partir de la documentación
disponible en OpenGroup. Se deja para el lector la ampliación del ejercicio para mejorar
el control de errores.
*/

#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h>

//Simula las veces que cada lector y escritor intentaran leer y escribir
#define DATOS_A_ESCRIBIR_LEER 5
//Numero de lectores
#define NUM_LECTORES 2
//Numero de escritores 
#define NUM_ESCRITORES 2 


/*Todo lo que hay a continuacion se podria reservar en el monticulo desde
el main usando mallloc(), pruebe a hacer el ejercicio de esta manera*/

/* Esta es la variable de la que no se puede leer y escribir a la vez */
int dato = 0; 
/* numero de lectores en SC */
int cuentalect = 0;
/* semaforo general ( o binario) para controlar el acceso cuentalect */ 
pthread_mutex_t x; 
/* semaforo general para controlar el acceso a dato */
sem_t sc; 

void * Lector(void * arg) 
{
    //Complete el manejo de errores en toda la funcion
    //....

    for(int i=0; i < DATOS_A_ESCRIBIR_LEER; i++ ) 
    {
        pthread_mutex_lock(&x); 
        
        cuentalect = cuentalect + 1; 
        if (cuentalect == 1)
            sem_wait(&sc); 
        
        pthread_mutex_unlock(&x);

        /* leer dato */
        printf("Lector %lu, valor leido = %d\n", (unsigned long)pthread_self(), dato); 
        
        pthread_mutex_lock(&x); 
        
        cuentalect = cuentalect - 1; 
        if (cuentalect == 0) 
            sem_post(&sc); 
        
        pthread_mutex_unlock(&x);        
    }  
  
    pthread_exit(NULL); 
}

void * Escritor(void * arg) 
{
    //Complete el manejo de errores en toda la funcion
    //....

    for(int i=0; i < DATOS_A_ESCRIBIR_LEER; i++ ) 
    {
        sem_wait(&sc); //No más de un escritor a la vez
        
        dato = dato + 1; /* modificar el recurso */
        printf("Escritor %lu, incrementando a valor = %d\n", (unsigned long) pthread_self(), dato); 
        
        sem_post(&sc);
    }
    pthread_exit(NULL); 
}


int main(void) 
{
    //Complete el manejo de errores en todo el main()...
    
    int i;
    pthread_t thlectores[NUM_LECTORES], thescritores[NUM_ESCRITORES];
    //Para proteger el dato que se lee o se escribe
    //sem_init(&sc, 0, 1);   
    pthread_mutex_init(&x,NULL); //Binario inicializado a 1
    //Para actualizar correctamente el numero de lectores que hay en SC
    sem_init(&sc, 0, 1); 
    
    for(i=0; i < NUM_LECTORES; i++ ) 
        pthread_create(&thlectores[i], NULL, Lector, NULL); 
    for(i=0; i < NUM_ESCRITORES; i++ ) 
        pthread_create(&thescritores[i], NULL, Escritor, NULL); 
    
    for(i=0; i < NUM_LECTORES; i++ )
        pthread_join(thlectores[i], NULL);
    for(i=0; i < NUM_ESCRITORES; i++ ) 
        pthread_join(thescritores[i], NULL);
    
    /* eliminar todos los semaforos */ 
    pthread_mutex_destroy(&x); 
    sem_destroy(&sc);
}
