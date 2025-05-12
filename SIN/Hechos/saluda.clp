(defrule r-saluda (saluda ?x)
	=> (printout t"Hola, " ?x crlf))
(assert (saluda Alejandro))