#include "Bucatar.h"
#include <iostream>
#include <vector>

Bucatar::Bucatar(): Angajat(), specializare("N/A"), certificari() {}; //Constructor implicit

Bucatar::Bucatar(std::string nume, std::string email, int varsta, int id_angajat, int salariu, std::string functie, std::string specializare, std::vector <std::string> certificari): 
Angajat(nume,email,varsta,id_angajat,salariu,functie), specializare(specializare), certificari(certificari) {}; //Constructor parametrizat

Bucatar::Bucatar(const Bucatar& obj): Angajat(obj), specializare(obj.specializare), certificari(obj.certificari) {}; //Copy constructor

Bucatar::~Bucatar() {}; //Destructor

//Getteri si setteri
std::string Bucatar::getSpecializare() const { return specializare; };
std::vector<std::string> Bucatar::getCertificari() const { return certificari; };

void Bucatar::setSpecializare(std::string specializare) { this->specializare=specializare; };

//Metode suplimentare

void Bucatar::afisareDetalii() const
{
    std::cout<<"Nume: "<<getNume()<<"\n";
    std::cout<<"Email: "<<getEmail()<<"\n";
    std::cout<<"Varsta: "<<getVarsta()<<"\n";
    std::cout<<"ID Angajat: "<<getId()<<"\n";
    std::cout<<"Salariu: "<<getSalariu()<<"\n";
    std::cout<<"Functie: "<<getFunctie()<<"\n";
    std::cout<<"Specializare: "<<specializare<<"\n";
    if(!certificari.empty())
    {
        std::cout<<"Certificari: \n";
        for(auto& a : certificari)
            std::cout<<a<<" ";
        std::cout<<"\n";
    }
}

void Bucatar::adaugaCertificare(std::string certificare)
{
    for(auto& a : certificari)
    {
        if(a==certificare)
        {
            std::cout<<"Angajatul detine deja certificarea introdusa\n";
            return;
        }
    }
    certificari.push_back(certificare);
    std::cout<<"Certificarea a fost adaugata cu succes!\n";
}

void Bucatar::eliminaCertificare(std::string certificare)
{
    int pozitie=0;
    bool ok=0;
    for(auto& a : certificari)
    {
        if(a==certificare)
        {
            certificari.erase(certificari.begin()+pozitie);
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
    copie->setSalariu(this->getSalariu() + suma);
    return copie;
}