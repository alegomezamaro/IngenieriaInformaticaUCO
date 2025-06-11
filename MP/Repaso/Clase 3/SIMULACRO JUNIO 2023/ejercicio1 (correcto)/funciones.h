#ifndef EXAMEN
#define EXAMEN

#define LENGTH 100
struct datos
{
   int codigo;
   char nombre[LENGTH];
   float pesoKg;  //ej. 56.8  
   float alturaM; //ej. 1.65     
};

void ejercicio1(int nEle, struct datos* Vector, int criterio);

//INCLUYE AQUI LOS PROTOTIPOS DE TUS FUNCIONES

int nombreDescendente(struct datos a, struct datos b);

int IMCAscendente(struct datos a, struct datos b);

void ordena(struct datos * v, int tam, int (*metodo)(struct datos a, struct datos b));

#endif
