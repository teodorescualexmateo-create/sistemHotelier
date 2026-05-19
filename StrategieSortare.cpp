#include "StrategieSortare.h"
#include <algorithm>

void SortareDupaPret::sorteaza(std::vector<Serviciu*>& catalog) {
   
    std::sort(catalog.begin(), catalog.end(), [](Serviciu* a, Serviciu* b) {
        return a->calculeazaPret() < b->calculeazaPret();
    });
}

void SortareDupaNume::sorteaza(std::vector<Serviciu*>& catalog) {
    std::sort(catalog.begin(), catalog.end(), [](Serviciu* a, Serviciu* b) {
        return a->getNume() < b->getNume();
    });
}