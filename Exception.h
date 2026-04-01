#pragma once
#include <exception>
#include <string>

class SistemException : public std::exception {
private:
    std::string mesaj;

public:
    // Constructor care primeste mesajul erorii
    explicit SistemException(std::string m) : mesaj(std::move(m)) {}

    const char* what() const noexcept override {
        return mesaj.c_str();
    }
};