#pragma once
#include "Utilizator.h"
#include <vector>

class Proprietar : public Utilizator {
private:
    double venitTotal;
    // Vector pentru stocarea pointerilor catre proprietati
    std::vector<void*> proprietatiDeInchiriat; 

public:
    Proprietar(std::string nume, std::string email, std::string parola);
    ~Proprietar() override;

    void afiseazaProfil() const override;

    void colecteazaChirie(double suma);
    void adaugaProprietate(void* proprietate);
    void eliminaProprietate(int index);

    double getVenitTotal() const { return venitTotal; }
};