#include "Client.h"
#include<iostream>

Client::Client(std::string nume, std::string email, std::string parola,double balanta): Utilizator(nume,email,parola){
    this->balanta=balanta;
}
Client::~Client(){}
void Client::afiseazaProfil() const {
    std::cout << "\n================================" << std::endl;
    std::cout << "      PROFIL CLIENT (ID: " << id << ")" << std::endl;
    std::cout << "================================" << std::endl;
    std::cout << "Nume:    " << nume << std::endl;
    std::cout << "Email:   " << email << std::endl;
    std::cout << "Balanta: " << balanta << " RON" << std::endl;
    std::cout << "================================\n" << std::endl;
}
void Client::depunere(double suma){
    if(suma>0){
        balanta +=suma;
        std::cout<<"S-a adaugat suma: "<<suma <<" RON la balanta!"<< std::endl;
    }else{
        std::cout<<"Eroare, suma pentru tranzactie trebuie sa fie pozitiva!"<< std::endl;
    }
}

bool Client::retragere(double suma){
    if(suma<=0) return false;
    if(balanta>=suma){
        balanta-=suma;
        std::cout<<"Tranzactie reusita!"<<std::endl;
        return true;
    }else{
        std::cout<<"Fonduri insuficiente!"<<std::endl;
        return false;
    }
}
