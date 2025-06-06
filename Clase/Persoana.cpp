#include "Persoana.h"
#include <iostream>

namespace HotelManagement {

//Constructori si destructor
Persoana::Persoana(): m_nume("Necunoscut"), m_email("Necunoscut"), m_varsta(0) {}; //Constructor implicit - initializeaza atributele obiectului dinainte sa fie creat

Persoana::Persoana(std::string nume, std::string email, int varsta):
m_nume(nume), m_email(email), m_varsta(varsta) {}; //Constructor parametrizat - initializeaza atributele cu cele primite ca argumente

Persoana::Persoana(const Persoana& p): m_nume(p.m_nume), m_email(p.m_email), m_varsta(p.m_varsta) {}; // Copy constructor - takes a reference to an object of the same class as an argument - const so we don`t modify de object by mistake

Persoana::~Persoana() {}  //Destructor


//Getteri pentru atribute
std::string Persoana::GetNume() const { return m_nume; }
std::string Persoana::GetEmail() const { return m_email; }
int Persoana::GetVarsta() const { return m_varsta; }

//Setteri pentru atribute
void Persoana::SetNume(std::string nume) { m_nume=nume; }
void Persoana::SetEmail(std::string email) { m_email=email; }
void Persoana::SetVarsta(int varsta) 
{
    if(varsta<0)
        std::cout<<"Varsta trebuie sa fie un numar pozitiv";
    else
        m_varsta=varsta;
}

//Metoda AfiseazaDetalii() este suprascrisa in clasele derivate
}