.data
matrix: .word 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
M:      .word 4          # filas
N:      .word 4          # columnas
space:  .asciiz " "
nl:     .asciiz "\n"

.text
.globl main
main:
    lw   $s0, M($zero)       # M = filas
    lw   $s1, N($zero)       # N = columnas
    la   $t0, matrix         # base matriz

    li   $t4, 0              # j = 0 (columna)
loopN:
    bge  $t4, $s1, end       # if j >= N -> fin

    li   $t3, 0              # i = 0 (fila)
loopM:
    bge  $t3, $s0, salto   # if i >= M -> siguiente columna

    # offset = (i*N + j)*4
    mul  $t2, $t3, $s1       # i*N
    add  $t2, $t2, $t4       # i*N + j
    sll  $t2, $t2, 2         # *4 (bytes)
    add  $t5, $t0, $t2       # dirección del elemento

    lw   $a0, 0($t5)         # cargar elemento
    li   $v0, 1
    syscall

    # imprimir espacio
    la   $a0, space
    li   $v0, 4
    syscall

    addi $t3, $t3, 1         # i++
    j    loopM

salto:
    # salto de línea tras cada columna
    la   $a0, nl
    li   $v0, 4
    syscall

    addi $t4, $t4, 1         # j++
    j    loopN

end:
    li   $v0, 10
    syscall
