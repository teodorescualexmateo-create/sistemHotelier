#include "Transport.h"
#include <iostream>

Transport::Transport(const std::string& nume, double taxaFixa, double pretKm, const std::string& tip)
    : Serviciu(nume, taxaFixa), pretPerKm(pretKm), tipVehicul(tip) {
}
Transport::Transport(const Transport& altul) : Serviciu(altul) {
    this->pretPerKm = altul.pretPerKm;
    this->tipVehicul = altul.tipVehicul;
}

Transport& Transport::operator=(const Transport& altul) {
    if (this != &altul) {
        Serviciu::operator=(altul);
        this->pretPerKm = altul.pretPerKm;
        this->tipVehicul = altul.tipVehicul;
    }
    return *this;
}
Transport::~Transport() {}

double Transport::calculeazaPret() const {
    return taxaFixa + pretPerKm;
}

void Transport::afiseazaDetalii() const {
    Serviciu::afiseazaDetalii(); 
    std::cout << "Vehicul: " << tipVehicul << std::endl;
}