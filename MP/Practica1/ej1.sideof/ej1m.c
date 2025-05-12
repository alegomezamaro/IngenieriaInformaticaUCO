#include <stdio.h>

int main(){
	int a, *b, **c;
	double d, *e, **f;
	char g, *h, **i;
	
	printf("Tamaño de a : %u\n", sizeof(a));
	printf("Tamaño de b : %u\n", sizeof(b));
	printf("Tamaño de c : %u\n", sizeof(c));
	printf("Tamaño de d : %u\n", sizeof(d));
	printf("Tamaño de e : %u\n", sizeof(e));
	printf("Tamaño de f : %u\n", sizeof(f));
	printf("Tamaño de g : %u\n", sizeof(g));
	printf("Tamaño de h : %u\n", sizeof(h));
	printf("Tamaño de i : %u\n", sizeof(i));
}
