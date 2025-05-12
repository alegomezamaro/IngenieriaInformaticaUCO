(defmodule MAIN (export ?ALL))
(deftemplate MAIN::objetivo (slot nombre) (slot estado))
(defrule MAIN::ejemplo-foco
	=>
	(printout t "Disparo en el modulo MAIN." crlf)
	(assert (objetivo (nombre principal) (estado resuelto)))
	(focus A B)
)
(defmodule A
	(export ?ALL)
	(import MAIN deftemplate initial-fact objetivo)
)
(deftemplate A::subobjetivo-A (slot nombre) (slot estado))
(defrule A::regla-ejemplo
	(objetivo (nombre principal) (estado resuelto))
	=>
	(assert (subobjetivo-A (estado resuelto)))
	(printout t "Disparando la regla en el modulo A." crlf)
)
(defmodule B (import A deftemplate subobjetivo-A) (import MAIN deftemplate initial-fact))
(defrule B::regla-ejemplo
	(subobjetivo-A (estado resuelto))
	=>
	(printout t "Disparando la regla en el modulo B." crlf)
)
