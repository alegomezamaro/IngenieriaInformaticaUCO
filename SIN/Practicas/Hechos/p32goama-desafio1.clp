(deftemplate paciente
	(slot nombre (type STRING) (default ?NONE))
	(multislot apellidos (type STRING))
	(slot numero_expediente (type INTEGER) (default ?NONE))
	(slot edad (type INTEGER))
	(slot sexo (type SYMBOL) (allowed-symbols V M) (default ?NONE))
	(slot volumen_pulmonar (type FLOAT) (default 25.0) (range 0.0 100.0))
	(slot estado (type SYMBOL) (allowed-symbols Alta Baja) (default Baja))
)

(deftemplate facultativo
	(slot nombre (type STRING) (default ?NONE))
	(multislot apellidos (type STRING))
	(slot numero_colegiado (type INTEGER) (default ?NONE))
	(slot numero_expediente (type INTEGER) (default ?NONE))
)

(deffacts constructor
	(paciente
		(nombre "Juan")
		(apellidos "Garcia" "Fernandez")
		(numero_expediente 103735)
		(edad 35)
		(sexo V)
		(volumen_pulmonar 78.0)
		(estado Alta)
	)
	(facultativo
		(nombre "Pedro")
		(apellidos "Gomez" "Castilla")
		(numero_colegiado 140035)
		(numero_expediente 103735)
	)
)