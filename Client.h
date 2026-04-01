#pragma once
#include "Utilizator.h"

class Client:public Utilizator{
    private:
        double balanta;
    public:
        Client(std::string nume, std::string email, std::string parola,double balanta);

        ~Client();
        void afiseazaProfil() const override;
        void depunere(double suma);
        bool retragere(double suma);
        double getBalanta() const { return balanta; }

        
};
