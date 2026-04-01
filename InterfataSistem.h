#pragma once
#include <vector>
#include <string>
#include "Utilizator.h"
#include "Client.h"
#include "Proprietar.h"
#include "Serviciu.h"
#include "Exception.h"

// Meniu secundar pt clienti
class MeniuClient {
private:
    MeniuClient() {}
public:
    static MeniuClient& getInstance();
    void run(Client* clientLogat, std::vector<Serviciu*>& catalog);
};

// Meniu secundar pt proprietari
class MeniuProprietar {
private:
    MeniuProprietar() {}
public:
    static MeniuProprietar& getInstance();
    void run(Proprietar* propLogat, std::vector<Serviciu*>& catalog);
};

// Meniu Principal
class MeniuAutentificare {
private:
    std::vector<Utilizator*> utilizatori; //baza de date a utilizatorilor
    std::vector<Serviciu*> catalog;

    MeniuAutentificare();
    MeniuAutentificare(const MeniuAutentificare&) = delete;
    MeniuAutentificare& operator=(const MeniuAutentificare&) = delete;

public:
    static MeniuAutentificare& getInstance();
    ~MeniuAutentificare();

    void pornireSistem();
    void inregistrare();
    void login();
};