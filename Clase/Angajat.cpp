#include "Angajat.h"
#include <iostream>

//Metodele si variabilele din struct StatisticiAngajati
int StatisticiAngajat::totalAngajati=0;
int StatisticiAngajat::salariuTotal=0;
int StatisticiAngajat::salariuMinim=INT_MAX;
int StatisticiAngajat::salariuMaxim=INT_MIN;

void StatisticiAngajat::adaugaSalariu(int salariu) {
    salariuTotal+=salariu;
    totalAngajati++;
    if(salariu<salariuMinim) 
        salariuMinim=salariu;
    if(salariu>salariuMaxim)
        salariuMaxim=salariu;
}

void StatisticiAngajat::eliminaSalariu(int salariu)
{
    salariuTotal-=salariu;
    totalAngajati--;
    //salariuMin/Max trebuie recalculate
}

double StatisticiAngajat::salariuMediu()
{
    return totalAngajati==0 ? 0 : static_cast<double>(salariuTotal)/totalAngajati;
}

//Clasa Angajat

//Constructori si Destructor
Angajat::Angajat():Persoana(), id_angajat(0), salariu(0), functie("Nedefinit") {}; //Constructor implicit - Fiind o clasa derivata din clasa de baza Persoana,
//Pentru atributele mostenite se apeleaza constructorul clasei de baza

Angajat::Angajat(std::string nume, std::string email, int varsta, int id_angajat, int salariu, std::string functie):Persoana(nume, email, varsta),
id_angajat(id_angajat), salariu(salariu), functie(functie) 
{
    StatisticiAngajat::adaugaSalariu(salariu);
}; 
//Constructor parametrizat - Fiind o clasa derivata din clasa de baza Persoana,
//Pentru atributele mostenite se apeleaza constructorul clasei de baza

Angajat::Angajat(const Angajat& a):Persoana(a), id_angajat(a.id_angajat), salariu(a.salariu), functie(a.functie){}; //Copy constructor

Angajat::~Angajat() 
{
    StatisticiAngajat::eliminaSalariu(salariu);
} //Destructor

//Getteri si setteri specifici pentru clasa Angajat (cei din clasa de baza Persoana fiind mosteniti)
int Angajat::getId() const { return id_angajat; };
int Angajat::getSalariu() const { return salariu; };
std::string Angajat::getFunctie() const { return functie; };

void Angajat::setId(int id_angajat) { this->id_angajat=id_angajat; };
void Angajat::setSalariu(int salariu)
{
    if(salariu<0)
        std::cout<<"Salariul trebuie sa fie un numar pozitiv";
    else
        this->salariu=salariu;
};
void Angajat::setFunctie(std::string functie) { this->functie=functie; };

//Metode suplimentare

// void Angajat::MarireSalariala(int procent)
// {
//     salariu=salariu+(procent*salariu)/100;
// };

void Angajat::MinorareSalariala(int procent)
{
    salariu=salariu-(procent*salariu)/100;
};

void Angajat::afisareDetalii() const
{
    std::cout<<"Nume: "<<getNume()<<"\n";
    std::cout<<"Email: "<<getEmail()<<"\n";
    std::cout<<"Varsta: "<<getVarsta()<<"\n";
    std::cout<<"ID Angajat: "<<id_angajat<<"\n";
    std::cout<<"Salariu: "<<salariu<<"\n";
    std::cout<<"Functie: "<<functie<<"\n";
};

//Operator overloading +
Angajat* Angajat::operator+(int suma) const
{
    Angajat* copie = new Angajat(*this); //copie dupa obiectul original
    copie->salariu += suma;
    return copie;
}