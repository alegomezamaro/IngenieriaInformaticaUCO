#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct libro {
    char titulo[100];
    char autor[100];
    int unidades;
};

void comprobar_existencia_libro(FILE *fichero);
void introducir_nuevo_libro(FILE *fichero);
void contar_libros_diferentes(FILE *fichero);
void listar_libros(FILE *fichero);
void vender_libro(FILE *fichero);
void borrar_libros_sin_stock(FILE *fichero);

#endif