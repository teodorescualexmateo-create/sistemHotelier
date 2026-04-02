#include "Utilizator.h"

int Utilizator::contorID = 0;

Utilizator::Utilizator(const std::string& nume, const std::string& email, const std::string& parola):
    nume(nume), email(email), parola(parola){
        this->id = ++contorID;
}

Utilizator::~Utilizator(){}
