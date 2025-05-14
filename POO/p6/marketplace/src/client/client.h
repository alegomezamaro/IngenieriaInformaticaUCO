// Delaración de la clase Client
#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <iostream>
#include "person.h"
#include "basket.h"

class Client: public Person, public Basket{

private:
    int premium_;

public:
    Client(std::string id, std::string name="empty", std::string town="empty",
        std::string province="empty", std::string country="empty", int age=0,
        double rank=0, int entry_year=0, int premium=0);
    
    inline int GetPremium(){return premium_;}
    inline void SetPremium(int premium){premium_ = premium;}

};

#endif