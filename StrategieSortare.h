#pragma once
#include "Serviciu.h"
#include <vector>


class StrategieSortare {
public:
    virtual void sorteaza(std::vector<Serviciu*>& catalog) = 0;
    virtual ~StrategieSortare() = default;
};

class SortareDupaPret : public StrategieSortare {
public:
    void sorteaza(std::vector<Serviciu*>& catalog) override;
};

class SortareDupaNume : public StrategieSortare {
public:
    void sorteaza(std::vector<Serviciu*>& catalog) override;
};