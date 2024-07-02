// Nivele.cpp
#include "Nivele.h"

Nivele::Nivele() : nivel(0), simboluriPasare({ '>', 'Q', 'Y', '%' }) {}
Nivele::~Nivele() {}

void Nivele::actualizeazaNivel(int scor) {
    if (scor > 20) {
        nivel = 3; 
    } else if (scor > 15) {
        nivel = 2; 
    } else if (scor > 10) {
        nivel = 1; 
    } else {
        nivel = 0; 
    }
}

char Nivele::getSimbolPasareCurent() const {
    return simboluriPasare[nivel];
}

void Nivele::setNivel(int nivel) {
    this->nivel = nivel;
}

int Nivele::getNivel() const {
    return nivel;
}

void Nivele::reset() {
    nivel = 0;
}
