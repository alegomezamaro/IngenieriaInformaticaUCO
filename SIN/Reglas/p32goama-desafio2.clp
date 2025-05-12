;Plantilla definiendo un producto de supermercado
(deftemplate producto
 (slot nombre)
 (slot precio)
)
;Plantilla definiendo la compra de un número de unidades de un producto
(deftemplate compra
 (slot producto)
 (slot unidades)
)

;El total de la compra quedará almacenado en un único hecho al final de la ejecución.
(deftemplate total
 (slot valor) ;El total de la compra
)

;Definición de los productos disponibles en el supermercado
(deffacts productos
 (producto (nombre leche) (precio 0.89))
 (producto (nombre pan) (precio 0.59))
 (producto (nombre chocolate) (precio 1.79))
 (producto (nombre tomate) (precio 1.37))
 (producto (nombre naranja) (precio 1.78))
 (producto (nombre arroz) (precio 1.42))
)
;Definición de algunas compras hechas por el usuario
(deffacts compras
 (compra (producto leche) (unidades 2))
 (compra (producto pan) (unidades 3))
 (compra (producto chocolate) (unidades 4))
)

;Inicializar total a 0
(defrule iniciar-total
   =>
   (assert (total (valor 0)))
)

;Los hechos de la plantilla compra podrán desaparecer de la base de hechos en la medida que se suman al
;total, si así se estima oportuno. Sin embargo, los de tipo producto deben conservase, ya que forman el
;stock del supermercado.
(defrule sumar-compra
   ?c <- (compra (producto ?nombre) (unidades ?u))
   ?p <- (producto (nombre ?nombre) (precio ?precio))
   ?t <- (total (valor ?v))
   =>
   (retract ?c) ;Eliminamos el hecho de compra
   (retract ?t) ;Eliminamos el hecho de total
   (bind ?subtotal (* ?u ?precio)) ;Calculamos el subtotal de la compra
   (assert (total (valor (+ ?v ?subtotal)))) ;Sumamos el subtotal al total
)

;Al terminar, debe imprimir por pantalla el valor total de la compra. La regla encargada de imprimir
;por pantalla tendrá una prioridad inferior al resto, para asegurar que se dispara la última.
(defrule mostrar-total
   (declare (salience -20)) ;Baja prioridad para que se ejecute al final
   ?t <- (total (valor ?v))
   =>
   (printout t "Total: " ?v crlf)
)
