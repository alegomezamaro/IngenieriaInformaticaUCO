    .data
size:       .word 16                      # Tamaño de la matriz (16x16)
data:       .space 1024                   # Espacio para 256 enteros (16*16 = 256, cada entero ocupa 4 bytes)
newline:    .asciiz "\n"                  # Carácter de nueva línea para formato de impresión

    .text
    .globl main
main:
    # Inicializar variables
    la $t0, data              # Cargar la dirección base de data en $t0
    li $t1, 0                 # Inicializar value = 0

    # Loop exterior: iteración por filas
    li $t2, 0                 # row = 0
row_loop:
    bge $t2, 16, print_matrix # Si row >= size (16), saltar a la impresión
    mul $t3, $t2, 16          # Calcular el desplazamiento de la fila (row * size) y guardar en $t3

    # Loop interior: iteración por columnas
    li $t4, 0                 # col = 0
col_loop:
    bge $t4, 16, next_row     # Si col >= size (16), ir a la siguiente fila
    add $t5, $t3, $t4         # Calcular el índice lineal (col + (size * row))
    mul $t5, $t5, 4           # Multiplicar por 4 porque cada palabra es de 4 bytes
    add $t6, $t0, $t5         # Dirección de data[col + (size * row)]
    sw $t1, 0($t6)            # Guardar value en data[col + (size * row)]
    addi $t1, $t1, 1          # Incrementar value
    addi $t4, $t4, 1          # Incrementar col
    j col_loop                # Volver al inicio del bucle col

next_row:
    addi $t2, $t2, 1          # Incrementar row
    j row_loop                # Volver al inicio del bucle row

# Impresión de la matriz
print_matrix:
    li $t2, 0                 # row = 0
print_row_loop:
    bge $t2, 16, exit         # Si row >= size (16), salir del programa
    mul $t3, $t2, 16          # Calcular el desplazamiento de la fila (row * size)

    # Loop para imprimir cada columna de la fila actual
    li $t4, 0                 # col = 0
print_col_loop:
    bge $t4, 16, print_newline # Si col >= size (16), imprimir salto de línea
    add $t5, $t3, $t4         # Calcular el índice lineal (col + (size * row))
    mul $t5, $t5, 4           # Multiplicar por 4
    add $t6, $t0, $t5         # Dirección de data[col + (size * row)]
    lw $a0, 0($t6)            # Cargar el valor de data[col + (size * row)] en $a0
    li $v0, 1                 # Llamada de sistema para imprimir un entero
    syscall

    # Separador entre columnas
    li $a0, 32                # ASCII para espacio
    li $v0, 11                # Llamada de sistema para imprimir un carácter
    syscall

    addi $t4, $t4, 1          # Incrementar col
    j print_col_loop          # Volver al inicio del bucle col

print_newline:
    # Imprimir un salto de línea al final de cada fila
    li $v0, 4                 # Llamada de sistema para imprimir cadena
    la $a0, newline           # Cadena de nueva línea
    syscall

    addi $t2, $t2, 1          # Incrementar row
    j print_row_loop          # Volver al inicio del bucle row

# Salida del programa
exit:
    li $v0, 10                # Llamada de sistema para terminar el programa
    syscall
