#Funcion orden a la que se llamara con make y que enorden hara saludo y posteriormente compilar
inicio: saludo compilar

saludo:
	@echo Ejecutando el makefile de Alejandro Gomez Amaro

#Compilar a su vez llamara antes de a si misma a las funciones main.o y funciones.o
compilar: main.o funciones.o
	gcc -Wall main.o funciones.o -o ejecutable.exe

main.o:
	gcc -c main.c

funciones.o:
	gcc -c funciones.c