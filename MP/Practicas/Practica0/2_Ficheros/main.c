//Ejemplo básico de programa con dos ficheros .c y un fichero .h
//PARA COMPILAR: gcc main.c funciones.c -o main.exe -Wall
//opción -Wall: muestra avisos con posibles fallos (recomendable usar)

#include <stdio.h>
#include "funciones.h"

int main()
{
   int numero;
   
   printf("\nNumero: ");
   scanf("%d", &numero);
    
   //En en lugar de un tipo boolean, en C se utiliza un entero
   //0 significa false
   //!=0 significa true

   if (esPar(numero))  
     printf("\n%d es par", numero);
   else
     printf("\n%d es impar", numero);
       
   return 0;
}
