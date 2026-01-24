.data
fib_values: .space 40   # Reservamos espacio para almacenar los valores de Fibonacci
n:          .word 16    # Número de términos de Fibonacci a calcular
coma: .asciiz ", "
enunciado: .asciiz "La sucecion de fibonacci es :"
.text
.globl main

main:
    # Cargar el número de términos a calcular
    lw $t0, n   # Cargar el valor original de n
    subi $t0, $t0, 2  # Restar 2 a n
    li $t1, 0     # Inicializar el primer número de Fibonacci (F0) a 0
    li $t2, 1     # Inicializar el segundo número de Fibonacci (F1) a 1
    
    la $a0,enunciado #imprimir la coma
    li $v0,4
    syscall
    

    # Imprimir los primeros dos números de Fibonacci (0 y 1)
    move $a0, $t1   # Cargamos F0 para imprimir
    li $v0, 1       # Código de servicio para imprimir un entero
    syscall
    
    la $a0,coma #imprimir la coma
    li $v0,4
    syscall
    
    move $a0, $t2   # Cargamos F1 para imprimir
    li $v0, 1       # Código de servicio para imprimir un entero
    syscall
    
    la $a0,coma #imprimir la coma
    li $v0,4
    syscall
    
    # Iniciar bucle para calcular los términos restantes
    loop:
        # Calcular el siguiente término de Fibonacci (F2 = F0 + F1)
        add $t3, $t1, $t2

        # Imprimir el término actual
        move $a0, $t3
        li $v0, 1
        syscall

        
        # Actualizar los valores de F0 y F1 para la siguiente iteración
        move $t1, $t2
        move $t2, $t3

        # Decrementar el contador de términos restantes
        subi $t0, $t0, 1

        # Comprobar si hemos calculado todos los términos
        beqz $t0, exit
        
        la $a0,coma #imprimir la coma
        li $v0,4
        syscall


        # Saltar de nuevo al bucle
        j loop

    exit:
        li $v0, 10  # Salir del programa
        syscall