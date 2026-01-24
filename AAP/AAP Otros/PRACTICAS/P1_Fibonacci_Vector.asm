.data
fibs: .word 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  # Reserva espacio para almacenar los números de Fibonacci
size: .word 16  # Almacena el número de elementos de la secuencia que se calcularán
space: .asciiz " "  # Cadena que se utilizará para imprimir espacios en la salida
head: .asciiz "La sucesion de Fibonacci es "  # Encabezado de la salida

.text
la $s0, fibs  # Carga la dirección base de la matriz de Fibonacci en $s0
la $s5, size  # Carga la dirección de la variable "size" en $s5

lw $s5, 0($s5)  # Carga el valor de "size" en $s5
li $s2, 1  # Inicializa $s2 con el valor 1
sw $s2, 4($s0)  # Almacena el valor 1 en la primera posición de la matriz
sw $s2, 8($s0)  # Almacena el valor 1 en la segunda posición de la matriz
addi $s1, $s5, -3  # Inicializa $s1 con (size - 3), se resta 3 para ajustar el índice

loop:
    lw $s3, 4($s0)  # Carga el valor en la posición i-1 en $s3
    lw $s4, 8($s0)  # Carga el valor en la posición i-2 en $s4
    add $s2, $s3, $s4  # Calcula el valor de Fibonacci actual y lo almacena en $s2
    sw $s2, 12($s0)  # Almacena el valor calculado en la siguiente posición de la matriz
    addi $s0, $s0, 4  # Avanza a la siguiente posición de la matriz
    addi $s1, $s1, -1  # Decrementa el contador $s1
    bgtz $s1, loop  # Salta de nuevo a "loop" si $s1 es mayor que cero

la $a0, fibs  # Carga la dirección base de la matriz de Fibonacci en $a0
add $a1, $zero, $s5  # Carga el valor de "size" en $a1
jal print  # Llama a la función "print" para imprimir la secuencia

li $v0, 10  # Establece el código de la llamada al sistema para salir del programa
syscall  # Llama al sistema para salir

print:
    add $t0, $zero, $a0  # Copia la dirección base de la matriz a $t0
    add $t1, $zero, $a1  # Copia el valor de "size" a $t1
    la $a0, head  # Carga la dirección de la cadena "head" en $a0
    li $v0, 4  # Establece el código de la llamada al sistema para imprimir una cadena
    syscall  # Llama al sistema para imprimir el encabezado

    la $a0, space  # Carga la dirección de la cadena "space" en $a0
    li $v0, 4  # Establece el código de la llamada al sistema para imprimir una cadena
    syscall  # Llama al sistema para imprimir un espacio en blanco

out:
    lw $a0, 0($t0)  # Carga el valor actual de la matriz en $a0
    li $v0, 1  # Expresar que se imprime un entero
    syscall  # Llama al sistema para imprimir el valor

    la $a0, space  # Carga la dirección de la cadena "space" en $a0
    li $v0, 4  #Expresar que se imprime una cadena
    syscall  # Llama al sistema para imprimir un espacio en blanco

    addi $t0, $t0, 4  # Avanza a la siguiente posición de la matriz
    addi $t1, $t1, -1  # Decrementa el contador $t1
    bgtz $t1, out  # Salta de nuevo a "out" si $t1 es mayor que cero

    jr $ra  # Retorna de la función "print"
      
