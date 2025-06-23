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

   //Ponderacion de las calificaciones
   float pesoExamen=0.5;
   int valorExamen=10;   
   
   float puntosLectura=0.5+0.5; 
   float puntosMDinamica=1;
   float puntosParametrosReferencia=1;
   float puntosApartado1 = puntosLectura+puntosMDinamica+puntosParametrosReferencia;
   
   float puntosEscritura=1;
   float puntosApartado2 = puntosEscritura;
      
   float totalPuntos=puntosApartado1+puntosApartado2;
   
   float notaAcumulada = 0.0;
   char opcion;
   char fichAlumnos[]="alumnos.txt";
   char fichNotas[]="notas.txt";
   char fichResultado[]="resultado.txt";
  
   struct alumno Correctos[] ={{99999999, "Barbara Millicent Roberts", 9.133333}, 
                               {88888888, "Marge Bubie Simpson", 6.333333}, 
                               {77777777, "John A. Zoidberg", 3.333333},
                               {55555555, "Gordon Shumway", 3.666667},
                               {44444444, "Patricia Reichardt", 4.333333}};
                             
   struct alumno* Vector=NULL;
   int respuesta, nEleCorrecto=5;   
  
   printf("\n\n-----------------------------");
   printf("\nPUNTUACION DEL EJERCICIO: PUNTEROS, MEMORIA DINAMICA Y FICHEROS");
   printf("\n\t\tApartado1: %.3f\n\t\tApartado2: %.3f", puntosApartado1, puntosApartado2);
   printf("\n\tTOTAL EJERCICIO (sobre 10): %.3f puntos", totalPuntos);
   //printf("\n\tTOTAL NOTA FINAL(sobre %.0f) : %.3f puntos", pesoExamen*10, pesoExamen*totalPuntos);    
   printf("\n\nSi el programa funciona correctamente te dara \nla puntuacion obtenida al terminar la ejecucion");
   printf("\n-----------------------------");
   
   printf("\n\nEL APARTADO1 SE ESTA EVALUANDO...\n\n");    
   Vector = apartado1(&respuesta, fichAlumnos, fichNotas);
   if(respuesta!=nEleCorrecto)
      printf("\n\tINCORRECTO: La funcion no devuelve POR REFERENCIA el numero correcto de elementos del vector. Devuelve %d en lugar de %d.\n\tPuntuacion obtenida en apartado1: %.3f puntos", respuesta, nEleCorrecto, 0.0);                
   else
  {   
       notaAcumulada+=puntosParametrosReferencia;       
       int code = comprobarVector(nEleCorrecto, Vector, Correctos);
       if(code!=1)
       {
            printf("\n\tINCORRECTO: Los datos no se han cargado correctamente en memoria. Puntuacion obtenida en apartado1: %.3f puntos", 0.0);        
            if(code==-1)
              printf("\n\t\tCodigo de error: %d (No todos los dni estan en el vector)", code);
            if(code==-2)
              printf("\n\t\tCodigo de error: %d (El campo nombre no es correcto en algun elemento del vector)", code);         
            if(code==-3)
              printf("\n\t\tCodigo de error: %d (El campo media no es correcto en algun elemento del vector)", code);         
       }
       else
       {
          notaAcumulada+=puntosLectura+puntosMDinamica;       
          printf("\n\tCORRECTO: puntuacion obtenida en apartado1: %.3f puntos", puntosApartado1);
       }   
   
  }
   printf("\n\tNOTA_ACUMULADA: %.3f/%d", notaAcumulada, valorExamen);  
   

   printf("\n\nEL APARTADO2 SE ESTA EVALUANDO CON UN VECTOR DE PRUEBA POR SI SE HAN PRODUCIDO ERRORES EN EL APARTADO1...\n\n");     
   apartado2(nEleCorrecto, Correctos, fichResultado);
   printf("\nEstos son los datos que deben aparecer en tu fichero resultado (el formato puede variar):\n");
   imprimirVector(Correctos, nEleCorrecto);

   printf("\nEstos son los datos generados por tu código:\n");
   imprimirVector(Vector,respuesta);
   
   printf("\n\nRESPONDE ESTA PREGUNTA: Los datos del fichero de texto generado por tu codigo coinciden?");
   printf("\n\tRESPUESTA (S|N): ");
   scanf("%c", &opcion);
   getchar();
   if((opcion=='S')||(opcion=='s')) 
   {         
      notaAcumulada+=puntosApartado2;
      printf("\n\tCORRECTO: Puntuacion obtenida en apartado2: %.3f puntos", puntosApartado2);
   }
   else
   {
      printf("\n\tINCORRECTO: Puntuacion obtenida en apartado2: %.3f puntos", 0.0); 
   }           

   printf("\n\tNOTA_ACUMULADA: %.3f/%d", notaAcumulada, valorExamen);   

   //Comprobar NULL para que no rompa la ejecución si no se
   //hace el apartado de reserva de memoria
   //Vector deja ser ser null cuando se hace la llamada a ejercicio1
   //no sirve la comprobacion
   //if(Vector!=NULL)  
   //   free(Vector);      
  
   printf("\n\n-----------------------------");
   printf("\nNOTA OBTENIDA");
   printf("\n\tSobre 10: %.3f puntos", notaAcumulada);
   //printf("\n\tSobre %.0f: %.3f puntos", pesoExamen*10, pesoExamen*notaAcumulada);   
   printf("\n\tLa calificacion es PROVISIONAL y deber ser validada por la profesora");   
   printf("\n-----------------------------\n");   
  
   return 0;
}

