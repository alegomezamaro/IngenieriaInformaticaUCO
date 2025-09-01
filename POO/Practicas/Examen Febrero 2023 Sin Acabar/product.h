#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
#include <fstream>

class Product{
    private:
    std::string name_;
    std::string id_;
    float price_;

    public:
    //Constructor de 3 parámetros
    Product(std::string id, std::string name="no-name", int price=0.0){
        if(id.empty()){
            id_="error";
        }
        else{
            id_=id;
        }
        name_=name;
        if(price < 0){
            price_=0.0;
        }
        else{
            price_=price;
        }
    }

    //Modificadores 
    bool setId(std::string id){
        if(id.empty()){
            return false;
        }
        else{
            id_=id;
            return true;
        }
    }

    bool setName(std::string name){
        if(name.empty()){
            return false;
        }
        else{
            name_=name;
            return true;
        }
    }

    bool setPrice(float price){
        if(price < 0){
            return false;
        }
        else{
            price_=price;
            return true;
        }
    }

    //Observadores
    float getPrice(){
        return price_;
    }

    std::string getId(){
        return id_;
    }

    std::string getName(){
        return name_;
    }

    //Observador IdName
    std::string getIdName(){
        return std::string(getId()) + ", " + getName();
    }

    //Observador Status
    std::string getStatus(){
        if(getId() == "error"){
            if(getName() != "no-name"){
                if(getPrice() > 0){
                    return std::string("ok");
                }
            }
        }
        return std::string("error");
    }

    //Observador WriteData
    void writeData(){
        std::fstream f("data.txt");
        if(f.is_open()){
            f << getId() << "," << getName() << "\n";
            f.close();
        }
    }


};

#endif