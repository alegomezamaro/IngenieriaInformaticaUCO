#Makefile de Aljandro Gómez Amaro

inicio: saludo compilar

saludo:
	@echo "Ejecutando el makefile de Alejandro Gómez Amaro"

compilar: main.o funciones.o
	@gcc main.o funciones.o funciones.h -o ejercicio.out

main.o:
	@gcc -c main.c

funciones.o:
	@gcc -c funciones.c

.PHONY: clean

clean:
	@echo "Limpiando"
	@rm *.o
	@rm min.txt
	@rm max.txt