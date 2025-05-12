(deftemplate equipo "datos de un equipo de futbol"
        (slot id (default-dynamic (gensym*))) ;Identificación del equipo
        (slot nombre (type STRING) (default ?NONE)) ;Nombre del equipo
        (slot posicion (type INTEGER) (range 1 10) (default 5)) ;Posición en la liga del equipo
        (multislot equipacion (type SYMBOL) (allowed-symbols blanco rojo azul verde amarillo)) ;Colores que componen la equipación del equipo
        (multislot plantilla (type LEXEME) (cardinality 3 7)) ;Jugadores que componen la plantilla del equipo
)

(deffacts liga "los equipos participantes"
        (equipo (nombre "Montilla CF")
                (equipacion verde amarillo)
                (plantilla Juanfran Robert Andrea "Maria del Mar" Rosa)
        )
        (equipo (nombre "El pozoalbense FC")
                (equipacion rojo)
                (plantilla Carla "Luis Miguel" Monica)
                (posicion 10)
        )
        (equipo (nombre "Sporting de Cabra")
                (equipacion azul blanco)
                (posicion 3)
                (plantilla Rodri Lucas Bartolo Inma)
        )
        (equipo (nombre "Club Maleno")
                (posicion 1)
                (plantilla Javi Josema Jimena)
        )
)