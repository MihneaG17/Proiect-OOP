#include "Persoana.h"
#include <iostream>

//Constructori si destructor
Persoana::Persoana(): nume("Necunoscut"), email("Necunoscut"), varsta(0) {}; //Constructor implicit - initializeaza atributele obiectului dinainte sa fie creat
//Daca ar fi fost de forma Persoana() { nume=....} atunci obiectul ar fi fost mai intai creat, apoi initializat

Persoana::Persoana(std::string nume, std::string email, int varsta):
nume(nume), email(email), varsta(varsta) {}; //Constructor parametrizat - initializeaza atributele cu cele primite ca argumente

Persoana::Persoana(const Persoana& p): nume(p.nume), email(p.email), varsta(p.varsta) {}; // Copy constructor - takes a reference to an object of the same class as an argument - const so we don`t modify de object by mistake

Persoana::~Persoana() {}  //Destructor

Persoana& Persoana::operator=(const Persoana& p) //Suprascrierea operatorului de atribuire
    {
    if(this != &p)
    {
        nume=p.nume;
        email=p.email;
        varsta=p.varsta;
    }
    return *this;
    }

//Getteri pentru atribute
std::string Persoana::getNume() { return nume; }
std::string Persoana::getEmail() { return email; }
int Persoana::getVarsta() { return varsta; }

//Setteri pentru atribute
void Persoana::setNume(std::string nume) { this->nume=nume; }
void Persoana::setEmail(std::string email) { this->email=email; }
void Persoana::setVarsta(int varsta) 
{
    if(varsta<0)
        std::cout<<"Varsta trebuie sa fie un numar pozitiv";
    else
        this->varsta=varsta;
}

//Metode suplimentare
void Persoana::afisareDetalii() const
    {
        std::cout<<"Nume: "<<nume<<"\n";
        std::cout<<"Email: "<<email<<"\n";
        std::cout<<"Varsta: "<<varsta<<"\n";
    }