#include <stdio.h>
#include "colas.h"

/*
Colas de impresión.
La biblioteca colas.a contiene las operaciones básicas para trabajar con colas. Utilizando
únicamente estas operaciones, diseña un programa que simule el funcionamiento de una
impresora con dos colas de impresión:
	a) Cola de impresión normal (usuarios normales)
	b) Cola especial (superusuarios)
Codificar un programa que, mediante un menú, deberá permitir las siguientes acciones:
- Introducir un trabajo en la cola normal solicitando el login del usuario y el fichero.
- Introducir un trabajo en la cola especial solicitando el login del usuario y el fichero.
- Mostrar el estado de las colas.
- Imprimir.
	- Tomará un trabajo de la cola y mostrará el login del propietario, el nombre del
	fichero y el mensaje: “fichero impreso”.
	- A la hora de imprimir, tendrán precedencia los trabajos de la cola especial, pero con
	la siguiente restricción:
		- No se podrán imprimir de forma consecutiva más de k trabajos de la cola de
		impresión especial si hay algún trabajo en la cola de impresión normal.
		- El valor inicial de k será 3.
	- Modificar el contador de la cola especial. Modificará el valor de k (k ≥1)
	- Terminar
*/

int main()
{
	struct nodo *colaNormalCabeza=NULL;
	struct nodo *colaEspecialCabeza=NULL;
	int opcionMenu=1;
	int k=3;
	struct trabajo aux;
	
	
	while(opcionMenu>0 && opcionMenu<6)
	{
	
		printf("1-Introducir un trabajo en la cola normal\n");
		printf("2-Introducir un trabajo en la cola especial\n");
		printf("3-Ver el estado de las colas.\n");
		printf("4-Imprimir cola\n");
		printf("5-Modificar el contador de la cola especial\n");
		printf("6-EXIT\n");
		
		scanf("%i",&opcionMenu);
		
		switch(opcionMenu)
		{
			case 1:
			{
				printf("Introduzca el login de usuario:\n");
				scanf("%i",&aux.login);
				getchar();
				
				printf("Introduzca el nombre del fichero:\n");
				fgets(aux.nombre,25,stdin);
				
				printf("Login: %i\tNombre: %s\n",aux.login,aux.nombre);
				
				insertaCola(&colaNormalCabeza, aux);
			
				
			}break;
			case 2:
			{
				printf("Introduzca el login de usuario especial:\n");
				scanf("%i",&aux.login);
				getchar();
				
				printf("Introduzca el nombre del fichero:\n");
				fgets(aux.nombre,25,stdin);
				
				insertaCola(&colaEspecialCabeza, aux);
			
			}break;
			case 3:
			{
				
				printf("La cola de impresion normal es:\n");
				
				struct nodo *aux=colaNormalCabeza;
				while(aux!=NULL)
				{
					printf("Login:%i\tNombre:%s\n",aux->elemento.login,aux->elemento.nombre);
					aux=aux->sig;
				}
				printf("\n");
				
				printf("La cola de impresion especial es:\n");
				
				aux=colaEspecialCabeza;
				while(aux!=NULL)
				{
					printf("Login:%i\tNombre:%s\n",aux->elemento.login,aux->elemento.nombre);
					aux=aux->sig;
				}
				
			}break;
			case 4:
			{
				struct nodo *aux1=NULL;
				aux1=colaNormalCabeza;
				struct nodo *aux2=NULL;
				aux2=colaEspecialCabeza;
				int cont=0;
				
				while((aux1!=NULL)||(aux2!=NULL))
				{
					while((aux2!=NULL)&&(cont<k))
					{
				   		printf("Cola Especia:\nLogin:%i\tNombre:%s\n",aux2->elemento.login,aux2->elemento.nombre);
						aux2=aux2->sig;
						cont++;
					}	
			        printf("Cola Normal:\nLogin:%i\tNombre:%s\n",aux1->elemento.login,aux1->elemento.nombre);
					aux1=aux1->sig;
					cont=0;
				}
			}break;
			case 5:
			{
				printf("Introduzca el nuevo valor de k\n");
				scanf("%i",&k);
			}break;
			
		}
	}
	return 0;
}
