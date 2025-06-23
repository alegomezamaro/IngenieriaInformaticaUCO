#Este es el makefile de compilacion del ejercicio4

all:Saludo eje4.exe clean

Saludo: 
	@echo Compilando el programa de David Guirado...
	
eje4.exe:main.o funciones.o
	@gcc main.o funciones.o -lm -o eje4.exe 

main.o:main.c funciones.h
	@gcc main.c -lm -c main.o
	
funciones.o:funciones.c  funciones.h
	@gcc funciones.c -lm -c funciones.o

 .PHONY: clean

clean:
	@echo Archivos .o borrados con exito
	@rm *.o
