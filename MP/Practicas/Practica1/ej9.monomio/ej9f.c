#include "ej9f.h"

void leerMonomio(struct Monomio *m){

    printf("\nCoeficiente: ");
    scanf("%i", &m->coeficiente);
    printf("Grado: ");
    scanf("%i", &m->grado);
}

void imprimirMonomio(struct Monomio m){

    printf("%dx^%d", m.coeficiente, m.grado);
}

void leerPolinomio(struct Monomio p[]){

    for(size_t i=0; i<TAM; i++){

        leerMonomio(&p[i]);
        printf("\n");
    }
}

void imprimirPolinomio(struct Monomio p[]){

    for(size_t i=0; i<TAM; i++){

        imprimirMonomio(p[i]);

        if(i != (TAM-1)){

            printf(" + ");
        }
    }
    printf("\n");
}

void mayorMenor(struct Monomio p[], struct Monomio *menor, struct Monomio *mayor){

    *mayor=p[0];
    *menor=p[0];


    for(size_t i=1; i<TAM; i++){

        if(mayor->grado < p[i].grado){

            *mayor = p[i];
        }

        if(mayor->grado == p[i].grado){

            if(mayor->coeficiente < p[i].coeficiente){

                *mayor = p[i];
            }
        }

        if(menor->grado > p[i].grado){

            *menor = p[i];
        }

        if(menor->grado == p[i].grado){

            if(menor->coeficiente > p[i].coeficiente){

                *menor = p[i];
            }
        }
    }
}

void evaluarPolinomio(struct Monomio p[]){

    double punto, suma=0;

    printf("\nIntroduce el punto en el que evaluar el polinomio: ");
    scanf("%lf", &punto);

    for(size_t i=0; i<TAM; i++){

        suma += (p[i].coeficiente * pow(punto, p[i].grado));
    }

    printf("\nEl polinomio en el punto %.2f es %.2f\n", punto, suma);
}