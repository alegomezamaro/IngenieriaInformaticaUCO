.data
str:	.asciiz "Sentencia if ha terminado\nValor del registro $s3 = "

.text
	li $v0, 5
 	syscall
 	move $s0, $v0
 	li $s1 ,1
 for:
 	addi $s1,$s1,1
 	move $a0,$s1
 	li $v0,1
 	syscall
 	bne $s0,$s1 for
 	
 
 		
 	