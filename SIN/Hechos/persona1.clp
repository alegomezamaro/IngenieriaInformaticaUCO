(deftemplate persona1 "Detalles de una persona"
  (slot nombre (type STRING) (default ?NONE))  
  (slot apellidos (type STRING) (default ?NONE))  
  (slot edad (type INTEGER) (default 20))  
  (slot color-ojos (type SYMBOL) (default negro))  
  (slot altura (type FLOAT) (default 1.65))
)


