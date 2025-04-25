#include "Ingrijitor.h"
#include <iostream>

Ingrijitor::Ingrijitor(): Angajat(), etaj_curatenie(-1) {}; //Constructor implicit - pentru atributele mostenite se apeleaza constructorul mostenit

Ingrijitor::Ingrijitor(std::string nume, std::string email, int varsta, int id_angajat, int salariu, std::string functie, int etaj_curatenie):
Angajat(nume,email,varsta,id_angajat,salariu,functie), etaj_curatenie(etaj_curatenie) {}; //Constructor parametrizat

Ingrijitor::Ingrijitor(const Ingrijitor& obj): Angajat(obj), etaj_curatenie(obj.etaj_curatenie) {}; //Copy constructor

Ingrijitor::~Ingrijitor() {}; //Destructor

//Getteri si setteri
int Ingrijitor::getEtaj() const { return etaj_curatenie; };

void Ingrijitor::setEtaj(int etaj_curatenie) { this->etaj_curatenie=etaj_curatenie; };

//Metode suplimentare
void Ingrijitor::afisareDetalii() const
{
    std::cout<<"Nume: "<<getNume()<<"\n";
    std::cout<<"Email: "<<getEmail()<<"\n";
    std::cout<<"Varsta: "<<getVarsta()<<"\n";
    std::cout<<"ID Angajat: "<<getId()<<"\n";
    std::cout<<"Salariu: "<<getSalariu()<<"\n";
    std::cout<<"Functie: "<<getFunctie()<<"\n";
    std::cout<<"Etaj atribuit pentru ingrijire: "<<etaj_curatenie<<"\n";
}

//Operator overloading +
Angajat* Ingrijitor::operator+(int suma) const {
    Ingrijitor* copie = new Ingrijitor(*this); //Copy constructor
    copie->setSalariu(this->getSalariu() + suma);
    return copie;
}