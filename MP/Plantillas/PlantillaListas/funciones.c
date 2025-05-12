#include "funciones.h"
#include <stdlib.h>
#include <stdio.h>


void inyectarDelante(struct nodo **cabeza,int dato){
    struct nodo *nuevo = nuevoElemento();
    nuevo -> dato =dato;
    nuevo -> sig = (*cabeza);
    (*cabeza)=nuevo;

}
//N
struct nodo * nuevoElemento(){
    struct nodo * nuevo=NULL;
    nuevo=(struct nodo *)malloc(sizeof(struct nodo));
    if (nuevo==NULL)
    {
        printf("error al reservar memoria \n");
        exit(-1);
    }
    return nuevo;
}
//I
void inyectarDetras(struct nodo ** cabeza,int dato){
     struct nodo *nuevo = nuevoElemento();
    nuevo -> dato =dato;
    nuevo -> sig = NULL;
    if ((*cabeza)==NULL){
        {
        (*cabeza)=nuevo;
        }
    }
    else{
        struct nodo *aux =(*cabeza);
        while (aux ->sig != NULL)
        {
            aux=aux ->sig;
        }
        aux -> sig =nuevo;
    }

}
//G
void mostrarLista(struct nodo * cabeza){
    struct nodo * aux =cabeza;
    while (aux!=NULL)
    {
        printf("%d \n",aux ->dato);
        aux=aux->sig;
    }
    
}
//G
void contarElemento(struct nodo * cabeza, int * tam){
    int cont=0;
    struct nodo * aux=cabeza;
    while (aux!=NULL)
    {
        cont++;
        aux=aux->sig;
    }
    (*tam)=cont;
}
//E
int buscaElemento(struct nodo * cabeza,int elemento){
     struct nodo * aux=cabeza;
       while (aux!=NULL)
    {
        if (aux->dato==elemento)
        {
           return 1;
        }
       aux=aux->sig;
    }
    return 0;
}
//R
void borrarLista(struct nodo ** cabeza){
    struct nodo * aux =(*cabeza);
    struct nodo * anterior;
    while (aux!=NULL)
    {
        anterior=aux;
        aux=aux->sig;
        free(anterior);
    }
    (*cabeza)=NULL;
}
//S
void borrarElemento(struct nodo ** cabeza, int dato){
    struct nodo * aux = (*cabeza);
    struct nodo * aut;

    while (aux!=NULL && aux->dato!=dato)
    {
        aut=aux;
        aux=aux->sig;
    }
    if (aux!=NULL)
    {
        if (aux==(*cabeza))
        {
            (*cabeza)=aux->sig;
        }
        else{
            aut->sig=aux->sig;
        }
        free(aux);
    }  
}
 
 void MostrarListaRecursiva(struct nodo * cabeza)
 {
    if (cabeza!=NULL)
    {
        printf(" %d\n",cabeza->dato);
        MostrarListaRecursiva(cabeza ->sig);
    }
    
 }

 /*Para imprimir la lista al reves:
    mostarListaRecursiva(aux->sig);
    printf("%d\n",aux->dato);
 */


/*
    struct persona{
        char dni[10];
        int edad;
        float altura;
    };

    struct nodo{
        struct persona dato;
        struct nodo * sig;
    };

    int buscarPersona(struct nodo * cabeza, char * dni){

        struct nodo * aux=cabeza;
        while(aux!=NULL)
        {
            if(strcmp(aux->dato).dni,dni){
                return 1;
            }
            aux=aux->sig;
        }
        return 0;

    }

*/