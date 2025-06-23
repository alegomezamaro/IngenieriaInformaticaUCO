#Makefile de compilacion de eje3

all:Saludo eje3.exe clean

Saludo:
	@echo Compilando el programa de David Guirado

eje3.exe:main.o funciones.o
	@gcc -o eje3.exe main.o funciones.o 
	
main.o: main.c funciones.h
	@gcc -c main.c 
	
funciones.o: funciones.c funciones.h
	@gcc -c funciones.c 
	
 .PHONY: clean

clean:
	@echo Archivos .o borrados
	@rm funciones.o main.o
	
	
