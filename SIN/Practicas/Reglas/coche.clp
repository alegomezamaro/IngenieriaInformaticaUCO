(deftemplate coche "Estado general del coche"
    (slot estado (type SYMBOL) (allowed-symbols bueno regular malo))
)

(defrule estado_coche "Ejemplo de modificación de hechos"
    (componente_ruedas "flojas")
    (componente_velocidad "lenta")
    =>
    (assert (coche (estado malo)))
)

(defrule coche_arreglado "Ponemos el coche a punto"
    ?dir1 <- (coche (estado malo|regular))
    ?dir2 <- (componente_ruedas ?)
    ?dir3 <- (componente_velocidad ?)
    =>
    (modify ?dir1 (estado bueno))
    (retract ?dir2 ?dir3)
)

(deffacts hechos "Nuestra base de afirmaciones"
    (componente_ruedas "flojas")
    (componente_velocidad "lenta")
)