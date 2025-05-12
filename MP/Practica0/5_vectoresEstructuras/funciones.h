//En los ficheros .h incluiremos #defines, struct y prototipos (cabeceras) de funciones

#define MAX_LINEA 250
#define MAX_VECTOR 15
 
struct datos
{
   char nombre[MAX_LINEA];
   int edad;
   float nota;
};

struct datos rellenarAlumno();
void imprimirAlumno(struct datos alumno);
void rellenarVector(struct datos Alumnos[], int nEle);
void imprimirVector(struct datos Alumnos[], int nEle);
int primerNombre(struct datos Alumnos[], int nEle);
float calcularEdadMedia(struct datos Alumnos[], int nEle);
