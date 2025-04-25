#ifndef ANGAJAT_H
#define ANGAJAT_H

#include "Persoana.h"
#include <iostream>

struct StatisticiAngajat {
    //Variabile declarate statice - apartin struct-ului, nu instantelor (obiectelor)
    static int totalAngajati;
    static int salariuTotal;
    static int salariuMinim;
    static int salariuMaxim;

    //Metode
    static void adaugaSalariu(int salariu);
    static void eliminaSalariu(int salariu);
    static double salariuMediu();
};

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
    //void MarireSalariala(int procent);
    //Am comentat metoda MarireSalariala deoarece maresc salariul folosind operatorul supraincarcat +
    void MinorareSalariala(int procent);
    void afisareDetalii() const override;

    //Operator overloading + (marire salariala)
    virtual Angajat* operator+(int suma) const; //pentru marire - virtual deoarece va fi rescris pentru fiecare tip de angajat
    
};

#endif //ANGAJAT_H