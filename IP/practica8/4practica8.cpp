#include <cstdlib> //define EXIT_FAILURE,EXIT_SUCCESS
#include <iostream>//cout
#include <string>//string
using namespace std;
int vocales(string cad){
	int vocales=0;
	for(int i=0; i < cad.size(); i++){
		cad[i] = tolower(cad[i]);
		if((cad[i] == 	'a') or (cad[i] == 	'e')  or (cad[i] == 	'i') or (cad[i] == 	'o') or (cad[i] == 	'u')){
			vocales++;
		}
	}
	return vocales;
}
 
int main(){
    if( vocales("HOLA COMO ESTAS")!=6){
        cout<<"Error 1"<<endl;
        return EXIT_FAILURE;
    }

    if( vocales("hola como Estas")!=6){
        cout<<"Error 2"<<endl;
        return EXIT_FAILURE;
    }

    if( vocales("xbnmsmnbx  nssmn")!=0){
        cout<<"Error 3"<<endl;
        return EXIT_FAILURE;
    }

    cout<<"Correcto"<<endl;
    return EXIT_SUCCESS;

}
