#include "basket.h"

Basket::Basket(void){
    total_ = 0.0;
}

void Basket::AddProduct(Product p) {

    std::string id = p.GetId();
    if(product_quantity_.count(id) == 0) {
        product_list_.push_back(p);
        product_quantity_[id] = 1;
    }
    else {
        product_quantity_[id] += 1;
    }
    total_ += p.GetPrice();
}

bool Basket::DeleteProduct(Product p) {
    std::string id = p.GetId();
    return DeleteProduct(p);
}

bool Basket::DeleteProduct(std::string id) {
    if (product_quantity_.count(id) == 0) {
        return false; // El producto no existe en la cesta
    }
    for (auto it = product_list_.begin(); it != product_list_.end(); ++it) {
        if (it->GetId() == id) {
            total_ -= it->GetPrice();
            if (--product_quantity_[id] == 0) {
                product_quantity_.erase(id);
                product_list_.erase(it);
            }
            return true;
        }
    }
    return false;
}

void Basket::DeleteBasket() {
    product_list_.clear();
    product_quantity_.clear();
    total_ = 0.0;
}

std::vector<std::string> Basket::GetIds(){
    std::vector<std::string> key;
    for (auto it = product_list_.begin(); it != product_list_.end(); ++it) {
        key.push_back(it->GetId());
    }
    return key;
}

std::vector<int> Basket::GetQs(){
    std::vector<int> value;
    for (auto it = product_list_.begin(); it != product_list_.end(); ++it) {
        value.push_back(product_quantity_[it->GetId()]);
    }
    return value;
}