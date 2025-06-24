(deffunction imprime-tiempo "Función para dar formato a una fecha dada como segundos, minutos, horas y días"
    (?segs $?resto)
    (bind ?t (str-cat ?segs " segundos"))
    (switch (length$ $?resto)
        (case 0 then ?t)
        (case 1 then (str-cat (nth$ 1 $?resto) " minutos y " ?t))
        (case 2 then (str-cat (nth$ 2 $?resto) " horas, " (nth$ 1 $?resto) " minutos y " ?t))
        (case 3 then (str-cat (nth$ 3 $?resto) " días, " (nth$ 2 $?resto) " horas, " (nth$ 1 $?resto) " minutos y " ?t))
        (default "Expresión inválida")
    )
)

(defrule segundos-a-minutos "Pasa los segundos a minutos si procede"
    ?dirS <- (segundos ?segs&:(>= ?segs 60))
    ?cal <- (calcular)
    =>
    (printout t "Pasando de segundos a minutos..." crlf)
    (retract ?dirS ?cal)
    (assert (minutos (div ?segs 60)))
    (assert (segundos (mod ?segs 60)))
)
(defrule minutos-a-horas "Pasa los minutos a horas si procede"
    ?dirM <- (minutos ?mins&:(>= ?mins 60))
    =>
    (printout t "Pasando de minutos a horas..." crlf)
    (retract ?dirM)
    (assert (horas (div ?mins 60)))
    (assert (minutos (mod ?mins 60)))
)
(defrule horas-a-dias "Pasa las horas a días si procede"
    ?dirH <- (horas ?horas&:(>= ?horas 24))
    =>
    (printout t "Pasando de horas a días..." crlf)
    (retract ?dirH)
    (assert (dias (div ?horas 24)))
    (assert (horas (mod ?horas 24)))
)

(defrule comienza-transformacion
    =>
    (assert (calcular))
    (printout t "Preparado para calcular" crlf)
)

(defrule pedir-segundos "Pide los segudos iniciales a transformar"
    (calcular)
    =>
    (printout t "¿Cuántos segundos va a medir?: ")
    (assert (segundos (read)))
)

(defrule mostrar-resultado-1 "Una serie de reglas para imprimir según el resultado"
    (declare (salience -1))
    (segundos ?s)
    (not (fin))
    =>
    (assert (fin))
    (printout t (imprime-tiempo ?s) crlf)
)
(defrule mostrar-resultado-2
    (declare (salience -1))
    (segundos ?s) (minutos ?m)
    (not (fin))
    =>
    (assert (fin))
    (printout t (imprime-tiempo ?s ?m) crlf)
)
(defrule mostrar-resultado-3
    (declare (salience -1))
    (segundos ?s) (minutos ?m) (horas ?h)
    (not (fin))
    =>
    (assert (fin))
    (printout t (imprime-tiempo ?s ?m ?h) crlf)
)
(defrule mostrar-resultado-4
    (declare (salience -1))
    (segundos ?s) (minutos ?m) (horas ?h) (dias ?d)
    (not (fin))
    =>
    (assert (fin))
    (printout t (imprime-tiempo ?s ?m ?h ?d) crlf)
)