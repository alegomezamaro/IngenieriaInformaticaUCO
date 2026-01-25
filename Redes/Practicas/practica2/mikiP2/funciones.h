#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/select.h>
#include <signal.h>
#include <stdbool.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#define MSG_SIZE 250
#define MAX_CLIENTS 30
#define MAX_PARTIDA 10

struct carta
{
    std::string valor;
    std::string palo;
};

struct cliente
{
    int sd;
    int estado;
    char *nombre;
    char *contraseña;
    bool turno;
    bool activo = true;
    bool plantado = false;
    std::vector<struct carta> mazo;
};

struct partida
{
    struct cliente *jugador1;
    struct cliente *jugador2;
    std::vector<struct carta> mazo;
};

void manejador(int signum);
void salirCliente(int socket, fd_set *readfds, int *numClientes, struct cliente *listaclientes, partida **listapartidas, int *partidas);

// funciones para la gestion de la base de datos
bool comprobarfiche(char *nombrefiche, char *nombresesion);
char *registrar(char *nombrefiche, char *nombre, char *contraseña);
bool comprobarfiche_contrasena(char *nombrefiche, char *usuario_input, char *contrasena_input);
bool comprobarlog(struct cliente * listaclientes, char* nombre, int numClientes);

// funciones para la concurrencia
struct cliente crearcliente(int sd); // esta funcion la tenemos que modificar para meter el nombre dentro del struct una vez se inicie sesion
struct cliente *reservarmemoriajugador();
struct partida *rspartida();
void anadircliente(struct cliente *listaclientes, int numClientes, struct cliente nuevo);
struct cliente *bcliente(struct cliente *array, int n, int i);
struct cliente *actualizarcliente(struct cliente *listaclientes, int numClientes, struct cliente *actualizado);
//void actualizarnombrecliente(struct cliente *listaclientes, int numClientes, int sd, char *nombre, char *contrasena); funcion desechada
struct cliente *buscarcontringante(struct cliente *listaclientes, int numClientes);

// funciones juego
void iniciarTurno(struct cliente *jugador);
void asignarCartasYNotificar(std::vector<carta> &mazo, struct cliente *jugador1, struct cliente *jugador2);
struct carta asignarCarta(std::vector<struct carta> &cartas, struct cliente *jugador);
struct carta sacar_carta(std::vector<struct carta> &cartas);
struct carta generarCartaAleatoria();
int obtenerValorCarta(const std::string &valor);
bool buscarYEliminarCarta(std::vector<struct carta> &cartas, const std::string &paloCartaBuscada, std::string valorCartaBuscada);
int calcularValorTotal(const std::vector<carta> &mazo);
bool partidaContinua(struct cliente *actual, struct cliente *adversario, struct cliente *listaclientes, int numClientes);
std::vector<carta> inicializarMazo(const std::string &nombreFichero);
void finalizarPartida(partida **listapartidas, int &partidas, partida *partidaActual, struct cliente *actual, struct cliente *adversario);

//FUNCIONES PARA MENUS
void MenuNoIniciados(int sd, char *buffer);

#endif

/*
Los estados en los que se va aencontrar el jugador va a ser los siguientes
dentrodelsistema = 0
registrado = 1
espera para partida= 2
jugando = 3
*/

// duda solo pueden haver 30 clientes dentro de la sesion o solo puede iniciar partida 30 clientes

// duda para que no se pueda cahtear cuando esta iniciada la partida como se podria hacer

// duda las funciones del juego las hago dentro de otro .h ???
