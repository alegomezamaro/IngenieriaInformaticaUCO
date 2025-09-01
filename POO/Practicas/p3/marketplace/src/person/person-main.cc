// person-main.cc
// Ejemplo de uso de person

#include "person.h"

namespace ns1{
    int a; // Esta es la variable ns1::a
    int b; // Esta es la variable ns1::b
}

namespace ns2{
    float a; // Esta es la variable ns2::a
    float c; // Esta es la variable ns2::c
}

using namespace std;
using namespace ns1;
using namespace ns2;

int main(void){
    Person p1("123", "Juan", "Cordoba", "Cordoba", "Spain", 18, 4.568, 2006);
    Person p2("456", "Ana", "Guadalcazar", "Cordoba", "Spain", 25, 7.371, 1999);
    std::cout << p1.GetDataStr();
    std::cout << p2.GetDataStr();
    return 0;
}