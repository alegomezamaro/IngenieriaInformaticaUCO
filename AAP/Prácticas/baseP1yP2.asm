	.data
dato:	.byte 40 

	.text
main :	lb $s0 , octeto+1( $0 )
	addi $t0 , $zero , 100
	addi $t1 , $zero , 50
	add $t2 , $t0 , $t1
	sub $t3 , $t0 , $
	lw $t4, dato($0)
bucle:	sub $t3, $t0, $t1 
