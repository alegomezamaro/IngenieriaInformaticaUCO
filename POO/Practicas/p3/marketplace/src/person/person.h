// Delaración de la clase Person
#include <string>
#include <vector>
#include <iostream>
#include <cstdio>

class Person{

private: // datos internos de la clase (solo se acceden desde las funciones internas)
    std::string name_;
    int age_;
    double rank_;
    std::vector<std::string> preferences_;
    std::string id_; // identifica a una persona en el marketplace.
    std::string town_; // ciudad
    std::string province_; // provincia
    std::string country_; // país
    int entry_year_; // el año de alta de la persona en el sistema

public: // funciones internas de la clase (se acceden desde el objeto y el operador . )
    Person(std::string id, std::string name="empty", std::string town="empty",
        std::string province="empty", std::string country="empty", int age=0,
        double rank=0, int entry_year=0);
    
    std::string GetDataStr();
    inline std::vector<std::string> GetPreferences(){return preferences_;}
    inline void AddPreference(std::string s1){preferences_.push_back(s1);}
    void AddPreferences(std::string s1, std::string s2, std::string s3);
    void ShowPreferences();
    void ChangePreference(int pos, std::string s1);
    inline std::string GetId(){return id_;}
    inline void SetId(std::string id){id_=id;}
    inline std::string GetName(){return name_;}
    inline void SetName(std::string name){name_=name;}
    inline std::string GetTown(){return town_;}
    inline void SetTown(std::string town){town_=town;}
    inline std::string GetProvince(){return province_;}
    inline void SetProvince(std::string province){province_=province;}
    inline std::string GetCountry(){return country_;}
    inline void SetCountry(std::string country){country_=country;}
    inline int GetAge(){return age_;}
    bool SetAge(int age);
    inline double GetRank(){return rank_;}
    inline void SetRank(double rank){rank_=rank;}
    inline int GetEntryYear(){return entry_year_;}
    bool SetEntryYear(int entry_year);

};