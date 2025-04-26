#include "Ingrijitor.h"
#include <iostream>

Ingrijitor::Ingrijitor(): Angajat(), m_etaj_curatenie(-1) {}; //Constructor implicit - pentru atributele mostenite se apeleaza constructorul mostenit

Ingrijitor::Ingrijitor(std::string nume, std::string email, int varsta, int id_angajat, int salariu, std::string functie, int etaj_curatenie):
Angajat(nume,email,varsta,id_angajat,salariu,functie), m_etaj_curatenie(etaj_curatenie) {}; //Constructor parametrizat

Ingrijitor::Ingrijitor(const Ingrijitor& obj): Angajat(obj), m_etaj_curatenie(obj.m_etaj_curatenie) {}; //Copy constructor

Ingrijitor::~Ingrijitor() {}; //Destructor

//Getteri si setteri
int Ingrijitor::GetEtaj() const { return m_etaj_curatenie; };

void Ingrijitor::SetEtaj(int etaj_curatenie) { m_etaj_curatenie=etaj_curatenie; };

//Metode suplimentare
void Ingrijitor::AfisareDetalii() const
{
    std::cout<<"Nume: "<<GetNume()<<"\n";
    std::cout<<"Email: "<<GetEmail()<<"\n";
    std::cout<<"Varsta: "<<GetVarsta()<<"\n";
    std::cout<<"ID Angajat: "<<GetId()<<"\n";
    std::cout<<"Salariu: "<<GetSalariu()<<"\n";
    std::cout<<"Functie: "<<GetFunctie()<<"\n";
    std::cout<<"Etaj atribuit pentru ingrijire: "<<GetEtaj()<<"\n";
}

//Operator overloading +
Angajat* Ingrijitor::operator+(int suma) const {
    Ingrijitor* copie = new Ingrijitor(*this); //Copy constructor
    copie->SetSalariu(this->GetSalariu() + suma);
    return copie;
}