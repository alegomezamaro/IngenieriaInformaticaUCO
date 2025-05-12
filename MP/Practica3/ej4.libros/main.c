#include "macros.h"
#include "funciones.h"

/*
Construye un programa que gestione mediante ficheros de texto el stock de libros de una librería.
Para cada libro se almacenarán tres líneas en un fichero de texto (stock):
- en la primera línea el título,
- en la segunda línea el autor,
- y en la tercera línea el precio y las unidades disponibles del libro.
El programa contará con un menú que permitirá realizar las siguientes operaciones:
- Comprobar la existencia de un determinado libro en el stock buscando por su título.
- Introducir un nuevo libro en el stock.
- Contar el número de libros (títulos) diferentes que hay en el stock. Considera que no puede
haber títulos de libros repetidos en el fichero.
- Listar los libros en el stock almacenándolos previamente en un vector dinámico con la
siguiente estructura:
	struct libro {
		char titulo[100];
		char autor[50];
		float precio;
		int unidades;
	}
Vender n unidades de un libro buscándolo por su título. Si hay menos de n unidades en el
stock, se venderán solo las unidades disponibles.
- Borrar aquellos registros con 0 unidades disponibles.
- Salir.
El nombre del fichero se pasará como argumento en la línea de órdenes. Tienes un ejemplo de
menú en Moodle.
*/

int main(int argc, char **argv){
 int opcion;
 char *nombreFichero;

 if (argc !=2 )
	{
		printf("Número de argumentos incorrecto\n");
		printf("El programa se debe ejecutar de la siguente forma:\n\t %s <nombre de fichero>\n",argv[0]);
		return -1;
	}

  nombreFichero = argv[1];
 
  CLEAR_SCREEN;
  LUGAR(5,1);
  BIGREEN;
  printf("Gestión de libros usando el fichero <%s>\n\n",nombreFichero);
  RESET;
  printf("Pulsa enter para continuar");
  getchar();
 
 do{
		opcion = menu();	

  CLEAR_SCREEN;
  LUGAR(5,1);
  switch(opcion)
	{
		case 0:  /* FIN DEL PROGRAMA */
			  	LUGAR(10,10);
			    INVERSE;
			    printf("Fin del programa %s.\n",argv[0]);
			    RESET;
			    LUGAR(24,10);
				return 0;
			    break;

		case 1: /* COMPROBAR SI EXISTE UN LIBRO Y MOSTRAR SUS DATOS EN SU CASO */
		  		BIGREEN;
 				printf("Opción 1: COMPROBAR SI EXISTE UN LIBRO Y MOSTRAR SUS DATOS EN SU CASO \n\n");
  				RESET;
  				comprobarLibro(nombreFichero);
        		break;

		case 2:   /* INTRODUCIR UN LIBRO: SI YA EXISTE, SE INCREMETARÁN SU UNIDADES */
		  		BIGREEN;
				printf("Opción 2: INTRODUCIR UN LIBRO: SI YA EXISTE, SE INCREMETARÁN SU UNIDADES \n");		
				RESET;
				añadirLibro(nombreFichero);
      		 	break;

		case 3: /* CONTAR LOS LIBROS CON TÍTULOS DIFERENTES DEL FICHERO */
			  	BIGREEN;
                printf("Opción 3: CONTAR LOS LIBROS CON TÍTULOS DIFERENTES DEL FICHERO \n");	
				RESET;
				contarLibros(nombreFichero);
				break;

		case 4:  /* LISTAR LOS LIBROS DEL FICHERO */
				BIGREEN;
				printf("Opción 4: LISTAR LOS LIBROS DEL FICHERO \n");	
				RESET;
				listarLibrosStock(nombreFichero);
				break;		

		case 5: /* VENDER EJEMPLARES DE UN LIBRO  */
			    BIGREEN;
				printf("Opción 5: VENDER EJEMPLARES DE UN LIBRO \n");	
				RESET;
				venderNunidades(nombreFichero);
      		 	break;

		case 6: /* BORRAR LIBROS SIN EJEMPLARES */
		  		BIGREEN;
			    printf("Opción 6: BORRAR LIBROS SIN EJEMPLARES  \n");	
				RESET;
				borrar0unidades(nombreFichero);
      		 	break;

		default: /* OPCIÓN INCORRECTA */
				 RESET;
				 RED;
				 LUGAR(10,10);
				 printf("Opción incorrecta");
				 RESET;

	}

	LUGAR(20,90);
    printf("pulse ");
	UNDERLINE;
	printf("ENTER");
	RESET;
	printf(" para ");
	INVERSE;
	printf(" regresar al menú"); 
	RESET;      
	getchar();	

		
  }while(opcion!=0);



return 0;
}

