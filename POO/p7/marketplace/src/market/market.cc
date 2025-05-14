#include "market.h"

Market::Market(std::string slogan){
    slogan_ = slogan;
}

bool Market::AddClient(Client c){
    std::string id = c.GetId();
    for(auto it = client_list_.begin(); it != client_list_.end(); ++it){
        if(it->GetId() == id){
            return false;
        }
    }
    client_list_.push_back(c);
    return true;
}

bool Market::AddSeller(Seller s){
    std::string id = s.GetId();
    for(auto it = seller_list_.begin(); it != seller_list_.end(); ++it){
        if(it->GetId() == id){
            return false;
        }
    }
    seller_list_.push_back(s);
    return true;
}

bool Market::DeleteClient(Client c){
    std::string id = c.GetId();
    for(auto it = client_list_.begin(); it != client_list_.end(); ++it){
        if(it->GetId() == id){
            client_list_.erase(it);
            return true;
        }
    }
    return false;
}

bool Market::DeleteSeller(Seller s){
    std::string id = s.GetId();
    for(auto it = seller_list_.begin(); it != seller_list_.end(); ++it){
        if(it->GetId() == id){
            seller_list_.erase(it);
            return true;
        }
    }
    return false;
}

bool Market::AddProductClient(Product p, std::string id_client){
    for(auto itS = seller_list_.begin(); itS != seller_list_.end(); ++itS){
        if(itS->DeleteProduct(p)){
            for(auto itC = client_list_.begin(); itC != client_list_.end(); ++itC){//Client
                if(itC->GetId() == id_client){
                    itC->AddProduct(p);
                    return true;
                }
            }
        return false;
        }
    }
    return false;
}

bool Market::AddProductSeller(Product p, std::string id_seller){
    for(auto it = seller_list_.begin(); it != seller_list_.end(); ++it){
        if(it->GetId() == id_seller){
            it->AddProduct(p);
            return true;
        }
    }
    return false;
}

bool Market::DeleteProductClient(Product p, std::string id_client){
    for(auto it = client_list_.begin(); it != client_list_.end(); ++it){
        if(it->GetId() == id_client){
            return it->DeleteProduct(p);
            return true;
        }
    }
    return false;
}

bool Market::DeleteProductSeller(Product p, std::string id_seller){
    for(auto it = seller_list_.begin(); it != seller_list_.end(); ++it){
        if(it->GetId() == id_seller){
            return it->DeleteProduct(p);
            return true;
        }
    }
    return false;
}

float Market::GetMoneyInBasket(){
    float total = 0.0;
    for(auto it = client_list_.begin(); it != client_list_.end(); ++it){
        total += it->GetTotal();
    }
    return total;
}

bool Market::DumpMarket(int outmode){
    if(outmode < 0 || outmode > 1){
        return false;
    }
    else if(outmode == 1){
        std::ofstream f; //modo escritura
        f.open("ventas.txt"); 
        if(!f){
            std::cout << "Error al abrir el fichero" << std::endl; 
            return false;
        }
        f << "|-------------------------------------|" << std::endl;
        f << "| CLIENT ID | PRODUCT ID |PRODUCT QTY |" << std::endl;
        for(auto i = client_list_.begin(); i!=client_list_.end(); ++i){
            std::vector<std::string> Ids = i->GetIds();
            std::vector<int> Qtys = i->GetQs();
            for(int j = 0; j<(i->GetSize()); ++j){
                f << "|     " << i->GetId() << "    |     " << Ids[j] << "     |      "
                << Qtys[j] << "    |" << std::endl;
            }
        }
        f << "|-------------------------------------|" << std::endl;
        f << "|TOTAL:            " << GetMoneyInBasket() << " €             |" << std::endl;
        f << "|-------------------------------------|" << std::endl;
        f.close(); //cerrar
        return true;
    }
    else if(outmode == 0){
        std::ifstream f; //modo lectura
        f.open("ventas.txt");
        if(!f){
            std::cout << "Error al abrir el fichero" << std::endl; 
            return false;
        }
        std::string linea;
        while(std::getline(f, linea)){
            std::cout << linea << std::endl;
        }
        f.close();
        return true;
    }
    return false;
}