#primero de todo hay que definir los segmentos de memoria 
.data #se usa para definir el segmento de memoria del data 
str: .asciiz "Hola Mundo en MIPS32\n" #antes de .asciiz (en ayuda lo explica ) hay que ponerle una variable 
.text #se usa para definir el segmento de memoria del texto
main: la $a0, str #la es load adrres, cargamos en a0 la direccion de memoria de str
li $v0, 4 #carga el 4 en $v0
syscall
li $v0, 10 #carga el 10 en el $vo
syscall
