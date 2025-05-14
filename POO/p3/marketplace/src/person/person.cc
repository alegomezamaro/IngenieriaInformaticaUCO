#include "person.h"

Person::Person(std::string id, std::string name, std::string town, std::string province,
    std::string country, int age, double rank, int entry_year){
    id_=id;
    name_=name;
    town_=town,
    province_=province;
    country_=country;
    age_=age;
    rank_=rank;
    if(entry_year>0){
        entry_year_=entry_year;
    }else{
        entry_year_=0;
    }
}

std::string Person::GetDataStr(){
    return std::string("Person:\n") +
    "id: " + id_ + "\n" +
    "name: " + name_ + "\n" +
    "town: " + town_ + "\n" +
    "province: " + province_ + "\n" +
    "country: " + country_ + "\n" +
    "age: " + std::to_string(age_) + "\n" +
    "rank: " + std::to_string(rank_) + "\n" +
    "entry year: " + std::to_string(entry_year_) + "\n";
}

void Person::AddPreferences(std::string s1, std::string s2, std::string s3){
    preferences_.insert(preferences_.begin(), s1);
    preferences_.insert(preferences_.end(), s3);
    preferences_.insert(preferences_.begin()+(preferences_.size()/2), s2);
}

void Person::ShowPreferences(){
    std::cout << "\nLas preferencias son: " << std::endl;
    for (auto s: preferences_){
        std::cout << s << std::endl;
    }
}

void Person::ChangePreference(int pos, std::string s1){
    try{
        preferences_.at(pos) = s1;
    }
    catch (std::out_of_range const& exc){
        std::cout << exc.what() << '\n';
    }
}

bool Person::SetAge(int age){
    if(age > 0){
        age_ = age;
        return true;
    }
    return false;
}

bool Person::SetEntryYear(int entry_year){
    if(entry_year > 2000){
        entry_year_=entry_year;
        return true;
    }
    return false;
}