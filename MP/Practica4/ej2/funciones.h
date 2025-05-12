#ifndef EJE2_0
#define EJE2_0

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
void ordenaDescendente(alumno *vector,int tam);

#endif//EJE2_0
