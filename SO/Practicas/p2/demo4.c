#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <unistd.h>

//Prototipos
void * mifuncion(void *);
void miFuncion2(); 

//Hilo principal
int main (void) 
{
    pthread_t tid; 
	char micadena[11] = "Hola mundo";

    printf("Hilo principal. Se va a crear un hilo...\n");
    if( pthread_create(&tid, NULL, mifuncion, (void *) micadena) )
    {
	  fprintf(stderr, "Error creating thread\n");
	  exit(EXIT_FAILURE); 
	}

    /*Si comentamos la siguiente linea, puede que a la hebra no le de tiempo a ejecutarse
    ni siquiera parcialmente, de manera que el main() terminará y con el todas las hebras 
    asociadas a este proceso*/ 
    printf("Hilo principal. Esperando finalizacion de hilo creado...\n");
    if( pthread_join(tid, NULL) )
	{
	  fprintf(stderr, "Error joining thread\n");
	  exit(EXIT_FAILURE);  
	}

    printf("Hilo principal finalizado...\n");
    exit(EXIT_SUCCESS);
}


//Función asignada a hilo
void *mifuncion(void *arg) 
{
    char *argu;
    
    printf("Hilo hijo %lu ejecutando...\n", pthread_self());
    argu = (char *) arg; //Casting a char del parámetro de entrada. 

	printf("Hilo hijo, valor recibido: %s\n", argu);
    
    printf("Hilo hijo invocando a subrutina....\n"); 
    miFuncion2();

    /*No se llegará a ejecutar de aquí hasta el final de esta función*/ 
    printf("Soy el hilo. He salido de la llamada a subrutina\n"); 
    pthread_exit(NULL);
}

//Esta funcion no es un hilo, es una subrutina
void miFuncion2() 
{
    printf("Soy el hilo hijo creado y estoy dentro de una subrutina para invocar a pthread_exit()...\n");
    pthread_exit(NULL); 
}
