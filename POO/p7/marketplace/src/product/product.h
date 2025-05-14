// Delaración de la clase Product
#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
#include <iostream>

class Product{

private: 
    std::string id_; //identificador
    std::string name_; // nombre producto
    float price_; // precio
    std::string maker_; // fabricante
    std::string seller_; // vendedor

public:
    Product(std::string id, std::string name="empty", float price=0.0,
        std::string maker="empty", std::string seller="empty");
    
    inline std::string GetId(){return id_;}
    inline void SetId(std::string id){id_=id;}
    inline std::string GetName(){return name_;}
    inline void SetName(std::string name){name_=name;}
    inline float GetPrice(){return price_;}
    inline void SetPrice(float price){price_=price;}
    inline std::string GetMaker(){return maker_;}
    inline void SetMaker(std::string maker){maker_=maker;}
    inline std::string GetSeller(){return seller_;}
    inline void SetSeller(std::string seller){seller_=seller;}

};

#endif