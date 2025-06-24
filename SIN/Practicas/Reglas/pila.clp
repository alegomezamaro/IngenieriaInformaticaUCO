(deffacts init-estructuras-datos
	(pila)
    (cola)
    (dato 4) ; Los datos los declaro en el orden inverso al que quiero que los lea CLIPS porque siempre toma los más recientes primero.
    (dato 3)
    (dato 2)
    (dato 1)
)
(defrule push
    (declare (salience 10))
	?pila <- (pila $?x)
	?dato <- (dato ?y)
	(modo pila)
	=>
	(retract ?pila ?dato)
	(assert (pila ?y $?x))
)

(defrule pop
	?pila <- (pila ?x $?y)
	(modo pila)
    =>
	(retract ?pila)
	(assert (pila $?y) (extraido ?x))
)

; ¿Cómo se haría una cola?

(defrule enqueue
	(declare (salience 10))
	?cola <- (cola $?x)
	?dato <- (dato ?y)
	(modo cola)
	=>
	(retract ?cola ?dato)
	(assert (cola ?y $?x))
)

(defrule dequeue
	?cola <- (cola $?y ?x)
	(modo cola)
	=>
	(retract ?cola)
	(assert (cola $?y) (dato ?x))
)