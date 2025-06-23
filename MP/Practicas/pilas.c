struct pila * nuevoElemento(){
    return((struct pila *)malloc(sizeof(struct pila)));
}

int vacia(struct pila *cabeza){
    if (cabeza == NULL)
    return 1;
    return 0;
}

void verCima(struct pila *cabeza, char *nombre){
    strcpy(nombre, cabeza->nombre);
} 

void apilar(struct pila **cabeza, char *nombre){
    struct pila *nuevo = NULL;
    nuevo = nuevoElemento();
    strcpy(nuevo->nombre, nombre);
    nuevo->sig = *cabeza;
    *cabeza = nuevo;
}

void desapilar(struct pila **cabeza, char *nombre){
    struct pila *aux;
    aux = *cabeza;
    strcpy(nombre, (*cabeza)->nombre);
    *cabeza = aux->sig;
    free (aux);
}

int contarNodos(struct pila** cabeza){
    struct pila* pilaAux = NULL; //PILA AUXILIAR VACÍA
    int nodos = 0;
    char nombre[20];
    while(!vacia(*cabeza)){
        desapilar(cabeza, nombre);
        apilar(&pilaAux, nombre);
        nodos ++;
    }
    while(!vacia(pilaAux)){
        desapilar(&pilaAux, nombre);
        apilar(cabeza, nombre);
    }
    return nodos;
}