// Delaración de la clase TV
#ifndef BASKET_H
#define BASKET_H
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include "product.h"
#include "computer.h"
#include "tv.h"

class Basket{

private:
    std::list<Product> product_list_;
    std::map<std::string, int> product_quantity_;
    float total_;

public:
    Basket(void);
    
    void AddProduct(Product product);
    bool DeleteProduct(Product product);
    bool DeleteProduct(std::string id);
    void DeleteBasket();
    inline int GetSize(){return product_quantity_.size(); }
    inline float GetTotal(){return total_; }
    std::vector<std::string> GetIds();
    std::vector<int> GetQs();

};

#endif