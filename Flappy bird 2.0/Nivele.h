#include <vector>
#include "ElementeJoc.h"

class Nivele : public ElementJoc {
private:
    int nivel;
    std::vector<char> simboluriPasare;
public:
    Nivele();
    ~Nivele();

    void actualizeazaNivel(int scor);
    char getSimbolPasareCurent() const;

    void setNivel(int nivel);
    int getNivel() const;

    void reset() override;//metoda  virtuala

};
