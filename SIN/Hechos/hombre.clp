(defrule r-hombre-animal
	(hombre ?x)
	=>
	(assert (animal ?x))
)
(defrule r-animal-respira
	(animal ?x)
	=>
	(assert (respira ?x))
)

(assert (hombre Juan))