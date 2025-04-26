#include "Manager.h"
#include <iostream>
#include <vector>

Manager::Manager() : Angajat(), m_departamente_coordonate(), m_ani_experienta(0) {} //Constructor implicit

Manager::Manager(std::string nume, std::string email, int varsta, int id_angajat, int salariu, std::string functie, std::vector<std::string> departamente_coordonate, int ani_experienta)
    : Angajat(nume, email, varsta, id_angajat, salariu, functie), m_departamente_coordonate(departamente_coordonate), m_ani_experienta(ani_experienta) {}; //Constructor parametrizat

Manager::Manager(const Manager& obj)
    : Angajat(obj), m_departamente_coordonate(obj.m_departamente_coordonate), m_ani_experienta(obj.m_ani_experienta) {}; //Copy constructor

Manager::~Manager() {}; //Destructor

// Getteri si setteri
std::vector<std::string> Manager::GetDepartamente() const { return m_departamente_coordonate; }
int Manager::GetExperienta() const { return m_ani_experienta; }

void Manager::SetDepartamente(std::vector<std::string> departamente)
{
    m_departamente_coordonate = departamente;
}

void Manager::SetExperienta(int ani)
{
    if (ani < 0)
        std::cout << "Anii de experienta trebuie sa fie reprezentati de un numar pozitiv.\n";
    else
        m_ani_experienta = ani;
}

// Metode suplimentare
void Manager::AfisareDetalii() const
{
    std::cout << "Nume: " << GetNume() << "\n";
    std::cout << "Email: " << GetEmail() << "\n";
    std::cout << "Varsta: " << GetVarsta() << "\n";
    std::cout << "ID Angajat: " << GetId() << "\n";
    std::cout << "Salariu: " << GetSalariu() << "\n";
    std::cout << "Functie: " << GetFunctie() << "\n";
    std::cout << "Ani experienta in management: " << GetExperienta() << "\n";
    if (!m_departamente_coordonate.empty())
    {
        std::cout << "Departamente coordonate: ";
        for (auto& dept : GetDepartamente())
            std::cout << dept << " ";
        std::cout << "\n";
    }
}

void Manager::AdaugaDepartament(std::string dept)
{
    for(auto& d : m_departamente_coordonate)
    {
        if(d==dept)
        {
            std::cout<<"Departamentul se afla deja in lista\n";
            return;
        }
    }
    m_departamente_coordonate.push_back(dept);
    std::cout<<"Departamentul a fost adaugata cu succes!\n";
}

void Manager::EliminaDepartament(std::string dept)
{
    int pozitie=0;
    bool ok=0;
    for(auto& d : m_departamente_coordonate)
    {
        if(d==dept)
        {
            m_departamente_coordonate.erase(m_departamente_coordonate.begin()+pozitie);
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
    copie->SetSalariu(this->GetSalariu() + suma);
    return copie;
}
