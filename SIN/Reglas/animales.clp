(defrule sonido-perro
    (sonido guau)
    =>
    (printout t "El animal que hace guau es el perro" crlf)
)

(defrule sonido-gato
    (sonido miau)
    =>
    (printout t "El animal que hace miau es el gato" crlf)
)

(defrule sonido-gallo
    (sonido kikiriki)
    =>
    (printout t "El animal que hace kikiriki es el gallo" crlf)
)

(deffacts sonidos
    (sonido beee)
    (sonido miau)
    (sonido kikiriki)
)