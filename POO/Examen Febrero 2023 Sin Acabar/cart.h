#ifndef CART_H
#define CART_H

#include "product.h"
#include <list>

class Cart{
    private:
    int id_;
    std::list<Product> bolsa_;

    public:
    Cart(int id){
        id_=id;
    }

    //Observador id
    int getId(){
        return id_;
    }

    //Devuelve el tamaño de bolsa
    int getN(){
        return bolsa_.size();
    }

    //Añade un producto a la bolsa
    bool addProduct(Product p){
        for(auto it=bolsa_.begin(); it!=bolsa_.end(); ++it){
            if(p.getId() == it->getId()){
                return false;
            }
        }
        bolsa_.push_back(p);
        return true;
    }
    
    //Borra un producto de la bolsa
    bool deleteProduct(Product p){
        for(auto it=bolsa_.begin(); it!=bolsa_.end(); ++it){
            if(p.getId() == it->getId()){
                bolsa_.erase(it);
                return true;
            }
        }
        return false;
    }

    //Precio total cesta
    float getTotal(){
        float precio = 0.0;
        for(auto it=bolsa_.begin(); it!=bolsa_.end(); ++it){
            precio += it->getPrice();
        }
        return precio;
    }

    void print(){
        float precio = 0.0;
        int i=1;
        for(auto it=bolsa_.begin(); it!=bolsa_.end(); ++it){
            std::cout << i << "/" << getN() << ": " << it->getId() << "," << it->getName() << "," << it->getPrice() << "\n";
            i++;
        }
        std::cout << "TOTAL=" << getTotal() << "\n";
    }
};

#endif