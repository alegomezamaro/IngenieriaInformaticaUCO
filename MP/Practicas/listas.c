struct lista{

int dato; //Dato de la lista
struct lista *sig; //Puntero al siguiente elemento de la lista
};

struct lista *nuevoElemento(){

    return ((struct lista *)malloc(sizeof(struct lista)));
}

void insertarDelante(struct lista **cabeza, int n){

    struct lista *nuevo = NULL; //Crear un nuevo elemento
    nuevo = nuevoElemento(); //Reservar memoria para el nuevo elemento
    nuevo->n = n; //Asignar el valor al nuevo elemento
    nuevo->sig = *cabeza; //Hacemos que el nuevo elemento apunte al antiguo primer elemento
    *cabeza = nuevo; //Hacemos que la cabeza de la lista apunte al nuevo elemento
}

void insertarDetras(struct lista **cabeza, int n){

    struct lista *nuevo = NULL; //Crear un nuevo elemento
    struct lista *aux = NULL; //Variable auxiliar para recorrer la lista
    nuevo = nuevoElemento(); //Reservar memoria para el nuevo elemento
    nuevo->n = n; //Asignar el valor al nuevo elemento
    nuevo->sig = NULL; //Hacemos que el nuevo elemento apunte a NULL, ya que será el último elemento de la lista

    if (*cabeza == NULL){ //Si la lista está vacía
        
        *cabeza = nuevo; //Hacemos que la cabeza de la lista apunte al nuevo elemento
    }

    else{ //Si la lista no está vacía, recorremos la lista hasta el final

        aux = *cabeza; //Hacemos que aux apunte al primer elemento de la lista

        while(aux->sig != NULL){ //Mientras aux no llegue al final de la lista

            aux = aux->sig; //Hacemos que aux apunte al siguiente elemento de la lista
        }

        aux->sig = nuevo; //Hacemos que el último elemento de la lista apunte al nuevo elemento
    } 
}

void imprimirLista(struct lista *cabeza){

    struct lista *aux = NULL; //Variable auxiliar para recorrer la lista
    aux = cabeza; //Hacemos que aux apunte al primer elemento de la lista

    while (aux != NULL){ //Mientras aux no llegue al final de la lista

        printf(" %d \n", aux->n); //Imprimimos el dato del elemento actual
        aux = aux->sig; //Hacemos que aux apunte al siguiente elemento de la lista
    }
}

void imprimirListaInverso(struct lista *elemento){

    if (elemento != NULL){ //Si no hemos llegado al final de la lista

        imprimirListaInverso(elemento->sig); //Llamamos recursivamente al siguiente elemento
        printf(" %d \n", elemento->n); //Imprimimos el dato del elemento actual
    }
}

int buscarElemento(struct lista *cabeza, int n){

    int encontrado = 0; //Variable para indicar si hemos encontrado el elemento
    struct lista *aux = NULL; //Variable auxiliar para recorrer la lista
    aux = cabeza; //Hacemos que aux apunte al primer elemento de la lista

    while (aux != NULL && encontrado ==0){ //Mientras aux no llegue al final de la lista y no hayamos encontrado el elemento

        if(aux->n == n){ //Si el dato del elemento actual es igual al que estamos buscando

            encontrado = 1;
        }

        else{ //Si no es igual, seguimos buscando

            aux = aux->sig;
        }
    }

    return encontrado; 
}

void borrarElemento(struct lista **cabeza, int n){

    struct lista *ant = NULL; //Elemento anterior al que se va a borrar
    struct lista *aux = NULL; //Elemento a borrar
    aux = *cabeza; //Hacemos que aux apunte al primer elemento de la lista

    while (aux->n != n){ //Mientras el dato del elemento actual no sea igual al que estamos buscando
    
        ant = aux; //Hacemos que ant apunte al elemento actual
        aux = aux->sig; //Hacemos que aux apunte al siguiente elemento de la lista
    }

    if (aux == *cabeza){ //Queremos borrar la cabeza de la lista

        *cabeza = aux->sig; //Hacemos que la cabeza de la lista apunte al siguiente elemento
        free(aux); //Liberamos el nodo a borrar
    }

    else{ //Queremos borrar un elemento que no es la cabeza de la lista

    ant->sig = aux->sig; //Enlazamos el elemento anterior al siguiente del elemento a borrar
    free(aux); //Liberamos el nodo a borrar
    }
}

void borrarElementoRecursivo(struct lista **cabeza, int n){

    struct lista *aux = NULL; //Elemento a borrar

    if ((*cabeza)->n != n){ //Si el dato del elemento actual no es igual al que estamos buscando

        borrarElementoRecursivo( &((*cabeza)->sig), n); //Llamamos recursivamente al siguiente elemento
    }

    else{ //Si el dato del elemento actual es igual al que estamos buscando

        aux = *cabeza; //Hacemos que aux apunte al elemento a borrar
        *cabeza = aux->sig; //Hacemos que la cabeza de la lista apunte al siguiente elemento
        free(aux); //Liberamos el nodo a borrar
    }
}

void borrarLista(struct lista **cabeza){

    struct lista * aux, * sig; //Variables auxiliares para recorrer la lista
    aux=*cabeza; //Hacemos que aux apunte al primer elemento de la lista

    while(aux!=NULL){ //Mientras aux no llegue al final de la lista

        sig=aux->sig; //Hacemos que sig apunte al siguiente elemento de la lista
        free(aux); //Liberamos el nodo actual
        aux=sig; //Hacemos que aux apunte al siguiente elemento de la lista
    }

    *cabeza=NULL; //Lista vacia
}

void borrarListaRecursiva(struct lista **elemento){

    if (*elemento != NULL){ //Si no hemos llegado al final de la lista

        borrarListaRecursiva(&((*elemento)->sig)); //Llamamos recursivamente al siguiente elemento
        free(*elemento); //Liberamos el nodo actual
        *elemento = NULL; //Fin de lista o lista vacia
    }
}

void insertarOrden(struct lista **cabeza, int n){
    struct lista *ant = NULL; /*anterior al que se inserta*/
    struct lista *aux = NULL; /*posterior al que se inserta*/
    struct lista *nuevo = NULL; /* nuevo elemento */
    int encontrado = 0; /*posición de inserción encontrada*/
    /* Se reserva espacio para el nuevo elemento */
    nuevo = nuevoElemento();
    nuevo->n = n;
    /* lista vacía o el elemento se inserta delante de la cabeza*/
    if((*cabeza == NULL) || ((*cabeza)->n > n))
    {
    nuevo->sig = *cabeza;
    /*la cabeza será el nuevo elemento*/
    *cabeza = nuevo;
    }
    else{ /*lista no vacía o insercion en el medio de la lista*/
    /*busqueda de la posicion de insercion, se interrumpe cuando se encuentra el primer elemento mayor que n o cuando se llega al final de la lista*/
    aux = *cabeza;
    while (aux != NULL && encontrado == 0)
    {
    if (aux->n > n)/*se ha encontrado la posicion de insercion*/
    encontrado = 1;
    else /*se actualizan los valores de aux y ant*/
    {
    ant = aux;
    aux = aux->sig;
    }
    }//while
    /* ubicamos el elemento nuevo entre ant y aux. Estas acciones son válidas aunque aux sea igual a NULL */
    nuevo->sig = aux;
    ant->sig = nuevo;
    } //else
}

void insertarOrdenRecursivo(struct lista **cabeza, int n){
    if( (*cabeza==NULL) || ((*cabeza)->n > n)){
        nuevo = nuevoElemento();
        nuevo->n = n;
        nuevo->sig = (*cabeza);
        *cabeza = nuevo;
    }
    else{
        insertarOrdenRecursivo( &((*cabeza)->sig), n);
    }
}

void ordenarLista(struct lista *cabeza){
    struct lista *aux;
    struct lista *aux1;
    struct lista *minimo;
    int minimo_n;
    aux = cabeza;
    //Recorrer toda la lista
    while(aux->sig != NULL){ //while1
        aux1 = aux->sig;
        minimo = aux;
        while(aux1 != NULL){//while2
            if (aux1->n < minimo->n){
                minimo = aux1; //seleccionar minimo
            }
            aux1 = aux1->sig;
        }//while 2
        //Intercambio aux y minimo
        minimo_n = minimo->n;
        minimo->n = aux->n;
        aux->n = minimo_n;
        //Preparar siguiente iteración
        aux = aux->sig;
    }//While1
}
