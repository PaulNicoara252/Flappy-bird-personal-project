#include "Vieti.h"


int Vieti::getVieti() const {
    return vieti;
}

void Vieti::setVieti(int vieti) {
    this->vieti = vieti;
}

int Vieti::getVietiInitiale() const {
    return vietiInitiale;
}

void Vieti::reset() {
    vieti = vietiInitiale;
}

Vieti& Vieti::operator++() {
    ++vieti;
    return *this;
}

Vieti& Vieti::operator--() {
    if (vieti > 0) {
        --vieti;
    }
    return *this;
}


Vieti::~Vieti() {}// Destructor
