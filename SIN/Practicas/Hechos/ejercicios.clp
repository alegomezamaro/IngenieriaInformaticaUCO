"Ejercicio 1"

(deftemplate persona
  (slot nombre (type STRING))
  (slot apellidos (type STRING))  
  (slot color-ojos (type SYMBOL))  
  (slot altura (type FLOAT))  
  (slot edad (type INTEGER))
)

"Ejercicio 2"

(deftemplate paciente
  (slot nombre (type STRING))  
  (slot apellidos (type STRING))  
  (slot dni (type STRING))  
  (slot seguro-medico (type INTEGER))  
)

(deftemplate historial
  (slot paciente (type FACT-ADDRESS)) 
  (slot fecha (type STRING))  
  (multislot sintomas (type STRING))  
  (multislot pruebas (type STRING))  
  (multislot medicacion (type STRING))  
)