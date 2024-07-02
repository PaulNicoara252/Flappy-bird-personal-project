#pragma once


#include <vector> // gestioneaza  coordonatele obstacolelor/power-ups
#include <string> //pentru sirurile de caractere (povestea)
#include <ctime> //initializeaza generatorul de numere aleatorii
#include "Nivele.h"
#include "Vieti.h"

class Joc {
private:
    void initializeaza();// initializeaza variailele de joc si seteaza obstacolele
    void actualizeaza();// actualizeaza daca se schimba ceva in scor, vieti, obstacole, powerups
    void deseneaza();//  face harta
    void Player(); // pozitia initiala a lui Randunelu'
    void reseteazaObstacole();// reseteza obstacolele
    void creeazaHarta(); // creeaza harta si gestioneaza power-up-urile
    void verificaColiziune();// verifica coliziunile dintre jucator și obstacole sau power-ups
    void actualizeazaScor();// actualizează scorul jucatorului
    void salveazaScoruri();// salveaza scorurile în fisier
    void plaseazaPowerUps(); // plaseaza power-ups pe harta
    void actualizeazaPowerUps(); // actualizeaza pozitiile power-ups
    void afiseazaPoveste();// afiseaza povestea lui Randunelu'
    void setScor(int scor); // setteri pentru scor
    void setPozitieJucator(int pozitieJucator);// seteaza pozitia jucatorului
    void setRuleaza(bool Ruleaza); // setter pentru a verifica daca ruleaza sau nus
    int numaraObstacole(int index); // functie recursiva ce arată numărul de obstacole.


    bool Ruleaza; // Indică dacă jocul rulează
    int scor; // Scorul curent al jucătorului
    int pozitieJucator; // Poziția curentă a jucătorului pentru desenare și coliziuni
    std::vector<int> obstacoleX; // Coordonatele X ale obstacolelor
    std::vector<int> obstacoleY; // Coordonatele Y ale obstacolelor
    std::vector<std::vector<std::string>> harta; // Reprezentarea hărții jocului
    time_t timpStart; // Momentul de start al jocului, utilizat pentru generarea obstacolelor și power-ups
    Nivele nivele; // Instanță a clasei Nivele
    Vieti vieti; // Instanță a clasei Vieti
    std::vector<int> powerUpsX; // Coordonatele X ale power-ups
    std::vector<int> powerUpsY; // Coordonatele Y ale power-ups
    std::string poveste; // Povestea jocului


public:
    Joc();
    void ruleaza(); //bucla principala a jocului
    ~Joc();     

};

