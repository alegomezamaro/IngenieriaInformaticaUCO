#include "funciones.h"

/*
MODELO EXAMEN. Cada ejercicio:
- main.c (NO TOCAR)
- funciones.o (NO TOCAR)
- funciones.h (NO TOCAR, se pueden usar las funciones)
- examen.c
- examen.h
1.- a. Memoria dinamica
	b. Ficheros
2.- a. Ordenacion (la que queramos)
	b. Quicksot (stdlib.h)
	c. Recursividad
3.- a. Listas, pilas y colas
	b. Makefile (All (todas las ordenes), crear bibliotecas y .PHONY)

Vectores
1. reservarMemoria
2. rellenarMemoria
3. imprimirVector 
4. liberarMemoria

Ficheros
5. existeFichero

...de texto
6. mostrarFichero
7. añadirAlumno
8. modificarAlumno
9. borrarAlumno
10. contarFichero
11. ficheroVector
12. vectorFichero
13. ficheroFicheroB

...binarios
14. mostrarFicheroB
15. añadirProducto
16. modificarProducto
17. borrarProducto
18. contarFicheroB
19. ficheroBVector
20. vectorFicheroB

Pilas
21. inyectarDelante
22. inyectarDetras
23. nuevoElemento
24. mostrarLista
25. contarElemento
26. buscaElemento
27. borrarElemento
28. borrarLista
29. mostrarListaRecursiva

Ordenacion
30. ordenaAscendente
31. ordenaDescendente
32. comparaAscendente
33. comparaDescendente
*/

int main(int argc, char **argv){ 
	
	inyectarDelante();
	inyectarDetras();
	nuevoElemento();
	mostrarLista();
	contarElemento();
	buscaElemento();
	borrarElemento();
	borrarLista();
	mostrarListaRecursiva();

	return 0;
}