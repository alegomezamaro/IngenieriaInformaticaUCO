inicio: saludo compilar

saludo:
	@echo "Este es el make de Alejandro"

compilar: main.o funciones.o
	@gcc main.o funciones.o

main.c: main.c
	@gcc -c main.c

funciones.c: funciones.c
	@gcc -c funciones.c

.PHONY:
clean:
	@rm main.o funciones.o