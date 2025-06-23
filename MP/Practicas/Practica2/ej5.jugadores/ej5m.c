#include "ej5f.h"

int main(){
	//Definimps variables
	int num_jugadores;
	char caracter[]="a";
	struct ficha_jugador *jugadores;

	//Introducimos el numero de jugadores
	printf("\nIntroduce el numero de jugadores: ");
	scanf("%i", &num_jugadores);

	//Reservamos memoria y rellenamos los datos
	reservarMemoria(&jugadores, num_jugadores);
	rellenarVectorDatos(&jugadores, num_jugadores);
	leerJugadores(&jugadores, num_jugadores);

	//Introducimos caracter y eliminamos los nombres que lo incluyen
	num_jugadores=borrarSiCaracter(&jugadores, caracter, num_jugadores);

	//Imprimir los datos
	printf("\nJugadores restantes:");
	leerJugadores(&jugadores, num_jugadores);

	//Liberar memoria y salir
	free(jugadores);
	return 0;
}