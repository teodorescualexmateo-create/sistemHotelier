#include "Serviciu.h"
#include <string>
//mostenire virtuala pt diamant
class Cazare: virtual public Serviciu{
    protected:
        double pretNoapte;
        int capacitatePersoane;
        bool oferaParcare;
    public:
        Cazare(const std::string& denumire, double pretBaza, double pretNoapte, int capacitatePersoane, bool oferaParcare);
        
        Cazare(const Cazare& alta);
        Cazare& operator=(const Cazare& alta);
        virtual ~Cazare() override;

        double calculeazaPret() const override; 
        void afiseazaDetalii() const override;

        double getPretNoapte() const { return pretNoapte; }
        int getCapacitate() const { return capacitatePersoane; }

};