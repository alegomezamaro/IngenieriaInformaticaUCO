// Delaración de la clase Market
#ifndef MARKET_H
#define MARKET_H
#include <iostream>
#include <fstream>
#include "client.h"
#include "seller.h"

class Market{

private:
    std::list<Client> client_list_;
    std::list<Seller> seller_list_;
    std::string slogan_;

public:
    Market(std::string slogan);
    
    inline std::string GetSlogan(){return slogan_;}
    inline void SetSlogan(std::string slogan){slogan_ = slogan;}
    bool AddClient(Client c); 
    bool AddSeller(Seller s);
    inline int NClients(){return client_list_.size();}
    inline int NSellers(){return seller_list_.size();}
    bool DeleteClient(Client c);
    bool DeleteSeller(Seller s);
    bool AddProductClient(Product p, std::string id_client);
    bool AddProductSeller(Product p, std::string id_seller);
    bool DeleteProductClient(Product p, std::string id_client);
    bool DeleteProductSeller(Product p, std::string id_seller);
    float GetMoneyInBasket();
    bool DumpMarket(int outmode);

};

#endif