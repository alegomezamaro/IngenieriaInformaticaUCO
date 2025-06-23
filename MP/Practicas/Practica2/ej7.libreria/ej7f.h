/**
 * @file ej7.h
 * @brief Escribe un programa que implemente las siguientes funciones sobre matrices dinámicas y las llame de manera secuencial mostrando, de manera adecuada, la salida por pantalla.
 * @author Alejandro Gómez Amaro
 * @date 28-04-2024
 * @version 1.0
 */

#ifndef EJ7F_H
#define EJ7F_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @fn int **reservarMemoria(int nFil, int nCol)
 * @brief Reserva la memoria dadas las filas y columnas
 * @var nFil Numero de filas
 * @var nCol Numero de columnas
 */
int **reservarMemoria(int nFil, int nCol);

/**
 * @fn void rellenaMatriz(int **matriz, int nFil, int nCol)
 * @brief Rellena la matriz dadas las filas y columnas
 * @var matriz La matriz con el espacio reservado necesario
 * @var nFil Numero de filas
 * @var nCol Numero de columnas
 */
void rellenaMatriz(int **matriz, int nFil, int nCol);

/**
 * @fn void imprimeMatriz(int **matriz, int nFil, int nCol)
 * @brief Imprime los valores de la matriz
 * @var matriz La matriz con el espacio reservado necesario
 * @var nFil Numero de filas
 * @var nCol Numero de columnas
 */
void imprimeMatriz(int **matriz, int nFil, int nCol);

/**
 * @fn void liberarMemoria(int **matriz)
 * @brief Libera la memoria de la matriz
 * @var matriz La matriz con el espacio reservado necesario
 */
void liberarMemoria(int **matriz);

#endif