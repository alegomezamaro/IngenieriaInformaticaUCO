#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void existeFichero(char *nombreFichero)
{
    FILE * fich=fopen(nombreFichero,"rb");
    if (fich==NULL)
    {
        printf("No eiste el fichero.\n");
        exit(-1);
    }

    fclose(fich);
    
}

/*void mostrarFichero(char *nombreFichero)
{
    FILE * fich=fopen(nombreFichero,"rb");
    if (fich==NULL)
    {
        printf("Error al abrir el fichero.\n");
        exit(-1);
    }

    struct producto p;

    while (fread(&p,sizeof(struct producto),1,fich)==1)
    {
        printf("nombre: %s cod: %d precio: %f unidades: %d\n",p.nombre,p.cod,p.precio,p.unidades);
    }
    
    fclose(fich);
}

void añadirProducto(char *nombreFichero,struct producto nuevo)
{
    FILE * fich=fopen(nombreFichero,"ab");
    if (fich==NULL)
    {
        printf("Error al abrir el fichero.\n");
        exit(-1);
    }

    fwrite(&nuevo,sizeof(struct producto),1,fich);

    fclose(fich);
}

void borrarProducto(char *nombreFichero,char *nombre)
{
    FILE * fich=fopen(nombreFichero,"rb");
    if (fich==NULL)
    {
        printf("Error al abrir el fichero.\n");
        exit(-1);
    }

     FILE * fich2=fopen("auxiliar.bin","wb");
    if (fich==NULL)
    {
        printf("Error al abrir el fichero.\n");
        exit(-1);
    }

    struct producto p;
    int borrador=0;
    while (fread(&p,sizeof(struct producto),1,fich)==1)
    {
        if (strcmp(p.nombre,nombre)!=0)
        {
            fwrite(&p,sizeof(struct producto),1,fich2);
        }
        else
        {
            borrador=1;
        }
        
    }
    

    fclose(fich);
    fclose(fich2);

    remove(nombreFichero);
    rename("auxiliar.bin",nombreFichero);
}*/

void contarFichero(char *nombreFichero,int *tam)
{
	FILE * fich=fopen(nombreFichero,"rb");
	if (fich==NULL)
	{
		printf("El fichero no existe.\n");
		exit(-1);
	}

	struct producto p;
	fseek(fich,0,SEEK_END);
	long int byte=ftell(fich);
	(*tam)=byte/sizeof(struct producto);
	fclose(fich);
}

/*void modificarFichero(char *nombreFichero,char *nombre,int cod)
{
    FILE * fich=fopen(nombreFichero,"rb+");
    if (fich==NULL)
    {
        printf("Error al abrir el fichero.\n");
        exit(-1);
    }

    struct producto p;
    while (fread(&p,sizeof(struct producto),1,fich)==1)
    {
        if (p.cod==cod)
        {
            strcpy(p.nombre,nombre);
            fseek(fich,-1*sizeof(struct producto),SEEK_CUR);
            fwrite(&p,sizeof(struct producto),1,fich);
        }       
    }
    
    fclose(fich);
}

struct producto *reservarMemoria(int cont)
{
    struct producto *v=NULL;
    v=(struct producto*)malloc(sizeof(struct producto)*cont);
    if (v==NULL)
    {
        printf("Error al reservar memoria,\n");
        exit(-1);
    }

    return v;
    
}

void FicherobinVector(char *nombreFichero,struct producto *v)
{
    FILE * fich=fopen(nombreFichero,"rb");
    if (fich==NULL)
    {
        printf("Error al abrir el fichero.\n");
        exit(-1);
    }

    struct producto p;
    int i=0;
    while (fread(&p,sizeof(struct producto),1,fich)==1)
    {
        strcpy(v[i].nombre,p.nombre);
        v[i].cod=p.cod;
        v[i].precio=p.precio;
        v[i].unidades=p.unidades;
        i++;
    }
    

    fclose(fich);
}

void VectorFichero(char *nuevoFichero,struct producto *v,int cont)
{
    FILE * fich=fopen(nuevoFichero,"w");
    if (fich==NULL)
    {
        printf("Error al abrir el fichero.\n");
        exit(-1);
    }

    for (int i = 0; i < cont; i++)
    {
        fprintf(fich,"nombre: %s cod: %d precio: %f unidades: %d\n",v[i].nombre,v[i].cod,v[i].precio,v[i].unidades);
    }
    

    fclose(fich);
}

void librerarMemoria(struct producto **v)
{
    free(*v);
    (*v)=NULL;
}*/
