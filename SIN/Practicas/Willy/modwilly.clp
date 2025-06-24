;moveWilly desplaza a Willy
;Noise sonido alienígena
;Pull sonido agujero negro
;FireLaser dispara el láser


;Definiciones iniciales

   (deffacts coordenadasInicio ;Define la posición incial de Willy (0,0)
      (coordenadas 0 0)
      (coordenadaX 0)
      (coordenadaY 0)
   )

;Movimientos

   (defrule moveNorth ;Mueve a Willy al norte (una casilla hacia arriba)
      (directions $? north $?) ;Si hay una dirección norte en la lista de direcciones
      (not(percepts Noise)) ;Si no hay ruido de alien 
      (not(percepts Pull)) ;Si no hay ningun agujero negro
      (not(percepts Noise Pull)) ;Si no hay ruido de alien y agujero
      (not(percepts Pull Noise)) ;Si no hay ruido de agujero y alien
      ?p1<-(coordenadas ?x ?y) ;Guarda las coordendas actuales en la variable ?p1
      ?p2<-(coordenadaX ?z) ;Guarda la última coordenada X en la variable ?p2
      ?p3<-(coordenadaY ?t) ;Guarda la última coordenada Y en la variable ?p3
      (not(test(=(- ?y 1) ?t))) ;Verifica que al moverse no se repita la coordenada Y
      => ;Si se cumplen todas las condiciones entonces
      (moveWilly north) ;Ejecuta la acción de mover a Willy al norte
      (retract ?p1) ;Elimina la coordenada actual
      (retract ?p2) ;Elimina la coordenada X 
      (retract ?p3) ;Elimina la coordenada Y
      (assert(coordenadas ?x (- ?y 1))) ;Actualiza coordenadas (y-1)
      (assert(coordenadaX ?x)) ;Guarda X actual (no cambia)
      (assert(coordenadaY ?y)) ;Guarda la nueva Y
   )

   (defrule moveSouth ;Mueve a Willy al sur (una casilla hacia abajo)
      (directions $? south $?) ;Si hay una dirección sur en la lista de direcciones
      (not(percepts Noise)) ;Si no hay ruido de alien
      (not(percepts Pull)) ;Si no hay ningun agujero  
      (not(percepts Noise Pull)) ;Si no hay ruido de alien y agujero
      (not(percepts Pull Noise)) ;Si no hay ruido de agujero y alien
      ?p1<-(coordenadas ?x ?y) ;Guarda las coordendas actuales en la variable ?p1
      ?p2<-(coordenadaX ?z) ;Guarda la última coordenada X en la variable ?p2
      ?p3<-(coordenadaY ?t) ;Guarda la última coordenada Y en la variable ?p3
      (not(test(=(+ ?y 1) ?t))) ;Verifica que al moverse no se repita la coordenada Y
      => ;Si se cumplen todas las condiciones entonces
      (moveWilly south) ;Ejecuta la acción de mover a Willy al sur
      (retract ?p1) ;Elimina la coordenada actual
      (retract ?p2) ;Elimina la coordenada X
      (retract ?p3) ;Elimina la coordenada Y
      (assert(coordenadas ?x (+ ?y 1))) ;Actualiza coordenadas (y+1)
      (assert(coordenadaX ?x)) ;Guarda X actual (no cambia)
      (assert(coordenadaY ?y)) ;Guarda la nueva Y
   )

   (defrule moveEast ;Mueve a Willy al este (una casilla hacia la derecha)
      (directions $? east $?) ;Si hay una dirección este en la lista de direcciones
      (not(percepts Noise)) ;Si no hay ruido de alien
      (not(percepts Pull)) ;Si no hay ningun agujero
      (not(percepts Noise Pull)) ;Si no hay ruido de alien y agujero
      (not(percepts Pull Noise)) ;Si no hay ruido de agujero y alien
      
      ?p1<-(coordenadas ?x ?y) ;Guarda las coordendas actuales en la variable ?p1
      ?p2<-(coordenadaX ?z) ;Guarda la última coordenada X en la variable ?p2
      ?p3<-(coordenadaY ?t) ;Guarda la última coordenada Y en la variable ?p3
      (not(test(=(+ ?x 1) ?z))) ;Verifica que al moverse no se repita la coordenada X
      => ;Si se cumplen todas las condiciones entonces
      (moveWilly east) ;Ejecuta la acción de mover a Willy al este
      (retract ?p1) ;Elimina la coordenada actual
      (retract ?p2) ;Elimina la coordenada X
      (retract ?p3) ;Elimina la coordenada Y
      (assert(coordenadas (+ ?x 1) ?y)) ;Actualiza coordenadas (x+1)
      (assert(coordenadaX ?x)) ;Guarda X actual (no cambia)
      (assert(coordenadaY ?y)) ;Guarda la nueva Y
   )

   (defrule moveWest ;Mueve a Willy al oeste (una casilla hacia la izquierda)
      (directions $? west $?) ;Si hay una dirección oeste en la lista de direcciones
      (not(percepts Noise)) ;Si no hay ruido de alien
      (not(percepts Pull)) ;Si no hay ningun agujero
      (not(percepts Noise Pull)) ;Si no hay ruido de alien y agujero
      (not(percepts Pull Noise)) ;Si no hay ruido de agujero y alien
      ?p1<-(coordenadas ?x ?y) ;Guarda las coordendas actuales en la variable ?p1
      ?p2<-(coordenadaX ?z) ;Guarda la última coordenada X en la variable ?p2
      ?p3<-(coordenadaY ?t) ;Guarda la última coordenada Y en la variable ?p3
      ?p4<-(desplazamientos ?s) ;Guarda el contador de movimientos en la variable ?p4
      (not(test(=(- ?x 1) ?z))) ;Verifica que al moverse no se repita la coordenada X
      => ;Si se cumplen todas las condiciones entonces 
      (moveWilly west) ;Ejecuta la acción de mover a Willy al oeste 
      (retract ?p1) ;Elimina la coordenada actual
      (retract ?p2) ;Elimina la coordenada X
      (retract ?p3) ;Elimina la coordenada Y
      (retract ?p4) ;Elimina el contador de movimientos
      (assert(coordenadas (- ?x 1) ?y)) ;Actualiza coordenadas (x-1)
      (assert(coordenadaX ?x)) ;Guarda X actual (no cambia)
      (assert(coordenadaY ?y)) ;Guarda la nueva Y
      (assert(desplazamientos (+ ?s 1))) ;Incrementa el contador de movimientos
   )


;Vuelta atras por ruido de alienígena
   (defrule moveNorthNoise
      (directions $? north $?) ;Si hay una dirección norte en la lista de direcciones
      (percepts Noise) ;Si hay ruido de alien
      (not(percepts Pull)) ;Pero no hay agujero
      (not(percepts Noise Pull)) ;Ni ruido de alien y agujero
      (not(percepts Pull Noise)) ;Ni ruido de agujero y alien
      ?p1<-(coordenadas ?x ?y) ;Guarda las coordendas actuales en la variable ?p1
      ?p2<-(coordenadaX ?z) ;Guarda la última coordenada X en la variable ?p2
      ?p3<-(coordenadaY ?t) ;Guarda la última coordenada Y en la variable ?p3  
      ?p4<-(desplazamientos ?s) ;Guarda el contador de movimientos en la variable ?p4
      (test(=(- ?y 1) ?t)) ;Solo se mueve si YA visitó esa coordenada
      => ;Si se cumplen todas las condiciones entonces 
      (moveWilly north) ;Ejecuta la acción de mover a Willy al norte
      (retract ?p1) ;Elimina la coordenada actual
      (retract ?p2) ;Elimina la coordenada X 
      (retract ?p3) ;Elimina la coordenada Y  
      (retract ?p4) ;Elimina el contador de movimientos
      (assert(coordenadas ?x (+ ?y 1))) ;Actualiza coordenadas (y+1)
      (assert(coordenadaX ?x)) ;Guarda X actual (no cambia)   
      (assert(coordenadaY ?y)) ;Guarda la nueva Y
      (assert(desplazamientos (+ ?s 1))) ;Incrementa el contador de movimientos
   )

   (defrule moveSouthNoise
      (directions $? south $?) ;Si hay una dirección sur en la lista de direcciones
      (percepts Noise) ;Si hay ruido de alien
      (not(percepts Pull)) ;Pero no hay agujero
      (not(percepts Noise Pull)) ;Ni ruido de alien y agujero 
      (not(percepts Pull Noise)) ;Ni ruido de agujero y alien
      ?p1<-(coordenadas ?x ?y) ;Guarda las coordendas actuales en la variable ?p1
      ?p2<-(coordenadaX ?z) ;Guarda la última coordenada X en la variable ?p2 
      ?p3<-(coordenadaY ?t) ;Guarda la última coordenada Y en la variable ?p3   
      ?p4<-(desplazamientos ?s) ;Guarda el contador de movimientos en la variable ?p4
      (test(=(+ ?y 1) ?t)) ;Solo se mueve si YA visitó esa coordenada
      => ;Si se cumplen todas las condiciones entonces
      (moveWilly south) ;Ejecuta la acción de mover a Willy al sur
      (retract ?p1) ;Elimina la coordenada actual 
      (retract ?p2) ;Elimina la coordenada X  
      (retract ?p3) ;Elimina la coordenada Y
      (retract ?p4) ;Elimina el contador de movimientos
      (assert(coordenadas ?x (+ ?y 1))) ;Actualiza coordenadas (y+1)
      (assert(coordenadaX ?x)) ;Guarda X actual (no cambia)
      (assert(coordenadaY ?y)) ;Guarda la nueva Y
      (assert(desplazamientos (+ ?s 1))) ;Incrementa el contador de movimientos
   )

   (defrule moveEastNoise
      (directions $? east $?) ;Si hay una dirección este en la lista de direcciones
      (percepts Noise) ;Si hay ruido de alien 
      (not(percepts Pull)) ;Pero no hay agujero
      (not(percepts Noise Pull)) ;Ni ruido de alien y agujero
      (not(percepts Pull Noise)) ;Ni ruido de agujero y alien
      ?p1<-(coordenadas ?x ?y) ;Guarda las coordendas actuales en la variable ?p1   
      ?p2<-(coordenadaX ?z) ;Guarda la última coordenada X en la variable ?p2   
      ?p3<-(coordenadaY ?t) ;Guarda la última coordenada Y en la variable ?p3
      ?p4<-(desplazamientos ?s) ;Guarda el contador de movimientos en la variable ?p4
      (test(=(+ ?x 1) ?z)) ;Solo se mueve si YA visitó esa coordenada
      => ;Si se cumplen todas las condiciones entonces 
      (moveWilly east) ;Ejecuta la acción de mover a Willy al este
      (retract ?p1) ;Elimina la coordenada actual
      (retract ?p2) ;Elimina la coordenada X
      (retract ?p3) ;Elimina la coordenada Y
      (retract ?p4) ;Elimina el contador de movimientos
      (assert(coordenadas (+ ?x 1) ?y)) ;Actualiza coordenadas (x+1)
      (assert(coordenadaX ?x)) ;Guarda X actual (no cambia) 
      (assert(coordenadaY ?y)) ;Guarda la nueva Y   
      (assert(desplazamientos (+ ?s 1))) ;Incrementa el contador de movimientos
   )

   (defrule moveWestNoise
      (directions $? west $?) ;Si hay una dirección oeste en la lista de direcciones
      (percepts Noise) ;Si hay ruido de alien
      (not(percepts Pull)) ;Pero no hay agujero
      (not(percepts Noise Pull)) ;Ni ruido de alien y agujero
      (not(percepts Pull Noise)) ;Ni ruido de agujero y alien
      ?p1<-(coordenadas ?x ?y) ;Guarda las coordendas actuales en la variable ?p1
      ?p2<-(coordenadaX ?z) ;Guarda la última coordenada X en la variable ?p2
      ?p3<-(coordenadaY ?t) ;Guarda la última coordenada Y en la variable ?p3
      ?p4<-(desplazamientos ?s) ;Guarda el contador de movimientos en la variable ?p4
      (test(=(- ?x 1) ?z)) ;Solo se mueve si YA visitó esa coordenada
      => ;Si se cumplen todas las condiciones entonces 
      (moveWilly west) ;Ejecuta la acción de mover a Willy al oeste 
      (retract ?p1) ;Elimina la coordenada actual
      (retract ?p2) ;Elimina la coordenada X
      (retract ?p3) ;Elimina la coordenada Y 
      (retract ?p4) ;Elimina el contador de movimientos  
      (assert(coordenadas (- ?x 1) ?y)) ;Actualiza coordenadas (x-1)
      (assert(coordenadaX ?x)) ;Guarda X actual (no cambia)
      (assert(coordenadaY ?y)) ;Guarda la nueva Y
      (assert(desplazamientos (+ ?s 1))) ;Incrementa el contador de movimientos
   )


;Vuelta atras por ruido de agujero negro

   (defrule moveNorthPull
      (directions $? north $?) ;Si hay una dirección norte en la lista de direcciones
      (not(percepts Noise)) ;Si no hay ruido de alien
      (percepts Pull) ;Pero si hay agujero
      (not(percepts Noise Pull)) ;Ni ruido de alien y agujero
      (not(percepts Pull Noise)) ;Ni ruido de agujero y alien
      ?p1<-(coordenadas ?x ?y) ;Guarda las coordendas actuales en la variable ?p1
      ?p2<-(coordenadaX ?z) ;Guarda la última coordenada X en la variable ?p2
      ?p3<-(coordenadaY ?t) ;Guarda la última coordenada Y en la variable ?p3   
      ?p4<-(desplazamientos ?s) ;Guarda el contador de movimientos en la variable ?p4
      (test(=(+ ?t 1) ?y)) ;Solo se mueve si YA visitó esa coordenada
      => ;Si se cumplen todas las condiciones entonces 
      (moveWilly north) ;Ejecuta la acción de mover a Willy al norte 
      (retract ?p1) ;Elimina la coordenada actual
      (retract ?p2) ;Elimina la coordenada X
      (retract ?p3) ;Elimina la coordenada Y
      (retract ?p4) ;Elimina el contador de movimientos
      (assert(coordenadas ?x (- ?y 1))) ;Actualiza coordenadas (y-1)   
      (assert(coordenadaX ?x)) ;Guarda X actual (no cambia)
      (assert(coordenadaY ?y)) ;Guarda la nueva Y
      (assert(desplazamientos (+ ?s 1))) ;Incrementa el contador de movimientos
   )

   (defrule moveSouthPull
      (directions $? south $?) ;Si hay una dirección sur en la lista de direcciones
      (not(percepts Noise)) ;Si no hay ruido de alien
      (percepts Pull) ;Pero si hay agujero
      (not(percepts Noise Pull)) ;Ni ruido de alien y agujero
      (not(percepts Pull Noise)) ;Ni ruido de agujero y alien    
      ?p1<-(coordenadas ?x ?y) ;Guarda las coordendas actuales en la variable ?p1
      ?p2<-(coordenadaX ?z) ;Guarda la última coordenada X en la variable ?p2
      ?p3<-(coordenadaY ?t) ;Guarda la última coordenada Y en la variable ?p3
      ?p4<-(desplazamientos ?s) ;Guarda el contador de movimientos en la variable ?p4
      (test(=(- ?t 1) ?y)) ;Solo se mueve si YA visitó esa coordenada
      => ;Si se cumplen todas las condiciones entonces 
      (moveWilly south) ;Ejecuta la acción de mover a Willy al sur 
      (retract ?p1) ;Elimina la coordenada actual
      (retract ?p2) ;Elimina la coordenada X 
      (retract ?p3) ;Elimina la coordenada Y
      (retract ?p4) ;Elimina el contador de movimientos
      (assert(coordenadas ?x (- ?y 1))) ;Actualiza coordenadas (y-1)   
      (assert(coordenadaX ?x)) ;Guarda X actual (no cambia)
      (assert(coordenadaY ?y)) ;Guarda la nueva Y
      (assert(desplazamientos (+ ?s 1))) ;Incrementa el contador de movimientos
   )

   (defrule moveEastPull
      (directions $? east $?) ;Si hay una dirección este en la lista de direcciones
      (not(percepts Noise)) ;Si no hay ruido de alien
      (percepts Pull) ;Pero si hay agujero
      (not(percepts Noise Pull)) ;Ni ruido de alien y agujero 
      (not(percepts Pull Noise)) ;Ni ruido de agujero y alien
      ?p1<-(coordenadas ?x ?y) ;Guarda las coordendas actuales en la variable ?p1
      ?p2<-(coordenadaX ?z) ;Guarda la última coordenada X en la variable ?p2
      ?p3<-(coordenadaY ?t) ;Guarda la última coordenada Y en la variable ?p3
      ?p4<-(desplazamientos ?s) ;Guarda el contador de movimientos en la variable ?p4
      (test(=(+ ?x 1) ?z)) ;Solo se mueve si YA visitó esa coordenada
      => ;Si se cumplen todas las condiciones entonces 
      (moveWilly east) ;Ejecuta la acción de mover a Willy al este 
      (retract ?p1) ;Elimina la coordenada actual  
      (retract ?p2) ;Elimina la coordenada X
      (retract ?p3) ;Elimina la coordenada Y
      (retract ?p4) ;Elimina el contador de movimientos
      (assert(coordenadas ?x (- ?y 1))) ;Actualiza coordenadas (y-1)
      (assert(coordenadaX ?x)) ;Guarda X actual (no cambia)
      (assert(coordenadaY ?y)) ;Guarda la nueva Y
      (assert(desplazamientos (+ ?s 1))) ;Incrementa el contador de movimientos
   )

   (defrule moveWestPull
      (directions $? west $?) ;Si hay una dirección oeste en la lista de direcciones
      (not(percepts Noise)) ;Si no hay ruido de alien
      (percepts Pull) ;Pero si hay agujero
      (not(percepts Noise Pull)) ;Ni ruido de alien y agujero
      (not(percepts Pull Noise)) ;Ni ruido de agujero y alien 
      ?p1<-(coordenadas ?x ?y) ;Guarda las coordendas actuales en la variable ?p1   
      ?p2<-(coordenadaX ?z) ;Guarda la última coordenada X en la variable ?p2
      ?p3<-(coordenadaY ?t) ;Guarda la última coordenada Y en la variable ?p3   
      ?p4<-(desplazamientos ?s) ;Guarda el contador de movimientos en la variable ?p4
      (test(=(- ?x 1) ?z)) ;Solo se mueve si YA visitó esa coordenada
      => ;Si se cumplen todas las condiciones entonces 
      (moveWilly west) ;Ejecuta la acción de mover a Willy al oeste 
      (retract ?p1) ;Elimina la coordenada actual
      (retract ?p2) ;Elimina la coordenada X
      (retract ?p3) ;Elimina la coordenada Y
      (retract ?p4) ;Elimina el contador de movimientos
      (assert(coordenadas ?x (- ?y 1))) ;Actualiza coordenadas (y-1)
      (assert(coordenadaX ?x)) ;Guarda X actual (no cambia)
      (assert(coordenadaY ?y)) ;Guarda la nueva Y
      (assert(desplazamientos (+ ?s 1))) ;Incrementa el contador de movimientos  
   )


;Disparamos solo al norte ya que la lógica que seguimos sirve para matar en el mapa 3

   (defrule fireNorthInicio
      (declare (salience 10)) ;Prioridad alta se ejecuta primero
      (not (directions $? south $?)) ;Si hay una dirección oeste en la lista de direcciones
      (hasLaser) ;Si Willy tiene láser
      (directions $? north $?) ;Si hay una dirección norte en la lista de direcciones
      (coordenadas 0 0) ;Si Willy está en la posición inicial
      (coordenadaX ?x) ;Guarda la última coordenada X en la variable ?p2
      (coordenadaY ?y) ;Guarda la última coordenada Y en la variable ?p3
      => ;Si se cumplen todas las condiciones entonces 
      (fireLaser north) ;Ejecuta la acción de disparar al norte
   )

   (defrule fireEastInicio
      (declare (salience 10)) ;Prioridad alta se ejecuta primero
      (not (directions $? north $?)) ;Si hay una dirección oeste en la lista de direcciones
      (not (directions $? west $?)) ;Si hay una dirección oeste en la lista de direcciones
      (hasLaser) ;Si Willy tiene láser
      (directions $? east $?) ;Si hay una dirección norte en la lista de direcciones
      (coordenadas 0 0) ;Si Willy está en la posición inicial
      (coordenadaX ?x) ;Guarda la última coordenada X en la variable ?p2
      (coordenadaY ?y) ;Guarda la última coordenada Y en la variable ?p3
      => ;Si se cumplen todas las condiciones entonces 
      (fireLaser east) ;Ejecuta la acción de disparar al este
   )