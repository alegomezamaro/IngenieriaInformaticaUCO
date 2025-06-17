#include <cstdlib> //define EXIT_FAILURE,EXIT_SUCCESS
#include <iostream>//cout
#include <string>//string
using namespace std;
bool palindromo(string cad){
	
	for(size_t i =0, j=(cad.size()-1) ; i < j; i++, j--){
		if(cad[i]==' '){
			i++;
		}
		if(cad[j]==' '){
			j--;
		}
		if(cad[i] != cad[j]){
			return false;
		}
	}
	return true;
}

int main(){
    if( palindromo("asddsa")==false){
        cout<<"Error 1"<<endl;
        return EXIT_FAILURE;
    }
    if( palindromo("xasddsa")==true){
        cout<<"Error 2"<<endl;
        return EXIT_FAILURE;
    }
    if( palindromo("acaso hubo buhos aca")==false){
        cout<<"Error 3"<<endl;
        return EXIT_FAILURE;
    }

    cout<<"Correcto"<<endl;
    return EXIT_SUCCESS;

}

