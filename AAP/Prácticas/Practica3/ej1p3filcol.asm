.data
matrix: .word 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15

M:      .word 4 #M=4
N:      .word 4 #N=4
space:	.asciiz " "
nl:	.asciiz "\n"

	.text
main:	lw $s0, M($0)     #Carga M
        lw $s1, N($0)     #Carga N
        li $t3, 1         #Mover M
        li $t4, 0         #Mover N
        li $t5, 0	   #Vector
        lw $a0, matrix($t5) #Guardo el dato
        addi $v0, $zero, 1
        syscall
        la $a0, space
	li $v0, 4
	syscall


loopN:	beq $t4, $s1, end

loopM:	addi $t5, $t5, 4
	lw $a0, matrix($t5)
	addi $v0, $zero, 1
	syscall
	
	la $a0, space
	li $v0, 4
	syscall
	
	addi $t3, $t3, 1
	bne $s0, $t3, loopM
	li $t3, 0
	addi $t4, ,$t4, 1
	
	la $a0, nl
	addi $v0, $zero, 4
	syscall
	
	bne $s1, $t4, loopN	
	
end:	li $v0, 10               # Finalizar programa
    	syscall