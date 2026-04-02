#pragma once
#include "Serviciu.h"

class Transport : virtual public Serviciu {
protected:
    double pretPerKm;
    std::string tipVehicul;

public:
    Transport(const std::string& nume, double taxaFixa, double pretKm, const std::string& tip);

    Transport(const Transport& altul);
    Transport& operator=(const Transport& altul);
    
    virtual ~Transport() override;
    double calculeazaPret() const override; 
    void afiseazaDetalii() const override;

    double getPretKm() const { return pretPerKm; }
};