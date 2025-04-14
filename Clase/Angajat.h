#ifndef ANGAJAT_H
#define ANGAJAT_H

#include "Persoana.h"
#include <iostream>

class Angajat: public Persoana
{
    int id_angajat;
    int salariu;
    std::string functie;

public:
    Angajat(); //Constructor predefinit
    Angajat(std::string nume, std::string email, int varsta, int id_angajat, int salariu, std::string functie); //Constructor parametrizat
    Angajat(const Angajat& a); //Copy Constructor

    ~Angajat(); //Destructor

    //Getteri si setteri specifici pentru clasa Angajat (cei din clasa de baza Persoana fiind mosteniti)
    int getId() const;
    int getSalariu() const;
    std::string getFunctie() const;

    void setId(int id_angajat);
    void setSalariu(int salariu);
    void setFunctie(std::string functie);

    //Metode suplimentare
    void MarireSalariala(int procent);
    void MinorareSalariala(int procent);
    void afisareDetalii() const override;
};

#endif //ANGAJAT_H