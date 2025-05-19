/*
Implemente un programa en C usando tuberías similar a los existentes en los ficheros
pipe.c y pipe2.c, pero en este caso que un proceso genere dos numeros aleatorios flotantes
y envie la suma de ellos al otro proceso para que este muestre su resultado.

El proceso padre generara los numeros aleatorios y el hijo recibira la suma de ellos.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h> 
#include <string.h>
#include <time.h>
#include <sys/wait.h>

int main(){

    pid_t pid; //Variable que almacenara el PID del proceso
	int flag, status; //Sirve para obtener info
	int result; //Permite gestionar errores
	int fildes[2]; //Variable de la tuberia
	float random1;
	float random2;
	float sum;
	result=pipe(fildes); //Creacion de la tuberia
	srand(time(NULL)); //Inicializamos los numeros aleatorios

	if(status==-1){ //Comprobamos que la tuberia se ha creado correctamente

		printf("\nError en la creacion de la tuberia.\n");
		exit(1);
	}

    pid=fork(); //Creacion del proceso hijo

	switch(pid) {

        case -1: //Si hay un error al crear el proceso

	    	printf("No se ha podido crear el proceso hijo...\n");
	    	exit(EXIT_FAILURE);
            break;

	    case 0: //Proceso creado correctamente, lee

	    	printf("[HIJO]: Mi PID es %d y mi PPID es %d\n", getpid(), getppid()); //Imprimimos la información del proceso
	    	close(fildes[1]); //Cerramos el extremo de escritura
            result=read(fildes[0], &sum, sizeof(float)); //Leemos el mensaje

            if(result != sizeof(float)){ //Si el mensaje no tiene el tamaño correcto

	    		printf("\n[HIJO]: ERROR al leer de la tubería...\n");
	    		exit(EXIT_FAILURE);
	    	}

            printf("[HIJO]: El resultado de la suma leido de la tubería es: %.2f.\n", sum); //Imprimimos el valor enviado		
	    	close(fildes[0]);//Cerramos el extremo de lectura
			printf("[HIJO]: Tubería cerrada ...\n"); //Cerramos la tuberia
	    	break;

	    default: //Proceso padre, escribe

	    	printf("[PADRE]: Mi PID es %d y el PID de mi hijo es %d \n", getpid(),pid); //Imprimimos la información del padre
	    	close(fildes[0]); //Cerramos el extremo de lectura
            random1=(float)rand() / RAND_MAX * 100.0f; //Generacion de los numeros aleatorios
	    	random2=(float)rand() / RAND_MAX * 100.0f;
	    	sum=random1+random2; //Sumamos los números
            printf("[PADRE]: Escribo el resultado de la suma de los números aleatorios %.2f y %.2f en la tubería...\n", random1, random2); //Se escribe en la tuberia
	    	result=write(fildes[1], &sum, sizeof(int)); //Escribimos el mensaje

	    	if(result!=sizeof(int)){ //Comprobamos que el tamaño sea correcto

	    		printf("\n[PADRE]: ERROR al escribir en la tubería...\n");
	    		exit(EXIT_FAILURE);
	    	}

	    	close(fildes[1]); //Cerramos el extremo de escritura
	    	printf("[PADRE]: Tubería cerrada...\n");

			while((flag=waitpid(-1, &status, WUNTRACED | WCONTINUED))>0){ //Mientras el padre espere hijos

	            if(WIFEXITED(status)){ //El proceso a finalizado correctamente

	    	        printf("Proceso Padre, Hijo con PID %ld finalizado, status = %d\n", (long int)flag, WEXITSTATUS(status));
	            } 

	            else if(WIFSIGNALED(status)){ //El proceso ha finalizado por una señal

	    	        printf("Proceso Padre, Hijo con PID %ld finalizado al recibir la señal %d\n", (long int)flag, WTERMSIG(status));
	            }
				
				else if (WIFCONTINUED(status)){ //Hay un proceso parado
					
        			printf("Proceso Padre %d, hijo con PID %ld reanudado\n", getpid(), (long int)flag);
    			}
	        }

	        if(flag==(pid_t)-1 && errno==ECHILD){ //Si no hay que esperar más hijos

	            printf("Proceso Padre %d, no hay mas hijos que esperar. Valor de errno = %d, definido como: %s\n", getpid(), errno, strerror(errno));
	        }
			
			else{ //Si hay mas hijos que esperar

	            printf("Error en la invocacion de wait o waitpid. Valor de errno = %d, definido como: %s\n", errno, strerror(errno));
	            exit(EXIT_FAILURE);
	        }			 
		}
	
	exit(EXIT_SUCCESS);
}