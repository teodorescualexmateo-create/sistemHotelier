#include "PachetVacanta.h"
#include "Rezervare.h"
#include "Exception.h"
#include <iomanip>

int Rezervare::contorRezervari = 10000;

Rezervare::Rezervare(Client* c, Serviciu* s, int cantitate, int persoane, int km)
    : beneficiar(c), serviciuAles(s), unitati(cantitate), kmPachet(km), nrPersoane(persoane) {
    idRezervare = ++contorRezervari;
}

Rezervare::~Rezervare() {}

Rezervare::Rezervare(const Rezervare& alta) {
    this->idRezervare = ++contorRezervari;
    this->beneficiar = alta.beneficiar;
    this->serviciuAles = alta.serviciuAles;
    this->unitati = alta.unitati;
    this->kmPachet = alta.kmPachet;
    this->nrPersoane = alta.nrPersoane;
}

Rezervare& Rezervare::operator=(const Rezervare& alta) {
    if (this != &alta) {
        this->beneficiar = alta.beneficiar;
        this->serviciuAles = alta.serviciuAles;
        this->unitati = alta.unitati;
        this->kmPachet = alta.kmPachet;
        this->nrPersoane = alta.nrPersoane;
        this->idRezervare = ++contorRezervari;
    }
    return *this;
}
double Rezervare::calculeazaCostTotal() const {
    double costBaza = 0;
    
    if (PachetVacanta* pachet = dynamic_cast<PachetVacanta*>(serviciuAles)) {
        Cazare* componentaCazare = dynamic_cast<Cazare*>(pachet);
        Transport* componentaTransport = dynamic_cast<Transport*>(pachet);
        
        double costCazare = componentaCazare->calculeazaPret() * unitati;
        double costTransport = componentaTransport->calculeazaPret() * kmPachet;
        
        double pretRedus1Unitate = pachet->calculeazaPret(); 
        double pretIntreg1Unitate = componentaCazare->calculeazaPret() + componentaTransport->calculeazaPret();
        double factorDiscount = pretRedus1Unitate / pretIntreg1Unitate;
        
        costBaza = (costCazare + costTransport) * factorDiscount;
    }
    else {
        costBaza = serviciuAles->calculeazaPret() * unitati;
    }

    return costBaza * nrPersoane; 
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
   
    if (dynamic_cast<PachetVacanta*>(serviciuAles)) {
        std::cout << "Cantitate: " << unitati << " nopti si " << kmPachet << " km transport" << std::endl;
    } else if (dynamic_cast<Transport*>(serviciuAles)) {
        std::cout << "Cantitate: " << unitati << " km" << std::endl;
    } else {
        std::cout << "Cantitate: " << unitati << " nopti" << std::endl;
    }
    
    std::cout << "Numar persoane: " << nrPersoane << std::endl;
    std::cout << "------------------------------------------" << std::endl;
    std::cout << "TOTAL DE PLATA: " << std::fixed << std::setprecision(2) << calculeazaCostTotal() << " RON" << std::endl;
    std::cout << "------------------------------------------\n" << std::endl;
}