#include "InterfataSistem.h"
#include <iostream>

int main() {
    try {
        // bucla principala
        MeniuAutentificare::getInstance().pornireSistem();
    } 
    catch (const std::exception& e) {
        std::cerr << "Eroare la inchiderea aplicatiei: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "\nAplicatie inchisa cu succes. O zi buna!" << std::endl;
    return 0;
}