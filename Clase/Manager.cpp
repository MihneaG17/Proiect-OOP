#include "Manager.h"
#include <iostream>
#include <vector>

Manager::Manager() : Angajat(), departamenteCoordonate(), aniExperienta(0) {} //Constructor implicit

Manager::Manager(std::string nume, std::string email, int varsta, int id_angajat, int salariu, std::string functie, std::vector<std::string> departamenteCoordonate, int aniExperienta)
    : Angajat(nume, email, varsta, id_angajat, salariu, functie), departamenteCoordonate(departamenteCoordonate), aniExperienta(aniExperienta) {}; //Constructor parametrizat

Manager::Manager(const Manager& obj)
    : Angajat(obj), departamenteCoordonate(obj.departamenteCoordonate), aniExperienta(obj.aniExperienta) {}; //Copy constructor

Manager::~Manager() {}; //Destructor

// Getteri si setteri
std::vector<std::string> Manager::getDepartamente() const { return departamenteCoordonate; }
int Manager::getExperienta() const { return aniExperienta; }

void Manager::setDepartamente(std::vector<std::string> departamente)
{
    departamenteCoordonate = departamente;
}

void Manager::setExperienta(int ani)
{
    if (ani < 0)
        std::cout << "Anii de experienta trebuie sa fie un numar pozitiv.\n";
    else
        aniExperienta = ani;
}

// Metode suplimentare
void Manager::afisareDetalii() const
{
    std::cout << "Nume: " << getNume() << "\n";
    std::cout << "Email: " << getEmail() << "\n";
    std::cout << "Varsta: " << getVarsta() << "\n";
    std::cout << "ID Angajat: " << getId() << "\n";
    std::cout << "Salariu: " << getSalariu() << "\n";
    std::cout << "Functie: " << getFunctie() << "\n";
    std::cout << "Ani experienta in management: " << aniExperienta << "\n";
    if (!departamenteCoordonate.empty())
    {
        std::cout << "Departamente coordonate: ";
        for (auto& dept : departamenteCoordonate)
            std::cout << dept << " ";
        std::cout << "\n";
    }
}

void Manager::adaugaDepartament(std::string dept)
{
    for(auto& a : departamenteCoordonate)
    {
        if(a==dept)
        {
            std::cout<<"Departamentul se afla deja in lista\n";
            return;
        }
    }
    departamenteCoordonate.push_back(dept);
    std::cout<<"Departamentul a fost adaugata cu succes!\n";
}

void Manager::eliminaDepartament(std::string dept)
{
    int pozitie=0;
    bool ok=0;
    for(auto& a : departamenteCoordonate)
    {
        if(a==dept)
        {
            departamenteCoordonate.erase(departamenteCoordonate.begin()+pozitie);
            ok=1;
            std::cout<<"Departamentul selectat a fost eliminat.\n";
            return;
        }
        pozitie++;
    }
    if(ok==0)
    {
        std::cout<<"Departamentul nu a fost gasit in lista\n";
    }
}

Angajat* Manager::operator+(int suma) const {
    Manager* copie = new Manager(*this); //Copy constructor
    copie->setSalariu(this->getSalariu() + suma);
    return copie;
}
