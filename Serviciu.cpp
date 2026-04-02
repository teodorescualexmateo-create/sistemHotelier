#include "Serviciu.h"
#include<iostream>
int Serviciu::contorIdServicii = 1000;

Serviciu::Serviciu(const std::string& nume, double taxaFixa):nume(nume),taxaFixa(taxaFixa){
    this->idServiciu = ++contorIdServicii;
}

Serviciu::Serviciu(const Serviciu& altul) {
    this->nume = altul.nume;
    this->taxaFixa = altul.taxaFixa;
    this->idServiciu = ++contorIdServicii;
}

Serviciu& Serviciu::operator=(const Serviciu& altul) {
    if (this != &altul) {
        this->nume = altul.nume;
        this->taxaFixa = altul.taxaFixa;
        this->idServiciu = ++contorIdServicii;
    }
    return *this;
}
Serviciu::~Serviciu(){};

//functie de baza de afisare
void Serviciu::afiseazaDetalii() const {
    std::cout << "ID Serviciu: " << idServiciu << " | Denumire: " << nume
              << " | Pret Baza: " << taxaFixa << " RON" << std::endl;
};

