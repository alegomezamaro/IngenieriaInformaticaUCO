(deffunction media1 "Función para calcular la media usando while"
    ($?vector)
	(bind ?longitud (length$ $?vector))
	(bind ?suma 0)
	(while (> (length$ $?vector) 0)
		do
		(bind ?actual (nth$ 1 (first$ $?vector)))
		(bind ?suma (+ ?suma ?actual))
		(bind $?vector (rest$ $?vector))
	)
	(/ ?suma ?longitud)
)

(deffunction media2 "Función para calcular la media usando for"
    ($?vector)
    (bind ?suma 0)
    (bind ?index 1)
    (bind ?longitud (length$ $?vector))
    (loop-for-count (?index ?longitud)
        do
        (bind ?actual (nth$ ?index $?vector))
        (bind ?suma (+ ?suma ?actual))
    )
    (/ ?suma ?longitud)
)