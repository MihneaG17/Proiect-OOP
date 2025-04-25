#include "Receptioner.h"
#include <iostream>
#include <vector>

Receptioner::Receptioner(): Angajat(), schimb("N/A"), limbi_vorbite() {}; //Constructor implicit

Receptioner::Receptioner(std::string nume, std::string email, int varsta, int id_angajat, int salariu, std::string functie, std::string schimb, std::vector <std::string> limbi_vorbite): 
Angajat(nume,email,varsta,id_angajat,salariu,functie), schimb(schimb), limbi_vorbite(limbi_vorbite) {}; //Constructor parametrizat

Receptioner::Receptioner(const Receptioner& obj): Angajat(obj), schimb(obj.schimb), limbi_vorbite(obj.limbi_vorbite) {}; //Copy constructor

Receptioner::~Receptioner() {}; //Destructor

//Getteri si setteri
std::string Receptioner::getSchimb() const { return schimb; };
std::vector <std::string> Receptioner::getLimbi() const { return limbi_vorbite; };

void Receptioner::setSchimb(std::string schimb) { this->schimb=schimb; };

//Metode suplimentare
void Receptioner::afisareDetalii() const
{
    std::cout<<"Nume: "<<getNume()<<"\n";
    std::cout<<"Email: "<<getEmail()<<"\n";
    std::cout<<"Varsta: "<<getVarsta()<<"\n";
    std::cout<<"ID Angajat: "<<getId()<<"\n";
    std::cout<<"Salariu: "<<getSalariu()<<"\n";
    std::cout<<"Functie: "<<getFunctie()<<"\n";
    std::cout<<"Schimb: "<<schimb<<"\n";
    if(!limbi_vorbite.empty())
    {
        std::cout<<"Limbi vorbite: \n";
        for(auto& a : limbi_vorbite)
            std::cout<<a<<" ";
        std::cout<<"\n";
    }
}

void Receptioner::adaugaLimba(std::string limba)
{
    for(auto& a : limbi_vorbite)
    {
        if(a==limba)
        {
            std::cout<<"Angajatul vorbeste deja limba introdusa\n";
            return;
        }
    }
    limbi_vorbite.push_back(limba);
    std::cout<<"Limba selectata a fost adaugata cu succes!\n";
}

void Receptioner::eliminaLimba(std::string limba)
{
    int pozitie=0;
    bool ok=0;
    for(auto& a : limbi_vorbite)
    {
        if(a==limba)
        {
            limbi_vorbite.erase(limbi_vorbite.begin()+pozitie);
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
    copie->setSalariu(this->getSalariu() + suma);
    return copie;
}
