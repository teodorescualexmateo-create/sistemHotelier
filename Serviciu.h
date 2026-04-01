#pragma once
#include <string>

class Serviciu {
    protected:
        int idServiciu;
        std::string nume;
        // taxa pe care o ia aplicatia din pretul platit de client
        double taxaFixa;
        static int contorIdServicii;
    public:
        Serviciu(std::string nume, double taxaFixa);
        // constructor de copiere
        Serviciu(const Serviciu& altul);
        Serviciu& operator=(const Serviciu& altul);
        virtual ~Serviciu();

        virtual double calculeazaPret() const = 0;
        virtual void afiseazaDetalii() const = 0;

        int getId() const { return idServiciu; }
        double getTaxaFixa() const { return taxaFixa; }
};

