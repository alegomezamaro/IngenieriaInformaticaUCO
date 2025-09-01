#include "client.h"

Client::Client(std::string id, std::string name, std::string town, std::string province,
    std::string country, int age, double rank, int entry_year, int premium) : Person(id,
    name, town, province, country, age, rank, entry_year){
    premium_ = premium;
}