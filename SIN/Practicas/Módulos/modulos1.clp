(defmodule MAIN (export ?ALL))
(deftemplate MAIN::objetivo
    (slot nombre)
    (slot estado)
)
(defrule MAIN::ejemplo-foco
    =>
    (printout t "Disparo en el modulo MAIN." crlf)
    (assert (objetivo (nombre principal) (estado resuelto)))
    (focus A B)
)

(defmodule A
    (export ?ALL)
    (import MAIN deftemplate objetivo)
)
(deftemplate A::subobjetivo-A
    (slot nombre)
    (slot estado)
)
(defrule A::regla-ejemplo
    (objetivo (nombre principal) (estado resuelto))
    =>
    (printout t "Disparando la regla en modulo A" crlf)
    (assert (subobjetivo-A (estado resuelto)))
)

(defmodule B
    (import A deftemplate subobjetivo-A)
    (import MAIN deftemplate objetivo)
)
(defrule B::regla-ejemplo
    (objetivo (estado resuelto))
    (subobjetivo-A (estado resuelto))
    =>
    (printout t "Disparando la regla en el modulo B" crlf)
)