; Redefinimos MÓDULO PRINCIPAL con los exports necesarios.
(defmodule MAIN
    (export deftemplate dato)
)
(deftemplate dato
    (slot valor)
    (slot estado)
)
(defrule init =>
	(assert (dato (valor 25) (estado pendiente)))
	(focus C)
)

; MÓDULO que Captura un dato pendiente de procesar
(defmodule C
    (import MAIN deftemplate dato)
    (export ?ALL)
)
(defrule lectura
	(dato (valor ?x) (estado pendiente))
	=>
	(assert (dato (valor ?x) (estado a-procesar)))
	(focus P)
)

; MÓDULO que Procesa un dato
(defmodule P
    (import C ?ALL)
    (export ?ALL)
)
(defrule doblar
	(dato (valor ?x) (estado a-procesar))
	=>
	(assert (dato (valor (* 2 ?x)) (estado procesado)))
	(focus R)
)

; MÓDULO que Reinicia el dato
(defmodule R (import P ?ALL))
(defrule limpiar
	?dir <- (dato (estado procesado|a-procesar|pendiente))
	=>
	(retract ?dir)
)