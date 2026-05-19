#include "Client.h"
#include "Rezervare.h"
#include "Exception.h"
#include<iostream>

Client::Client(const std::string& nume, const std::string& email, const std::string& parola, double balanta): Utilizator(nume, email, parola){
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


bool Client::efectueazaRezervare(Serviciu* serviciu, int unitati, int persoane, int km) {
    if (serviciu == nullptr) {
        throw SistemException("Serviciul selectat nu este valid!");
    }

    double pretUnitar = serviciu->calculeazaPret();
    double costTotal = pretUnitar * unitati;

    if (balanta >= costTotal) {
        balanta -= costTotal;
        
        Rezervare* rez = new Rezervare(this, serviciu, unitati, persoane, km);
        rez->finalizeazaRezervare();
        rez->afiseazaFactura();
        
        delete rez; 
        return true;
    } else {
        throw SistemException("Fonduri insuficiente pentru a finaliza aceasta rezervare!");
    }
}