;Ejemplo 1
;=========
(deftemplate dato
(slot w (default ?NONE))
(slot x (default ?DERIVE))
(slot y (default (gensym*)))
(slot z (default-dynamic (gensym*) )) )
