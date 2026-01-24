        .data
        # A almacenada en column-major order (M x K)
mat_A:  .word 0, 4, 8, 12,
              1, 5, 9, 13,
              2, 6, 10, 14,
              3, 7, 11, 15

        # B almacenada en column-major order (K x N)
mat_B:  .word 0, 4, 8, 12,
              1, 5, 9, 13,
              2, 6, 10, 14,
              3, 7, 11, 15

        # C almacenada en row-major order (M x N)
mat_C:  .word 0, 0, 0, 0,
              0, 0, 0, 0,
              0, 0, 0, 0,
              0, 0, 0, 0

M:      .word 4         # M = 4
N:      .word 4         # N = 4
K:      .word 4         # K = 4

newline:    .asciiz "\n"
space:      .asciiz " "

        .text
        .globl main
main:
        # Cargar dimensiones
        lw  $s0, M($zero)     # $s0 = M
        lw  $s1, N($zero)     # $s1 = N
        lw  $s2, K($zero)     # $s2 = K

        li  $t3, 0            # i = 0 (fila de C)

########################################
# CÁLCULO DE C = A * B
########################################
loop_i:                         # for (i = 0; i < M; i++)
        bge $t3, $s0, end_calc  # if (i >= M) -> fin del cálculo

        li  $t4, 0             # j = 0 (columna de C)

loop_j:                         # for (j = 0; j < N; j++)
        bge $t4, $s1, next_i   # if (j >= N) -> siguiente fila

        # Índice de C(i,j) en row-major: indexC = i*N + j
        mul $t6, $t3, $s1      # t6 = i * N
        add $t6, $t6, $t4      # t6 = i*N + j
        sll $t6, $t6, 2        # t6 = (i*N + j) * 4 (bytes)

        li  $t2, 0             # acumulador = 0
        li  $t5, 0             # z = 0

loop_k:                         # for (z = 0; z < K; z++)
        bge $t5, $s2, store_C  # if (z >= K) -> guardar resultado

        ########################################
        # A(i,z) en column-major: indexA = i + z*M
        ########################################
        mul $t7, $t5, $s0      # t7 = z * M
        add $t7, $t7, $t3      # t7 = z*M + i
        sll $t7, $t7, 2        # t7 = (z*M + i) * 4
        lw  $t0, mat_A($t7)    # t0 = A(i,z)

        ########################################
        # B(z,j) en column-major: indexB = z + j*K
        ########################################
        mul $t8, $t4, $s2      # t8 = j * K
        add $t8, $t8, $t5      # t8 = j*K + z
        sll $t8, $t8, 2        # t8 = (j*K + z) * 4
        lw  $t1, mat_B($t8)    # t1 = B(z,j)

        ########################################
        # Producto y suma al acumulador
        ########################################
        mul $t9, $t0, $t1      # t9 = A(i,z) * B(z,j)
        add $t2, $t2, $t9      # acumulador += t9

        addi $t5, $t5, 1       # z++
        j    loop_k

store_C:
        # Guardar C(i,j) = acumulador
        sw  $t2, mat_C($t6)

        addi $t4, $t4, 1       # j++
        j    loop_j

next_i:
        addi $t3, $t3, 1       # i++
        j    loop_i

end_calc:
########################################
# IMPRESIÓN DE LA MATRIZ C (4x4)
########################################
        li  $t3, 0             # i = 0

print_i:                       # for (i = 0; i < M; i++)
        bge $t3, $s0, end      # if (i >= M) -> salir

        li  $t4, 0             # j = 0

print_j:                       # for (j = 0; j < N; j++)
        bge $t4, $s1, print_newline  # if (j >= N) -> salto de línea

        # indexC = i*N + j (row-major)
        mul $t6, $t3, $s1      # t6 = i * N
        add $t6, $t6, $t4      # t6 = i*N + j
        sll $t6, $t6, 2        # *4 (bytes)

        lw  $a0, mat_C($t6)    # cargar C(i,j)
        li  $v0, 1             # print_int
        syscall

        # Imprimir espacio
        li  $v0, 4
        la  $a0, space
        syscall

        addi $t4, $t4, 1       # j++
        j    print_j

print_newline:
        # salto de línea al final de cada fila
        li  $v0, 4
        la  $a0, newline
        syscall

        addi $t3, $t3, 1       # i++
        j    print_i

end:
        li  $v0, 10
        syscall
