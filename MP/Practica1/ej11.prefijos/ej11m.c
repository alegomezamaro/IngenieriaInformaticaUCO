#include "ej11f.h"

int main(){//código para probar todos los casos
	if(es_prefijo("prefijo", "pref")){ printf("pref es prefijo de prefijo\n");}
	if(!es_prefijo("noprefijo", "pref")){ printf("pref no es prefijo de noprefijo\n");}
	if(es_sufijo("sufijo", "ijo")){ printf("ijo es sufijo de sufijo\n");}
	if(!es_sufijo("sufijono", "ijo")){ printf("ijo no es sufijo de sufijono\n");}
	return 0;
}