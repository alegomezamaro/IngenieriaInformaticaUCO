(deffacts factoriales_iniciales
    (factorial 1 1)
)

(defrule busca_factorial
    (dame_factorial ?x)
    (factorial ?z&=(- ?x 1) ?y)
    =>
    (assert (factorial ?x (* ?x ?y))))

(defrule busca_factorial_sin_anterior
    (dame_factorial ?x)
    (not (factorial ?z&=(- ?x 1) ?))
    =>
    (assert (dame_factorial (- ?x 1))))

