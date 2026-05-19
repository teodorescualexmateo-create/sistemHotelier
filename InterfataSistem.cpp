#include "InterfataSistem.h"
#include "Cazare.h"
#include "Transport.h"
#include "PachetVacanta.h"
#include "Rezervare.h"
#include "ServiciuFactory.h"
#include "StrategieSortare.h"
#include <iostream>

// initierea singleton-urilor
MeniuClient& MeniuClient::getInstance() { static MeniuClient inst; return inst; }
MeniuProprietar& MeniuProprietar::getInstance() { static MeniuProprietar inst; return inst; }
MeniuAutentificare& MeniuAutentificare::getInstance() { static MeniuAutentificare inst; return inst; }

void MeniuClient::run(Client* client, std::vector<Serviciu*>& catalog) {
    int opt = -1;
    while (opt != 0) {
        std::cout << "\n[CLIENT: " << client->getNume() << "] 1.Sold 2.Depunere 3.Retragere 4.Catalog 5.Rezervare 0.Logout: ";
        std::cin >> opt;
        if (opt == 1) std::cout << "Sold: " << client->getBalanta() << " RON\n";
        else if (opt == 2) { double s; std::cout << "Suma: "; std::cin >> s; client->depunere(s); }
        else if (opt == 3) { double s; std::cout << "Suma: "; std::cin >> s; client->retragere(s); }
        else if (opt == 4) {
                std::cout << "\n--- CATALOG SERVICII DISPONIBILE ---\n";
                std::cout << "Cum doriti sa fie afisat catalogul?\n";
                std::cout << "1. Sortat crescator dupa pret\n";
                std::cout << "2. Sortat alfabetic (dupa denumire)\n";
                std::cout << "3. Nesortat (implicit)\n";
                std::cout << "Optiune sortare: ";
                
                int optSortare;
                std::cin >> optSortare;

                StrategieSortare* strategie = nullptr;
                if (optSortare == 1) {
                    strategie = new SortareDupaPret();
                } else if (optSortare == 2) {
                    strategie = new SortareDupaNume();
                }

                if (strategie != nullptr) {
                    strategie->sorteaza(catalog);
                    delete strategie; 
                }
            for (auto s : catalog) s->afiseazaDetalii();
        }else if (opt == 5) {
            if (catalog.empty()) {
                std::cout << "Nu exista servicii disponibile in catalog!\n";
            } else {
                
                std::cout << "\n--- CATALOG SERVICII DISPONIBILE ---\n";
                std::cout << "Cum doriti sa fie afisat catalogul?\n";
                std::cout << "1. Sortat crescator dupa pret\n";
                std::cout << "2. Sortat alfabetic (dupa denumire)\n";
                std::cout << "3. Nesortat (implicit)\n";
                std::cout << "Optiune sortare: ";
                
                int optSortare;
                std::cin >> optSortare;

                StrategieSortare* strategie = nullptr;
                if (optSortare == 1) {
                    strategie = new SortareDupaPret();
                } else if (optSortare == 2) {
                    strategie = new SortareDupaNume();
                }

                if (strategie != nullptr) {
                    strategie->sorteaza(catalog);
                    delete strategie; 
                }

                for (int i = 0; i < (int)catalog.size(); i++) {
                    std::cout << "Index [" << i << "] ";
                    catalog[i]->afiseazaDetalii();
                }

                int index;
                std::cout << "Alegeti indexul serviciului dorit: "; 
                std::cin >> index;
                
                if (index >= 0 && index < (int)catalog.size()) {
                    int nopti = 0, km = 0, persoane = 0;
                    
                    if (dynamic_cast<PachetVacanta*>(catalog[index])) {
                        std::cout << "Numar nopti cazare: "; std::cin >> nopti;
                        std::cout << "Numar kilometri transport: "; std::cin >> km;
                    } 
                    else if (dynamic_cast<Transport*>(catalog[index])) {
                        std::cout << "Numar kilometri: "; std::cin >> nopti; 
                    } 
                    else {
                        std::cout << "Numar nopti: "; std::cin >> nopti;
                    }
                    
                    std::cout << "Numar persoane: "; std::cin >> persoane;

                    try {
                        client->efectueazaRezervare(catalog[index], nopti, persoane, km);
                    } 
                    catch (const SistemException& e) {
                        std::cerr << "EROARE REZERVARE: " << e.what() << "\n";
                    }
                }
            }
        }
            
        
    }
}


void MeniuProprietar::run(Proprietar* prop, std::vector<Serviciu*>& catalog) {
    int opt = -1;
    while (opt != 0) {
        std::cout << "\n--- ADMIN: " << prop->getNume() << " ---\n";
        std::cout << "1. Adauga\n2. Afiseaza Venituri Taxe\n3. Sterge Serviciu (ID)\n0. Logout\nSelectie: ";
        std::cin >> opt;
        
        if (opt == 1) {
            std::string denumire;
            double pretBaza;
            std::cout << "Denumire serviciu: "; std::cin.ignore(); std::getline(std::cin, denumire);
            std::cout << "Taxa fixa (pret baza): "; std::cin >> pretBaza;

            std::cout << "Ce tip de serviciu doriti sa adaugati?\n1. Cazare\n2. Transport\n3. Pachet Vacanta\nOptiune: ";
            int tipServiciu;
            std::cin >> tipServiciu;

            if (tipServiciu == 1) {
                double pretNoapte;
                int capacitate;
                bool parcare;
                std::cout << "Pret pe noapte: "; std::cin >> pretNoapte;
                std::cout << "Capacitate persoane: "; std::cin >> capacitate;
                std::cout << "Ofera parcare? (1 = Da, 0 = Nu): "; std::cin >> parcare;

                catalog.push_back(ServiciuFactory::creazaCazare(denumire, pretBaza, pretNoapte, capacitate, parcare));
                std::cout << "Cazare adaugata cu succes in catalog!\n";
            }
            else if (tipServiciu == 2) {
                double pretKm;
                std::string vehicul;
                std::cout << "Pret pe kilometru: "; std::cin >> pretKm;
                std::cout << "Tip vehicul (ex: Autobuz, Avion, Masina): "; std::cin.ignore(); std::getline(std::cin, vehicul);

                catalog.push_back(ServiciuFactory::creazaTransport(denumire, pretBaza, pretKm, vehicul));
                std::cout << "Transport adaugat cu succes in catalog!\n";
            }
            else if (tipServiciu == 3) {
                double pretNoapte, pretKm, discount;
                int capacitate;
                bool parcare;
                std::string vehicul;

                std::cout << "[Date Cazare] Pret pe noapte: "; std::cin >> pretNoapte;
                std::cout << "[Date Cazare] Capacitate persoane: "; std::cin >> capacitate;
                std::cout << "[Date Cazare] Ofera parcare? (1 = Da, 0 = Nu): "; std::cin >> parcare;
                std::cout << "[Date Transport] Pret pe kilometru: "; std::cin >> pretKm;
                std::cout << "[Date Transport] Tip vehicul: "; std::cin.ignore(); std::getline(std::cin, vehicul);
                std::cout << "Discount pachet (ex: 0.10 pentru 10%): "; std::cin >> discount;

                catalog.push_back(ServiciuFactory::creazaPachet(denumire, pretBaza, pretNoapte, capacitate, parcare, pretKm, vehicul, discount));
                std::cout << "Pachet Vacanta adaugat cu succes in catalog!\n";
            }
            else {
                std::cout << "Optiune invalida de serviciu!\n";
            }
        
        } 
        else if (opt == 2) {
            double total = 0;
            for (auto s : catalog) {
                total += s->getTaxaFixa();
            }
            std::cout << "Venit cumulat din taxe: " << total << " RON\n";
        } 
        else if (opt == 3) {
            int id;
            std::cout << "ID pentru stergere: "; std::cin >> id;
            for (auto it = catalog.begin(); it != catalog.end(); ++it) {
                if ((*it)->getId() == id) {
                    delete *it; 
                    catalog.erase(it);
                    std::cout << "Eliminat.\n";
                    break;
                }
            }
        }
    }
}

MeniuAutentificare::MeniuAutentificare() {}

MeniuAutentificare::~MeniuAutentificare() {
    for (auto u : utilizatori) delete u;
    for (auto s : catalog) delete s;
}

void MeniuAutentificare::pornireSistem() {
    int opt = -1;
    while (opt != 0) {
        std::cout << "\n=== SISTEM HOTELIER ===\n1.Login 2.Inregistrare 0.Iesire: ";
        std::cin >> opt;
        try {
            if (opt == 1) login();
            else if (opt == 2) inregistrare();
            else if (opt != 0) throw SistemException("Optiune invalida!");
        } catch (const std::exception& e) { std::cerr << e.what() << "\n"; }
    }
}

void MeniuAutentificare::inregistrare() {
    std::string n, e, p; int tip;
    std::cout << "Nume: "; std::cin >> n;
    std::cout << "Email: "; std::cin >> e;
    std::cout << "Parola: "; std::cin >> p;
    std::cout << "Tip (1.Client 2.Proprietar): "; std::cin >> tip;
    
    if (tip == 1) utilizatori.push_back(new Client(n, e, p, 0));
    else utilizatori.push_back(new Proprietar(n, e, p));
    std::cout << "Cont creat!\n";
}

void MeniuAutentificare::login() {
    std::string e, p;
    std::cout << "Email: "; std::cin >> e;
    std::cout << "Parola: "; std::cin >> p;

    for (auto u : utilizatori) {
        if (u->getEmail() == e && u->getParola() == p) {
            if (Client* c = dynamic_cast<Client*>(u)) 
                MeniuClient::getInstance().run(c, catalog);
            else if (Proprietar* pr = dynamic_cast<Proprietar*>(u)) 
                MeniuProprietar::getInstance().run(pr, catalog);
            return;
        }
    }
    throw SistemException("Email sau parola gresite!");
}
