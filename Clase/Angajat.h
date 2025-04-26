#ifndef ANGAJAT_H
#define ANGAJAT_H

#include "Persoana.h"
#include <iostream>

struct StatisticiAngajat {
    //Variabile declarate statice - apartin struct-ului, nu instantelor (obiectelor)
    static int total_angajati;
    static int salariu_total;
    static int salariu_minim;
    static int salariu_maxim;

    //Metode
    static void AdaugaSalariu(int salariu);
    static void EliminaSalariu(int salariu);
    static double SalariuMediu();
};

class Angajat: public Persoana
{
    int m_id_angajat;
    int m_salariu;
    std::string m_functie;

public:
    Angajat(); //Constructor predefinit
    Angajat(std::string nume, std::string email, int varsta, int id_angajat, int salariu, std::string functie); //Constructor parametrizat
    Angajat(const Angajat& a); //Copy Constructor

    ~Angajat(); //Destructor

    //Getteri si setteri specifici pentru clasa Angajat (cei din clasa de baza Persoana fiind mosteniti)
    int GetId() const;
    int GetSalariu() const;
    std::string GetFunctie() const;

    void SetId(int id_angajat);
    void SetSalariu(int salariu);
    void SetFunctie(std::string functie);

    //Metode suplimentare
    //void MarireSalariala(int procent);
    //Am comentat metoda MarireSalariala deoarece maresc salariul folosind operatorul supraincarcat +
    void MinorareSalariala(int procent);
    void AfisareDetalii() const override;

    //Operator overloading + (marire salariala)
    virtual Angajat* operator+(int suma) const; //pentru marire - virtual deoarece va fi rescris pentru fiecare tip de angajat
    
};

#endif //ANGAJAT_H