#include "ServiciuFactory.h"

Serviciu* ServiciuFactory::creazaCazare(const std::string& nume, double pretBaza, double pretNoapte, int cap, bool parc) {
    return new Cazare(nume, pretBaza, pretNoapte, cap, parc);
}

Serviciu* ServiciuFactory::creazaTransport(const std::string& nume, double pretBaza, double pretKm, const std::string& vehicul) {
    return new Transport(nume, pretBaza, pretKm, vehicul);
}

Serviciu* ServiciuFactory::creazaPachet(const std::string& nume, double pretBaza, double pretNoapte, int cap, bool parc, double pretKm, const std::string& vehicul, double discount) {
    return new PachetVacanta(nume, pretBaza, pretNoapte, cap, parc, pretKm, vehicul, discount);
}