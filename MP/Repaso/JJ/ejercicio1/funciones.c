#include "funciones.h"
#include <stdlib.h>
#include <string.h>

int comprobar1(struct lista *ls, struct estudiante *v, int tam)
{
    if(ls==NULL)
        return 0;
    for (size_t i = 0; i < tam; i++,ls=ls->siguiente)
    {
        if(strcmp(v[i].nombre,ls->nombre) || v[i].nota_media!=ls->nota_media || v[i].creditos_superados!=ls->porcentaje_superado)
            return 0;
    }
    return 1;
}

void delete(struct lista ** ls)
{
    while((*ls)!=NULL)
    {
        struct lista * aux = (*ls);
        (*ls)=(*ls)->siguiente;
        free(aux);
    }
}