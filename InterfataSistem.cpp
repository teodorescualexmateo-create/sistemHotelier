#include "InterfataSistem.h"
#include "Cazare.h"
#include "Transport.h"
#include "Rezervare.h"
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
            for (auto s : catalog) s->afiseazaDetalii();
        }else if (opt == 5) {
            if (catalog.empty()) {
                std::cout << "Nu exista servicii disponibile in catalog!\n";
            } else {
                std::cout << "\n--- SERVICII DISPONIBILE ---\n";
                for (int i = 0; i < (int)catalog.size(); ++i) {
                    std::cout << i << ". ";
                    catalog[i]->afiseazaDetalii();
                }

            int index, nopti, persoane;
            std::cout << "Alegeti indexul serviciului: "; 
            std::cin >> index;
            
            if (index >= 0 && index < (int)catalog.size()) {
                std::cout << "Numar nopti/unitati: "; 
                std::cin >> nopti;
                std::cout << "Numar persoane: "; 
                std::cin >> persoane;

                try {
                    Rezervare* rez_noua = new Rezervare(client, catalog[index], nopti, persoane);
                    rez_noua->finalizeazaRezervare();
                    rez_noua->afiseazaFactura();
                } 
                catch (const SistemException& e) {
                    std::cerr << "EROARE REZERVARE: " << e.what() << "\n";
                }
            } else {
                std::cout << "Index invalid!\n";
            }
        }
    }
}
}

void MeniuProprietar::run(Proprietar* prop, std::vector<Serviciu*>& catalog) {
    int opt = -1;
    while (opt != 0) {
        std::cout << "\n--- ADMIN: " << prop->getNume() << " ---\n";
        std::cout << "1. Adauga Cazare\n2. Afiseaza Venituri Taxe\n3. Sterge Serviciu (ID)\n0. Logout\nSelectie: ";
        std::cin >> opt;
        
        if (opt == 1) {
            std::string nume; double taxa, pret; int cap;
            std::cout << "Nume: "; 
            std::cin.ignore(); // pt buffer
            std::getline(std::cin, nume); // pt spatiu dintre cuv
            std::cout << "Taxa: "; std::cin >> taxa;
            std::cout << "Pret/noapte: "; std::cin >> pret;
            std::cout << "Capacitate: "; std::cin >> cap;
            std::cout << "Ofera parcare? (DA/NU): "; std::string parcare; std::cin >> parcare;
            bool areParcare = (parcare == "DA" || parcare == "da");
            catalog.push_back(new Cazare(nume, taxa, pret, cap, areParcare));
            std::cout << "Succes!\n";
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