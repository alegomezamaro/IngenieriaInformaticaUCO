/*------------------------------------------------------------------*/
//                 NO MODIFICAR ESTE FICHERO
/*------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "examen.h"

int main()
{
   float pesoExamen=0.5;
   int valorExamen=10;
   
   float puntosOrdenacionA=0.75;
   float puntosOrdenacionD=0.75;
   float puntosPteroFuncion=1.25;   
   float puntosApartado1=puntosOrdenacionA+puntosOrdenacionD+puntosPteroFuncion;
   
   float puntosRecursividad=1.25;
   float puntosApartado2=puntosRecursividad;
   
   float totalEjercicio = puntosOrdenacionA+puntosOrdenacionD+puntosPteroFuncion+puntosRecursividad;  

   float acumulada = 0;
   struct nomina Vector[6];
   int nEle = 6;
   char opcion;   
   int orden=0;  

   
   rellenarVector(nEle, Vector);   
   
   printf("\n\n-----------------------------");
   printf("\nPUNTUACION DEL EJERCICIO: ORDENACION, PUNTEROS A FUNCIONES Y RECURSIVIDAD");
   printf("\n\tApartado1: %.3f\n\t\tordenacion ascendente %.3f puntos\n\t\tordenacion descendente: %.3f puntos\n\t\tpunteros a funciones: %.3f puntos", puntosApartado1, puntosOrdenacionA, puntosOrdenacionD, puntosPteroFuncion);
   printf("\n\tApartado2: %.3f\n\t\trecursividad: %.3f", puntosApartado2, puntosRecursividad);
   printf("\n\tTOTAL EJERCICIO (sobre 10): %.3f puntos", totalEjercicio);   
   //printf("\n\tTOTAL NOTA FINAL(sobre %.0f) : %.3f puntos", pesoExamen*10, pesoExamen*totalEjercicio);   
   printf("\n\nSi el programa funciona correctamente te dara \nla puntuacion obtenida al terminar la ejecucion");   
   printf("\n-----------------------------");
   
   printf("\n\nEL APARTADO1 SE ESTA EVALUANDO...\n\n");    
   printf("\nVector relleno SIN ORDENAR: ");
   imprimirVector(nEle, Vector);
   apartado1(nEle, Vector, 0);  
   printf("\n\nEste el vector ORDENADO ascendentemente por SALARIO NETO con TU funcion de ordenacion: ");
   imprimirVector(nEle, Vector);   
   int ordenCodigosA[]={4,9,3,8,1,7};
   char* ordenNombresA[]={"Ana Maria Segura", "Gonzalo Martinez", "Lucas Lopez", "Esperanza Garcia", "Luis Alonso", "Francisco Rivera"};
   
   if(comprobarOrdenacion(nEle, Vector, ordenCodigosA, ordenNombresA)==0)
   {
       printf("\n\n\tINCORRECTO: puntuacion obtenida en ordenacion ascendente: %.3f puntos", 0.0);
   }
   else
   {
       acumulada+=puntosOrdenacionA;
       orden=1;
       printf("\n\n\tCORRECTO: puntuacion obtenida en ordenacion ascendente: %.3f puntos", puntosOrdenacionA);
   }
   printf("\n\tACUMULADA: %.3f/%d", acumulada, valorExamen);  

   apartado1(nEle, Vector, 1);  
   printf("\n\nEste el vector ORDENADO descendentemente por NOMBRE con TU funcion de ordenacion: ");
   imprimirVector(nEle, Vector);  
   int ordenCodigosD[]={9,8,7,4,3,1};
   char* ordenNombresD[]={"Luis Alonso", "Lucas Lopez", "Gonzalo Martinez", "Francisco Rivera", "Esperanza Garcia", "Ana Maria Segura"};    
   
   if(comprobarOrdenacion(nEle, Vector, ordenCodigosD, ordenNombresD)==0)
   {
       printf("\n\n\tINCORRECTO: puntuacion obtenida en ordenacion descendente: %.3f puntos", 0.0);
   }
   else
   {
       acumulada+=puntosOrdenacionD;
       orden=1;
       printf("\n\n\tCORRECTO: puntuacion obtenida en ordenacion descendente: %.3f puntos", puntosOrdenacionD);
   }       
   printf("\n\tACUMULADA: %.3f/%d", acumulada, valorExamen);    
 
   if(orden)
   {       
       printf("\n\n\tRESPONDE ESTA PREGUNTA: Tu funcion de ordenacion acepta como parametro un puntero a una funcion de comparacion?");
       printf("\n\tO has utilizado el quicksort de C?");
       printf("\n\tRESPUESTA (S|N): ");
       scanf("%c", &opcion);
       getchar();
       if((opcion=='S')||(opcion=='s')) 
       {         
          acumulada+=puntosPteroFuncion;
          printf("\n\n\tCORRECTO: Puntuacion obtenida en punteros a funciones: %.3f puntos", puntosPteroFuncion);
       }
       else
       {
          printf("\n\n\tINCORRECTO: Puntuacion obtenida en punteros a funciones: %.3f puntos", 0.0); 
       }           
   }
   else
   {
      printf("\n\n\tINCORRECTO: Puntuacion obtenida en punteros a funciones: %.3f puntos", 0.0); 
   }
   
   printf("\n\tACUMULADA: %.3f/%d", acumulada, valorExamen);    

   printf("\n\nEL APARTADO2 SE ESTA EVALUANDO...\n\n");      
   printf("\n\tRESPONDE ESTA PREGUNTA: La funcion programada para contar en el vector es RECURSIVA?");   
   printf("\n\tRESPUESTA (S|N): ");
   scanf("%c", &opcion);
   getchar();
   if((opcion=='S')||(opcion=='s')) 
   {                                    
      rellenarVector(nEle, Vector);    
      printf("\n\nEste es el vector que tu funcion recursiva tiene que imprimir: ");
      imprimirVector2(nEle, Vector);
      printf("\n\nEste es el vector impreso con TU funcion RECURSIVA:\n");                                          
      apartado2(nEle, Vector);
      printf("\n\nRESPONDE ESTA PREGUNTA: Se visualizan correctamente en orden directo todos los elementos del vector? (el formato puede variar)");                     
      printf("\n\tRESPUESTA (S|N): ");
      scanf("%c", &opcion);
      getchar();
      if((opcion=='S')||(opcion=='s')) 
      {
         acumulada+=puntosRecursividad;
         printf("\n\n\tCORRECTO: Puntuacion obtenida en recursividad: %.3f puntos", puntosRecursividad);               
      }  
      else
         printf("\n\n\tINCORRECTO: puntuacion obtenida en recursividad: %.3f puntos", 0.0);

   }
   else
         printf("\n\tINCORRECTO: puntuacion obtenida en recursividad: %.3f puntos", 0.0);

  
   printf("\n\tACUMULADA: %.3f/%d", acumulada, valorExamen);   
  
   printf("\n\n-----------------------------");
   printf("\nNOTA OBTENIDA");
   printf("\n\tSobre 10: %.3f puntos", acumulada);
   //printf("\n\tSobre %.0f:  %.3f puntos", pesoExamen*10, pesoExamen*acumulada);
   printf("\n\tLa calificacion es PROVISIONAL y deber ser validada por la profesora");   
   printf("\n-----------------------------\n");   
   
   return 0;    
}


