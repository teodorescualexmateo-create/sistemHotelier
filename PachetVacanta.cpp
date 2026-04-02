#include "PachetVacanta.h"
#include <iostream>
#include<iomanip>

PachetVacanta::PachetVacanta(const std::string& nume, double taxaFixa, double pNoapte, int cap, bool parc, 
                             double pKm, const std::string& vehicul, double discount)
    : Serviciu(nume, taxaFixa), 
      Cazare(nume, taxaFixa, pNoapte, cap, parc),
      Transport(nume, taxaFixa, pKm, vehicul),
      discountPachet(discount) {}

PachetVacanta::PachetVacanta(const PachetVacanta& altul) 
    : Serviciu(altul), 
      Cazare(altul), 
      Transport(altul) 
{
    this->discountPachet = altul.discountPachet;
}
PachetVacanta& PachetVacanta::operator=(const PachetVacanta& altul) {
    if (this != &altul) {
        Cazare::operator=(altul);
        Transport::operator=(altul);
        this->discountPachet = altul.discountPachet;
    }
    return *this;
}
PachetVacanta::~PachetVacanta() {}

double PachetVacanta::calculeazaPret() const {
    double pretFaraDiscount = Cazare::calculeazaPret() + Transport::calculeazaPret();
    return pretFaraDiscount * (1.0 - discountPachet);
}

void PachetVacanta::afiseazaDetalii() const {
    std::cout << "\n========== PACHET VACANTA COMBO ==========" << std::endl;
    std::cout << "ID: " << idServiciu << " | Denumire: " << nume << std::endl;
    std::cout << "Taxa Fixa: " << taxaFixa << " RON" << std::endl;
    std::cout << "------------------------------------------" << std::endl;
    
    std::cout << "CAZARE: " << pretNoapte << " RON/noapte (" << capacitatePersoane << " pers.)" << std::endl;
    std::cout << "TRANSPORT: " << pretPerKm << " RON/km (" << tipVehicul << ")" << std::endl;
    std::cout << "------------------------------------------" << std::endl;
    
    std::cout << "DISCOUNT: " << discountPachet * 100 << "%" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "PRET TOTAL PORNIRE: " << calculeazaPret() << " RON (1 noapte)" << std::endl;
    std::cout << "==========================================\n" << std::endl;
}