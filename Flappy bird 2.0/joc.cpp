
#include <iostream>
#include <cstdlib>//folosim rand si srand pentru generarea coordonatelor aleatorii
#include <windows.h> //pentru a seta pozitia cursorului din consola
#include <fstream>
#include <string>
#include <cassert>  // pentru assert

#include "Joc.h"

//generatorul de numere aleatorii ajuta la plasarea obstacolelor. la generarea de power-ups si la reimprospatarea  obstacolelor
//obstacole sunt 3 tot timpul, de acolo e 3 ul in cod
//iluzia de miscare e data de decrementii matricei plaseazaX--;

Joc::Joc() : Ruleaza(true), scor(0), pozitieJucator(9), vieti(), nivele(),
poveste("       Randunelu', un pasaroi curajos, si-a propus sa zboare spre tarile calde.\n"
    "       Drumul e plin de obstacole si provocari,dar el este determinat sa le parcurga pana la capat.\n"
    "        Ajuta-l pe Randunelu' sa ajunga in tarile calde!!!.") {
    srand((time(0)));//initializarea generatorului de numere aleatorii (ajutorul functiei time/cstdlib
    obstacoleX = { 10, 18, 27 };//pozitii initiale unde sa fie puse obstacolele
    obstacoleY.resize(3);//functia resize redimensioneaza vectorul la 3 elemente(cate obstacole concomitente avem)
    reseteazaObstacole(); 
    creeazaHarta();
}

void Joc::ruleaza() {
    system("Color E0"); //executa comanda in shellul-ul OS-ului
    std::cout << "     ____  //\\            _                  _       _ \n";
    std::cout << "    |  _ \\|/ \\| _ __   __| |_   _ _ __   ___| |_   _( )\n";
    std::cout << "    | |_) / _` | '_ \\ / _` | | | | '_ \\ / _ \\ | | | |/ \n";
    std::cout << "    |  _ < (_| | | | | (_| | |_| | | | |  __/ | |_| |  \n";
    std::cout << "    |_| \\_\\__,_|_| |_|\\__,_|\\__,_|_| |_|\\___|_|\\__,_|  \n";
    std::cout << "\n";
    std::cout << "                   Versiunea 3.0";
    std::cout << "\n";
    std::cout << "\n";


    afiseazaPoveste();
    std::cout << "\n";
    std::cout << "\n";

    std::cout << "                   Apasa pe tasta ENTER pentru a incepe!";
    std::cin.get();
    system("cls"); // comanda  "clear screen" care sterge tot continutul anterior 

    while (true) {
        initializeaza(); // initializarea variabilelor din joc
        while (Ruleaza) {
            Player(); // cand apas spacebar
            actualizeaza();//puteri+obstacole (le actualizeaza)
            verificaColiziune();
            deseneaza();
            Sleep(100); // determina cat de rapid se misca jocul,  functia sleep pune programul in pauza timp de 0,1 secunde
        }
        std::cout << "Scor = " << scor << std::endl;
        salveazaScoruri();

        std::cout << "Reincerci? (da/nu)--->(d,n) = ";
        char repeta;
        std::cin >> repeta;
        if (repeta == 'd') {
            std::string command = "start \"\" \"" + std::string(__argv[0]) + "\""; //start- relanseaza programul fara sa i dea nume
            //__argv[0] este numele executabilului curent, și construiește o comandă start pentru a deschide o nouă instanta a acestui program.
            system(command.c_str()); //ruleaza comanda din shell-ul  os-ului    
            exit(0); //iese din program
        }
        else {
            break;
        }
    }
}

void Joc::afiseazaPoveste() {
    std::cout << poveste;
}

void Joc::setScor(int scor) {
    this->scor = scor;
}

void Joc::setPozitieJucator(int pozitieJucator) {
    this->pozitieJucator = pozitieJucator;
}

void Joc::setRuleaza(bool Ruleaza) {
    this->Ruleaza = Ruleaza;
}

void Joc::initializeaza() {
    scor = 0;
    pozitieJucator = 9;
    vieti.reset(); // sa inceapa jocul cu viata initiala
    timpStart = time(0);
    reseteazaObstacole(); 
    creeazaHarta();
    plaseazaPowerUps();
}

void Joc::actualizeaza() {
    assert(obstacoleX.size() == 3 && "Numarul de obstacole trebuie sa fie 3"); //asertiune  
    assert(obstacoleY.size() == 3 && "Numarul de obstacole trebuie sa fie 3");

    for (int i = 0; i < 3; ++i) {
        obstacoleX[i]--;//decrement
    }
    for (int i = 0; i < 3; ++i) {
        if (obstacoleX[i] < 1) {
            obstacoleX[i] = 28; //reseteaza coordonata X 
            obstacoleY[i] = rand() % 12 + 2; //reseteaza coordonata Y a obstacolului
        }
    }

    actualizeazaScor();
    nivele.actualizeazaNivel(scor);
    actualizeazaPowerUps();
    creeazaHarta();
}


void Joc::deseneaza() {
    COORD coord; //gasita pe reddit, e din windows.api si reprezinta o pereche  de coordonate X,Y
    coord.X = 0;
    coord.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // ne asiguram ca harta este  afisata in acelasi loc de fiecare data

    for (const auto& row : harta) {  //parcurge fiecare rand  din matricea hartii
        for (const auto& cell : row) { //parcurge fiecare celula
            std::cout << cell;//afiseaza ce este in celula
        } //celula se refera la | * sau +
        std::cout << std::endl;
    }
    std::cout << "\n";
    std::cout << "Scor: " << scor << "\n";
    std::cout << "Vieti: " << vieti.getVieti() << "\n\n";
    std::cout << "Obstacole active: " << numaraObstacole(0) << "\n";  // Afișează numărul de obstacole active
}


void Joc::Player() {
    if (GetAsyncKeyState(VK_SPACE)) {// verifica daca tasta este apasata
        pozitieJucator -= 3; //daca tasta e apasata, pozitia jucatorului este scazuta cu 3 unitati
    }//trebuie sa scadem 3 unitati, deoarece daca am creste cu 3 unitati, pasarea ar merge in jos
    pozitieJucator++;  //efectul de gravitatie
    if (pozitieJucator < 1) {   // daca ar iesi, iese de tot din chenar
        pozitieJucator = 1;  // sa fie mereu valoarea 1
    }
    if (pozitieJucator > 18) {
        pozitieJucator = 18; //aceeasi explicatie
    }
}

void Joc::reseteazaObstacole() {
    for (int i = 0; i < 3; ++i) {
        obstacoleY[i] = rand() % 12 + 2;//reseteaza pozitiile Y ale obstacolelor /rand-generarea de nr aleatorii
    }
}

void Joc::creeazaHarta() {
    //initializeaza harta cu dimensiunile de 20x30 si celulele goale reprezentate  de doua spatii
    harta = std::vector<std::vector<std::string>>(20, std::vector<std::string>(30, "  "));
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 30; ++j) {
            if (i == 0 || i == 19 || j == 29 || j == 0)
                harta[i][j] = "* "; //pentru margini 
        }//initializata si pe i si pe j pentru a face chenar
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 19; ++j) {
            if (j < obstacoleY[i] || j >= obstacoleY[i] + 5) {
                harta[j][obstacoleX[i]] = "| "; // pentru obstacole
            } // face doar pe axa j obstacole, punand pe i ---> |
        }
    }

    for (int i = 0; i < powerUpsX.size(); ++i) {
        harta[powerUpsY[i]][powerUpsX[i]] = "+ ";
    }

    harta[pozitieJucator][3] = std::string(1, nivele.getSimbolPasareCurent()) + " "; //pentru a lua simbolul de la nivele
}

void Joc::verificaColiziune() {
    for (int i = 0; i < 3; ++i) {
        if (obstacoleX[i] == 3 && (pozitieJucator < obstacoleY[i] || pozitieJucator >= obstacoleY[i] + 5)) {
            --vieti;
            /*vieti.pierdeViata();*/ // metoda fara supraincarcarea operatorilor, din versiunea 2.0
            //apeleaza clasa si functia ei
            if (vieti.getVieti() <= 0) {
                Ruleaza = false;
            }
            else {
                obstacoleX[i] = 28; 
                obstacoleY[i] = rand() % 12 + 2;
            }
        }
    }

    for (int i = 0; i < powerUpsX.size(); ++i) {
        if (powerUpsX[i] == 3 && powerUpsY[i] == pozitieJucator) {
            ++vieti;
            /*vieti.castigaViata();*/ //metoda din versiunea 2.0, fara supraincarcarea operatorilor
            powerUpsX.erase(powerUpsX.begin() + i); //sterge elementul de la pozitia i
            powerUpsY.erase(powerUpsY.begin() + i);
            break;
        }
    }
}

void Joc::actualizeazaScor() {
    for (int i = 0; i < 3; ++i) {
        if (obstacoleX[i] == 3 && pozitieJucator >= obstacoleY[i] && pozitieJucator < obstacoleY[i] + 5) {
            scor++;
        }
    }
}

void Joc::salveazaScoruri() {
    std::ofstream file("scorul.txt", std::ios::app);
    if (file.is_open()) {
        file << "Scor: " << scor << "\n";
        file.close();
    }
}

void Joc::plaseazaPowerUps() {
    powerUpsX.clear();
    powerUpsY.clear();
    for (int i = 0; i < 3; ++i) {
        powerUpsX.push_back(rand() % 25 + 4); // pune power-ups in diferite pozitii aleatorii
        powerUpsY.push_back(rand() % 18 + 1); 
        //functia push_back adauga la sfarsitului vectorului un +
    }
}

void Joc::actualizeazaPowerUps() {
    for (int i = 0; i < powerUpsX.size(); ++i) {
        powerUpsX[i]--; // misca power-ups spre stanga
    }
    for (int i = 0; i < powerUpsX.size(); ++i) {
        if (powerUpsX[i] < 1) {
            powerUpsX[i] = rand() % 25 + 4;  // resetează power-ups la marginea dreapta a ecranului
            powerUpsY[i] = rand() % 18 + 1;
        }
    }
    while (powerUpsX.size() < 3) {         //asta e pentru genereare continuua, cauzeaza putin lag
        powerUpsX.push_back(rand() % 25 + 4);
        powerUpsY.push_back(rand() % 18 + 1);
    }
}


Joc::~Joc() {} //destructor

// Functie recursiva pentru a numara obstacolele
int Joc::numaraObstacole(int index) {
    if (index >= obstacoleX.size()) {  // Cazul de baza: am ajuns la sfarsitul vectorului
        return 0;
    }
    if (obstacoleX[index] >= 1 && obstacoleX[index] < 28) {  // Obstacol activ
        return 1 + numaraObstacole(index + 1);
    }
    return numaraObstacole(index + 1);  // Obstacol inactiv
}

