#include "contador.h"

Contador::Contador(int valor, int min, int max){
    if(min >= max){
        valor = 0;
        min = 0;
        max = 1000;
    }
    else if(valor > max || valor < min){
        valor = 0;
    }
    valor_ = valor;
    min_ = min;
    max_ = max;
}

Contador Contador::operator=(const Contador &c){
    if(c.valor_ > max_){
        valor_ = c.max_;
    }
    else if(c.valor_ < min_){
        valor_ = c.min_;
    }
    else{
        valor_ = c.valor_;
    }
    return *this;
}

Contador Contador::operator=(int n){
    if(n > max_){
        valor_ = max_;
    }
    else if(n < min_){
        valor_ = min_;
    }
    else{
        valor_ = n;
    }
    return *this;
}

Contador Contador::operator++(){ //valor++
    if(valor_ < max_){
        valor_++;
    }
    return *this;
}

Contador Contador::operator++(int){ //++valor
    Contador c = *this;
    if(valor_ < max_){
        valor_++;
    }
    return c;
}

Contador Contador::operator--(){ //valor--
    if(valor_ > min_ && valor_ != 0){
        valor_--;
    }
    return *this;
}

Contador Contador::operator--(int){ //--valor
    Contador c = *this;
    if(valor_ > min_ && valor_ != 0){
        valor_--;
    }
    return c;
}

Contador Contador::operator+(int n){  //valor+n
    Contador c = *this;
    if((c.valor_ + n) > c.max_){
        c.valor_ = c.max_;
    }
    else{
        c.valor_ += n;
    }
    return c;
}

Contador operator+(int n, Contador &c){ //n+valor
    if((n + c.valor_) > c.max_){
        return Contador(c.max_);
    }
    else{
        return Contador(n + c.valor_);
    }
}

Contador Contador::operator-(int n){ //valor-n
    Contador c = *this;
    if((c.valor_ - n) < c.min_){
        c.valor_ = c.min_;
    }
    else{
        c.valor_ -= n;
    }
    return c;
}

Contador operator-(int n, Contador &c){ //n-valor
    if((n - c.valor_) < c.min_){
        return Contador(c.min_);
    }
    else{
        return Contador(n - c.valor_);
    }
}

std::ostream &operator<<(std::ostream &o, const Contador &c){
    o << "valor_ = " << c.valor_ << "\n";
    o << "min_ = " << c.min_ << "\n";
    o << "max_ = " << c.max_ << "\n";
    return o;
}

std::istream &operator>>(std::istream &i, Contador &c){
    std::cout << "Introduce el valor: ";
    i >> c.valor_;
    std::cout << "Introduce el minimo: ";
    i >> c.min_;
    std::cout << "Introduce el maximo: ";
    i >> c.max_;
    return i;
}