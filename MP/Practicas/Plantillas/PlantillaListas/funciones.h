#ifndef FUNCIONES_H
#define FUNCIONES_H


struct nodo
{
    int dato;//unico caso donde cambia es en el char dato[100] ya que seria una cadena y no se prodria = a las funciones.(usar strcpy)
    struct nodo * sig;
};

void inyectarDelante(struct nodo ** cabeza,int dato);
struct nodo * nuevoElemento();
void inyectarDetras(struct nodo ** cabeza,int dato);
//N
void mostrarLista(struct nodo * cabeza);
//I
void contarElemento(struct nodo * cabeza, int * tam);
//G
int buscaElemento(struct nodo * cabeza,int elemento);
//G
void borrarElemento(struct nodo ** cabeza, int dato);
//E
void borrarLista(struct nodo ** cabeza);
//R
void MostrarListaRecursiva(struct nodo * cabeza);
//S
#endif