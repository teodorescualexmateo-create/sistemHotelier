#include "Cazare.h"
#include <iostream>
#include <string>

Cazare::Cazare(std::string denumire, double pretBaza, double pretNoapte, int capacitatePersoane, bool oferaParcare):
        Serviciu(denumire,pretBaza), pretNoapte(pretNoapte),capacitatePersoane(capacitatePersoane), oferaParcare(oferaParcare){}
        
Cazare::Cazare(const Cazare& alta) : Serviciu(alta) {
    this->pretNoapte = alta.pretNoapte;
    this->capacitatePersoane = alta.capacitatePersoane;
    this->oferaParcare = alta.oferaParcare;
}

Cazare& Cazare::operator=(const Cazare& alta) {
    if (this != &alta) {
        Serviciu::operator=(alta);
        this->pretNoapte = alta.pretNoapte;
        this->capacitatePersoane = alta.capacitatePersoane;
        this->oferaParcare = alta.oferaParcare;
    }
    return *this;
}
Cazare::~Cazare(){};

double Cazare::calculeazaPret() const{
    return taxaFixa + pretNoapte;
}
void Cazare::afiseazaDetalii() const {
    Serviciu::afiseazaDetalii(); 
    std::cout << "Capacitate: " << capacitatePersoane << " pers." << std::endl;
}
