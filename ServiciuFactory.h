#pragma once
#include "Serviciu.h"
#include "Cazare.h"
#include "Transport.h"
#include "PachetVacanta.h"
#include <string>

// factory pattern ul pt crearea obiectelor
class ServiciuFactory {
public:
   
    static Serviciu* creazaCazare(const std::string& nume, double pretBaza, double pretNoapte, int cap, bool parc);
    
    static Serviciu* creazaTransport(const std::string& nume, double pretBaza, double pretKm, const std::string& vehicul);
    
    static Serviciu* creazaPachet(const std::string& nume, double pretBaza, double pretNoapte, int cap, bool parc, double pretKm, const std::string& vehicul, double discount);
};