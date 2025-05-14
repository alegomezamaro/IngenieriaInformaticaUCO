// person-main.cc
// A example program with a simple class

#include "person.h"
#include <iostream> 

//using namespace std;

namespace ns1{
    int a; // Esta es la variable ns1::a
    int b; // Esta es la variable ns1::b
}

namespace ns2{
    float a; // Esta es la variable ns2::a
    float c; // Esta es la variable ns2::c
}

int main(void){


    int a=55;
    ns1::a=0;
    ns2::a=2.3;
    std::cout<< "ns1::a= " << ns1::a << "\n";
    std::cout<< "ns2::a= " << ns2::a << "\n";
    std::cout<< "a= " << a << "\n";

}