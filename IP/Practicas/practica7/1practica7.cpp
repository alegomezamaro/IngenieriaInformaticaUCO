#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

struct alumno{
	int dni=0;
	int edad=0;
	float nota=0;

	void imprime(){
		cout << "DNI de alumno: " << dni << endl;
		cout << "Edad del alumno: " << edad << endl;
		cout << "Nota del alumno: " << nota << endl;
	}
};

int buscardni(alumno v[], int valor, int x){
	int posicion = -1;
	for(int i=0; i<x; i++){
		if(v[i].dni == valor){
			posicion = i;
		}
	}
	return posicion;
}

int main(){
	alumno alumnos[10];
	int na=0;
	int opcion_menu=0;
	int dnitemp=0;
	int dnidonde=0;
	do{
		cout << "Seleccione una opcion:" << endl;
		cout << "1. Añadir alumno" << endl;
		cout << "2. Imprimir datos de un alumno" << endl;
		cout << "3. Imprimir datos de todos los alumnos" << endl;
		cout << "4. Modificar alumno" << endl;
		cout << "5. Eliminar a un alumno" << endl;
		cout << "6. Salir" << endl;
		cout << "Has elegido la opcion: ";
		cin >> opcion_menu;
		if ((opcion_menu < 1) or (opcion_menu > 6)){
			cout << "Selecciona una opcion incluida en el menu" << endl;
		}
		cout << endl << endl;

		switch (opcion_menu){
			case 1: {
				if(na>=10){
					cout << "No se pueden matricular mas alumnos" << endl;
				}
				else{
					cout << "Has entrado en la opcion 1, añadir alumno" << endl;
					cout << "Introduce el DNI del alumno: ";
					cin >> dnitemp;
					if(buscardni(alumnos, dnitemp, na) != -1){
						cout << "El DNI introducido ya esta registrado" << endl << endl;
					}
					else{
						alumnos[na].dni = dnitemp;
						cout << "Introduce la edad del alumno: ";
						cin >> alumnos[na].edad;
						cout << "Introduce la nota del alumno: ";
						cin >> alumnos[na].nota;
						na++;
						cout << "Los datos del nuevo alumno han sido introducidos correctamente" << endl << endl;
				}
			}
			break;

			case 2: {
				if (na == 0){
					cout << "No hay alumnos inscritos aun, porfavor añadalos" << endl;
				}
				else{
					cout << "Has entrado en la opcion 2, imprimir datos de un alumno" << endl;
					cout << "Introduce el DNI del alumno del que quieres que se lean los datos: ";
					cin >> dnitemp;
					dnidonde = buscardni(alumnos, dnitemp, na);
					if (dnidonde == -1){
						cout << "No existen datos con dicho DNI" << endl;
					}
					else{
						cout << "Los datos del alumno que coincide con dicho DNI son: " << endl;
						alumnos[dnidonde].imprime();
						cout << endl << endl;
					}
				}
			}
			break;

			case 3: {
				if (na == 0){
					cout << "No hay alumnos inscritos aun, porfavor añadalos" << endl;
				}
				else{
					cout << "Has entrado en la opcion 3, imprimir los datos de todos los alumnos" << endl;
					for(int i=0; i<na; i++){
						cout << "Alumno numero " << (i+1) << ": " << endl;
						alumnos[i].imprime();
						cout << endl << endl;
					}
				}
			}
			break;

			case 4: {
				if (na == 0){
					cout << "No hay alumnos inscritos aun, porfavor añadalos" << endl;
				}
				else{
					cout << "Has entrado en la opcion 4, modificar los datos de un alumno" << endl;
					cout << "Introduce el DNI del alumno del que quieres modificar los datos: " << endl;
					cin >> dnitemp;
					dnidonde = buscardni(alumnos, dnitemp, na);
					if (dnidonde == -1){
						cout << "No existen datos con dicho DNI" << endl << endl;
					}
					else{
						cout << "Introduce el nuevo DNI del alumno: ";
						cin >> dnitemp;
						if (buscardni(alumnos, dnitemp, na) != -1){
							cout << "No se puede modificar con estos datos, el nuevo DNI introducido ya existe" << endl << endl;
						}
						else{
							alumnos[dnidonde].dni=dnitemp;
							cout << "Introduce la nueva edad del alumno: ";
							cin >> alumnos[dnidonde].edad;
							cout << "Introduce la nueva nota del alumno: ";
							cin >> alumnos[dnidonde].nota;
							cout << endl << endl;
						}
					}
				}
			}
			break;

			case 5: {
				if (na == 0){
					cout << "No hay alumnos inscritos aun, porfavor añadalos" << endl;
				}
				else{
					cout << "Has entrado en la opcion 5, eliminar a un alumno" << endl;
					cout << "Introduce el DNI del alumno del que quieres eliminar los datos: " << endl;
					cin >> dnitemp;
					dnidonde = buscardni(alumnos, dnitemp, na);
					if (dnidonde == -1){
						cout << "No existen datos con dicho DNI" << endl;
					}
					else{
						alumnos[dnidonde]=alumnos[na-1];
						na--;
						cout << "El alumno ha sido eliminado correctamente" << endl << endl;
					}
				}
			}
			break;
		};
		}
	}
	while (opcion_menu != 6);
	cout << "Ha salido del programa" << endl;
	cin.get();
	cin.ignore();
}