#ifndef COMPUTER_H
#define COMPUTER_H

#include "product.h"

class Computer : public Product{
    private:
    int ram_;

    public:
    Computer(int ram, std::string id, std::string name, float price) : Product(id, name, price){
        if(ram <= 0){
            ram_=1;
        }
        else{
            ram_=ram;
        }
    }

    //Observador ram
    int getRam(){
        return ram_;
    }

    //Modificador ram
    bool setRam(int ram){
        if(ram <= 0){
            return false;
        }
        else{
            ram_=ram;
            return true;
        }
    }

    //Observador IdNameRam
    std::string getIdNameRam(){
        return std::string(getId()) + ", " + getName() + ", " + std::to_string(getRam());
    }

};

#endif