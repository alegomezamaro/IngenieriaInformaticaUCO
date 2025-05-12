#include <stdio.h>
#include "funciones.h"

int imprimirVector(int nEle, int* Vector);
int comprobar(int nEle, int* Vector, int* Correcto);

int main()
{
   int nEle = 5;
   char opcion;   
   
   float acumulada = 0;
   float pesoExamen=0.3;
   float puntosRecursividad=2.5;   
  
   int Vector1[]={-4,-7,-1,-9,-3};
   int Vector2[]={2,8,15,6,5};
   int Correcto[]={-4,2,-7,8,-1,15,-9,6,-3,5};
   int Resultado[10];   
  
   printf("\n\n-----------------------------");
   printf("\nEJERCICIO 2: RECURSIVIDAD");
   printf("\n\tTOTAL EJERCICIO (sobre 10): %.3f puntos", puntosRecursividad);
   printf("\n\tTOTAL NOTA FINAL(sobre 3) : %.3f puntos", pesoExamen*puntosRecursividad);   
   printf("\n-----------------------------");
   
   printf("\nEl ejercicio se esta evaluando...");    
   printf("\n\nVector 1: ");
   imprimirVector(nEle, Vector1);
   printf("\n\nVector 2: ");
   imprimirVector(nEle, Vector2);   
   
   ejercicio2(nEle, Vector1, Vector2, Resultado); 
   
   printf("\n\nVector RESULTADO");
   imprimirVector(nEle*2, Resultado); 
   if(!comprobar(nEle*2, Resultado, Correcto))
   {
       printf("\n\n\tINCORRECTO: puntuacion obtenida en recursividad: %.3f puntos", 0.0);
   }
   else
   {   
       printf("\n\nPREGUNTA: La funcion programada es recursiva?");   
       printf("\n\tRESPUESTA (S|N): ");
       scanf("%c", &opcion);
       getchar();
       if((opcion=='S')||(opcion=='s')) 
       {
          acumulada+=puntosRecursividad;
          printf("\n\tCORRECTO: Puntuacion obtenida en recursividad: %.1f puntos", puntosRecursividad);               
       }
       else
         printf("\n\n\tINCORRECTO: puntuacion obtenida en recursividad: %.3f puntos", 0.0);
   }    

   printf("\n\n-----------------------------");
   printf("\nEJERCICIO 2: RESUMEN");
   printf("\n\tEVALUACION EJERCICIO (sobre 10): %.3f puntos", acumulada);
   printf("\n\tTOTAL NOTA FINAL(sobre 3) : %.3f puntos", pesoExamen*acumulada);   
   printf("\n\tLa calificacion es PROVISIONAL y deber ser validada por la profesora");   
   printf("\n-----------------------------");   
   
   return 0;    
}



int imprimirVector(int nEle, int * Vector)
{
  
  int i;
  printf("\n\t(");
  for(i=0; i<nEle-1; i++)
  {
        printf(" %d,", Vector[i]);
  }
  printf(" %d)\n", Vector[i]);  
  
 return 1;
   
}


int comprobar(int nEle, int* Vector, int* Correcto)
{
    int correcto=1, i;
    
    for(i=0; (i<nEle) && correcto; i++)  
      if(Vector[i]!=Correcto[i])
         correcto=0;
    return correcto;                      
}

