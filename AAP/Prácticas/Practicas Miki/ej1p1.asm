
.data
size:       .word 16                # Tamaño del arreglo
data:       .space 64               # Espacio para almacenar los 16 números (4 bytes por cada uno)

.text
.globl main
main:

    li      $t0, 1                  
    li      $t1, 1                
    
    la      $t2, data              
    sw      $t0, 0($t2)           
    sw      $t1, 4($t2)          

    li      $t3, 2                 

for:

    lw      $t4, size              
    bge     $t3, $t4, fin        

   
    sub     $t5, $t3, 1             
    sub     $t6, $t3, 2             

    mul     $t5, $t5, 4             
    mul     $t6, $t6, 4             

    add     $t5, $t2, $t5           # Direccion de data[i-1]
    add     $t6, $t2, $t6           # Direccion de data[i-2]

    lw      $a0, 0($t5)             # Cargar data[i-1] en $a0
    lw      $a1, 0($t6)             # Cargar data[i-2] en $a1

    
    add     $t7, $a0, $a1           
    
    mul     $t8, $t3, 4            
    add     $t8, $t2, $t8           
    sw      $t7, 0($t8)             

   
    addi    $t3, $t3, 1
    j       for

fin:
   
    li      $v0, 4                 
    la      $a0, result_msg
    syscall


    li      $t3, 0                

print_for:
    lw      $t4, size               
    bge     $t3, $t4, exit          

    mul     $t5, $t3, 4            
    add     $t5, $t2, $t5          
    lw      $a0, 0($t5)            

    li      $v0, 1                 
    syscall

    li      $v0, 4                 
    la      $a0, space
    syscall

    addi    $t3, $t3, 1            
    j       print_for

exit:
    li      $v0, 10                 
    syscall

.data
result_msg: .asciiz "SUSESIÓN DE FIBONACCI:\n"
space:      .asciiz " "
