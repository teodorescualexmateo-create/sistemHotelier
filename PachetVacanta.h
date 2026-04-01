#pragma once
#include "Cazare.h"
#include "Transport.h"

class PachetVacanta : public Cazare, public Transport {
    private:
        double discountPachet; // 0.1 pt 10% reducere

    public:
        PachetVacanta(std::string nume, double taxaFixa, double pNoapte, int cap, bool parc, 
                    double pKm, std::string vehicul, double discount);
                    
        PachetVacanta(const PachetVacanta& altul);
        PachetVacanta& operator=(const PachetVacanta& altul);
        
        ~PachetVacanta() override;

        double calculeazaPret() const override;
        void afiseazaDetalii() const override;
};