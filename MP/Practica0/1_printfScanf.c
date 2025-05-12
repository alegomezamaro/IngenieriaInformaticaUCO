//Ejemplo basico de printf y scanf
//int =>  %d, %i
//float => %f
//char => %c
//cadena => %s
//long => %ld
//double => %lf    

//PARA COMPILAR: gcc printfScanf.c -o printfScanf.exe -Wall
//opción -Wall: muestra avisos con posibles fallos (recomendable usar)

#include <stdio.h>

int main()
{
 
  int entero;
  float real;
  
  printf("\nValor entero: ");
  scanf("%d", &entero);
  printf("\n\t=>entero: %d", entero);
     
 
  printf("\nValor real: ");
  scanf("%f", &real);
  printf("\n\t=>real: %.3f", real); //%.3f muestra el dato con 3 decimales
  
  printf("\n%d*%d=%d", entero, entero, entero*entero);
    
  return 0;
}
