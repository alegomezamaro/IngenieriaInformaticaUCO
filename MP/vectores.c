struct dato* reservaVectorStr(int nEle){
    struct dato* ptr;
    if((ptr=(struct dato*)malloc(nEle*sizeof(struct dato)))==NULL){
        printf("\nError en la reserva de memoria");
        exit(-1);
    }
    return(ptr);
}

void reservaVectorStrReferencia(struct dato** ptr, int nEle){
    if((*ptr=(struct dato*)malloc(nEle*sizeof(struct dato)))==NULL){
        printf("\nError en la reserva de memoria");
        exit(-1);
    }
}

void liberaVectorStr(struct dato* ptr){
    free(ptr);
}