#include <cstdlib> //define EXIT_FAILURE,EXIT_SUCCESS
#include <iostream>//cout
#include <string>//string
using namespace std;
bool compruebadni(string dni){
	string letras = "TRWAGMYFPDXBNJZSQVHLCKE";
	string dniaux =  dni;
	unsigned letradni = dni.size()-1;
	dni[letradni] = toupper(dni[letradni]);
	dniaux.resize(8);
	char letra = letras[stoi(dniaux)%23];
	dniaux.push_back(letra);
	if (dniaux == dni){
		return true;
	}
	else{
		return false;
	}
}

int main(){
    if( compruebadni("12345678")!=false){
        cout<<"Error 1"<<endl;
        return EXIT_FAILURE;
    }
    if( compruebadni("12345678Z")!=true){
        cout<<"Error 2"<<endl;
        return EXIT_FAILURE;
    }
    if( compruebadni("12345678z")!=true){
        cout<<"Error 3"<<endl;
        return EXIT_FAILURE;
    }
    if( compruebadni("12345678X")!=false){
        cout<<"Error 4"<<endl;
        return EXIT_FAILURE;
    }
    if( compruebadni("87654321X")!=true){
        cout<<"Error 5"<<endl;
        return EXIT_FAILURE;
    }
    if( compruebadni("87654321a")!=false){
        cout<<"Error 6"<<endl;
        return EXIT_FAILURE;
    }


    cout<<"Correcto"<<endl;
    return EXIT_SUCCESS;

}


