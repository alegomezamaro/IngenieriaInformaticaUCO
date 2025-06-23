 #include "ej11f.h"

int es_prefijo(char *cadena, char *prefijo){	//Define si la cadena es prefijo o no
	char *direccion= strstr(cadena, prefijo);
	if(direccion== &cadena[0]){
		return 1;
	}
	else{
		return 0;
	}
}

int es_sufijo(char *cadena, char *sufijo){	//Define si la cadena es sufijo o no
	char *direccion= strstr(cadena, sufijo);
	if(direccion==NULL){
		return 0;
	}
	else{
		int tam_nosuf= (strlen(cadena)-strlen(sufijo));	//Tamaño de la cadena sin el tamaño del sufijo
		int tam_suf=(strlen(sufijo)-1);	//Tamaño del sufijo a recorrer
		for(int tam_cad=((strlen(cadena))-1); tam_cad>=tam_nosuf; tam_cad--){
			if(cadena[tam_cad]!=sufijo[tam_suf]){ return 0;}
			tam_suf--;
		}
		return 1;
	}
	return 0;
}
