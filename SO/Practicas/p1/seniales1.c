#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

//Definimos el coportamiento de la función tratarsennal1. SIGUSR1 es la senial 10
void tratarSennal1(int senial)
{
  
  for (int i = 1; i <= 5; i++)
  {
    printf("Hijo %d, senial recibida %d - %s: i=%d\n", getpid(), senial, strsignal(senial), i);
    sleep(1);
  }
  
}

//Definimos el coportamiento de la función tratarsennal2. SIGUSR1 es la senial 12
void tratarSennal2(int senial)
{
  
  for (int i = 1; i <=5; i++)
  {
    printf("Hijo %d, senial recibida %d - %s: i=%d\n", getpid(), senial, strsignal(senial), i);
    sleep(1);
  }

}

int main()
{
  int n,status; //Creamos la variable que almacena el número de hijos y la que almacena el estado de salida del hijo
  pid_t pid, childpid; //Estas variables almacenan el id de los procesos hijos. 
  //Pid almacena el valor devuelto al padre tras el fork y chilpid el valor devuelto al padre por la función wait cuando termina de esperar al hijo 
  
  printf("Soy %d, el padre de todos\n", getpid()); //El proceso padre imprime su id  
  
  pid = fork(); // Aqúi el proceso tiene su hijo. En el padre pid valdrá el id del hijo y en el hijo pid valdrá 0
  switch(pid) //En base al valor de pid cada proceso ejecutará una función
  {
    case 0: //El fork se ha realizado corractamente
      signal(SIGUSR1, tratarSennal1); //Le decimos al hijo que ejecute tratarSennal1 cuando reciba esta señal
      signal(SIGUSR2, tratarSennal2); //Le decimos al hijo que ejecute tratarSennal2 cuando reciba esta señal
      
      printf("Soy %d, el hijo del proceso %d. Pasando a bloqueado...\n", getpid(), getppid()); //El hijo se identifica 
      pause();
      exit(EXIT_SUCCESS);
      
    case -1: //Ha ocurrido un error al realizar el fork
      printf("Error al crear el proceso hijo\n"); //Se informa al usuario
      exit(EXIT_FAILURE); //Indica que ha ocurrido un fallo en la ejecución
    
    default:
      
      sleep(2); //Para que le de tiempo al hijo a ejecutar los signal()
      
      printf("Soy %d, el padre. Enviando SIGUSR1...,\n", getpid());
      kill(pid, SIGUSR1);//El padre le manda la primera señal al hijo
      
      sleep(1);
      printf("Soy %d, el padre. Enviando SIGUSR2...,\n", getpid());
      kill(pid, SIGUSR2);//El padre le manda la segunda señal al hijo
       
      sleep(1); 
      printf("Soy %d, el padre. Enviando SIGUSR2...,\n", getpid());
      kill(pid, SIGUSR2);//El padre le manda la segunda señal al hijo
      
  }

   printf("Esperando a que acabe mi hijo\n");
  //ESTE CODIGO LO EJECUTARA SOLAMENTE EL PADRE.
  while ( (childpid=waitpid(-1, &status, WUNTRACED | WCONTINUED)) > 0 )//Si lo hacemos así en vez de con wait podemos saber si el proceso ha sido pausado y poniendo -1 en el primer parametro de waitpid esperamos a cualquier hijo
	{//Este bucle se repetirá mientas haya hijos que esperar cuando no haya mas wait devolverá -1
		if (WIFEXITED(status)) 
		{//Entrará en el caso de que el hijo haya finaizado correctamente ya que WIFEXITED(status) devolverá true
			printf("Proceso padre %d, hijo con PID %ld finalizado, status = %d\n", getpid(), (long int)childpid, WEXITSTATUS(status));
		} 
		else if (WIFSIGNALED(status))
		{//Entrará en el caso de que el proceso haya finalizado debido a una señar externa ya sea de finalizar o matar 
			printf("Proceso padre %d, hijo con PID %ld finalizado al recibir la señal %d\n", getpid(), (long int)childpid, WTERMSIG(status));
		}//La macro WTERMSIG nos dice que señal ha sido la que ha recibido el proceso que ha producido que acabe 
	}
	if (childpid==(pid_t)-1 && errno==ECHILD) 
	{//Entra cuando vuelve al while y no hay más hijos que esperar porque en ese caso chilpid valdrá -1 y erno 10 que es el valor que devuelce ECHILD cuando no hay mas procesos hijo
		printf("Proceso padre %d, no hay mas hijos que esperar. Valor de errno = %d, definido como: %s\n", getpid(), errno, strerror(errno));
	}	//strerror devuelve una cadena de caracteres que nos permite identificar el valor de la variable errno
	else
	{//Solo entra si se ha producido un error con wait 
		printf("Error en la invocacion de wait o waitpid. Valor de errno = %d, definido como: %s\n", errno, strerror(errno));
		exit(EXIT_FAILURE); //Acaba el proceso padre con error
	} 
  exit(EXIT_SUCCESS); //Como todo ha ido bien el proceso padre acaba exitosamente
}
