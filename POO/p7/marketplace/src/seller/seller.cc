#include "seller.h"

Seller::Seller(std::string id, std::string name, std::string town, std::string province,
    std::string country, int age, double rank, int entry_year, std::string sector) : Person(id,
    name, town, province, country, age, rank, entry_year){
    sector_ = sector;
}