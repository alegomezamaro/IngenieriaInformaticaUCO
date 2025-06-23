#Makefile para crear las bibliotecas de la práctica 4
CFLAGS = -c -g -ansi -Wall

all:eje5.exe clean

eje5.exe:main.o colas.a 
	gcc main.o -o eje5.exe colas.a

main.o:main.c
	gcc $(CFLAGS) main.c 

bib: pilas.a colas.a

colas.a: colas.o
	ar -rsv colas.a colas.o
	
pilas.a: pilas.o
	ar -rsv pilas.a pilas.o

pilas.o: pilas.c pilas.h
	gcc $(CFLAGS) pilas.c

colas.o: colas.c colas.h
	gcc $(CFLAGS) colas.c

clean:
	rm -f *.o 


