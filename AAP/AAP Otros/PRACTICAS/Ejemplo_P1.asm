.data
array: .word 1,2,3,4,5,6,7,8
size: .word 8
print: .asciiz "los valores del vector son"
space: .asciiz " "
.text

la $a0,print
li $v0, 4
syscall

lw $t0, size
sll $t0,$t0,2
li $t1, 0

loop:la $a0,space
li $v0,4
syscall

lw $a0,array($t1)
li $v0,1
syscall

add $t1  $t1 4
bne $t1,$t0,loop


end: li $v0,10
syscall