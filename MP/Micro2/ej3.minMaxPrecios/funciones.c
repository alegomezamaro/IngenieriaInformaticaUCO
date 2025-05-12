#include "funciones.h"

void funcion(char* fb, char* ftmin, char* ftmax){

	FILE* fbin;
	FILE* fmin;
	FILE* fmax;
	struct producto p;
	float prec;

	if((fbin=fopen(fb, "rb"))==NULL){

		printf("\nError al intentar abrir %s\n", fb);
		exit(-1);
	}

	if((fmin=fopen(ftmin, "w"))==NULL){

		printf("\nError al intentar abrir %s\n", ftmin);
		fclose(fbin);
		exit(-1);
	}

	if((fmax=fopen(ftmax, "w"))==NULL){

		printf("\nError al intentar abrir %s\n", ftmax);
		fclose(fbin);
		fclose(fmin);
		exit(-1);
	}

	printf("\nIntroduce el valor que dividira los ficheros en menor y mayor: ");
	scanf("%f", &prec);
	printf("\n");

	while(fread(&p, sizeof(struct producto), 1, fbin)==1){
		
		if(p.precio < prec){

			fprintf(fmin, "%s\n%i\n%f\n%i\n", p.nombre, p.cod, p.precio, p.unidades);
		}

		else{

			fprintf(fmax, "%s\n%i\n%f\n%i\n", p.nombre, p.cod, p.precio, p.unidades);
		}
	}

	fclose(fbin);
	fclose(fmin);
	fclose(fmax);

}