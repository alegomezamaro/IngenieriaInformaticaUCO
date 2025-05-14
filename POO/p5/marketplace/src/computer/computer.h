// Delaración de la clase Computer
#ifndef COMPUTER_H
#define COMPUTER_H
#include <string>
#include <iostream>
#include "product.h"

enum class ComputerType {
    Desktop,
    Laptop,
    Server,
    Tablet,
    Gaming
};

class Computer : public Product{

private:
    ComputerType type_; // tipo de ordenador

public:
    Computer(std::string id, ComputerType type, std::string name="empty", float price=0.0,
        std::string maker="empty", std::string seller="empty");
    
    inline ComputerType GetType(){return type_;}
    inline void SetType(ComputerType type){type_ = type;}

};

#endif