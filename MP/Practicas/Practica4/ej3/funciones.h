#ifndef EJE3_0
#define EJE3_0

typedef struct
{

	char nombre[50];
	int DNI;
	float nota;
	
}alumno;

void rellenaVector(alumno **vector,char fname[50],int *tam);
void tamañoStruct(char fname[50],int *tam);
void imprimeVector(alumno *vect,int tam);
void ordenaAscendente(alumno *vector,int tam);
int  comparaAscendente(const void *a,const void*b);
void ordenaDescendente(alumno *vector,int tam);
int  comparaDescendente(const void *a,const void*b);

#endif//EJE3_0
