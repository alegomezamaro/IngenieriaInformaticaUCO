#!/bin/bash
read -p "Introduce el nombre del usuario: " nombre
if [ $nombre == $USER ];
then
	echo "Hola $USER"
else
	echo "Error, el usuario no coincide"
fi
