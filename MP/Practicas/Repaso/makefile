inicio: saludo compilar

saludo:
	@echo "Este es el makefile de repaso de Alejandro"

compilar: main.o funciones.o
	gcc -Wall main.o funciones.o -o ej.exe

main.o:
	gcc -c main.c

funciones.o:
	gcc -c funciones.c

.PHONY:
clear:
	rm main.o funciones.o
clearall:
	rm main.o funciones.o ej.exe