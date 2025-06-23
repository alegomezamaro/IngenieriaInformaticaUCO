struct cola *nuevoElemento(){
    return ((struct cola *)malloc(sizeof(struct cola)));
}

int contiene(struct cola *cabeza){
    if (cabeza == NULL) return 0;
    return 1;
}

void insertarCola(struct cola **cabeza, struct punto p){
    struct cola *nuevo = NULL;
    nuevo = nuevoElemento();
    nuevo->p = p;
    nuevo->sig = *cabeza;
    *cabeza = nuevo;
}

struct punto extraerCola(struct cola **cabeza){
    struct cola *aux = NULL;
    struct cola *ant = NULL;
    struct punto p;
    if (((*cabeza)->sig) == NULL){//Un solo nodo
        p = (*cabeza)->p;
        free(*cabeza);
        *cabeza = NULL;
        return p;
    }
    else{
        aux = *cabeza;
        while(aux->sig != NULL){
            ant = aux;
            aux = aux->sig;
        }
        p = aux->p;
        free(aux); /* se borra el ultimo*/
        ant->sig = NULL;
        return p;
    }
} 

int contarNodos(struct cola** cabeza){
    int nodos = 0;
    struct punto p;
    struct cola* colaAux = NULL;
    while(contiene(*cabeza)){
        p=extraerCola(cabeza);
        insertarCola(&colaAux, p);
        nodos++;
    }
    *cabeza = colaAux;
    return nodos;
}