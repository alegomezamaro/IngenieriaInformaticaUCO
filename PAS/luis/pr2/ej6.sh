#!/bin/bash

# Este ejercicio consiste en analizar los ultimos 20 comandos ejecutados por el usuario en la terminal
# utilizando el historial de comandos (.bash_history). A partir de estos comandos, el script debe proporcionar
# la siguiente información:
# 1. Contar cuántas veces ha sido ejecutado cada comando.
# 2. Determinar cuál ha sido el número máximo de argumentos con los que se ha invocado cada comando.
# NOTA1: Para los efectos del ejercicio, no se van a considerar tuberías o el separador “;”. Es decir, el comando
# de cada línea siempre será la primera palabra y, si hay tuberías, se considera que son argumentos al comando 
# detectado al principio de la línea. Ej.: echo 2 | tail -c 4 contabiliza como un comando 'echo' con 5 argumentos.
# NOTA2: El propio nombre del comando no se contabiliza como argumento.

# Definimos el archivo temporal que contendrá los últimos 20 comandos del historial
file="history.txt"

# Usamos 'tail' para obtener las últimas 20 líneas del archivo .bash_history
tail -20 ~/.bash_history > $file

# A continuación, procesamos el archivo $file para contar la cantidad de veces que se ha ejecutado cada comando
# y determinar el número máximo de argumentos con los que se ha invocado cada comando.

# Ejemplo de salida esperada:
# comando: ./ej1.sh
#   -> veces: [0-9]
#   -> max(argc): [0-9]

# Ordenamos el archivo y contamos las ocurrencias únicas de cada comando usando 'uniq -c'
sort $file | uniq -c | awk '

  # Función que calcula el número de argumentos del comando, excluyendo el nombre del comando.
  # 'NF' es el número total de campos, y quitamos 2 porque el nombre del comando no cuenta como argumento.
  function find_words(){
    return NF - 2
  }

  # Función que imprime la información del comando: cuántas veces se ejecutó y su máximo número de argumentos.
  function print_info(){
    print "Comando " cmd
    print "\t-> Veces ejecutado: " count
    print "\t-> Máximo número de argumentos: " argc
    print ""
  }

  # Bloque principal que procesa cada línea del archivo
  {
    cmd = $2  # El nombre del comando está en la segunda columna (después de la cantidad de veces)
    count = $1  # Contamos cuántas veces se ejecutó el comando
    argc = find_words()  # Calculamos el número de argumentos del comando usando la función find_words

    # Leemos línea por línea el archivo para procesar todos los comandos
    while(getline){  
      cmd_new = $2  # Nuevo comando detectado

      # Si el comando actual es diferente del siguiente (cmd != cmd_new), imprimimos la información
      if ( cmd != cmd_new ){
        print_info()  # Llamamos a la función print_info para mostrar la información
        cmd = cmd_new  # Actualizamos el comando
        count = $1  # Actualizamos el número de veces que se ejecutó
        argc = find_words()  # Calculamos nuevamente los argumentos
      }
      else{
        count = count+1  # Si el comando es el mismo, simplemente aumentamos el contador
        new = find_words()  # Calculamos los argumentos para la línea actual
        if ( new > argc )  # Si encontramos más argumentos, actualizamos el valor de argc
          argc = new
      }
    }

    # Finalmente, imprimimos la información del último comando que se procesó
    print_info()
    exit  # Salimos del script después de procesar todo
}'

# Explicación del bloque que realiza el procesamiento:
# 1. 'cmd' almacena el nombre del comando que estamos procesando.
# 2. 'count' almacena el número de veces que se ha ejecutado el comando (usamos 'uniq -c').
# 3. 'argc' almacena el número máximo de argumentos con los que se ha ejecutado el comando.
# 4. El ciclo 'while(getline)' recorre el archivo de comandos y calcula el número de argumentos de cada uno.
# 5. Cada vez que encuentra un nuevo comando (cmd_new), imprime la información del comando anterior.
# 6. Al final, se imprime la información del último comando y el script termina.
