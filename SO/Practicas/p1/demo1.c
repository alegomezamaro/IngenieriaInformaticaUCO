#include <sys/types.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <errno.h>
#include <sys/wait.h>


int main(void) 
{
    pid_t hijo_pid, childpid; 
    int status;
    
    hijo_pid= fork(); 
    
    if (hijo_pid == -1) 
    {
      perror("fork error");
      printf("errno value= %d\n", errno); 
      exit(EXIT_FAILURE); //exit(-1); //Necesaria la librería <stdlib.h> 
    }
    else if (hijo_pid == 0) //hijo
    {
      printf("Soy el hijo, mi pid es: %d\n", getpid());
      
      exit(EXIT_SUCCESS); //exit(0);
    }
    else /* padre */ 
    {
      printf("Padre con pid: %d, el pid de mi hijo es: %d\n", getpid(),hijo_pid); 

      childpid=wait(&status);

      if(childpid>0)
      {
        if (WIFEXITED(status)) 
        {
            printf("Soy el padre, hijo %d recogido, status=%d\n",childpid, WEXITSTATUS(status));
        } 
        else if (WIFSIGNALED(status)) 
        {
            printf("Soy el padre, hijo %d matado (signal %d)\n", childpid, WTERMSIG(status));
        } 
      }
      else 
      {
         printf("Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");
         exit(EXIT_FAILURE);
      } 
      exit(EXIT_SUCCESS); //exit 0; return 0;
   }
}