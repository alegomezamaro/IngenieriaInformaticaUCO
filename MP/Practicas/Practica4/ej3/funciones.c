#include"funciones.h"
#include <stdio.h>
#include <stdlib.h>

void tamañoStruct(char fname[50],int *tam)
{
	alumno aux;
	FILE *f;
	f=fopen(fname,"rb");
	
	if(f==NULL)
	{
		printf("No se ha podido abrir el fichero\n");
		exit(1);
	}
	
	while(fread(&aux,sizeof(alumno),1,f)==1)
	{
		(*tam)++;
	}
	
	fclose(f);
}


void rellenaVector(alumno **vector,char fname[50],int *tam)
{
	int cont=0;
	FILE *f;
	
	f=fopen(fname,"rb");
	if(f==NULL)
	{
		printf("No se ha podido abrir el fichero");
		exit(1);
	}
	
	*vector=(alumno*)malloc(sizeof(alumno)*(*tam));
	if(*vector==NULL)
	{
		printf("No se ha podido reservar memoria\n");
		exit(1);
	}
	
	while(fread(&((*vector)[cont]),sizeof(alumno),1,f)==1)
	{
		(cont)++;
	}
	fclose(f);
}


void imprimeVector(alumno *vector,int tam)
{
	int i;
	
	for(i=0;i<tam;i++)
	{
		printf("Nombre: %s\nDNI: %i\nNota: %0.2f\n",vector[i].nombre,vector[i].DNI,vector[i].nota);
	}
}

int  comparaAscendente(const void *a,const void*b)
{
	alumno *A=(alumno*)a;
	alumno *B=(alumno*)b;
	return((A->DNI)-(B->DNI));
}

void ordenaAscendente(alumno *vector,int tam)
{
	qsort(vector,tam,sizeof(alumno),comparaAscendente);
	
	printf("\nEl vector ordenado de forma ascendente quedaria de la siguiente manera:\n\n");
	imprimeVector(vector,tam);
}

int  comparaDescendente(const void *a,const void*b)
{
	alumno *A=(alumno*)a;
	alumno *B=(alumno*)b;
	return(B->DNI-A->DNI);
}

void ordenaDescendente(alumno *vector,int tam)
{
	qsort(vector,tam,sizeof(alumno),comparaDescendente);
	printf("\nEl vector ordenado de forma descendente quedaria de la siguiente manera:\n\n");
	imprimeVector(vector,tam);
}

