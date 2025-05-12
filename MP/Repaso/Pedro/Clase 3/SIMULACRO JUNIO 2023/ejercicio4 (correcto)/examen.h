#ifndef EXAMEN_H

struct dato
{
    char codigo[10];
    int unidades;
    float precio_compra;
    float precio_venta;
};

struct lista
{
    char codigo[10];
    int unidades;
    float ratio_ganancia; // es igual a precio_venta/precio_compra
    struct lista *siguiente;
};

struct dato2
{
    char codigo[10];
    int unidades;
    float ratio_ganancia; // es igual a precio_venta/precio_compra
};

void ejercicio1(struct dato *V, int numeroElementos, struct lista **cola);

struct dato2 *ejercicio2(struct lista *cola, int *tam);

// COMPLETAR CON EL PROTOTIPO DE LAS FUNCIONES IMPLEMENTADAS

void insertarDetras(struct lista ** COLA, struct dato d);

struct lista * nuevoElemento();

struct dato2 * reservarMemoria(int * tam);

#endif
