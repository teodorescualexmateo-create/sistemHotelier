#include "Utilizator.h"

int Utilizator::contorID = 0;

Utilizator::Utilizator(std::string nume, std::string email, std::string parola):
    nume(nume), email(email), parola(parola){
        this->id = ++contorID;
}

Utilizator::~Utilizator(){}
