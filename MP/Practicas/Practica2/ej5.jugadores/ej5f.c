 #include "ej5f.h"

void reservarMemoria(struct ficha_jugador **jugadores, int num_jugadores){	//Función para reservar memoria para un vector de estructuras de jugador.
	if((*jugadores=(struct ficha_jugador*)malloc(num_jugadores*sizeof(struct ficha_jugador))) == NULL){
		printf("\nError1: Fallo en la reserva");
		exit(-1);
	}
}

struct ficha_jugador nuevoJugador(){	//Función para leer un nuevo jugador. La función pedirá al usuario los datos de un jugador y los devolverá en una estructura struct Ficha_jugador.
	struct ficha_jugador jugadores;
	printf("\nIntroduce el nombre del jugador: ");
	scanf("%s", jugadores.nombre);
	printf("\nIntroduce el dorsal del jugador: ");
	scanf("%i", &jugadores.dorsal);
	printf("\nIntroduce el peso del jugador: ");
	scanf("%f", &jugadores.peso);
	printf("\nIntroduce la estatura del jugador (en centimetros): ");
	scanf("%i", &jugadores.estatura);
	return (jugadores);
}

void rellenarVectorDatos(struct ficha_jugador **jugadores, int num_jugadores){
	for(int i=0; i<num_jugadores; i++){
		printf("\nRellena los datos del jugador %i", i);
		(*jugadores)[i] = nuevoJugador();
	}
}

void leerJugadores(struct ficha_jugador **jugadores, int num_jugadores){	//Imprime los datos de los jugadores
	for(int i=0; i<num_jugadores; i++){
		printf("\nLos datos del jugador son: ");
		printf("\nNombre: %s", (*jugadores)[i].nombre);
		printf("\nDorsal: %i", (*jugadores)[i].dorsal);
		printf("\nPeso: %f", (*jugadores)[i].peso);
		printf("\nEstatura: %icm", (*jugadores)[i].estatura);
	}
}

int borrarSiCaracter(struct ficha_jugador **jugadores, char *caracter, int num_jugadores){	//Función para borrar jugadores cuyo nombre contenga un carácter que se pasará como argumento y que podrá aparecer en mayúscula o minúscula. Te pueden ser de utilidad las funciones tolower, toupper y strchr. Al terminar la ejecución, el vector de jugadores habrá reducido su tamaño usando la función realloc. La función devolverá el número de jugadores que quedan en el vector
    int aux=0;
    for(int i=0; i<num_jugadores; i++){
    	char *nombre=(*jugadores)[i].nombre;
    	for(int j=0; nombre[j] != '\0'; j++){
    		if(tolower(nombre[j+1]) == tolower(*caracter)){
    			break;
    		}
    		else if(nombre[j+1] == '\0'){
    			(*jugadores)[aux++] = (*jugadores)[i];
    		}
    	}
    }
    *jugadores=(struct ficha_jugador*)realloc(*jugadores, aux*sizeof(struct ficha_jugador));
    if(*jugadores==NULL){
    	printf("Error2: Fallo en la reserva");
    }
    return(aux);
}