float** reservaMatrizDinamicaPorFilas(int nFil, int nCol){
    float** Matriz;
    int i;
    Matriz=(float**)malloc(nFil*sizeof(float*));
    for(i=0; i<nFil;i++){
        Matriz[i]=(float*)malloc(nCol*sizeof(float));
    }
    return(Matriz);
}

void liberaMatrizDinamicaPorFilas(float** Matriz, int nFil){
    int i;
    for(i=0; i<nFil; i++){
        free(Matriz[i]);
    }
    free(Matriz);
}

void liberaMatrizDinamicaPorFilas(float*** Matriz, int nFil){ //Igualada a NULL por referencia
    int i;
    for(i=0; i<nFil; i++){
        free((*Matriz)[i]);
    }
    free(*Matriz);
    (*Matriz) = NULL;
}

float** reservaMatrizDinamicaUnSoloBloque(int nFil, int nCol){
    float** Matriz;
    int i;
    Matriz=(float**)malloc(nFil*sizeof(float*));
    Matriz[0]=(float*)malloc(nFil*nCol*sizeof(float));
    for(i=1; i<nFil; i++)
    Matriz[i]=Matriz[i-1]+nCol;
    return(Matriz);
}

void liberaMatrizDinamicaUnSoloBloque(float** Matriz){
    free(Matriz[0]);
    free(Matriz);
}

void reservaMatrizDinamicaPorFilasRef(float*** Matriz,int nFil, int nCol){
    int i;
    *Matriz=(float**)malloc(nFil*sizeof(float*));
    for(i=0; i<nFil;i++){
        (*Matriz)[i]=(float*)malloc(nCol*sizeof(float));
    }
}

struct dato** reservaMatrizStr(int nFil, int nCol){
    struct dato** ptr;
    int i;
    if((ptr=(struct dato**)malloc(nFil*sizeof(struct dato*)))==NULL){
        printf("\nError en la reserva de memoria (1)");
        exit(-1);
    }
    for(i=0; i<nFil; i++){
        if((ptr[i]=(struct dato*)malloc(nCol*sizeof(struct dato)))==NULL){
            printf("\nError en la reserva de memoria (2)");
            exit(-1);
        }
    }
    return(ptr);
}

void reservaMatrizStrReferencia(struct dato*** ptr,int nFil,int nCol){
    int i;
    if((*ptr = (struct dato**)malloc(nFil*sizeof(struct dato*)))==NULL){
        printf("\nError en la reserva de memoria (1)");
        exit(-1);
    }
    for(i=0; i<nFil; i++){
        if(((*ptr)[i] = (struct dato*)malloc(nCol*sizeof(struct dato)))==NULL){
            printf("\nError en la reserva de memoria (2)");
            exit(-1);
        }
    }
}

void liberaMatrizStr(struct dato** ptr, int nFil){
    int i;
    for(i=0; i<nFil; i++){
        free(ptr[i]);
    }
    free(ptr);
}

float*** reservaMatrizTridimensional(int nFil, int nCol, int nAlt){
    float*** Matriz;
    int i, j;
    Matriz=(float***)malloc(nFil*sizeof(float**));
    for(i=0; i<nFil;i++){
        Matriz[i]=(float**)malloc(nCol*sizeof(float*));
        for(j=0; j<nCol; j++){
            Matriz[i][j]=(float*)malloc(nAlt*sizeof(float));
        }
    }
    return(Matriz);
}

void liberaMatrizTridimensional(float*** Matriz,int nFil, int nCol){
    int i, j;
    for(i=0; i<nFil; i++){
        for(j=0; j<nCol; j++){
            free(Matriz[i][j]);
        }
        free(Matriz[i]);
    }
    free(Matriz);
}