#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void manejador(int sig)
{
    printf("Hilo %lu recibió señal %d\n", pthread_self(), sig);
    pthread_exit(NULL);
}

void * hilo(void * arg)
{
    printf("Soy el hilo %lu\n", pthread_self());
    
    if (signal(SIGTERM, manejador) == SIG_ERR)
    {
        fprintf(stderr, "Error en signal\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        printf("Hilo %lu en ejecución\n", pthread_self());
        sleep(1);
    }
}

int main(int argc, char const *argv[])
{
    // Se podría establecer el manejador de señal aquí
    // en lugar de hacerlo en el hilo
    // if (signal(SIGTERM, manejador) == SIG_ERR)
    // {
    //     fprintf(stderr, "Error en signal\n");
    //     exit(EXIT_FAILURE);
    // }
    
    pthread_t thread;
    if (pthread_create(&thread, NULL, hilo, NULL))
    {
        fprintf(stderr, "Error creando hilo\n");
        exit(EXIT_FAILURE);
    }

    sleep(5);
    if (pthread_kill(thread, SIGTERM))
    {
        fprintf(stderr, "Error matando hilo\n");
        exit(EXIT_FAILURE);
    }

    if (pthread_join(thread, NULL))
    {
        fprintf(stderr, "Error en pthread_join\n");
        exit(EXIT_FAILURE);
    }

    sleep(3);

    printf("Hilo principal terminado\n");

    return 0;
}
