#ifndef EJ5F_H
#define EJ5F _H
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct ficha_jugador{
	char nombre[50];	//Nombre
	int dorsal;		// Número entero
	float peso;		// Kilos
	int estatura;		// Centímetros
};

void reservarMemoria(struct ficha_jugador **jugadores, int num_jugadores);
struct ficha_jugador nuevoJugador();
void rellenarVectorDatos(struct ficha_jugador **jugadores, int num_jugadores);
void leerJugadores(struct ficha_jugador **jugadores, int num_jugadores);
int borrarSiCaracter(struct ficha_jugador **jugadores, char *caracter, int num_jugadores);

#endif