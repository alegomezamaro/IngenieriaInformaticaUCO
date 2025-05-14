#include "computer.h"

Computer::Computer(std::string id, ComputerType type, std::string name, float price,
    std::string maker, std::string seller) : Product(id, name, price, maker, seller){
    type_ = type;
}