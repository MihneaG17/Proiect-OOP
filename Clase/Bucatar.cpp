#include "Bucatar.h"
#include <iostream>
#include <vector>

Bucatar::Bucatar(): Angajat(), m_specializare("-"), m_certificari() {}; //Constructor implicit

Bucatar::Bucatar(std::string nume, std::string email, int varsta, int id_angajat, int salariu, std::string functie, std::string specializare, std::vector <std::string> certificari): 
Angajat(nume,email,varsta,id_angajat,salariu,functie), m_specializare(specializare), m_certificari(certificari) {}; //Constructor parametrizat

Bucatar::Bucatar(const Bucatar& obj): Angajat(obj), m_specializare(obj.m_specializare), m_certificari(obj.m_certificari) {}; //Copy constructor

Bucatar::~Bucatar() {}; //Destructor

//Getteri si setteri
std::string Bucatar::GetSpecializare() const { return m_specializare; };
std::vector<std::string> Bucatar::GetCertificari() const { return m_certificari; };

void Bucatar::SetSpecializare(std::string specializare) { m_specializare=specializare; };

//Metode suplimentare

void Bucatar::AfisareDetalii() const
{
    std::cout<<"Nume: "<<GetNume()<<"\n";
    std::cout<<"Email: "<<GetEmail()<<"\n";
    std::cout<<"Varsta: "<<GetVarsta()<<"\n";
    std::cout<<"ID Angajat: "<<GetId()<<"\n";
    std::cout<<"Salariu: "<<GetSalariu()<<"\n";
    std::cout<<"Functie: "<<GetFunctie()<<"\n";
    std::cout<<"Specializare: "<<GetSpecializare()<<"\n";
    if(!m_certificari.empty())
    {
        std::cout<<"Certificari: \n";
        for(auto& certificare : GetCertificari())
            std::cout<<certificare<<" ";
        std::cout<<"\n";
    }
}

void Bucatar::AdaugaCertificare(std::string certificare)
{
    for(auto& c : m_certificari)
    {
        if(c==certificare)
        {
            std::cout<<"Angajatul detine deja certificarea introdusa\n";
            return;
        }
    }
    m_certificari.push_back(certificare);
    std::cout<<"Certificarea a fost adaugata cu succes!\n";
}

void Bucatar::EliminaCertificare(std::string certificare)
{
    int pozitie=0;
    bool ok=0;
    for(auto& c : m_certificari)
    {
        if(c==certificare)
        {
            m_certificari.erase(m_certificari.begin()+pozitie);
            ok=1;
            std::cout<<"Certificarea selectata a fost eliminata.\n";
            return;
        }
        pozitie++;
    }
    if(ok==0)
    {
        std::cout<<"Certificarea nu a fost gasita in lista\n";
    }
}

//Operator overloading +
Angajat* Bucatar::operator+(int suma) const {
    Bucatar* copie = new Bucatar(*this); //Copy constructor
    copie->SetSalariu(this->GetSalariu() + suma);
    return copie;
}