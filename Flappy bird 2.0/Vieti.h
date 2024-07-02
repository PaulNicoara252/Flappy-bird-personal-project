#include "ElementeJoc.h"

class Vieti : public ElementJoc {
private:
    int vieti;
    int vietiInitiale = 3;
public:

    ~Vieti();

    int getVieti() const;

    void setVieti(int vieti);
    int getVietiInitiale() const;

    // Supraincarcare operator ++ pentru a creste numarul de vieti
    Vieti& operator++();

    // Supraincarcare operator -- pentru a reduce numarul de vieti
    Vieti& operator--();

    // Implementare metode virtuale
    void reset() override; // de asemenea, este si supraincarcare

};