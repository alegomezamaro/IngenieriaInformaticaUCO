(deftemplate superheroe
    (slot nombre)
    (slot estado (allowed-values ocupado libre))
)
(deffacts plantilla
    (superheroe (nombre spiderman) (estado libre))
    (superheroe (nombre viuda-negra) (estado ocupado))
    (superheroe (nombre drextrange) (estado libre))
    (superheroe (nombre capitana-marvel))
)
(defrule salvar-dia "Necesitamos que un súper heroe salve el día"
    (superheroe (estado libre))
    =>
    (printout t "El día está salvado" crlf)
)