// Delaración de la clase Client
#ifndef CONTADOR_H
#define CONTADOR_H
#include <iostream>
#include <string>

class Contador{

private:
    int valor_;
    int min_;
    int max_;

public:
    Contador(int valor=0, int min=0, int max=1000);
    
    inline int get(){return valor_;}
    Contador operator=(const Contador& c);
    Contador operator=(int n);
    Contador operator++(); //valor++
    Contador operator++(int); //++valor
    Contador operator--(); //valor--
    Contador operator--(int); //--valor
    Contador operator+(int n); //valor+n
    friend Contador operator+(int n, Contador& c); //n+valor
    Contador operator-(int n); //valor-n
    friend Contador operator-(int n, Contador& c); //n-valor
    friend std::ostream &operator<<(std::ostream &o, const Contador &c);
    friend std::istream &operator>>(std::istream &i, Contador &c);

};

#endif