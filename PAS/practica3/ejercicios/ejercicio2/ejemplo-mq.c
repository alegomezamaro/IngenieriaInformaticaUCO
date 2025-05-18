/*
El proceso hijo generara los numeros aleatorios y el padre recibira la suma de ellos. 
*/

#include <errno.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define MAX_SIZE 5
#define QUEUE_NAME "/una_cola"

int main() {

    mqd_t mq; //Variable cola
    char buffer[MAX_SIZE]; //Buffer
    struct mq_attr attr; //Atributos de la cola
    char queue_name[100]; //Almacena el nombre de la cola
    int resultado; //Resultado de las operaciones
    pid_t rf, flag; //Variable que almacenara el PID del proceso
    int status; //Numero aleatorio a generar
    int numeroAleatorio; //Inicializar los atributos de la cola
    attr.mq_maxmsg = 10; //Maximo número de mensajes
    attr.mq_msgsize = MAX_SIZE; //Maximo tamaño de un mensaje (incluir el '/0')
    sprintf(queue_name, "%s-%s", QUEUE_NAME, getenv("USER")); //Nombre para la cola. Al concatenar el login, sera unica en un sistema compartido.
    rf = fork(); //Creación de un proceso hijo

    switch (rf){

        case -1: //Si hay un error al crear el proceso

            printf("No he podido crear el proceso hijo \n");
            exit(1);

        case 0: //Proceso creado correctamente, se encargará de escribir.

            mq = mq_open(queue_name, O_CREAT | O_WRONLY, 0644, &attr); //Creamos la tuberia
            //Crearla si no existe y solo escritura
            printf("[HIJO]: El nombre de la cola es: %s\n", queue_name);
            printf("[HIJO]: El descriptor de la cola es: %d\n", (int)mq);

            if (mq == -1){ //La cola no se ha abierto correctamente

                perror("[HIJO]: Error en la apertura de la cola");
                exit(-1);
            }

            printf("[HIJO]: Mi PID es %d y mi PPID es %d\n", getpid(), getppid()); //IMprimimos la información del proceso
            srand(time(NULL));
            numeroAleatorio = rand() % 5000; //Generamos un número aleatorio
            sprintf(buffer, "%d", numeroAleatorio); //Añade el '/0' a numeroAleatorio
            printf("[HIJO]: Generado el mensaje \"%s\"\n", buffer);
            resultado = mq_send(mq, buffer, MAX_SIZE, 0); //Enviamos el mensaje
            printf("[HIJO]: Enviando mensaje...\n");


            if (resultado == -1){ //Error al enviar el mensaje

                perror("[HIJO]: Error al enviar mensaje");
                exit(-1);
            }

            printf("[HIJO]: Mensaje enviado!\n");

            if (mq_close(mq) == -1){ //Si la cola no se ha cerrado correctamente

                perror("[HIJO]: Error cerrando la cola");
                exit(-1);
            }

            printf("[HIJO]: Cola cerrada.\n");
            break;

        default: //Proceso padre, solo se encargará de leer

            mq = mq_open(queue_name, O_CREAT | O_RDONLY, 0644, &attr); //Abrimos la cola
            printf("[PADRE]: El nombre de la cola es: %s\n", queue_name);
            printf("[PADRE]: El descriptor de la cola es:%d\n", (int)mq);

            if (mq == -1){ //Si la cola no se ha abierto correctamente

                perror("[PADRE]: Error en la apertura de la cola");
                exit(-1);
            }

            printf("[PADRE]: Mi PID es %d y el PID de mi hijo es %d \n", getpid(), rf);
            printf("[PADRE]: Recibiendo mensaje (espera bloqueante)...\n");
            resultado = mq_receive(mq, buffer, MAX_SIZE, NULL); //Recibimos el mensaje

            if (resultado <= 0){ //Si no se recibe el mensaje correctamente

                perror("[PADRE]: Error al recibir el mensaje");
                exit(-1);
            }

            printf("[PADRE]: El mensaje recibido es \"%s\"\n", buffer);

            if (mq_close(mq) == -1){ //Si la cola no se ha cerrado correctamente

                perror("[PADRE]: Error cerrando la cola");
                exit(-1);
            }

            printf("[PADRE]: Cola cerrada.\n");

            if (mq_unlink(queue_name) == -1){ //Si la cola no se elimina correctamente

                perror("[PADRE]: Error eliminando la cola");
                exit(-1);
            }
            
            while ((flag = wait(&status)) > 0){ //Espera del padre a los hijos

                if (WIFEXITED(status)){ //El proceso a finalizado correctamente

                    printf("Proceso Padre, Hijo con PID %ld finalizado, status = %d\n", (long int)flag, WEXITSTATUS(status));
                }
                
                else if (WIFSIGNALED(status)){ //EL proceso ha finalizado por una señal
                
                    printf("Proceso Padre, Hijo con PID %ld finalizado al recibir la señal %d\n", (long int)flag, WTERMSIG(status));
                }
            }

            if (flag == (pid_t)-1 && errno == ECHILD){ //Si no hay que esperar más hijos

                printf("Proceso Padre %d, no hay mas hijos que esperar. Valor de errno = %d, definido como: %s\n", getpid(), errno, strerror(errno));
            }
            
            else{ //Si hay mas hijos que esperar

                printf("Error en la invocacion de wait o waitpid. Valor de errno = %d, definido como: %s\n", errno, strerror(errno));
                exit(EXIT_FAILURE);
            }
        }

    exit(0);
}