#include "Proprietar.h"
#include <iostream>
#include<vector>

Proprietar::Proprietar(std::string nume, std::string email, std::string parola): Utilizator(nume,email,parola){
    venitTotal=0.0;
}

Proprietar::~Proprietar(){};

void Proprietar::afiseazaProfil() const{
     std::cout << "\n================================" << std::endl;
    std::cout << "      PROFIL PROPRIETAR (ID: " << id << ")" << std::endl;
    std::cout << "================================" << std::endl;
    std::cout << "Nume:    " << nume << std::endl;
    std::cout << "Email:   " << email << std::endl;
    std::cout << "Venit total: " << venitTotal << " RON" << std::endl;
    std::cout << "Numar proprietati listate: " << proprietatiDeInchiriat.size() << std::endl;
    std::cout << "================================\n" << std::endl;
}

void Proprietar::colecteazaChirie(double suma){
    if(suma>0){
        venitTotal += suma;
        std::cout << "Ati primit o plata de " << suma << " RON." << std::endl;
    }
}

void Proprietar::adaugaProprietate(void* proprietate){
    if(proprietate != nullptr){
        proprietatiDeInchiriat.push_back(proprietate);
    }
}

void Proprietar::eliminaProprietate(int index){
    // sterg proprietatea de pe pozitia indexului 
    if(index >=0 && index < (int)proprietatiDeInchiriat.size()){
        proprietatiDeInchiriat.erase(proprietatiDeInchiriat.begin() + index);
    }
}
