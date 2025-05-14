// Delaración de la clase Person
#include <string>

class Person{

private: // datos internos de la clase (solo se acceden desde las funciones internas)
    std::string name_;
    int age_;
    double rank_;

public: // funciones internas de la clase (se acceden desde el objeto y el operador . )
    Person(std::string name, int age, double rank) {name_=name;age_=age;rank_=rank;}
    inline std::string GetName(){return name_;}
    inline int GetAge(){return age_;}
    inline double GetRank(){return rank_;}
    std::string GetDataStr(){
    
        return name_ + " " +
        std::to_string(age_) +
        " " + std::to_string(rank_) + "\n";
    
    }

};