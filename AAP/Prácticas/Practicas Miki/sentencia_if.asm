#if (i==j) h = i + j; else h = i - j

.data
str:	.asciiz "Sentencia if ha terminado\nValor del registro $s3 = "

.text
	li $v0, 5
	syscall
	move $s0, $v0
	li $v0, 5
	syscall
	move $s1, $v0

	bne $s0, $s1, Else #salta alelse si no son iguales
	add $s3, $s0, $s1 # tres tipo r es suma
	j Exit #salta a exit
Else:	sub $s3, $s0, $s1 # tres tipo r es resta
Exit:	la $a0, str
	li $v0, 4
	syscall
	move $a0, $s3
	li $v0, 34
	syscall
	li $v0, 10
	syscall
