#pragma once

#include <string>
#include <iostream>

class Utilizator {
    protected:
        int id;
        std::string nume;
        std::string email;
        std::string parola;
        static int contorID;
    public:
        Utilizator(std::string nume, std::string email, std::string parola);

        //Destructor virtual
        virtual ~Utilizator();
        
        virtual void afiseazaProfil() const = 0;

        //getter
        int getId() const { return id; }
        std::string getNume() const { return nume; }
        std::string getEmail() const { return email; }
        std::string getParola() const { return parola; }
    };