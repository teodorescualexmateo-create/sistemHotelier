#pragma once
#include "Client.h"
#include "Serviciu.h"
#include <iostream>

class Rezervare {
private:
    int idRezervare;
    Client* beneficiar;
    Serviciu* serviciuAles;
    int unitati; // nopti sau km 
    int nrPersoane;
    static int contorRezervari;

public:
    Rezervare(Client* c, Serviciu* s, int cantitate, int persoane);
    ~Rezervare();

    // Regula celor 3 
    Rezervare(const Rezervare& alta);
    Rezervare& operator=(const Rezervare& alta);

    double calculeazaCostTotal() const;
    void finalizeazaRezervare(); // Aici verific banii si arunc exceptia
    void afiseazaFactura() const;
};