//Ejemplo básico de vectores de enteros con dos ficheros .c y un fichero .h
//PARA COMPILAR: gcc main.c funciones.c -lm -std=c9x -Wall -o main.exe
//opcion -lm: porque se utiliza math.h
//opcion -std=c9x: para declarar variables dentro del for (ej. for (int i=0; <10; i++))
//opción -Wall: muestra avisos con posibles fallos (recomendable usar)

#include<stdio.h>
#include<math.h> //para usar la funcion pow
#include "funciones.h" //nuestros .h van con comillas dobles

int main()
{
   int Vector[MAX_VECTOR];
   int nEle;
   float media;
   
   printf("\nIndique longitud del vector (maximo: %d): ", MAX_VECTOR);
   scanf("%d", &nEle);  
   
   rellenarVector(Vector, nEle);
   
   printf("\nEl vector relleno es el siguiente:\n");
   imprimirVector(Vector, nEle);
   
   media = calcularMedia(Vector, nEle);  
   
   printf("\n\nLa media es: %.3f", media); //%.3f muestra solo tres decimales
   printf("\n\nLa media al cuadrado es es: %f", pow(media, 2));
   
   return 0;
}
