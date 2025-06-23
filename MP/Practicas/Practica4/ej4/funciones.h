#ifndef EJE4
#define EJE4

typedef struct Monomio 
{
	int coef;
	int exp;
	struct Monomio *siguiente;
}monomio;

void aniadeMonomio(monomio **cabeza,int *nmonomios);
int contiene(monomio *cabeza,monomio temp);
void imprimeMonomio(monomio *cabeza);
void evaluaPolinomio(monomio *cabeza,int x);
void eliminarMonomio(monomio *cabeza);

#endif//EJE4
