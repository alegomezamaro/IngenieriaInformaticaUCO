#include "funciones.h"
#include "macros.h"

int menu(){
 int opcion;

  CLEAR_SCREEN;
  LUGAR(5,10);
  BIYELLOW;
  printf("Opciones del menú");
  RESET;

	LUGAR(6,10);
  	printf("1.- Comprobar si existe un libro y mostrar sus datos en su caso.");
  	
	LUGAR(7,10);
	printf("2.- Introducir un libro: si ya existe, se incrementarán sus ejemplares.");
  
	LUGAR(8,10);
  	printf("3.- Contar el número de libros con títulos diferentes.");
		
	LUGAR(9,10);
	printf("4.- Listar los libros del fichero almacenándolos previamente en un vector.");

	LUGAR(10,10);
	printf("5.- Vender ejemplares de un libro.");
	
	LUGAR(11,10);
	printf("6.- Borrar los libros sin ejemplares.");
	
	LUGAR(12,10);
	GREEN;
	printf("0.- Salir");
	RESET;

	LUGAR(14,10);
	BIYELLOW;
	printf("Opción --> ");
	RESET;
	scanf("%d",&opcion);
	getchar();

	CLEAR_SCREEN;
	LUGAR(5,1);

	return opcion;
}

void comprobarLibro(char* nombreFichero){ //Comprueba si el libro existe
	//Define las variables
	char tituloBuscado[100];
	FILE* fichero;
	struct libro l;
	int encontrado = 0;

	//Pide el titulo del libro y le elimina el \0
    printf("Introduce el título del libro a buscar: ");
    fgets(tituloBuscado, 100, stdin);
    tituloBuscado[strlen(tituloBuscado)-1] = '\0';

	//Si el fichero no se abre error
	if((fichero = fopen(nombreFichero, "r")) == NULL){
		if((fichero = fopen(nombreFichero, "")) == NULL){
			printf("Error1, no se abre el fichero <%s>", nombreFichero);
			exit(-1);
		}
	}

	//Mientras el primer fichero sea distinto a NULL copia los datos en el vector y tambien en mayuscula con los auxiliarees
	while(fgets(l.titulo, 100, fichero)!=NULL){
		l.titulo[strlen(l.titulo)-1]='\0';
		fgets(l.autor, 50, fichero);
		l.autor[strlen(l.autor)-1]='\0';
		fscanf(fichero, "%f %d\n", &l.precio, &l.unidades);
		char aux_titulo[100];
		char aux2_titulo[100];
        for (int i = 0; i < 100; i++) {
            aux2_titulo[i] = toupper(tituloBuscado[i]);
        }
        for (int i = 0; i < 100; i++) {
            aux_titulo[i] = toupper(l.titulo[i]);
        }

        //Imprime los datos del libro encontrado
		if(strcmp(aux_titulo, aux2_titulo)==0){
			printf("\nEl libro <%s> si se encuentra entre nuestras existencias\n", l.titulo);
			printf("\nAutor: %s\n", l.autor);
			printf("\nQuedan %d unidades de este libro\n", l.unidades);
			printf("\nPrecio: %.2f\n", l.precio);
			encontrado = 1;
			break;
		}

	}

	//Si no ha encontrado el libro lo comunica
	if(encontrado == 0){
		printf("\nNo tenemos existencias del libro <%s>\n", tituloBuscado);
	}

	//Cierra el fichero y finaliza el programa
	fclose(fichero);
}

void añadirLibro(char* nombreFichero){ //Añade un nuevo libro
	//Definimos las variables
	struct libro nuevo;
	FILE* fichero;
	struct libro l;
	int encontrado = 0;

	//Introducimos el titulo del libro que queremos añadir y lo añadimos
    printf("Introduce el título del libro que desea añadir: ");
    fgets(nuevo.titulo, 100, stdin);
    nuevo.titulo[strlen(nuevo.titulo)-1] = '\0';

    //Si el fichero no se abre error
	if((fichero = fopen(nombreFichero, "r")) == NULL){
		printf("Error2, el fichero no se abre <%s>", nombreFichero);
		exit(-1);
	}

	while(fgets(l.titulo, 100, fichero)!=NULL){
		l.titulo[strlen(l.titulo)-1]='\0';
		fgets(l.autor, 50, fichero);
		l.autor[strlen(l.autor)-1]='\0';
		fscanf(fichero, "%f %d\n", &l.precio, &l.unidades);

		char aux_titulo[100];
		char aux2_titulo[100];

        for (int i = 0; i < 100; i++) {
            aux2_titulo[i] = toupper(nuevo.titulo[i]);
        }
        for (int i = 0; i < 100; i++) {
            aux_titulo[i] = toupper(l.titulo[i]);
        }
		if(strcmp(aux_titulo, aux2_titulo)==0){
			printf("\nEl libro <%s> ya existe en el fichero.\n", l.titulo);
			printf("\nIntroduzca el número de unidades a añadir: ");
			int udsAñadir;
			scanf("%d", &udsAñadir);
			l.unidades += udsAñadir;
			FILE* fichero_temp;
			if((fichero_temp = fopen("fichero_temporal.txt", "w")) == NULL){
				printf("Error al abrir el fichero <%s>", nombreFichero);
				exit(-1);
			}
			struct libro temp;
			fseek(fichero, 0, SEEK_SET);
			while(fgets(temp.titulo, 100, fichero)!=NULL){
				temp.titulo[strlen(temp.titulo)-1]='\0';
				fgets(temp.autor, 50, fichero);
				temp.autor[strlen(temp.autor)-1]='\0';
				fscanf(fichero, "%f %d\n", &temp.precio, &temp.unidades);
				if(strcmp(temp.titulo, l.titulo)==0){
					fprintf(fichero_temp, "%s\n%s\n%.2f %d\n", temp.titulo, temp.autor, temp.precio, l.unidades);
				}
				else{
					fprintf(fichero_temp, "%s\n%s\n%.2f %d\n", temp.titulo, temp.autor, temp.precio, temp.unidades);
				}
			}
			fclose(fichero);
			fclose(fichero_temp);
			remove(nombreFichero);
			rename("fichero_temporal.txt", nombreFichero);
			encontrado = 1;
			printf("\nUnidades añadidas correctamente.\n");
			getchar();
			break;
		}

	}
	if(encontrado == 0){	
		fclose(fichero);
		if((fichero = fopen(nombreFichero, "a")) == NULL){
			printf("Error al abrir el fichero <%s>", nombreFichero);
			exit(-1);
		}
		fprintf(fichero, "%s\n", nuevo.titulo);
		printf("\nIntroduzca el nombre del autor: ");
		fgets(nuevo.autor, 50, stdin);
		nuevo.autor[strlen(nuevo.autor)-1] = '\0';
		fprintf(fichero, "%s\n", nuevo.autor);
		printf("\nIntroduzca el precio del libro: ");
		scanf("%f", &nuevo.precio);
		fprintf(fichero, "%.2f ", nuevo.precio);
		printf("\nIntroduzca las unidades del libro: ");
		scanf("%d", &nuevo.unidades);
		fprintf(fichero, "%d", nuevo.unidades);
		printf("\nLibro añadido correctamente\n");
		getchar();
		fclose(fichero);
	}

}

int contarLibros(char* nombreFichero){
	FILE* fichero;
	if((fichero = fopen(nombreFichero, "r")) == NULL){
		if((fichero = fopen(nombreFichero, "w")) == NULL){
			printf("Error al abrir el fichero <%s>", nombreFichero);
			exit(-1);
		}
	}
	struct libro l;
	int contador = 0;
	while(fgets(l.titulo, 100, fichero)!=NULL){
		l.titulo[strlen(l.titulo)-1]='\0';
		fgets(l.autor, 50, fichero);
		l.autor[strlen(l.autor)-1]='\0';
		fscanf(fichero, "%f %d\n", &l.precio, &l.unidades);
		contador++;
	}
	printf("\nEl número de libros distintos entre nuestras existencias es %d\n", contador);
	fclose(fichero);
	return contador;
}

struct libro* reservarMemoria(int tamaño){
	struct libro* vector = (struct libro*)malloc(tamaño*sizeof(struct libro));
	if (vector == NULL) {
		printf("Error: no se pudo reservar memoria para lel vector\n");
		return NULL; // Devuelve NULL para indicar que la asignación de memoria ha fallado
	}
	return vector;
}

void liberarMemoria(struct libro** vector){
	free(*vector);
	*vector = NULL;
}

void listarLibrosStock(char *nombreFichero){
	int tamaño_vector = contarLibros(nombreFichero);
	struct libro* vector = reservarMemoria(tamaño_vector);
	struct libro l;
	FILE* fichero;
	if((fichero = fopen(nombreFichero, "r")) == NULL){
		if((fichero = fopen(nombreFichero, "w")) == NULL){
			printf("Error al abrir el fichero <%s>", nombreFichero);
			exit(-1);
		}
	}
	int i = 0;
	while(fgets(l.titulo, 100, fichero)!=NULL){
		l.titulo[strlen(l.titulo)-1]='\0';
		fgets(l.autor, 50, fichero);
		l.autor[strlen(l.autor)-1]='\0';
		fscanf(fichero, "%f %d\n", &l.precio, &l.unidades);
		vector[i] = l;
		i++;
	}
	fclose(fichero);
	for (int j = 0; j < tamaño_vector; ++j){
		BIYELLOW;	
		printf("\n  *\n");	
		RESET;
		printf("\n\tTítulo: %s\tAutor: %s\n\n\tUnidades disponibles: %d\tPrecio: %.2f",vector[j].titulo, vector[j].autor, vector[j].unidades, vector[j].precio);
	}
	liberarMemoria(&vector);
}

void venderNunidades(char* nombreFichero){
	struct libro vender;
    printf("Introduce el título del libro que desea vender: ");
    fgets(vender.titulo, 100, stdin);
    vender.titulo[strlen(vender.titulo)-1] = '\0';
	FILE* fichero;
	if((fichero = fopen(nombreFichero, "r")) == NULL){
		printf("Error al abrir el fichero <%s>", nombreFichero);
		exit(-1);
	}
	struct libro l;
	int encontrado = 0;
	while(fgets(l.titulo, 100, fichero)!=NULL){
		l.titulo[strlen(l.titulo)-1]='\0';
		fgets(l.autor, 50, fichero);
		l.autor[strlen(l.autor)-1]='\0';
		fscanf(fichero, "%f %d\n", &l.precio, &l.unidades);
		char aux_titulo[100];
		char aux2_titulo[100];
        for (int i = 0; i < 100; i++) {
            aux2_titulo[i] = toupper(vender.titulo[i]);
        }
        for (int i = 0; i < 100; i++) {
            aux_titulo[i] = toupper(l.titulo[i]);
        }
		if(strcmp(aux_titulo, aux2_titulo)==0){
			encontrado = 1;
			printf("\nIntroduzca el número de unidades a vender: ");
			int udsVender;
			scanf("%d", &udsVender);
			if (udsVender == 0){ printf(
				"Vaya! Al final no se han vendido unidades");
				getchar();
				break;
			};
			if(udsVender < 0){
				printf("No se pueden vender unidades negativas");
				getchar();
				break;
			}
			if(udsVender > l.unidades){
				printf("No se pueden vender más unidades de las que hay en stock\n");
				getchar();
				break;
			}
			l.unidades -= udsVender;
			FILE* fichero_temp;
			if((fichero_temp = fopen("fichero_temporal.txt", "w")) == NULL){
				printf("Error al abrir el fichero <%s>", nombreFichero);
				exit(-1);
			}
			struct libro temp;
			fseek(fichero, 0, SEEK_SET);
			while(fgets(temp.titulo, 100, fichero)!=NULL){
				temp.titulo[strlen(temp.titulo)-1]='\0';
				fgets(temp.autor, 50, fichero);
				temp.autor[strlen(temp.autor)-1]='\0';
				fscanf(fichero, "%f %d\n", &temp.precio, &temp.unidades);
				if(strcmp(temp.titulo, l.titulo)==0){
					fprintf(fichero_temp, "%s\n%s\n%.2f %d\n", temp.titulo, temp.autor, temp.precio, l.unidades);
				}
				else{
					fprintf(fichero_temp, "%s\n%s\n%.2f %d\n", temp.titulo, temp.autor, temp.precio, temp.unidades);
				}
			}
			fclose(fichero);
			fclose(fichero_temp);
			remove(nombreFichero);
			rename("fichero_temporal.txt", nombreFichero);
			printf("\nUnidades vendidas correctamente.\n");
			getchar();
			break;
		}

	}
	if(encontrado == 0){
		printf("El libro <%s> no se encuentra entre nuestras existencias\n", vender.titulo);
		getchar();
	}
}

void borrar0unidades(char* nombreFichero){
	FILE* fichero;
	if((fichero = fopen(nombreFichero, "r")) == NULL){
		printf("Error al abrir el fichero <%s>", nombreFichero);
		exit(-1);
	}
	struct libro l;
	while(fgets(l.titulo, 100, fichero)!=NULL){
		l.titulo[strlen(l.titulo)-1]='\0';
		fgets(l.autor, 50, fichero);
		l.autor[strlen(l.autor)-1]='\0';
		fscanf(fichero, "%f %d\n", &l.precio, &l.unidades);
		FILE* fichero_temp;
		if((fichero_temp = fopen("fichero_temporal.txt", "w")) == NULL){
			printf("Error al abrir el fichero <%s>", nombreFichero);
			exit(-1);
		}
		struct libro temp;
		fseek(fichero, 0, SEEK_SET);
		while(fgets(temp.titulo, 100, fichero)!=NULL){
			temp.titulo[strlen(temp.titulo)-1]='\0';
			fgets(temp.autor, 50, fichero);
			temp.autor[strlen(temp.autor)-1]='\0';
			fscanf(fichero, "%f %d\n", &temp.precio, &temp.unidades);
			if(temp.unidades !=0){
				fprintf(fichero_temp, "%s\n%s\n%.2f %d\n", temp.titulo, temp.autor, temp.precio, temp.unidades);
			}
		}
		fclose(fichero);
		fclose(fichero_temp);
		remove(nombreFichero);
		rename("fichero_temporal.txt", nombreFichero);
		printf("\nUnidades vendidas correctamente.\n");
		getchar();
		break;
	}
}