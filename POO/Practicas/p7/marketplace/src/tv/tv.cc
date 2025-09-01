#include "tv.h"

Tv::Tv(std::string id, std::string name, float price,
    std::string maker, std::string seller, float inch) : Product(id, name, price, maker, seller){
    inch_ = inch;
}

bool Tv::SetInch(float inch){

    if(inch > 0){
        inch_ = inch;
        return true;
    }
    return false;

}