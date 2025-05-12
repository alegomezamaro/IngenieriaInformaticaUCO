//Ejemplo básico de trabajo con cadenas de caracteres
//PARA COMPILAR: gcc cadenas.c -o cadenas.exe -Wall
//opción -Wall: muestra avisos con posibles fallos (recomendable usar)

#include <string.h> //librería con funciones de cadenas
#include <stdio.h>
#include <ctype.h> //para usar toupper
#define TAM_MAX 100 // definicion de una constante

int main()
{
	//Una cadena es un vector de caracteres terminado en '\0'
	char nombreApe[TAM_MAX]; //declara vector de caracteres vacio, NO es una cadena
	char cadena[TAM_MAX]="soy una cadena"; //declara e inicializa una cadena, las "" implican un '\0' al final
	int i;
	
	//escribir una cadena, recomendable poner los <> para ver si tiene basura al final
	printf("\ncadena: <%s>", cadena);	
	
	//rellenar una cadena
  
	// opcion A - para de leer cuando encuentra espacio en blanco
    //scanf %s no acepta espacios en blanco	
    printf("\nEscriba nombre (no puede contener espacios en blanco o fallará): ");         
	scanf("%s", nombreApe);
    printf("nombreApe con scanf %%s es: <%s>\n", nombreApe);
    getchar(); //scanf no quita el \n del buffer de entrada => limpia \n

    //opcion B - scanf %100[^\n] si acepta espacios en blanco, 100 es TAM_MAX
	printf("\nEscriba nombre y apellidos: ");         
    scanf("%100[^\n]", nombreApe);
    printf("nombreApe con scanf %%100[^\\n] es: <%s>\n", nombreApe);
    getchar();  //scanf no quita el \n del buffer de entrada => getchar para limpiar \n  
	
	//opcion C - fgets
	printf("\nEscriba nombre y apellidos: "); 
    fgets(nombreApe, TAM_MAX, stdin);
    if(nombreApe[strlen(nombreApe)-1]=='\n')
           nombreApe[strlen(nombreApe)-1]='\0';
    printf("nombreApe con fgets es: <%s>\n", nombreApe);
    //fgets si quita el \n del buffer de entrada => no es necesario getchar 

    //opcion D - puede dar warning el compilador    
	printf("\nEscriba nombre y apellidos: "); 
	gets(nombreApe);		
    printf("nombreApe con gets es: <%s>\n", nombreApe);

	//longitud de una cadena
	printf("\nLa longitud de <%s> es: %d", cadena, strlen(cadena));
	
	//recorrer una cadena ej. pasar a mayusculas
	for(i=0; i<strlen(cadena); i++)
	{
		cadena[i]=toupper(cadena[i]); //hay que incluir ctype.h
	}
	printf("\ncadena: <%s>", cadena);
	
	//manipular cadena elemento a elemento
	cadena[0]='s';	
	cadena[1]='o';	
	cadena[2]='l';	
	cadena[3]='\0';	
	printf("\ncadena: <%s>", cadena);

    //copiar una cadena en otra cadena, no se puede usar el operador de asignación
    strcpy(nombreApe, cadena); 
    
	//comparar cadenas
	if(strcmp(nombreApe, cadena)==0) //las cadenas  son iguales
	  printf("\nLas cadenas <%s> y <%s> son iguales", nombreApe, cadena);	
	
	return 0;
}


