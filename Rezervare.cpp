#include "Rezervare.h"
#include "Exception.h"
#include <iomanip>

int Rezervare::contorRezervari = 10000;

Rezervare::Rezervare(Client* c, Serviciu* s, int cantitate, int persoane)
    : beneficiar(c), serviciuAles(s), unitati(cantitate), nrPersoane(persoane) {
    idRezervare = ++contorRezervari;
}

Rezervare::~Rezervare() {}

Rezervare::Rezervare(const Rezervare& alta) {
    this->idRezervare = ++contorRezervari;
    this->beneficiar = alta.beneficiar;
    this->serviciuAles = alta.serviciuAles;
    this->unitati = alta.unitati;
    this->nrPersoane = alta.nrPersoane;
}
Rezervare& Rezervare::operator=(const Rezervare& alta) {
    if (this != &alta) {
        this->beneficiar = alta.beneficiar;
        this->serviciuAles = alta.serviciuAles;
        this->unitati = alta.unitati;
        this->nrPersoane = alta.nrPersoane;
    }
    return *this;
}

double Rezervare::calculeazaCostTotal() const {
    return serviciuAles->calculeazaPret() * unitati * (nrPersoane/2.0);
}

void Rezervare::finalizeazaRezervare() {
    double total = calculeazaCostTotal();
    
    if (beneficiar->getBalanta() < total) {
        throw SistemException("Fonduri insuficiente! Balanta actuala: " + 
                               std::to_string(beneficiar->getBalanta()) + " RON. Necesar: " + 
                               std::to_string(total) + " RON.");
    }
    
    beneficiar->retragere(total);
    std::cout << "Rezervarea #" << idRezervare << " a fost platita cu succes!" << std::endl;
}

void Rezervare::afiseazaFactura() const {
    std::cout << "\n>>>> FACTURA REZERVARE #" << idRezervare << " <<<<" << std::endl;
    std::cout << "Client: " << beneficiar->getNume() << std::endl;
    std::cout << "Serviciu selectat: ";
    serviciuAles->afiseazaDetalii(); 
    std::cout << "Cantitate (nopti/km): " << unitati << std::endl;
    std::cout << "Numar persoane: " << nrPersoane << std::endl;
    std::cout << "------------------------------------------" << std::endl;
    std::cout << "TOTAL DE PLATA: " << std::fixed << std::setprecision(2) << calculeazaCostTotal() << " RON" << std::endl;
    std::cout << "------------------------------------------\n" << std::endl;
}