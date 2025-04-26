#include "Receptioner.h"
#include <iostream>
#include <vector>

Receptioner::Receptioner(): Angajat(), m_schimb("-"), m_limbi_vorbite() {}; //Constructor implicit

Receptioner::Receptioner(std::string nume, std::string email, int varsta, int id_angajat, int salariu, std::string functie, std::string schimb, std::vector <std::string> limbi_vorbite): 
Angajat(nume,email,varsta,id_angajat,salariu,functie), m_schimb(schimb), m_limbi_vorbite(limbi_vorbite) {}; //Constructor parametrizat

Receptioner::Receptioner(const Receptioner& obj): Angajat(obj), m_schimb(obj.m_schimb), m_limbi_vorbite(obj.m_limbi_vorbite) {}; //Copy constructor

Receptioner::~Receptioner() {}; //Destructor

//Getteri si setteri
std::string Receptioner::GetSchimb() const { return m_schimb; };
std::vector <std::string> Receptioner::GetLimbi() const { return m_limbi_vorbite; };

void Receptioner::SetSchimb(std::string schimb) { m_schimb=schimb; };

//Metode suplimentare
void Receptioner::AfisareDetalii() const
{
    std::cout<<"Nume: "<<GetNume()<<"\n";
    std::cout<<"Email: "<<GetEmail()<<"\n";
    std::cout<<"Varsta: "<<GetVarsta()<<"\n";
    std::cout<<"ID Angajat: "<<GetId()<<"\n";
    std::cout<<"Salariu: "<<GetSalariu()<<"\n";
    std::cout<<"Functie: "<<GetFunctie()<<"\n";
    std::cout<<"Schimb: "<<GetSchimb()<<"\n";
    if(!m_limbi_vorbite.empty())
    {
        std::cout<<"Limbi vorbite: \n";
        for(auto& l : GetLimbi())
            std::cout<<l<<" ";
        std::cout<<"\n";
    }
}

void Receptioner::AdaugaLimba(std::string limba)
{
    for(auto& l : m_limbi_vorbite)
    {
        if(l==limba)
        {
            std::cout<<"Angajatul vorbeste deja limba introdusa\n";
            return;
        }
    }
    m_limbi_vorbite.push_back(limba);
    std::cout<<"Limba selectata a fost adaugata cu succes!\n";
}

void Receptioner::EliminaLimba(std::string limba)
{
    int pozitie=0;
    bool ok=0;
    for(auto& l : m_limbi_vorbite)
    {
        if(l==limba)
        {
            m_limbi_vorbite.erase(m_limbi_vorbite.begin()+pozitie);
            ok=1;
            std::cout<<"Limba selectata a fost eliminata.\n";
            return;
        }
        pozitie++;
    }
    if(ok==0)
    {
        std::cout<<"Limba nu a fost gasita in lista\n";
    }
}

//Operator overloading +
Angajat* Receptioner::operator+(int suma) const {
    Receptioner* copie = new Receptioner(*this); //Copy constructor
    copie->SetSalariu(this->GetSalariu() + suma);
    return copie;
}
