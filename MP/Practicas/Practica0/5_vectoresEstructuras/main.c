//Ejemplo básico de vectores de enteros con dos ficheros .c y un fichero .h
//PARA COMPILAR: gcc main.c funciones.c -o main.exe -Wall
//opción -Wall: muestra avisos con posibles fallos (recomendable usar)

#include<stdio.h>
#include "funciones.h" //nuestros .h van con comillas dobles

int main()
{
   struct datos Alumnos[MAX_VECTOR];
   struct datos primero;
   int nEle, index;
   float edadMedia;
   
   printf("\nIndique longitud del vector (maximo: %d): ", MAX_VECTOR);
   scanf("%d", &nEle);
   getchar(); //quita el \n    
   
   rellenarVector(Alumnos, nEle);
   
   printf("\nEl vector relleno es el siguiente:\n");
   imprimirVector(Alumnos, nEle);
   
   index = primerNombre(Alumnos, nEle);
   //Podemos asignar dos estructuras directamente, sin necesidad de hacerlo campo a campo
   primero = Alumnos[index];
   
   edadMedia = calcularEdadMedia(Alumnos, nEle);
   
   printf("\n\nLa edad media es: %.3f", edadMedia);
   printf("\n\nNombre alfabeticamente mas bajo: <%s>", primero.nombre);
   
   
   
   return 0;
}
