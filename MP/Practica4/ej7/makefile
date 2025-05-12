#Makefile de ejecucion programa 7


 all: Saludo libMemoria.a crucigrama.x clean

 Saludo:
	@echo Ejecutando el Makefile de David Guirado
	
 crucigrama.x:main.o ficheros.o crucigrama.o
	@gcc  main.o ficheros.o crucigrama.o -o crucigrama.x libMemoria.a
	
 libMemoria.a:reservaMemoria.o liberaMemoria.o 
	@ar rcs libMemoria.a reservaMemoria.o liberaMemoria.o
	
 main.o:main.c
	@gcc -c main.c -o main.o
	
 ficheros.o:ficheros.c
	@gcc -c ficheros.c -o ficheros.o
	
 crucigrama.o:crucigrama.c 
	@gcc -c crucigrama.c  -o crucigrama.o

 liberaMemoria.o:liberaMemoria.c 
	@gcc -c liberaMemoria.c -o liberaMemoria.o
	
 reservaMemoria.o:reservaMemoria.c
	@gcc -c reservaMemoria.c  -o reservaMemoria.o
	
 .PHONY:clean
	
 clean:
	@echo Borrando los archivos .o ...
	@rm *.o



