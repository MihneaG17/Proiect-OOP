#include "Angajat.h"
#include <iostream>

//Constructori si Destructor
Angajat::Angajat():Persoana(), id_angajat(0), salariu(0), functie("Nedefinit") {}; //Constructor implicit - Fiind o clasa derivata din clasa de baza Persoana,
//Pentru atributele mostenite se apeleaza constructorul clasei de baza

Angajat::Angajat(std::string nume, std::string email, int varsta, int id_angajat, int salariu, std::string functie):Persoana(nume, email, varsta),
id_angajat(id_angajat), salariu(salariu), functie(functie) {}; //Constructor parametrizat - Fiind o clasa derivata din clasa de baza Persoana,
//Pentru atributele mostenite se apeleaza constructorul clasei de baza

Angajat::Angajat(const Angajat& a):Persoana(a), id_angajat(a.id_angajat), salariu(a.salariu), functie(a.functie){}; //Copy constructor

Angajat::~Angajat() {} //Destructor

//Getteri si setteri specifici pentru clasa Angajat (cei din clasa de baza Persoana fiind mosteniti)
int Angajat::getId() { return id_angajat; };
int Angajat::getSalariu() { return salariu; };
std::string Angajat::getFunctie() { return functie; };

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

void Angajat::MarireSalariala(int procent)
{
    salariu=salariu+(procent*salariu)/100;
};
void Angajat::MinorareSalariala(int procent)
{
    salariu=salariu-(procent*salariu)/100;
};

void Angajat::afisareDetaliiAngajat() const
{
    afisareDetalii();
    std::cout<<"ID Angajat: "<<id_angajat<<"\n";
    std::cout<<"Salariu: "<<salariu<<"\n";
    std::cout<<"Functie: "<<functie<<"\n";
};