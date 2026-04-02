#pragma once
#include "Utilizator.h"

class Client:public Utilizator{
    private:
        double balanta;
    public:
        Client(const std::string& nume, const std::string& email, const std::string& parola, double balanta);

        ~Client();
        void afiseazaProfil() const override;
        void depunere(double suma);
        bool retragere(double suma);
        double getBalanta() const { return balanta; }

        
};
